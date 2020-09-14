void read(){

	ifstream bb,sb,be,se;
	bb.open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2017/uncer_jesr/barrel/jer/SR/2017jer-uncertainty-barrel_ZA.txt");
	sb.open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2017/uncer_jesr/barrel/jer/SR/2017jer-uncertainty-barrel_ZA-EWK.txt");
	be.open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2017/uncer_jesr/endcap/jer/SR/2017jer-uncertainty-endcap_ZA.txt");
	se.open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2017/uncer_jesr/endcap/jer/SR/2017jer-uncertainty-endcap_ZA-EWK.txt");
	ofstream f1("jes_uncer_summary.txt");
	if(!bb.is_open())  cout<<"nb open error"<<endl;
	if(!sb.is_open())  cout<<"sb open error"<<endl;
	if(!be.is_open())  cout<<"be open error"<<endl;
	if(!se.is_open())  cout<<"se open error"<<endl;
        double uncer_bb[8],uncer_sb[8],uncer_be[8],uncer_se[8];
        for(int i=0;i<8;i++){
          bb>>uncer_bb[i];
          sb>>uncer_sb[i];
          be>>uncer_be[i];
          se>>uncer_se[i];
          cout<<uncer_bb[i]<<endl;
	}
        for(int i=0;i<8;i++){
           f1<<fixed<<setprecision(1)<<uncer_sb[i]*100<<"%\t"<<uncer_se[i]*100<<"%\t"<<uncer_bb[i]*100<<"%\t"<<uncer_be[i]*100<<"%"<<endl;
	}









}
