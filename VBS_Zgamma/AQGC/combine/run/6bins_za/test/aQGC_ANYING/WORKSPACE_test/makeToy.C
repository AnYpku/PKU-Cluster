#include "RooGlobalFunc.h"
#include "RooRealVar.h"
#include "RooProdPdf.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include "TH1.h"
#include "RooPlot.h"
#include "RooMsgService.h"
#include <map>
#include "RooStats/NumberCountingUtils.h"

#include "RooStats/HybridCalculator.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/HypoTestPlot.h"

#include "RooStats/ProfileLikelihoodTestStat.h"
#include "RooStats/SimpleLikelihoodRatioTestStat.h"
#include "RooStats/RatioOfProfiledLikelihoodsTestStat.h"
#include "RooStats/MaxLikelihoodEstimateTestStat.h"

#include "TMath.h"
#include "TRandom3.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TROOT.h"
#include "THStack.h"
#include "TString.h"
#include "TH1.h"
#include "TRandom.h"
#include "RooRealVar.h"
#include "RooExponential.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooAbsData.h"
#include "RooAbsRealLValue.h"
#include "RooAbsPdf.h"
#include "RooMinuit.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include <RooArgSet.h>
#include "RooDataHist.h"
#include "RooNLLVar.h"
#include "RooSimultaneous.h"
#include "RooExponential.h"
#include "RooGlobalFunc.h"
#include "RooCBShape.h"
#include "RooFormula.h"
#include "RooRandom.h"
#include "RooFitResult.h"
#include "RooProdPdf.h"
#include "RooProfileLL.h"
#include "RooLognormal.h"
#include "RooPoisson.h"
#include "RooProduct.h"
#include "RooAddition.h"
#include "RooBifurGauss.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "RobustMinimize.C"


using namespace std;
using namespace RooFit;
using namespace RooStats;

int printlevel = 0;
int robustprintlevel = -1; 


void makeSnapshot(TString wsname, TString mconfig, double true_value, double hypo_tested, TString poi_name_for_hypo, TString workspace_filename,TString outfile_name,TString parameter_var="", double value_parameter_var=0)
{

  ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit");
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(printlevel);
  
  if(robustprintlevel<0)
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;
 
  TFile *f_ws = TFile::Open(workspace_filename);
  
  RooWorkspace* ws = (RooWorkspace*)f_ws->Get(wsname); 
  ModelConfig* mc = (ModelConfig*)ws->obj(mconfig);
  RooProdPdf *pdf = (RooProdPdf *)ws->pdf("model_s");
  RooDataSet* data = (RooDataSet*)ws->data("data_obs");
                                                                                                                                                    
  RooRealVar *mR = 0; 
  if(parameter_var!="") {
    mR =  (RooRealVar*)ws->var(parameter_var);
    if(mR) {
      mR->setVal(value_parameter_var);
      mR->setConstant(1);
    }
    else {
      cout << parameter_var << " does not exist in workspace" << endl;
    }
  }

  RooRealVar* npbBSM = ws->var(poi_name_for_hypo);
  npbBSM->setConstant(1); 
  double npbBSM_val=true_value;
  npbBSM->setVal(npbBSM_val);

  const RooArgSet* globs_ptr = mc->GetGlobalObservables();
  TIterator* glob_itr = globs_ptr->createIterator();
  RooRealVar* glob_var;
  while ((glob_var = (RooRealVar*)glob_itr->Next())) {
    glob_var->setConstant(1);
  }
    
  const RooArgSet *np = mc->GetNuisanceParameters(); 
  TIterator* np_itr = np->createIterator();
  
  RooRealVar* np_var;
  while ((np_var = (RooRealVar*)np_itr->Next())) {
    TString name_of_nuisance = np_var->GetName(); 
  }
    
  npbBSM->setRange(-100,100);
  npbBSM->setConstant(1);
 
  RooAbsReal* nll  = pdf->createNLL(*data, Constrain(*mc->GetNuisanceParameters()), GlobalObservables(*mc->GetGlobalObservables()));
  nll->enableOffsetting(true);

  RooMinimizer* minim = new RooMinimizer(*nll);
  minim->setStrategy(1);
  minim->setPrintLevel(robustprintlevel);
  int  status = robustMinimize(*nll,*minim,robustprintlevel);
  
  if(robustprintlevel>-1)
    cout <<"First min : " <<  status << endl;

  if(status!=1)
    return ;

  np_itr->Reset();

  RooArgSet* poi_tmp = const_cast<RooArgSet*> (mc->GetParametersOfInterest());
  RooArgSet* poiAndNuisance = new RooArgSet();
  poiAndNuisance->add(ws->allVars());  
  poiAndNuisance->add( *((RooAbsCollection*)poi_tmp) ); 
  poiAndNuisance->writeToFile(outfile_name);
};

void makeToy(int init_toy, int n_toy, TString wsname, TString mconfig, double true_value, double hypo_tested, TString poi_name_for_hypo, TString workspace_filename, TString outfile_name,int save_np=0,double min_ghost=-999, double max_ghost=-999, double Nghost=100, TString parameter_var="", double value_parameter_var=0){

  ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit");
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(printlevel);
  gErrorIgnoreLevel =kError;
  int true_value_int = true_value*10.; // for file name
  TFile *f_ws = TFile::Open(workspace_filename);
 
  RooWorkspace* ws = (RooWorkspace*)f_ws->Get(wsname); 
  ModelConfig* mc = (ModelConfig*)ws->obj(mconfig);
  RooProdPdf *pdf = (RooProdPdf *)ws->pdf("model_s");
  RooDataSet* data = (RooDataSet*)ws->data("data_obs");

  if(robustprintlevel<0)  
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;
  
  TString nom_snapshot = outfile_name;
  nom_snapshot = nom_snapshot+TString::Itoa(init_toy,10)+".dat";
  makeSnapshot(wsname,mconfig,true_value,hypo_tested,poi_name_for_hypo,workspace_filename,nom_snapshot,parameter_var,value_parameter_var);
  if(robustprintlevel>-1)
    cout << "Reading from file "<< endl;
  ws->allVars().readFromFile(nom_snapshot);
                                                                                                                                                    
  RooRealVar *mR = 0; 
  if(parameter_var!="") {
    mR =  (RooRealVar*)ws->var(parameter_var);
    if(mR) {
      mR->setVal(value_parameter_var);
      mR->setConstant(1);
    }
    else {
      cout << parameter_var << " does not exist in workspace" << endl;
    }
  }

  /* Specific treatment for the workspace*/
  if(robustprintlevel>-1)
    cout << "Setting variable" << endl;

  if(robustprintlevel>-1)
    cout << "Reading variable" << endl;

  RooRealVar* PoiStudied = ws->var(poi_name_for_hypo); 

/*  
  if(parameter_var=="mResonance"||parameter_var=="lambda") {
    // for limit in function of mX or lambda the poi is a cross section   
    PoiStudied->setRange(-10,100);
  }
  else {
    // else poi is a mu (NR workspace) or lambda directly
    PoiStudied->setRange(-10,10);
  }
*/  
  PoiStudied->setRange(-100,100);
  PoiStudied->setVal(true_value);
  cout<<"set POI to true value: "<<true_value<<endl;	
  PoiStudied->setConstant(1);

  if(robustprintlevel>-1)
    cout << "Created Tree" << endl;

  double NLL_fixed, NLL_fixed2;
  double NLL_free; 
  double PLR, PoiStudied_free, PoiStudied_fix2, PoiStudied_fix;
  double tmu,tmutilde,qmu,qmutilde,q0;
  int status_free,status_fix,status_fix2;
  int Ntoy;

  TString filename;
  TString fin_fichier = ".root";
  filename = outfile_name+TString::Itoa(init_toy,10)+fin_fichier;
  TFile *fOutput = new TFile(filename,"RECREATE");
  fOutput->cd();

  TTree *t;
  t = new TTree("nll","nll");
  t->Branch("DataSet_TrueValue",&true_value,"DataSet_TrueValue/D");
  t->Branch("Ntoy",&Ntoy,"Ntoy/I");
  t->Branch("TestedValue",&hypo_tested,"TestedValue/D");
  t->Branch("NLL_fixed",&NLL_fixed,"NLL_fixed/D");
  t->Branch("NLL_fixed2",&NLL_fixed2,"NLL_fixed2/D");
  t->Branch("NLL_free",&NLL_free,"NLL_free/D");
  t->Branch("PLR",&PLR,"PLR/D");
  t->Branch("poiTested_free",&PoiStudied_free,"poiTested_free/D");
  t->Branch("poiTested_fix2",&PoiStudied_fix2,"poiTested_fix2/D");
  t->Branch("poiTested_fix",&PoiStudied_fix,"poiTested_fix/D");
  t->Branch("status_free",&status_free,"status_free/I");
  t->Branch("status_fix",&status_fix,"status_fix/I");
  t->Branch("status_fix2",&status_fix2,"status_fix2/I");

  t->Branch("tmu",&tmu,"tmu/D");
  t->Branch("tmutilde",&tmutilde,"tmutilde/D");
  t->Branch("qmu",&qmu,"qmu/D");
  t->Branch("qmutilde",&qmutilde,"qmutilde/D");
  t->Branch("q0",&q0,"q0/D");

  std::map<std::string, double> muMap;
  std::map<std::string, int> muConstMap;
  std::map<std::string, double> muErrorMap;
  
  const RooArgSet* poi_ptr = mc->GetParametersOfInterest();
  TIterator* poi_itr = poi_ptr->createIterator();
  for ( RooRealVar* v = (RooRealVar*)poi_itr->Next(); v!=0; v = (RooRealVar*)poi_itr->Next() ) {
    RooRealVar* realV = ws->var(v->GetName());
    muMap[std::string(v->GetName())+"FloatedFit"] = realV->getVal();
    muConstMap[std::string(v->GetName())+"FloatedFit_isConst"] = realV->isConstant() ? 1 : 0;
    t->Branch( (std::string(v->GetName())+"FloatedFit").c_str(), &(muMap[string(v->GetName())+"FloatedFit"]));
    t->Branch( (std::string(v->GetName())+"FloatedFit_isConst").c_str(), &(muConstMap[std::string(v->GetName())+"FloatedFit_isConst"]));
    t->Branch( (std::string(v->GetName())+"FloatedFit_Error").c_str(), &(muErrorMap[std::string(v->GetName())+"FloatedFit_Error"]));
    
    muMap[std::string(v->GetName())+"ConstantFit"] = realV->getVal();
    muConstMap[std::string(v->GetName())+"ConstantFit_isConst"] = realV->isConstant() ? 1 : 0;
    t->Branch( (std::string(v->GetName())+"ConstantFit").c_str(), &(muMap[string(v->GetName())+"ConstantFit"]));
    t->Branch( (std::string(v->GetName())+"ConstantFit_isConst").c_str(), &(muConstMap[std::string(v->GetName())+"ConstantFit_isConst"]));
    t->Branch( (std::string(v->GetName())+"ConstantFit_Error").c_str(), &(muErrorMap[std::string(v->GetName())+"ConstantFit_Error"]));

    muMap[std::string(v->GetName())+"Constant2Fit"] = realV->getVal();
    muConstMap[std::string(v->GetName())+"Constant2Fit_isConst"] = realV->isConstant() ? 1 : 0;
    t->Branch( (std::string(v->GetName())+"Constant2Fit").c_str(), &(muMap[string(v->GetName())+"Constant2Fit"]));
    t->Branch( (std::string(v->GetName())+"Constant2Fit_isConst").c_str(), &(muConstMap[std::string(v->GetName())+"Constant2Fit_isConst"]));
    t->Branch( (std::string(v->GetName())+"Constant2Fit_Error").c_str(), &(muErrorMap[std::string(v->GetName())+"Constant2Fit_Error"]));
  }
  
  const RooArgSet *nuisPar = mc->GetNuisanceParameters(); 
  TIterator *iter_nui = nuisPar -> createIterator();
  RooRealVar *parg_nui = NULL;
  
  while((parg_nui=(RooRealVar*)iter_nui->Next()) )
    {      
      if(save_np==1) {
	muMap[std::string(parg_nui->GetName())+"FloatedFit"] = parg_nui->getVal(); 
	muErrorMap[std::string(parg_nui->GetName())+"FloatedFit_Error"] = parg_nui->getError();
	muConstMap[std::string(parg_nui->GetName())+"FloatedFit_isConst"] = parg_nui->isConstant() ? 1 : 0;
	t->Branch( (std::string(parg_nui->GetName())+"FloatedFit").c_str(), &(muMap[std::string(parg_nui->GetName())+"FloatedFit"]));
	t->Branch( (std::string(parg_nui->GetName())+"FloatedFit_isConst").c_str(), &(muConstMap[std::string(parg_nui->GetName())+"FloatedFit_isConst"]));
	t->Branch( (std::string(parg_nui->GetName())+"FloatedFit_Error").c_str(), &(muErrorMap[std::string(parg_nui->GetName())+"FloatedFit_Error"]));
	
	muMap[std::string(parg_nui->GetName())+"ConstantFit"] = parg_nui->getVal(); 
	muErrorMap[std::string(parg_nui->GetName())+"ConstantFit_Error"] = parg_nui->getError();
	muConstMap[std::string(parg_nui->GetName())+"ConstantFit_isConst"] = parg_nui->isConstant() ? 1 : 0;
	t->Branch( (std::string(parg_nui->GetName())+"ConstantFit").c_str(), &(muMap[string(parg_nui->GetName())+"ConstantFit"]));
	t->Branch( (std::string(parg_nui->GetName())+"ConstantFit_isConst").c_str(), &(muConstMap[std::string(parg_nui->GetName())+"ConstantFit_isConst"]));
	t->Branch( (std::string(parg_nui->GetName())+"ConstantFit_Error").c_str(), &(muErrorMap[std::string(parg_nui->GetName())+"ConstantFit_Error"]));

	muMap[std::string(parg_nui->GetName())+"Constant2Fit"] = parg_nui->getVal(); 
	muErrorMap[std::string(parg_nui->GetName())+"Constant2Fit_Error"] = parg_nui->getError();
	muConstMap[std::string(parg_nui->GetName())+"Constant2Fit_isConst"] = parg_nui->isConstant() ? 1 : 0;
	t->Branch( (std::string(parg_nui->GetName())+"Constant2Fit").c_str(), &(muMap[string(parg_nui->GetName())+"Constant2Fit"]));
	t->Branch( (std::string(parg_nui->GetName())+"Constant2Fit_isConst").c_str(), &(muConstMap[std::string(parg_nui->GetName())+"Constant2Fit_isConst"]));
	t->Branch( (std::string(parg_nui->GetName())+"Constant2Fit_Error").c_str(), &(muErrorMap[std::string(parg_nui->GetName())+"Constant2Fit_Error"]));
      }
      const RooArgSet* globs_ptr = mc->GetGlobalObservables();
      TIterator *it_global = globs_ptr -> createIterator();
      RooRealVar* parg_global = NULL;
      while((parg_global=(RooRealVar*)it_global->Next()) )
	{
	  TString name_of_globs = parg_global->GetName(); 
	  parg_global->setVal(parg_nui->getVal()); 
	}
    }
  
  const RooArgSet* globs_ptr3 = mc->GetGlobalObservables();
  TIterator *it_global3 = globs_ptr3 -> createIterator();
  RooRealVar* parg_global3 = NULL;
  while((parg_global3=(RooRealVar*)it_global3->Next()) )
    {
      TString name_of_globs = parg_global3->GetName(); 
      if(save_np==1) {
	t->Branch( (std::string(parg_global3->GetName())+"").c_str(), &(muMap[std::string(parg_global3->GetName())+""]));
      }
    }

  if(robustprintlevel>-1)
    cout << "Save snapshot " << endl;

  const RooArgSet* nuisanceParameters_original_values = (RooArgSet*)(mc->GetNuisanceParameters())->snapshot();
  ws->saveSnapshot("nuisanceParameters_original_values",*nuisanceParameters_original_values); 
  const RooArgSet* GlobalObservables_original_values = (RooArgSet*)(mc->GetGlobalObservables())->snapshot();
  ws->saveSnapshot("GlobalObservables_original_values",*GlobalObservables_original_values);

  cout<<"Starting loop of toys"<<endl;
  //TString filename;
  //TString fin_fichier = ".root";
  //filename = outfile_name+TString::Itoa(init_toy,10)+fin_fichier;
  //TFile *fOutput = new TFile(filename,"RECREATE");
  //fOutput->cd();
    
  for (int i = init_toy; i<init_toy+n_toy; i++){
    if(robustprintlevel>-1)
      cout << "Toys :" << i << endl;
    Ntoy = i;

    if (i%10==0) cout<<"Toys: "<<i<<endl;

    TRandom3 *rndm3 = new TRandom3(i);
    ws->allVars().readFromFile(nom_snapshot);
    ws->loadSnapshot("GlobalObservables_original_values");

    if (i%10==0) cout<<"randomization of Gloabal vairalbes!"<<endl; 
    // Randomisation of the Global observable 
    // Important that the np is at MLEs
    const RooArgSet* globs_ptr = mc->GetGlobalObservables();
    TIterator *it_global2 = globs_ptr -> createIterator();
    RooRealVar* parg_global32 ;
    while((parg_global32=(RooRealVar*)it_global2->Next()) )      
      {	
	RooRealVar* parg_global2 = ws->var(parg_global32->GetName());	
	double mean_globs = parg_global32->getVal();
	TString name_of_globs = parg_global2->GetName();
	double r=0;
	r = rndm3->Gaus(mean_globs,1); 
	if( r < (-5+mean_globs)) r = -5+mean_globs;
	else if (r>(5+mean_globs)) r = 5+mean_globs; 
       	parg_global2->setConstant(kFALSE); 
	parg_global2->setVal(r);
	muMap[std::string(parg_global2->GetName())+""]=r;
      }

    ws->loadSnapshot("nuisanceParameters_original_values"); 
    RooRandom::randomGenerator()->SetSeed(i);
    PoiStudied->setVal(true_value);
    if (i%10==0)  cout<<"set POI to true value just before the toy generation: "<<true_value<<endl;	 
    PoiStudied->setConstant(1); 
    const RooArgSet* Observables = (RooArgSet*)mc->GetObservables(); 

    RooDataSet* toyData;

    toyData= pdf->generate(*Observables, 1);

    if (i==0) toyData->Write("toyData1");

    TIterator *iter_nui_release = nuisPar -> createIterator();
    RooRealVar* parg_nui_release = NULL;                                                                      
    TIterator *iter_global = globs_ptr -> createIterator();
    RooRealVar* parg_global = NULL;
    
    while((parg_nui_release=(RooRealVar*)iter_nui_release->Next()) )
      { parg_nui_release->setConstant(kFALSE);}
    while((parg_global=(RooRealVar*)iter_global->Next()) )
      { 
	RooRealVar* parg_global2 = ws->var(parg_global->GetName());	
	parg_global2->setConstant();
      }                                                                         
    
    /* Plot the pseudo_dataset*/
    PoiStudied->setVal(true_value); 
    PoiStudied->setConstant(0); 
 
 if (i%10==0) cout<<"1st fit"<<endl; 
    /* fit with the poi fix to 0*/
    //    ws->loadSnapshot("nuisanceParameters_original_values"); 
    PoiStudied->setVal(0); 
    PoiStudied->setConstant(1); 
    RooAbsReal* nll_fix  = pdf->createNLL(*toyData, CloneData(kFALSE),Constrain(*nuisPar));
    RooMinimizer* _minuit = new RooMinimizer(*nll_fix);
    _minuit->setPrintLevel(robustprintlevel);
    // fit
    status_fix = robustMinimize(*nll_fix,*_minuit,robustprintlevel);

    NLL_fixed = nll_fix->getVal();
    PoiStudied_fix = PoiStudied->getVal(); 

    /* Store the result of the constant fit*/
    poi_itr->Reset(); 
    for ( RooRealVar* v = (RooRealVar*)poi_itr->Next(); v!=0; v = (RooRealVar*)poi_itr->Next() ) {
      RooRealVar* realV = ws->var(v->GetName());
      muMap[std::string(v->GetName())+"ConstantFit"] = realV->getVal();
      muConstMap[std::string(v->GetName())+"ConstantFit_isConst"] = realV->isConstant() ? 1 : 0;
      muErrorMap[std::string(v->GetName())+"ConstantFit_Error"] = realV->getError();
    }   
    if(save_np==1) {      
      const RooArgSet * nuisPar = mc->GetNuisanceParameters();
      TIterator *iter_nui_release = nuisPar -> createIterator();
      RooRealVar* parg_nui_release36 = NULL ;
      while ((parg_nui_release36 = (RooRealVar*)iter_nui_release->Next())) {  
	RooRealVar* parg_nui_release = ws->var(parg_nui_release36->GetName());
	muMap[std::string(parg_nui_release->GetName())+"ConstantFit"] = parg_nui_release->getVal();
	muConstMap[std::string(parg_nui_release->GetName())+"ConstantFit_isConst"] = parg_nui_release->isConstant() ? 1 : 0;
	muErrorMap[std::string(parg_nui_release->GetName())+"ConstantFit_Error"] = parg_nui_release->getError();
      }
    }

 if (i%10==0) cout<<"2nd fit"<<endl;
    /* fit with the poi fix to the hypo*/
    //    ws->loadSnapshot("nuisanceParameters_original_values"); 
    PoiStudied->setVal(hypo_tested); 
    PoiStudied->setConstant(1); 
    RooAbsReal* nll_fix2  = pdf->createNLL(*toyData, CloneData(kFALSE),Constrain(*nuisPar));
    RooMinimizer* _minuit3 = new RooMinimizer(*nll_fix2);
    _minuit3->setPrintLevel(robustprintlevel);
    // fit
    status_fix2 = robustMinimize(*nll_fix2,*_minuit3,robustprintlevel);

    NLL_fixed2 = nll_fix2->getVal();
    PoiStudied_fix2 = PoiStudied->getVal();
    //PLR = 2*(NLL_fixed2-NLL_free);
    
    /* Store the result of the constant fit*/
    poi_itr->Reset(); 
    for ( RooRealVar* v = (RooRealVar*)poi_itr->Next(); v!=0; v = (RooRealVar*)poi_itr->Next() ) {
      RooRealVar* realV = ws->var(v->GetName());
      muMap[std::string(v->GetName())+"Constant2Fit"] = realV->getVal();
      muConstMap[std::string(v->GetName())+"Constant2Fit_isConst"] = realV->isConstant() ? 1 : 0;
      muErrorMap[std::string(v->GetName())+"Constant2Fit_Error"] = realV->getError();
    }   
    if(save_np==1) {
      const RooArgSet * nuisPar = mc->GetNuisanceParameters();
      TIterator *iter_nui_release = nuisPar -> createIterator();
      RooRealVar* parg_nui_release36 = NULL ;
      while ((parg_nui_release36 = (RooRealVar*)iter_nui_release->Next())) {  
	RooRealVar* parg_nui_release = ws->var(parg_nui_release36->GetName());
	muMap[std::string(parg_nui_release->GetName())+"Constant2Fit"] = parg_nui_release->getVal();
	muConstMap[std::string(parg_nui_release->GetName())+"Constant2Fit_isConst"] = parg_nui_release->isConstant() ? 1 : 0;
	muErrorMap[std::string(parg_nui_release->GetName())+"Constant2Fit_Error"] = parg_nui_release->getError();
      }
    }

 if (i%10==0) cout<<"3rd fit"<<endl;
    /* Free fit*/
    //    ws->loadSnapshot("nuisanceParameters_original_values"); 
    PoiStudied->setVal(true_value); 
    PoiStudied->setConstant(0); 
    RooAbsReal* nll_free  = pdf->createNLL(*toyData, CloneData(kFALSE),Constrain(*nuisPar)); 
    RooMinimizer* _minuit2 = new RooMinimizer(*nll_free);
    _minuit2->setPrintLevel(robustprintlevel);
    // fit
    status_free = robustMinimize(*nll_free,*_minuit2,robustprintlevel);
   
    PoiStudied->setRange(-100,100);
    
    NLL_free = nll_free->getVal();
    PoiStudied_free = PoiStudied->getVal(); 
  
    PLR = 2*(NLL_fixed2-NLL_free);
 
    /* Store the result of the floated fit*/
    poi_itr->Reset(); 
    for ( RooRealVar* v = (RooRealVar*)poi_itr->Next(); v!=0; v = (RooRealVar*)poi_itr->Next() ) {
      RooRealVar* realV = ws->var(v->GetName());
      muMap[std::string(v->GetName())+"FloatedFit"] = realV->getVal();
      muConstMap[std::string(v->GetName())+"FloatedFit_isConst"] = realV->isConstant() ? 1 : 0;
      muErrorMap[std::string(v->GetName())+"FloatedFit_Error"] = realV->getError();
    }   
    if(save_np==1) {
      const RooArgSet * nuisPar = mc->GetNuisanceParameters();
      TIterator *iter_nui_release = nuisPar -> createIterator();
      RooRealVar* parg_nui_release36 = NULL ;
      while ((parg_nui_release36 = (RooRealVar*)iter_nui_release->Next())) {  
	RooRealVar* parg_nui_release = ws->var(parg_nui_release36->GetName());
	muMap[std::string(parg_nui_release->GetName())+"FloatedFit"] = parg_nui_release->getVal();
	muConstMap[std::string(parg_nui_release->GetName())+"FloatedFit_isConst"] = parg_nui_release->isConstant() ? 1 : 0;
	muErrorMap[std::string(parg_nui_release->GetName())+"FloatedFit_Error"] = parg_nui_release->getError();
      }
    }

 if (i%10==0) cout<<"store information"<<endl;

    /* Compute Test*/
    tmu = 2*(NLL_fixed2-NLL_free);

    if( PoiStudied_free > 0)
      tmutilde = 2*(NLL_fixed2-NLL_free) ;
    else 
      tmutilde = 2*(NLL_fixed2-NLL_fixed) ;

    if( PoiStudied_free < hypo_tested)
      qmu = 2*(NLL_fixed2-NLL_free) ;
    else 
      qmu = 0;

    if( PoiStudied_free > 0)
      q0 = 2*(NLL_fixed2-NLL_free) ;
    else 
      q0 = -2*(NLL_fixed2-NLL_free);

    if( PoiStudied_free < 0)
      qmutilde = 2*(NLL_fixed2-NLL_fixed) ;
    else if(PoiStudied_free > 0 && PoiStudied_free<hypo_tested)
      qmutilde = 2*(NLL_fixed2-NLL_free) ;
    else
      qmutilde = 0;

 if (i%10==0) cout<<"Fill information"<<endl;

    t->Fill();
    delete toyData;
    delete nll_free; delete nll_fix; delete _minuit; delete _minuit2; delete _minuit3; 

 if (i%10==0) cout<<"end this toy"<<endl;

  }
  cout<<"end loop"<<endl;

  //TString filename; 
  //TString fin_fichier = ".root";
  //filename = outfile_name+TString::Itoa(init_toy,10)+fin_fichier;
  
  //TFile *fOutput = new TFile(filename,"RECREATE");
  //fOutput->cd(); 
  //    toyData->Write();
  t->Write(); 
  fOutput->Close(); 
  cout<<"file close!"<<endl;     
  
}

