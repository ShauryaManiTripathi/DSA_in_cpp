#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int arr[10]={2,2,3,4,4,4,4,5,6,7};
    int n=10;
    cout<<*lower_bound(arr, arr+n,7)<<endl;// gives iterator to 3
    cout<<*upper_bound(arr, arr+n,7)<<endl;// gives iterator to 4

    return 0;
}
