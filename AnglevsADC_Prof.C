void AnglevsADC_Prof()
{
        // Variables and Branches 
        // Angles are Radians 

        double ph, th;
        double hadc0, hadc1;
        double ladc0, ladc1;
        double phmax = 0.3, phmin = -0.30;
        double thmax = 0.15, thmin = -0.15;
        double hadc0max = 250, hadc0min = 120;
        double ladc0max = 1800, ladc0min = 1000;
        double hadc1max = 180, hadc1min = 120;
        double ladc1max = 1300, ladc1min = 1000;
        double pedestal[4] = {1194,151.7,1084,137.2}; // M: L0, H0, L1, H1
        long noevt[3] = {2798,1712,425}; // M: Must manually set number of events, check ph hist. 
        int nofiles = 2; // M: Number of files minus 1 for 0

        // Histograms

        gStyle->SetOptStat("Men");

        TProfile * h_ladc0_ph = new TProfile("ladc0.ph","Low ADC0 Charge vs #phi",25,phmin,phmax);
        //h_ladc0_ph->SetOption("COLZ");
        TProfile * h_hadc0_ph = new TProfile("hadc0.ph","High ADC0 Charge vs #phi",25,phmin,phmax);
        //h_hadc0_ph->SetOption("COLZ");
        TProfile * h_ladc1_ph = new TProfile("ladc1.ph","Low ADC1 Charge vs #phi",25,phmin,phmax);
        //h_ladc1_ph->SetOption("COLZ");
        TProfile * h_hadc1_ph = new TProfile("hadc1.ph","High ADC1 Charge vs #phi",25,phmin,phmax);
        //h_hadc1_ph->SetOption("COLZ");
        TProfile * h_ladc0_th = new TProfile("ladc0.th","Low ADC0 Charge vs #theta",20,thmin,thmax);
        //h_ladc0_th->SetOption("COLZ");
        TProfile * h_hadc0_th = new TProfile("hadc0.th","High ADC0 Charge vs #theta",20,thmin,thmax);
        //h_hadc0_th->SetOption("COLZ");
        TProfile * h_ladc1_th = new TProfile("ladc1.th","Low ADC1 Charge vs #theta",20,thmin,thmax);
                                                                      
        for (int ifile = 0; ifile < nofiles; ifile++)
        {
                TString filename = Form("mergedtests_%d.root",ifile);
                TFile * p_infile = TFile::Open(filename,"READ");
                TTree * t_T = (TTree*)p_infile->Get("T");

                t_T->SetBranchAddress("prex.tr.ph",&ph);
                t_T->SetBranchAddress("prex.tr.th",&th);
                t_T->SetBranchAddress("prex.sbuscint.hadc0",&hadc0);
                t_T->SetBranchAddress("prex.sbuscint.hadc1",&hadc1);
                t_T->SetBranchAddress("prex.sbuscint.ladc0",&ladc0);
                t_T->SetBranchAddress("prex.sbuscint.ladc1",&ladc1);

                //cout << "Number of Events is " << noevt << endl;

                // Fill Histograms

                for (int ievt = 0; ievt < noevt[ifile]; ievt++)
                {
                        //cout << "Event Number " << ievt << endl;
                        t_T->GetEntry(ievt);

                        //ladc0 -= pedestal[0]; 
                        //hadc0 -= pedestal[1];
                        //ladc1 -= pedestal[2]; 
                        //hadc1 -= pedestal[3];

                        if (ladc0 > pedestal[0] && hadc0 > pedestal[1] && ladc1 > pedestal[2] && hadc1 > pedestal[3]) // Change acceptance conditions as needed
                        {
                                h_ladc0_ph->Fill(ph,ladc0);
                                h_ladc1_ph->Fill(ph,ladc1);
                                h_hadc0_ph->Fill(ph,hadc0);
                                h_hadc1_ph->Fill(ph,hadc1);

                                h_ladc0_th->Fill(th,ladc0);
                                h_ladc1_th->Fill(th,ladc1);
                                h_hadc0_th->Fill(th,hadc0);
                                h_hadc1_th->Fill(th,hadc1);
                                
                         }
                 }

                 p_infile->Close();
        }

        TCanvas * c_th = new TCanvas("c_th","c_th",900,900);
        c_th->Divide(2,2);
        c_th->cd(1);
        h_ladc0_th->Draw();
        c_th->cd(2);
        h_ladc1_th->Draw();
        c_th->cd(3);
        h_hadc0_th->Draw();
        c_th->cd(4);
        h_hadc1_th->Draw();

        TCanvas * c_ph = new TCanvas("c_ph","c_ph",900,900);
        c_ph->Divide(2,2);
        c_ph->cd(1);
        h_ladc0_ph->Draw();
        c_ph->cd(2);
        h_ladc1_ph->Draw();
        c_ph->cd(3);
        h_hadc0_ph->Draw();
        c_ph->cd(4);
        h_hadc1_ph->Draw();
}

                                                                                                                                       39,0-1        57%
