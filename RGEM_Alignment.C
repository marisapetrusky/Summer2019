void Transform(double& x, double& y, double& z);
void FitLin(double x1, double x2, double x3, double z1, double z2, double z3, double& m, double& b);
//void Refit(double& x1, double& x2, double& x3, double m, double b);

double xRotation = 0.00703; // From Run 20862
double yRotation = 0.007447; 
double xTranslation = 0.013;
double yTranslation = -0.00687;

void RGEM_Alignment(int runno)
{
	double x1, x2, x3, y1, y2, y3, z1 = 0.684, z2 = 1.3698, z3 = 1.573;
	double x1p, x2p, x3p, y1p, y2p, y3p, z1p, z2p, z3p;
	double x1o, x2o, x3o, y1o, y2o, y3o;
	double xv, yv, x0v,y0v;
	double x1v, x2v, x3v, y1v, y2v, y3v; 
	double x1_3D, x2_3D, x3_3D, y1_3D, y2_3D, y3_3D;
	double VDCth, VDCph;
	double VDCth2, VDCph2;
	double mx, bx, my, by;
	double GEMtr, VDCtr;
	double DSQadc, USQadc;
	double DSQadcO, USQadcO;

	//TChain * ch = new TChain("T");
	TString s_in = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%i_-1_0.root",runno);
	//Int_t infiles = ch->Add(s_in.Data());
	TFile * f_in = TFile::Open(s_in,"READ");
	TTree * t_in = (TTree*)f_in->Get("T");
	t_in->SetBranchAddress("RGEM.rgems.x1.coord.3Dpos",&x1);
	t_in->SetBranchAddress("RGEM.rgems.x2.coord.3Dpos",&x2);
	t_in->SetBranchAddress("RGEM.rgems.x3.coord.3Dpos",&x3);
	t_in->SetBranchAddress("RGEM.rgems.y1.coord.3Dpos",&y1);
	t_in->SetBranchAddress("RGEM.rgems.y2.coord.3Dpos",&y2);
	t_in->SetBranchAddress("RGEM.rgems.y3.coord.3Dpos",&y3);
	t_in->SetBranchAddress("R.tr.x",&xv);
	t_in->SetBranchAddress("R.tr.y",&yv);
	t_in->SetBranchAddress("R.tr.ph",&VDCph);
	t_in->SetBranchAddress("R.tr.th",&VDCth);
	t_in->SetBranchAddress("RGEM.tr.n",&GEMtr);
	t_in->SetBranchAddress("R.tr.n",&VDCtr);
	t_in->SetBranchAddress("P.loQadcR",&DSQadc);
        t_in->SetBranchAddress("P.upQadcR",&USQadc);	

	long entries = t_in->GetEntries();

	TString s_out = Form("/chafs1/work1/prex_counting/marisa/RHRS/prexRHRS_%d_transformed.root",runno);
	TFile * f_out = TFile::Open(s_out,"RECREATE");
	TTree * t_out = new TTree("T","T");
	TBranch * b_x1p = t_out->Branch("RGEM.x1",&x1p,"RGEM.x1/D");
	TBranch * b_x2p = t_out->Branch("RGEM.x2",&x2p,"RGEM.x2/D");
	TBranch * b_x3p = t_out->Branch("RGEM.x3",&x3p,"RGEM.x3/D");
	TBranch * b_y1p = t_out->Branch("RGEM.y1",&y1p,"RGEM.y1/D");
	TBranch * b_y2p = t_out->Branch("RGEM.y2",&y2p,"RGEM.y2/D");
	TBranch * b_y3p = t_out->Branch("RGEM.y3",&y3p,"RGEM.y3/D");
	TBranch * b_z1p = t_out->Branch("RGEM.z1",&z1p,"RGEM.z1/D");
	TBranch * b_z2p = t_out->Branch("RGEM.z2",&z2p,"RGEM.z2/D");
	TBranch * b_z3p = t_out->Branch("RGEM.z3",&z3p,"RGEM.z3/D");
	TBranch * b_x1_3D = t_out->Branch("RGEM.x1_3D",&x1_3D,"RGEM.x1_3D/D");
	TBranch * b_x2_3D = t_out->Branch("RGEM.x2_3D",&x2_3D,"RGEM.x2_3D/D");
	TBranch * b_x3_3D = t_out->Branch("RGEM.x3_3D",&x3_3D,"RGEM.x3_3D/D");
	TBranch * b_y1_3D = t_out->Branch("RGEM.y1_3D",&y1_3D,"RGEM.y1_3D/D");
	TBranch * b_y2_3D = t_out->Branch("RGEM.y2_3D",&y2_3D,"RGEM.y2_3D/D");
	TBranch * b_y3_3D = t_out->Branch("RGEM.y3_3D",&y3_3D,"RGEM.y3_3D/D");
	TBranch * b_x1o = t_out->Branch("RGEM.x1.ori",&x1o,"RGEM.x1.ori/D");
	TBranch * b_x2o = t_out->Branch("RGEM.x2.ori",&x2o,"RGEM.x2.ori/D");
	TBranch * b_x3o = t_out->Branch("RGEM.x3.ori",&x3o,"RGEM.x3.ori/D");
	TBranch * b_y1o = t_out->Branch("RGEM.y1.ori",&y1o,"RGEM.y1.ori/D");
	TBranch * b_y2o = t_out->Branch("RGEM.y2.ori",&y2o,"RGEM.y2.ori/D");
	TBranch * b_y3o = t_out->Branch("RGEM.y3.ori",&y3o,"RGEM.y3.ori/D");
	TBranch * b_x0v = t_out->Branch("RVDC.x",&x0v,"RVDC.x/D");
	TBranch * b_y0v = t_out->Branch("RVDC.y",&y0v,"RVDC.y/D");
	TBranch * b_x1v = t_out->Branch("RVDC.x1",&x1v,"RVDC.x1/D");
	TBranch * b_x2v = t_out->Branch("RVDC.x2",&x2v,"RVDC.x2/D");
        TBranch * b_x3v = t_out->Branch("RVDC.x3",&x3v,"RVDC.x3/D"); 
	TBranch * b_y1v = t_out->Branch("RVDC.y1",&y1v,"RVDC.y1/D");
	TBranch * b_y2v = t_out->Branch("RVDC.y2",&y2v,"RVDC.y2/D");
	TBranch * b_y3v = t_out->Branch("RVDC.y3",&y3v,"RVDC.y3/D");
	TBranch * b_VDCth = t_out->Branch("RVDC.th",&VDCth2,"RVDC.th/D");
	TBranch * b_VDCph = t_out->Branch("RVDC.ph",&VDCph2,"RVDC.ph/D");
	TBranch * b_GEMth = t_out->Branch("RGEM.th",&mx,"RGEM.th/D");
	TBranch * b_GEMph = t_out->Branch("RGEM.ph",&my,"RGEM.ph/D");
	TBranch * b_DSQ = t_out->Branch("DSQadc",&DSQadcO,"DSQadc/D");
	TBranch * b_USQ = t_out->Branch("USQadc",&USQadcO,"USQadc/D");

	for (int ievt = 0; ievt < entries; ievt++)
	{
	        t_in->GetEntry(ievt);
		
		if (GEMtr > 0 && VDCtr > 0)
		{
			//cout << "Event = " << ievt << endl;
			x1p = x1;
			x2p = x2;
			x3p = x3;
			y1p = y1;
			y2p = y2;
			y3p = y3;
			z1p = z1;
			z2p = z2;
			z3p = z3;
			
			x1o = x1;
			x2o = x2;
			x3o = x3;
			y1o = y1;
			y2o = y2;
			y3o = y3;
		
			x0v = xv;
			y0v = yv;

			USQadcO = USQadc;
			DSQadcO = DSQadc;

			Transform(x1p,y1p,z1p);	
			Transform(x2p,y2p,z2p);
			Transform(x3p,y3p,z3p);
			
			x1v = xv + z1p*VDCth;
			x2v = xv + z2p*VDCth;
			x3v = xv + z3p*VDCth;
			y1v = yv + z1p*VDCph;
			y2v = yv + z2p*VDCph;
			y3v = yv + z3p*VDCph;
		
			VDCth2 = VDCth;
			VDCph2 = VDCph;

			FitLin(x1p,x2p,x3p,z1p,z2p,z3p,mx,bx);
			FitLin(y1p,y2p,y3p,z1p,z2p,z3p,my,by);
			
			x1_3D = mx*z1p + bx;
			x2_3D = mx*z2p + bx; 
			x3_3D = mx*z3p + bx; 
		
			y1_3D = my*z1p + by; 
			y2_3D = my*z2p + by;
			y3_3D = my*z3p + by;

			t_out->Fill();
		}
	}
	f_in->Close();
	t_out->Write();
	f_out->Close();
}

void Transform(double& x, double& y, double& z)
{
	double a = xRotation;
	double b = yRotation;
	double xoff = xTranslation;
	double yoff = yTranslation;

	x = cos(a)*x + sin(b)*sin(a)*y + sin(b)*cos(a)*z - xoff;
	y = cos(a)*y - sin(a)*y - yoff;
	z = -sin(b)*x + cos(b)*sin(a)*y + cos(b)*cos(a)*z; 
}

void FitLin(double x1, double x2, double x3, double z1, double z2, double z3, double& m, double& b)
{
	double x[3] = {x1,x2,x3};
	double z[3] = {z1,z2,z3};
	TGraph * gr = new TGraph(3,z,x);
	TF1 * lin = new TF1("lin","[0] + [1]*x",0,2);
	gr->Fit("lin","Q");
	m = lin->GetParameter(1);
	b = lin->GetParameter(0); 
}

//void Refit(double& x1, double& x2, double& x3, double m, double b)
