double z[3] = {0.0,0.6858,0.889};
double F = ((z[1] - z[0])/z[2] - z[0]);

double CalcPos(double x2, double x3, double x2off, double x3off)
{
	double x1;
	x1 = 1/(1-F) * (x2 - F*x3 + x2off - F*x3off);
	return x1; 
} 

double CalcRes(double x1, double x1t)
{
	double resid;
	resid = x1t - x1;
	return resid; 
}

void OffsetCalc()
{
	// User Variables
	int runno = 20452;
	bool arm = 1; // 0 for Left, 1 for Right
	long maxcalls = 2e5;
	double minTrans = -1e-2;
	double maxTrans = 1e-2;
	double stepTrans = 1e-7;
	// Branch Variables
	double x1, x2t, x3t, y1, y2t, y3t;
	double x1_fit, y1_fit; // x1 and y1 positions fitted with offsets
	// Control Variables
	double x2off = minTrans, x3off = 0.0, y2off = 0.0, y3off = 0.0;
	double x2res, x3res, y2res, y3res;
	double dummy;

	TH2D * h_x2 = new TH2D("h_x2","Mean Residual vs GEM2 X Offset",2e5,0.,0.,5e2,0.,0.);

	TString s_infile = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%d_verf.root",runno);
	TFile * f_infile = TFile::Open(s_infile,"READ");
	TTree * Tin = (TTree*)f_infile->Get("T");
	long entries = Tin->GetEntries();

	//Tin->SetBranchAddress("x1_coordt",&x1_coordt);
	Tin->SetBranchAddress("x2_coordt",&x2t);
	Tin->SetBranchAddress("x3_coordt",&x3t);
	//Tin->SetBranchAddress("y1_coordt",&y1_coordt);	
	Tin->SetBranchAddress("y2_coordt",&y2t);
	Tin->SetBranchAddress("y3_coordt",&y3t);
	Tin->SetBranchAddress("x1_coord",&x1);
	Tin->SetBranchAddress("y1_coord",&y1);

	cout << "Starting call process..." << endl;

	for (int icall = 0; icall < maxcalls; icall++)
	{
		for (int ievt = 0; ievt < entries; ievt++)	
		{
			Tin->GetEntry(ievt);
			x1_fit = CalcPos(x2t,x3t,x2off,x3off);
			dummy = CalcRes(x1,x1_fit);
			x2res += dummy;
		}
 
		x2res = fabs(x2res/entries);		
		h_x2->Fill(x2off,x2res);
		
		x2res = 0.0;
		x2off += stepTrans;
	
		if (icall%1000 == 0)
		{cout << "Reached call number " << icall << "..." << endl;}
	}
	
	h_x2->Draw();
	//double h_min = h_x2->GetYaxis()->GetXmin();
	//double 
	//int maxbin = h_x2->GetMinimumBin();

	//cout << "X offset in GEM 2: " << x2_offset << endl;
	//cout << "Y offset in GEM 2: " << y2_offset << endl;
	//cout << "X offset in GEM 3: " << x3_offset << endl;
	//cout << "Y offset in GEM 3: " << y3_offset << endl;	
}

