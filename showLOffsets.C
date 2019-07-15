{
	gROOT->Reset();
	
	T->Draw("VDC.th - LGEM.th>>h_th(100,-0.1,0.1)");
	h_th = (TH1F*)gDirectory->Get("h_th");
	//h_th->SetLogy();

	T->Draw("VDC.ph - LGEM.ph>>h_ph(100,-0.2,0.2)");
	h_ph = (TH1F*)gDirectory->Get("h_ph");
	//h_ph->SetLogy();

	T->Draw("LVDC.x1 - LGEM.x1_3D:LVDC.y1 - LGEM.y1_3D>>h_g1(100,-0.1,0.1,100,-0.08,0.08)");
	h_g1 = (TH2F*)gDirectory->Get("h_g1");
	
	T->Draw("LVDC.x2 - LGEM.x2_3D:LVDC.y2 - LGEM.y2_3D>>h_g2(100,-0.1,0.1,100,-0.08,0.08)");
	h_g2 = (TH2F*)gDirectory->Get("h_g2");
	
	T->Draw("LVDC.x3 - LGEM.x3_3D:LVDC.y3 - LGEM.y3_3D>>h_g3(100,-0.1,0.1,100,-0.08,0.08)");
	h_g3 = (TH2F*)gDirectory->Get("h_g3");
	
	T->Draw("LGEM.x1_3D - LGEM.x1 >> h_x1(100,-0.02,0.02");
	h_x1 = (TH1F*)gDirectory->Get("h_x1");

	T->Draw("LGEM.x2_3D - LGEM.x2 >> h_x2(100,-0.02,0.02");
	h_x2 = (TH1F*)gDirectory->Get("h_x2");	

	T->Draw("LGEM.x3_3D - LGEM.x3 >> h_x3(100,-0.02,0.02");
	h_x3 = (TH1F*)gDirectory->Get("h_x3");	

	T->Draw("LGEM.y1_3D - LGEM.y1 >> h_y1(100,-0.01,0.01");
	h_y1 = (TH1F*)gDirectory->Get("h_y1");

	T->Draw("LGEM.x2_3D - LGEM.x2 >> h_y2(100,-0.01,0.01");
	h_y2 = (TH1F*)gDirectory->Get("h_y2");	

	T->Draw("LGEM.x3_3D - LGEM.x3 >> h_y3(100,-0.01,0.01");
	h_y3 = (TH1F*)gDirectory->Get("h_y3");	
	
	TCanvas * c2 = new TCanvas();
	c2->Divide(2,1);
	c2->cd(1);
	h_th->Draw();
	c2->cd(2);
	h_ph->Draw();

	TCanvas * c3 = new TCanvas();
	h_g1->Draw("COLZ");	

	TCanvas * c4 = new TCanvas();
	h_g2->Draw("COLZ");
		
	TCanvas * c5 = new TCanvas();
	h_g3->Draw("COLZ");

	TCanvas * c6 = new TCanvas();
	c6->Divide(2,1);
	c6->cd(1);
	h_x1->Draw();
	c6->cd(2);
	h_y1->Draw();
	
	TCanvas * c7 = new TCanvas();
	c7->Divide(2,1);
	c7->cd(1);
	h_x2->Draw();
	c7->cd(2);
	h_y2->Draw();
	
	TCanvas * c8 = new TCanvas();
	c8->Divide(2,1);
	c8->cd(1);
	h_x3->Draw();
	c8->cd(2);
	h_y3->Draw();	
}
