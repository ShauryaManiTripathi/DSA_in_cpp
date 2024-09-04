#include<iostream>
#include<vector>
using namespace std;

#define debug(x) cout << #x << " = " << x << endl


void vectors(vector<pair<int,int>> v);
void vectors(){
    vector<int> a1;
    a1.push_back(1);
    a1.emplace_back(2);
    debug(a1[0]);
    debug(a1[1]);


    vector<int> a2(5); //initializes 5 elements with 0 or garbage values depends on compiler
    debug(a2[0]);
    debug(a2[1]);

    vector<int> a3(5, 100); //initializes 5 elements with 100
    debug(a3[0]);
    debug(a3[1]);

    vector<int> a4(a3.begin(), a3.begin()+2);
    debug(a4[0]);
    debug(a4[1]);
    debug(a4.size());
    vector<int> a5(a4);
    debug(a5[0]);
    debug(a5[1]);
    debug(a5.size());

    //other functions
    a5.reserve(1000);
    debug(a5.capacity());
    debug(a5.size());
    a5.resize(5);
    debug(a5.size());
    debug(a5.capacity());

    vector<pair<int, int>> v= { {1,2}, {3,4}, {5,6}, {7,8} };
    vectors(v);

}
#include<iterator>
void vectors(vector<pair<int,int>> v){
    for(auto x: v){
        cout<<x.first<<" "<<x.second<<endl;
    }
    cout<<endl;
    vector<pair<int,int>>::iterator it= v.begin();
    for(it; it!=v.end(); it++){
        cout<<it->first<<" "<<it->second<<endl;
    }
}






int main(int argc, char const *argv[])
{
    vectors();
    return 0;
}
