#include <bits/stdc++.h>
using namespace std;


class DisjointSet {
public:
    std::vector<int> parent;
    std::vector<int> size;

    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);

        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        } 
    }

    int findUltimateParent(int node) {
        if (node == parent[node]) {
            return node;
        }

        return parent[node] = findUltimateParent(parent[node]);
    }

    void unionBySize(int u, int v) {
        int ultParentU = findUltimateParent(u);
        int ultParentV = findUltimateParent(v);

        if (ultParentU == ultParentV) {
            return;
        }

        if (size[ultParentU] < size[ultParentV]) {
            parent[ultParentU] = ultParentV;
            size[ultParentV] += size[ultParentU];
        } else {
            parent[ultParentV] = ultParentU;
            size[ultParentU] += size[ultParentV];
        }
    }
    int countSets(){
        int size=parent.size(),count=0;
        for (int i = 0; i < size; i++)
        {
            if(parent[i]==i){
                count++;
            }
        }
        return count;
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int V=isConnected.size();
        DisjointSet ds(V);
        for(int i=0;i<V;i++){
            for (int j = 0; j < i; j++)
            {
                if (isConnected[i][j] == 1)
                {
                    ds.unionBySize(i, j);
                }
            }
            
        }
        return ds.countSets();
    }

};
