#include <bits/stdc++.h>
using namespace std;

void explainPQ()
{
    priority_queue<int> pq;
    pq.push(3);// O(logn)
    pq.push(5);
    pq.push(7);
    pq.push(2);
    pq.push(4);
    pq.push(6);

    cout << pq.top() << endl; // 7 // O(1)
    pq.pop();// O(logn)
    cout << pq.top() << endl; // 6

    priority_queue<int, vector<int>, greater<int>> pq_min;
    pq_min.push(3);
    pq_min.push(5);
    pq_min.push(7);
    pq_min.push(2);
    pq_min.push(4);
    pq_min.push(6);

    cout << pq_min.top() << endl; // 2
    pq_min.pop();
    cout << pq_min.top() << endl; // 3

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_pair;
    pq_pair.push({1, 2});
    pq_pair.push({1, 1});
    pq_pair.push({2, 2});   
    pq_pair.push({2, 1});


    while (!pq_pair.empty())
    {
        cout << pq_pair.top().first << " " << pq_pair.top().second << endl;
        pq_pair.pop();
    }
}

int main(int argc, char const *argv[])
{
    explainPQ();
    return 0;
}
