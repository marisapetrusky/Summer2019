Double_t langaufun(Double_t * x, Double_t * par);
void GetRangeX(TH1 * h, double overflow, double& xmin, double& xmax);
int FindBestBins(TH1 * h, int maxcalls);

//#include "hist_optimize.h"
//using namespace Optimize; 

void ADC_langaufit()
{
	// User Variables
	int runs[9] = {427,430,432,438,439,440,441,442,444};
	int noruns = 9;
	double overflow_l = 100; // Increases range of histogram
	double overflow_h = 20;
	bool PedCap = 1; // Set TRUE to eliminate events less than pedestal
	bool LogY = 1; // Set TRUE to have log axis in the Y
	bool DoFit = 1; // Set TRUE to perform Landau-Gauss fit
	double ped_l[2] = {1166,1067}; // Pedestal in each PMT
	double ped_h[2] = {148,135};
	double width_l = 25, width_h = 2;
	// Branch Variables 
	double hadc0, ladc0, hadc1, ladc1;
	long entries; 
	// Control Variables
	double xmin_ladc0 = ped_l[0] - overflow_l, xmin_ladc1 = ped_l[1] - overflow_l;
	double xmin_hadc0 = ped_h[0] - overflow_h, xmin_hadc1 = ped_h[1] - overflow_h;
	double xmax_ladc0 = 2000, xmax_ladc1 = 2000, xmax_hadc0 = 250, xmax_hadc1 = 250;
	int bins_ladc0 = (xmax_ladc0 - xmin_ladc0)/width_l, bins_ladc1 = (xmax_ladc1 - xmin_ladc1)/width_l, bins_hadc0 = (xmax_hadc0 - xmin_hadc0)/width_h, bins_hadc1 = (xmax_hadc1 - xmin_hadc1)/width_h;
	//int maxbins_ladc0 = 200, maxbins_ladc1 = 200, maxbins_hadc0 = 100, maxbins_hadc1 = 100;
	
	// Histograms
	TH1D * h_ladc0 = new TH1D("ladc0","Quartz 1, Low Resolution",bins_ladc0,xmin_ladc0,xmax_ladc0);
	TH1D * h_ladc1 = new TH1D("ladc1","Quartz 2, Low Resolution",bins_ladc1,xmin_ladc1,xmax_ladc1);
	TH1D * h_hadc0 = new TH1D("hadc0","Quartz 1, High Resolution",bins_hadc0,xmin_hadc0,xmax_hadc0);//22,0.,0.);
	TH1D * h_hadc1 = new TH1D("hadc1","Quartz 2, High Resolution",bins_hadc1,xmin_hadc1,xmax_hadc1);//21,0.,0.);
	
	for (int irun = 0; irun < noruns; irun++)
	{

		TString filename = Form("/home/marisa/rootfiles/test_%d_verf.root",runs[irun]);
		TFile * p_infile = TFile::Open(filename,"READ");
		TTree * Tin = (TTree*)p_infile->Get("T");
		entries = Tin->GetEntries();
		Tin->SetBranchAddress("h_adc0",&hadc0);
		Tin->SetBranchAddress("h_adc1",&hadc1);
		Tin->SetBranchAddress("l_adc0",&ladc0);
		Tin->SetBranchAddress("l_adc1",&ladc1);

		for (int ievt = 0; ievt < entries; ievt++)
		{
			Tin->GetEntry(ievt);
			if (PedCap && ladc0 > ped_l[0] && ladc1 > ped_l[1])
			{
				h_ladc0->Fill(ladc0);
				h_ladc1->Fill(ladc1);	
			}
			else if (!PedCap)
			{
				h_ladc0->Fill(ladc0);
				h_ladc1->Fill(ladc1);
			}
			if (PedCap && hadc0 > ped_h[0] && hadc1 > ped_h[1])
			{
				h_hadc0->Fill(hadc0);
				h_hadc1->Fill(hadc1);
			}
			else if (!PedCap)
			{
				h_hadc0->Fill(hadc0);
				h_hadc1->Fill(hadc1);
			}
		}	
	}

	//h_ladc0->GetXaxis()->SetRangeUser(xmin_ladc0,xmax_ladc0);

	TCanvas * c1 = new TCanvas("Q1","Q1",1000,800);
	c1->Divide(2,1);
	c1->cd(1);
	if (LogY) {gPad->SetLogy();}
	h_ladc0->Draw();
	c1->cd(2);
	if (LogY) {gPad->SetLogy();}
	h_hadc0->Draw();

	TCanvas * c2 = new TCanvas("Q2","Q2",1000,800);
	c2->Divide(2,1);	
	c2->cd(1);
	if (LogY) {gPad->SetLogy();}
	h_ladc1->Draw();
	c2->cd(2);
	if (LogY) {gPad->SetLogy();}
	h_hadc1->Draw();

	if (DoFit)
	{	
		// Create a Landau-Gauss distribution for each one
		double mean, area, sigma, fr[2];
		double lgmin_l0, lgmin_l1, lgmin_h0, lgmin_h1;
		double lgmax_l0, lgmax_l1, lgmax_h0, lgmax_h1;
		gStyle->SetOptStat(1111);
		gStyle->SetOptFit(111);

		GetRangeX(h_ladc0,0,lgmin_l0,lgmax_l0);
		GetRangeX(h_ladc1,70,lgmin_l1,lgmax_l1);
		GetRangeX(h_hadc0,0,lgmin_h0,lgmax_h0);
		GetRangeX(h_hadc1,5,lgmin_h1,lgmax_h1);

		TF1 * lg_ladc0 = new TF1("lg_ladc0",langaufun,lgmin_l0,lgmax_l0,4); // Set range according to each histogram
		lg_ladc0->SetParNames("lwidth","mpv","integral","gsigma");
		mean = h_ladc0->GetMean();
		area = h_ladc0->Integral(lgmin_l0,lgmax_l0);
		sigma = h_ladc0->GetRMS();
		fr[0] = 0.5*mean;
		fr[1] = 2*mean;
		lg_ladc0->SetParameters(2.,mean,area,6);
		h_ladc0->Fit("lg_ladc0","R0","",fr[0],fr[1]);
		c1->cd(1);
		lg_ladc0->Draw("SAME");

		TF1 * lg_ladc1 = new TF1("lg_ladc1",langaufun,lgmin_l1,lgmax_l1,4);
		lg_ladc1->SetParNames("lwidth","mpv","integral","gsigma");
		mean = h_ladc1->GetMean();
		area = h_ladc1->Integral(lgmin_l1,lgmax_l1);
		sigma = h_ladc1->GetRMS();
		fr[0] = 0.5*mean;
		fr[1] = 2*mean;
		lg_ladc1->SetParameters(2.,mean,area,6);
		h_ladc1->Fit("lg_ladc1","R0","",fr[0],fr[1]);
		c2->cd(1);
		lg_ladc1->Draw("SAME");

		TF1 * lg_hadc0 = new TF1("lg_hadc0",langaufun,lgmin_h0,lgmax_h1,4); // Set range according to each histogram
		lg_hadc0->SetParNames("lwidth","mpv","integral","gsigma");
		mean = h_hadc0->GetMean();
		area = h_hadc0->Integral(lgmin_h0,lgmax_h0);
		sigma = h_hadc0->GetRMS();
		fr[0] = 0.5*mean;
		fr[1] = 2*mean;
		lg_hadc0->SetParameters(2.,mean,area,6);
		h_hadc0->Fit("lg_hadc0","R0","",fr[0],fr[1]);
		c1->cd(2);
		lg_hadc0->Draw("SAME");

		TF1 * lg_hadc1 = new TF1("lg_hadc1",langaufun,lgmin_h1,lgmax_h1,4);
		lg_hadc1->SetParNames("lwidth","mpv","integral","gsigma");
		mean = h_hadc1->GetMean();
		area = h_hadc1->Integral(lgmin_h1,lgmax_h1);
		sigma = h_hadc1->GetRMS();
		fr[0] = 0.5*mean;
		fr[1] = 2*mean;
		lg_hadc1->SetParameters(2.,mean,area,6);
		h_hadc1->Fit("lg_hadc1","R0","",fr[0],fr[1]);
		c2->cd(2);
		lg_hadc1->Draw("SAME"); 
	}
}

void GetRangeX(TH1 * h, double overflow, double& xmin, double& xmax)
{
	xmin = h->GetBinCenter(h->FindFirstBinAbove(0,1) - overflow);
	xmax = h->GetBinCenter(h->FindLastBinAbove(0,1) + overflow);
	//cout << "Xmax = " << xmax << endl;
}

Double_t langaufun(Double_t * x, Double_t * par)
{
	// Chandan's Landau-Gaussian Fit
	// Numeric Constants
	double invsq2pi = 0.3989422804014; // (2pi)^(-0.5)
	double mpshift = -0.22278298; // Landau max location
	// Control Constants
	double np = 100.0;
	double sc = 5.0;
	// Variables
	double xx, mpc, fland, sum = 0.0, xlow, xup, step, i;

	// MP Shift Correction
	mpc = par[1] - mpshift * par[0];

	// Range of convolution integral 
	xlow = x[0] - sc * par[3];
	xup = x[0] + sc * par[3];

	step = (xup - xlow)/np;

	// Convolution Integral of Landau and Gaussian by Sum

	for (i = 1.0; i <= np/2; i++)
	{
		xx = xlow + (i-0.5)*step;
		fland = TMath::Landau(xx,mpc,par[0])/par[0];
		sum += fland * TMath::Gaus(x[0],xx,par[3]);

		xx = xup - (i-0.5)*step;
		fland = TMath::Landau(xx,mpc,par[0])/par[0];
		sum += fland*TMath::Gaus(x[0],xx,par[3]);
	}	

	return (par[2]*step*sum*invsq2pi/par[3]);
	return 0;
}
