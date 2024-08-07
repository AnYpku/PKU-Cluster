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
#include "test.C"
#include "CMSTDRStyle.h"
//#include "Scale_jet_with_fakerate.C"
#include "TH2.h"
using namespace std;
void loopPlot() {
	gErrorIgnoreLevel = kFatal; //suppresses all info messages

	setTDRStyle(); //TDR style

	//#####################EDIT THE OPTIONS##############################

	double lumiValue = 35.862*0.96;
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
	std::string pathToTrees = "/home/pku/anying/cms/RunII2016/analysis_code/aa2/MuonBarrel/output-slimmed-rootfiles/";
	//  std::string pathToTrees="./";
	std::string outputDir = "./";
	
        /// file for scale factors

// Setup names of data files for trees.
	const int nDATA = 1;
	std::cout << "set data imformation, we have " << nDATA << "data file"
			<< std::endl;
	std::string dataLabels[nDATA] = { "Muon" };
	std::vector < std::string > fData;
	for (int ii = 0; ii < nDATA; ii++) {
		fData.push_back(pathToTrees+"optimal_" + dataLabels[ii] + ".root");
	}
// set mc imformation
		const int nMC = 6;
		std::cout << "set data imformation, we have " << nMC << "mc file"
				<< std::endl;
		std::string mcLabels[nMC] = { "ST", "TTA", "VV", "WA","plj_mubarrel", "ZA" };
		double kFactorsMC_array[nMC] = { 1, 1, 1, 1, 1, 1};
		std::vector< std::string > fMC;
		for (int ii = 0; ii < nMC; ii++) {
			fMC.push_back(pathToTrees + "optimal_" + mcLabels[ii] + ".root");
		}
		std::vector<double> kFactorsMC;
		for (int index = 0; index < nMC; index++) {
			kFactorsMC.push_back(kFactorsMC_array[index]);
		}

// set mcsig information
	const int nMCSig = 1;
	std::cout << "set data imformation, we have " << nMCSig << "mcsig file"
			<< std::endl;
	std::string mcLabelsSig[nMCSig] = { "ZA-EWK" };
	double kFactorsSig_array[nMCSig] = { 1 };
	std::vector < std::string > fMCSig;
	for (int ii = 0; ii < nMCSig; ii++) {
		fMCSig.push_back(pathToTrees+"optimal_" + mcLabelsSig[ii] + ".root");
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
		std::cout << "\n-------\nRunning over " << dataLabels[i].c_str()
				<< std::endl;
		std::cout << "The file is " << fData.at(i) << std::endl; //fData.push_back(pathToTrees + dataLabels[ii] + ".root");
		sprintf(buffer, "histos_%s.root", dataLabels[i].c_str());
		sprintf(out_buffer, "optimal_%s.root", dataLabels[i].c_str());
		fHistosData.push_back(buffer);

		std::cout << "retrieve ith data file" << std::endl;
		TFile *fileData = TFile::Open(fData.at(i).c_str());
		std::cout << "retrieve tree of data file" << std::endl;
		TTree *treeData = (TTree*) fileData->Get("outtree");
		TFile *fileMC = TFile::Open(fMC.at(i).c_str());
		TTree *treeMC = (TTree*) fileMC->Get("outtree");
		std::cout << "retrieve ith mc file" << std::endl;
		if (dopileupreweight) {
			hisRatio = test(treeData, treeMC);
			std::cout << "hisRatio" << std::endl;
		}
		if (redoHistograms) {
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
		std::cout << "\n-------\nRunning over " << mcLabels[i].c_str()
				<< std::endl;
		std::cout << "The file is " << fMC.at(i) << std::endl;
		sprintf(buffer, "histos_%s.root", mcLabels[i].c_str());
		sprintf(out_buffer, "optimal_%s.root", mcLabels[i].c_str());
		fHistosMC.push_back(buffer);
		std::cout << "test" << std::endl;

		if (redoHistograms) {
			std::cout << "retrieve ith mc file" << std::endl;
			TFile *fileMC = TFile::Open(fMC.at(i).c_str());
			std::cout << "retrieve tree of mc file" << std::endl;
			TTree *treeMC = (TTree*) fileMC->Get("outtree");
			EDBRHistoMaker* maker = new EDBRHistoMaker(treeMC, fileMC,
					hisRatio, out_buffer);
			if ( i == 4) {
                                maker->setUnitaryWeights(true);
                                maker->Loop_plj(buffer);
                                maker->endjob();
			}
			else{
			maker->setUnitaryWeights(false);
			maker->Loop_SFs_mc(buffer);
			//maker->Loop(buffer);
			maker->endjob();}
			fileMC->Close();
		}

	}  //end loop on MC files

	printf("Loop over MC done\n");

	//loop over MC signal files and make histograms individually for each of them
	for (int i = 0; i < nMCSig; i++) {
		std::cout << "\n-------\nRunning over " << mcLabelsSig[i].c_str()
				<< std::endl;
		std::cout << "The file is " << fMCSig.at(i) << std::endl;
		sprintf(buffer, "histos_%s.root", mcLabelsSig[i].c_str());
		sprintf(out_buffer, "optimal_%s.root", mcLabelsSig[i].c_str());
		fHistosMCSig.push_back(buffer);

		if (redoHistograms) {
			std::cout << "retrieve ith mcsig file" << std::endl;
			TFile *fileMCSig = TFile::Open(fMCSig.at(i).c_str());
			std::cout << "retrieve tree of mcsig file" << std::endl;
			TTree *treeMCSig = (TTree*) fileMCSig->Get("outtree");
			EDBRHistoMaker* maker = new EDBRHistoMaker(treeMCSig, fileMCSig,
					hisRatio, out_buffer);
			maker->setUnitaryWeights(false);
			maker->Loop_SFs_mc(buffer);
			//maker->Loop(buffer);
			maker->endjob();
			fileMCSig->Close();
		}

	}  //end loop on MC files

	printf("Loop over MC signal done\n");

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
		sprintf(buffer, "histos_%s.root", mcLabels[0].c_str());
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
			fHistosMC, fHistosMCSig, lumiValue, scaleToData, scaleOnlyWJets,
			makeRatio, isSignalStackOnBkg, kFactorsMC, kFactorsMCSig);
	std::cout << "Set output dir" << std::endl;
	plotter->setOutDir(outputDir);
	plotter->setDebug(false);

	//colors are assigned in the same order of mcLabels
	// For ZZ
	////// {DYJetsToLL_HT-200to400,DYJetsToLL_HT-200to400,DYJetsToLL_HT-600toInf}
	std::vector<int> fColorsMC;

	fColorsMC.push_back(kGreen);
	fColorsMC.push_back(kCyan);
	fColorsMC.push_back(kBlue - 6);
	fColorsMC.push_back(kBlue + 2);
	fColorsMC.push_back(kYellow);
	fColorsMC.push_back(kMagenta);
	fColorsMC.push_back(kMagenta + 3);
	fColorsMC.push_back(kOrange + 7);
	fColorsMC.push_back(2);
	fColorsMC.push_back(2);
	fColorsMC.push_back(2);
	fColorsMC.push_back(2);
	fColorsMC.push_back(210);
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

