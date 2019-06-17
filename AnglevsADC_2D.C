void AnglevsADC_2D()
{	
	// Variables and Branches 
	// Angles in Radians 
	
	double ph, th;
	double hadc0, hadc1;
	double ladc0, ladc1;
	double phmax = 0.3, phmin = -0.30;
	double thmax = 0.15, thmin = -0.15;
	double hadc0max = 250, hadc0min = 120;
	double ladc0max = 1800, ladc0min = 1000;
	double hadc1max = 180, hadc1min = 120;
	double ladc1max = 1300, ladc1min = 1000;
	long noevt[3] = {2798,1712,425}; // M: Must manually set number of events, check ph hist. 
	int nofiles = 2; // M: Number of files minus 1 for 0
	double pedestal[4] = {1194,151.7,1084,137.2};
	
	// Histograms
	
	//gStyle->SetOptStat("Men");
	
	// 2D Histograms
	TH2D * h_ladc0_ph = new TH2D("ladc0.ph","Low ADC0 Charge vs #phi",50,phmin,phmax,100,ladc0min,ladc0max);
	h_ladc0_ph->SetOption("COLZ");
	TH2D * h_hadc0_ph = new TH2D("hadc0.ph","High ADC0 Charge vs #phi",50,phmin,phmax,50,hadc0min,hadc0max);
	h_hadc0_ph->SetOption("COLZ");
	TH2D * h_ladc1_ph = new TH2D("ladc1.ph","Low ADC1 Charge vs #phi",50,phmin,phmax,100,ladc1min,ladc1max);
	h_ladc1_ph->SetOption("COLZ");
	TH2D * h_hadc1_ph = new TH2D("hadc1.ph","High ADC1 Charge vs #phi",50,phmin,phmax,50,hadc1min,hadc1max);
	h_hadc1_ph->SetOption("COLZ");
	TH2D * h_ladc0_th = new TH2D("ladc0.th","Low ADC0 Charge vs #theta",50,thmin,thmax,100,ladc0min,ladc0max);
	h_ladc0_th->SetOption("COLZ");
	TH2D * h_hadc0_th = new TH2D("hadc0.th","High ADC0 Charge vs #theta",50,thmin,thmax,50,hadc0min,hadc0max);
	h_hadc0_th->SetOption("COLZ");
	TH2D * h_ladc1_th = new TH2D("ladc1.th","Low ADC1 Charge vs #theta",50,thmin,thmax,100,ladc1min,ladc1max);
	h_ladc1_th->SetOption("COLZ");
	TH2D * h_hadc1_th = new TH2D("hadc1.th","High ADC1 Charge vs #theta",50,thmin,thmax,50,hadc1min,hadc1max);
	h_hadc1_th->SetOption("COLZ");
	
	// 1D Histograms
	TH1D * h_ph = new TH1D("h_ph","#phi Distribution",25,phmin,phmax);
	TH1D * h_th = new TH1D("h_th","#theta Distribution",25,thmin,thmax);
	TH1D * h_ladc0 = new TH1D("h_ladc0","Low ADC0 Charge Distribution",25,ladc0min,ladc0max);
	TH1D * h_hadc0 = new TH1D("h_hadc0","High ADC0 Charge Distribution",25,hadc0min,hadc0max);
	TH1D * h_ladc1 = new TH1D("h_ladc1","Low ADC1 Charge Distribution",25,ladc1min,ladc1max);
	TH1D * h_hadc1 = new TH1D("h_hadc1","High ADC1 Charge Distribution",25,hadc1min,hadc1max);
	
	for (int ifile = 0; ifile < nofiles; ifile++)
	{
		TString filename = Form("mergedtests_%d.root",ifile);
		TFile * p_infile = TFile::Open(filename,"READ");
		TTree * t_T = (TTree*)p_infile->Get("T");

		t_T->SetBranchAddress("prex.tr.ph",&ph);
		t_T->SetBranchAddress("prex.tr.th",&th);
		t_T->SetBranchAddress("prex.sbuscint.hadc0",&hadc0);
		t_T->SetBranchAddress("prex.sbuscint.hadc1",&hadc1);
		t_T->SetBranchAddress("prex.sbuscint.ladc0",&ladc0);
		t_T->SetBranchAddress("prex.sbuscint.ladc1",&ladc1);
	
		//cout << "Number of Events is " << noevt << endl;
	
		// Fill Histograms
	
		for (int ievt = 0; ievt < noevt[ifile]; ievt++)
		{
			t_T->GetEntry(ievt);
			
			h_ladc0->Fill(ladc0);
			h_hadc0->Fill(hadc0);
			h_ladc1->Fill(ladc1);
			h_hadc1->Fill(hadc1);

			if (ladc0 > pedestal[0] && hadc0 > pedestal[1] && ladc1 > pedestal[2] && hadc1 > pedestal[3])
			{
				// 1D Histogram Fill
				h_ph->Fill(ph);
				h_th->Fill(th);
					
				// 2D Histogram Fill
				h_ladc0_ph->Fill(ph,ladc0);
				h_ladc1_ph->Fill(ph,ladc1);
				h_hadc0_ph->Fill(ph,hadc0);
				h_hadc1_ph->Fill(ph,hadc1);
		
				h_ladc0_th->Fill(th,ladc0);
				h_ladc1_th->Fill(th,ladc1);
				h_hadc0_th->Fill(th,hadc0);		
				h_hadc1_th->Fill(th,hadc1);		
			}
		}
		
		p_infile->Close();
		
	}
		
	/*TCanvas * c_th = new TCanvas("c_th","c_th",900,900);
	c_th->Divide(2,2);
	c_th->cd(1);
	h_ladc0_th->Draw();
	c_th->cd(2);
	h_ladc1_th->Draw();
	c_th->cd(3);
	h_hadc0_th->Draw();
	c_th->cd(4);
	h_hadc1_th->Draw();*/

	/*TCanvas * c_ph = new TCanvas("c_ph","c_ph",900,900);
	c_ph->Divide(2,2);
	c_ph->cd(1);
	h_ladc0_ph->Draw();
	c_ph->cd(2);
	h_ladc1_ph->Draw();
	c_ph->cd(3);
	h_hadc0_ph->Draw();
	c_ph->cd(4);
	h_hadc1_ph->Draw();*/
	
	TCanvas * c_ang = new TCanvas("c_ang","c_ang",1200,600);
	c_ang->Divide(2,1);
	c_ang->cd(1);
	h_ph->Draw();
	c_ang->cd(2);
	h_th->Draw();
	
	TCanvas * c_ch = new TCanvas("c_ch","c_ch",900,900);
	c_ch->Divide(2,2);
	c_ch->cd(1);
	h_ladc0->Draw();
	c_ch->cd(2);
	h_hadc0->Draw();
	c_ch->cd(3);
	h_ladc1->Draw();
	c_ch->cd(4);
	h_hadc1->Draw();
	
}
