void QuartzMap_TH3D()
{
	// User Variables
	int runs[9] = {427,430,431,438,439,440,441,442,444};
	int noruns = 9;
	// Branch Variables
	double x1, x2, x3, x4;
	double y1, y2, y3, y4;
	double qx1, qx2;
	double qy1, qy2;
	double ph, th;
	double hadc0, hadc1, ladc0, ladc1;
	long entries;
	double pedestal_l[2] = {1166,1067};
	double pedestal_h[2] = {148,135};
	// Histograms
	gStyle->SetOptStat("nemruoi");
	auto * h_q1_l = new TH3D("h_q1_l","Quartz 1 Map, Low Resolution",25,0.,0.,50,0.,0.,12,0,0.);
	h_q1_l->GetXaxis()->SetTitle("X-axis (5 cm long)");
	h_q1_l->GetYaxis()->SetTitle("Y-axis (10 cm long)");
	TH3D * h_q2_l= new TH3D("h_q2_l","Quartz 2 Map, Low Resolution",25,0.,0.,50,0.,0.,12,0.,0.);
	h_q2_l->GetXaxis()->SetTitle("X-axis (5 cm long)");
	h_q2_l->GetYaxis()->SetTitle("Y-axis (10 cm long)");
	TH3D * h_q1_h = new TH3D("h_q1_h","Quartz 1 Map, High Resolution",25,0.,0.,50,0.,0.,40,0.,0.);
	h_q1_h->GetXaxis()->SetTitle("X-axis (5 cm long)");
	h_q1_h->GetYaxis()->SetTitle("Y-axis (10 cm long)");
	TH3D * h_q2_h = new TH3D("h_q2_h","Quartz 2 Map, High Resolution",25,0.,0.,50,0.,0.,40,0.,0.);
	h_q2_h->GetXaxis()->SetTitle("X-axis (5 cm long)");
	h_q2_h->GetYaxis()->SetTitle("Y-axis (10 cm long)");

	//cout << "Enter run number" << endl;
	//cin >> run;

	for (int irun = 0; irun < noruns; irun++)
	{
		cout << "Processing Run " << runs[irun] << endl;

		TString s_infile = Form("/home/marisa/rootfiles/test_%d_verf.root",runs[irun]);
		TFile * p_infile = TFile::Open(s_infile,"READ");
		TTree * t_T = (TTree*)p_infile->Get("T");
		entries = t_T->GetEntries();
		t_T->SetBranchAddress("x1_coord",&x1);
		t_T->SetBranchAddress("x2_coord",&x2);
		t_T->SetBranchAddress("x3_coord",&x3);
		t_T->SetBranchAddress("x4_coord",&x4);
		t_T->SetBranchAddress("y1_coord",&y1);
		t_T->SetBranchAddress("y2_coord",&y2);
		t_T->SetBranchAddress("y3_coord",&y3);
		t_T->SetBranchAddress("y4_coord",&y4);
		t_T->SetBranchAddress("qx1_coord",&qx1);
		t_T->SetBranchAddress("qx2_coord",&qx2);
		t_T->SetBranchAddress("qy1_coord",&qy1);
		t_T->SetBranchAddress("qy2_coord",&qy2);
		t_T->SetBranchAddress("phi",&ph);
		t_T->SetBranchAddress("theta",&th);
		t_T->SetBranchAddress("h_adc0",&hadc0);
		t_T->SetBranchAddress("h_adc1",&hadc1);
		t_T->SetBranchAddress("l_adc0",&ladc0);
		t_T->SetBranchAddress("l_adc1",&ladc1);

		for (int ievt = 0; ievt < entries; ievt++)
		{
			t_T->GetEntry(ievt);
			//cout << qx1 << endl;
			if (ladc0 > pedestal_l[0] && ladc1 > pedestal_l[1] && hadc0 > pedestal_h[0] && hadc1 > pedestal_h[1])
			{
				h_q1_l->Fill(qx1,qy1,ladc0);
				h_q2_l->Fill(qx2,qy2,ladc1);
				h_q1_h->Fill(qx1,qy1,hadc0);
				h_q2_h->Fill(qx2,qy2,hadc1);
			}
		}	
	}

	h_q1_l->Draw();	
}
