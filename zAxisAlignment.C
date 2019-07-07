using namespace ROOT;

void Transform(double& x, double& y, double& z);
//void FitLin(double x1, double x2, double x3, double& m, double& b);
//void Refit(double& x1, double& x2, double& x3, double m, double b);

void zAxisAlignment()
{
	int runno = 20862;
	double x1, x2, x3, y1, y2, y3, z1 = 0.684, z2 = 1.3698, z3 = 1.573;
	double x1p, x2p, x3p, y1p, y2p, y3p, z1p, z2p, z3p;
	//double xoff = 0.0, yoff = 0.0;
	double m, b;
	int GEMtr, VDCtr;

	TChain * ch = new TChain("T");
	TString s_in = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%i_-1_[*].root",runno);
	Int_t infiles = ch->Add(s_in.Data());
	ch->SetBranchAddress("RGEM.rgems.x1.coord.3Dpos",&x1);
	ch->SetBranchAddress("RGEM.rgems.x2.coord.3Dpos",&x2);
	ch->SetBranchAddress("RGEM.rgems.x3.coord.3Dpos",&x3);
	ch->SetBranchAddress("RGEM.rgems.y1.coord.3Dpos",&y1);
	ch->SetBranchAddress("RGEM.rgems.y2.coord.3Dpos",&y2);
	ch->SetBranchAddress("RGEM.rgems.y3.coord.3Dpos",&y3);
	ch->SetBranchAddress("RGEM.tr.n",&GEMtr);
	ch->SetBranchAddress("R.tr.n",&VDCtr);
	Int_t entries = ch->GetEntries();
	cout << "Entries = " << entries << " Number of Files = " << infiles << endl;
	TString s_out = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%d_transformed.root",runno);
	TFile * f_out = TFile::Open(s_out,"RECREATE");
	TTree * t_out = new TTree("T","T");
	TBranch * b_x1p = t_out->Branch("RGEM.x1",&x1p,"RGEM.x1/D");
	TBranch * b_x2p = t_out->Branch("RGEM.x2",&x2p,"RGEM.x2/D");
	TBranch * b_x3p = t_out->Branch("RGEM.x3",&x3p,"RGEM.x3/D");
	TBranch * b_y1p = t_out->Branch("RGEM.y1",&y1p,"RGEM.y1/D");
	TBranch * b_y2p = t_out->Branch("RGEM.y2",&y2p,"RGEM.y2/D");
	TBranch * b_y3p = t_out->Branch("RGEM.y3",&y3p,"RGEM.y3/D");

	for (int ievt = 0; ievt < entries; ievt++)
	{
		ch->GetEntry(ievt);
		if (GEMtr > 0)// && VDCtr > 0)
		{
			cout << "Event = " << ievt << endl;
			x1p = x1;
			x2p = x2;
			x3p = x3;
			y1p = y1;
			y2p = y2;
			y3p = y3;

			Transform(x1p,y1p,z1p);	
			Transform(x2p,y2p,z2p);
			Transform(x3p,y3p,z3p);
	
			t_out->Fill();
		}
	}
	t_out->Write();
	f_out->Close();
}

void Transform(double& x, double& y, double& z)
{
	double a = -0.006717;
	double b = -0.007317;

	x = cos(a)*x + sin(b)*sin(a)*y + sin(b)*cos(a)*z;
	y = cos(a)*y - sin(a)*y;
	z = -sin(b)*x + cos(b)*sin(a)*y + cos(b)*cos(a)*z; 
}
