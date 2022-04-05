#define TrigEff_cxx
#include "TrigEff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TrigEff::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   nentries = 10;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      std::cout<<"Event: "<<eventNum<<std::endl; 
      //for (int i = 0; i < 10; i++){
      //  std::cout <<"HLTDecision("<<i<<"): "<<HLTDecision->at(i)<<std::endl;
      //}
   }
}

