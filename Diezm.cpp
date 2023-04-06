#include "mex.h"
#include <math.h>//fucnión utilizadas sin(x), ceil(x)

//función principal: Downsample.
void Diezm(double *x,double *y,mwSize s,mwSize D=4){	
	for(int i=0;i<s;i++)
		y[i]=x[i*D];
}

/*funciones secundarias: 
double sinc(x)	calculo de la función sinc.

void myConv(x,h,y,nx,np) Calculo de la convolución entre
la señal de entrada y el filtro pasa-bajo. By Parrado.

void low_pass(x,s,D) Función principal allí se lleva acabo
la implementación del filtro pasa-bajos dado una frecuencia
de corte pi/D
*/
double sinc(double x){
	if(x==0)
		return 1;
	return sin(x)/x;
}
void myConv(double *x, double *h,double *y, int nx,int p)
{

//Variables auxiliares
double xnk;

/* Recorre la señal de entrada*/
for (int n=0; n<nx; n++) {
//Acumulador en cero
y[n]=0.0;

//Para cada muestra de la respuesta al impulso
for(int k=0;k<p;k++){

//Valor de muestra considerando condiciones iniciales en cero

xnk=(n-k)<0?0.0:x[n-k];

//Multiplicación y acumulación
y[n] += h[k] * xnk;
}

}

}
void low_pass(double *x,mwSize s,const float D=4){

	//declaración de variables.	

	const float pi=3.14159265359;
	double hl_p[2001]={0};
	double y[s]={0}; //variable auxiliar.
	int n[2001];
	int Omc;

	Omc=pi/D;	//frecuencia de corte del filtro.

	for(int i=0;i<2001;i++)
		n[i]=i-1000;	//numero del filtro -1000<n<1000
	
	
	for(int i=0;i<2001;i++)
		hl_p[i]=((Omc/pi)*(sinc((Omc/pi)*n[i])));	//calculo del filtro pasa bajos.

	//implementación del filtro pasa bajos.
	myConv(x,hl_p,y,(int)s,2001);

	x=y;

}
void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]){

	//declaración de los punteros	

	double *x,*y;

	//variables de medida para calculos de tamaños de vectores
	float s=0,D=0;

	if( nlhs != 1){
		mexErrMsgIdAndTxt("MyToolbox:Diezm:nlhs","One output required.");
	}

	if( nrhs != 2 && nrhs !=1 ){
		mexErrMsgIdAndTxt("MyToolbox:Diezm:nrhs","Two or one inputs required.");
	}

	/*
	Dado que la función basica es de un Diezmador de 4 se establece por defecto.
	Si se llegase a usar un valor de Diezmado diferente se establecen parametros diferentes.
	*/
	if(nrhs==1){
		x=mxGetPr(prhs[0]);
		s=mxGetN(prhs[0]);
		low_pass(x,(mwSize)s);	//implementación del filtro pasa-bajos.
		D=ceil(s/4);		// valor por defecto 4
		plhs[0]=mxCreateDoubleMatrix(1,(mwSize)D,mxREAL);
		y=mxGetPr(plhs[0]);
		Diezm(x,y,(mwSize)D);	//función del diezmado.
	}

	else{
		x=mxGetPr(prhs[0]);
		s=mxGetN(prhs[0]);
		D=mxGetScalar(prhs[1]);
		low_pass(x,(mwSize)s,D);
		s=ceil(s/D);		//valor dado por el usuario.
		plhs[0]=mxCreateDoubleMatrix(1,(mwSize)s,mxREAL);
		y=mxGetPr(plhs[0]);
		Diezm(x,y,(mwSize)s,(mwSize)D);
	}

}
