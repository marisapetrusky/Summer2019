using namespace ROOT;

void VDCvsGEMAngle()
{
	int runno = 20862;
	TChain * ch = new TChain("T");
	TString s_in; 

	s_in = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%d_-1_[*].root",runno);
	ch->Add(s_in.Data());
	
	TH1D * h_thg = new TH1D("h_thg","#theta Distribution (RGEM.tr.n > 0 && R.tr.n > 0)",100,0.,0.);
	TH1D * h_thv = new TH1D("h_thv","#theta Distribution (RGEM.tr.n > 0 && R.tr.n > 0)",100,-0.1,0.1);
	TH1D * h_phg = new TH1D("h_phg","#phi Distribution (RGEM.tr.n > 0 && R.tr.n > 0)",100,-0.1,0.1);
	TH1D * h_phv = new TH1D("h_phv","#phi Distribution (RGEM.tr.n > 0 && R.tr.n > 0)",100,-0.1,0.1);
	
	h_thv->SetLineColor(kRed);
	h_phv->SetLineColor(kRed);

	TCanvas * c1 = new TCanvas("c1","c1",800,600);
	c1->cd();
	ch->Draw("RGEM.tr.th >> h_thg","RGEM.tr.n > 0 && R.tr.n > 0");
	//ch->Draw("RGEM.tr.th >> h_thg");
	//TH1* h_thv = (TH1*)gDirectory->FindObject("h_thv");
	auto l_th = new TLegend(0.1,0.7,0.48,0.9);
   	//l_th->AddEntry(h_thg,"GEM Fitted #theta","l");
	//l_th->AddEntry(h_thv,"VDC Fitted #theta","l");
	//l_th->Draw("SAME");
	//h_thg->Draw("SAME");
	//h_thv->Draw("SAME");
	
	TCanvas * c2 = new TCanvas("c2","c2",800,600);
	c2->cd();
	ch->Draw("RGEM.tr.ph >> h_phg","RGEM.tr.n > 0 && R.tr.n > 0");
	ch->Draw("R.tr.ph >> h_phv","RGEM.tr.n > 0 && R.tr.n > 0","SAME");
	auto l_ph = new TLegend(0.1,0.7,0.48,0.9);
   	l_ph->AddEntry(h_phg,"GEM Fitted #phi","l");
	l_ph->AddEntry(h_phv,"VDC Fitted #phi","l");
	l_ph->Draw("SAME");	
}

