#include<bits/stdc++.h>
using namespace std;

bool _idfs(unordered_map<string,vector<string>> graph, string root, string goal, int depth, string &seq, string &path);

bool idfs(unordered_map<string,vector<string>> graph, string root, string goal, int maxdepth, string &seq, string &path){
    seq="DEPTH\tPATH\n";
    path="";
    for(int i=0; i<=maxdepth; ++i){
        seq=seq+to_string(i)+"\t";
        if(_idfs(graph,root,goal,i,seq,path)){
            return true;
        }
        seq=seq+"\n";
    }

    path="->Not found...";
    return false;
}

bool _idfs(unordered_map<string,vector<string>> graph, string root, string goal, int depth, string &seq, string &path){
    seq=seq+"->"+root;
    if(root==goal){ 
        
        path="->"+root;
        return true;
    }

    if(depth==0) return false;

    for(int i=0; i<graph[root].size(); ++i){
        if(_idfs(graph,graph[root][i],goal,depth-1,seq,path)){
            path="->"+root+path;
            return true;
        }
    }

    return false;
}

int main(){
    unordered_map<string,vector<string>> graph;

    graph["A"].push_back("B");
    graph["A"].push_back("C");

    graph["B"].push_back("D");
    graph["B"].push_back("E");

    graph["C"].push_back("F");
    graph["C"].push_back("G");
    graph["C"].push_back("H");

    graph["D"].push_back("I");
    graph["D"].push_back("J");

    graph["E"].push_back("K");
    graph["E"].push_back("L");
    graph["E"].push_back("M");

    graph["F"].push_back("N");

    graph["H"].push_back("O");
    graph["H"].push_back("P");


    cout<<"Enter maxdepth:";
    int depth;
    cin>>depth;
    string path;
    string seq;

    idfs(graph,"A","P",depth,seq,path);
    cout<<"SEQ:\n"<<seq<<endl<<endl;
    cout<<"PATH\t"<<path<<endl;

    return 0;
}