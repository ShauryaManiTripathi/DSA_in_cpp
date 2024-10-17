#include <bits/stdc++.h>
using namespace std;

void explainMap(){
    map<int,int> mp1;
    map<int,pair<int,int>>mp2;
    map<pair<int,int>,int>mp3;
    // ** stores values in sorted order of keys
    // ** stores unique keys only
    mp1[1]=2;
    mp1.emplace(3,3);// O(logn)
    mp1.insert({2,4});// O(logn)
    for(auto it : mp1){
        cout<<it.first<<" "<<it.second<<", ";
    }
    cout<<endl;
    cout<<mp1[1]<<endl;

    {auto it = mp1.find(2);
    if(it == mp1.end()){
        cout<<"Not found\n";
    }else{
        cout<<it->first<<" "<<it->second<<endl;
    }}

    {auto it = mp1.find(55);
    if(it == mp1.end()){
        cout<<"Not found\n";
    }else{
        cout<<it->first<<" "<<it->second<<endl;
    }}
}

void explainmultimap(){
    // ** stores values in sorted order of keys
    // ** stores duplicate keys
    std::multimap<int,int> mp;
    mp.insert({1,2});
    mp.insert({1,3});// O(logn)
    mp.insert({2,4});
    mp.insert({3,5});

    for(auto it : mp){
        cout<<it.first<<" "<<it.second<<", ";
    }
    cout<<endl;

    auto it = mp.find(1);// returns iterator to the first element with key 1
    if(it == mp.end()){
        cout<<"Not found\n";
    }else{ 
        cout<<it->first<<" "<<it->second<<endl;
    }

    // get all element with key 1
    pair<multimap<int,int>::iterator, multimap<int,int>::iterator> it2 = mp.equal_range(1);
    for(auto it = it2.first; it!=it2.second; it++){
        cout<<it->first<<" "<<it->second<<", ";
    }

}
void explainUnorderedMap(){
    // ** stores values in any order
    // ** stores unique keys only
    // ** implemented using hashing
    // ** O(1) time complexity for insert, find, erase amortized
    
    unordered_map<int,int> ump;
    ump[2] = 3;
    ump[1] = 2;
    ump.insert({3,4}); // O(1)
    ump.emplace(4,5);
    for(auto it : ump){
        cout<<it.first<<" "<<it.second<<", ";
    }
    cout<<endl;
    // and so on
    // ** we can use functions like find, insert, erase, size, empty, 
    // ** clear, begin, end, rbegin, rend, cbegin, cend, crbegin, crend
    // normal comment
    // ** highlight comment
    // ! warning comment
    // ? query comment

}

int main(int argc, char const *argv[])
{
    explainMap();
    //explainmultimap();
    //explainUnorderedMap();
    return 0;
}