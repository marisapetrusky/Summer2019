void EffvsVoltage()
{
	double voltage[4] = {3.65,3.7,3.9,3.95};

	double gem0[4] = {0.906,0.939,0.949,0.9355};
	double gem1[4] = {0.93,0.945,0.983,0.965};
	double gem2[4] = {0.927,0.935,0.965,0.963};
	double gem3[4] = {0.739,0.775,0.798,0.803};
	
	TGraph * g0 = new TGraph(4,voltage,gem0);
	TGraph * g1 = new TGraph(4,voltage,gem1);	
	TGraph * g2 = new TGraph(4,voltage,gem2);
	TGraph * g3 = new TGraph(4,voltage,gem3);
	
	g0->SetMarkerStyle(20);
	g1->SetMarkerStyle(21);
	g1->SetMarkerColor(2);
	g1->SetLineColor(2);
	g2->SetMarkerStyle(22);
	g2->SetMarkerColor(8);
	g2->SetLineColor(8);
	g3->SetMarkerStyle(34);
	g3->SetMarkerColor(4);
	g3->SetLineColor(4);

	TMultiGraph * mg = new TMultiGraph();
	mg->Add(g0,"P");
	mg->Add(g1,"P");
	mg->Add(g2,"P");
	mg->Add(g3,"P");

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
