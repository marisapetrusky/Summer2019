void EffvsVoltage()
{
	double voltage[3] = {3.7,3.75,4};
	double g0_37 = 115.0/137, g0_375 = 748.0/813, g0_4 = 1006.0/1056;
	double g1_37 = 118.0/163, g1_375 = 758.0/866, g1_4 = 1017.0/1071;
	double g2_37 = 120.0/129, g2_375 = 770./818, g2_4 = 1033.0/1076;
	double g3_37 = 99.0/143, g3_375 = 637.0/847, g3_4 = 824.0/1098;

	double gem0[3] = {g0_37,g0_375,g0_4};
	double gem1[3] = {g1_37,g1_375,g1_4};
	double gem2[3] = {g2_37,g2_375,g2_4};
	double gem3[3] = {g3_37,g3_375,g3_4};
	
	TGraph * g0 = new TGraph(3,voltage,gem0);
	TGraph * g1 = new TGraph(3,voltage,gem1);	
	TGraph * g2 = new TGraph(3,voltage,gem2);
	TGraph * g3 = new TGraph(3,voltage,gem3);
	
	g0->SetMarkerStyle(20);
	g1->SetMarkerStyle(20);
	g1->SetMarkerColor(2);
	g1->SetLineColor(2);
	g2->SetMarkerStyle(20);
	g2->SetMarkerColor(6);
	g2->SetLineColor(6);
	g3->SetMarkerStyle(20);
	g3->SetMarkerColor(4);
	g3->SetLineColor(4);

	TMultiGraph * mg = new TMultiGraph();
	mg->Add(g0,"LP");
	mg->Add(g1,"LP");
	mg->Add(g2,"LP");
	mg->Add(g3,"LP");

	TCanvas * c1 = new TCanvas("c1","c1",800,600);
	mg->Draw("a");
	mg->SetTitle("Absolute GEM Efficiencies versus Voltage (kV)");
	auto legend = new TLegend(0.1,0.9,0.3,0.7);
	legend->AddEntry(g0,"GEM0","p");
	legend->AddEntry(g1,"GEM1","p");
	legend->AddEntry(g2,"GEM2","p");
	legend->AddEntry(g3,"GEM3","p");
	legend->Draw("SAME");
	
}
