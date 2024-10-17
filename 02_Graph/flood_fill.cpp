#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        queue<pair<int,int>> q;
        int r=image.size();
        int c=image[0].size();
        q.push({sr,sc});
        while(!q.empty()){
            auto head=q.front(); 
            q.pop();
            int i=head.first;
            int j=head.second;
            int originalColor=image[i][j];
            if(originalColor==color){
                continue;
            }
            image[i][j]=color;
            pair<int,int> delta[]={{0,1},{0,-1},{1,0},{-1,0}};
            for(auto it:delta){
                int x=i+it.first;
                int y=j+it.second;
                if(x>=0 && x<r && y>=0 && y<c && image[x][y]==originalColor){
                    q.push({x,y});
                }
            }
        }
    }
};


int main(int argc, char const *argv[])
{
    vector<vector<int>> image={{1,1,1},{1,1,0},{1,0,1}};
    return 0;
}

