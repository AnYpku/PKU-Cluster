#include<iostream>
using namespace std;

template<class T>

int length(T& arr)
{
    //cout << sizeof(arr[0]) << endl;
    //cout << sizeof(arr) << endl;
    return sizeof(arr) / sizeof(arr[0]);
}

int test()
{
    int arr[] = { 1,5,9,10,9,2 };
    // 方法一
    cout << "数组的长度为：" << length(arr) << endl;
    // 方法二
    //cout << end(arr) << endl;
    //cout << begin(arr) << endl;
    cout << "数组的长度为：" << end(arr)-begin(arr) << endl;
    system("pause");
    return 0;
}
