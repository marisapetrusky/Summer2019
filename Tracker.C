bool QuartzCheck(double th, double ph, double x0, double y0, double z0)
{
	bool Verbose = 0; // Decide if you want output messages displayed
	double q_xproj[2], q_yproj[2];
	double q_xmax = 0.015;
	double q_ymax = 0.045;
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

int Tracker()
{
	// User Variables 
	bool ProjectionOn = 1; // Set TRUE if you'd like to input Z positions and output X and Y positions
	bool QuartzCheckOn = 1; // Set TRUE if you'd like to check if the track hit the quartz detectors
	bool FixedZ = 0; // Set TRUE if only checking one z spot, set FALSE if different z position per entry
	bool PromptUser = 0; // Set TRUE if you want prompts to go through good tracks one by one
	bool Verbose = 0; // Set TRUE if you want projected positions displayed each time
	// Branch Variables
	long entries; 
	double tr; 
	double x0, y0, z0 = 0; // Decide reference plane and edit height
	//double x2, y2, z2, x2_resid, y2_resid;
	double th, ph;
	double xproj, yproj, zproj;
	// Calculated Variables
	double qevt_proj = 0, qevt_verf = 0;
	double q_efficiency; 
	// For Code
	int run;	
	int SameEntry = 0; 
	bool QuartzHit;

	cout << "Enter run number" << endl;
	cin >> run;

	TString filename = Form("/home/marisa/rootfiles/test_%d.root",run);
	TFile * p_infile = TFile::Open(filename,"READ");
	TTree * t_T = (TTree*)p_infile->Get("T");

	t_T->SetBranchAddress("prex.tr.n",&tr);
	t_T->SetBranchAddress("prex.gems.x1.coord.3Dpos",&x0);
	t_T->SetBranchAddress("prex.gems.y1.coord.3Dpos",&y0);
	//t_T->SetBranchAddress("prex.gems.x2.coord.3Dpos",&x2);
	//t_T->SetBranchAddress("prex.gems.y2.coord.3Dpos",&y2);
	//t_T->SetBranchAddress("prex.gems.x2.coord.resid",&x2_resid);
	//t_T->SetBranchAddress("prex.gems.y2.coord.resid",&y2_resid);
	t_T->SetBranchAddress("prex.tr.ph",&ph);
	t_T->SetBranchAddress("prex.tr.th",&th);
	entries = t_T->GetEntries();

	if (FixedZ && ProjectionOn)
	{
		cout << "Input Z position (m)" << endl;
		cin >> zproj; 
	}

	for (int ientry = 0; ientry < entries; ientry++)
	{
		t_T->GetEntry(ientry);
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
				if (QuartzCheckOn)
				{
					QuartzHit = QuartzCheck(th,ph,x0,y0,z0);
					if (QuartzHit) {qevt_verf++;}	
				}						
			}
			else if (QuartzCheckOn)
			{
				QuartzHit = QuartzCheck(th,ph,x0,y0,z0);
				if (QuartzHit) {qevt_verf++;}
			}
			else {cout << "Turn on some more flags! Ending program..." << endl; return 404;}
		}
	}
	cout << "Reached end of file." << endl;
	if (QuartzCheckOn)
	{
		q_efficiency = qevt_verf/qevt_proj;
		cout << "Quartz Detectors' Efficiency is " << q_efficiency << endl;
	}
	return 0;
}	
