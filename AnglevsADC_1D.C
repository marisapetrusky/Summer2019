void AnglevsADC_2D()
{
	TFile * p_infile = TFile::Open("/home/marisa/rootfiles/test_409.root","READ");//mergedtests.root");
	TTree * t_T = (TTree*)p_infile->Get("T");
	
	// Variables and Branches 
	// Angles in Radians 
	
	double ph, th;
	double hadc0, hadc1;
	double ladc0, ladc1;
	double phmax = 0.3, phmin = -0.30;
	double thmax = 0.15, thmin = -0.15;
	double hadc0max = 800, hadc0min = 120;
	double ladc0max = 4000, ladc0min = 1000;
	double hadc1max = 350, hadc1min = 110;
	double ladc1max = 800, ladc1min = 2700;

	t_T->SetBranchAddress("prex.tr.ph",&ph);
	t_T->SetBranchAddress("prex.tr.th",&th);
	t_T->SetBranchAddress("prex.sbuscint.hadc0",&hadc0);
	t_T->SetBranchAddress("prex.sbuscint.hadc1",&hadc1);
	t_T->SetBranchAddress("prex.sbuscint.ladc0",&ladc0);
	t_T->SetBranchAddress("prex.sbuscint.ladc1",&ladc1);
	
	long noevt = 4935;//ph->GetEntries();
	//cout << "Number of Events is " << noevt << endl;
	
	// Histograms
	
	gStyle->SetOptStat("Men");
	
	TH2D * h_ladc0_ph = new TH2D("ladc0.ph","Low ADC0 Charge vs #phi",50,phmin,phmax,100,ladc0min,ladc0max);
	h_ladc0_ph->SetOption("COLZ");
	TH2D * h_hadc0_ph = new TH2D("hadc0.ph","High ADC0 Charge vs #phi",50,phmin,phmax,100,hadc0min,hadc0max);
	h_hadc0_ph->SetOption("COLZ");
	TH2D * h_ladc1_ph = new TH2D("ladc1.ph","Low ADC1 Charge vs #phi",50,phmin,phmax,100,ladc1min,ladc1max);
	h_ladc1_ph->SetOption("COLZ");
	TH2D * h_hadc1_ph = new TH2D("hadc1.ph","High ADC1 Charge vs #phi",50,phmin,phmax,100,hadc1min,hadc1max);
	h_hadc1_ph->SetOption("COLZ");
	TH2D * h_ladc0_th = new TH2D("ladc0.th","Low ADC0 Charge vs #theta",50,thmin,thmax,100,ladc1min,ladc1max);
	h_ladc0_th->SetOption("COLZ");
	TH2D * h_hadc0_th = new TH2D("hadc0.th","High ADC0 Charge vs #theta",50,thmin,thmax,100,hadc1min,hadc1max);
	h_hadc0_th->SetOption("COLZ");
	TH2D * h_ladc1_th = new TH2D("ladc1.th","Low ADC1 Charge vs #theta",50,thmin,thmax,100,ladc1min,ladc1max);
	h_ladc1_th->SetOption("COLZ");
	TH2D * h_hadc1_th = new TH2D("hadc1.th","High ADC1 Charge vs #theta",50,thmin,thmax,100,hadc1min,hadc1max);
	h_hadc1_th->SetOption("COLZ");

	// Fill Histograms
	
	for (int ievt = 0; ievt < noevt; ievt++)
	{
		//cout << "Event Number " << ievt << endl;
		//int dummy = ievt; // M: Somehow fixed "Warning: Invalid Memory Pointer Passed to a Callee"
		t_T->GetEntry(ievt);
		
		h_ladc0_ph->Fill(ph,ladc0);
		h_ladc1_ph->Fill(ph,ladc1);
		h_hadc0_ph->Fill(ph,hadc0);
		h_hadc1_ph->Fill(ph,hadc1);
		
		h_ladc0_th->Fill(th,ladc0);
		h_ladc1_th->Fill(th,ladc1);
		h_hadc0_th->Fill(th,hadc0);
		h_hadc1_th->Fill(th,hadc1);		
	}

	TCanvas * c_th = new TCanvas("c_th","c_th",900,900);
	c_th->Divide(2,2);
	c_th->cd(1);
	h_ladc0_th->Draw();
	c_th->cd(2);
	h_ladc1_th->Draw();
	c_th->cd(3);
	h_hadc0_th->Draw();
	c_th->cd(4);
	h_hadc1_th->Draw();

	TCanvas * c_ph = new TCanvas("c_ph","c_ph",900,900);
	c_ph->Divide(2,2);
	c_ph->cd(1);
	h_ladc0_ph->Draw();
	c_ph->cd(2);
	h_ladc1_ph->Draw();
	c_ph->cd(3);
	h_hadc0_ph->Draw();
	c_ph->cd(4);
	h_hadc1_ph->Draw();
}
