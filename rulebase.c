    if(xl==pl) {
		if (yl==z){rb_compare_low = pl;}

		if (yh==z){rb_compare_high = pl;}
	} 

	//Rule 8
	if(xl==pm){
		if (yl==z){rb_compare_low = pm;} 
	
		if (yh==z){rb_compare_high = pm;} 
	} 

	//Rule 7
	if(xl==ps){
		if (yl==z){rb_compare_low = ps;} 

		if (yh==z){rb_compare_high = ps;} 
	} 

	//Rule 6,5,4
	if(xl==z){
		if (yl==ps){rb_compare_low = ps;}
		if (yl==z){rb_compare_low = z;}
		if (yl==ns){rb_compare_low = ns;}

		if (yh==ps){rb_compare_high = ps;}
		if (yh==z){rb_compare_high = z;}
		if (yh==ns){rb_compare_high = ns;}
	} 

	//Rule 3
	if(xl==ns){
		if (yl==z){rb_compare_low = ns;} 

		if (yh==z){rb_compare_high = ns;} 
	} 

	//Rule 2
	if(xl==nm){
		if (yl==z){rb_compare_low = nm;} 
 
		if (yh==z){rb_compare_high = nm;} 
	} 

	//Rule 1
	if(xl==nl){
		if (yl==z){rb_compare_low = nl;} 

		if (yh==z){rb_compare_high = nl;} 
	}
	rb1 = rb_compare_low;
	rb2 = rb_compare_high;

	//Xh dengan Yl dan Yh
	//Rule 9
	if(xh==pl) {
		if (yl==z){rb_compare_low = pl;}

		if (yh==z){rb_compare_high = pl;}
	} 

	//Rule 8
	if(xh==pm){
		if (yl==z){rb_compare_low = pm;} 
	
		if (yh==z){rb_compare_high = pm;} 
	} 

	//Rule 7
	if(xh==ps){
		if (yl==z){rb_compare_low = ps;} 

		if (yh==z){rb_compare_high = ps;} 
	} 

	//Rule 6,5,4
	if(xh==z){
		if (yl==ps){rb_compare_low = ps;}
		if (yl==z){rb_compare_low = z;}
		if (yl==ns){rb_compare_low = ns;}

		if (yh==ps){rb_compare_high = ps;}
		if (yh==z){rb_compare_high = z;}
		if (yh==ns){rb_compare_high = ns;}
	} 

	//Rule 3
	if(xh==ns){
		if (yl==z){rb_compare_low = ns;} 

		if (yh==z){rb_compare_high = ns;} 
	} 

	//Rule 2
	if(xh==nm){
		if (yl==z){rb_compare_low = nm;} 
 
		if (yh==z){rb_compare_high = nm;} 
	} 

	//Rule 1
	if(xh==nl){
		if (yl==z){rb_compare_low = nl;} 

		if (yh==z){rb_compare_high = nl;} 
	}
	rb3 = rb_compare_low;
	rb4 = rb_compare_high;


	//SIMPAN 2//
	if(xl==pl) {
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==ps){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = pl;} 
		if (yl==ns){rb_compare_low = ps;} 
		if (yl==nl){rb_compare_low = z;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==ps){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = pl;} 
		if (yh==ns){rb_compare_high = ps;} 
		if (yh==nl){rb_compare_high = z;}
	} 

	if(xl==ps){
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==ps){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = pl;} 
		if (yl==ns){rb_compare_low = ps;}
		if (yl==nl){rb_compare_low = z;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==ps){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = pl;} 
		if (yh==ns){rb_compare_high = ps;}
		if (yh==nl){rb_compare_high = z;}
	} 

	if(xl==z){
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==ps){rb_compare_low = ps;}
		if (yl==z){rb_compare_low = z;}
		if (yl==ns){rb_compare_low = ns;}
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==ps){rb_compare_high = ps;}
		if (yh==z){rb_compare_high = z;}
		if (yh==ns){rb_compare_high = ns;}
		if (yh==nl){rb_compare_high = nl;}
	} 

	if(xl==ns){
		if (yl==pl){rb_compare_low = ps;}
		if (yl==ps){rb_compare_low = z;}
		if (yl==z){rb_compare_low = ns;} 
		if (yl==ns){rb_compare_low = ns;} 
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = ps;}
		if (yh==ps){rb_compare_high = z;}
		if (yh==z){rb_compare_high = ns;} 
		if (yh==ns){rb_compare_high = ns;} 
		if (yh==nl){rb_compare_high = nl;}
	} 
	if(xl==nl){
		if (yl==pl){rb_compare_low = z;} 
		if (yl==ps){rb_compare_low = ns;} 
		if (yl==z){rb_compare_low = nl;} 
		if (yl==ns){rb_compare_low = nl;} 
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = z;} 
		if (yh==ps){rb_compare_high = ns;} 
		if (yh==z){rb_compare_high = nl;} 
		if (yh==ns){rb_compare_high = nl;} 
		if (yh==nl){rb_compare_high = nl;}
	}

	rb1 = rb_compare_low;
	rb2 = rb_compare_high;

	//Xh dengan Yl dan Yh
	if(xh==pl) {
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==ps){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = pl;} 
		if (yl==ns){rb_compare_low = ps;} 
		if (yl==nl){rb_compare_low = z;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==ps){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = pl;} 
		if (yh==ns){rb_compare_high = ps;} 
		if (yh==nl){rb_compare_high = z;}
	} 

	if(xh==ps){
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==ps){rb_compare_low = pl;} 
		if (yl==z){rb_compare_low = pl;} 
		if (yl==ns){rb_compare_low = ps;}
		if (yl==nl){rb_compare_low = z;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==ps){rb_compare_high = pl;} 
		if (yh==z){rb_compare_high = pl;} 
		if (yh==ns){rb_compare_high = ps;}
		if (yh==nl){rb_compare_high = z;}
	} 

	if(xh==z){
		if (yl==pl){rb_compare_low = pl;} 
		if (yl==ps){rb_compare_low = ps;}
		if (yl==z){rb_compare_low = z;}
		if (yl==ns){rb_compare_low = ns;}
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = pl;} 
		if (yh==ps){rb_compare_high = ps;}
		if (yh==z){rb_compare_high = z;}
		if (yh==ns){rb_compare_high = ns;}
		if (yh==nl){rb_compare_high = nl;}
	} 

	if(xh==ns){
		if (yl==pl){rb_compare_low = ps;}
		if (yl==ps){rb_compare_low = z;}
		if (yl==z){rb_compare_low = ns;} 
		if (yl==ns){rb_compare_low = ns;} 
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = ps;}
		if (yh==ps){rb_compare_high = z;}
		if (yh==z){rb_compare_high = ns;} 
		if (yh==ns){rb_compare_high = ns;} 
		if (yh==nl){rb_compare_high = nl;}
	} 

	if(xh==nl){
		if (yl==pl){rb_compare_low = z;} 
		if (yl==ps){rb_compare_low = ns;} 
		if (yl==z){rb_compare_low = nl;} 
		if (yl==ns){rb_compare_low = nl;} 
		if (yl==nl){rb_compare_low = nl;}

		if (yh==pl){rb_compare_high = z;} 
		if (yh==ps){rb_compare_high = ns;} 
		if (yh==z){rb_compare_high = nl;} 
		if (yh==ns){rb_compare_high = nl;} 
		if (yh==nl){rb_compare_high = nl;}
	}