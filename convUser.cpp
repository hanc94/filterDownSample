#include "mex.h"
#include "matrix.h"


void convUser(double *hr,double *xr,double *yr,mwSize hn,mwSize xm)
{
	yr[0]=0;
	for(int i=0;i<xm;i++){
		for(int j=0;j<hn;j++)
			yr[i+j]+=xr[i]*hr[j];
	}
}
	
void convUser(double *hr,double *xr,double *xi,double *yr,double *yi, mwSize hn, mwSize xm)
{
	int i,j;
	yr[0]=0;
	yi[0]=0;
	for(i=0;i<xm;i++){
		for(j=0;j<hn;j++){
            		yr[i+j] +=  xr[i] * hr[j];
		        yi[i+j] +=  xi[i] * hr[j];
		}
	}
	
}

void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
	double *hr,*xr,*xi,*yr,*yi;
	size_t Hn,Xm,yn;

	if( nlhs != 1)
		mexErrMsgIdAndTxt("MyToolbox:convUser:nlhs","One output required.");
	if( nrhs != 2)
		mexErrMsgIdAndTxt("MyToolbox:convUser:nrhs","Two vectors input required.");

	Hn=mxGetN(prhs[1]);
	Xm=mxGetN(prhs[0]);
	yn=Hn+Xm-1;

	if( mxIsComplex(prhs[0])){ 
		
		xr=mxGetPr(prhs[0]);
		hr=mxGetPr(prhs[1]);
		xi=mxGetPi(prhs[0]);		
		plhs[0] = mxCreateDoubleMatrix(1,(mwSize)yn,mxCOMPLEX);
		yr=mxGetPr(plhs[0]);
		yi=mxGetPi(plhs[0]);
		convUser(hr,xr,xi,yr,yi,(mwSize)Hn,(mwSize)Xm);
	}	
	else{	
		hr=mxGetPr(prhs[0]);
		xr=mxGetPr(prhs[1]);
		plhs[0] = mxCreateDoubleMatrix((mwSize)1,(mwSize)yn,mxREAL);
		yr=mxGetPr(plhs[0]);
		convUser(hr,xr,yr,(mwSize)Hn,(mwSize)Xm);
	
	}

	return;
}
