void Transform(double& x, double& y, double& z);
void FitLin(double x1, double x2, double x3, double z1, double z2, double z3, double& m, double& b);
//void Refit(double& x1, double& x2, double& x3, double m, double b);

double xRotation = 0.0;//0.00703; // From Run 20862
double yRotation = 0.0;//0.007447; 
double xTranslation = 0.0;//0.013;
double yTranslation = 0.0;//-0.00687;

void LGEM_Alignment()
{
	int runno = 1850;
	double x1, x2, x3, y1, y2, y3, z1 = 0.684, z2 = 1.3698, z3 = 1.573;
	double x1p, x2p, x3p, y1p, y2p, y3p, z1p, z2p, z3p;
	double x1o, x2o, x3o, y1o, y2o, y3o;
	double xv, yv;
	double x1v, x2v, x3v, y1v, y2v, y3v; 
	double x1_3D, x2_3D, x3_3D, y1_3D, y2_3D, y3_3D;
	double VDCth, VDCph;
	double VDCth2, VDCph2;
	double mx, bx, my, by;
	double GEMtr, VDCtr;

	//TChain * ch = new TChain("T");
	TString s_in = Form("/chafs1/work1/prex_counting/marisa/LHRS/prexLHRS_%i_-1_0.root",runno);
	//Int_t infiles = ch->Add(s_in.Data());
	TFile * f_in = TFile::Open(s_in,"READ");
	TTree * t_in = (TTree*)f_in->Get("T");
	t_in->SetBranchAddress("LGEM.rgems.x1.coord.3Dpos",&x1);
	t_in->SetBranchAddress("LGEM.rgems.x2.coord.3Dpos",&x2);
	t_in->SetBranchAddress("LGEM.rgems.x3.coord.3Dpos",&x3);
	t_in->SetBranchAddress("LGEM.rgems.y1.coord.3Dpos",&y1);
	t_in->SetBranchAddress("LGEM.rgems.y2.coord.3Dpos",&y2);
	t_in->SetBranchAddress("LGEM.rgems.y3.coord.3Dpos",&y3);
	t_in->SetBranchAddress("L.tr.x",&xv);
	t_in->SetBranchAddress("L.tr.y",&yv);
	t_in->SetBranchAddress("L.tr.ph",&VDCph);
	t_in->SetBranchAddress("L.tr.th",&VDCth);
	t_in->SetBranchAddress("LGEM.tr.n",&GEMtr);
	t_in->SetBranchAddress("L.tr.n",&VDCtr);
	long entries = t_in->GetEntries();

	TString s_out = Form("/chafs1/work1/prex_counting/marisa/LHRS/prexLHRS_%d_transformed.root",runno);
	TFile * f_out = TFile::Open(s_out,"RECREATE");
	TTree * t_out = new TTree("T","T");
	TBranch * b_x1p = t_out->Branch("LGEM.x1",&x1p,"LGEM.x1/D");
	TBranch * b_x2p = t_out->Branch("LGEM.x2",&x2p,"LGEM.x2/D");
	TBranch * b_x3p = t_out->Branch("LGEM.x3",&x3p,"LGEM.x3/D");
	TBranch * b_y1p = t_out->Branch("LGEM.y1",&y1p,"LGEM.y1/D");
	TBranch * b_y2p = t_out->Branch("LGEM.y2",&y2p,"LGEM.y2/D");
	TBranch * b_y3p = t_out->Branch("LGEM.y3",&y3p,"LGEM.y3/D");
	TBranch * b_z1p = t_out->Branch("LGEM.z1",&z1p,"LGEM.z1/D");
	TBranch * b_z2p = t_out->Branch("LGEM.z2",&z2p,"LGEM.z2/D");
	TBranch * b_z3p = t_out->Branch("LGEM.z3",&z3p,"LGEM.z3/D");
	TBranch * b_x1_3D = t_out->Branch("LGEM.x1_3D",&x1_3D,"LGEM.x1_3D/D");
	TBranch * b_x2_3D = t_out->Branch("LGEM.x2_3D",&x2_3D,"LGEM.x2_3D/D");
	TBranch * b_x3_3D = t_out->Branch("LGEM.x3_3D",&x3_3D,"LGEM.x3_3D/D");
	TBranch * b_y1_3D = t_out->Branch("LGEM.y1_3D",&y1_3D,"LGEM.y1_3D/D");
	TBranch * b_y2_3D = t_out->Branch("LGEM.y2_3D",&y2_3D,"LGEM.y2_3D/D");
	TBranch * b_y3_3D = t_out->Branch("LGEM.y3_3D",&y3_3D,"LGEM.y3_3D/D");
	TBranch * b_x1o = t_out->Branch("LGEM.x1.ori",&x1o,"LGEM.x1.ori/D");
	TBranch * b_x2o = t_out->Branch("LGEM.x2.ori",&x2o,"LGEM.x2.ori/D");
	TBranch * b_x3o = t_out->Branch("LGEM.x3.ori",&x3o,"LGEM.x3.ori/D");
	TBranch * b_y1o = t_out->Branch("LGEM.y1.ori",&y1o,"LGEM.y1.ori/D");
	TBranch * b_y2o = t_out->Branch("LGEM.y2.ori",&y2o,"LGEM.y2.ori/D");
	TBranch * b_y3o = t_out->Branch("LGEM.y3.ori",&y3o,"LGEM.y3.ori/D");
	TBranch * b_x1v = t_out->Branch("LVDC.x1",&x1v,"LVDC.x1/D");
	TBranch * b_x2v = t_out->Branch("LVDC.x2",&x2v,"LVDC.x2/D");
        TBranch * b_x3v = t_out->Branch("LVDC.x3",&x3v,"LVDC.x3/D"); 
	TBranch * b_y1v = t_out->Branch("LVDC.y1",&y1v,"LVDC.y1/D");
	TBranch * b_y2v = t_out->Branch("LVDC.y2",&y2v,"LVDC.y2/D");
	TBranch * b_y3v = t_out->Branch("LVDC.y3",&y3v,"LVDC.y3/D");
	TBranch * b_VDCth = t_out->Branch("VDC.th",&VDCth2,"VDC.th/D");
	TBranch * b_VDCph = t_out->Branch("VDC.ph",&VDCph2,"VDC.ph/D");
	TBranch * b_GEMth = t_out->Branch("LGEM.th",&mx,"LEM.th/D");
	TBranch * b_GEMph = t_out->Branch("LGEM.ph",&my,"LGEM.ph/D");

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
