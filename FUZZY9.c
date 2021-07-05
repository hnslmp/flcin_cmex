#define S_FUNCTION_LEVEL 2 
#define S_FUNCTION_NAME FUZZY9
#include "simstruc.h" 
#include <math.h> 

#define U(element) (*uPtrs[element]) /*Pointer to Input Port0*/ 

static void mdlInitializeSizes(SimStruct *S)
{ 
	ssSetNumDiscStates(S, 3);
	if (!ssSetNumInputPorts(S, 1)) return; 
	ssSetInputPortWidth(S, 0, 2); 
	ssSetInputPortDirectFeedThrough(S, 0, 1); 
	ssSetInputPortOverWritable(S, 0, 1); 
	
	if (!ssSetNumOutputPorts(S, 1)) return; 
	ssSetOutputPortWidth(S, 0, 3); 
	ssSetNumSampleTimes(S, 1); 

	ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_DISCRETE_VALUED_OUTPUT));
} 

static void mdlInitializeSampleTimes(SimStruct *S)
{ 
	ssSetSampleTime(S, 0, 1e-4); 
	ssSetOffsetTime(S, 0, 0.0);
} 

#define MDL_INITIALIZE_CONDIT	IONS 
static void mdlInitializeConditions(SimStruct *S)
{ 
	real_T *X0 = ssGetRealDiscStates(S); 
	int_T nXStates = ssGetNumDiscStates(S); 
	InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0); 
	int_T i; 

	/* initialize the states to 0.0 */ 
	for (i=0; i < nXStates; i++) 
	{ 
		X0[i] = 0.0; 
	} 
} 

static void mdlOutputs(SimStruct *S, int_T tid)
{ 
	real_T *Y = ssGetOutputPortRealSignal(S,0);
    real_T *X = ssGetRealDiscStates(S);
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
	
	//DECLARE VARIABEL
    real_T iq_ref, e, ec;

	//AMBIL DARI MEMORI
    iq_ref = X[0]; 
    e = X[1]; 
    ec = X[2];

	//OUTPUT 
    Y[0] = iq_ref; 
    Y[1] = e; 
    Y[2] = ec;
} 

#define MDL_UPDATE 
static void mdlUpdate(SimStruct *S, int_T tid) 
{ 
	real_T *X = ssGetRealDiscStates(S);
	InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);

	real_T dt = 1e-3;

	//DECLARE VARIABEL
	real_T e, ec, e_prev, w_ref, w_act;
	real_T nl, nm, ns, z, ps, pm, pl;
	real_T x, xl, xh, y, yl, yh, se, a, b, c ,d;
	real_T dom_xh, dom_xl, dom_yh, dom_yl;
	real_T rb1,rb2,rb3,rb4;
	real_T rb_compare_low,rb_compare_high;  
	real_T mag_infer_1,mag_infer_2,mag_infer_3,mag_infer_4;
	real_T iq_ref;
    real_T gmf = 4.1;
	
	//INPUT
	e_prev = X[1];
	w_ref = U(0);
	w_act = U(1);

	//HITUNG ERROR DAN CHANGE OF ERROR
	e	= (w_ref - w_act);
	ec 	= (e - e_prev);

	//MEMBERSHIP FUNCTION
	pl 	= 0.5*gmf;
	z 	= 0.0*gmf;
	nl 	= -0.5*gmf;

	//SCALING CRISP INPUT GE & GCE
	x 	= e*1000; 
	y 	= ec;

	if(x < 0.0){se = -1;}
	else {se = 1;}

	//DEGREE OF MEMBERSHIP E
	if(x <= nl){
		xl = z;
		xh = nl;
		a = 0;
		b = 1;
	}
	else if(nl < x && x < pl){
		if(z <= x < pl){
			xl = z; 
			xh = pl;
			b = (x-xl)*se;
			a = 1-b;
		}
		else if(nl < x < z){
			xl = z;
			xh = nl;
			b = (x-xl)*se;
			a = 1-b;
		}
	}
	else if(x >= pl){
		xl = z;
		xh = pl;
		a = 0;
		b = 1;
	}

	//DEGREE OF MEMBERSHIP EC
	if(y <= nl){
		yl = z;
		yh = nl;
		c = 0;
		d = 1;
	}
	else if(nl < y && y < pl){
		if(z <= y < pl){
			yl = z; 
			yh = pl;
			d = (y-yl)*se;
			c = 1-d;
		}
		else if(nl < y <z){
			yl = z;
			yh = nl;
			d = (y-yl)*se;
			c = 1-d;
		}
	}
	else if(y >= pl){
		yl = z;
		yh = pl;
		c = 0;
		d = 1;
	}

	dom_xh = a;
	dom_xl = b;
	dom_yh = c;
	dom_yl = d;

	//RULE BASE
	//Xl dengan Yl dan Yh
	if(xl==pl) {
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = pl;}  
		if (yl==nl){rb_compare_low = z;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = pl;} 
		if (yh==nl){rb_compare_high = z;}
	} 

	if(xl==ps){
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = pl;} 
		if (yl==nl){rb_compare_low = z;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = pl;} 
		if (yh==nl){rb_compare_high = z;}
	} 

	if(xl==z){
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = z;}
		if (yl==ns){rb_compare_low = ns;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = z;}
		if (yh==nl){rb_compare_high = nl;}
	} 

	if(xl==ns){
		if (yl==pl){rb_compare_low = ps;}
		if (yl==z){rb_compare_low = ns;} 
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = ps;}
		if (yh==z){rb_compare_high = ns;} 
		if (yh==nl){rb_compare_high = nl;}
	} 
	if(xl==nl){
		if (yl==pl){rb_compare_low = z;} 
		if (yl==z){rb_compare_low = nl;} 
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = z;} 
		if (yh==z){rb_compare_high = nl;} 
		if (yh==nl){rb_compare_high = nl;}
	}

	rb1 = rb_compare_low;
	rb2 = rb_compare_high;

	//Xh dengan Yl dan Yh
	if(xh==pl) {
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = pl;} 
		if (yl==nl){rb_compare_low = z;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = pl;} 
		if (yh==nl){rb_compare_high = z;}
	} 

	if(xh==ps){
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = pl;} 
		if (yl==nl){rb_compare_low = z;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = pl;} 
		if (yh==nl){rb_compare_high = z;}
	} 

	if(xh==z){
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = z;}
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = z;}
		if (yh==nl){rb_compare_high = nl;}
	} 

	if(xh==ns){
		if (yl==pl){rb_compare_low = ps;}
		if (yl==z){rb_compare_low = ns;} 
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = ps;}
		if (yh==z){rb_compare_high = ns;} 
		if (yh==nl){rb_compare_high = nl;}
	} 

	if(xh==nl){
		if (yl==pl){rb_compare_low = z;} 
		if (yl==z){rb_compare_low = nl;} 
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = z;} 
		if (yh==z){rb_compare_high = nl;} 
		if (yh==nl){rb_compare_high = nl;}
	}
	rb3 = rb_compare_low;
	rb4 = rb_compare_high;

	//INFERENCE ENGINE - MAX MIN ALGORITHM
	//Min layer
	if(dom_xh < dom_yh){
		mag_infer_1 = dom_xh;
	}
	else {
		mag_infer_1 = dom_yh;
	}

	if(dom_xh < dom_yl){
		mag_infer_2 = dom_xh;
	}
	else {
		mag_infer_2 = dom_yl;
	}

	if(dom_xl < dom_yh){
		mag_infer_3 = dom_xl;
	}
	else {
		mag_infer_3 = dom_yh;
	}

	if(dom_xl < dom_yl){
		mag_infer_4 = dom_xl;
	}
	else {
		mag_infer_4 = dom_yl;
	}

	//Perhitungan MAX
	//Max Layer
	if(rb1 == rb2){
		if(mag_infer_1 < mag_infer_2){
			mag_infer_1 = 0.0;
		}
		else{
			mag_infer_2 = 0.0;
		}
	}

	else if(rb1 == rb3){
		if(mag_infer_1 < mag_infer_3){
			mag_infer_1 = 0.0;}
		else{
			mag_infer_3 = 0.0;
		}
	}

	else if(rb1 == rb4){
		if(mag_infer_1 < mag_infer_4){
			mag_infer_1 = 0.0;
		}
		else{
		mag_infer_4 = 0.0;
		}
	}

	else if(rb2 == rb3){
		if(mag_infer_2 < mag_infer_3){
			mag_infer_2 = 0.0;
		}
		else{
			mag_infer_3 = 0.0;
		}
	}

	else if(rb2 == rb4){
		if(mag_infer_2 < mag_infer_4){
			mag_infer_2 = 0.0;
		}
		else{
			mag_infer_4 = 0.0;
		}
	}

	else if(rb3 == rb4){
		if(mag_infer_3 < mag_infer_4){
			mag_infer_3 = 0.0;
		}
		else{
			mag_infer_4 = 0.0;
		}
	}

	//DEFUZZYFICATION
	iq_ref = ((mag_infer_1*rb1)+(mag_infer_2*rb2)+(mag_infer_3*rb3)+(mag_infer_4*rb4))/(mag_infer_1+mag_infer_2+mag_infer_3+mag_infer_4);

	X[0] = iq_ref; 
	X[1] = e; 
	X[2] = ec; 
}

static void mdlTerminate(SimStruct *S) 
{ } /*Keep this function empty since no memory is allocated*/ 

#ifdef MATLAB_MEX_FILE 
/* Is this file being compiled as a MEX-file? */ 
#include "simulink.c" /*MEX-file interface mechanism*/ 
#else 
#include "cg_sfun.h" /*Code generation registration function*/ 
#endif 