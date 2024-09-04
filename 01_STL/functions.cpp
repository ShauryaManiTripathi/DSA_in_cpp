#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

void explainFuncs();

int main(int argc, char const *argv[])
{
    explainFuncs();
    return 0;
}

bool comp(int a, int b){
    return a>b;
}


bool compchar(char a,char b){
    return (int)a<(int)b;
}
void explainFuncs(){
    vector<int> arr = {1,2,3,4,5,6,7,8,9,10};

    sort(arr.begin(), arr.end(),[](int a, int b){return a>b;});
    for(int x: arr){
        cout<<x<<" ";
    }
    cout<<endl;

    vector<pair<int,int>> v= { {7,2}, {5,4}, {3,6}, {1,8} };
    
    sort(v.begin(), v.end(), [](pair<int,int> a, pair<int,int> b){return a.second>b.second;});
    for(auto x: v){
        cout<<x.first<<" "<<x.second<<",";
    }
    cout<<endl;

    int num=7;
    long long num2=7;
    cout<<__builtin_popcount(num)<<endl;
    cout<<__builtin_popcountll(num2)<<endl;

    

    string s="abc";
    sort(s.begin(),s.end(),compchar);
    cout<<s<<endl;
    vector<int> v2= {1,2,3};
    do{
        cout<<s<<endl;
    }
    while(next_permutation(s.begin(), s.end()));

    do{
        cout<<v2[0]<<" "<<v2[1]<<" "<<v2[2]<<endl;
    }
    while(next_permutation(v2.begin(), v2.end()));

    vector<int> arr2={1,4,3,2};

    cout<<max_element(arr2.begin(), arr2.end())-arr2.begin()<<endl;
    cout<<min_element(arr2.begin(),arr2.end())-arr2.begin()<<endl;
}