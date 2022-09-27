void aa(){

	TF1* f1= new TF1("f1","exp(-0.5*x)/sqrt(2*3.1416*x)",10e-8,50);
	double a=f1->Integral(10e-8,3);
	cout<<a<<endl;
}
