#include <bits/stdc++.h>
using namespace std;

void explainSet(){
    set<int> st;
    st.insert(1);
    st.insert(3);
    st.insert(3);// O(logn)
    st.insert(2);
    st.insert(4);
    st.insert(5);
    st.insert(6);


    for(auto s: st){
        cout<<s<<" ";
    }
    cout<<endl;

    auto it = st.find(3);
    if(it == st.end()){
        cout<<"Not found\n";
    }else{
        st.erase(*it);// or st.erase(it); // O(logn)
    }
    for(auto s: st){
        cout<<s<<" ";
    }
    cout<<endl;

    cout<<*st.lower_bound(4)<<endl;// gives iterator to 3
    cout<<*st.upper_bound(4)<<endl;// gives iterator to 4

    // other functions are size, empty, clear, swap, insert, erase, find, count, lower_bound, upper_bound

    // ! also , erase can be used to erase in range
    
    st.erase(st.begin(), st.find(5));   // ** [first, last), last is excluded

    for(auto s: st){
        cout<<s<<" ";
    }
    cout<<endl;

    cout<<"Count of 4: "<<st.count(4)<<endl;// gives 1 if present 0 if not

}


void explainMultiset(){
    // ** multiset allows duplicates
    // ** in terms of complexity , it differs from set in insert and erase functions
    // ** erase in multiset removes all the elements with the value
    // ** in multiset, lower_bound and upper_bound gives the iterator to the first element with the value
    // ** insert and erase functions have O(logn) complexity
    multiset<int> st;
    st.insert(1);
    st.insert(3);
    st.insert(3);// O(logn)
    st.insert(2);
    st.insert(4);
    st.insert(5);
    st.insert(6);
    st.insert(3);

    for(auto s: st){
        cout<<s<<" ";
    }
    cout<<endl;

    auto it = st.find(3);
    if(it == st.end()){
        cout<<"Not found\n";
    }else{
        st.erase(*it);// or st.erase(it); // O(logn)
    }
    for(auto s: st){
        cout<<s<<" ";
    }
    cout<<endl;

    cout<<*st.lower_bound(4)<<endl;// gives iterator to 3
    cout<<*st.upper_bound(4)<<endl;// gives iterator to 4

    // other functions are size, empty, clear, swap, insert, erase, find, count, lower_bound, upper_bound

    // ! also , erase can be used to erase in range
    
    st.erase(st.begin(), st.find(5));   // ** [first, last), last is excluded

    for(auto s: st){
        cout<<s<<" ";
    }
    cout<<endl;

    cout<<"Count of 4: "<<st.count(4)<<endl;// gives 1 if present 0 if not

}

void explainPairSet(){
    // ** pair set is a set of pairs
    // ** it is used to store pairs
    // ** it is ordered on the basis of first element
    // ** if first element is same, then second element is considered
    // ** it is implemented using balanced binary search tree
    // ** it has O(logn) time complexity for insert, find, erase
    // ** lower_bound and upper_bound gives the iterator to the first element with the value
    set<pair<int, int>> st;
    st.insert({1, 2});
    st.insert({3, 4});
    st.insert({3, 3});
    st.insert({2, 4});
    st.insert({4, 5});
    st.insert({5, 6});
    st.insert({6, 7});
    st.insert({3, 4});

    for(auto s: st){
        cout<<s.first<<" "<<s.second<<" - ";
    }
    cout<<endl;

    auto it = st.find({3, 4});
    if(it == st.end()){
        cout<<"Not found\n";
    }else{
        st.erase(it); // O(logn)
    }
    for(auto s: st){
        cout<<s.first<<" "<<s.second<<" - ";
    }
    cout<<endl;

    cout<<(*st.lower_bound({4, 4})).first<<endl;// gives iterator to 3
    cout<<(*st.upper_bound({4, 4})).first<<endl;// gives iterator to 4

    // other functions are size, empty, clear, swap, insert, erase, find, count, lower_bound, upper_bound

    // ! also , erase can be used to erase in range
    
    st.erase(st.begin(), st.find({5, 6}));   // ** [first, last), last is excluded

    for(auto s: st){
        cout<<s.first<<" "<<s.second<<endl;
    }
    cout<<endl;

    cout<<"Count of 4: "<<st.count({4, 5})<<endl;// gives 1 if present 0 if not
}

void explainunordered_set(){
    // ** unordered set is implemented using hashing
    // ** it has O(1) amortized time complexity for insert, find, erase. for insert the worst is O(n) but it happens like blue moon.
    // ! lower_bound and upper_bound are not available
    // ** it is faster than set
    // ** it is implemented using hashing
    // ** it is not ordered
    // ** it is implemented using chaining
    std::unordered_set<int> st;
    st.insert(1);
    st.insert(3);
    st.insert(3);// O(1)
    st.insert(2);
    st.insert(4);
    st.insert(5);
    st.insert(6);

    for(auto s: st){
        cout<<s<<" ";
    }
    cout<<endl;

    auto it = st.find(3);// O(1)
    if(it == st.end()){
        cout<<"Not found\n";
    }else{
        st.erase(*it);// or st.erase(it); // O(1)
    }
    for(auto s: st){
        cout<<s<<" ";
    }
    cout<<endl;

    // cout<<*st.lower_bound(4)<<endl;// gives iterator to 3
    // cout<<*st.upper_bound(4)<<endl;// gives iterator to 4

    // other functions are size, empty, clear, swap, insert, erase, find, count, lower_bound, upper_bound

    // ! also , erase can be used to erase in range
    
    // st.erase(st.begin(), st.find(5));   // ** [first, last), last is excluded

    for(auto s: st){
        cout<<s<<" ";
    }
    cout<<endl;

    cout<<"Count of 4: "<<st.count(4)<<endl;// gives 1 if present 0 if not
}
int main(int argc, char const *argv[])
{
    //explainSet();
    //explainMultiset();
    //explainPairSet();
    explainunordered_set();
    return 0;
}
