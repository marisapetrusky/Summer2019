#include <iostream>
#include <TTree.h>
using namespace std;

// User Variables
int runno = 20452;
bool arm = 1; // 0 for Left, 1 for Right
double z[3] = {0.0,0.6858,0.889};
double F = ((z[1] - z[0])/z[2] - z[0]);
// Branch Variables
double x1_coordt, x2_coordt, x3_coordt, y1_coordt, y2_coordt, y3_coordt;
double x1_fit, y1_fit; // x1 and y1 positions fitted with offsets
// Control Variables
int iflag; 

TString s_infile = Form("/chafs1/work1/marisa/RHRS/prexRHRS_%d_verf.root",runno);
TFile * f_infile = TFile::Open(s_infile,"READ");
TTree * Tin = (TTree*)f_infile->Get("T");
long entries = Tin->GetEntries();
//Tin->GetEntry(0);

double f_x1(double x2, double x3, double x2off, double x3off)
{
	// Calculate x1 position
	double x1;
	x1 = 1/(1-F) * (x2 - F*x3 + x2off - F*x3off);
	return x1; 
} 

double f_y1(double y2, double y3, double y2off, double y3off)
{
	// Calculate y1 position
	double y1; 
	y1 = 1/(1-F) * (y2 - F*y3 + y2off - F*y3off);
	return y1;
}

void fcn(int& npar, double* gin, double& result, double *par, int iflag)
{
	double chi2 = 0.0, chi2x = 0.0, chi2y = 0.0;

	for (int ievt = 0; ievt < entries; ievt++)
	{
		Tin->GetEntry(ievt);
		x1_fit = f_x1(x2_coordt,x3_coordt,par[0],par[1]);
		y1_fit = f_y1(y2_coordt,y3_coordt,par[2],par[3]);

		chi2x = 1e7*pow(x1_fit - x1_coordt,2); // Scale Chi2 because residual is too small
		chi2y = 1e7*pow(y1_fit - y1_coordt,2);
		chi2 += (chi2x + chi2y)/2;
	}	

	result = chi2/entries; 
}

void OffsetCalc()
{
	Tin->GetEntry(0);
	Tin->SetBranchAddress("x1_coordt",&x1_coordt);
	Tin->SetBranchAddress("x2_coordt",&x2_coordt);
	Tin->SetBranchAddress("x3_coordt",&x3_coordt);
	Tin->SetBranchAddress("y1_coordt",&y1_coordt);	
	Tin->SetBranchAddress("y2_coordt",&y2_coordt);
	Tin->SetBranchAddress("y3_coordt",&y3_coordt);

	TMinuit * gMinuit = new TMinuit(4);
	gMinuit->SetFCN(fcn);

	double arglist[10];
	arglist[0] = 1;
	gMinuit->mnexcm("SET ERR",arglist,1,iflag);

	Double_t minTrans = 0.0;
	Double_t maxTrans = 1e-2;
	Double_t stepTrans = 1e-7;

	gMinuit->DefineParameter(0,"x2off",0.0,stepTrans,minTrans,maxTrans);
	gMinuit->DefineParameter(1,"x3off",0.0,stepTrans,minTrans,maxTrans);
	gMinuit->DefineParameter(2,"y2off",0.0,stepTrans,minTrans,maxTrans);
	gMinuit->DefineParameter(3,"y3off",0.0,stepTrans,minTrans,maxTrans);

	gMinuit->mnexcm("CALL FCN",arglist,1,iflag);
	arglist[0] = 100000; // Max number of calls
	gMinuit->mnexcm("MIGRAD",arglist,1,iflag);

	double dummy; 
	double x2_offset, x3_offset, y2_offset, y3_offset;

	gMinuit->GetParameter(0,x2_offset,dummy);
	gMinuit->GetParameter(1,x3_offset,dummy);
	gMinuit->GetParameter(2,y2_offset,dummy);
	gMinuit->GetParameter(3,y3_offset,dummy);

	cout << "X offset in GEM 2: " << x2_offset << endl;
	cout << "Y offset in GEM 2: " << y2_offset << endl;
	cout << "X offset in GEM 3: " << x3_offset << endl;
	cout << "Y offset in GEM 3: " << y3_offset << endl;	
}

