#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

void iterators(vector<pair<int, int>> v)
{
    vector<pair<int, int>>::iterator it = v.begin();
    cout << it->first << " " << it->second << endl;
    cout << (*it).first << " " << (*it).second << endl;
    it++;
    cout << it->first << " " << it->second << endl;

    vector<pair<int, int>>::reverse_iterator it2 = v.rbegin();
    cout << it2->first << " " << it2->second << endl;
    cout << (*it2).first << " " << (*it2).second << endl;
    it2++;
    cout << it2->first << " " << it2->second << endl;

    //similarly rend, and rbegin


    for(vector<pair<int, int>>::iterator it3 = v.begin(); it3!=v.end(); it3++){
        cout<<it3->first<<" "<<it3->second<<" ";
    }
    cout<<endl;
    //or with auto
    //auto is used to automatically detect the data type of the variable

    for(auto it4 = v.begin(); it4!=v.end(); it4++){
        cout<<it4->first<<" "<<it4->second<<" ";
    }
    cout<<endl;

    for(auto it : v){// this auto assigns it as int
        cout<<it.first <<" "<< it.second <<" ";
    }
    cout<<endl;

    //{1,2}, {3,4}, {5,6}, {7,8}
    v.erase(v.begin()+1);
    //or
    v.erase(v.begin(), v.begin()+2);
    for(auto it : v){
        cout<<it.first <<" "<< it.second <<" ";
    }
    cout<<endl;

    //simularly to erase, there is insert method

    vector<int> a = {1, 2, 3, 4, 5, 6};

    // ** there are other functions like swap, clear, empty, size, max_size, resize, reserve, capacity, shrink_to_fit
    // ** there are other functions like assign, emplace, emplace_back, push_back, pop_back, insert, erase, swap, clear, empty, size, max_size, resize, reserve, capacity, shrink_to_fit
    // ** explaining each function in one line
    // ** assign: assigns new values to the vector
    // ** emplace: constructs element in place
    // ** emplace_back: constructs element in place at the end
    // ** push_back: adds element at the end
    // ** pop_back: removes element from the end
    // ** insert: inserts elements
    // ** erase: removes elements
    // ** swap: swaps the contents of two vectors
    // ** clear: removes all elements
    // ** empty: checks if the vector is empty
    // ** size: returns the number of elements
    // ** max_size: returns the maximum number of elements
    // ** resize: changes the size of the vector
    // ** reserve: reserves the space
    // ** capacity: returns the number of elements that can be held in the vector
    // ** shrink_to_fit: reduces the capacity to the size of the vector
    // ** iterators: begin, end, rbegin, rend, cbegin, cend, crbegin, crend

    a.assign(5, 100);
    for(auto it : a){
        cout<<it<<" ";
    }

}


int main(int argc, char const *argv[])
{
    vector<pair<int, int>> v = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    iterators(v);

    return 0;
}
