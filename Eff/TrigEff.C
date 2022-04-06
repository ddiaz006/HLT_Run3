#define TrigEff_cxx
#include "TrigEff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iterator>
#include <map>
#include <iostream>

void TrigEff::Loop(std::map<int, std::vector<Bool_t>> &m_hlt, std::map<int, std::vector<Float_t>> &m_FatJetPT, std::map<int, std::vector<Float_t>> &m_FatJetMass)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   //nentries = 50;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      std::vector<Bool_t> v_hlt;
      for (int i = 0; i<1201; i++) v_hlt.push_back( HLTDecision[i] );
      m_hlt[eventNum] = v_hlt;

      std::vector<Float_t> v_FatJetPT;
      for (int i = 0; i<nFatJets; i++) v_FatJetPT.push_back( fatJetPt[i] );
      m_FatJetPT[eventNum] = v_FatJetPT;

      std::vector<Float_t> v_FatJetMass;
      for (int i = 0; i<nFatJets; i++) v_FatJetMass.push_back( fatJetSoftDropM[i] );
      m_FatJetMass[eventNum] = v_FatJetMass;

      //for (int i = 0; i < 1; i++){
      //  std::cout <<"HLTDecision("<<eventNum<<"): "<<HLTDecision[i]<<std::endl;
      //  std::cout <<"HLTDecision("<<eventNum<<"): "<<v_hlt[i]<<std::endl;
      //}
   //std::cout<<jentry<<"th Event"<<std::endl;
   if(jentry%1000 ==0)std::cout<<jentry<<"th Entry      Event: "<<eventNum<<std::endl;
   }
   //for (std::map<int, std::vector<Bool_t>>::iterator itr = m_hlt.begin(); itr != m_hlt.end(); ++itr) {
   //     for (int i = 0; i<50; i++){
   //     if ((itr->second)[i] !=0)std::cout<<i << '\t' << itr->first << '\t' << (itr->second)[i]
   //          << '\n';
   //     }
   // }
}

