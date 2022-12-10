//
// Created by Clayton Nguyen on 11/10/22.
//
// TIME EFFICIENY:
// N = # of rows
// M = # of columns
// O(N) = N * M

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node {
    int x;
    int y;
    int dist;
};

int bfs(vector<vector<char>>& graph, node p, int& maxx, int& maxy){
    queue <node> q;
    q.push(p);
    while (!q.empty()) {
        node search = q.front();
        int x = search.x;
        int y = search.y;
        int dist = search.dist;
        q.pop();

        if(x >= 0 && x < maxx && y >= 0 && y < maxy){
            if(graph[x][y] == 'E'){
                return dist;
            }
            if(graph[x][y] == '#'){
                continue;
            }
            else{
                graph[x][y] = '#';
            }
        }
        if(x-1 >= 0 && x-1 < maxx && y >= 0 && y < maxy){
            if(graph[x-1][y] == '.' || graph[x-1][y] == 'E'){
                node v1;
                v1.x = x-1;
                v1.y = y;
                v1.dist = dist + 1;
                q.push(v1);
            }
        }
        if(x >= 0 && x < maxx && y-1 >= 0 && y-1 < maxy){
            if(graph[x][y-1] == '.' || graph[x][y-1] == 'E'){
                node v2;
                v2.x = x;
                v2.y = y-1;
                v2.dist = dist + 1;
                q.push(v2);
            }
        }
        if(x+1 >= 0 && x+1 < maxx && y >= 0 && y < maxy){
            if(graph[x+1][y] == '.' || graph[x+1][y] == 'E'){
                node v3;
                v3.x = x+1;
                v3.y = y;
                v3.dist = dist + 1;
                q.push(v3);
            }
        }
        if(x >= 0 && x < maxx && y+1 >= 0 && y+1 < maxy){
            if(graph[x][y+1] == '.' || graph[x][y+1] == 'E'){
                node v4;
                v4.x = x;
                v4.y = y+1;
                v4.dist = dist + 1;
                q.push(v4);
            }
        }
    }
    return -1;
}

int main(){
    int cases = 0, height, width;
    char ele  = '*';
    cin >> cases;
    for(int i = 0; i < cases; i++) {
        cin >> height >> width;
        vector <vector<char>> vec;
        node first;
        for (int j = 0; j < height; j++) {
            vector<char> v1;
            for (int k = 0; k < width; k++) {
                cin >> ele;
                if (ele == 'S') {
                    first.x = j;
                    first.y = k;
                    first.dist = 0;
                }
                v1.push_back(ele);
            }
            vec.push_back(v1);
        }
        cout << bfs(vec, first, height, width) << endl;
    }
    return 0;
}
