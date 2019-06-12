bool res_bad(double x, double res)
{
	if (x < 0)
	{x = -1*x;}
	if (x > res)
	{return true;}
	else
	{return false;}		
}

void GEM_Efficiency()
{
	// User Variables
	double resolution = 0.001;
	// Branch Variables
	double tr; 
	double x0_resid = 0, x1_resid = 0, x2_resid = 0, x3_resid = 0;
	long entries;
	// Calculated Variables
	double evt_proj[4] = {0,0,0,0}, evt_verf[4] = {0,0,0,0};
	double efficiency[4] = {0,0,0,0};
	
	for (int iplane = 0; iplane < 4; iplane++)
	{
		TString filename = Form("/home/marisa/rootfiles/test_416_plane%d.root",iplane);
		TFile * p_infile = TFile::Open(filename,"READ");
		TTree * t_T = (TTree*)p_infile->Get("T");
		entries = 5000;//t_T->GetEntries();
		
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
				if (iplane == 0 && res_bad(x0_resid,resolution))
				{	//cout << "x0_resid = " << x0_resid << endl;
					evt_verf[0] = evt_verf[0] + 1;}
				if (iplane == 1 && res_bad(x1_resid,resolution))
				{	//cout << "x1_resid = " << x1_resid << endl;
					evt_verf[1] = evt_verf[1] + 1;}
				if (iplane == 2 && res_bad(x2_resid,resolution))
				{	//cout << "x2_resid = " << x2_resid << endl;
					evt_verf[2] = evt_verf[2] + 1;}
				if (iplane == 3 && res_bad(x3_resid,resolution))
				{	//cout << "x3_resid = " << x3_resid << endl;
					evt_verf[3] = evt_verf[3] + 1;}
			}	
		}
		cout << "Projected Events: " << evt_proj[iplane] << endl;
		cout << "Bad Events: " << evt_verf[iplane] << endl;
		efficiency[iplane] = 1 - evt_verf[iplane]/evt_proj[iplane];
		cout << "GEM" << iplane << " Efficiency: " << efficiency[iplane] << endl;
		p_infile->Close();
	}
}
