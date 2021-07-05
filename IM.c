#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME IM
#include "simstruc.h"
#include <math.h>

#define U(element) (*uPtrs[element]) /*Pointer to Input Port0*/

static void mdlInitializeSizes(SimStruct *S){
    ssSetNumContStates(S, 6);
    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 4); 
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortOverWritable(S, 0, 1);
    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 8); 
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S) {
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    }

#define MDL_INITIALIZE_CONDITIONS
static void mdlInitializeConditions(SimStruct *S) {
    real_T *X0 = ssGetContStates(S);
    int_T nStates = ssGetNumContStates(S);
    int_T i;
    /* initialize the states to 0.0 */
    for (i=0; i < nStates; i++) {X0[i] = 0.0;}
}

static void mdlOutputs(SimStruct *S, int_T tid) {
    real_T *Y = ssGetOutputPortRealSignal(S,0);
    real_T *X = ssGetContStates(S);
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);

    real_T K = 0.816497, L = 0.866025;
    real_T Lm = 0.2279, Lr = 0.2349;
    real_T Np = 2.0, pi2 = 6.28318530718;
    real_T fx, fy;

    Y[0] = K*X[0];
    Y[1] = K*( -0.5*X[0] + L*X[1] );
    Y[2] = K*( -0.5*X[0] - L*X[1] );
    fx = (Lr*X[2] + Lm*X[0]);
    fy = (Lr*X[3] + Lm*X[1]);
    Y[3] = (sqrt(fx*fx + fy*fy))/Lm;
    Y[4] = Np*Lm*( X[1]*X[2] - X[0]*X[3] );
    if(fy == 0.0){fy = 1e-6;}
    if(fx < 0.0 && fy < 0.0){Y[5]= pi2 + atan2(fy,fx);}
    if(fx < 0.0 && fy > 0.0){Y[5]= atan2(fy,fx);}
    if(fx >= 0.0 && fy < 0.0){Y[5]= pi2 + atan2(fy,fx);}
    if(fx >= 0.0 && fy > 0.0){Y[5]= atan2(fy,fx);}
    while(X[5] > pi2){ X[5] -= pi2;}
    while(X[5] < 0.0) { X[5] += pi2;}
    Y[6] = X[5];
    Y[7] = X[4];
}

#define MDL_DERIVATIVES
static void mdlDerivatives(SimStruct *S) {
    real_T *dX = ssGetdX(S);
    real_T *X = ssGetContStates(S);
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);

    real_T Lm=0.2279, Ls=0.2349, Lr=0.2349;
    real_T Rs=2.76, Rr=2.9;
    real_T a0=1/( Lm*Lm-Ls*Lr);
    real_T K=0.816497, L=0.866025;
    real_T B =0.0005, J=0.0436, Np=2.0;

    real_T idsn_dot, iqsn_dot, idrn_dot, iqrn_dot;
    real_T wr_dot, theta_r_dot, vds, vqs, Te;

    vds = K*( U(0) - 0.5*U(1) - 0.5*U(2) );
    vqs = K*L*( U(1) - U(2) );

    idsn_dot = (Rs*Ls*X[0]-Np*X[4]*Lm*Lm*X[1]-Rr*Lm*X[2]-Np*X[4]*Lr*Lm*X[3]-Lr*vds)*a0;
    iqsn_dot = (Np*X[4]*Lm*Lm*X[0]+Rs*Lr*X[1] +Np*X[4]*Lr*Lm*X[2]-Rr*Lm*X[3]-Lr*vqs)*a0;
    idrn_dot = -(Rs*Lm*X[0]-Np*X[4]*Lm*Ls*X[1] -Rr*Ls*X[2]-Np*X[4]*Lr*Ls*X[3]-Lm*vds)*a0;
    iqrn_dot = -(Np*X[4]*Lm*Ls*X[0]+Rs*Lm*X[1] +Np*X[4]*Lr*Ls*X[2]-Rr*Ls*X[3]-Lm*vqs)*a0;

    Te = Np * Lm*(X[1] * X[2] - X[0] * X[3]);
    wr_dot = ( Te - U(3) - B * X[4] ) / J;
    theta_r_dot = X[4];

    dX[0] = idsn_dot;
    dX[1] = iqsn_dot;
    dX[2] = idrn_dot;
    dX[3] = iqrn_dot;
    dX[4] = wr_dot;
    dX[5] = theta_r_dot;
}

static void mdlTerminate(SimStruct *S)
{} /*Keep this function empty since no memory is allocated*/

#ifdef MATLAB_MEX_FILE
/* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else 105
#include "cg_sfun.h" /*Code generation registration function*/
#endif
