void DependencyR()
{
	double DSQx, DSQy, USQx, USQy;
	double DSQpe, USQpe, DSQadc, USQadc;
	double entries;

	TProfile * h_DSQ_xprof = new TProfile("h_DSQ_xprof","Downstream Quartz ADC vs X-Position; X-axis (m); ADC",160,-0.08,0.08);
	h_DSQ_xprof->GetYaxis()->SetRange(20,150);
	TProfile * h_DSQ_yprof = new TProfile("h_DSQ_yprof","Downstream Quartz ADC vs Y-Position; Y-axis (m); ADC",60,-0.03,0.03);
	h_DSQ_yprof->GetYaxis()->SetRange(20,150);
	TProfile * h_USQ_xprof = new TProfile("h_USQ_xprof","Upstream Quartz ADC vs X-Position; X-axis (m); ADC",160,-0.08,0.08);
	h_USQ_xprof->GetYaxis()->SetRange(20,150);
	TProfile * h_USQ_yprof = new TProfile("h_USQ_yprof","Upstream Quartz ADC vs Y-Position; Y-axis (m); ADC",60,-0.03,0.03);
	h_USQ_yprof->GetYaxis()->SetRange(20,150);

	TFile * p_infile = TFile::Open("Run21331_cuts.root","READ");
	TTree * t_T = (TTree*)p_infile->Get("T");
	entries = t_T->GetEntries();
	t_T->SetBranchAddress("DSQx",&DSQx);
	t_T->SetBranchAddress("DSQy",&DSQy);
	t_T->SetBranchAddress("USQx",&USQx);
	t_T->SetBranchAddress("USQy",&USQy);
	t_T->SetBranchAddress("DSQpe",&DSQpe);
	t_T->SetBranchAddress("USQpe",&USQpe);
	t_T->SetBranchAddress("DSQadc",&DSQadc);
	t_T->SetBranchAddress("USQadc",&USQadc);
	
	for (int ievt = 0; ievt < entries; ievt++)
	{
		t_T->GetEntry(ievt);
		if (DSQpe < 200)//DSQpe > 40 && DSQpe < 150)
		{
			h_DSQ_xprof->Fill(DSQx,DSQadc);
			h_DSQ_yprof->Fill(DSQy,DSQadc);
		}
		if (USQpe < 200)//if (USQpe > 40 && USQpe < 150)
		{ 
			h_USQ_xprof->Fill(USQx,USQadc);
			h_USQ_yprof->Fill(USQy,USQadc);
		}
	}
	gStyle->SetOptFit(1);
	//cout << "DSQ X" << endl;
	//h_DSQ_xprof->Fit("pol1","","",-0.07,0.01);
	//cout << "DSQ Y" << endl;
	h_DSQ_yprof->Fit("pol0","","");//,-0.015,0.02);//,-0.02,0.01);
	//cout << "USQ X" << endl;
	//h_USQ_xprof->Fit("pol1","","",-0.07,0.01);
	//cout << "USQ Y" << endl;
	h_USQ_yprof->Fit("pol0","","");//,-0.015,0.02);//,-0.02,-0.01);
	
	TCanvas * c1 = new TCanvas();
	//c1->Divide(2,1);
//c1->cd(1);
	//h_DSQ_xprof->Draw();
	//c1->cd(2);
	TCanvas * c3 = new TCanvas();
	h_DSQ_yprof->Draw();
	
	TCanvas * c2 = new TCanvas();
	//c2->Divide(2,1);
	//c2->cd(1);
	//h_USQ_xprof->Draw();
	//c2->cd(2);
	TCanvas * c4 = new TCanvas();
	h_USQ_yprof->Draw();
	
}
