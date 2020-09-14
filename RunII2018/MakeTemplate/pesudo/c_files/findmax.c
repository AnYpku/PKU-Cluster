#include <vector>
#include <algorithm>
#include <iostream>

void test()
{
     vector<double> v {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0};

     vector<double>::iterator biggest =  max_element( begin(v),  end(v));
     cout << "Max element is " << *biggest<< " at position " <<  distance( begin(v), biggest) <<  endl;

    auto smallest =  min_element( begin(v),  end(v));
     cout << "min element is " << *smallest<< " at position " <<  distance( begin(v), smallest) <<  endl;
    auto position =   distance( begin(v), biggest);
    cout<<" position "<< position<<"  "<<  distance(     begin(v), biggest) << endl;
    double a = v[position];
    cout<< "a = "<<a<<endl;
}

