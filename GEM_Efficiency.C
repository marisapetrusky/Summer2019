// Marisa Petrusky
// Edit TString filename (Line 29) to change run number
// Edit value of planes (Line 72) to change number of GEMs to check

bool isBadTrack(double x)
{	
	double resolution = 1e-3;
	if (fabs(x) > resolution) 
	{return true;}
	else 
	{return false;}
}

void PlaneCheck(int iplane)
{
	// User Variables
	bool xdummy, ydummy;
	// Branch Variables
	double tr;
	double x_resid;
	double y_resid;
	long entries;
	// Calculated Variables
	double evt_proj = 0;	
	double evt_bad = 0;
	double evtx_bad = 0;
	double evty_bad = 0;
	double efficiency = 0;
	
	TString filename = Form("/home/marisa/rootfiles/test_417_plane%d.root",iplane);
	TFile * p_infile = TFile::Open(filename,"READ");
	TTree * t_T = (TTree*)p_infile->Get("T");
	entries = t_T->GetEntries();
	
	t_T->SetBranchAddress("prex.tr.n",&tr);
	TString xbranch = Form("prex.gems.x%d.coord.resid",iplane);
	t_T->SetBranchAddress(xbranch,&x_resid);
	TString ybranch = Form("prex.gems.y%d.coord.resid",iplane);
	t_T->SetBranchAddress(ybranch,&y_resid);

	for (int ientry = 0; ientry < entries; ientry++)	
	{
		t_T->GetEntry(ientry);
		
		if (tr > 0)
		{
			evt_proj++;
			xdummy = isBadTrack(x_resid);
			ydummy = isBadTrack(y_resid);
			if (xdummy)
			{evtx_bad++;}
			if (ydummy)
			{evty_bad++;}
		}
	}
		
	if (evtx_bad > evty_bad)
	{evt_bad = evtx_bad;}
	else 
	{evt_bad = evty_bad;}
	
	cout << "Projected Events: " << evt_proj << endl;
	cout << "Bad Events: " << evt_bad << endl;
	efficiency = 1 - evt_bad/evt_proj;
	
	cout << "GEM Efficiency = " << efficiency << endl;
	p_infile->Close();
}

void GEM_Efficiency()
{
	int planes = 4;
	for (int iplane = 1; iplane <= planes; iplane++)
	{
		cout << "Checking GEM" << iplane << "..." << endl;
		PlaneCheck(iplane);
	}
	
}
