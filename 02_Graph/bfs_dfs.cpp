#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
        vector<vector<pair<int,int>>> adj;
        bool isDirected;
    public:
        Graph(int V,bool isDirected = false){
            adj.resize(V);
            this->isDirected=isDirected;
        }
        
        void addEdge(int u, int v, int w=1){
            adj[u].push_back({v,w});
            if(!isDirected){
                adj[v].push_back({u,w});
            }
        }

        vector<int> bfs(int start){
            vector<int> bfs_order;
            vector<bool> visited(adj.size(), false);
            queue<int> q;
            q.push(start);
            visited[start] = true;
            while(!q.empty()){
                int u = q.front();
                q.pop();
                bfs_order.push_back(u);
                for(auto it: adj[u]){
                    if(!visited[it.first]){
                        q.push(it.first);
                        visited[it.first] = true;
                    }
                }
            }
            return bfs_order;
        }

        vector<int> dfs(int start){
            vector<int> dfs_order;
            vector<bool> visited(adj.size(), false);
            stack<int> s;
            s.push(start);
            visited[start] = true;
            while(!s.empty()){
                int u = s.top();
                s.pop();
                dfs_order.push_back(u);
                for(auto it: adj[u]){
                    if(!visited[it.first]){
                        s.push(it.first);
                        visited[it.first] = true;
                    }
                }
            }
            return dfs_order;
        }

        // connected component, most optimal way

        vector<vector<int>> connectedComponents() {
            vector<vector<int>> components;
            vector<bool> visited(adj.size(), false);
            for (int i = 0; i < adj.size(); i++) {
                if (!visited[i]) {
                    vector<int> component;
                    stack<int> s;
                    s.push(i);
                    visited[i] = true;
                    while (!s.empty()) {
                        int u = s.top();
                        s.pop();
                        component.push_back(u);
                        for (auto it : adj[u]) {
                            if (!visited[it.first]) {
                                s.push(it.first);
                                visited[it.first] = true;
                            }
                        }
                    }
                    components.push_back(component);
                }
            }
            return components;
        }

        bool isDirected(){
            return isDirected;
        }

        // SCC works best with kosaraju algorithm
        




};


int main() 
{
    
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    for(auto it: g.bfs(0)){
        cout<<it<<" ";
    }
    cout<<endl;

    for(auto it: g.dfs(0)){
        cout<<it<<" ";
    }
    cout<<endl;

    for(auto it1:g.connectedComponents()){
        for(auto it2:it1){
            cout<<it2<<" ";
        }
        cout<<endl;
    }
    cout<<endl;




    return 0;
}