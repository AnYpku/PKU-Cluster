# Analysis stage

## Control Region definition and selection determination

Find a region that contains few signal called control region. In this region, determine the selection to make the comparison between data and MC have an agreement.

## Scale factor applied

There are kinds of scale factors as a function of $\eta$ and $p_{T}$ in most case, including
- electron/muon/photon ID scale factor
- muon isolation scale factor
- electron reconstrution scale factor
- photon veto scale factor
- trigger scale factor
- pileup reweighting
- egamma energy scale and smearing
- L1 prefiring 

For electron scale factors application, please refer to [ElectronSFs](https://twiki.cern.ch/twiki/bin/view/CMS/TWikiSMP-EGM-Electron)

For muon SFs, please refer to [muonSFs](https://twiki.cern.ch/twiki/bin/view/CMS/MuonPOG)

For photon SFs, please refer to [photonSFs](https://twiki.cern.ch/twiki/bin/view/CMS/EgammaRunIIRecommendations#Fall17v2_AN1) and [photonSFs](https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2#Electron_Veto_CSEV_or_pixel_seed)

Almost scale factors are provided by corrsponding POG except the trigger efficiencies measurement. As the trigger scale factors vary with different working points and basic selection requirement. For example, in Zgamma measurement, we require the electron p_T>25 GeV, but in other analysis, they may require the electron p_T>30 GeV. There is an official tools provided by Egamma POG seen [TnpTools](https://github.com/lsoffi/egm_tnp_analysis/tree/egm_tnp_Prompt2018_102X_09062018/etc). There are some approval HLT SFs [eleHLTSFs](https://twiki.cern.ch/twiki/bin/view/CMS/EgHLTScaleFactorMeasurements).

### Trigger efficiency 

We always use Z to ee events to measure the trigger efficiency. The MC samples are DYell processes with different generator in LO or NLO. These difference is used to estimate one soucrce of uncertainty called **alternative MC**. In the [TnpTools](https://github.com/lsoffi/egm_tnp_analysis/tree/egm_tnp_Prompt2018_102X_09062018/etc) page, it has a brief introduction, you can do step by step. I also attach some disscussion and introduction from my understanding [ref_Tnp](https://indico.cern.ch/event/903012/). 

### Add weights

Beside these SFs, we need to normalized the MC to its corresponding cross section. There is a table can be refered to [XS_Table](https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns). Or if there is a paper giving a more accurate cross section, it can also be used. Besides, the [GenXSAnalyzer](https://twiki.cern.ch/twiki/bin/viewauth/CMS/HowToGenXSecAnalyzer) is often used. I provide some codes in my GitHub here [Add_weights](https://github.com/AnYpku/PKU-Cluster/tree/master/RunII2016/step1_add_weight). As some processes in different years may have little difference and SFs files are different, it is better to do separately. Actually, the code I show is not convenient to write. You may also have the idea that do `SetBranchAddress` many times very annoyed. I introduce a way called `TTreeFormula`. 

In this step, we want to add extra branches that save different SFs and slim the root files at the same time.
```
void add(){
TFile*fin=new TFile("fin.root");
TFile*fout=new TFile("fout.root","recreate");
TTree*treeIn=(TTree*)fin->Get("tree");
TTree*treeOut=treeIn->Clone();
treeOut->Branch("ele1_id_sf",&ele1_id_sf,"ele1_id_sf/D");
TString cut="basic cuts";
TTreeFormula*tformula1=new TTreeFormula("formula1",cut,tree);
for(int i=0;i<treeIn->GetEntries();i++){
   treeIn->GetEntry(i);
    ele1_id_sf=xxx;
    if (  !tformula1->EvalInstance() )
         continue;
    treeOut->Fill();
}
fout->cd();
treeOut->Write();
fout->Close();
fin->Close();
}

```
A very simple example listed above. 

### Background estimation

#### Fake photon

- Prepare fake photon sample from data seen [plj_production](https://github.com/AnYpku/PKU-Cluster/tree/master/RunII2016/plj/plj-production)
- Calculate fakefraction [fakefraction](https://github.com/AnYpku/PKU-Cluster/tree/master/RunII2016/MakeTemplate/With_sieieCorr/BarrelMuon)
- Calculate weights of fake photon sample [pljweight](https://github.com/AnYpku/PKU-Cluster/tree/master/RunII2016/plj/plj-weight/all)

#### Fake lepton

### Uncertainty calculation
As it's still annoyed to repeate the same procedure in different years and channels. I recommend you define functions and call for them later to prepare histograms that you want in differents and channels one time. See an example here [Build_hist](https://github.com/AnYpku/PKU-Cluster/blob/master/Significance/Uncer/fakephoton/Uncer_batch_bkg.C). These histograms can be use to prepare data card for significance calculation and calculate uncertainties. 

```
.....
TString th1name="hist_name";
TString cut="(basic cuts)"
TString var="ptlep1";
TH1D*h1=new TH1D(th1name,"",bin,xlow,xhigh);
tree->Draw(var+">>"+th1name,cut+"*weight","goff");

```

List a simple example to fill histograms not in a loop.

#### Scale and PDF uncertainties

As the renormalization(mu_R) and factorization(mu_F) are used to estimate pp collsion that included in the MC simulation, it is necessary to consider its uncertainty. In CMS MC simulation, we vary mu_R and mu_F by combination of (1,0.5,2). From the envelop, the largest variation comapred with the central one as uncertainty, except condition when mu_R and mu_F are 0.5 0r 2.0. 

Besides the scale uncertainties, the uncertainty from PDF(parton distribution function) is also needed to consider. The way of handling PDF uncetainties is to calculate the standard deviation from hundreds of PDF weights.

### Interference effect

Make use of MadGraph syntax, the interference process can be produced by:

```
generate p p > lep+ lep- a j j QCDˆ2==2

```

Take the fraction to signal process in SR as the uncertainty.

### Uncertainty from data-driven method

Introdution

Three sources uncertainties here. Code here [fakeuncertainties](https://github.com/AnYpku/PKU-Cluster/tree/master/FakePhoton)

### Jet energy correction uncertainties

### Commom uncertaintis

- particel ID and reconstruction
- pileup
- luminosity
- cross section estimation
- L1 prefiring in 2016 and 2017

I usualy print all uncertaintis into a txt file seen an example [summary_uncer](https://github.com/AnYpku/PKU-Cluster/blob/master/Significance/Uncer/summary_uncer_elebarrel16.txt). When prepare data card, use function of python to transfer them.

```
f=open('/home/pku/anying/cms/PKU-Cluster/Significance/Uncer/summary_uncer_'+sys.argv[2]+sys.argv[1]+'.txt')
import re
import numpy as np
for line in f:
        if not line.strip():
            continue
        print line
        line = line.replace('[','')
        line = line.replace(']','')
        line = line.replace('\n','')
        print line
        arr_Temp = re.split(',|=',line)
        print arr_Temp
        name = arr_Temp[0]
        arr_Temp = np.array(arr_Temp[1:])
        #arr_Temp.astype(np.float)
        arr_Temp = [float(x) for x in arr_Temp]
        print name
        arr[name]=arr_Temp
print arr
```
Then we can get special arrays with style like [string][double], which is convenient in the following usage.

### Significance

Introdution

#### Optimization cuts

#### Code preparation

- Histograms preparation [code](https://github.com/AnYpku/PKU-Cluster/blob/master/Significance/Build_Hist.C)
- data card [code](https://github.com/AnYpku/PKU-Cluster/tree/master/Significance/data_cards)
- Combine from [HiggsCombieTools](http://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/)

### Signal Strength

Introdution

At first, please save branch of gen variables. You should build gen variables same as what you did in the ntuple code in reconstruction level. An example for VBS Zgamma seen [genparticles](https://github.com/AnYpku/PKU-Cluster/tree/master/Unfolding/produce).

Except the minor change of selection, when calculate signal strength, the optimization cuts not included, method of handling EW theoretical uncertainties and division of EW signal sample to in-fiducial(reco&&gen) and out-fiducial(reco&&!gen), the left is same as in calculating significance.

#### Code preparation

It is very similar with steps in significance calculation.

### Unfolding

Unfolding is the generic term used to describe this detector-level to particle-level correction for distributions. In general, this can account for limited acceptance, finite resolution, and inefficiencies of the detector, as well as bin migrations in the distribution between measured and corrected. Simulated EW samples from MC event generators are used to perform the unfolding. Distributions obtained from the generated events correspond to particle-level (will be referred to as gen). Then the events are passed through a detector simulation programme, mimicking the behaviour of the CMS detector as closely as possible, and the same distributions obtained using these events correspond to detector-level (will be referred to as reco). 

The unfolded differential cross section can be measured as a function of some variables.

#### Code preparation

At first, please save branch of gen variables. You should build gen variables same as what you did in the ntuple code in reconstruction level.

- Histograms [Build_Hist](https://github.com/AnYpku/PKU-Cluster/tree/master/Unfolding/common)
- data card [card](https://github.com/AnYpku/PKU-Cluster/tree/master/Unfolding/data_card)
- Combine [HiggsCombine_Unfolding](http://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/part3/regularisation/)

 
