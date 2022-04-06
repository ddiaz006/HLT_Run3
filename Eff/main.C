#include "TrigEff.h"
#include <TTree.h>
#include <TChain.h>
#include "TH1F.h"
#include "TH2F.h"

int main(){
//file="ntupleFromHLTX.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root"

TChain* chain = new TChain("ntuples/llp");
chain->Add("ntupleFromMiniAOD.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root");
TChain* chain_HLTX = new TChain("ntuples/llp");
chain_HLTX->Add("ntupleFromHLTX.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root");

TH1F* h_EffNum  = new TH1F("h_EffNum", "h_EffNum", 50, 0, 500) ;
TH1F* h_EffDen  = new TH1F("h_EffDen", "h_EffDen", 50, 0, 500) ;

std::map<int, std::vector<Bool_t>> m_hlt;
std::map<int, std::vector<Bool_t>> m_hlt_HLTX;

std::map<int, std::vector<Float_t>> m_FatJetPT;
std::map<int, std::vector<Float_t>> m_FatJetPT_HLTX;

std::map<int, std::vector<Float_t>> m_FatJetMass;
std::map<int, std::vector<Float_t>> m_FatJetMass_HLTX;

//Grab trigger Decisions/Pt/Mass
TrigEff T(chain_HLTX);
T.Loop(m_hlt_HLTX, m_FatJetPT_HLTX, m_FatJetMass_HLTX);
std::cout<<"Done with HLT loop"<<std::endl;

TrigEff U(chain);
U.Loop( m_hlt, m_FatJetPT, m_FatJetMass);

std::cout<<"Done with AOD loop"<<std::endl;
//Loop over Events
int k=1000;
for (std::map<int, std::vector<Bool_t>>::iterator itr = m_hlt_HLTX.begin(); itr != m_hlt_HLTX.end(); ++itr) {
   //std::cout<< "HLT: "<<itr->first <<std::endl;
   for(std::map<int, std::vector<Float_t>>::iterator jtr = m_FatJetPT.begin(); jtr != m_FatJetPT.end(); ++jtr) {
   //std::cout<< "HLT: "<<itr->first <<"  AOD: "<<jtr->first<<std::endl;
      if(itr->first == jtr->first){
         //Loop over triggers
         for (int i = 0; i<817; i++){
            //Loop over jets
            for(int j=0; j< (jtr->second).size(); j++){
              //std::cout<<(jtr->second).size()<<", "<<;
              std::cout<<"Trigger: "<<i << '\t'<<"Event: " << itr->first << '\t' << "Decision: "<<(itr->second)[i] << '\t' << "Pt: "<<(jtr->second)[j]<< '\n';
            }
         }
      }
   }
   //k++;
   //if(k>1) break;
}
//for (std::map<int, std::vector<Bool_t>>::iterator itr = m_hlt.begin(); itr != m_hlt.end(); ++itr) {
//     for (int i = 0; i<50; i++){
//     if ((itr->second)[i] !=0)std::cout<<i << '\t' << itr->first << '\t' << (itr->second)[i]
//          << '\n';
//     }
// }

std::cout<<"Done with Final Loop"<<std::endl;

return 0;
}
