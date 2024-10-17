// class Solution {
// public:
//     int findCircleNum(vector<vector<int>>& isConnected) {
//         int n=isConnected.size();
//         vector<vector<int>> adjLs(n);

//         //!converting it to adjacency list
//         for(int i=0;i<n;i++){
//             for(int j=0;j<i;j++){
//                 if(isConnected[i][j]!=0){
//                     adjLs[i].push_back(j);
//                     adjLs[j].push_back(i);
//                 }
//             }
//         }

//         vector<int> vis(n,0);
//         int count=0;

//         for(int i=0;i<n;i++){
//             if(!vis[i]){
//                 count++;
//                 vis[i]=1;
//                 stack<int> st;
//                 st.push(i);
//                 while(!st.empty()){
//                     int root=st.top();
//                     st.pop();
//                     for(auto it:adjLs[root]){
//                         if(!vis[it]){
//                             vis[it]=1;
//                             st.push(it);
//                         }
//                     }
//                 }
//             }
//         }
//         return count;
//     }

// };