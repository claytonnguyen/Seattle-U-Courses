//
// Created by Clayton Nguyen on 11/10/22.
//
// TIME EFFICIENCY:
// N = # of rows
// M = # of columns
// O(N) = N * M 

#include<iostream>
#include<vector>

using namespace std;

void dfs(int u, int v, vector<vector<char>>& graph, int& maxu, int& maxv){
    if(u >= 0 && u < maxu && v >= 0 && v < maxv){
        graph[u][v] = '*';
    }
    if(u-1 >= 0 && u-1 < maxu && v >= 0 && v < maxv){
        if(graph[u-1][v] == '#'){
            dfs(u-1, v, graph, maxu, maxv);
        }
    }
    if(u >= 0 && u < maxu && v-1 >= 0 && v-1 < maxv){
        if(graph[u][v-1] == '#'){
            dfs(u, v-1, graph, maxu, maxv);
        }
    }
    if(u+1 >= 0 && u+1 < maxu && v >= 0 && v < maxv){
        if(graph[u+1][v] == '#'){
            dfs(u+1, v, graph, maxu, maxv);
        }
    }
    if(u >= 0 && u < maxu && v+1 >= 0 && v+1 < maxv){
        if(graph[u][v+1] == '#'){
            dfs(u, v+1, graph, maxu, maxv);
        }
    }
}

int main(){
    int cases = 0, height, width, num = 0;
    char ele  = '*';
    cin >> cases;
    for(int i = 0; i < cases; i++){
        cin >> height >> width;
        vector<vector<char>> vec;
        for(int j = 0; j < height; j++){
            vector<char> v1;
            for(int k = 0; k < width; k++){
                cin >> ele;
                v1.push_back(ele);
            }
            vec.push_back(v1);
        }
        for(int u = 0; u < vec.size(); u++){
            for(int v = 0; v < vec[u].size(); v++){
                if(vec[u][v] == '#'){
                    dfs(u,v, vec, height, width);
                    num++;
                }
            }
        }
        cout << num << endl;
        num = 0;
    }
    return 0;
}

