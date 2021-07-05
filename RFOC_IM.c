#define S_FUNCTION_LEVEL 2 
#define S_FUNCTION_NAME RFOC_IM
#include "simstruc.h" 
#include <math.h> 

#define U(element) (*uPtrs[element]) /*Pointer to Input Port0*/ 

static void mdlInitializeSizes(SimStruct *S){ 

    ssSetNumDiscStates(S, 5); 

    if (!ssSetNumInputPorts(S, 1)) return; 
    ssSetInputPortWidth(S, 0, 12); 
    ssSetInputPortDirectFeedThrough(S, 0, 1); 
    ssSetInputPortOverWritable(S, 0, 1); 

    if (!ssSetNumOutputPorts(S, 1)) return; 
    ssSetOutputPortWidth(S, 0, 3); 
    ssSetNumSampleTimes(S, 1); 

    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE 
    | SS_OPTION_DISCRETE_VALUED_OUTPUT));
} 

static void mdlInitializeSampleTimes(SimStruct *S){ 
    ssSetSampleTime(S, 0, 1e-4); 
    ssSetOffsetTime(S, 0, 0.0);
} 

#define MDL_INITIALIZE_CONDITIONS 
    static void mdlInitializeConditions(SimStruct *S){ 
    real_T *X0 = ssGetRealDiscStates(S); 
    int_T nXStates = ssGetNumDiscStates(S); 
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0); 
    int_T i; 

    /* initialize the states to 0.0 */ 
    for (i=0; i < nXStates; i++) { 
    X0[i] = 0.0; } } 

static void mdlOutputs(SimStruct *S, int_T tid){ 
    real_T *Y = ssGetOutputPortRealSignal(S,0); 
    real_T *X = ssGetRealDiscStates(S); 

    real_T Va = X[2];
    real_T Vb = X[3];
    real_T Vc = X[4];

    Y[0] = Va;
    Y[1] = Vb;
    Y[2] = Vc;

} 

#define MDL_UPDATE 
static void mdlUpdate(SimStruct *S, int_T tid) { 
    real_T *X = ssGetRealDiscStates(S); 
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0); 

    real_T dt = 1e-4;
    //Variabel Input
    real_T Id_ref,Iq_ref,Ia,Ib,Ic,Kpd,Kid,Kpq,Kiq,imr,wr,Thetae;

    //Variabel RFOC
    real_T vds_ref,vqs_ref,Valfa,Vbeta,Va,Vb,Vc;

    //Variabel Transformasi
    real_T Ialfa,Ibeta,Id,Iq;

    //Parameter Motor
    real_T Lm=0.2279, Ls=0.2349, Lr=0.2349;
    real_T Rs=2.76, Rr=2.9;
    real_T a0=1/( Lm*Lm-Ls*Lr);
    real_T K=0.816497, L=0.866025;
    real_T B =0.0005, J=0.0436, Np=2.0;

    //Konstanta Transformasi
    real_T A    = 0.81649658092;    // sqrt(2/3)
    real_T Q    = 0.86602540378;    // sqrt(3)/2

    //Ambil Input
    Id_ref  = U(0);
    Kpd     = U(1);
    Kid     = U(2);
    Iq_ref  = U(3);
    Kpq     = U(4);
    Kiq     = U(5);
    Ia      = U(6);
    Ib      = U(7);
    Ic      = U(8);
    imr     = U(9);
    wr      = U(10);
    Thetae  = U(11);

    real_T integralId_old,integralIq_old;
    integralId_old  = X[0];
    integralIq_old  = X[1];
    

    //Transformasi Alfabeta
    Ialfa   = A*(Ia - 0.5*Ib - 0.5*Ic);
    Ibeta   = A*(Q*Ib - Q*Ic);

    //Transformasi DQ
    Id      = Ialfa*cos(Thetae) + Ibeta*sin(Thetae);
    Iq      = -Ialfa*sin(Thetae) + Ibeta*cos(Thetae);

    //Current Control Signal
    real_T errorId = Id_ref - Id;
    real_T errorIq = Iq_ref - Iq;

    real_T integralId = integralId_old + errorId*dt;
    real_T integralIq = integralIq_old + errorIq*dt;
    
    real_T uds = Kpd*errorId + Kid*integralId;
    real_T uqs = Kiq*errorIq + Kid*integralIq;

    //Flux Model
    real_T omegae = (Np*wr)+((Rr/Lr)*(Iq_ref/(imr+0.001))); //ditambah 0.001 agar tidak pembagian 0 pada awal simulasi

    // real_T omegae;
    // if(imr==0){
    //     omegae = (Np*wr)+((Rr/Lr)*(Iq_ref));
    // }
    // else{
    //     omegae = (Np*wr)+((Rr/Lr)*(Iq_ref/imr));
    // }
    
    real_T imr_dt = (Rr/Lr)*(Id-imr);
    real_T epsilon = (1-((Lm*Lm)/(Ls*Lr)));

    //Decoupling Circuit
    real_T vcd = ((-omegae)*Ls*epsilon*Iq) + (Ls*(1-epsilon)*imr_dt);
    real_T vcq = (omegae*Ls*epsilon*Id) + (Ls*(1-epsilon)*omegae*imr);

    //Voltage references
    vds_ref = uds + vcd;
    vqs_ref = uqs + vcq;

    //Transformasi Alfabeta
    Valfa   = vds_ref*cos(Thetae) - vqs_ref*sin(Thetae);
    Vbeta   = vds_ref*sin(Thetae) + vqs_ref*cos(Thetae);
    
    //Transformasi abc
    Va      = A*Valfa;
    Vb      = A*(-0.5*Valfa + Q*Vbeta);
    Vc      = A*(-0.5*Valfa - Q*Vbeta);
    
    X[0]    = integralId;
    X[1]    = integralIq;
    X[2]    = Va;
    X[3]    = Vb;
    X[4]    = Vc; 
    X[5]    = imr;
    

}

static void mdlTerminate(SimStruct *S) 
{ } /*Keep this function empty since no memory is allocated*/ 

#ifdef MATLAB_MEX_FILE 
/* Is this file being compiled as a MEX-file? */ 
#include "simulink.c" /*MEX-file interface mechanism*/ 
#else 
#include "cg_sfun.h" /*Code generation registration function*/ 
#endif 

