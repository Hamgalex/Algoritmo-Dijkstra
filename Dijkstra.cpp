#include<bits/stdc++.h>
using namespace std;

const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;
vector<vector<int>> costvector;
int cost=0;

void dijkstra(int s, vector<int> & d, vector<int> & p)
{

    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    vector<bool> u(n, false);

    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        u[v] = true;
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}

vector<int> restore_path(int s, int t, vector<int> const& p)
{
    vector<int> path;

    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());

    for(int i=1;i<path.size();i++)
    {
        cost+=costvector.at(path.at(i-1)).at(path.at(i));
    }

    return path;
}

int main()
{

    int N,M;
    cin>>N>>M;
    vector<pair<int,int>> aux1;
    adj.assign(N,aux1);
    vector<int>aux2;
    aux2.assign(N,0);
    costvector.assign(N,aux2);


    vector<int>d,p;

    for(int i=0;i<M;i++)
    {
        int a,b,c;
        pair<int,int> pairaux;

        cin>>a>>b>>c;
        pairaux.first=b;
        pairaux.second=c;
        adj.at(a).push_back(pairaux);

        costvector.at(a).at(b)=c;
    }

    int s,t;
    cin>>s>>t;

    dijkstra(s,d,p);

    vector<int> path;
    path=restore_path(s,t,p);

    cout<<endl;
    for(auto& i:path)
        cout<<i<<" ";

    cout<<endl<<"z = "<<cost;
    return 0;
}
