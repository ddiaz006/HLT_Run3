// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "HLT_Run3/ntuples/interface/lldjNtuple.h"

//// trigger fired variables
ULong64_t   AOD_HLT_DoubleEle33_;
//
//// trigger is prescaled variables
ULong64_t   AOD_HLT_DoubleEle33_isPS_;

void lldjNtuple::branchesAODTrigger(TTree* tree){
  tree->Branch("AOD_HLT_DoubleEle33",      &AOD_HLT_DoubleEle33_)     ;
//
//  //prescale
  tree->Branch("AOD_HLT_DoubleEle33_isPS",      &AOD_HLT_DoubleEle33_isPS_)      ;
}


void lldjNtuple::fillAODTrigger(const edm::Event &e, const edm::EventSetup &es){

  AOD_HLT_DoubleEle33_      = 0;
//
//  //prescale
  AOD_HLT_DoubleEle33_isPS_      = 0;

  if( !( e.getByToken(AODTriggerToken_, AODTriggerHandle_) && e.getByToken(AODTriggerEventToken_, AODTriggerEventHandle_) ) ){ return; }

  for(int i = 0; i < (int)hltConfig_.size(); i++){
    string name = hltConfig_.triggerName(i);
    //std::cout<<name<<"\n";

    // Double Electron
    int bitDoubleEle33 = -1;
    if      (name.find("HLT_DoubleEle33_CaloIdL_MW_v1")  != string::npos) bitDoubleEle33 = 0  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v2")  != string::npos) bitDoubleEle33 = 1  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v3")  != string::npos) bitDoubleEle33 = 2  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v4")  != string::npos) bitDoubleEle33 = 3  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v5")  != string::npos) bitDoubleEle33 = 4  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v6")  != string::npos) bitDoubleEle33 = 5  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v7")  != string::npos) bitDoubleEle33 = 6  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v8")  != string::npos) bitDoubleEle33 = 7  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v9")  != string::npos) bitDoubleEle33 = 8  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v10") != string::npos) bitDoubleEle33 = 9  ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v11") != string::npos) bitDoubleEle33 = 10 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v12") != string::npos) bitDoubleEle33 = 11 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v13") != string::npos) bitDoubleEle33 = 12 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v14") != string::npos) bitDoubleEle33 = 13 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v15") != string::npos) bitDoubleEle33 = 14 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v16") != string::npos) bitDoubleEle33 = 15 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v17") != string::npos) bitDoubleEle33 = 16 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v18") != string::npos) bitDoubleEle33 = 17 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v19") != string::npos) bitDoubleEle33 = 18 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v20") != string::npos) bitDoubleEle33 = 19 ;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v")   != string::npos) bitDoubleEle33 = 31 ;


    //printf(" Reading trigger: %s\n" , name.c_str()  );
    //printf(" bitEle23Loose      %d \n", bitEle23Loose      );
    //printf(" bitEle27Tight      %d \n", bitEle27Tight      );
    //printf(" bitEle17Ele12      %d \n", bitEle17Ele12      );
    //printf(" bitEle23Ele12      %d \n", bitEle23Ele12      );
    //printf(" bitIsoMu22         %d \n", bitIsoMu22         );
    //printf(" bitIsoTkMu22       %d \n", bitIsoTkMu22       );
    //printf(" bitMu17Mu8         %d \n", bitMu17Mu8         );
    //printf(" bitMu17TkMu8       %d \n", bitMu17TkMu8       );

    // indicates prescaling and whether trigger was fired or not
    unsigned int isPrescaled = (hltPrescale_.prescaleValue(e,es,name)) != 1;
    const unsigned int triggerIndex = hltConfig_.triggerIndex(name);
    unsigned int isFired     = AODTriggerHandle_->accept(triggerIndex);
    // if statement checks if trigger was present (any version XXX_vN)
    // set the bit N of our trigger variable to 1 or 0 based on isFired
    // DoubleEle
    if ( bitDoubleEle33           >= 0 ){
      AOD_HLT_DoubleEle33_            |= (isFired     << bitDoubleEle33      );
      AOD_HLT_DoubleEle33_isPS_       |= (isPrescaled << bitDoubleEle33      );
    }

  }//hltConfig loop

}//fillAODTrigger
