import os
import math 
from subprocess import call

def main():
    
    min_ghost = 0 #105
    max_ghost = 0 #160
    NGhost = 0
    save_np = 0
    nTotalToy = 50
    nToyPerCommand = 50
    nCommandPerJob = 100 #80
    shiftseed = 0 #if you have already generated toy allow to generate more toy
    mail_for_job = "guo@lal.in2p3.fr"
    prefix = "/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/combine/run/6bins_za/test/"
    path_to_the_project = prefix+"/aQGC_ANYING/WORKSPACE_test/"
    directory_output = "TEST"
    path_to_the_workspace = prefix+"/aQGC_ANYING/WORKSPACE_test/"
    path_for_log = prefix+"/aQGC_ANYING/Log_Toy/"

    wsname = "w"
    mconfig = "ModelConfig"

    directory = ""
    #TrueValue_1 = [2,5,7,10,12,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40]
#,50,55,60,65,70]
#   TrueValue_1 = [1]
    TrueValue_1 = [2]
 

    #TrueValue = [0]
    #TestedValue = [0]
    TrueValue = []
    TestedValue = []  

    poi_name = []
    file_with_workspace = []
    
    for i in range(0,len(TrueValue_1)) :
        TrueValue.append(TrueValue_1[i])
        #TrueValue.append(0)
        TestedValue.append(TrueValue_1[i])
        #TestedValue.append(TrueValue_1[i])
        poi_name.append("param")
        #poi_name.append("param")
        #file_with_workspace.append("os_mll_fT8.root")
        file_with_workspace.append("os_mll_fT5.root")

    #call(["root","-b","-q",path_to_the_project+"/Tools/makeToy.C+"])
    
    #f1 = open("StandardPlotLauncher.sh","w")
    path  = path_to_the_workspace+directory+"/"
    call(["mkdir","-p",path+"/"+directory_output+"/"])
    call(["mkdir","-p",path+"/"+directory_output+"/PlotAfterFit/"])
    path_for_log= path_for_log+"/"+directory+"/"+directory_output+"/"
    call(["mkdir","-p",path_for_log])

    ifile = 0
    counter = 0
    name_script_file = "Script_"+directory+str(ifile)+".sh"
    f = open(name_script_file,"w")
    '''
    f.write("export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase\n")
    f.write("source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh\n")
    f.write("PATH=$PATH:"+path_to_the_project+"/Tools/\n")
    f.write("export PATH\n")
    f.write("ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:"+path_to_the_project+"/Tools/\n")
    f.write("export ROOT_INCLUDE_PATH\n")
    ''' 
    #f1.write("qsub -P P_atlas -m e -M "+mail_for_job+" -l ct=24:00:00 -l sps=1,vmem=3G,fsize=28G -N Toy_"+name_script_file+" -o "+path_for_log+"Log_Toy_"+name_script_file+".OU -e "+path_for_log+"Log_Toy_"+name_script_file+".ER "+name_script_file+"\n")

    for i_workspace in range(0, len(TrueValue)) :
        nJobs = (int)(nTotalToy*1.0/nToyPerCommand)
        bins = []        
        for i in range(0,nJobs) :
            bins.append(i*nToyPerCommand+shiftseed)
        file_name_output = "Toys_"+str(TrueValue[i_workspace])+"_"+str(TestedValue[i_workspace])
        for i in range(0,len(bins)) : #len(bins) -1 non inclus
            f.write("root -b -q \'"+path_to_the_project+"/makeToy.C+("+str(bins[i])+","+str(nToyPerCommand)+",\""+wsname+"\",\""+mconfig+"\","+str(TrueValue[i_workspace])+","+str(TestedValue[i_workspace])+",\""+poi_name[i_workspace]+"\",\""+str(path+file_with_workspace[i_workspace])+"\",\""+str(path+directory_output+"/"+file_name_output)+"_\","+str(save_np)+","+str(min_ghost)+","+str(max_ghost)+","+str(NGhost)+")\'\n")
            counter = counter+1
            if counter >  nCommandPerJob : 
                counter = 0
                ifile = ifile + 1
                name_script_file = "Script_"+directory+str(ifile)
                f = open(name_script_file,"w")
                '''
                f.write("export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase\n")
                f.write("source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh\n")
                f.write("PATH=$PATH:"+path_to_the_project+"/Tools/\n")
                f.write("export PATH\n")
                f.write("ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:"+path_to_the_project+"/Tools/\n")
                f.write("export ROOT_INCLUDE_PATH\n")
                '''
                #f1.write("qsub -P P_atlas -m e -M "+mail_for_job+" -l ct=24:00:00 -l sps=1,vmem=3G,fsize=28G -N Toy_"+name_script_file+" -o "+path_for_log+"Log_Toy_"+name_script_file+".OU -e "+path_for_log+"Log_Toy_"+name_script_file+".ER "+name_script_file+"\n")

if __name__ == "__main__":
	main()
