//
//  main.cpp
//  130b_mst
//
//  Created by Nick Ray on 5/2/17.
//  Copyright © 2017 test. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#include <cstdint>
#include <limits>
#include <algorithm>

using namespace std;

#define node pair<double, double>
#define INT_MAX std::numeric_limits<std::int32_t>::max()

class graph{
public:
    
    vector<vector<double>> edges;
    
    bool isConnected(int a, int b){
        return edges[a][b]!=0;
    }
    graph(int n){
       edges = vector<vector<double>>(n, vector<double>(n, 0));
    }
    
};

vector<int> primMST(graph& g, int n)
{
    
    vector<int> parent(n, 0);
    vector<bool> mstSet(n, false);
    vector<double> key(n, INT_MAX);
    
    key[0] = 0;
    parent[0] = -1;
    
    for (int j = 0; j < n-1; j++)
    {
        double min = INT_MAX;
        int min_index;
        
        for (int i = 0; i < n; i++)
            if (mstSet[i] == false && key[i] < min){
                min = key[i];
                min_index = i;
            }
        
        mstSet[min] = true;
        for (int i = 0; i < n; i++)
            if (g.edges[min][i]!=0 && !mstSet[i] && g.edges[min][i]< key[i]){
                parent[i]  = min;
                key[i] = g.edges[min][i];
            }
    }
    return parent;
}


int main(int argc, const char * argv[]) {
    
    vector<node> nodes;
    int n, vn, count = 0;
    cin >> n;
    vector<vector<bool>> isEdge = vector<vector<bool>>(n, vector<bool>(n, false));
    graph g(n);
    string line;
    while (nodes.size()<n && std::getline(cin, line))
    {
        std::istringstream iss(line);
        double a, b;
        if (!(iss >> a >>std::skipws >> b)) {
            continue;
        }
        nodes.push_back(node(a, b));
    }
    cin >> vn;
    
    while (count<vn && std::getline(cin, line))
    {
        std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >>std::skipws >> b)) {
            continue;
        }
        isEdge[a][b] = true;
        isEdge[b][a] = true;
        count++;
    }
    
    if(count < vn)
        cout << "not all input was taken in uh" << endl;
    
    double x1, y1, x2, y2, d;
    
    for(int i=0;i<isEdge.size(); i++){
        for(int j=0;j<isEdge[i].size(); j++){
            if(isEdge[i][j] || vn == 0){
                x1 = nodes[i].first;
                y1 = nodes[i].second;
                x2 = nodes[j].first;
                y2 = nodes[j].second;
                d = sqrt(pow(y2 - y1, 2) + pow(x2 - x1, 2));
                g.edges[i][j] = d;
                g.edges[j][i] = d;
            }
        }
    }
    
    vector<int> mst = primMST(g, n);
    vector<pair<int, int>> mstEdges (n, pair<int, int>(0,0));
    
    for (int i = 1; i < n; i++)
        mstEdges[i].first = min(mst[i], i), mstEdges[i].second = max(i, mst[i]);
    
    sort(mstEdges.begin(), mstEdges.end());
    
    for (int i = 1; i < n; i++)
        cout << mstEdges[i].first << " " << mstEdges[i].second << endl;

    return 0;
}
