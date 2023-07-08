#include<bits/stdc++.h>
using namespace std;

struct Node {
    int value;
    vector<Node*> next;
};

bool dfs(Node* root, int goal, string &path){
    if(root==NULL) return false;

    if(root->value==goal){ 
        
        path="->"+to_string(root->value);
        return true;
    }

    for(int i=0; i<root->next.size(); ++i){
        if(dfs(root->next[i],goal,path)){
            path="->"+to_string(root->value)+path;
            return true;
        }
    }
}

bool bfs(Node* root, int goal, string &path){
    if(root==NULL) return false;
}