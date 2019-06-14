bool QuartzCheck(double th, double ph, double x0, double y0, double z0)
{
	bool Verbose = 0; // Decide if you want output messages displayed
	double q_xproj[2], q_yproj[2];
	double q_xmax = 0.025; // Correct quartz dimensions?
	double q_ymax = 0.05;
	double q_z[2] = {0.7,0.71};
	
	for (int iquartz = 0; iquartz < 2; iquartz++)
	{	
		q_xproj[iquartz] = tan(th)*(q_z[iquartz] - z0) + x0;
		q_xproj[iquartz] = fabs(q_xproj[iquartz]);
		q_yproj[iquartz] = tan(ph)*(q_z[iquartz] - z0) + y0;
		q_yproj[iquartz] = fabs(q_yproj[iquartz]);
	}
	if (q_xproj[0]< q_xmax && q_yproj[0] < q_ymax)
	{
		if (Verbose) {cout << "Hit in Quartz 1!" << endl;}
		if (q_xproj[1] < q_xmax && q_yproj[1] < q_ymax)
		{
			if (Verbose) {cout << "Hit in Quartz 2!" << endl;}
			return true;
		}
		else {return false;}
	}
	else {return false;}
}

bool QuartzCheck(double th, double ph, double x0, double y0, double z0, double& qx1, double& qx2, double& qy1, double& qy2)
{
	bool Verbose = 0; // Decide if you want output messages displayed
	double q_xproj[2], q_yproj[2];
	double q_xmax = 0.025; // Correct quartz dimensions?
	double q_ymax = 0.05;
	double q_z[2] = {0.7,0.71};

	for (int iquartz = 0; iquartz < 2; iquartz++)
	{	
		q_xproj[iquartz] = tan(th)*(q_z[iquartz] - z0) + x0;
		//q_xproj[iquartz] = fabs(q_xproj[iquartz]);
		q_yproj[iquartz] = tan(ph)*(q_z[iquartz] - z0) + y0;
		//q_yproj[iquartz] = fabs(q_yproj[iquartz]);
	}
	if (fabs(q_xproj[0]) < q_xmax && fabs(q_yproj[0]) < q_ymax)
	{
		if (Verbose) {cout << "Hit in Quartz 1!" << endl;}
		if (fabs(q_xproj[1]) < q_xmax && fabs(q_yproj[1]) < q_ymax)
		{
			if (Verbose) {cout << "Hit in Quartz 2!" << endl;}
			qx1 = q_xproj[0];
			qx2 = q_xproj[1];
			qy1 = q_yproj[0];
			qy2 = q_yproj[1];
			return true;
		}
		else {return false;}
	}
	else {return false;}
}

int Tracker()
{
	// User Variables 
	bool ProjectionOn = 1; // Set TRUE if you'd like to input Z positions and output X and Y positions
	bool QuartzCheckOn = 1; // Set TRUE if you'd like to check if the track hit the quartz detectors
	bool FixedZ = 0; // Set TRUE if only checking one z spot, set FALSE if different z position per entry
	bool PromptUser = 0; // Set TRUE if you want prompts to go through good tracks one by one
	bool Verbose = 0; // Set TRUE if you want projected positions displayed each time
	bool OutputFile = 1; // Set TRUE if you want a separate ROOT file with all quartz verified tracks in it
	// Branch Variables
	long entries; 
	double tr; 
	double x0, y0, z0 = 0; // Decide reference plane and edit height
	//double x2, y2, z2, x2_resid, y2_resid;
	double th, ph;
	double xproj, yproj, zproj;
	double x1, x2, x3;
	double y1, y2, y3;
	double hadc0, hadc1, ladc0, ladc1;
	double x1_coord, x2_coord, x3_coord, x4_coord;
	double y1_coord, y2_coord, y3_coord, y4_coord;
	double qx1_coord = 10, qx2_coord = 10, qy1_coord = 10, qy2_coord = 10;
	double phi, theta;
	double h_adc0, h_adc1, l_adc0, l_adc1;
	// Calculated Variables
	double qevt_proj = 0, qevt_verf = 0;
	double q_efficiency; 
	// For Code
	int run;	
	int SameEntry = 0; 
	bool QuartzHit;

	cout << "Enter run number" << endl;
	cin >> run;

	TString s_infile = Form("/home/marisa/rootfiles/test_%d.root",run);
	TFile * p_infile = TFile::Open(s_infile,"READ");
	TTree * t_Tin = (TTree*)p_infile->Get("T");

	t_Tin->SetBranchAddress("prex.tr.n",&tr);
	t_Tin->SetBranchAddress("prex.gems.x1.coord.3Dpos",&x0);
	t_Tin->SetBranchAddress("prex.gems.y1.coord.3Dpos",&y0);
	//t_Tin->SetBranchAddress("prex.gems.x2.coord.3Dpos",&x2);
	//t_Tin->SetBranchAddress("prex.gems.y2.coord.3Dpos",&y2);
	//t_Tin->SetBranchAddress("prex.gems.x2.coord.resid",&x2_resid);
	//t_Tin->SetBranchAddress("prex.gems.y2.coord.resid",&y2_resid);
	t_Tin->SetBranchAddress("prex.tr.ph",&ph);
	t_Tin->SetBranchAddress("prex.tr.th",&th);
	entries = t_Tin->GetEntries();

	//if (OutputFile)
	
		t_Tin->SetBranchAddress("prex.gems.x2.coord.3Dpos",&x1);
		t_Tin->SetBranchAddress("prex.gems.y2.coord.3Dpos",&y1);
		t_Tin->SetBranchAddress("prex.gems.x3.coord.3Dpos",&x2);
		t_Tin->SetBranchAddress("prex.gems.y3.coord.3Dpos",&y2);
		t_Tin->SetBranchAddress("prex.gems.x4.coord.3Dpos",&x3);
		t_Tin->SetBranchAddress("prex.gems.y4.coord.3Dpos",&y3);
		t_Tin->SetBranchAddress("prex.sbuscint.hadc0",&hadc0);
		t_Tin->SetBranchAddress("prex.sbuscint.hadc1",&hadc1);
		t_Tin->SetBranchAddress("prex.sbuscint.ladc0",&ladc0);
		t_Tin->SetBranchAddress("prex.sbuscint.ladc1",&ladc1);

		TString s_outfile = Form("/home/marisa/rootfiles/test_%d_verf.root",run);
		TFile * p_outfile = TFile::Open(s_outfile,"RECREATE");
		TTree *t_Tout = new TTree("T","T");
		TBranch * b_x1 = t_Tout->Branch("x1_coord",&x1_coord,"x1_coord/D");
		TBranch * b_y1 = t_Tout->Branch("y1_coord",&y1_coord,"y1_coord/D");
		TBranch * b_x2 = t_Tout->Branch("x2_coord",&x2_coord,"x2_coord/D");
		TBranch * b_y2 = t_Tout->Branch("y2_coord",&y2_coord,"y2_coord/D");
		TBranch * b_x3 = t_Tout->Branch("x3_coord",&x3_coord,"x3_coord/D");
		TBranch * b_y3 = t_Tout->Branch("y3_coord",&y3_coord,"y3_coord/D");
		TBranch * b_x4 = t_Tout->Branch("x4_coord",&x4_coord,"x4_coord/D");
		TBranch * b_y4 = t_Tout->Branch("y4_coord",&y4_coord,"y4_coord/D");
		TBranch * b_qx1 = t_Tout->Branch("qx1_coord",&qx1_coord,"qx1_coord/D");
		TBranch * b_qx2 = t_Tout->Branch("qx2_coord",&qx2_coord,"qx2_coord/D");
		TBranch * b_qy1 = t_Tout->Branch("qy1_coord",&qy1_coord,"qy1_coord/D");
		TBranch * b_qy2 = t_Tout->Branch("qy2_coord",&qy2_coord,"qy2_coord/D");
		TBranch * b_phi = t_Tout->Branch("phi",&phi,"phi/D");
		TBranch * b_theta = t_Tout->Branch("theta",&theta,"theta/D");
		TBranch * b_hadc0 = t_Tout->Branch("h_adc0",&h_adc0,"h_adc0/D");
		TBranch * b_hadc1 = t_Tout->Branch("h_adc1",&h_adc1,"h_adc1/D");
		TBranch * b_ladc0 = t_Tout->Branch("l_adc0",&l_adc0,"l_adc0/D");
		TBranch * b_ladc1 = t_Tout->Branch("l_adc1",&l_adc1,"l_adc1/D");	
	

	if (FixedZ && ProjectionOn)
	{
		cout << "Input Z position (m)" << endl;
		cin >> zproj; 
	}

	for (int ientry = 0; ientry < entries; ientry++)
	{
		t_Tin->GetEntry(ientry);
		if (tr > 0)
		{
			qevt_proj++;	
			if (ProjectionOn)
			{
				do 
				{
					if (!FixedZ && SameEntry == 0 && PromptUser)
					{
						cout << "Input Z position (m)" << endl;
						cin >> zproj;
					}
					xproj = tan(th)*(zproj - z0) + x0;		
					yproj = tan(ph)*(zproj - z0) + y0;
					if (Verbose)
					{
						cout << "Projected X position is " << xproj << endl;
						cout << "Projected Y position is " << yproj << endl;
					}
					//	cout << "x2 " << x2 << endl;
					//	cout << "y2 " << y2 << endl;
					//	cout << "xresid " << x2_resid << endl;
					//	cout << "yresid " << y2_resid << endl;
					//	do {cout << "Press any key to continue." << endl;} while (cin.get() != '\n');
					if (!FixedZ && PromptUser)
					{
						cout << "Type 0 to check another position, 1 to move to the next good track, or 2 to exit." << endl;
						cin >> SameEntry;
						if (SameEntry == 2)
						{
							cout << "Ending program..." << endl;
							return 0;
						}
					}
					else if (PromptUser)
					{
						cout << "Type 1 to move to the next good track or 2 to end early." << endl;	
						cin >> SameEntry;
						if (SameEntry == 2)
						{
							cout << "Ending program..." << endl;
							return 0;
						}
					}
					else {SameEntry = 1; continue;}
				} while (SameEntry == 0);				
				if (QuartzCheckOn && OutputFile)
				{
					QuartzHit = QuartzCheck(th,ph,x0,y0,z0,qx1_coord,qx2_coord,qy1_coord,qy2_coord);
					if (QuartzHit) 
					{
						qevt_verf++;
						x1_coord = x0;
						x2_coord = x1;
						x3_coord = x2;
						x4_coord = x3;
						y1_coord = y0;
						y2_coord = y1;
						y3_coord = y2;
						y4_coord = y3;
						phi = ph;
						theta = th;
						h_adc0 = hadc0;
						h_adc1 = hadc1;
						l_adc0 = ladc0;
						l_adc1 = ladc1;
						t_Tout->Fill();
					}	
				}
				else if (QuartzCheckOn && !OutputFile)
				{
					QuartzHit = QuartzCheck(th,ph,x0,y0,z0);
					if (QuartzHit) {qevt_verf++;}	
				}						
			}
			else if (QuartzCheckOn && OutputFile)
			{
				QuartzHit = QuartzCheck(th,ph,x0,y0,z0,qx1_coord,qx2_coord,qy1_coord,qy2_coord);
				if (QuartzHit) 
				{
					qevt_verf++;
					x1_coord = x0;
					x2_coord = x1;
					x3_coord = x2;
					x4_coord = x3;
					y1_coord = y0;
					y2_coord = y1;
					y3_coord = y2;
					y4_coord = y3;
					phi = ph;
					theta = th;
					h_adc0 = hadc0;
					h_adc1 = hadc1;
					l_adc0 = ladc0;
					l_adc1 = ladc1;
					t_Tout->Fill();
				}
			}
			else if (QuartzCheckOn && !OutputFile)
			{
				QuartzHit = QuartzCheck(th,ph,x0,y0,z0);
				if (QuartzHit) {qevt_verf++;}
			}
			else {cout << "Turn on some more flags! Ending program..." << endl; return 404;}
		}
	}
	cout << "Reached end of file." << endl;
	p_infile->Close();
	t_Tout->Write();
	p_outfile->Close();
	if (QuartzCheckOn)
	{
		q_efficiency = qevt_verf/qevt_proj;
		cout << "Quartz Detectors' Efficiency is " << q_efficiency << endl;
	}
	return 0;
}	
