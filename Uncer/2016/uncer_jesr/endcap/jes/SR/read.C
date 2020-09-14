void read(){

	ifstream mb,me,eb,ee;
	mb.open("/afs/cern.ch/work/y/yian/work/PKU-Cluster/Uncer/2017/fakephoton/mubarrel/step2/SR/2017mubarrel_fake_uncer.txt");
	me.open("/afs/cern.ch/work/y/yian/work/PKU-Cluster/Uncer/2017/fakephoton/muendcap/step2/2017muendcap_fake_uncer.txt");
	eb.open("/afs/cern.ch/work/y/yian/work/PKU-Cluster/Uncer/2017/fakephoton/elebarrel/step2/2017elebarrel_fake_uncer.txt");
	ee.open("/afs/cern.ch/work/y/yian/work/PKU-Cluster/Uncer/2017/fakephoton/eleendcap/step2/2017eleendcap_fake_uncer.txt");
	ofstream f1("fake_uncer_summary.txt");
	if(!mb.is_open())  cout<<"mb open error"<<endl;
	if(!me.is_open())  cout<<"me open error"<<endl;
	if(!eb.is_open())  cout<<"eb open error"<<endl;
	if(!ee.is_open())  cout<<"ee open error"<<endl;
        double uncer_mb[8],uncer_me[8],uncer_eb[8],uncer_ee[8];
        for(int i=0;i<8;i++){
          mb>>uncer_mb[i];
          me>>uncer_me[i];
          eb>>uncer_eb[i];
          ee>>uncer_ee[i];
//          cout<<uncer_mb[i]<<endl;
	}
        for(int i=0;i<8;i++){
           f1<<fixed<<setprecision(1)<<uncer_mb[i]*100<<"%\t"<<uncer_me[i]*100<<"%\t"<<uncer_eb[i]*100<<"%\t"<<uncer_ee[i]*100<<"%"<<endl;
	}









}
