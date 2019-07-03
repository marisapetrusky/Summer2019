using namespace ROOT;

void BeamProfCOLZ()
{
	int runno;
	cout << "Enter run number" << endl;
	cin >> runno;

	TString s_in = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%d_-1_[0-9].root",runno);//verf.root",runno);
	//TFile * f_in = TFile::Open(s_in);
	//auto t_in = f_in->Get("T");
	//RDataFrame d("T",f_in);
	
	TChain * ch = new TChain("T");
	ch->Add(s_in.Data());
	
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);

	//TH2D * h_g1t = new TH2D("h_g1t","3Dpos Hit Map, GEM1",128,-0.07,0.07,64,-0.13,0.13);
	//h_g1t->SetTitle("3Dpos Hit Map, GEM1;Y-axis (m);X-axis (m)");
	//TH2D * h_g2t = new TH2D("h_g2t","3Dpos Hit Map, GEM2",128,-0.07,0.07,64,-0.13,0.13);
	//h_g2t->SetTitle("3Dpos Hit Map, GEM2;Y-axis (m);X-axis (m)");
	//TH2D * h_g3t = new TH2D("h_g3t","Hit Map, GEM3",128,-0.07,0.07,64,-0.13,0.13);
	//h_g3t->SetTitle("3Dpos Hit Map, GEM3;Y-axis (m);X-axis (m)");
	TH2D * h_g1 = new TH2D("h_g1","hit.pos Hit Map, GEM1",128,-0.07,0.07,64,-0.13,0.13);
	h_g1->SetTitle("hit.pos Hit Map, GEM1;Y-axis (m);X-axis (m)");
	TH2D * h_g2 = new TH2D("h_g2","hit.pos Hit Map, GEM2",128,-0.07,0.07,64,-0.13,0.13);
	h_g2->SetTitle("hit.pos Hit Map, GEM2;Y-axis (m);X-axis (m)");
	TH2D * h_g3 = new TH2D("h_g3","Hit Map, GEM3",128,-0.07,0.07,64,-0.13,0.13);
	h_g3->SetTitle("hit.pos Hit Map, GEM3;Y-axis (m);X-axis (m)");

	TCanvas * c1 = new TCanvas("c1","c1",800,600);
	ch->Draw("RGEM.rgems.x1.hit.pos:RGEM.rgems.y1.hit.pos >> h_g1","RGEM.tr.n > 0","COLZ");
	TCanvas * c2 = new TCanvas("c2","c2",800,600);
	ch->Draw("RGEM.rgems.x2.hit.pos:RGEM.rgems.y2.hit.pos >> h_g2","RGEM.tr.n > 0","COLZ");
	//ch->Draw("RGEM.rgems.x2.coord.pos:RGEM.rgems.y2.coord.pos >> h_g2","RGEM.tr.n > 0","SAME");
	TCanvas * c3 = new TCanvas("c3","c3",800,600);
	ch->Draw("RGEM.rgems.x3.hit.pos:RGEM.rgems.y3.hit.pos >> h_g3","RGEM.tr.n > 0","COLZ");
	//ch->Draw("RGEM.rgems.x3.coord.pos:RGEM.rgems.y3.coord.pos >> h_g3","RGEM.tr.n > 0","SAME");

	//auto h_g1 = d.Histo2D<double,double>({"h_g1","Beam Profile, GEM2",512,-0.1,0.1,256,-0.05,0.05},"x1_coordt","y1_coordt"); 	
	//auto h_g1 = d.Histo2D<double,double>({},"x1_coordt","y1_coordt"); 	
	//auto h_g2 = d.Histo2D({"h_g2","Beam Profile, GEM2",256u,-0.05,0.05,512u,-0.1,0.1},"x2_coordt","y2_coordt"); 	
	//auto h_g3 = d.Histo2D({"h_g3","Beam Profile, GEM3",256u,-0.05,0.05,512u,-0.1,0.1},"x3_coordt","y3_coordt");

	//cout << "X offset in GEM 2: " << x2off << endl;
	//cout << "Y offset in GEM 2: " << y2off << endl;
	//cout << "X offset in GEM 3: " << x3off << endl;
	//cout << "Y offset in GEM 3: " << y3off << endl;	
}

