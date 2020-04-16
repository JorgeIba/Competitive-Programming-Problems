#include <bits/stdc++.h>
#define lli long long int

using namespace std;


void solve()
{
    lli n, m; cin>>n>>m;
    int layout[n];
    memset(layout, 0, sizeof(layout));
    vector< vector<int> > adjacency(n);
    for(int i=0; i<m; i++)
    {
        lli x,y; cin>>x>>y;
        x--;
        y--;
        adjacency[x].push_back(y);
        adjacency[y].push_back(x);
    }
    queue<int> toVisit;
    toVisit.push(0);
    unordered_set<int> check;

    while(!toVisit.empty())
    {
        int node = toVisit.front();
        int dist = layout[node];
        toVisit.pop();
        check.insert(node);
        for(int i=0; i<adjacency[node].size(); i++)
        {
            int nodeAux = adjacency[node][i];
            if(check.find(nodeAux) != check.end())
            {
                continue;
            }
            else
            {
                if(layout[nodeAux] == 0)
                {
                    layout[nodeAux] = dist+1;
                }
                toVisit.push(nodeAux);
            }
        }
    }

    

    
        cout<<layout[n-1]<<endl;
}

int main()
{
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }


}