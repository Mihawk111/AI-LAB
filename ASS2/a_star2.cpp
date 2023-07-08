#include <bits/stdc++.h>
#define INF FLT_MAX
using namespace std;

float euclDist(pair<int, int> p1, pair<int, int> p2)
{
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

struct Node
{
public:
    int cur;
    float dist;
    int prev;

    Node(int cur, float dist = 0.0, int prev = -1){ this->cur = cur; this->dist = dist; this->prev = prev; }
};

struct MyComp
{
public:
    bool operator () (Node p1, Node p2)
    {
        return p1.dist > p2.dist;
    }
};

float findDist(int src, int dest, vector<vector<pair<int, float>>> &g)
{
    for(pair<int, float> next: g[src]) if(next.first == dest) return next.second;
    return INF;
}

pair<float, pair<vector<int>, vector<int>>> aStar(int start, int end, vector<pair<int, int>> &pos, vector<vector<pair<int, float>>> &g)
{
    int n = g.size(), cur, parent; float dist, heurDist;
    vector<bool> vis(n, false);  // marked nodes ...
    vector<int> path, actualPath, prev(n, -1);
    priority_queue<Node, vector<Node>, MyComp> pq;  // cur , dist , prev
    pq.push({start, euclDist(pos[start], pos[end])});

    while(!pq.empty())
    {
        cur = pq.top().cur; dist = pq.top().dist; parent = pq.top().prev; pq.pop(); // cout << cur << "|" << dist << "|" << parent << endl;
        dist -= euclDist(pos[cur], pos[end]);
        if(vis[cur]) continue;
        vis[cur] = true, path.push_back(cur); prev[cur] = parent;
        if(cur == end) break;

        for(pair<int, float> ngh: g[cur]) if(!vis[ngh.first]) heurDist = euclDist(pos[ngh.first], pos[end]), pq.push({ngh.first, dist + ngh.second + heurDist, cur});
    }

    cur = end; dist = 0.0;
    while(cur != -1){ actualPath.push_back(cur); if(prev[cur] != -1) dist += findDist(prev[cur], cur, g);  cur = prev[cur]; }
    reverse(actualPath.begin(), actualPath.end());

    return {dist, {path, actualPath}};
}

void f1()
{
    int n = 10000, nR = 100, x, y;
    vector<vector<pair<int, float>>> g(n);
    vector<pair<int, int>> pos(n);
    for(int i = 0; i < n; i++)
    {
        x = i % nR, y = i / nR;  // Row major wise ...
        for(pair<int, int> p: vector<pair<int, int>>({{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}})) 
        {
            int X = p.first, Y = p.second;
            if(X >= 0 && Y >= 0 && X < nR && Y < nR) g[i].push_back({X + Y * nR, 1.0});
        }
        pos.push_back({x, y});
    }


    int start, end;
    cout << "Enter node to start (0 - indexed): ";
    cin >> x >> y; start = x + y * nR;
    cout << "Enter node to end (0 - indexed): ";
    cin >> x >> y; end = x + y * nR;
    cout << "Start = " << start << " , End = " << end << endl << endl;

    cout << "\nA* --> \n";
    pair<float, pair<vector<int>, vector<int>>> lol1 = aStar(start ,end, pos, g);
    cout << "Search Path :"; for(int e: lol1.second.first) cout << "(" << (e % nR) << "," << (e / nR) << ")" << " "; cout << endl;
    cout << "Actual Path: "; if(lol1.second.second.back() == end){ for(int e: lol1.second.second) cout << "(" << (e % nR) << "," << (e / nR) << ")" << " "; } else cout << "Not Found !!!"; cout << endl;
    cout << "Distance = "; if(lol1.second.second.back() == end) cout << lol1.first; else cout << "Not Found !!!"; cout << endl;

    exit(0);
}

int main()
{
    // f1();

    fstream f("nodes.txt", ios::in);

    int a, b, c, d, e = 0, h;
    f >> a; h = a; vector<vector<pair<int, float>>> g(a); vector<pair<int, int>> pos(a);
    while(a--){ f >> d; while(d--){ f >> b >> c; g[e].push_back({b, c}); } e++; } e = 0;
    while(h--){ f >> a >> b; pos[e++] = {a, b}; }

    f.close();

    int start, end;
    cout << "Enter node to start (1 - indexed): ";
    cin >> start;
    cout << "Enter node to end (1 - indexed): ";
    cin >> end;

    cout << "\nA* --> \n";
    pair<float, pair<vector<int>, vector<int>>> lol1 = aStar(start ,end, pos, g);
    cout << "Search Path :"; for(int e: lol1.second.first) cout << ((char)(e + 'A' - 1)) << " "; cout << endl;
    cout << "Actual Path: "; if(lol1.second.second.back() == end){ for(int e: lol1.second.second) cout << ((char)(e + 'A' - 1)) << " "; } else cout << "Not Found !!!"; cout << endl;
    cout << "Distance = "; if(lol1.second.second.back() == end) cout << lol1.first; else cout << "Not Found !!!"; cout << endl;

    return 0;
}