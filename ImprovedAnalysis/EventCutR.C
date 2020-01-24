void EventCutR()
{
	// Input Variables
	double DSQx, USQx, DSQy, USQy;
	double VDCtr, VDCx, VDCy;
	double VDCph, VDCth;
	double DSQadc, USQadc;
	long entries; 
	double DSQped = 555; // 600 too high? 
	double USQped = 490; 
	double DSQcut = 570; 
	double USQcut = 505;
	int nrun = 21331;
	int nsplit_i = 0;
	int nsplit_f = 36;

	// Output Variables 
	double DSQadco, USQadco;
	double DSQpe, USQpe;
	
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

	//for (int isplit = nsplit_i; isplit <= nsplit_f; isplit++)
	{
		TString s_infile = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%i_-1.root",nrun);
		TFile * p_infile = TFile::Open(s_infile,"READ");
		TTree * t_Tin = (TTree*)p_infile->Get("T");
		//cout << "Processing File " << isplit << "..." << endl;
		entries = t_Tin->GetEntries();	
		t_Tin->SetBranchAddress("R.tr.x",&VDCx);
		t_Tin->SetBranchAddress("R.tr.y",&VDCy);
		t_Tin->SetBranchAddress("R.tr.ph",&VDCph);
		t_Tin->SetBranchAddress("R.tr.th",&VDCth);
		t_Tin->SetBranchAddress("R.tr.n",&VDCtr);
		t_Tin->SetBranchAddress("P.loQadcR",&DSQadc);
		t_Tin->SetBranchAddress("P.upQadcR",&USQadc);

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
		}
		p_infile->Close();
	}	

	p_outfile->cd();
	cout << "Cd into file..." << endl;
	t_Tout->Write();
	cout << "Writing file..." << endl;
	p_outfile->Close();
	cout << "Closing file..." << endl;
}
