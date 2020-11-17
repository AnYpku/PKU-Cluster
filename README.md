# Analysis stage

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

Almost scale factors are provided by corrsponding POG except the trigger efficiencies measurement. As the trigger scale factors vary with different working points and basic selection requirement. For example, in Zgamma measurement, we require the electron p_T>25 GeV, but in other analysis, they may require the electron p_T>30 GeV. There is an official tools provided by Egamma POG seen [TnpTools](https://github.com/lsoffi/egm_tnp_analysis/tree/egm_tnp_Prompt2018_102X_09062018/etc).

### Trigger efficiency 

We always use Z to ee events to measure the trigger efficiency. The MC samples are DYell processes with different generator in LO or NLO. These difference is used to estimate one soucrce of uncertainty called **alternative MC**. In the [TnpTools](https://github.com/lsoffi/egm_tnp_analysis/tree/egm_tnp_Prompt2018_102X_09062018/etc) page, it has a brief introduction, you can do step by step. I also attach some disscussion and introduction from my understanding [ref_Tnp](https://indico.cern.ch/event/903012/). 

### Add weights

Beside these SFs, we need to normalized the MC to its corresponding cross section. There is a table can be refered to [XS_Table](https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns). Or if there is a paper giving a more accurate cross section, it can also be used. Besides, the [GenXSAnalyzer](https://twiki.cern.ch/twiki/bin/viewauth/CMS/HowToGenXSecAnalyzer) is often used. I provide some codes in my GitHub here [Add_weights](https://github.com/AnYpku/PKU-Cluster/tree/master/RunII2016/step1_add_weight). As some processes in different years may have little difference and SFs files are different, it is better to do separately. Actually, the code I show is not convenient to write. You may also have the idea that do `SetBranchAddress` many times very annoyed. I introduce a way called `TTreeFormula`. 

In this step, we want to add extra branches that save different SFs and slimme the root files at the same time.
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
A very sample example listed above.

 
