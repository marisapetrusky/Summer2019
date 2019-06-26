void GetVerified()
{
	// User Variables
	int bins = 50; 
	double resmin, resmax;
	// Input Branch Variables
	double tr; 
	double x1, y1, x2, y2, x3, y3;
	double x1t, y1t, x2t, y2t, x3t, y3t;
	double x1res, y1res, x2res, y2res, x3res, y3res;
	double ph, th;
	long entries;
	// Output Branch Variables
	double x1_coord, y1_coord, x2_coord, y2_coord, x3_coord, y3_coord;
	double x1_coordt, y1_coordt, x2_coordt, y2_coordt, x3_coordt, y3_coordt;
	double theta, phi;
	// Control Variables
	int runno, nofiles;
	bool arm = 1;
	TString s_infile, s_outfile; 

	// Histograms
	TH1D * h_x1res = new TH1D("x1res","X1 Residual",bins,0.,0.);
	TH1D * h_y1res = new TH1D("y1res","Y1 Residual",bins,0.,0.);
	TH1D * h_x2res = new TH1D("x2res","X2 Residual",bins,0.,0.);
	TH1D * h_y2res = new TH1D("y2res","Y2 Residual",bins,0.,0.);
	TH1D * h_x3res = new TH1D("x3res","X3 Residual",bins,0.,0.);
	TH1D * h_y3res = new TH1D("y3res","Y3 Residual",bins,0.,0.);
	TH1D * h_ph = new TH1D("ph","Phi",bins,0.,0.);
	TH1D * h_th = new TH1D("th","Theta",bins,0.,0.);

	cout << "Enter Run number" << endl;
	cin >> runno;
	cout << "Enter last index of .root file (e.g. prexRHRS..._15.root is the last index)" << endl;
	cin >> nofiles; 
	
	cout << "Left (0) or Right (1) Arm?" << endl;
	cin >> arm; 
	

	//Create Output File
	TTree * Tout = new TTree("T","T");
	TBranch * b_x1 = Tout->Branch("x1_coord",&x1_coord,"x1_coord/D");
	TBranch * b_y1 = Tout->Branch("y1_coord",&y1_coord,"y1_coord/D");
	TBranch * b_x2 = Tout->Branch("x2_coord",&x2_coord,"x2_coord/D");
	TBranch * b_y2 = Tout->Branch("y2_coord",&y2_coord,"y2_coord/D");
	TBranch * b_x3 = Tout->Branch("x3_coord",&x3_coord,"x3_coord/D");
	TBranch * b_y3 = Tout->Branch("y3_coord",&y3_coord,"y3_coord/D");
	TBranch * b_x1t = Tout->Branch("x1_coordt",&x1_coordt,"x1_coordt/D");
	TBranch * b_y1t = Tout->Branch("y1_coordt",&y1_coordt,"y1_coordt/D");
	TBranch * b_x2t = Tout->Branch("x2_coordt",&x2_coordt,"x2_coordt/D");
	TBranch * b_y2t = Tout->Branch("y2_coordt",&y2_coordt,"y2_coordt/D");
	TBranch * b_x3t = Tout->Branch("x3_coordt",&x3_coordt,"x3_coordt/D");
	TBranch * b_y3t = Tout->Branch("y3_coordt",&y3_coordt,"y3_coordt/D");
	TBranch * b_phi = Tout->Branch("phi",&phi,"phi/D");
	TBranch * b_theta = Tout->Branch("theta",&theta,"theta/D");

	for (int ifile = 0; ifile <= nofiles; ifile++)
	{
		cout << "Processing File " << ifile << "..." << endl;
		if (arm)
		{
			s_infile = Form("/chafs1/work1/marisa/RHRS/NoOffsetCosmic/prexRHRS_20452_%d.root",ifile);
		}
		else 
		{
			s_infile = Form("/chafs1/work1/marisa/LHRS/NoOffsetCosmic/prexLHRS_20452_%d.root",ifile);
		}

		TFile * f_infile = TFile::Open(s_infile,"READ");
		TTree * Tin = (TTree*)f_infile->Get("T");
		Tin->SetBranchAddress("RGEM.tr.n",&tr);
		Tin->SetBranchAddress("RGEM.rgems.x1.coord.3Dpos",&x1t);	
		Tin->SetBranchAddress("RGEM.rgems.x2.coord.3Dpos",&x2t);	
		Tin->SetBranchAddress("RGEM.rgems.x3.coord.3Dpos",&x3t);	
		Tin->SetBranchAddress("RGEM.rgems.y1.coord.3Dpos",&y1t);	
		Tin->SetBranchAddress("RGEM.rgems.y2.coord.3Dpos",&y2t);	
		Tin->SetBranchAddress("RGEM.rgems.y3.coord.3Dpos",&y3t);
		Tin->SetBranchAddress("RGEM.rgems.x1.coord.pos",&x1);	
		Tin->SetBranchAddress("RGEM.rgems.x2.coord.pos",&x2);	
		Tin->SetBranchAddress("RGEM.rgems.x3.coord.pos",&x3);	
		Tin->SetBranchAddress("RGEM.rgems.y1.coord.pos",&y1);	
		Tin->SetBranchAddress("RGEM.rgems.y2.coord.pos",&y2);	
		Tin->SetBranchAddress("RGEM.rgems.y3.coord.pos",&y3);
		Tin->SetBranchAddress("RGEM.rgems.x1.coord.resid",&x1res);
		Tin->SetBranchAddress("RGEM.rgems.x2.coord.resid",&x2res);
		Tin->SetBranchAddress("RGEM.rgems.x3.coord.resid",&x3res);
		Tin->SetBranchAddress("RGEM.rgems.y1.coord.resid",&y1res);
		Tin->SetBranchAddress("RGEM.rgems.y2.coord.resid",&y2res);
		Tin->SetBranchAddress("RGEM.rgems.y3.coord.resid",&y3res);
		Tin->SetBranchAddress("RGEM.tr.th",&th);
		Tin->SetBranchAddress("RGEM.tr.ph",&ph);
		entries = Tin->GetEntries();

		for (int ievt = 0; ievt < entries; ievt++)
		{
			Tin->GetEntry(ievt);
			if (tr > 0) 
			{
				h_x1res->Fill(x1res);
				h_y1res->Fill(y1res);
				h_x2res->Fill(x2res);
				h_y2res->Fill(y2res);
				h_x3res->Fill(x3res);
				h_y3res->Fill(y3res);
				h_ph->Fill(ph);
				h_th->Fill(th);			
				
				x1_coord = x1;
				x2_coord = x2;
				x3_coord = x3;
				y1_coord = y1;
				y2_coord = y2; 
				y3_coord = y3;	
				x1_coordt = x1t;
				x2_coordt = x2t;
				x3_coordt = x3t;
				y1_coordt = y1t;
				y2_coordt = y2t; 
				y3_coordt = y3t;
				phi = ph;
				theta = th;
	
				Tout->Fill();	
			}
		}
		f_infile->Close();
	}
	
	if (!arm)
	{
		s_outfile = Form("/chafs1/work1/marisa/LHRS/prexLHRS_%d_verf.root",runno);
	}
	if (arm)
	{	
		s_outfile = Form("/chafs1/work1/marisa/RHRS/prexRHRS_%d_verf.root",runno);
	}

	TFile * f_outfile = TFile::Open(s_outfile,"RECREATE");
	Tout->Write();
	f_outfile->Close();

	TCanvas * c1 = new TCanvas("c1","c1",1200,800);
	c1->Divide(2,1);
	c1->cd(1);
	h_ph->Draw();
	c1->cd(2);
	h_th->Draw();
	
	TCanvas * c2 = new TCanvas("c2","c2",1200,800);
	c2->Divide(3,2);
	c2->cd(1);
	h_x1res->Draw();
	c2->cd(2);
	h_x2res->Draw();
	c2->cd(3);
	h_x3res->Draw();
	c2->cd(4);
	h_y1res->Draw(); 
	c2->cd(5);
	h_y2res->Draw();
	c2->cd(6);
	h_y3res->Draw();
}
