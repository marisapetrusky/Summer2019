void BeamTrack3Sim(int RandSeed = 0)
{
	// User Variables
	int nofile = 1; 
	int entries = 1e6;
	double alert = 1e6;
	double xOff[3] = {0.0,-6.9e-4,6.9e-6};
	double yOff[3] = {0.0,6.9e-5,-6.9e-7};
	bool AddResolution = 0;
	// Output Branch Variables
	double x1_coord, y1_coord, x2_coord, y2_coord, x3_coord, y3_coord;
	double x1_coordt, y1_coordt, x2_coordt, y2_coordt, x3_coordt, y3_coordt;
	double theta, phi;
	// Beam Specs
	double beamCenter = 0.0;
	double beamRMS = 1e-2; // Beam width is 4 cm centered at 0
	// GEM Specs
	const double z1 = 0.0;
	const double z2 = 0.6858;
	const double z3 = 0.889;
	double z[3] = {z1,z2,z3};
	double pitch = 4e-4;
	// Control Variables
	double midFactor = (z1 - z2)/(z3 - z2);
	int xID, yID;
	double xGEM[3];
	double yGEM[3];
	double kx, ky; // Slope of fitted track
	double bx, by; // Y-int of fitted track
	double z0x, z0y; // Z coordinate of Y-int

	TRandom3 * RandGen = new TRandom3(RandSeed);
	
	// Fits and Graphs
	TF1 * f_linx = new TF1("f_linx","[1]*(x-[2]) + [0]",0.,1.);
	//f_linx->FixParameter(2,z[0]);
	TF1 * f_liny = new TF1("f_liny","[1]*(x-[2]) + [0]",0.,1.);
	//f_liny->FixParameter(2,z[0]);

	gStyle->SetOptFit(1);

	TString s_outfile = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%d_verf.root",nofile);
	TFile * f_outfile = TFile::Open(s_outfile,"RECREATE");
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

	for (int ievt = 0; ievt < entries; ievt++)
	{
		
		//{cout << "Processing event " << ievt << endl;}
	
		// Simulate GEM tracks
		x1_coord = RandGen->Gaus(beamCenter,beamRMS);
		x3_coord = RandGen->Gaus(beamCenter,beamRMS);
		x2_coord = (1/(1-midFactor))*(x1_coord - midFactor*x3_coord);
		y1_coord = RandGen->Gaus(beamCenter,beamRMS);
		y3_coord = RandGen->Gaus(beamCenter,beamRMS);
		y2_coord = (1/(1-midFactor))*(y1_coord - midFactor*y3_coord);		
		//x1_coord = x1_coord; 
		//y1_coord = y1_coord;
		x2_coord = x2_coord + xOff[1];
		y2_coord = y2_coord + yOff[1];
		x3_coord = x2_coord + xOff[2];
		y3_coord = y3_coord + yOff[2];
		
		if (AddResolution)
		{
			xID = floor(x1_coord/pitch);
			x1_coord = xID * pitch + pitch/2;
			xID = floor(x2_coord/pitch);
			x2_coord = xID * pitch + pitch/2;
			xID = floor(x3_coord/pitch);
			x3_coord = xID * pitch + pitch/2;
			yID = floor(y1_coord/pitch);
			y1_coord = yID * pitch + pitch/2;
			yID = floor(y2_coord/pitch);
			y2_coord = yID * pitch + pitch/2;
			yID = floor(y3_coord/pitch);
			y3_coord = yID * pitch + pitch/2;
		}
		
		xGEM[0] = x1_coord;
		xGEM[1] = x2_coord;
		xGEM[2] = x3_coord;
		yGEM[0] = y1_coord;
		yGEM[1] = y2_coord;
		yGEM[2] = y3_coord;
		
		//f_linx->FixParameter(0,xGEM[0]);
		//f_liny->FixParameter(0,yGEM[0]);
		
		TGraph * gx = new TGraph(3,z,xGEM);
		TGraph * gy = new TGraph(3,z,yGEM);
		gx->Fit(f_linx,"QR","",0,1);
		gy->Fit(f_liny,"QR","",0,1);
		
		kx = f_linx->GetParameter(1);
		ky = f_liny->GetParameter(1);
		bx = f_linx->GetParameter(0);
		by = f_liny->GetParameter(0);
		z0x = f_linx->GetParameter(2);
		z0y = f_liny->GetParameter(2);

		theta = atan2(kx);
		phi = atan2(ky);
		
		x1_coordt = kx*(z1 - z0x) + bx;//x1_coord;
		x2_coordt = kx*(z2 - z0x) + bx;
		x3_coordt = kx*(z3 - z0x) + bx;//x1_coord;
		y1_coordt = ky*(z1 - z0y) + by;
		y2_coordt = ky*(z2 - z0y) + by;//y1_coord;
		y3_coordt = ky*(z3 - z0y) + by;//y1_coord;

		Tout->Fill();
	}
	
	Tout->Write();
	f_outfile->Close();
	
}
