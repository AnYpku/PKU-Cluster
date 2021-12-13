void test(){
	ifstream file("file18");
	cout<<"open the file"<<endl;
	abort();
	TString line1,line2;
	if(file.is_open()){
		while(!file.eof()){
			file>>line1>>line2;
//			getline(file,line1);
			cout<<line1<<"; "<<line2<<endl;
		}
	}
}
