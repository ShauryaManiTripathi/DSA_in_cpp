// ** STL **
// its divided into 4 parts
// 1. Containers DONE
// 2. Algorithms all essentials DONE 
// 3. Functions NOT REQUIRED
// 4. Iterators DONE
#include<utility>
#include<iostream>
using namespace std;
#define debug(x) cout << #x << " = " << x << endl

//pairs , generally used to store two values of different data types
// present in utility header file
void pairs(){
    pair<int, char> p;
    p.first = 3;
    p.second = 'f';

    pair<int, char> p2(p);
    debug(p2.first);
    debug(p2.second);

    p2={2, 'a'};
    debug(p2.first);
    debug(p2.second);



    pair<int, char> p3 = make_pair(2, 'a');
    debug(p3.first);
    debug(p3.second);


    pair<int, pair<int, char>> p4;
    p4.second.first = 3;
    p4.second.second = 'f';
    p4.first = 2;
    debug(p4.first);
    debug(p4.second.first);
    debug(p4.second.second);

    pair<int, int> arr[] = {make_pair(1, 2), make_pair(3, 4), make_pair(5, 6)};
    debug(arr[0].first);
    debug(arr[0].second);


    pair<int,int> arr2[]= { {1,2}, {3,4}, {5,6} };
    cout<<arr2[0].first<<endl;
    cout<<arr2[0].second<<endl;

}
int main(int argc, char const *argv[])
{
    pairs();
    return 0;
}
