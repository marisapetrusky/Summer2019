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
	double phmax = 0.0005;
	double thmax = 0.0005;
	// Branch Variables
	double x1t, x2t, x3t, y1t, y2t, y3t;
	double ph, th;
	// Control Variables
	double x2off = 0.0, x3off = 0.0, y2off = 0.0, y3off = 0.0;
	double x2res, x3res, y2res, y3res;
	int dummy;

	TH1D * h_x2 = new TH1D("h_x2","Mean Residual for Straight Tracks, GEM2 X",2000,-0.01,0.01);
	TH1D * h_x3 = new TH1D("h_x3","Mean Residual for Straight Tracks, GEM3 X",2000,-0.01,0.01);
	TH1D * h_y2 = new TH1D("h_y2","Mean Residual for Straight Tracks, GEM2 Y",2000,-0.01,0.01);
	TH1D * h_y3 = new TH1D("h_y3","Mean Residual for Straight Tracks, GEM3 Y",2000,-0.01,0.01);

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
			x3res = CalcRes(x1t,x3t);
			y2res = CalcRes(y1t,y2t);
			y3res = CalcRes(y1t,y3t);
			h_x2->Fill(x2res);
			h_x3->Fill(x3res);
			h_y2->Fill(y2res);
			h_y3->Fill(y3res);
			
		}
	}
	
	TCanvas * c1 = new TCanvas("c1","c1",800,600);
	c1->Divide(2,2);
	c1->cd(1);
	h_x2->Draw();
	c1->cd(2);
	h_y2->Draw();
	c1->cd(3);
	h_x3->Draw();
	c1->cd(4);
	h_y3->Draw();

	dummy = h_x2->FindLastBinAbove(1);
	x2off = h_x2->GetBinCenter(dummy);
	dummy = h_y2->FindLastBinAbove(1);
	y2off = h_y2->GetBinCenter(dummy);
	dummy = h_x3->FindLastBinAbove(1);
	x3off = h_x3->GetBinCenter(dummy);
	dummy = h_y3->FindLastBinAbove(1);
	y3off = h_y3->GetBinCenter(dummy);

	cout << "X offset in GEM 2: " << x2off << endl;
	cout << "Y offset in GEM 2: " << y2off << endl;
	cout << "X offset in GEM 3: " << x3off << endl;
	cout << "Y offset in GEM 3: " << y3off << endl;	
}

