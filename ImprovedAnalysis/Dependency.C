void Dependency()
{
	double DSQx, DSQy, USQx, USQy;
	double DSQpe, USQpe, DSQadc, USQadc;
	double entries;
	
	double GDSQx, GDSQy, GUSQx, GUSQy;
	double GDSQpe, GUSQpe, GDSQadc, GUSQadc;
	double entries2;

	TProfile * h_DSQ_xprof = new TProfile("h_DSQ_xprof","Downstream Quartz ADC vs X-Position; X-axis (m); ADC",160,-0.08,0.08);
	h_DSQ_xprof->GetYaxis()->SetRange(20,150);
	TProfile * h_DSQ_yprof = new TProfile("h_DSQ_yprof","Downstream Quartz ADC vs Y-Position; Y-axis (m); ADC",50,-0.05,0.00);//50,-0.04,-0.01);
	h_DSQ_yprof->GetYaxis()->SetRange(20,150);
	TProfile * h_USQ_xprof = new TProfile("h_USQ_xprof","Upstream Quartz ADC vs X-Position; X-axis (m); ADC",160,-0.08,0.08);
	h_USQ_xprof->GetYaxis()->SetRange(20,150);
	TProfile * h_USQ_yprof = new TProfile("h_USQ_yprof","Upstream Quartz ADC vs Y-Position; Y-axis (m); ADC",50,-0.05,0.00);//50,-0.04,-0.01);
	h_USQ_yprof->GetYaxis()->SetRange(20,150);

	TProfile * h_GDSQ_xprof = new TProfile("h_GDSQ_xprof","GEM Projected Downstream Quartz ADC vs X-Position; X-axis (m); ADC",40,-0.08,0.08);//160,-0.08,0.08);
	h_GDSQ_xprof->GetYaxis()->SetRange(20,150);
	TProfile * h_GDSQ_yprof = new TProfile("h_GDSQ_yprof","GEM Projected Downstream Quartz ADC vs Y-Position; Y-axis (m); ADC",10,-0.04,-0.01);//50,-0.04,-0.01);
	h_GDSQ_yprof->GetYaxis()->SetRange(20,150);
	TProfile * h_GUSQ_xprof = new TProfile("h_GUSQ_xprof","GEM Projected Upstream Quartz ADC vs X-Position; X-axis (m); ADC",40,-0.08,0.08);//160,-0.08,0.08);
	h_GUSQ_xprof->GetYaxis()->SetRange(20,150);
	TProfile * h_GUSQ_yprof = new TProfile("h_GUSQ_yprof","GEM Projected Upstream Quartz ADC vs Y-Position; Y-axis (m); ADC",10,-0.04,-0.01);//50,-0.04,-0.01);//50,-0.04,-0.01);
	h_GUSQ_yprof->GetYaxis()->SetRange(20,150);
	
	TFile * p_infile = TFile::Open("Run2011_cuts.root","READ");
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

	TTree * t_T2 = (TTree*)p_infile->Get("T2");
	entries2 = t_T2->GetEntries();
	t_T2->SetBranchAddress("GDSQx",&GDSQx);
	t_T2->SetBranchAddress("GDSQy",&GDSQy);
	t_T2->SetBranchAddress("GUSQx",&GUSQx);
	t_T2->SetBranchAddress("GUSQy",&GUSQy);
	t_T2->SetBranchAddress("GDSQpe",&GDSQpe);
	t_T2->SetBranchAddress("GUSQpe",&GUSQpe);
	t_T2->SetBranchAddress("GDSQadc",&GDSQadc);
	t_T2->SetBranchAddress("GUSQadc",&GUSQadc);	
	
	double xbin[160];
	double ybin[50];
	double DSQ_xadc[160], USQ_xadc[160];
	double DSQ_yadc[50], USQ_yadc[50];

	double gxbin[160];
	double gybin[50];
	double GDSQ_xadc[160], GUSQ_xadc[160];
	double GDSQ_yadc[50], GUSQ_yadc[50]; 
	
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

	for (int ievt = 0; ievt < entries2; ievt++)
	{
		t_T2->GetEntry(ievt);
		if (GDSQadc < 200)//DSQpe > 40 && DSQpe < 150)
		{
			h_GDSQ_xprof->Fill(GDSQx,GDSQadc);
			h_GDSQ_yprof->Fill(GDSQy,GDSQadc);
		}
		if (GUSQadc < 200)//if (USQpe > 40 && USQpe < 150)
		{ 
			h_GUSQ_xprof->Fill(GUSQx,GUSQadc);
			h_GUSQ_yprof->Fill(GUSQy,GUSQadc);
		}
	}

	for (int ixbin = 0; ixbin < 160; ixbin++)
	{
		xbin[ixbin] = -0.079 + ixbin*0.001;
		DSQ_xadc[ixbin] = h_DSQ_xprof->GetBinContent(ixbin);
		USQ_xadc[ixbin] = h_USQ_xprof->GetBinContent(ixbin);
	}
	for (int iybin = 0; iybin < 50; iybin++)
	{
		ybin[iybin] = -0.039 + iybin*0.001; 
		DSQ_yadc[iybin] = h_DSQ_yprof->GetBinContent(iybin);
		//cout << DSQ_yadc[iybin] << endl;
		USQ_yadc[iybin] = h_USQ_yprof->GetBinContent(iybin);
	}

	for (int ixbin = 0; ixbin < 160; ixbin++)
	{
		gxbin[ixbin] = -0.079 + ixbin*0.001;
		GDSQ_xadc[ixbin] = h_GDSQ_xprof->GetBinContent(ixbin);
		GUSQ_xadc[ixbin] = h_GUSQ_xprof->GetBinContent(ixbin);
	}
	for (int iybin = 0; iybin < 50; iybin++)
	{
		gybin[iybin] = -0.039 + iybin*0.001; 
		GDSQ_yadc[iybin] = h_GDSQ_yprof->GetBinContent(iybin);
		//cout << DSQ_yadc[iybin] << endl;
		GUSQ_yadc[iybin] = h_GUSQ_yprof->GetBinContent(iybin);
	}

	TGraph * g_DSQ_x = new TGraph(160,xbin,DSQ_xadc);
	TGraph * g_DSQ_y = new TGraph(50,ybin,DSQ_yadc);
	TGraph * g_USQ_x = new TGraph(160,xbin,USQ_xadc);
	TGraph * g_USQ_y = new TGraph(50,ybin,USQ_yadc);
	g_DSQ_x->SetTitle("Downstream Quartz ADC vs X-Position; X-axis (m); ADC");
	g_DSQ_y->SetTitle("Downstream Quartz ADC vs Y-Position; Y-axis (m); ADC");
	g_USQ_x->SetTitle("Upstream Quartz ADC vs X-Position; X-axis (m); ADC");
	g_USQ_y->SetTitle("Upstream Quartz ADC vs Y-Position; Y-axis (m); ADC");

	TGraph * g_GDSQ_x = new TGraph(160,gxbin,GDSQ_xadc);
	TGraph * g_GDSQ_y = new TGraph(50,gybin,GDSQ_yadc);
	TGraph * g_GUSQ_x = new TGraph(160,gxbin,GUSQ_xadc);
	TGraph * g_GUSQ_y = new TGraph(50,gybin,GUSQ_yadc);
	g_GDSQ_x->SetTitle("GEM Projected Downstream Quartz ADC vs X-Position; X-axis (m); ADC");
	g_GDSQ_y->SetTitle("GEM Projected Downstream Quartz ADC vs Y-Position; Y-axis (m); ADC");
	g_GUSQ_x->SetTitle("GEM Projected Upstream Quartz ADC vs X-Position; X-axis (m); ADC");
	g_GUSQ_y->SetTitle("GEM Projected Upstream Quartz ADC vs Y-Position; Y-axis (m); ADC");
	
	gStyle->SetOptFit(1);
	//cout << "DSQ X" << endl;
	//h_DSQ_xprof->Fit("pol1","","",-0.07,0.005);
	//cout << "DSQ Y" << endl;
	//h_DSQ_yprof->Fit("pol2","","",-0.05,0);//-0.04,-0.01);
	//cout << "USQ X" << endl;
	//h_USQ_xprof->Fit("pol1","","",-0.07,0.005);
	//cout << "USQ Y" << endl;
	//h_USQ_yprof->Fit("pol2","","",-0.05,0);//-0.038,-0.008);
	
	//g_DSQ_x->Fit("pol1","","",-0.07,0.01);
	//g_DSQ_y->Fit("pol2");//,"","",-0.04,-0.01);
	//g_USQ_x->Fit("pol1","","",-0.07,0.01);
	//g_USQ_y->Fit("pol2");//,"","",-0.038,-0.008);	

	//g_GDSQ_x->Fit("pol1","","",-0.07,-0.02);
	//g_GDSQ_y->Fit("pol2");//,"","",-0.04,-0.01);
	//g_GUSQ_x->Fit("pol1","","",-0.07,-0.02);
	//g_GUSQ_y->Fit("pol2");//,"","",-0.038,-0.008);
	
	//TCanvas * c1 = new TCanvas();
	//h_DSQ_xprof->Draw("P");

	TCanvas * c3 = new TCanvas();
	h_DSQ_yprof->Draw("P");
	
	//TCanvas * c2 = new TCanvas();
	//h_USQ_xprof->Draw("P");

	TCanvas * c4 = new TCanvas();
	h_USQ_yprof->Draw("P");
	
	//g_DSQ_x->SetMarkerStyle(5);
	//g_DSQ_y->SetMarkerStyle(5);
	//g_USQ_x->SetMarkerStyle(5);
	//g_USQ_y->SetMarkerStyle(5);

	//g_GDSQ_x->SetMarkerStyle(5);
	//g_GDSQ_y->SetMarkerStyle(5);
	//g_GUSQ_x->SetMarkerStyle(5);
	//g_GUSQ_y->SetMarkerStyle(5);

	//TCanvas * c5 = new TCanvas();
	//g_DSQ_x->Draw("AP");
	//	
	//TCanvas * c6 = new TCanvas();
	//g_DSQ_y->Draw("AP");
	//
	//TCanvas * c7 = new TCanvas();
	//g_USQ_x->Draw("AP");
	//
	//TCanvas * c8 = new TCanvas();
	//g_USQ_y->Draw("AP");
}
