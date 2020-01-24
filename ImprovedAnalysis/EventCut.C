void EventCut()
{
	// Input Variables
	double DSQx, USQx, DSQy, USQy;
	double GDSQx, GUSQx, GDSQy, GUSQy;
	double VDCtr, VDCx, VDCy;
	double VDCph, VDCth;
	double GEMtr, GEMx, GEMy;
	double GEMph, GEMth;
	double DSQadc, USQadc;
	long entries; 
	double DSQcut = 600;// too high? 
	double USQcut = 485; 
	double DSQped = 585; 
	double USQped = 465;
	int nrun = 2011;//2004;
	int nsplit_i = 0;
	int nsplit_f = 36;

	// Output Variables 
	double DSQadco, USQadco;
	double GDSQadco, GUSQadco;
	double DSQpe, USQpe;
	double GDSQpe, GUSQpe;
	
	TString s_outfile = Form("Run%i_cuts.root",nrun);
	TFile * p_outfile = TFile::Open(s_outfile,"RECREATE");
	TTree * t_Tout = new TTree("T","T");
	TBranch * b_DSQx = t_Tout->Branch("DSQx",&DSQx,"DSQx/D");
	TBranch * b_USQx = t_Tout->Branch("USQx",&USQx,"USQx/D");
	TBranch * b_DSQy = t_Tout->Branch("DSQy",&DSQy,"DSQy/D");
	TBranch * b_USQy = t_Tout->Branch("USQy",&USQy,"USQy/D");
	TBranch * b_DSQadc = t_Tout->Branch("DSQadc",&DSQadco,"DSQadco/D");
	TBranch * b_USQadc = t_Tout->Branch("USQadc",&USQadco,"USQadco/D");
	TBranch * b_DSQpe = t_Tout->Branch("DSQpe",&DSQpe,"DSQpe/D");
	TBranch * b_USQpe = t_Tout->Branch("USQpe",&USQpe,"USQpe/D");
	TTree * t_Tout2 = new TTree("T2","T2");
	TBranch * b_GDSQx = t_Tout2->Branch("GDSQx",&GDSQx,"GDSQx/D");
	TBranch * b_GUSQx = t_Tout2->Branch("GUSQx",&GUSQx,"GUSQx/D");
	TBranch * b_GDSQy = t_Tout2->Branch("GDSQy",&GDSQy,"GDSQy/D");
	TBranch * b_GUSQy = t_Tout2->Branch("GUSQy",&GUSQy,"GUSQy/D");
	TBranch * b_GDSQadc = t_Tout2->Branch("GDSQadc",&GDSQadco,"GDSQadco/D");
	TBranch * b_GUSQadc = t_Tout2->Branch("GUSQadc",&GUSQadco,"GUSQadco/D");
	TBranch * b_GDSQpe = t_Tout->Branch("GDSQpe",&GDSQpe,"GDSQpe/D");
	TBranch * b_GUSQpe = t_Tout->Branch("GUSQpe",&GUSQpe,"GUSQpe/D");

	//for (int isplit = nsplit_i; isplit <= nsplit_f; isplit++)
	{
		TString s_infile = Form("/chafs1/work1/prex_counting/marisa/LHRS/prexLHRS_2011_50000.root");//Run2004/prexLHRS_2004_-1_%i.root",isplit);
		TFile * p_infile = TFile::Open(s_infile,"READ");
		TTree * t_Tin = (TTree*)p_infile->Get("T");
		//cout << "Processing File " << isplit << "..." << endl;
		entries = t_Tin->GetEntries();	
		t_Tin->SetBranchAddress("L.tr.x",&VDCx);
		t_Tin->SetBranchAddress("L.tr.y",&VDCy);
		t_Tin->SetBranchAddress("L.tr.ph",&VDCph);
		t_Tin->SetBranchAddress("L.tr.th",&VDCth);
		t_Tin->SetBranchAddress("L.tr.n",&VDCtr);
		t_Tin->SetBranchAddress("P.loQadcL",&DSQadc);
		t_Tin->SetBranchAddress("P.upQadcL",&USQadc);
		t_Tin->SetBranchAddress("LGEM.lgems.x1.coord.3Dpos",&GEMx);
		t_Tin->SetBranchAddress("LGEM.lgems.y1.coord.3Dpos",&GEMy);
		t_Tin->SetBranchAddress("LGEM.tr.th",&GEMth);
		t_Tin->SetBranchAddress("LGEM.tr.ph",&GEMph);
		t_Tin->SetBranchAddress("LGEM.tr.n",&GEMtr);
		for (int ievt = 0; ievt < entries; ievt++)
		{
			t_Tin->GetEntry(ievt);
			if (VDCtr > 0)
			{
				if (DSQadc > DSQcut && USQadc > USQcut)
				{
					DSQx = VDCx + 1.06*VDCth;
					DSQy = VDCy + 1.06*VDCph;
					USQx = VDCx + 0.9*VDCth;
					USQy = VDCy + 0.9*VDCph;
					DSQadco = DSQadc - DSQped; // Use pedestal only as cut
					USQadco = USQadc - USQped; 
					DSQpe = (0.5 * 1.6/.646)*DSQadco;
					USQpe = (0.5 * 1.6/.646)*USQadco;
					t_Tout->Fill();		
				}
			}
			if (GEMtr > 0)
			{
				if (DSQadc > DSQcut && USQadc > USQcut)
				{
					GDSQx = GEMx + 0.216*GEMth;
					GDSQy = GEMy + 0.216*GEMph;
					GUSQx = GEMx + 0.376*GEMth;
					GUSQy = GEMy + 0.376*GEMph;
					GUSQadco = USQadc - USQped; 
					GDSQadco = DSQadc - DSQped;
					GUSQpe = (0.5 * 1.6/.646)*GUSQadco;
					GDSQpe = (0.5 * 1.6/.646)*GDSQadco;
					t_Tout2->Fill();
				}
			}
		}
		p_infile->Close();
	}	

	p_outfile->cd();
	cout << "Cd into file..." << endl;
	t_Tout->Write();
	t_Tout2->Write();
	cout << "Writing file..." << endl;
	p_outfile->Close();
	cout << "Closing file..." << endl;
}
