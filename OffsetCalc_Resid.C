using namespace ROOT;

void OffsetCalc_Resid()
{
	int runno[3] = {20862,20861,20863};
	int nofiles = 3;
	double dummy, x2off, y2off, x3off, y3off;

	//cout << "Enter run number" << endl;
	//cin >> runno;

	TString s_in;
	TChain * ch = new TChain("T");
	
	for (int ifile = 0; ifile < nofiles; ifile++)
	{
		if (runno[ifile] > 20000)
		{s_in = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%d_-1_[0-1].root",runno[ifile]);}
		else
		{s_in = Form("/chafs1/work1/prex_counting/marisa/LHRS/prexLHRS_%d_-1_[0-1].root",runno[ifile]);}

		ch->Add(s_in.Data());
	}
	
	TH1D * h_g2_x = new TH1D("h_g2_x","x2 - x1 for th < 0.0005",2000,-0.001,0.001);
	TH1D * h_g2_y = new TH1D("h_g2_y","y2 - y1 for ph < 0.0005",2000,-0.001,0.001);
	TH1D * h_g2res_x = new TH1D("h_g2res_x","RGEM.rgems.x2.coord.3Dresid",100,0.,0.);
	TH1D * h_g2res_y = new TH1D("h_g2res_y","RGEM.rgems.y2.coord.3Dresid",100,0.,0.);
	
	TCanvas * c2 = new TCanvas("c2","c2",800,600);
	c2->Divide(2,1);
	c2->cd(1);
	ch->Draw("RGEM.rgems.x2.coord.3Dpos - RGEM.rgems.x1.coord.3Dpos >> h_g2_x","RGEM.tr.n > 0 && fabs(RGEM.tr.th) < 0.005");
	dummy = h_g2_x->GetMaximumBin();
	x2off = h_g2_x->GetBinCenter(dummy);
	cout << "x2off = " << x2off << endl;
	c2->cd(2);
	ch->Draw("RGEM.rgems.y2.coord.3Dpos - RGEM.rgems.y1.coord.3Dpos >> h_g2_y","RGEM.tr.n > 0 && fabs(RGEM.tr.ph) <  0.005");
	dummy = h_g2_y->GetMaximumBin();
	y2off = h_g2_y->GetBinCenter(dummy);
	cout << "y2off = " << y2off << endl;

	TCanvas * c1 = new TCanvas("c1","c1",800,600);
	c1->Divide(2,1);
	c1->cd(1);
	ch->Draw("RGEM.rgems.x2.coord.3Dresid >> h_g2res_x","RGEM.tr.n > 0");
	c1->cd(2);
	ch->Draw("RGEM.rgems.y2.coord.3Dresid >> h_g2res_y","RGEM.tr.n > 0");


}
