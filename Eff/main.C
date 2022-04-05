#include "TrigEff.h"
#include <TTree.h>
#include <TChain.h>

int main(){
//file="ntupleFromHLTX.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root"

TChain* chain = new TChain("ntuples/llp");
chain->Add("ntupleFromMiniAOD.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root");
TChain* chain_HLTX = new TChain("ntuples/llp");
chain_HLTX->Add("ntupleFromHLTX.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root");



TrigEff T(chain);
T.Loop();


TrigEff U(chain_HLTX);
U.Loop();

return 0;
}
