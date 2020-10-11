#define tree_analyser_cxx
#include "tree_analyser.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void tree_analyser::Loop()
{
//   In a ROOT session, you can do:
//      root> .L tree_analyser.C
//      root> tree_analyser t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   //const int nbins = 25;
   //double ptbin[nbins+1] = {22.0,24.0,26.0,28.0,30.0,32.0,34.0,36.0,38.0,40.0,42.0,44.0,46.0,48.0,50.0,55.0,60.0,65.0,70.0,75.0,80.0,90.0,100.0,150.0,200.0,250.0};
   //  vector<float> varY = {eleR9};
   //  vector<float> varX = {elePt};
   double myR9_1, myR9_2, cmsR9_2 = 999.0;
   Long64_t nbytes = 0, nb = 0;
   TH1D *hist[8];
   const char *hname[] = {"R9_EB","R9_EE","myR9_1_EB","myR9_1_EE","myR9_2_EB","myR9_2_EE", "cmsR9_2_EB","cmsR9_2_EE"};
   float hist_min[] = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0,-1.0, -1.0};
   float hist_max[] = {10.0,10.0,10.0,10.0,10.0,10.0,10.0,10.0};
   float hist_nbins[] = {550,550,550,550,550,550,550,550};
   for(int i=0;i<sizeof(hist_min)/sizeof(hist_min[0]);i++){
     std::cout<<hname[i]<<" 1D histogram is defined"<<std::endl;
     
     // hprof[i] = new TProfile(histname[i],histname[i],nbins,ptbin);
     string tname;
     tname += hname[i];
     hist[i] = new TH1D(tname.c_str(),tname.c_str(),hist_nbins[i],hist_min[i],hist_max[i]);
   }
   
   
   
   TProfile *hprof[24];
   const char *histname[] = {"R9_EB","R9_EE","R9","R9", "R9_EB","R9_EE","R9_EB","R9_EE",   "myR9_1_EB","myR9_1_EE","myR9_1","myR9_1", "myR9_1_EB","myR9_1_EE","myR9_1_EB","myR9_1_EE",   "myR9_2_EB","myR9_2_EE","myR9_2","myR9_2", "myR9_2_EB","myR9_2_EE","myR9_2_EB","myR9_2_EE"};
   const char *varX[] = {"pt","pt", "eta","phi","nvtx", "nvtx", "rho", "rho","pt","pt", "eta","phi","nvtx", "nvtx", "rho", "rho","pt","pt", "eta","phi","nvtx", "nvtx", "rho", "rho"};
   float histrange_min[] = {0.0, 0.0, -2.5, -3.5, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, -2.5, -3.5, 0.0, 0.0, 0.0, 0.0,   0.0, 0.0, -2.5, -3.5, 0.0, 0.0, 0.0, 0.0};
   float histrange_max[] = {250.0, 250, 2.5, 3.5, 110.0, 110.0, 80.0, 80.0,   250.0, 250, 2.5, 3.5, 110.0, 110.0, 80.0, 80.0,   250.0, 250, 2.5, 3.5, 110.0, 110.0, 80.0, 80.0};
   float histrange_nbins[] = {125, 125, 100, 100, 110, 110, 80, 80,   125, 125, 100, 100, 110, 110, 80, 80,   125, 125, 100, 100, 110, 110, 80, 80};
   for(int i=0;i<sizeof(histrange_min)/sizeof(histrange_min[0]);i++){
     std::cout<<histname[i]<<" profile histogram is defined"<<std::endl;
	  
     // hprof[i] = new TProfile(histname[i],histname[i],nbins,ptbin);
     string tmpname;
     tmpname += histname[i];
     tmpname += varX[i];
     //hprof[i] = new TProfile(histname[i],histname[i],histrange_nbins[i],histrange_min[i],histrange_max[i]);
     hprof[i] = new TProfile(tmpname.c_str(),tmpname.c_str(),histrange_nbins[i],histrange_min[i],histrange_max[i]);
     }



   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      for(unsigned j =0; j<nEle;j++){
	/*if((*eleE3x3Full5x5)[j]==0){
	  std::cout<<"cms E3x3 of this electron for which E3x3 is zero is "<< (*eleR9Full5x5)[j]*(*eleSCRawEn)[j]<<std::endl;
	  continue;
	  }*/
	if((*elePt)[j]<5 || (*ele_genmatched)[j]==0) continue;
	//if((*elePt)[j]<5 || (*ele_genmatched)[j]==0 || (*eleE3x3Full5x5)[j]==0) continue;
	myR9_1 = (*eleE3x3Full5x5)[j]/(*eleE5x5Full5x5)[j];
	myR9_2 = (*eleE3x3Full5x5)[j]/(*eleEn)[j];
	cmsR9_2 = (*eleE3x3Full5x5)[j]/(*eleSCRawEn)[j];
	//if(myR9_1==0 || myR9_2==0) std::cout<<"In this event myR91 and myR92 are zero. "<<(*eleE3x3Full5x5)[j]<<" is 3x3 energy and original R9 "<<(*eleE3x3Full5x5)[j]/(*eleSCRawEn)[j]<<std::endl;
	for(int i=0;i<sizeof(hist_min)/sizeof(hist_min[0]);i++){
	  if(jentry%10000 == 0) std::cout<<"In "<<jentry<<"th entry, " << hname[i]<<" histogram is being filled"<<std::endl;
	  if(i==0 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if((*eleR9Full5x5)[j]>=-1.0) hist[i]->Fill((*eleR9Full5x5)[j],genWeight);
	  }
	  if(i==1 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if((*eleR9Full5x5)[j]>=-1.0) hist[i]->Fill((*eleR9Full5x5)[j],genWeight);
	  }
	  if(i==2+0 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if((*eleR9Full5x5)[j]>=-1.0) hist[i]->Fill(myR9_1,genWeight);
	  }
	  if(i==2+1 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if((*eleR9Full5x5)[j]>=-1.0) hist[i]->Fill(myR9_1,genWeight);
	  }
	  if(i==4+0 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if((*eleR9Full5x5)[j]>=-1.0) hist[i]->Fill(myR9_2,genWeight);
	  }
	  if(i==4+1 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if((*eleR9Full5x5)[j]>=-1.0) hist[i]->Fill(myR9_2,genWeight);
	  }
	  if(i==6+0 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if((*eleR9Full5x5)[j]>=-1.0) hist[i]->Fill(cmsR9_2,genWeight);
	  }
	  if(i==6+1 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if((*eleR9Full5x5)[j]>=-1.0) hist[i]->Fill(cmsR9_2,genWeight);
	  }
	  
	  
	  
	}
	
	
	
	
	
	for(int i=0;i<sizeof(histrange_min)/sizeof(histrange_min[0]);i++){
	  if(jentry%10000 == 0) std::cout<<"In "<<jentry<<"th entry, " << histname[i]<<" profile histogram is being filled"<<std::endl;
	  if(i==0 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if((*eleR9Full5x5)[j]>=-1.0) hprof[i]->Fill((*elePt)[j],(*eleR9Full5x5)[j],genWeight);
	  }
	  if(i==1 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if((*eleR9Full5x5)[j]>=-1.0) hprof[i]->Fill((*elePt)[j],(*eleR9Full5x5)[j],genWeight);
	  }
	  if(i==2 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<2.5){
	    if((*eleR9Full5x5)[j]>=-1.0) hprof[i]->Fill((*eleSCEta)[j],(*eleR9Full5x5)[j],genWeight);
	  }
	  if(i==3 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<2.5){
	    if((*eleR9Full5x5)[j]>=-1.0) hprof[i]->Fill((*eleSCPhi)[j],(*eleR9Full5x5)[j],genWeight);
	  }
	  if(i==4 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if((*eleR9Full5x5)[j]>=-1.0) hprof[i]->Fill(nVtx,(*eleR9Full5x5)[j],genWeight);
	  }
	  if(i==5 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if((*eleR9Full5x5)[j]>=-1.0) hprof[i]->Fill(nVtx,(*eleR9Full5x5)[j],genWeight);
	  }
	  if(i==6 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if((*eleR9Full5x5)[j]>=-1.0) hprof[i]->Fill(rho,(*eleR9Full5x5)[j],genWeight);
	  }
	  if(i==7 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if((*eleR9Full5x5)[j]>=-1.0) hprof[i]->Fill(rho,(*eleR9Full5x5)[j],genWeight);
	  }





	  //New 1st version R9 Full5x5_e3x3/Full5x5_e5x5
	  if(i==8+0 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if(myR9_1>=-1.0) hprof[i]->Fill((*elePt)[j],myR9_1,genWeight);
	  }
	  if(i==8+1 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_1>=-1.0) hprof[i]->Fill((*elePt)[j],myR9_1,genWeight);
	  }
	  if(i==8+2 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_1>=-1.0) hprof[i]->Fill((*eleSCEta)[j],myR9_1,genWeight);
	  }
	  if(i==8+3 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_1>=-1.0) hprof[i]->Fill((*eleSCPhi)[j],myR9_1,genWeight);
	  }
	  if(i==8+4 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if(myR9_1>=-1.0) hprof[i]->Fill(nVtx,myR9_1,genWeight);
	  }
	  if(i==8+5 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_1>=-1.0) hprof[i]->Fill(nVtx,myR9_1,genWeight);
	  }
	  if(i==8+6 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if(myR9_1>=-1.0) hprof[i]->Fill(rho,myR9_1,genWeight);
	  }
	  if(i==8+7 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_1>=-1.0) hprof[i]->Fill(rho,myR9_1,genWeight);
	  }






	  //New 2nd version R9 Full5x5_e3x3/(electron corrected energy)
	  if(i==16+0 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if(myR9_2>=-1.0) hprof[i]->Fill((*elePt)[j],myR9_2,genWeight);
	  }
	  if(i==16+1 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_2>=-1.0) hprof[i]->Fill((*elePt)[j],myR9_2,genWeight);
	  }
	  if(i==16+2 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_2>=-1.0) hprof[i]->Fill((*eleSCEta)[j],myR9_2,genWeight);
	  }
	  if(i==16+3 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_2>=-1.0) hprof[i]->Fill((*eleSCPhi)[j],myR9_2,genWeight);
	  }
	  if(i==16+4 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if(myR9_2>=-1.0) hprof[i]->Fill(nVtx,myR9_2,genWeight);
	  }
	  if(i==16+5 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_2>=-1.0) hprof[i]->Fill(nVtx,myR9_2,genWeight);
	  }
	  if(i==16+6 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])<1.479){
	    if(myR9_2>=-1.0) hprof[i]->Fill(rho,myR9_2,genWeight);
	  }
	  if(i==16+7 && (*ele_genmatched)[j]==1 && std::abs((*eleSCEta)[j])>1.479 && std::abs((*eleSCEta)[j])<2.5){
	    if(myR9_2>=-1.0) hprof[i]->Fill(rho,myR9_2,genWeight);
	  }
	  
	}
      }
   }
   
   //   TFile *outputfile = new TFile("Outputfile_histograms_QCDMC2021_8Dec.root","RECREATE");
   // TFile *outputfile = new TFile("Outputfile_histograms_TTToSemileptonicMC2021_8Dec.root","RECREATE");
   // TFile *outputfile = new TFile("Outputfile_histograms_DYMC2021_8Dec_zeroE3x3removed.root","RECREATE");
   //TFile *outputfile = new TFile("Outputfile_histograms_DYMC2021_zeroE3x3removed_30Jan.root","RECREATE");
   TFile *outputfile = new TFile("Outputfile_histograms_DYMC2018_30Jan.root","RECREATE");
   for(int i=0;i<sizeof(histrange_min)/sizeof(histrange_min[0]);i++){
     std::cout<<histname[i]<<" profile histogram is being saved"<<std::endl;
     hprof[i]->Write();
   }
   for(int i=0;i<sizeof(hist_min)/sizeof(hist_min[0]);i++){
     std::cout<<hname[i]<<" histogram is being saved"<<std::endl;
     hist[i]->Write();
   }
   outputfile->Close();
}
