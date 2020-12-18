#include "TGraphAsymmErrors.h"
#include "Riostream.h"
#include <vector>
#include <string>
#include "TROOT.h"
#include "TError.h"
#include "TFile.h"
#include "TCollection.h"
#include "TKey.h"
#include "EDBRHistoMaker.h"
#include "EDBRHistoPlotter.h"
#include "CMSTDRStyle.h"
#include "RoccoR.cc"
#include "TH2.h"
void loopPlot() {
	gErrorIgnoreLevel = kFatal; //suppresses all info messages

	setTDRStyle(); //TDR style

	//#####################EDIT THE OPTIONS##############################

	double lumiValue1 = 59.7;
	double lumiValue2 = 41.52;
	double lumiValue3 = 35.86;
	double lumiValue = 137.1;
	/// Should we scale the histograms to data?
	bool scaleToData = false;
	// Should we scale only wjets to make total MC = DATA?
	bool scaleOnlyWJets = false;
	/// Should we plot the Data/Bkg and Data-Bkg/Error ratios?
	bool makeRatio = true;
	/// Should we REDO histograms?
	bool redoHistograms = true;
	/// Should we put the signal MC stacked on top of the background (or just plot the signal alone)?
	bool isSignalStackOnBkg = false;
	bool dopileupreweight = false;

	// Path to wherever the files with the trees are. 
	vector<TString> pathToTrees = {"/home/pku/anying/cms/rootfiles/2016/","/home/pku/anying/cms/rootfiles/2017/","/home/pku/anying/cms/rootfiles/2018/"};
	std::string outputDir = "./fig-output_a/";
	RoccoR  rc;
        /// file for scale factors

// Setup names of data files for trees.
	const int nDATA = 6;
	std::cout << "set data imformation, we have " << nDATA << "data file"
			<< std::endl;
	std::string data[nDATA] = { "Muon16","Ele16","Muon17","Ele17","Muon18","Ele18"};
	std::vector < TString > fData;
	for (int j = 0; j< pathToTrees.size(); j++) {
		for (int ii = 0; ii < nDATA; ii++) {
                        if(ii<2) j=0;else if(ii>1 && ii<4) j=1; else if(ii>3&&ii<6)j=2;
			fData.push_back(pathToTrees[j] + "cutla-outD" + data[ii] + ".root");
		}
	}
	const int kk=fData.size();
	std::string dataLabels[kk] = { "Muon16","Ele16","Muon17","Ele17","Muon18","Ele18"};
	cout<<"Data size "<<fData.size()<<endl;
	// set mc imformation
	const int nMC = 21;//
	std::cout << "set data imformation, we have " << nMC << "mc file"
		<< std::endl;
	std::string mc[nMC] ={"ST16","TTA16","VV16","plj16_weight","plj16_weight_down","plj16_weight_up","ZA16",
		              "ST17","TTA17","VV17","plj17_weight","plj17_weight_down","plj17_weight_up","ZA17",
			      "ST18","TTA18","VV18","plj18_weight","plj18_weight_down","plj18_weight_up","ZA18" };
	std::vector< TString > fMC;
	for (int j = 0; j< pathToTrees.size(); j++) {
		for (int ii = 0; ii < nMC; ii++) {
                        if(ii<7) j=0;else if(ii>6 && ii<14) j=1; else if(ii>13&&ii<21)j=2;
			fMC.push_back(pathToTrees[j] +"cutla-out"+ mc[ii] + ".root");
		}
	}
	const int nmc=fMC.size();
	std::string mcLabels[nmc] ={"ST16","TTA16","VV16","plj16_weight","plj16_weight_down","plj16_weight_up","ZA16",
		                    "ST17","TTA17","VV17","plj17_weight","plj17_weight_down","plj17_weight_up","ZA17",
				    "ST18","TTA18","VV18","plj18_weight","plj18_weight_down","plj18_weight_up","ZA18"};
	double kFactorsMC_array[nmc] ={1,1,1,1,1,1,1,
		                       1,1,1,1,1,1,1,
				       1,1,1,1,1,1,1};
	cout<<"MC size "<<fMC.size()<<endl;
	std::vector<double> kFactorsMC;
	for (int index = 0; index < nmc; index++) {
		kFactorsMC.push_back(kFactorsMC_array[index]);
	}
	// set mcsig information
	const int nMCSig = 6;
	std::cout << "set data imformation, we have " << nMCSig << "mcsig file"
		<< std::endl;
	std::string mcSig[nMCSig] = { "ZA-EWK16","ZA-EWK_interf16","ZA-EWK17","ZA-EWK_interf17","ZA-EWK18","ZA-EWK_interf18"};
	std::vector < TString > fMCSig;
	for (int j = 0; j< pathToTrees.size(); j++) {
		for (int ii = 0; ii < nMCSig; ii++) {
			if(ii==0||ii==1)j=0;else if(ii==2||ii==3)j=1;else if(ii==4||ii==5)j=2;
			fMCSig.push_back(pathToTrees[j] + "cutla-out" + mcSig[ii] + ".root");
		}
	}
	cout<<"MC Sig size "<<fMCSig.size()<<endl;
	const int nmcsig=fMCSig.size();
	std::string mcLabelsSig[nmcsig] = { "ZA-EWK16","ZA-EWK_interf16","ZA-EWK17","ZA-EWK_interf17","ZA-EWK18","ZA-EWK_interf18"};
	double kFactorsSig_array[nmcsig] = {1,1,1,1,1,1};
	std::vector<double> kFactorsMCSig;
	for (int index = 0; index < nmcsig; index++) {
		kFactorsMCSig.push_back(kFactorsSig_array[index]);
	}

	std::cout << "set data mc mcsig Jet information done" << std::endl;

	std::vector < std::string > fHistosData;
	std::vector < std::string > fHistosMC;
	std::vector < std::string > fHistosMCSig;

	char buffer[256], out_buffer[256];
	printf("All strings set\n");

	/// ----------------------------------------------------------------
	/// This first part is the loop over trees to create histogram files 
	/// ----------------------------------------------------------------


	printf("\nStart making histograms\n\n");

	//loop over data files and make histograms individually for each of them
	TH1F* hisRatio = 0;

	for (int i = 0; i < fData.size(); i++) {
		continue;
		std::cout << "\n-------\nRunning over " << dataLabels[i].c_str()
			<< std::endl;
		std::cout << "The file is " << fData.at(i) << std::endl; 
		TString tag,sample;
		if(fData.at(i).Contains("2016")) {tag="16";rc.init("RoccoR2016.txt"); }
		if(fData.at(i).Contains("2017")) {tag="17";rc.init("RoccoR2017.txt"); }
		if(fData.at(i).Contains("2018")) {tag="18";rc.init("RoccoR2018.txt"); }
		sprintf(buffer, "./histos_%s.root", dataLabels[i].c_str());
		sprintf(out_buffer, "./optimal_%s.root", dataLabels[i].c_str());
		fHistosData.push_back(buffer);

		std::cout << "retrieve "<<i+1<<"th data file" << std::endl;
		TFile *fileData = TFile::Open(fData.at(i));
		TTree *treeData = (TTree*) fileData->Get("ZPKUCandidates");
		std::cout << "retrieve ith mc file" << std::endl;
		if (redoHistograms) {
			EDBRHistoMaker* maker = new EDBRHistoMaker(treeData, fileData,
					hisRatio, out_buffer, &rc);
			maker->setUnitaryWeights(true);
			maker->Loop(buffer);
			maker->endjob();
			fileData->Close();
		}

	}  //end loop on data files
	printf("Loop over data done\n");



	//loop over MC files and make histograms individually for each of them
	for (int i = 0; i < fMC.size(); i++) {
//		continue;
		std::cout << "\n-------\nRunning over " << mcLabels[i].c_str()
			<< std::endl;
		std::cout << "The file is " << fMC.at(i) << std::endl;
		TString tag;
		if(fMC.at(i).Contains("2016")) {tag="16";rc.init("RoccoR2016.txt"); }
		if(fMC.at(i).Contains("2017")) {tag="17";rc.init("RoccoR2017.txt"); }
		if(fMC.at(i).Contains("2018")) {tag="18";rc.init("RoccoR2018.txt"); }
		sprintf(buffer, "./histos_%s.root",mcLabels[i].c_str());
		sprintf(out_buffer, "./optimal_%s.root",mcLabels[i].c_str());
		fHistosMC.push_back(buffer);
		std::cout << "test" << std::endl;

		if (redoHistograms) {
			std::cout << "retrieve ith mc file" << std::endl;
			TFile *fileMC = TFile::Open(fMC.at(i));
			std::cout << "retrieve tree of mc file" << std::endl;
			TTree *treeMC = (TTree*) fileMC->Get("ZPKUCandidates");
			EDBRHistoMaker* maker = new EDBRHistoMaker(treeMC, fileMC,
					hisRatio, out_buffer, &rc);
			maker->setUnitaryWeights(false);
			maker->Loop_SFs_mc(buffer);
			maker->endjob();
			fileMC->Close();
		}

	}  //end loop on MC files

	printf("Loop over MC done\n");

	//loop over MC signal files and make histograms individually for each of them
	for (int  i = 0; i < fMCSig.size(); i++) {
//		continue;
		std::cout << "\n-------\nRunning over " << mcLabelsSig[i].c_str()
			<< std::endl;
		std::cout << "The file is " << fMCSig.at(i) << std::endl;
		TString tag;
		if(fMCSig.at(i).Contains("2016")) {tag="16";rc.init("RoccoR2016.txt"); }
		if(fMCSig.at(i).Contains("2017")) {tag="17";rc.init("RoccoR2017.txt"); }
		if(fMCSig.at(i).Contains("2018")) {tag="18";rc.init("RoccoR2018.txt"); }
		sprintf(buffer, "./histos_%s.root",mcLabelsSig[i].c_str());
		sprintf(out_buffer, "./optimal_%s.root",mcLabelsSig[i].c_str());
		fHistosMCSig.push_back(buffer);

		if (redoHistograms) {
			std::cout << "retrieve ith mcsig file" << std::endl;
			TFile *fileMCSig = TFile::Open(fMCSig.at(i));
			std::cout << "retrieve tree of mcsig file" << std::endl;
			TTree *treeMCSig = (TTree*) fileMCSig->Get("ZPKUCandidates");
			std::cout<<"open MC sig file OK"<<endl;
			EDBRHistoMaker* maker = new EDBRHistoMaker(treeMCSig, fileMCSig,
					hisRatio, out_buffer,&rc);
			maker->setUnitaryWeights(false);
			maker->Loop_SFs_mc(buffer);
			maker->endjob();
			fileMCSig->Close();
		}
	}  //end loop on MC files

	/// ------------------------------------------------------------------
	/// This second part is the loop over histograms to create stack plots
	/// ------------------------------------------------------------------  
	//	printf("\nStart looping over histograms\n\n");
	//	//make nice plots
	//	std::vector < std::string > listOfHistos;
	//	if (nMC > 0) {
	//		// Open one of the histogram files just to get the list of histograms
	//		// produced, then loop over all the histograms inheriting 
	//		// from TH1 contained in the file.
	//		sprintf(buffer, "./output-slimmed-rootfiles/histos_%s.root", mcLabels[0].c_str());
	//		std::cout << "Opening " << buffer << std::endl;
	//		TFile* oneFile = TFile::Open(buffer);
	//		TIter next(oneFile->GetListOfKeys());
	//		TKey *key;
	//		while ((key = (TKey*) next())) {
	//			TClass *cl = gROOT->GetClass(key->GetClassName());
	//			if (!cl->InheritsFrom("TH1"))
	//				continue;
	//			TH1 *hTMP = (TH1*) key->ReadObj();
	//			std::string hName = hTMP->GetName();
	//			printf("Histogram found: %s\n", hName.c_str());
	//			listOfHistos.push_back(hName);
	//		}      //end while loop
	//		oneFile->Close();
	//	}      //end if fmc size >0
	//
	//	std::cout << "Creating plotter" << std::endl;
	//	EDBRHistoPlotter *plotter = new EDBRHistoPlotter("./", fHistosData,
	//			fHistosMC, fHistosMCSig,/* mc2Labels,*/ lumiValue, scaleToData, scaleOnlyWJets,
	//			makeRatio, isSignalStackOnBkg, kFactorsMC, kFactorsMCSig);
	//	std::cout << "Set output dir" << std::endl;
	//	plotter->setOutDir(outputDir);
	//	plotter->setDebug(false);
	//
	//	//colors are assigned in the same order of mcLabels
	//	// For ZZ
	//	////// {DYJetsToLL_HT-200to400,DYJetsToLL_HT-200to400,DYJetsToLL_HT-600toInf}
	//	std::vector<int> fColorsMC;
	//
	///*	fColorsMC.push_back(kGreen-6);
	//	fColorsMC.push_back(kGreen-10);
	//	fColorsMC.push_back(kBlue-7);
	//	fColorsMC.push_back(kBlue-9);
	//	fColorsMC.push_back(kOrange);
	//	fColorsMC.push_back(kRed-4);*/
	//
	//	fColorsMC.push_back(kGreen-4);
	//	fColorsMC.push_back(kGreen-4);
	//	fColorsMC.push_back(kGreen-4);
	//	fColorsMC.push_back(kGreen-10);
	//	fColorsMC.push_back(kGreen-10);
	//	fColorsMC.push_back(kGreen-10);
	//	fColorsMC.push_back(kBlue-4);
	//	fColorsMC.push_back(kBlue-4);
	//	fColorsMC.push_back(kBlue-4);
	//	fColorsMC.push_back(kBlue-7);
	//	fColorsMC.push_back(kBlue-7);
	//	fColorsMC.push_back(kBlue-7);
	//	fColorsMC.push_back(kOrange-2);
	//	fColorsMC.push_back(kOrange-2);
	//	fColorsMC.push_back(kOrange-2);
	//	fColorsMC.push_back(kRed-7);
	//	fColorsMC.push_back(kRed-7);
	//	fColorsMC.push_back(kRed-7);
	//
	///*	fColorsMC.push_back(kGreen-7);
	//	fColorsMC.push_back(kGreen-8);
	//	fColorsMC.push_back(kBlue-5);
	//	fColorsMC.push_back(kBlue-10);
	//	fColorsMC.push_back(kOrange-3);
	//	fColorsMC.push_back(kRed-9);*/
	//
	//	std::vector<int> fColorsMCSig;
	//	fColorsMCSig.push_back(kRed);
	//	fColorsMCSig.push_back(kBlue + 3);
	//
	//	plotter->setFillColor(fColorsMC);
	//	plotter->setLineColor(fColorsMCSig);
	//
	//	int numOfHistos = listOfHistos.size();
	//	for (int i = 0; i != numOfHistos; ++i)
	//		plotter->makeStackPlots(listOfHistos.at(i));
	//	printf("Plotting done\n");
	//	delete plotter;
}

int main() {
	loopPlot();
	return 0;
}

