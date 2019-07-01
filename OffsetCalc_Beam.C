double CalcRes(double x1, double x2)
{
	double resid;
	resid = x1 - x2;
	return resid; 
}

void OffsetCalc_Beam()
{
	// User Variables
	int runno = 1;
	bool arm = 1; // 0 for Left, 1 for Right
	double phmax = 0.0001;
	double thmax = 0.0001;
	// Branch Variables
	double x1t, x2t, x3t, y1t, y2t, y3t;
	double ph, th;
	// Control Variables
	double x2off = 0.0, x3off = 0.0, y2off = 0.0, y3off = 0.0;
	double x2res, x3res, y2res, y3res;
	int dummy;

	TH1D * h_x2 = new TH1D("h_x2","Mean Residual for Straight Tracks, GEM2",2000,-0.001,0.001);

	TString s_infile = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%d_verf.root",runno);
	TFile * f_infile = TFile::Open(s_infile,"READ");
	TTree * Tin = (TTree*)f_infile->Get("T");
	long entries = Tin->GetEntries();

	Tin->SetBranchAddress("x1_coord",&x1t);
	Tin->SetBranchAddress("x2_coord",&x2t);
	Tin->SetBranchAddress("x3_coord",&x3t);
	Tin->SetBranchAddress("y1_coord",&y1t);	
	Tin->SetBranchAddress("y2_coord",&y2t);
	Tin->SetBranchAddress("y3_coord",&y3t);
	Tin->SetBranchAddress("theta",&th);
	Tin->SetBranchAddress("phi",&ph);

	//cout << "Starting call process..." << endl;

	for (int ievt = 0; ievt < entries; ievt++)	
	{
		Tin->GetEntry(ievt);
		if (fabs(th) < thmax && fabs(ph) < phmax)
		{
			//cout << "Found track!" << endl;
			x2res = CalcRes(x1t,x2t);
			h_x2->Fill(x2res);
		}
	}
	
	h_x2->Draw();
	dummy = h_x2->GetMaximumBin();
	x2res = h_x2->GetBinCenter(dummy);
	cout << "X offset in GEM 2: " << x2res << endl;
	//cout << "Y offset in GEM 2: " << y2_offset << endl;
	//cout << "X offset in GEM 3: " << x3_offset << endl;
	//cout << "Y offset in GEM 3: " << y3_offset << endl;	
}

