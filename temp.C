bool isBadTrack(double x)
{	
	double resolution = 1e-3;
	if (fabs(x) > resolution) 
	{return true;}
	else 
	{return false;}
}

void temp()
{
	// User Variables
	bool xdummy, ydummy;
	double placeholder;
	// Branch Variables
	double tr;
	double x0_resid, x1_resid, x2_resid, x3_resid;
	double y0_resid, y1_resid, y2_resid, y3_resid;
	long entries;
	// Calculated Variables
	double g0_proj=0, g1_proj=0, g2_proj=0, g3_proj=0;	
	double g0_bad=0, g1_bad=0, g2_bad=0, g3_bad=0;
	double g0x_bad=0, g1x_bad=0, g2x_bad=0, g3x_bad=0;
	double g0y_bad=0, g1y_bad=0, g2y_bad=0, g3y_bad=0;
	double g0_eff=0, g1_eff=0, g2_eff=0, g3_eff=0;
	
	TFile * p_infile_0 = TFile::Open("/home/marisa/rootfiles/test_416_plane0.root","READ");
	TTree * t_T0 = (TTree*)p_infile_0->Get("T");
	entries = t_T0->GetEntries();
	
	t_T0->SetBranchAddress("prex.tr.n",&tr);
	t_T0->SetBranchAddress("prex.gems.x1.coord.resid",&x0_resid);
	t_T0->SetBranchAddress("prex.gems.x2.coord.resid",&x1_resid);
	t_T0->SetBranchAddress("prex.gems.x3.coord.resid",&x2_resid);
	t_T0->SetBranchAddress("prex.gems.x4.coord.resid",&x3_resid);
	t_T0->SetBranchAddress("prex.gems.y1.coord.resid",&y0_resid);
	t_T0->SetBranchAddress("prex.gems.y2.coord.resid",&y1_resid);
	t_T0->SetBranchAddress("prex.gems.y3.coord.resid",&y2_resid);
	t_T0->SetBranchAddress("prex.gems.y4.coord.resid",&y3_resid);
	
	for (int ientry = 0; ientry < entries; ientry++)	
	{
		t_T0->GetEntry(ientry);
		
		if (tr > 0)
		{
			g0_proj++;
			xdummy = isBadTrack(x0_resid);
			ydummy = isBadTrack(y0_resid);
			if (xdummy)
			{g0x_bad++;}
			if (ydummy)
			{g0y_bad++;}
		}
	}
		
	if (g0x_bad > g0y_bad)
	{g0_bad = g0x_bad;}
	else 
	{g0_bad = g0y_bad;}
	
	cout << "Projected Events: " << g0_proj << endl;
	cout << "Bad Events: " << g0_bad << endl;
	g0_eff = 1 - g0_bad/g0_proj;
	
	cout << "GEM0 Eff = " << g0_eff << endl;
	p_infile_0->Close();
}
