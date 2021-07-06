#include <iostream>
#include <vector>
#include <string>
#include <TH1F.h>
using namespace std;

void plots()
{
   vector<std::string> names_files { "bkg1.root", "bkg2.root","signal5_l.root", "signal1.root",  "signal4.root", "signal2.root"} ;
   
    vector<std::string> names {"t#bar{t} h -> #tau+ #tau-", "t#bar{t}b#bar{b}/h","t#bar{t}Z' m(Z')= 150 GeV", "t#bar{t}Z' m(Z')= 350 GeV", "t#bar{t}Z' m(Z')= 1000 GeV", "t#bar{t}Z' m(Z')= 2000 GeV" };
    
    vector<std::string> plots {"Efficiencies_e", "StMet_e", "PT_Scalar_leptons_e", "PT_Vector_leptons_e", "dETA_leptons_e", "ETA_lepton1_e", "ETA_lepton2_e", "dPHI_leptons_e", "PHI_lepton1_e", "PHI_lepton2_e", "dPT_Scalar_leptons_e", "dPT_Vector_leptons_e", "Efficiencies_mu", "StMet_mu", "PT_Scalar_leptons_mu", "PT_Vector_leptons_mu", "dETA_leptons_mu", "ETA_lepton1_mu", "ETA_lepton2_mu", "dPHI_leptons_mu", "PHI_lepton1_mu", "PHI_lepton2_mu", "dPT_Scalar_leptons_mu", "dPT_Vector_leptons_mu", "M_leptons_e", "M_leptons_mu"};

    vector<std::string> plots_names {"Number of event after cuts for e #nu_{e}", "Total scalar PT of final states for e #nu_{e}", "Scalar PT of #tau+ #tau- for e #nu_{e}", "PT of #tau+ #tau- for e #nu_{e}", "#delta #eta of #tau+ #tau- for e #nu_{e}", "#eta of #tau_{1} for e #nu_{e}", "#eta of #tau_{2} for e #nu_{e}", "#delta #phi of #tau+ #tau- for e #nu_{e}", "#phi of #tau_{1} for e #nu_{e}", "#phi of #tau_{2} for e #nu_{e}", "Scalar #delta #p_{T} of #tau+ #tau- for e #nu_{e}", "Vector #delta #p_{T} of #tau+ #tau- for e #nu_{e}", "Number of event after cuts for #mu #nu_{#mu}", "Total scalar PT of final states for #mu #nu_{#mu}", "Scalar PT of #tau+ #tau- for #mu #nu_{#mu}", "PT of #tau+ #tau- for #mu #nu_{#mu}", "#delta #eta of #tau+ #tau- for #mu #nu_{#mu}", "#eta of #tau_{1} for #mu #nu_{#mu}", "#eta of #tau_{2} for #mu #nu_{#mu}", "#delta #phi of #tau+ #tau- for #mu #nu_{#mu}", "#phi of #tau_{1} for #mu #nu_{#mu}", "#phi of #tau_{2} for #mu #nu_{#mu}", "Scalar #delta #p_{T} of #tau+ #tau- for #mu #nu_{#mu}", "Vector #delta #p_{T} of #tau+ #tau- for #mu #nu_{#mu}", "Recostructed mass of #tau+ #tau- for #e #nu_{#e}", "Recostructed mass of #tau+ #tau- for #mu #nu_{#mu}"};
   

    vector<std::string> x_labels {"Cuts", "STMet  [GeV]", "|p_{T}| (#tau+ #tau-) [GeV]", "#vec p_{T} (#tau+ #tau-) [GeV]", "#delta #eta (#tau+ #tau-) [a.u.]", "#eta (#tau_{1}) [a.u.]", "#eta (#tau_{2}) [a.u.]", "#delta #phi (#tau+ #tau-) [a.u.]", "#phi (#tau_{1}) [a.u.]", "#phi (#tau_{2}) [a.u.]", "#delta #p_{T} (#tau+ #tau-) [a.u.]", "#delta #p_{T} (#tau+ #tau-) [a.u.]", "Cuts", "STMet  [GeV]", "|p_{T}| (#tau+ #tau-) [GeV]", "#vec p_{T} (#tau+ #tau-) [GeV]", "#delta #eta (#tau+ #tau-) [a.u.]", "#eta (#tau_{1}) [a.u.]", "#eta (#tau_{2}) [a.u.]", "#delta #phi (#tau+ #tau-) [a.u.]", "#phi (#tau_{1}) [a.u.]", "#phi (#tau_{2}) [a.u.]", "#delta #p_{T} (#tau+ #tau-) [a.u.]", "#delta #p_{T} (#tau+ #tau-) [a.u.]", "M (#tau+ #tau-) [GeV]", "M (#tau+ #tau-) [GeV]"};
    



    vector<int> colors {82, 5, 6, 7, 2, 4, 6, 8};

    vector<int> linestyles {1, 1, 10, 10, 10, 10, 10, 10};
    vector<double> cross {4.3623, 5.2391, 0.108, 0.13331, 0.16696, 0.28229, 0.33319}; 
    vector<double> total_events_e;
    vector<double> total_events_mu;
    for (int j=0; j<names.size(); j++)
    {
    	TFile f(names_files[j].c_str());
    	TH1F *h_mu = (TH1F*)f.Get("Efficiencies_mu");
    	TH1F *h_e = (TH1F*)f.Get("Efficiencies_e");
    	double mu= h_mu->GetBinContent(1);
    	double e= h_e->GetBinContent(1);
	total_events_e.push_back(e);
	total_events_mu.push_back(mu);
    }
    
    
TList *l = new TList();
    for(int i=0; i<plots.size(); i++)
    {
        THStack *hs = new THStack("hs", " ");
        TCanvas *c2 = new TCanvas(plots[i].c_str(),"Histos",1280,1024);  
        Double_t x_1,x_2;
        Double_t y_1,y_2;

        x_1 = 0.65;
        x_2 = 0.85;
        
	if (plots[i]=="PHI_lepton2_mu" || plots[i]=="PHI_lepton2_e"||plots[i]=="PHI_lepton1_mu" || plots[i]=="PHI_lepton1_e"){
		y_1 = 0.15;
		y_2 = 0.35;
	    
	} 
	else{
		y_1 = 0.65;
		y_2 = 0.85;
	}
        
        auto legend = new TLegend(x_1,y_1,x_2,y_2);
    for (int j=0; j<names.size(); j++)
    {    
        TFile f(names_files[j].c_str());
        TH1F *h = (TH1F*)f.Get(plots[i].c_str());
        h->SetDirectory(0);

        h->SetLineColor(colors[j]);
        h->SetLineStyle(linestyles[j]);
        h->SetLineWidth(3);
        

        /*if (plots[i]=="M_leptons_mu"){
        	h->Scale(1.0*cross[j]*150/total_events_mu[j]);
        	gPad->SetLogy();
        }
        
        else if (plots[i]=="M_leptons_e"){
        	h->Scale(1.0*cross[j]*150/total_events_e[j]);
        	gPad->SetLogy();
        }
        	
        else{*/
        h->Scale(1.0/h->Integral());
        //}

        legend->AddEntry(h,names[j].c_str(),"l");

        legend->SetBorderSize(0);
        hs->Add(h); 
    }   
        hs->Draw("NOSTACK HIST");
        hs->GetXaxis()->SetTitle(x_labels[i].c_str());
        hs->GetYaxis()->SetTitle("a.u.");
        legend->Draw();
        l->Add(c2);
        std::string filename = plots[i] + "_0cut.png";
        c2->SaveAs(filename.c_str());
    }
    
    TFile* Output = new TFile("joined.root", "RECREATE"); 
    l->Write();
    Output->Close();

}
    //PRUEBA *********************************************************
