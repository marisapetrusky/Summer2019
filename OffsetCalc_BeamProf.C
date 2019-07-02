using namespace ROOT;

void OffsetCalc_BeamProf()
{
	int runno;
	cout << "Enter run number" << endl;
	cin >> runno;

	TString s_in = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%d_[0-4].root",runno);//verf.root",runno);
	//TFile * f_in = TFile::Open(s_in);
	//auto t_in = f_in->Get("T");
	//RDataFrame d("T",f_in);
	
	TChain * ch = new TChain("T");
	ch->Add(s_in.Data());
	TH2D * h_g1 = new TH2D("test","test",128,-0.1,0.1,64,-0.05,0.05);
	ch->Draw("RGEM.rgems.x1.coord.pos:RGEM.rgems.y1.coord.pos >> test","RGEM.tr.n > 0","COLZ");//"x1_coordt:x2_coordt >> test","RGEM.tr.n > 0");
	//auto h_g1 = d.Histo2D<double,double>({"h_g1","Beam Profile, GEM2",512,-0.1,0.1,256,-0.05,0.05},"x1_coordt","y1_coordt"); 	
	//auto h_g1 = d.Histo2D<double,double>({},"x1_coordt","y1_coordt"); 	
	//auto h_g2 = d.Histo2D({"h_g2","Beam Profile, GEM2",256u,-0.05,0.05,512u,-0.1,0.1},"x2_coordt","y2_coordt"); 	
	//auto h_g3 = d.Histo2D({"h_g3","Beam Profile, GEM3",256u,-0.05,0.05,512u,-0.1,0.1},"x3_coordt","y3_coordt");
	
	
	//TCanvas * c1 = new TCanvas("c1","c1",800,600);
	//h_g1->Draw();
	//TCanvas * c2 = new TCanvas("c2","c2",800,600);
	//h_g2->Draw();
	//TCanvas * c3 = new TCanvas("c3","c3",800,600);
	//h_g3->Draw();

	//cout << "X offset in GEM 2: " << x2off << endl;
	//cout << "Y offset in GEM 2: " << y2off << endl;
	//cout << "X offset in GEM 3: " << x3off << endl;
	//cout << "Y offset in GEM 3: " << y3off << endl;	
}

