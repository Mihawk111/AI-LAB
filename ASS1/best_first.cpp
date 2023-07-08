#include<bits/stdc++.h>
using namespace std;

class Compare {
public:
    bool operator()(pair<pair<int,string>,string> below, pair<pair<int,string>,string> above)
    {
        if (below.first.first > above.first.first) {
            return true;
        }
        return false;
    }
};

bool bestFirstSearch(unordered_map<string,vector<pair<int,string>>> graph, string root, string goal, string &vpath, string &spath){
    priority_queue<pair<int,string>, vector<pair<pair<int,string>,string>>, Compare> pq;
    unordered_set<string> visited;
    pq.push({{0,root},"->"+root});

    while(!pq.empty()){
        string temp=pq.top().first.second;
        string cpath=pq.top().second;
        pq.pop();
        visited.insert(temp);
        if(temp==goal){
            vpath=vpath+"->"+temp;
            spath=cpath;
            return true;
        }

        for(int i=0; i<graph[temp].size();++i){
            if(visited.find(graph[temp][i].second)==visited.end()){
                pq.push({graph[temp][i],cpath+"->"+graph[temp][i].second});
            }
        }

        vpath=vpath+"->"+temp;
    }

    return false;
}

int main(){
    unordered_map<string,vector<pair<int,string>>> graph;

    graph["A"]={{5,"B"},{3,"D"}};
    graph["B"]={{1,"C"}};
    graph["C"]={{6,"E"},{8,"G"}};
    graph["D"]={{2,"E"},{2,"F"}};
    graph["E"]={{4,"B"}};
    graph["F"]={{3,"G"}};
    graph["G"]={{4,"E"}};


    string vpath="",spath="";

    bestFirstSearch(graph,"A","C",vpath,spath);

    cout<<"Visited Sequence"<<vpath<<endl;
    cout<<"Solution path"<<spath<<endl;

    return 0;
}