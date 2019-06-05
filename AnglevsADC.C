void AnglevsADC()
{
	TFile * p_infile = TFile::Open("mergedtests.root","read");
	TTree * p_T = (TTree*)p_infile->Get("T");
	
	// Variables and Branches 
	
	double ph, th;
	double hadc0, hadc1;
	double ladc0, ladc1;
	long noevt;

	p_T->SetBranchAddress("prex.tr.ph",&ph);
	p_T->SetBranchAddress("prex.tr.th",&th);
	p_T->SetBranchAddress("prex.sbuscint.hadc0",&hadc0);
	p_T->SetBranchAddress("prex.sbuscint.hadc1",&hadc1);
	p_T->SetBranchAddress("prex.sbuscint.ladc0",&ladc0);
	p_T->SetBranchAddress("prex.sbuscint.ladc1",&ladc1);
	
	noevt = p_T->GetEntries();
	
	// Histograms
	
	gStyle->SetOptStat("Men");
	
	TProfile * h_ladc0_ph = new TProfile("ladc0.ph","Low ADC0 Charge vs #phi",2000,-0.5,3000);
	TProfile * h_hadc0_ph = new TProfile("hadc0.ph","High ADC0 Charge vs #phi",2000,-0.5,3000);
	TProfile * h_ladc1_ph = new TProfile("ladc1.ph","Low ADC1 Charge vs #phi",2000,-0.5,3000);
	TProfile * h_hadc1_ph = new TProfile("hadc1.ph","High ADC1 Charge vs #phi",2000,-0.5,3000);

	TProfile * h_ladc0_th = new TProfile("ladc0.th","Low ADC0 Charge vs #theta",2000,-0.5,3000);
	TProfile * h_hadc0_th = new TProfile("hadc0.th","High ADC0 Charge vs #theta",2000,-0.5,3000);
	TProfile * h_ladc1_th = new TProfile("ladc1.th","Low ADC1 Charge vs #theta",2000,-0.5,3000);
	TProfile * h_hadc1_th = new TProfile("hadc1.th","High ADC1 Charge vs #theta",2000,-0.5,3000);

	// Fill Histograms
	
	for (int ievt = 0; ievt < noevt; ievt++)
	{
		p_T->GetEntry(ievt);
		
		h_ladc0_ph->Fill(ph,ladc0);
		h_ladc1_ph->Fill(ph,ladc1);
		h_hadc0_ph->Fill(ph,hadc0);
		h_hadc1_ph->Fill(ph,hadc1);
		
		h_ladc0_th->Fill(th,ladc0);
		h_ladc1_th->Fill(th,ladc1);
		h_hadc0_th->Fill(th,hadc0);
		h_hadc1_th->Fill(th,hadc1);		
	}

	TCanvas * c_th = new TCanvas("c_th","c_th",1000,1000);
	c_th->Divide(2,2);
	c_th->cd(1);
	h_ladc0_th->Draw();
	c_th->cd(2);
	h_ladc1_th->Draw();
	c_th->cd(3);
	h_hadc0_th->Draw();
	c_th->cd(4);
	h_hadc1_th->Draw();

}
