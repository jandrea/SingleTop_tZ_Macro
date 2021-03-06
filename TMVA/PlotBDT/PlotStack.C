#include "TString.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "THStack.h"


#include <iostream>



bool useDDTemplates = true;
bool applyDD = true;




bool PlotStack(TString varname, bool setlogy,  std::vector<TString> dataSample_list, 
	       std::vector<TString> mcSample_list, std::vector<TString > signalSample_list, std::vector<int> colorVector, std::vector<int> colorVectorSignal, std::vector< TString > dataDrivenTemplates_list){
  

  std::vector<double > sf_DY, sf_DY_err;  /*
  if(selection == "afterjetsel"){
    sf_DY.push_back(0.68); sf_DY_err.push_back(0.69);
    sf_DY.push_back(0.96); sf_DY_err.push_back(0.22);
    sf_DY.push_back(3.89); sf_DY_err.push_back(1.46);
    sf_DY.push_back(1.39); sf_DY_err.push_back(1.39);
  }else if (selection == "afterbjetsel"){
    sf_DY.push_back(0.77); sf_DY_err.push_back(0.64);
    sf_DY.push_back(0.97); sf_DY_err.push_back(0.21); 
    sf_DY.push_back(2.89); sf_DY_err.push_back(1.27);
    sf_DY.push_back(1.39); sf_DY_err.push_back(0.23); 
  
  }else{
    sf_DY.push_back(1.91); sf_DY_err.push_back(0.45);
    sf_DY.push_back(0.75); sf_DY_err.push_back(0.12); 
    sf_DY.push_back(1.22); sf_DY_err.push_back(0.35);
    sf_DY.push_back(1.14); sf_DY_err.push_back(0.13);
  }
  */
  
  std::vector<double > sf_WZ, sf_WZ_err;
  /*if(selection == "afterjetsel"){
    sf_WZ.push_back(1.04); sf_WZ_err.push_back(0.05);
    sf_WZ.push_back(0.90); sf_WZ_err.push_back(0.07);
    sf_WZ.push_back(0.69); sf_WZ_err.push_back(0.04);
    sf_WZ.push_back(1.20); sf_WZ_err.push_back(0.07);
  }else if (selection == "afterbjetsel"){
    sf_WZ.push_back(1.03); sf_WZ_err.push_back(0.05);
    sf_WZ.push_back(0.86); sf_WZ_err.push_back(0.07); 
    sf_WZ.push_back(0.70); sf_WZ_err.push_back(0.06);
    sf_WZ.push_back(1.17); sf_WZ_err.push_back(0.10); 
  
  }else{
    sf_WZ.push_back(1.01); sf_WZ_err.push_back(0.04);
    sf_WZ.push_back(0.87); sf_WZ_err.push_back(0.05); 
    sf_WZ.push_back(0.67); sf_WZ_err.push_back(0.04);
    sf_WZ.push_back(1.14); sf_WZ_err.push_back(0.07);
  }
  
  */
  
    sf_DY.push_back(1); sf_DY_err.push_back(0.69);
    sf_DY.push_back(1); sf_DY_err.push_back(0.22);
    sf_DY.push_back(1); sf_DY_err.push_back(1.46);
    sf_DY.push_back(1); sf_DY_err.push_back(1.39);
    sf_WZ.push_back(1); sf_WZ_err.push_back(0.05);
    sf_WZ.push_back(1); sf_WZ_err.push_back(0.07);
    sf_WZ.push_back(1); sf_WZ_err.push_back(0.04);
    sf_WZ.push_back(1); sf_WZ_err.push_back(0.07);
  
  
  
  TString filename;
  
  filename = "../TemplateRootFiles/"+varname+"_theta.root";
              
  
  Int_t stati=0;
  Bool_t  fit=1;
  
  
  //-----------------------------------
  //define the canvas 
  //-----------------------------------
  
  // For the canvas:
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0); // must be kWhite but I dunno how to do that in PyROOT
  gStyle->SetCanvasDefH(600); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas
  gStyle->SetCanvasDefX(0);   //POsition on screen
  gStyle->SetCanvasDefY(0);
  
  
  // For the Pad:
  gStyle->SetPadBorderMode(0);
  // ROOT . gStyle . SetPadBorderSize(Width_t size = 1);
  gStyle->SetPadColor(0); // kWhite
  gStyle->SetPadGridX(0); //false
  gStyle->SetPadGridY(0); //false
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  
  // For the frame:
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);
  
  // For the histo:
  // ROOT . gStyle . SetHistFillColor(1);
  // ROOT . gStyle . SetHistFillStyle(0);
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(1);
  // ROOT . gStyle . SetLegoInnerR(Float_t rad = 0.5);
  // ROOT . gStyle . SetNumberContours(Int_t number = 20);
  
  gStyle->SetEndErrorSize(2);
  //ROOT . gStyle . SetErrorMarker(20);   /// I COMMENTED THIS OUT
  //ROOT . gStyle . SetErrorX(0.);
  
  //ROOT . gStyle . SetMarkerStyle(20);
  
  
  //For the fit/function:
  gStyle->SetOptFit(1011);
  gStyle->SetFitFormat("5.4g");
  gStyle->SetFuncColor(2);
  gStyle->SetFuncStyle(1);
  gStyle->SetFuncWidth(1);
  
  //For the date:
  gStyle->SetOptDate(0);
  // ROOT . gStyle . SetDateX(Float_t x = 0.01);
  // ROOT . gStyle . SetDateY(Float_t y = 0.01);
  
  // For the statistics box:
  gStyle->SetOptFile(0);
  gStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  gStyle->SetStatColor(0); // kWhite
  gStyle->SetStatFont(42);
  //ROOT . gStyle . SetStatFontSize(0.025);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetStatTextColor(1);
  gStyle->SetStatFormat("6.4g");
  gStyle->SetStatBorderSize(1);
  gStyle->SetStatH(0.1);
  gStyle->SetStatW(0.15);
  
  // Margins:
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.16);
  //ROOT . gStyle . SetPadRightMargin(0.12);
  gStyle->SetPadRightMargin(0.03);
  
  // For the Global title:
  
  gStyle->SetOptTitle(0);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(10);
  gStyle->SetTitleFontSize(0.05);
  // ROOT . gStyle . SetTitleH(0); // Set the height of the title box
  // ROOT . gStyle . SetTitleW(0); // Set the width of the title box
  // ROOT . gStyle . SetTitleX(0); // Set the position of the title box
  // ROOT . gStyle . SetTitleY(0.985); // Set the position of the title box
  // ROOT . gStyle . SetTitleStyle(Style_t style = 1001);
  // ROOT . gStyle . SetTitleBorderSize(2);
  
  // For the axis titles:
  
  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  // ROOT . gStyle . SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // ROOT . gStyle . SetTitleYSize(Float_t size = 0.02);
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(1.25);
  // ROOT . gStyle . SetTitleOffset(1.1, "Y"); // Another way to set the Offset
  
  // For the axis labels:
  
  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");
  
  // For the axis:
  
  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(1); // kTRUE
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);
  
  // Change for log plots:
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);
  
  // Postscript options:
  gStyle->SetPaperSize(20.,20.);
  
  
  
  //TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);
  TCanvas *c1 = new TCanvas("c1","c1", 1000, 800);
  c1->SetBottomMargin(0.3);
  c1->SetLogy(setlogy);
  c1->cd();
  
  
  
  TFile * filechannel = new TFile(filename.Data());
  
  
  
  TH1F *histo_data = 0;
  std::vector<TH1F *> histo_mcSamples;  
  std::vector<TH1F *> histo_ddSamples;  
  std::vector<TH1F *> histo_mcSignal;  
  
  //---------------------------------------------
  //retrieve and add histograms
  //---------------------------------------------
  int niter_data = 0;
  int niter_chan  = 0;
  
    
  
    //--------------------
    //loop over datasamples
    //--------------------
    for(unsigned int idatasampl = 0; idatasampl< dataSample_list.size() ; idatasampl++){
      
      TString histo_Data_name   = varname+"__"+dataSample_list[idatasampl];
      cout << histo_Data_name << endl;
      if( niter_data == 0 && niter_chan == 0){
        histo_data = (TH1F*)filechannel->Get(histo_Data_name);
        if(varname == "mWT") histo_data->Rebin(5);
        if( histo_data== 0)  cout << "  no existing histo data with name  " << histo_Data_name  << endl;
      }
      else if(niter_data!=0) {
        TH1F * histo_tmp = (TH1F*)filechannel->Get(histo_Data_name);
        if(histo_tmp == 0)  cout << "  no existing histo data with name  " << histo_Data_name  << endl;
        if(varname == "mWT") histo_tmp->Rebin(5);
        histo_data->Add(histo_data, histo_tmp);
      }
      
      
      niter_data++;
    }
    
    
  
    
    //--------------------
    //loop over MC samples
    //--------------------
    for(unsigned int imc = 0; imc < mcSample_list.size(); imc++){
    
      TString histo_mc_name   = varname+"__"+ mcSample_list[imc];
      TH1F * histo_tmp = (TH1F*)filechannel->Get(histo_mc_name);
      
      if(histo_tmp == 0)  cout << "  no existing histo with name  " << histo_mc_name << endl;
	       
      histo_mcSamples.push_back(histo_tmp);
      
    }
    
    
    //-----------------------------
    //loop over data driven samples
    //-----------------------------
    for(unsigned int idd = 0; idd < dataDrivenTemplates_list.size(); idd++){
    
      TString histo_dd_name   = varname+"__"+ dataDrivenTemplates_list[idd];
      TH1F * histo_tmp = (TH1F*)filechannel->Get(histo_dd_name);
      if(varname == "mWT") histo_tmp->Rebin(5);
      if(histo_tmp == 0)  cout << "  no existing histo with name  " << histo_dd_name << endl;
        histo_ddSamples.push_back(histo_tmp);
      
        
    }
    
    
    
    //------------------------
    //loop over signal samples
    //------------------------
  
    for(unsigned int isign = 0; isign < signalSample_list.size(); isign++){
      TString histo_mc_name   = varname+"__"+ signalSample_list[isign];
      TH1F * histo_tmp = (TH1F*)filechannel->Get(histo_mc_name);
       histo_tmp->SetFillStyle(0);
       histo_tmp->SetFillColor(colorVectorSignal[isign]);
       histo_tmp->SetLineColor(colorVectorSignal[isign]);
       histo_tmp->SetLineWidth(2);
       histo_tmp->SetMarkerColor(colorVectorSignal[isign]);
      if(histo_tmp == 0)  cout << "  no existing histo with name  " << histo_mc_name << endl;
      histo_mcSignal.push_back(histo_tmp);
    }
  
  
  
  
  
  double nDY = 0;
  
  THStack *the_stack_histo= new THStack();
  for(unsigned int imc = 0; imc< histo_mcSamples.size(); imc++){
    
    histo_mcSamples[imc]->SetFillStyle(1001);
    histo_mcSamples[imc]->SetFillColor(colorVector[imc]);
    histo_mcSamples[imc]->SetLineColor(colorVector[imc]);
    if(imc < histo_mcSamples.size() && colorVector[imc] != colorVector[imc+1] )  histo_mcSamples[imc]->SetLineColor(1);
    if(imc ==  histo_mcSamples.size()) histo_mcSamples[imc]->SetLineColor(1);
    the_stack_histo->Add(histo_mcSamples[imc]);
  }  
  
  
  //---------------------------
  //include data driven templates
  //---------------------------
  
  
  the_stack_histo->Draw("h");
  the_stack_histo->GetXaxis()->SetLabelSize(0.0);
  if(histo_data->GetMaximum() > the_stack_histo->GetMaximum() ) the_stack_histo->SetMaximum(histo_data->GetMaximum()+0.3*histo_data->GetMaximum());
  else the_stack_histo->SetMaximum(the_stack_histo->GetMaximum()+0.3*the_stack_histo->GetMaximum());
  
  
  
  
  histo_data->SetMarkerStyle(20);
  histo_data->SetMarkerSize(1.2);
  histo_data->SetLineColor(1);
  histo_data->Draw("epsame");
  
  //--------------------------
  //MC systematic plot
  //--------------------------
  TH1F * histo_syst_MC   = (TH1F*)(the_stack_histo->GetHistogram() )->Clone();
  for(unsigned int imc=0; imc< histo_mcSamples.size(); imc++){
    histo_syst_MC->Add(histo_mcSamples[imc]);
  }
  
  
  //histo_syst_MC->Draw();
  //add here systematic uncertainties
  TGraphErrors *thegraph = new TGraphErrors(histo_syst_MC);
  thegraph->SetFillStyle(3005);
  thegraph->SetFillColor(1);
  thegraph->Draw("e2same");
  
   for(unsigned int isign = 0; isign< histo_mcSignal.size(); isign++)
     {	
	histo_mcSignal[isign]->Draw("hist e1 same");
     }      
  
  
  //-------------------
  //legend and captions
  //-------------------
  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.04);
  latex->SetTextAlign(31); 
  latex->DrawLatex(0.45, 0.95, "CMS Preliminary");
  
  
  
  TLatex *latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.04);
  latex2->SetTextAlign(31); 
  latex2->DrawLatex(0.87, 0.95, "19.7 fb^{-1} at #sqrt{s} = 8 TeV");
  
  TString info_data = "eee, #mu#mu#mu, e#mu#mu, ee#mu channels";
  if(varname == "MVA_mumumu") info_data = "#mu#mu#mu";
  if(varname == "MVA_mumue")  info_data = "#mu#mue";
  if(varname == "MVA_eemu")  info_data = "ee#mu";
  if(varname == "MVA_eee")    info_data = "eee";
  
  
  TLatex * text2 = new TLatex(0.45,0.98, info_data);
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.18);
  text2->SetY(0.92);
  //text2->SetLineWidth(2);
  text2->SetTextFont(42);
  text2->SetTextSize(0.0610687);
  //    text2->SetTextSizePixels(24);// dflt=28
  text2->Draw();
  
  
  TLegend* qw = 0;
  qw = new TLegend(.80,.60,.95,.90);

  qw->SetShadowColor(0);
  qw->SetFillColor(0);
  qw->SetLineColor(0);
  
  qw->AddEntry(histo_data,         "Data" ,                "ep");
  for(unsigned int i=0; i<mcSample_list.size(); i++){
    if(mcSample_list[i] == "tZq"       ) qw->AddEntry( histo_mcSamples[7],	"tZq"		 ,"f");
    if(mcSample_list[i] == "TT"        ) qw->AddEntry( histo_mcSamples[0],	"t#bar{t}"	 ,"f");
    if(mcSample_list[i] == "TTZ"       ) qw->AddEntry( histo_mcSamples[1],	"t#bar{t}V"	 ,"f");
    if(mcSample_list[i] == "Zjets"     ) qw->AddEntry( histo_mcSamples[6],	"DY"		 ,"f");
    if(mcSample_list[i] == "WZ"        ) qw->AddEntry( histo_mcSamples[3],	"VV"		 ,"f");
    if(mcSample_list[i] == "WZHF"        ) qw->AddEntry( histo_mcSamples[5],	"WZ+hf"		 ,"f");
  }
   
  for(unsigned int i=0; i<signalSample_list.size(); i++)
     {	
//	if(signalSample_list[i] == "FCNCzut"       ) qw->AddEntry( histo_mcSignal[0],       "FCNC Zut"               ,"lp");
	if(signalSample_list[i] == "FCNCzct"       ) qw->AddEntry( histo_mcSignal[0],       "FCNC Zct"               ,"lp");
     }
   
  /*
  mcSample_list.push_back("TT");            colorVector.push_back(kRed-7);
  mcSample_list.push_back("TTZ");           colorVector.push_back(kRed+1);
  mcSample_list.push_back("TTW");           colorVector.push_back(kRed+1);
  mcSample_list.push_back("WZ");            colorVector.push_back(13);
  mcSample_list.push_back("ZZ");            colorVector.push_back(13);
  mcSample_list.push_back("WZHF");            colorVector.push_back(12);
  mcSample_list.push_back("Zjets");         colorVector.push_back(kAzure-2);
  mcSample_list.push_back("tZq");           colorVector.push_back(kGreen+2);
  */
  
  
  
  qw->Draw();
  
  //--------------------------
  //Data over background ratio
  //--------------------------
  
   //TPad *canvas_2 = new TPad("canvas_2", "canvas_2",0,0.,1.0,0.34);
  TPad *canvas_2 = new TPad("canvas_2", "canvas_2", 0.0, 0.0, 1.0, 1.0);
  canvas_2->SetTopMargin(0.7);
  canvas_2->SetFillColor(0);
  canvas_2->SetFillStyle(0);
  canvas_2->SetGridy(1);
  canvas_2->Draw();
  canvas_2->cd(0);
  
  
  
  TH1F * histo_ratio_data = (TH1F*)histo_data->Clone();
  histo_ratio_data->Sumw2();
  histo_ratio_data->Divide(histo_syst_MC);
  
  //double theX[thegraph->GetN()] = thegraph->GetX();
  TGraphErrors *thegraph_tmp = (TGraphErrors*) thegraph->Clone();
  
  double *theErrorX  = thegraph_tmp->GetEX();
  double *theErrorY  = thegraph_tmp->GetEY();
  double *theY       = thegraph_tmp->GetY() ;
  for(int i=0; i<thegraph_tmp->GetN(); i++){
    theErrorY[i] = theErrorY[i]/theY[i];
    
    theY[i]=1;
  }
  
  
  TGraphErrors *thegraph_ratio = new TGraphErrors(thegraph_tmp->GetN(), thegraph_tmp->GetX() , theY ,  thegraph_tmp->GetEX(),     thegraph_tmp->GetEY() );
  thegraph_ratio->SetFillStyle(3005);
  thegraph_ratio->SetFillColor(1);
  if(varname == "InvM_ll") 	  histo_ratio_data->GetXaxis()->SetTitle("M_{ll} [GeV/c^{-1}]");
  else if(varname == "Njets")     histo_ratio_data->GetXaxis()->SetTitle("jet mult.");
  else if(varname == "NBjets")    histo_ratio_data->GetXaxis()->SetTitle("b-tagged jet mult.");
  else if(varname == "Met")	  histo_ratio_data->GetXaxis()->SetTitle("missing E_{T} [GeV]");
  histo_ratio_data->GetXaxis()->SetTitle("BDT");
  
  histo_ratio_data->SetMinimum(0.0);
  histo_ratio_data->SetMaximum(2.0);
  histo_ratio_data->GetXaxis()->SetTitleOffset(1.2);
  histo_ratio_data->GetXaxis()->SetLabelSize(0.04);
  histo_ratio_data->GetYaxis()->SetLabelSize(0.04);
  histo_ratio_data->GetYaxis()->SetNdivisions(6);
  histo_ratio_data->GetYaxis()->SetTitleSize(0.03);
  histo_ratio_data->Draw("E1X0");
  
  thegraph_ratio->Draw("e2same");
  
  TString end_name;
//  if(setlogy) end_name="_Logy.gif";
//  else end_name=".gif"; 
  if(setlogy) end_name="_Logy.eps";
  else end_name=".eps"; 

  TString outputname = "plots/"+varname+end_name;
 
  
  c1->SaveAs(outputname.Data());
  
  
  
}
