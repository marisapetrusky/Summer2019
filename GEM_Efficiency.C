void GEM_Efficiency()
{
	// User Variables
	double resolution = 0.001;
	// Branch Variables
	double tr; 
	double x0_resid, x1_resid, x2_resid, x3_resid;
	long entries;
	// Calculated Variables
	double evt_proj[4] = {0,0,0,0}, evt_verf[4] = {0,0,0,0};
	double efficiency[4] = {0,0,0,0};
	
	for (int iplane = 0; iplane < 4; iplane++)
	{
		TString filename = Form("/home/marisa/rootfiles/test_416_plane%d.root",iplane);
		TFile * p_infile = TFile::Open(filename,"READ");
		TTree * t_T = (TTree*)p_infile->Get("T");
		entries = t_T->GetEntries();
		
		t_T->SetBranchAddress("prex.tr.n",&tr);
		t_T->SetBranchAddress("prex.gems.x1.coord.resid",&x0_resid);
		t_T->SetBranchAddress("prex.gems.x2.coord.resid",&x1_resid);
		t_T->SetBranchAddress("prex.gems.x3.coord.resid",&x2_resid);
		t_T->SetBranchAddress("prex.gems.x4.coord.resid",&x3_resid);
	
		for (int ientry = 0; ientry < entries; ientry++)
		{
			t_T->GetEntry(ientry);
			if (tr > 0)
			{
				evt_proj[iplane]++;
				if (iplane == 0 && abs(x0_resid) < resolution)
				{evt_verf[iplane]++;}
				else if (iplane == 1 && abs(x1_resid) < resolution)
				{evt_verf[iplane]++;}
				else if (iplane == 2 && abs(x2_resid) < resolution)
				{evt_verf[iplane]++;}
				else if (iplane == 3)
				{ 
					if (x3_resid < 0)
					{x3_resid = x3_resid*-1;}
					if (x3_resid < resolution)
					{evt_verf[iplane]++;}
				}
			}	
			else 
			{continue;}
		}
		cout << "Projected Events: " << evt_proj[iplane] << endl;
		cout << "Verified Events: " << evt_verf[iplane] << endl;
		efficiency[iplane] = evt_verf[iplane]/evt_proj[iplane];
		cout << "GEM" << iplane << " Efficiency: " << efficiency[iplane] << endl;
		p_infile->Close();
	}
}
