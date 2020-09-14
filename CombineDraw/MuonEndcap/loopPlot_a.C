#include "TGraphAsymmErrors.h"
#include "Riostream.h"
#include <vector>
#include <string>
#include "TROOT.h"
#include "TError.h"
#include "TFile.h"
#include "TCollection.h"
#include "TKey.h"
#include "EDBRHistoMaker_a.h"
#include "EDBRHistoPlotter.h"
#include "test.C"
#include "CMSTDRStyle.h"
#include "RoccoR.cc"
#include "Scale_jet_with_fakerate.C"
#include "TH2.h"
void loopPlot() {
	gErrorIgnoreLevel = kFatal; //suppresses all info messages

	setTDRStyle(); //TDR style

	//#####################EDIT THE OPTIONS##############################

	double lumiValue1 = 58.7;
	double lumiValue2 = 41.52;
	double lumiValue3 = 35.9;
	double lumiValue = lumiValue1+lumiValue2+lumiValue3;
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

	/// Path to wherever the files with the trees are. 
	//std::string pathToTrees = "./output-slimmed-rootfiles/root/";
	std::string pathToTrees = "../ScalSeq/rootfiles/";
	std::string outputDir = "./fig-output_a/";
	
//	RoccoR  rc("./RoccoR2017.txt");
        /// file for scale factors

// Setup names of data files for trees.
	const int nDATA = 3;
	std::cout << "set data imformation, we have " << nDATA << "data file"
			<< std::endl;
	std::string dataLabels[nDATA] = { "2018_Muon","2017_Muon17","2016_DMuon16" };
	std::vector < std::string > fData;
	for (int ii = 0; ii < nDATA; ii++) {
		fData.push_back(pathToTrees + "optimal_" + dataLabels[ii] + ".root");
	}
// set mc imformation
		const int nMC = 18;
		std::cout << "set data imformation, we have " << nMC << "mc file"
				<< std::endl;
		//std::string mcLabels[nMC] = { "ZJets_FX", "ZA" };
		//std::string mcLabels[nMC] = {"ST","TTA","VV","WA", "ZJets_FX","WJets_FX","TTJets_FX","ZA" };
		//double kFactorsMC_array[nMC] = { lumiValue,lumiValue,lumiValue,lumiValue,lumiValue,lumiValue,lumiValue,lumiValue};
std::string mcLabels[nMC] ={"2018_ST","2017_ST","2016_ST","2018_TTA","2017_TTA","2016_TTA","2018_VV","2017_VV","2016_VV","2018_WA","2017_WA","2016_WA","2018_plj_muendcap","2017_plj_muendcap","2016_plj_muendcap","2018_ZA","2017_ZA","2016_ZA"};
 double kFactorsMC_array[nMC+1] ={lumiValue1,lumiValue2,lumiValue3,lumiValue1,lumiValue2,lumiValue3,lumiValue1,lumiValue2,lumiValue3,
	                          lumiValue1,lumiValue2,lumiValue3,1,1,1,
	                          lumiValue1,lumiValue2,lumiValue3};
//		std::string mcLabels[nMC] = {"2018_ST", "2018_TTA", "2018_VV","2018_WA","2018_plj_mubarrel","2018_ZA",
//			"2017_ST", "2017_TTA", "2017_VV","2017_WA","2017_plj_mubarrel","2017_ZA",
//			"2016_ST", "2016_TTA", "2016_VV","2016_WA","2016_plj_mubarrel","2016_ZA", };//,"Contamination_ZA"};
//		double kFactorsMC_array[nMC+1] = { lumiValue1,lumiValue1,lumiValue1,lumiValue1,1,lumiValue1,
//                                                   lumiValue2,lumiValue2,lumiValue2,lumiValue2,1,lumiValue2,
//						   lumiValue3,lumiValue3,lumiValue3,lumiValue3,1,lumiValue3};
                /*const int nMC2 = 1;      
                std::string mc2Labels =  "Contamination_ZA" ;*/
		std::vector< std::string > fMC;
		for (int ii = 0; ii < nMC; ii++) {
			fMC.push_back(pathToTrees +"optimal_"+ mcLabels[ii] + ".root");
		}
		std::vector<double> kFactorsMC;
		for (int index = 0; index < nMC; index++) {
			kFactorsMC.push_back(kFactorsMC_array[index]);
		}
                std::string ll[6] ={"ST", "TTA", "VV","WA",
			"plj_mubarrel","ZA"}; 
                std::vector<std::string> mcTotalLabels;
                for (int index = 0; index < 6; index++) {
                        mcTotalLabels.push_back(ll[index]);
                }

// set mcsig information
	const int nMCSig = 3;
	std::cout << "set data imformation, we have " << nMCSig << "mcsig file"
			<< std::endl;
	std::string mcLabelsSig[nMCSig] = { "2018_ZA-EWK","2017_ZA-EWK","2016_ZA-EWK" };
	double kFactorsSig_array[nMCSig] = { lumiValue1,lumiValue2,lumiValue3};
	std::vector < std::string > fMCSig;
	for (int ii = 0; ii < nMCSig; ii++) {
		fMCSig.push_back(pathToTrees + "optimal_" + mcLabelsSig[ii] + ".root");
	}
	std::vector<double> kFactorsMCSig;
	for (int index = 0; index < nMCSig; index++) {
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

	for (int i = 0; i < nDATA; i++) {
                //continue;
		std::cout << "\n-------\nRunning over " << dataLabels[i].c_str()
				<< std::endl;
		std::cout << "The file is " << fData.at(i) << std::endl; //fData.push_back(pathToTrees + dataLabels[ii] + ".root");
		sprintf(buffer, "./output-slimmed-rootfiles/histos_%s.root", dataLabels[i].c_str());
		sprintf(out_buffer, "./output-slimmed-rootfiles/optimal_CR_%s.root", dataLabels[i].c_str());
		fHistosData.push_back(buffer);

		std::cout << "retrieve "<<i+1<<"th data file" << std::endl;
		TFile *fileData = TFile::Open(fData.at(i).c_str());
//		TTree *treeData = (TTree*) fileData->Get("demo");
		TTree *treeData = (TTree*) fileData->Get("outtree");
		//TFile *fileMC = TFile::Open(fMC.at(i).c_str());
		//TTree *treeMC = (TTree*) fileMC->Get("demo");
		std::cout << "retrieve ith mc file" << std::endl;
		/*if (dopileupreweight) {
			hisRatio = test(treeData, treeMC);
			std::cout << "hisRatio" << std::endl;
		}*/
		if (redoHistograms) {
//			EDBRHistoMaker* maker = new EDBRHistoMaker(treeData, fileData,
//					hisRatio, out_buffer, &rc);
		EDBRHistoMaker* maker = new EDBRHistoMaker(treeData, fileData,
					hisRatio, out_buffer);
			maker->setUnitaryWeights(true);
			maker->Loop(buffer);
			maker->endjob();
			fileData->Close();
		}

	}  //end loop on data files
	printf("Loop over data done\n");



	//loop over MC files and make histograms individually for each of them
	for (int i = 0; i < nMC; i++) {
		//continue;
		std::cout << "\n-------\nRunning over " << mcLabels[i].c_str()
				<< std::endl;
		std::cout << "The file is " << fMC.at(i) << std::endl;
		sprintf(buffer, "./output-slimmed-rootfiles/histos_%s.root", mcLabels[i].c_str());
		sprintf(out_buffer, "./output-slimmed-rootfiles/optimal_CR_%s.root", mcLabels[i].c_str());
		fHistosMC.push_back(buffer);
		std::cout << "test" << std::endl;

		if (redoHistograms) {
			std::cout << "retrieve ith mc file" << std::endl;
			TFile *fileMC = TFile::Open(fMC.at(i).c_str());
			std::cout << "retrieve tree of mc file" << std::endl;
//			TTree *treeMC = (TTree*) fileMC->Get("demo");
			TTree *treeMC = (TTree*) fileMC->Get("outtree");
			EDBRHistoMaker* maker = new EDBRHistoMaker(treeMC, fileMC,
					hisRatio, out_buffer);
			maker->setUnitaryWeights(false);
			maker->Loop_SFs_mc(buffer);
			//maker->Loop(buffer);
			maker->endjob();
			fileMC->Close();
		}

	}  //end loop on MC files

	printf("Loop over MC done\n");

	//loop over MC signal files and make histograms individually for each of them
	for (int  i = 0; i < nMCSig; i++) {
		//continue;
		std::cout << "\n-------\nRunning over " << mcLabelsSig[i].c_str()
				<< std::endl;
		std::cout << "The file is " << fMCSig.at(i) << std::endl;
		sprintf(buffer, "./output-slimmed-rootfiles/histos_%s.root", mcLabelsSig[i].c_str());
		sprintf(out_buffer, "./output-slimmed-rootfiles/optimal_CR_%s.root", mcLabelsSig[i].c_str());
		fHistosMCSig.push_back(buffer);

		if (redoHistograms) {
			std::cout << "retrieve ith mcsig file" << std::endl;
			TFile *fileMCSig = TFile::Open(fMCSig.at(i).c_str());
			std::cout << "retrieve tree of mcsig file" << std::endl;
//			TTree *treeMCSig = (TTree*) fileMCSig->Get("demo");
			TTree *treeMCSig = (TTree*) fileMCSig->Get("outtree");
                        std::cout<<"OK1"<<endl;
			EDBRHistoMaker* maker = new EDBRHistoMaker(treeMCSig, fileMCSig,
					hisRatio, out_buffer);
			maker->setUnitaryWeights(false);
			maker->Loop_SFs_mc(buffer);
			//maker->Loop(buffer);
			maker->endjob();
			fileMCSig->Close();
		}
	}  //end loop on MC files
/*	printf("Loop over MC signal done\n");
	if (redoHistograms) {
		std::cout << "The file is " <<pathToTrees<< "cutla-out" << mc2Labels.c_str() << ".root" << std::endl;
		sprintf(buffer, "./output-slimmed-rootfiles/histos_%s.root", mc2Labels.c_str());
		sprintf(out_buffer, "./output-slimmed-rootfiles/optimal_%s.root", mc2Labels.c_str());
		std::cout << "retrieve contamination ZA file" << std::endl;
		std::vector < std::string > fCon;
		fCon.push_back(pathToTrees + "cutla-out" + mc2Labels + ".root");

		TFile *file = TFile::Open( fCon.at(0).c_str());
		std::cout << "retrieve tree of contamination ZA file" << std::endl;
		TTree *tree = (TTree*) file->Get("demo");
		std::cout<<"OK2"<<endl;
		EDBRHistoMaker* maker = new EDBRHistoMaker(tree, file,
				hisRatio, out_buffer);
		std::cout<<"OK3"<<endl;
		maker->setUnitaryWeights(false);
		maker->Loop_SFs_mc(buffer);
		std::cout<<"OK4"<<endl;
		maker->endjob();
		file->Close();
	}
	printf("Loop over contamination ZA done\n");*/



	/// ------------------------------------------------------------------
	/// This second part is the loop over histograms to create stack plots
	/// ------------------------------------------------------------------  
	printf("\nStart looping over histograms\n\n");
	//make nice plots
	std::vector < std::string > listOfHistos;
	if (nMC > 0) {
		// Open one of the histogram files just to get the list of histograms
		// produced, then loop over all the histograms inheriting 
		// from TH1 contained in the file.
		sprintf(buffer, "./output-slimmed-rootfiles/histos_%s.root", mcLabels[0].c_str());
		std::cout << "Opening " << buffer << std::endl;
		TFile* oneFile = TFile::Open(buffer);
		TIter next(oneFile->GetListOfKeys());
		TKey *key;
		while ((key = (TKey*) next())) {
			TClass *cl = gROOT->GetClass(key->GetClassName());
			if (!cl->InheritsFrom("TH1"))
				continue;
			TH1 *hTMP = (TH1*) key->ReadObj();
			std::string hName = hTMP->GetName();
			printf("Histogram found: %s\n", hName.c_str());
			listOfHistos.push_back(hName);
		}      //end while loop
		oneFile->Close();
	}      //end if fmc size >0

	std::cout << "Creating plotter" << std::endl;
	EDBRHistoPlotter *plotter = new EDBRHistoPlotter("./", fHistosData,
			fHistosMC, fHistosMCSig,/* mc2Labels,*/ lumiValue, scaleToData, scaleOnlyWJets,
			makeRatio, isSignalStackOnBkg, kFactorsMC, kFactorsMCSig);
	std::cout << "Set output dir" << std::endl;
	plotter->setOutDir(outputDir);
	plotter->setDebug(false);

	//colors are assigned in the same order of mcLabels
	// For ZZ
	////// {DYJetsToLL_HT-200to400,DYJetsToLL_HT-200to400,DYJetsToLL_HT-600toInf}
	std::vector<int> fColorsMC;

/*	fColorsMC.push_back(kGreen-6);
	fColorsMC.push_back(kGreen-10);
	fColorsMC.push_back(kBlue-7);
	fColorsMC.push_back(kBlue-9);
	fColorsMC.push_back(kOrange);
	fColorsMC.push_back(kRed-4);*/

	fColorsMC.push_back(kGreen-4);
	fColorsMC.push_back(kGreen-4);
	fColorsMC.push_back(kGreen-4);
	fColorsMC.push_back(kGreen-10);
	fColorsMC.push_back(kGreen-10);
	fColorsMC.push_back(kGreen-10);
	fColorsMC.push_back(kBlue-4);
	fColorsMC.push_back(kBlue-4);
	fColorsMC.push_back(kBlue-4);
	fColorsMC.push_back(kBlue-7);
	fColorsMC.push_back(kBlue-7);
	fColorsMC.push_back(kBlue-7);
	fColorsMC.push_back(kOrange-2);
	fColorsMC.push_back(kOrange-2);
	fColorsMC.push_back(kOrange-2);
	fColorsMC.push_back(kRed-7);
	fColorsMC.push_back(kRed-7);
	fColorsMC.push_back(kRed-7);

/*	fColorsMC.push_back(kGreen-7);
	fColorsMC.push_back(kGreen-8);
	fColorsMC.push_back(kBlue-5);
	fColorsMC.push_back(kBlue-10);
	fColorsMC.push_back(kOrange-3);
	fColorsMC.push_back(kRed-9);*/

	std::vector<int> fColorsMCSig;
	fColorsMCSig.push_back(kRed);
	fColorsMCSig.push_back(kBlue + 3);

	plotter->setFillColor(fColorsMC);
	plotter->setLineColor(fColorsMCSig);

	int numOfHistos = listOfHistos.size();
	for (int i = 0; i != numOfHistos; ++i)
		plotter->makeStackPlots(listOfHistos.at(i));
	printf("Plotting done\n");
	delete plotter;
}

int main() {
	loopPlot();
	return 0;
}

