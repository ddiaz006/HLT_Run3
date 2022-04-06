#include "TrigEff.h"
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include "TH1F.h"
#include "TH2F.h"
#include <fstream>

int main(){

TChain* chain = new TChain("ntuples/llp");
TChain* chain_HLTX = new TChain("ntuples/llp");

// CHANGE SAMPLES HERE
chain->Add("ntupleFromMiniAOD.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root");
chain_HLTX->Add("ntupleFromHLTX.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root");
TString SampleName = "_GluGluToHHTo2B2Tau_node_cHHH1";

TString name[817];
std::fstream names;
names.open("trigger_names_llp_ForRun3HLTStudy.txt", std::fstream::in);
int n = 0;
if (names.is_open()) {
            TString x;
            while (!names.eof()) {
                names>>x;
                name[n] = x;
                n++;
            }
}
names.close();

TH1F* h_NumPT[817];
TH1F* h_DenPT[817];
TH1F* h_NumMass[817];
TH1F* h_DenMass[817];

char titleNum[100];
char titleDen[100];
for (int k = 0; k<817; k++){
   sprintf(titleNum,"h_PT[%d]_Num",k);
   sprintf(titleDen,"h_PT[%d]_Den",k);
   h_NumPT[k] = new TH1F(titleNum, name[k]+"_Num", 50, 0, 800);
   h_DenPT[k] = new TH1F(titleDen, name[k]+"_Den", 50, 0, 800);
   
   sprintf(titleNum,"h_Mass[%d]_Num",k);
   sprintf(titleDen,"h_Mass[%d]_Den",k);
   h_NumMass[k] = new TH1F(titleNum, name[k]+"_Num", 10, 0, 200);
   h_DenMass[k] = new TH1F(titleDen, name[k]+"_Den", 10, 0, 200);
}


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
for (std::map<int, std::vector<Bool_t>>::iterator itr = m_hlt_HLTX.begin(); itr != m_hlt_HLTX.end(); ++itr) {
      auto jtr = m_FatJetPT.find(itr->first) ;
      auto mtr = m_FatJetMass.find(itr->first) ;
      if( jtr != m_FatJetPT.end() ){
         //Loop over triggers
         for (int i = 0; i<817; i++){
            //Loop over jets
            for(int j=0; j< (jtr->second).size(); j++){
              if( (itr->second)[i] ) {
                h_NumPT[i]  ->Fill( (jtr->second)[j] );
                h_NumMass[i]->Fill( (mtr->second)[j] );
              } 
              h_DenPT[i]  ->Fill( (jtr->second)[j] );
              h_DenMass[i]->Fill( (mtr->second)[j] );
            }
         }
   }
}
////for (std::map<int, std::vector<Bool_t>>::iterator itr = m_hlt.begin(); itr != m_hlt.end(); ++itr) {
////     for (int i = 0; i<50; i++){
////     if ((itr->second)[i] !=0)std::cout<<i << '\t' << itr->first << '\t' << (itr->second)[i]
////          << '\n';
////     }
//// }
TFile *f = TFile::Open("histograms"+SampleName+".root", "recreate");
f->cd();
for (int k = 0; k<817; k++){
   h_NumPT[k]->Write();
   h_DenPT[k]->Write();
   h_NumMass[k]->Write();
   h_DenMass[k]->Write();
}
f->Close();

std::cout<<"Done with Final Loop"<<std::endl;

return 0;
}
