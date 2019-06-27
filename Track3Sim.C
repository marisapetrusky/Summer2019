void Track3Sim(int RandSeed = 0)
{
	// User Variables
	int nofile = 0;
	int entries = 100000;
	double xOff[3] = {3.5e-4,6.9e-6};
	double yOff[3] = {7.4e-3,2.5e-7};
	// Output Branch Variables
	double x1_coord, y1_coord, x2_coord, y2_coord, x3_coord, y3_coord;
	double x1_coordt, y1_coordt, x2_coordt, y2_coordt, x3_coordt, y3_coordt;
	double theta, phi;
	// GEM Specs
	double xGEMmin = -0.05, xGEMmax = 0.05;
	double yGEMmin = -0.1, yGEMmax = 0.1; 
	const double z1 = 0; 
	const double z2 = 0.6858;
	const double z3 = 0.889;
	double z[3] = {z1,z2,z3};
	double pitch = 4e-4; // Width of one strip  
	// Control Variables
	double xGEM[3], yGEM[3];
	double midFactor = (z1 - z2)/(z3 - z2); 
	int xID, yID;

	TRandom3 * RandGen = new TRandom3(RandSeed);	

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
	//TBranch * b_phi = Tout->Branch("phi",&phi,"phi/D");
	//TBranch * b_theta = Tout->Branch("theta",&theta,"theta/D");

	for (int ievt = 0; ievt < entries; ievt++)
	{
		// Simulate truth tracks
		x1_coord = RandGen->Uniform(xGEMmin,xGEMmax);
		x3_coord = RandGen->Uniform(xGEMmin,xGEMmax);
		x2_coord = (1/(1-midFactor))*(x1_coord - midFactor*x3_coord);

		y1_coord = RandGen->Uniform(yGEMmin,yGEMmax);
		y3_coord = RandGen->Uniform(yGEMmin,yGEMmax);
		y2_coord = (1/(1-midFactor))*(y1_coord - midFactor*y3_coord);

		// Simulate GEM tracks with resolution
		x1_coordt = x1_coord;
		y1_coordt = y1_coord; 
		x2_coordt = y2_coord + xOff[1];
		y2_coordt = y2_coord + yOff[1];
		x3_coordt = x3_coord + xOff[2];
		y3_coordt = y3_coord + yOff[2];
		
		xID = floor(x1_coordt/pitch);
		x1_coordt = xID * pitch + pitch/2;
		xID = floor(x2_coordt/pitch);
		x2_coordt = xID * pitch + pitch/2;
		xID = floor(x3_coordt/pitch);
		x3_coordt = xID * pitch + pitch/2;
		yID = floor(y1_coordt/pitch);
		y1_coordt = yID * pitch + pitch/2;
		yID = floor(y2_coordt/pitch);
		y2_coordt = yID * pitch + pitch/2;
		yID = floor(y3_coordt/pitch);
		y3_coordt = yID * pitch + pitch/2;

		Tout->Fill();
	}
	
	Tout->Write();
	f_outfile->Close();		
}
