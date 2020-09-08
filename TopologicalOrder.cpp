#include <bits/stdc++.h>
#define lli long long int

using namespace std;

bool visited[400100];
vector< priority_queue< pair<lli,lli> > > adj;

bool dfs(lli indexNode, lli &indexAnswer, vector<lli> &answer)
{
    if(visited[indexNode])
    {
        return false;
    }
    visited[indexNode] = true;
    lli sizeNeighbor = adj[indexNode].size();
    while(!adj[indexNode].empty())
    {
        lli u = adj[indexNode].top().second;
        adj[indexNode].pop();
        if( dfs(u, indexAnswer, answer) )
        {
            indexAnswer--;
        }
    }
    answer[indexAnswer] = indexNode;
    return true;
}


vector<lli> topologicalOrder()
{
    vector<lli> answer( adj.size() );
    lli index = adj.size() - 1;
    for(lli i=1; i<adj.size(); i++)
    {       
        if(dfs(i, index, answer))
        {
            index--;
        }
    }
    return answer;
}



int main()
{
    lli n, k; cin>>n;
    adj.resize(n);

    for(int i = 0; i<n; i++)
    {
        lli minutes, dep; cin>>minutes>>dep;
        forn(j,0,dep)
        {
            lli v; cin>>v;
            
        }
    }
    return 0;
}