#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int orangesRotting(vector<vector<int>> &grid)
    {
        int row = grid.size();
        int column = grid[0].size();
        // pair saying {{i,j},time}
        queue<pair<pair<int, int>, int>> q;
        int time = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (grid[i][j] == 2)
                {
                    q.push({{i, j}, time});
                }
            }
        }
        while (!q.empty())
        {
            auto curr = q.front();
            q.pop();
            time = curr.second;
            int i = curr.first.first;
            int j = curr.first.second;
            cout << "iterating for " << i << " " << j << endl;
            int arr[] = {-1, 1, 0};
            for (auto itROW : arr)
            {
                for (auto irCOL : arr)
                {
                    if ((i + itROW) < row && (i + itROW) >= 0 && (j + irCOL) < column && (j + irCOL) >= 0 && grid[i + itROW][j + irCOL] == 1)
                    {
                        if (itROW == 0 || irCOL == 0)
                        {
                            grid[i + itROW][j + irCOL] = 2;
                            cout << irCOL << " " << itROW << endl;
                            q.push({{i + itROW, j + irCOL}, time + 1});
                        }
                    }
                }
            }
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (grid[i][j] == 1)
                {
                    return -1;
                }
            }
        }
        return time;
    }
};



//the below one has best runtime

class SolutionV2 {
public:
     int orangesRotting(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        int m = grid.size(), n = grid[0].size(), days = 0, tot = 0, cnt = 0;
        queue<pair<int, int>> rotten;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] != 0) tot++;
                if(grid[i][j] == 2) rotten.push({i, j});
            }
        }
        
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        
        while(!rotten.empty()){
            int k = rotten.size();
            cnt += k; 
            while(k--){
                int x = rotten.front().first, y = rotten.front().second;
                rotten.pop();
                for(int i = 0; i < 4; ++i){
                    int nx = x + dx[i], ny = y + dy[i];
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != 1) continue;
                    grid[nx][ny] = 2;
                    rotten.push({nx, ny});
                }
            }
            if(!rotten.empty()) days++;
        }
        
        return tot == cnt ? days : -1;
    }

};