#include "timeseries.h"
#include "matrix.h"
#include <iostream>
#include <string>
#include <fstream>
#include <strstream>
#include <iomanip>


#include <iomanip>
#include <strstream>
#include <complex>
#include <string>
#include <functional>
#include <gsl/gsl_specfunc.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include "matrix.h"
#include "abrand.h"
#include "poly.h"
#include "timeseries.h"




#include "garch.h"

//#include "tsinterface.h"
// #include "svm.h"

using namespace std;
//using namespace mslib;

	// void callback(int m, void* g)
	//  	{ int n = 1; }
	 
int main() {

 	//void *cb_parms;
 	bool get_parameter_cov = 1;	
 	std::ostringstream msg;
 	std::ostringstream supplemental;
 	int n,m,o,p;
 	double N,M,O,P, mean, arma_mean, arma_sd;	
 	char const *fn = "EURUSD_test.csv";
 	char const *miss = "missing.dat";
  	Matrix data, missing, mletest;	
 	TimeSeries *timeseries;	
 	TimeSeries *resids;
 	TimeSeries *garch_resids;	
 	ARMAModel *armamodel;
 	GARCHModel *garchmodel;

  	//INITIALIZE STUFF

 	armamodel = new ARMAModel();
 	resids = new TimeSeries();
 	garch_resids = new TimeSeries();
 	timeseries = new TimeSeries();
 	garchmodel = new GARCHModel();
 	
 	//MATRIX STUFF
 	int pp = data.read_file(fn);
 	int kk = missing.read_file(miss);

 	//TIMESERIES STUFF

 	double sd;
 	double *test;
 	Vector acfs(1);

 	timeseries->data = data;
 	timeseries->missing = missing;
 	timeseries->n=198;
 
 	n = timeseries->GetN();
 	mean = timeseries->SampleMean();
 	test = timeseries->GetData();

 	
  	timeseries->ComputeSampleACF(&acfs, NULL, 0);
  	
  	sd = sqrt(acfs[0]); //standard deviation of the timeseries, first term
 						//of de autocorrelation function of a stationary ts
  						//is the variance.

	printf("\n");

 	printf("Mean: %f\n", mean);
 	printf("var: %f\n", acfs[0]);
 	printf("sd: %f\n", sd);
 	printf("first data: %f\n", *test);
 	printf("read_file: %i\n", pp);
 	printf("read_file missing: %i\n", kk);	
 	printf("numero de datos en matrix: %i\n",  n);

	printf("\n");

 
 	//ARMA STUFF

 	Vector phis;
	Vector thetas;

	//aquí comienza el for para loopear entre todos los modelos de arma(p,q) 
	// p>0 y p <=5 y q >=0 y q<=p

 	
	armamodel->SetOrder(5,5);  //aqui cambiar (1,0) por (p,q)
	armamodel->SetFracDiff(0);
	
	int ttt= armamodel->FitModel(timeseries,1,1000,NULL,NULL,msg,supplemental,get_parameter_cov);
	
	arma_sd = armamodel -> GetSigma();
	arma_mean = armamodel -> GetMean();
 	

	
	printf("\n");

 	printf("ARMA Mean: %f\n", arma_mean);
 	printf("ARMA sigma: %f\n", arma_sd);
 	
	printf("\n");

	armamodel->GetCoefficients(phis,thetas);
	printf("AR: %f\n", phis[0]);
	printf("MA: %f\n", thetas[0]);

	double lll = armamodel -> GetLogLikelihood();
	double aic = armamodel->GetAICC();

	TimeSeries *not_norm_resids;
	not_norm_resids = new TimeSeries();
	armamodel->ComputeStdResiduals(timeseries, resids);
	armamodel->ComputeResiduals(timeseries, not_norm_resids);


	double *test2 = resids->GetData();
	printf("first resids: %f\n", *test2);

	// resids_garch->SetOrder(1,1);
	// resids_garch->SetFracDiff(0);
	// int qqq = armamodel->FitModel(resids,1,1000,NULL,NULL,msg,supplemental,get_parameter_cov);
	// Vector phis1;
	// Vector thetas1;

	// resids_garch->GetCoefficients(phis1,thetas1);
	// printf("GARCH ALPHA: %f\n", phis1[0]);


	printf("loglikelihood: %f\n", lll);
	printf("aic: %f\n", aic);

printf("\n");

	//GARCH Stuff

	
	Vector phis_g;
	Vector thetas_g;
	double muu=0;
	garchmodel -> SetParameters(1,1,phis_g,thetas_g,muu);

	garchmodel -> FitModel(resids,1,1000,NULL,NULL,msg,supplemental,get_parameter_cov);

	int pg,qg;
	double mug, sd_g;
	Vector asg, bsg;

	garchmodel -> GetParameters(pg, qg, asg, bsg, mug);	
	garchmodel -> ComputeStdResiduals(not_norm_resids,garch_resids);

	Vector garch_resids_acfs(1);
	garch_resids -> ComputeSampleACF(&garch_resids_acfs, NULL, 0);

	sd_g = sqrt(garch_resids_acfs[0]);
	
	printf("p garch:%i\n", pg);
	printf("q garch:%i\n", qg);
	printf("mu garch:%f\n", mug);
	printf("garch ALPHA: %f\n", asg[0]);
	printf("garch BETA: %f\n", bsg[0]);


////// FORECAST STUFF ////////

	double *fret;
	double *fmse; 
	fret = new double();
	fmse = new double();
	armamodel -> Forecast(timeseries,1, fret, fmse);
	printf("\n");
	printf("fret: %f\n", *fret);
	printf("fmse: %f\n", *fmse);
	printf("\n");

	double *gfret;
	double *gfmse; 
	gfret = new double();
	gfmse = new double();


	garchmodel -> Forecast(timeseries,1, gfret, gfmse);
	printf("gfret: %f\n", *gfret);
	printf("gfmse: %f\n", *gfmse);
	printf("\n");


	double final_forecast;
	
	final_forecast = *fret + *gfret;
	printf("garch sd: %f\n", sd_g);
	printf("final_forecast: %f\n", final_forecast);





 	printf("final test final\n");
  
 	return 0;
 	}