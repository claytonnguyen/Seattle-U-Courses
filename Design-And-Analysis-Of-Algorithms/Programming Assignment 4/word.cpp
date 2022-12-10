//
// Created by Clayton Nguyen on 11/10/22.
//
// TIME EFFICIENCY:
// N = # of rows
// M = # of columns
// L = Length of the search word
// O(N) = N * M * 3^L

#include<iostream>
#include<vector>
#include<string>

using namespace std;

bool dfs(int u, int v, int idx, vector<vector<char>>& graph, vector<vector<bool>> visited, string str, int maxu, int maxv) {
    if(idx == str.length()){
        return true;
    }
    if(u >= 0 && u < maxu && v >= 0 && v < maxv){
        visited[u][v] = true;
        if(u-1 >= 0 && u-1 < maxu && v >= 0 && v < maxv){
            if(graph[u-1][v] == str[idx] && !visited[u-1][v]){
                if(dfs(u-1, v, idx+1, graph, visited, str, maxu, maxv)){
                    return true;
                };
            }
        }
        if(u >= 0 && u < maxu && v-1 >= 0 && v-1 < maxv){
            if(graph[u][v-1] == str[idx] && !visited[u][v-1]){
                if(dfs(u, v-1, idx+1, graph, visited, str, maxu, maxv)){
                    return true;
                };
            }
        }
        if(u+1 >= 0 && u+1 < maxu && v >= 0 && v < maxv){
            if(graph[u+1][v] == str[idx] && !visited[u+1][v]){
                if(dfs(u+1, v, idx+1, graph, visited, str, maxu, maxv)){
                    return true;
                };
            }
        }
        if(u >= 0 && u < maxu && v+1 >= 0 && v+1 < maxv){
            if(graph[u][v+1] == str[idx] && !visited[u][v+1]){
                if(dfs(u, v+1, idx+1, graph, visited, str, maxu, maxv)){
                    return true;
                };
            }
        }
    }
    return false;
}

int main(){
    int cases = 0, height, width;
    bool ret = false, found;
    char ele = '*';
    string str;
    cin >> cases;
    for(int i = 0; i < cases; i++) {
        cin >> str;
        cin >> height >> width;
        vector <vector<char>> vec;
        for (int j = 0; j < height; j++) {
            vector<char> v1;
            for (int k = 0; k < width; k++) {
                cin >> ele;
                v1.push_back(ele);
            }
            vec.push_back(v1);
        }
        vector<vector<bool>> visited(height, vector<bool> (width, false));
        for(int u = 0; u < vec.size(); u++){
            for(int v = 0; v < vec[u].size(); v++){
                if(vec[u][v] == str[0]){
                    ret = dfs(u, v, 1, vec, visited, str, height, width);
                    if(ret){
                        found = true;
                        cout << "YES" << endl;
                    }
                }
            }
        }
        if(found == false) {
            cout << "NO" << endl;
        }
    	found = false;
    }
    return 0;
}
