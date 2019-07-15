{
	gROOT->Reset();
	
	T->Draw("L.tr.th - LGEM.tr.th>>h_th(100,-0.1,0.1)","LGEM.tr.n > 0 && L.tr.n > 0");
	h_th = (TH1F*)gDirectory->Get("h_th");
	//h_th->SetLogy();

	T->Draw("L.tr.ph - LGEM.tr.ph>>h_ph(100,-0.2,0.2)","LGEM.tr.n > 0 && L.tr.n > 0");
	h_ph = (TH1F*)gDirectory->Get("h_ph");
	//h_ph->SetLogy();

	TCanvas * c1 = new TCanvas();
	h_th->Draw();
	
	TCanvas * c2 = new TCanvas();
	h_ph->Draw();
	
}
