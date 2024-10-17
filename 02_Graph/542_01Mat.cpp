#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        queue<pair<int,int>> q;
        int childs[] = {0, 1, 0, -1, 0};
        int m = mat.size(), n = mat[0].size();
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++){
                if(mat[i][j] == 0) q.push({i,j});
                else mat[i][j] = -1; // unprocessed
            }
        
        while(!q.empty()){
            auto [r, c] = q.front();
            q.pop();
            
            for(int i = 0; i < 4; i++){
                int nr = r + childs[i], nc = c + childs[i+1];
                if(nr < 0 || nr >= m || nc < 0 || nc >= n || mat[nr][nc] != -1)
                    continue;
                mat[nr][nc] = mat[r][c] + 1;
                q.push({nr, nc});
            }
        }
        
        return mat;
    }
};


int main(int argc, char const *argv[])
{
    for(int i=0;i<10;i++)
    
    return 0;
}

