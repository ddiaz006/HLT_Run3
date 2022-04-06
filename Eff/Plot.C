#include <iostream>
#include "TString.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TText.h"
#include "TFile.h"
#include <stdio.h>
#include <fstream>
#include <cstdlib> /* mkdir */

#include <stdlib.h>     /* getenv */


void Plot(){

TString SampleName = "_GluGluToHHTo2B2Tau_node_cHHH1";
TFile *_file0 = TFile::Open("histograms"+SampleName+".root");
std::cout<<"open root file"<<std::endl;
TString outpath = "plots"+SampleName;
TString mdcommand = (TString)"mkdir -p "+outpath.Data();
const int dir_err = system(mdcommand);

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

 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 canvas->Clear();
 canvas->cd();
 TPad *pad1  = new TPad("pad1", "pad1", 0, 0, 1, 1);
 pad1->SetTickx();
 pad1->SetTicky();
 pad1->SetGrid();
 pad1->Draw();
 pad1->cd();
 gStyle->SetPalette(kBird);
 gStyle->SetLineWidth(2);

 TH1F* TTOCNum_PT[817];  
 TH1F* TTOCDen_PT[817];  
 TH1F* TTOCNum_Mass[817];  
 TH1F* TTOCDen_Mass[817];  
 TGraphAsymmErrors* gr_TTOC_PT[817]; //= new TGraphAsymmErrors();
 TGraphAsymmErrors* gr_TTOC_Mass[817]; //= new TGraphAsymmErrors();


 
 char titleNum[100];
 char titleDen[100];
 char histName[100];
 //Plot all PT Turn ons
 for (int k = 0; k<143; k++){
   //if(k >143) continue; //only for Triggers we care about
   // Pt Histos
   sprintf(titleNum,"h_PT[%d]_Num",k);
   sprintf(titleDen,"h_PT[%d]_Den",k);
   TTOCNum_PT[k] = (TH1F*)_file0->Get(titleNum)->Clone(titleNum);
   TTOCDen_PT[k] = (TH1F*)_file0->Get(titleDen)->Clone(titleDen);
   TGraphAsymmErrors* gr_TTOC_PT_ = new TGraphAsymmErrors(); 
   gr_TTOC_PT_->Divide(TTOCNum_PT[k], TTOCDen_PT[k], "cl=0.683 b(1,1) mode");
   gr_TTOC_PT[k] = gr_TTOC_PT_;
   
   // Mass Histos
   sprintf(titleNum,"h_Mass[%d]_Num",k);
   sprintf(titleDen,"h_Mass[%d]_Den",k);
   TTOCNum_Mass[k] = (TH1F*)_file0->Get(titleNum)->Clone(titleNum);
   TTOCDen_Mass[k] = (TH1F*)_file0->Get(titleDen)->Clone(titleDen);
   TGraphAsymmErrors* gr_TTOC_Mass_ = new TGraphAsymmErrors(); 
   gr_TTOC_Mass_->Divide(TTOCNum_Mass[k], TTOCDen_Mass[k], "cl=0.683 b(1,1) mode");
   gr_TTOC_Mass[k] = gr_TTOC_Mass_;
   

   //Plotting
   gr_TTOC_PT[k]->GetXaxis()->SetTitle("AK8JetPT GeV");
   gr_TTOC_PT[k]->SetTitle(name[k]);
   gr_TTOC_PT[k]->SetMaximum(1.0);
   gr_TTOC_Mass[k]->GetXaxis()->SetTitle("AK8JetSoftDropMass GeV");
   gr_TTOC_Mass[k]->SetTitle(name[k]);
   gr_TTOC_Mass[k]->SetMaximum(1.0);

   sprintf(histName,"Eff_PT[%d]",k);
   gr_TTOC_PT[k]->Draw();   
   canvas->SaveAs(outpath+"/"+histName+".pdf");
   canvas->Clear(); 
  
   sprintf(histName,"Eff_Mass[%d]",k);
   gr_TTOC_Mass[k]->Draw();   
   canvas->SaveAs(outpath+"/"+histName+".pdf");
   canvas->Clear(); 
 }


 //Special Plots
 TLegend *leg;
 leg = new TLegend(0.15,0.6,0.5,0.8);
 leg->SetBorderSize(0);
 leg->SetNColumns(1);
 leg->SetFillColor(kWhite);
 
 //AK8PFJet360, AllMasses
 gr_TTOC_PT[4]->SetLineColor(kBlue); 
 gr_TTOC_PT[13]->SetLineColor(kBlack); 
 gr_TTOC_PT[22]->SetLineColor(kGreen); 
 gr_TTOC_PT[0]->SetLineColor(kRed);
 leg->AddEntry(gr_TTOC_PT[4],  name[4],  "lpe");
 leg->AddEntry(gr_TTOC_PT[13], name[13], "lpe");
 leg->AddEntry(gr_TTOC_PT[22], name[22], "lpe");
 leg->AddEntry(gr_TTOC_PT[0],  name[0],  "lpe");
 gr_TTOC_PT[0]->SetTitle(name[4]);
 gr_TTOC_PT[4]->Draw(); //SD 30
 gr_TTOC_PT[13]->Draw("sames"); //SD 40
 gr_TTOC_PT[22]->Draw("sames"); //SD 50
 gr_TTOC_PT[0]->Draw("sames"); //Trim
 leg->Draw("sames");
 canvas->SaveAs("plots"+SampleName+"/1JPT360AllMass_compare.pdf");
 //canvas->Clear();
 leg->Clear();



 //AK8PFJet360, 30,30
 leg->AddEntry(gr_TTOC_PT[4],  name[4],  "lpe");
 leg->AddEntry(gr_TTOC_PT[0],  name[0],  "lpe");
 gr_TTOC_PT[0]->SetTitle(name[4]);
 gr_TTOC_PT[4]->Draw(); //SD 30
 gr_TTOC_PT[0]->Draw("sames"); //Trim
 leg->Draw("sames");
 canvas->SaveAs("plots"+SampleName+"/1JPT360Mass30-30_compare.pdf");
 //canvas->Clear();
 leg->Clear();


 //AK8PFJet360, 30,40
 leg->AddEntry(gr_TTOC_PT[13], name[13], "lpe");
 leg->AddEntry(gr_TTOC_PT[0],  name[0],  "lpe");
 gr_TTOC_PT[0]->SetTitle(name[13]);
 gr_TTOC_PT[13]->Draw(); //SD 40
 gr_TTOC_PT[0]->Draw("sames"); //Trim
 leg->Draw("sames");
 canvas->SaveAs("plots"+SampleName+"/1JPT360Mass30-40_compare.pdf");
 //canvas->Clear();
 leg->Clear();


 //AK8PFJet360, 30,50
 leg->AddEntry(gr_TTOC_PT[22], name[22], "lpe");
 leg->AddEntry(gr_TTOC_PT[0],  name[0],  "lpe");
 gr_TTOC_PT[0]->SetTitle(name[22]);
 gr_TTOC_PT[22]->Draw(); //SD 50
 gr_TTOC_PT[0]->Draw("sames"); //Trim
 leg->Draw("sames");
 canvas->SaveAs("plots"+SampleName+"/1JPT360Mass30-50_compare.pdf");
 //canvas->Clear();
 leg->Clear();








}
