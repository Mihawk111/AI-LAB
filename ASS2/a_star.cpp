#include<bits/stdc++.h>
using namespace std;

float edist(pair<int,int> p1, pair<int,int> p2){
    return sqrt((p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second));
}

class Compare {
public:
    bool operator()(pair<float,string> below, pair<float,string> above)
    {
        if (below.first > above.first) {
            return true;
        }
        return false;
    }
};

void addEdge(unordered_map<string,pair<pair<int,int>,vector<string>>> &graph,string a, string b){
    graph[a].second.push_back(b);
    graph[b].second.push_back(a);
}

bool aStarSearch(unordered_map<string,pair<pair<int,int>,vector<string>>> graph, string root, string goal, string &seq, string &path){
    priority_queue<pair<int,string>, vector<pair<int,string>>, Compare> pq;
    unordered_map<string,float> visited;
    seq="";
    path="";
    pq.push({edist(graph[goal].first,graph[root].first),root});

    while(!pq.empty()){
        float sf=pq.top().first;
        string s=pq.top().second;
        pq.pop();

        visited[s]=sf;

        seq=seq+"->"+s;

        if(s==goal){
            return true;
        }

        for(int i=0; i<graph[s].second.size();++i){
            string temp=graph[s].second[i];
            float tf=edist(graph[temp].first,graph[goal].first)+sf;
            if(visited.find(temp)==visited.end()){
                pq.push({tf,temp});
            }
            else if(visited[temp]>tf){
                pq.push({tf,temp});
            }
        }
    }
}