#define TrigEff_cxx
#include "TrigEff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iterator>
#include <map>
#include <iostream>

void TrigEff::Loop()
{
   //std::map<int, Bool_t[1201]> m_hlt;
   std::map<int, std::vector<Bool_t>> m_hlt;
   //std::map<std::vector<Bool_t>, int> m_hlt;
   //std::map<int, Float_t[1000]> m_FatJetPT;
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   nentries = 50;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      std::vector<Bool_t> v_hlt;
      for (int i = 0; i<1201; i++) v_hlt.push_back( HLTDecision[i] );
      m_hlt[eventNum] = v_hlt;
      //m_hlt[eventNum] = HLTDecision;
      //m_hlt[v_hlt] = eventNum;
      for (int i = 0; i < 1; i++){
        std::cout <<"HLTDecision("<<eventNum<<"): "<<HLTDecision[i]<<std::endl;
        std::cout <<"HLTDecision("<<eventNum<<"): "<<v_hlt[i]<<std::endl;
        //std::cout <<"HLTDecision("<<eventNum<<"): "<<HLTDecision->at(i)<<std::endl;
      }
   }
   for (std::map<int, std::vector<Bool_t>>::iterator itr = m_hlt.begin(); itr != m_hlt.end(); ++itr) {
   //for (std::map<int, Bool_t[1201]>::iterator itr = m_hlt.begin(); itr != m_hlt.end(); ++itr) {
        for (int i = 0; i<50; i++){
        if ((itr->second)[i] !=0)std::cout<<i << '\t' << itr->first << '\t' << (itr->second)[i]
        //if ((itr->first)[i] !=0)std::cout << '\t' << (itr->first)[i] << '\t' << itr->second
             << '\n';
        }
    }
}

