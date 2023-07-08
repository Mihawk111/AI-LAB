#include<bits/stdc++.h>
using namespace std;

bool dfs(vector<vector<int>> graph, int root, int goal, string &path){

    if(root==goal){ 
        
        path="->"+to_string(root);
        return true;
    }

    for(int i=0; i<graph[root].size(); ++i){
        if(dfs(graph,graph[root][i],goal,path)){
            path="->"+to_string(root)+path;
            return true;
        }
    }

    return false;
}

bool bfs(vector<vector<int>> graph, int root, int goal, string &path){
    if(graph.size()==0) return false;

    queue<int> q;

    q.push(root);

    while(q.empty()==false){
        int temp=q.front();
        q.pop();
        if(temp==goal){
            path=path+"->"+to_string(temp);
            return true;
        }
        for(int i=0; i<graph[temp].size(); ++i){
            q.push(graph[temp][i]);
        }
        path=path+"->"+to_string(temp);
    }
    return false;
}

int main(){
    vector<vector<int>> graph;

    graph.push_back(vector<int> {});
    graph.push_back(vector<int> {8,5,2});
    graph.push_back(vector<int> {9});
    graph.push_back(vector<int> {});
    graph.push_back(vector<int> {});
    graph.push_back(vector<int> {});
    graph.push_back(vector<int> {10,7});
    graph.push_back(vector<int> {});
    graph.push_back(vector<int> {6,4,3});
    graph.push_back(vector<int> {});
    graph.push_back(vector<int> {});

    string path;

    dfs(graph,1,3,path);
    cout<<"DFS"<<path<<endl;
    path="";
    bfs(graph,1,3,path);
    cout<<"BFS"<<path<<endl;

    return 0;
}