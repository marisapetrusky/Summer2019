void SortHit(double qx, double qy, double adc, double xup_bd[15], double yup_bd[80], int& tempx, int& tempy)
{
	//cout << "(qx,qy) = (" << qx << "," << qy << ")" << endl;
	if (qy >= 0) // Use q_map[][40-79]
	{
		for (int ix = 0; ix < 15; ix++)
		{
			if (qx < xup_bd[ix]){tempx = ix; break;}
			else {continue;}
		}
		for (int iy = 40; iy < 79; iy++)
		{
			if (qy < yup_bd[iy]){tempy = iy; break;}
			else {continue;}
		}
	}
	else if (qy < 0) // Use q_map[][0-39]
	{
		for (int ix = 0; ix < 15; ix++)
		{
			if (qx < xup_bd[ix]){tempx = ix; break;}
			else {continue;}
		}
		for (int iy = 0; iy < 39; iy++)
		{
			if (qy < yup_bd[iy]){tempy = iy; break;}
			else {continue;}
		}
	}
}

void QuartzMap_TH2D_avgadc()
{
	// User Variables
	int runs[9] = {427,430,432,438,439,440,441,442,444};
	int noruns = 9;
	// Branch Variables
	double x1, x2, x3, x4;
	double y1, y2, y3, y4;
	double qx1, qx2;
	double qy1, qy2;
	double ph, th;
	double hadc0, hadc1, ladc0, ladc1;
	long entries;
	double pedestal_l[2] = {1166,1067};
	double pedestal_h[2] = {148,135};
	// Code Variables
	double q1_map_l[15][80]; // From left to right, and down to up
	double q1_count_l[15][80];
	double q2_map_l[15][80];
	double q2_count_l[15][80];
	double q1_map_h[15][80]; // From left to right, and down to up
	double q1_count_h[15][80];
	double q2_map_h[15][80];
	double q2_count_h[15][80];
	double xup_bd[15] = {-0.013,-0.011,-.009,-0.007,-0.005,-0.003,-0.001,0.001,0.003,0.005,0.007,0.009,0.011,0.013,0.015};
	double xmid[15] = {-0.014,-0.012,-0.01,-0.008,-0.006,-0.004,-0.002,0,0.002,0.004,0.006,0.008,0.01,0.012,0.014};
	double yup_bd[80];
	double ymid[80];

	for (int iy = 0; iy < 80; iy++)
	{
		yup_bd[iy] = -0.078 + iy*0.002;
		ymid[iy] = -0.079 + iy*0.002;
		//cout << "ymid = " << ymid[iy] << endl;
		for (int ix = 0; ix < 15; ix++)
		{
			q1_map_l[ix][iy] = 0;
			q2_map_l[ix][iy] = 0;
			q1_map_h[ix][iy] = 0;
			q2_map_h[ix][iy] = 0;
			q1_count_l[ix][iy] = 0;
			q2_count_l[ix][iy] = 0;
			q1_count_h[ix][iy] = 0;
			q2_count_h[ix][iy] = 0;
		}
	}	
	int tempx, tempy;

	// Histograms
	//gStyle->SetOptStat("nemruoi");
	TH2D * h_q1_l = new TH2D("h_q1_l","Quartz 1 Map, Low Resolution",15,-0.015,0.015,80,-0.08,0.08);
	h_q1_l->GetXaxis()->SetTitle("X-axis (3 cm long)");
	h_q1_l->GetYaxis()->SetTitle("Y-axis (16 cm long)");
	TH2D * h_q2_l= new TH2D("h_q2_l","Quartz 2 Map, Low Resolution",15,-0.015,0.015,80,-0.08,0.08);
	h_q2_l->GetXaxis()->SetTitle("X-axis (3 cm long)");
	h_q2_l->GetYaxis()->SetTitle("Y-axis (16 cm long)");
	TH2D * h_q1_h = new TH2D("h_q1_h","Quartz 1 Map, High Resolution",15,-0.015,0.015,80,-0.08,0.08);
	h_q1_h->GetXaxis()->SetTitle("X-axis (3 cm long)");
	h_q1_h->GetYaxis()->SetTitle("Y-axis (16 cm long)");
	TH2D * h_q2_h = new TH2D("h_q2_h","Quartz 2 Map, High Resolution",15,-0.015,0.015,80,-0.08,0.08);
	h_q2_h->GetXaxis()->SetTitle("X-axis (3 cm long)");
	h_q2_h->GetYaxis()->SetTitle("Y-axis (16 cm long)");

	//cout << "Enter run number" << endl;
	//cin >> run;

	for (int irun = 0; irun < noruns; irun++)
	{
		cout << "Processing Run " << runs[irun] << endl;

		TString s_infile = Form("/home/marisa/rootfiles/test_%d_verf.root",runs[irun]);
		TFile * p_infile = TFile::Open(s_infile,"READ");
		TTree * t_T = (TTree*)p_infile->Get("T");
		entries = t_T->GetEntries();
		t_T->SetBranchAddress("x1_coord",&x1);
		t_T->SetBranchAddress("x2_coord",&x2);
		t_T->SetBranchAddress("x3_coord",&x3);
		t_T->SetBranchAddress("x4_coord",&x4);
		t_T->SetBranchAddress("y1_coord",&y1);
		t_T->SetBranchAddress("y2_coord",&y2);
		t_T->SetBranchAddress("y3_coord",&y3);
		t_T->SetBranchAddress("y4_coord",&y4);
		t_T->SetBranchAddress("qx1_coord",&qx1);
		t_T->SetBranchAddress("qx2_coord",&qx2);
		t_T->SetBranchAddress("qy1_coord",&qy1);
		t_T->SetBranchAddress("qy2_coord",&qy2);
		t_T->SetBranchAddress("phi",&ph);
		t_T->SetBranchAddress("theta",&th);
		t_T->SetBranchAddress("h_adc0",&hadc0);
		t_T->SetBranchAddress("h_adc1",&hadc1);
		t_T->SetBranchAddress("l_adc0",&ladc0);
		t_T->SetBranchAddress("l_adc1",&ladc1);

		for (int ievt = 0; ievt < entries; ievt++)
		{
			t_T->GetEntry(ievt);
			//cout << qx1 << endl;
			if (ladc0 > pedestal_l[0] && ladc1 > pedestal_l[1])
			{
				SortHit(qx1,qy1,ladc0,xup_bd,yup_bd,tempx,tempy);
				q1_map_l[tempx][tempy] = q1_map_l[tempx][tempy] + ladc0;
				q1_count_l[tempx][tempy]++;
				SortHit(qx2,qy2,ladc1,xup_bd,yup_bd,tempx,tempy);
				q2_map_l[tempx][tempy] = q2_map_l[tempx][tempy] + ladc1;
				q2_count_l[tempx][tempy]++;
			}
			if (hadc0 > pedestal_h[0] && hadc1 > pedestal_h[1])
			{
				SortHit(qx1,qy1,hadc0,xup_bd,yup_bd,tempx,tempy);
				q1_map_h[tempx][tempy] = q1_map_h[tempx][tempy] + hadc0;
				q1_count_h[tempx][tempy]++;
				SortHit(qx1,qy1,hadc1,xup_bd,yup_bd,tempx,tempy);
				q2_map_h[tempx][tempy] = q2_map_h[tempx][tempy] + hadc1;
				q2_count_h[tempx][tempy]++;
			}
			else {continue;}
		}	
	}

	for (int ix = 0; ix < 15; ix++)
	{	
		for (int iy = 0; iy < 80; iy++)
		{
			q1_map_l[ix][iy] = (q1_count_l[ix][iy] > 0)? q1_map_l[ix][iy]/q1_count_l[ix][iy] : q1_map_l[ix][iy];
			h_q1_l->Fill(xmid[ix],ymid[iy],q1_map_l[ix][iy]);
		
			q2_map_l[ix][iy] = (q2_count_l[ix][iy] > 0)? q2_map_l[ix][iy]/q2_count_l[ix][iy] : q2_map_l[ix][iy];
			h_q2_l->Fill(xmid[ix],ymid[iy],q1_map_l[ix][iy]);
	
			q1_map_h[ix][iy] = (q1_count_h[ix][iy] > 0)? q1_map_h[ix][iy]/q1_count_h[ix][iy] : q1_map_h[ix][iy];
			h_q1_h->Fill(xmid[ix],ymid[iy],q1_map_h[ix][iy]);
		
			q2_map_h[ix][iy] = (q2_count_h[ix][iy] > 0)? q2_map_h[ix][iy]/q2_count_h[ix][iy] : q2_map_h[ix][iy];
			h_q2_h->Fill(xmid[ix],ymid[iy],q2_map_h[ix][iy]);
		}
		h_q1_l->SetBinContent(ix,40,q1_map_l[ix][40]);
		h_q1_h->SetBinContent(ix,40,q1_map_h[ix][40]);
		h_q2_l->SetBinContent(ix,40,q2_map_l[ix][40]);
		h_q2_h->SetBinContent(ix,40,q2_map_h[ix][40]);
	}
	
	//double hello = h_q1_l->GetBinContent(16,40);
	//cout << hello << endl;
	gStyle->SetOptStat(0);
	gStyle->SetPalette(kBlueRedYellow);	
	TCanvas * c1 = new TCanvas("Q1","Q1",800,1000);
	c1->Divide(2,1);
	c1->cd(1);
	h_q1_l->Draw("COLZ");
	c1->cd(2);
	h_q1_h->Draw("COLZ");
	TCanvas * c2 = new TCanvas("Q2","Q2",800,1000);
	c2->Divide(2,1);
	c2->cd(1);
	h_q2_l->Draw("COLZ");
	c2->cd(2);
	h_q2_h->Draw("COLZ");
	
}
