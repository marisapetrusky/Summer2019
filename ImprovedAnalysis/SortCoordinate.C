void SortHit(double qx, double qy, double adc, double xup_bd[200], double yup_bd[200], int& tempx, int& tempy)
{
	//cout << "(qx,qy) = (" << qx << "," << qy << ")" << endl;
	if (qy >= 0) // Use q_map[][40-79]
	{
		for (int ix = 0; ix < 200; ix++)
		{
			if (qx < -0.2 || qx > 0.2){tempx = 999; break;}
			if (qx < xup_bd[ix]){tempx = ix; break;}
			else {continue;}
		}
		for (int iy = 100; iy < 200; iy++)
		{
			if (qy < -0.2 || qy > 0.2){tempy = 999; break;}
			if (qy < yup_bd[iy]){tempy = iy; break;}
			else {continue;}
		}
	}
	else if (qy < 0) // Use q_map[][0-39]
	{
		for (int ix = 0; ix < 200; ix++)
		{
			if (qx < -0.2 || qx > 0.2){tempx = 999; break;}
			if (qx < xup_bd[ix]){tempx = ix; break;}
			else {continue;}
		}
		for (int iy = 0; iy < 100; iy++)
		{
			if (qy < -0.2 || qy > 0.2){tempy = 999; break;}
			if (qy < yup_bd[iy]){tempy = iy; break;}
			else {continue;}
		}
	}
}

void SortCoordinate()
{
	// User Variables
	int runno = 2004;//21331;//2004;//2011;
	// Branch Variables
	double DSQx, USQx;
	double DSQy, USQy;
	double DSQadc, USQadc;
	double DSQpe, USQpe;
	double GDSQx, GUSQx;
	double GDSQy, GUSQy;
	double GDSQadc, GUSQadc, GDSQpe, GUSQpe;
	double DSQ_xsort, DSQ_ysort;
	double USQ_xsort, USQ_ysort;
	double GDSQ_xsort, GDSQ_ysort;
	double GUSQ_xsort, GUSQy_sort;
	long entries;
	long entries2;
	// Code Variables
	double DSQ_map[200][200]; // From left to right, and down to up
	double DSQ_count[200][200];
	double USQ_map[200][200]; // From left to right, and down to up
	double USQ_count[200][200];
	double xup_bd[200];// = {-0.013,-0.011,-.009,-0.007,-0.005,-0.003,-0.001,0.001,0.003,0.005,0.007,0.009,0.011,0.013,0.015};
	double xmid[200]; //= {-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014};
	double yup_bd[200];
	double ymid[200];
	double GDSQ_map[200][200];
	double GUSQ_map[200][200];
	double GDSQ_count[200][200];
	double GUSQ_count[200][200];
	int tempx, tempy;

	for (int iy = 0; iy < 200; iy++)
	{
		xup_bd[iy] = -0.198 + iy*0.002;
		xmid[iy] = -0.199 + iy*0.002;
		yup_bd[iy] = -0.198 + iy*0.002;
		ymid[iy] = -0.199 + iy*0.002;
		for (int ix = 0; ix < 200; ix++)
		{
			DSQ_map[ix][iy] = 0;
			USQ_map[ix][iy] = 0;
			DSQ_count[ix][iy] = 0;
			USQ_count[ix][iy] = 0;
			GDSQ_map[ix][iy] = 0;
			GUSQ_map[ix][iy] = 0;
			GDSQ_count[ix][iy] = 0;
			GUSQ_count[ix][iy] = 0;
		}
	}	

	// Histograms
	//gStyle->SetOptStat("nemruoi");
	TH2D * h_DSQ_avg = new TH2D("h_DSQ_avg","Mean ADC per 2mm^2, Downstream Quartz;Y-axis (m);X-axis (m)",200,-0.2,0.2,200,-0.2,0.2);//15,-0.015,0.015,80,-0.08,0.08);
	TH2D * h_USQ_avg = new TH2D("h_USQ_avg","Mean ADC per 2 mm^2, Upstream Quartz;Y-axis (m);X-axis (m)",200,-0.2,0.2,200,-0.2,0.2);//15,-0.015,0.015,80,-0.08,0.08);
	TH2D * h_DSQ_prof = new TH2D("h_DSQ_prof","Downstream Quartz Beam Profile;Y-axis (m);X-axis (m)",200,-0.2,0.2,200,-0.2,0.2);//15,-0.015,0.015,80,-0.08,0.08);
	TH2D * h_USQ_prof = new TH2D("h_USQ_prof","Upstream Quartz Beam Profile;Y-axis (m);X-axis (m)",200,-0.2,0.2,200,-0.2,0.2);//15,-0.015,0.015,80,-0.08,0.08);	
	TProfile * h_DSQ_xprofile = new TProfile("h_DSQ_x","Downstream Quartz PE vs Y-Position;Y-axis (m);Photoelectrons",30,-0.015,0.015);//,50,0,300);
	TProfile * h_USQ_xprofile = new TProfile("h_USQ_x","Upstream Quartz PE vs Y-Position;Y-axis (m);Photoelectrons",30,-0.015,0.015);//,50,0,300);
	TProfile * h_DSQ_yprofile = new TProfile("h_DSQ_y","Downstream Quartz PE vs X-Position;X-axis (m);Photoelectrons",80,-0.08,0.08);//,50,0,300);
	TProfile * h_USQ_yprofile = new TProfile("h_USQ_y","Upstream Quartz PE vs X-Position;X-axis (m);Photoelectrons",80,-0.08,0.08);//,50,0,300);

	TH2D * h_GDSQ_avg = new TH2D("h_GDSQ_avg","GEM Projected Mean ADC per 2mm^2, Downstream Quartz;Y-axis (m);X-axis (m)",200,-0.2,0.2,200,-0.2,0.2);//15,-0.015,0.015,80,-0.08,0.08);
	TH2D * h_GUSQ_avg = new TH2D("h_GUSQ_avg","GEM Projected Mean ADC per 2 mm^2, Upstream Quartz;Y-axis (m);X-axis (m)",200,-0.2,0.2,200,-0.2,0.2);//15,-0.015,0.015,80,-0.08,0.08);
	TH2D * h_GDSQ_prof = new TH2D("h_GDSQ_prof","GEM Projected Downstream Quartz Beam Profile;Y-axis (m);X-axis (m)",200,-0.2,0.2,200,-0.2,0.2);//15,-0.015,0.015,80,-0.08,0.08);
	TH2D * h_GUSQ_prof = new TH2D("h_GUSQ_prof","GEM Projected Upstream Quartz Beam Profile;Y-axis (m);X-axis (m)",200,-0.2,0.2,200,-0.2,0.2);//15,-0.015,0.015,80,-0.08,0.08);	

	TString s_infile = Form("Run%i_cuts.root",runno);
	TFile * p_infile = TFile::Open(s_infile,"READ");
	TTree * t_T = (TTree*)p_infile->Get("T");
	entries = t_T->GetEntries();
	t_T->SetBranchAddress("DSQx",&DSQx);
	t_T->SetBranchAddress("DSQy",&DSQy);
	t_T->SetBranchAddress("USQx",&USQx);
	t_T->SetBranchAddress("USQy",&USQy);
	t_T->SetBranchAddress("DSQadc",&DSQadc);
	t_T->SetBranchAddress("USQadc",&USQadc);
	t_T->SetBranchAddress("DSQpe",&DSQpe);
	t_T->SetBranchAddress("USQpe",&USQpe);
	
	/*TTree * t_T2 = (TTree*)p_infile->Get("T2");
	entries2 = t_T2->GetEntries();
	t_T2->SetBranchAddress("GDSQx",&GDSQx);
	t_T2->SetBranchAddress("GDSQy",&GDSQy);
	t_T2->SetBranchAddress("GUSQx",&GUSQx);
	t_T2->SetBranchAddress("GUSQy",&GUSQy);
	t_T2->SetBranchAddress("GDSQadc",&GDSQadc);
	t_T2->SetBranchAddress("GUSQadc",&GUSQadc);
	//t_T2->SetBranchAddress("GDSQpe",&GDSQpe);
	//t_T2->SetBranchAddress("GUSQpe",&GUSQpe);
	*/
	TString s_outfile = Form("Run%d_sorted.root",runno);
	TFile * p_outfile = TFile::Open(s_outfile,"RECREATE");
	TTree * t_Tnew = new TTree("Tnew","Tnew");
	TBranch * b_DSQ_xsort = t_Tnew->Branch("DSQ_xsort",&DSQ_xsort,"DSQ_xsort/D");
	TBranch * b_DSQ_ysort = t_Tnew->Branch("DSQ_ysort",&DSQ_ysort,"DSQ_ysort/D");
	TBranch * b_USQ_xsort = t_Tnew->Branch("USQ_xsort",&USQ_xsort,"USQ_xsort/D");
	TBranch * b_USQ_ysort = t_Tnew->Branch("USQ_ysort",&USQ_ysort,"USQ_ysort/D");	
	cout << "VDC entries: " << entries << endl;
	for (int ievt = 0; ievt < entries; ievt++)
	{
		t_T->GetEntry(ievt);

		//h_DSQ_xprofile->Fill(DSQx,DSQpe);	
		//h_DSQ_yprofile->Fill(DSQy,DSQpe);
		//h_USQ_xprofile->Fill(USQx,USQpe);
		//h_USQ_yprofile->Fill(USQy,USQpe);
		SortHit(DSQy,DSQx,DSQadc,yup_bd,xup_bd,tempy,tempx);
		if (tempx != 999 && tempy != 999)
		{
			if (DSQpe > 40) {h_DSQ_prof->Fill(DSQy,DSQx);}
			DSQ_map[tempy][tempx] = DSQ_map[tempy][tempx] + DSQadc; //adc;//DSQpe; 
			DSQ_count[tempy][tempx]++;
			DSQ_xsort = tempx;
			DSQ_ysort = tempy;
		}
		SortHit(USQy,USQx,USQadc,yup_bd,xup_bd,tempy,tempx);
		if (tempx != 999 && tempy != 999)
		{
			if (USQpe > 40) {h_USQ_prof->Fill(USQy,USQx);}
			USQ_map[tempy][tempx] = USQ_map[tempy][tempx] + USQadc; //adc;//USQpe; 
			USQ_count[tempy][tempx]++;
			USQ_xsort = tempx;
			USQ_ysort = tempy;
		}
		//cout << USQ_ysort << endl;
		t_Tnew->Fill();
	}

	for (int ix = 0; ix < 200; ix++)
	{	
		for (int iy = 0; iy < 200; iy++)
		{
			DSQ_map[iy][ix] = (DSQ_count[iy][ix] > 100)? DSQ_map[iy][ix]/DSQ_count[iy][ix] : 0;//DSQ_map[ix][iy];
			h_DSQ_avg->Fill(ymid[iy],xmid[ix],DSQ_map[iy][ix]);
			USQ_map[iy][ix] = (USQ_count[iy][ix] > 100)? USQ_map[iy][ix]/USQ_count[iy][ix] : 0;//USQ_map[ix][iy];
			h_USQ_avg->Fill(ymid[iy],xmid[ix],USQ_map[iy][ix]);
		}
	}
	cout << "GEM Entries: " << entries2 << endl;
	/*for (int ievt = 0; ievt < entries2; ievt++)
	{
		t_T2->GetEntry(ievt);
		h_GUSQ_prof->Fill(GUSQy,GUSQx);
		h_GDSQ_prof->Fill(GDSQy,GDSQx);
		
		//h_DSQ_xprofile->Fill(DSQx,DSQpe);	
		//h_DSQ_yprofile->Fill(DSQy,DSQpe);
		//h_USQ_xprofile->Fill(USQx,USQpe);
		//h_USQ_yprofile->Fill(USQy,USQpe);
		SortHit(GDSQy,GDSQx,GDSQadc,yup_bd,xup_bd,tempy,tempx);
		if (tempx != 999 && tempy != 999)
		{
			if (GDSQpe > 40) {h_GDSQ_prof->Fill(GDSQy,GDSQx);}
			GDSQ_map[tempy][tempx] = GDSQ_map[tempy][tempx] + GDSQadc; //adc;//DSQpe; 
			GDSQ_count[tempy][tempx]++;
			//GDSQ_xsort = tempx;
			//GDSQ_ysort = tempy;
		}
		SortHit(GUSQy,GUSQx,GUSQadc,yup_bd,xup_bd,tempy,tempx);
		if (tempx != 999 && tempy != 999)
		{
			if (GUSQpe > 40) {h_GUSQ_prof->Fill(GUSQy,GUSQx);}
			GUSQ_map[tempy][tempx] = GUSQ_map[tempy][tempx] + GUSQadc; //adc;//USQpe; 
			GUSQ_count[tempy][tempx]++;
		}
		//cout << USQ_ysort << endl;
	}

	for (int ix = 0; ix < 200; ix++)
	{	
		for (int iy = 0; iy < 200; iy++)
		{
			GDSQ_map[iy][ix] = (GDSQ_count[iy][ix] > 50)? GDSQ_map[iy][ix]/GDSQ_count[iy][ix] : 0;//DSQ_map[ix][iy];
			h_GDSQ_avg->Fill(ymid[iy],xmid[ix],GDSQ_map[iy][ix]);
			GUSQ_map[iy][ix] = (GUSQ_count[iy][ix] > 50)? GUSQ_map[iy][ix]/GUSQ_count[iy][ix] : 0;//USQ_map[ix][iy];
			//if (GUSQ_map[iy][ix] > 0) {cout << GUSQ_map[iy][ix];}
			h_GUSQ_avg->Fill(ymid[iy],xmid[ix],GUSQ_map[iy][ix]);
		}
	}
	*/
	gStyle->SetOptStat(0);
	h_USQ_avg->SetMinimum(55);	
	h_DSQ_avg->SetMinimum(35);
	//gStyle->SetPalette(kBlueRedYellow);	
	TCanvas * c1 = new TCanvas("Q1","Q1",1000,1000);
	//c1->Divide(2,1);
	//c1->cd(1);
	h_USQ_avg->Draw("COLZ");
	//c1->cd(2);
	TCanvas * c2 = new TCanvas("c2","c2",1000,1000);
	h_DSQ_avg->Draw("COLZ");
	TCanvas * cprof = new TCanvas("prof","prof",1000,1000);
	//cprof->Divide(2,1);
	//cprof->cd(1);
	h_USQ_prof->Draw("COLZ");
	//cprof->cd(2);
	TCanvas * c3 = new TCanvas("c3","c3",1000,1000);
	h_DSQ_prof->Draw("COLZ");
	/*TCanvas * c2 = new TCanvas("Q2","Q2",800,1000);
	  c2->Divide(2,1);
	  c2->cd(1);
	  TH1D * hx = h_USQ->ProjectionX();
	  hx->Draw();
	  c2->cd(2);
	  TH1D * hy = h_DSQ->ProjectionY();
	  hy->Draw();*/
	/*TCanvas * c3 = new TCanvas();
	  h_0_28->Draw();
	  TCanvas * c4 = new TCanvas();
	  h_5_28->Draw();
	  TCanvas * c5 = new TCanvas();
	  h_10_28->Draw();*/
	//t_T->Write();
	t_Tnew->Write();
	t_Tnew->Print();
	p_infile->Close();
}
