#include "TROOT.h"
#include "TKey.h"
#include "TFile.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TObjArray.h"
#include "THStack.h"
#include "TLegend.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"
#include "TMath.h"
#include "TCut.h"
#include "TPaletteAxis.h"
#include "TMVA/Reader.h"
#include "TLatex.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>

void myROC_maker(){

  string fileNames[10];

  fileNames[0] = "Outputfile_histograms_GJetMC2018_newThr_bkg.root";
  fileNames[1] = "Outputfile_histograms_GJetMC2021_newThr_bkg.root";
  fileNames[2] = "Outputfile_histograms_GJetMC2023_newThr_bkg.root";
  //fileNames[3] = "Outputfile_histograms_QCDMC2024_30Jan.root";


  fileNames[3] = "Outputfile_histograms_GJetMC2018_newThr_sig.root";
  fileNames[4] = "Outputfile_histograms_GJetMC2021_newThr_sig.root";
  fileNames[5] = "Outputfile_histograms_GJetMC2023_newThr_sig.root";
  //fileNames[7] = "Outputfile_histograms_DYMC2024_30Jan.root";

  TCanvas * can = new TCanvas("can_mvares","can_mvares",600,600);
  string label_RNINEres = "RNINE output";

  TLegend *legend = new TLegend(0.15,0.55,0.8,0.85,"","brNDC");
  legend->SetHeader("EB");
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextFont(42);

  string labelLeg_s[10];

  labelLeg_s[0] = "Sig: 2018";
  labelLeg_s[1] = "Sig: 2021";
  labelLeg_s[2] = "Sig: 2023";
  //labelLeg_s[3] = "Sig: 2024";

  string labelLeg_b[10];

  labelLeg_b[0] = "Bkg: 2018";
  labelLeg_b[1] = "Bkg: 2021";
  labelLeg_b[2] = "Bkg: 2023";
  //labelLeg_b[3] = "Bkg: 2024";


  TCanvas * can_RoC = new TCanvas ("can_RoC","can_RoC",600,600);

  TLegend *legend_RoC = new TLegend(0.2,0.6,0.7,0.90,"","brNDC");
  legend_RoC->SetHeader("EB");
  legend_RoC->SetBorderSize(0);
  legend_RoC->SetFillStyle(0);
  legend_RoC->SetTextFont(42);

  string labelLeg_RoC[10];  
  labelLeg_RoC[0] = "2018";
  labelLeg_RoC[1] = "2021";
  labelLeg_RoC[2] = "2023";
  //labelLeg_RoC[3] = "2024";


  for(int i = 0; i < 3; i++){

    cout << "file # " << i << endl;

    TFile *RNINEResFile_s = new TFile(fileNames[i].c_str());
    TFile *RNINEResFile_b = new TFile(fileNames[i+3].c_str());

    //    TTree *t_output_s = (TTree*)RNINEResFile->Get("promptPhotons");
    // TTree *t_output_b = (TTree*)RNINEResFile->Get("fakePhotons");

    // TH1F * histo_s = new TH1F ("histo_s","histo_s",100,-1,1);
    // TH1F * histo_b = new TH1F ("histo_b","histo_b",100,-1,1);
    //    TH1F * histo_s = (TH1F*)RNINEResFile_s->Get("myR9_2_EB");
    TH1F * histo_s = (TH1F*)RNINEResFile_s->Get("R9_EB");
    //TH1F * histo_b = (TH1F*)RNINEResFile_b->Get("myR9_2_EB");
    TH1F * histo_b = (TH1F*)RNINEResFile_b->Get("R9_EB");
    TString tmp_s = "";
    TString tmp_b  = "";

    /*    tmp_s = "RNINEres";
    tmp_s+=">>histo_s";
    
    tmp_b = "RNINEres";
    tmp_b+=">>histo_b";

    t_output_s->Draw(tmp_s,"(abs(scEta)<1.5)*weight","goff");
    t_output_b->Draw(tmp_b,"(abs(scEta)<1.5)*weight","goff");
    */
    
    float Nsig[320], Nbkg[320];
    float sigEff[320], bkgEff[320];
    float cutsVal[320];
    float RNINEResCutVal = -0.00625;
    //float RNINEResCutVal = -0.002;

    //int nCuts = 1000;
    int nCuts = 320;

    int RNINESMaxBin = histo_s->GetXaxis()->FindBin(2);
    int RNINEBMaxBin = histo_b->GetXaxis()->FindBin(2);

    for(int k = 0; k < nCuts; k++){

      RNINEResCutVal+= 0.00625;
      // RNINEResCutVal+= 0.002;
      cutsVal[k] = RNINEResCutVal;

      int RNINEBin = histo_s->GetXaxis()->FindBin(RNINEResCutVal);
      Nsig[k] = histo_s->Integral(RNINEBin,RNINESMaxBin);

      int RNINEBin_b = histo_b->GetXaxis()->FindBin(RNINEResCutVal);
      Nbkg[k] = histo_b->Integral(RNINEBin_b,RNINEBMaxBin);
      sigEff[k] = Nsig[k]/Nsig[0];
      bkgEff[k] = Nbkg[k]/Nbkg[0];

      // if(sigEff[k] > 0.98) cout << " sigEff[k] = " << sigEff[k] <<  " bkgEff[k] = " << bkgEff[k] << " with a cut at " << RNINEResCutVal << endl;
      if(sigEff[k] > 0.89 && sigEff[k] < 0.91) cout << " sigEff[k] = " << sigEff[k] <<  " bkgEff[k] = " << bkgEff[k] << " with a cut at " << RNINEResCutVal << endl;


    }

    TGraph * sigEff_vs_cut = new TGraph (nCuts, cutsVal, sigEff);
    TGraph * bkgEff_vs_cut = new TGraph (nCuts, cutsVal, bkgEff);
    TGraph * sigEff_vs_bkgEff = new TGraph (nCuts, sigEff, bkgEff);

    // draw RNINEres
    can->cd();
    can->SetLogy();

    histo_s->SetTitle("");
    histo_s->SetStats(0);
    histo_s->GetXaxis()->SetTitle(label_RNINEres.c_str());
    histo_s->SetMaximum(histo_s->GetBinContent(histo_s->GetMaximumBin())*10);
       
    histo_s->SetLineStyle(1);
    histo_s->SetLineWidth(2);

    histo_b->SetLineStyle(2);
    histo_b->SetLineWidth(2);

    if(i == 0) {
      histo_s->SetLineColor(kBlue);
      histo_b->SetLineColor(kBlue);
    }
    else if(i == 1){
      histo_s->SetLineColor(kRed);
      histo_b->SetLineColor(kRed);
    }
    else if(i == 2){
      histo_s->SetLineColor(kGreen+2);
      histo_b->SetLineColor(kGreen+2);
    }
    else{
      histo_s->SetLineColor(i+2);
      histo_b->SetLineColor(i+2);
    }

    legend->AddEntry(histo_s,labelLeg_s[i].c_str(),"l");
    legend->AddEntry(histo_b,labelLeg_b[i].c_str(),"l");

        
    if(i == 0){
      histo_s->Draw("HIST");
    }
    else histo_s->Draw("HISTSAME");
    legend->Draw("same");
    histo_b->Draw("same");

    TLatex *txt = new TLatex(0.2, 0.9, "");
    // txt->SetTextSize(0.05);
    txt->DrawLatexNDC(0.1, 0.91, "CMS #bf{#it{#scale[0.8]{Simulation Preliminary}}}");
    //txt->DrawLatexNDC(0.76, 0.91, "#bf{13 TeV}");
    txt->Draw("same");

    can->Update();
    can->Modified();

    // draw RoC curves 

    can_RoC->cd();

    if(i == 0){
      sigEff_vs_bkgEff->SetTitle("");
      sigEff_vs_bkgEff->GetYaxis()->SetTitleOffset(1.5);
      sigEff_vs_bkgEff->GetYaxis()->SetTitleSize(0.03);
      sigEff_vs_bkgEff->GetYaxis()->SetLabelSize(0.02);
      sigEff_vs_bkgEff->GetXaxis()->SetTitleOffset(1.5);
      sigEff_vs_bkgEff->GetXaxis()->SetTitleSize(0.03);
      sigEff_vs_bkgEff->GetXaxis()->SetLabelSize(0.02);

      
      //      sigEff_vs_bkgEff->GetXaxis()->SetRangeUser(0.8,1.);
      sigEff_vs_bkgEff->GetXaxis()->SetRangeUser(0.0,1.);
      // sigEff_vs_bkgEff->GetYaxis()->SetRangeUser(0.,0.4);
      sigEff_vs_bkgEff->GetYaxis()->SetRangeUser(0.,1.0);
      

      sigEff_vs_bkgEff->GetXaxis()->SetTitle("Signal Eff.");
      sigEff_vs_bkgEff->GetYaxis()->SetTitle("Background Eff.");

    }


    sigEff_vs_bkgEff->SetLineWidth(2);

    if(i == 0) {
      sigEff_vs_bkgEff->SetLineColor(kBlue);
      // sigEff_vs_bkgEff->SetMarkerColor(kBlue);
    }
    else if(i == 1){
      sigEff_vs_bkgEff->SetLineColor(kRed);
      // sigEff_vs_bkgEff->SetMarkerColor(kRed);
    }
    else if(i == 2){
      sigEff_vs_bkgEff->SetLineColor(kGreen+2);
      // sigEff_vs_bkgEff->SetMarkerColor(kGreen+2);
    }

    else{
      sigEff_vs_bkgEff->SetLineColor(i+2);
      // sigEff_vs_bkgEff->SetMarkerColor(i+2);
    }

    can_RoC->SetGrid();

    if(i == 0)  sigEff_vs_bkgEff->Draw("AC");
    else sigEff_vs_bkgEff->Draw("sameC");

    legend_RoC->AddEntry(sigEff_vs_bkgEff,labelLeg_RoC[i].c_str(),"pl");
    legend_RoC->Draw("same");

    TLatex *txt1 = new TLatex(0.2, 0.9, "");
    // txt->SetTextSize(0.05);
    txt1->DrawLatexNDC(0.1, 0.91, "CMS #bf{#it{#scale[0.8]{Simulation Preliminary}}}");
    // txt->DrawLatexNDC(0.76, 0.91, "#bf{13 TeV}");
    txt1->Draw("same");

    can_RoC->Update();
    can_RoC->Modified();
  }

  string RNINERes = "";
  RNINERes = "RNINEres_EB_R9_Hgg";

  can->SaveAs((RNINERes+".pdf").c_str()); 
  can->SaveAs((RNINERes+".png").c_str()); 
  can->SaveAs((RNINERes+".root").c_str()); 

  string canName_RoC = "";

  canName_RoC = "RoC_EB_R9_Hgg";

  can_RoC->SaveAs((canName_RoC+".pdf").c_str()); 
  can_RoC->SaveAs((canName_RoC+".png").c_str()); 
  can_RoC->SaveAs((canName_RoC+".root").c_str()); 
}
