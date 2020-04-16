#include <bits/stdc++.h>
#define lli long long int

using namespace std;


bool visited(lli index, unordered_set<lli> visitedNodes)
{
    if(visitedNodes.find(index) != visitedNodes.end())
    {
        return true;
    }
    return false;
}


bool dfs(lli indexNode, unordered_set<lli> &visitedNodes, lli &indexAnswer, vector< vector< lli> > adj, vector<lli> &answer)
{
    if(visited(indexNode, visitedNodes))
    {
        return false;
    }
    visitedNodes.insert(indexNode);
    lli sizeNeighbor = adj[indexNode].size();
    for(lli i=0; i<sizeNeighbor; i++)
    {
        if( dfs(adj[indexNode][i], visitedNodes, indexAnswer, adj, answer) )
        {
            indexAnswer--;
        }
    }
    answer[indexAnswer] = indexNode;
    return true;
}


vector<lli> topologicalOrder(vector< vector<lli> > adj)
{
    unordered_set<lli> visitedNodes;  
    vector<lli> answer( adj.size() );
    lli index = adj.size() - 1;
    for(lli i=1; i<adj.size(); i++)
    {       
        if(dfs(i, visitedNodes, index, adj, answer))
        {
            index--;
        }
    }
    return answer;
}



int main()
{
    lli n, k; cin>>n>>k;
    vector< vector<lli> > adj(n);
    for(lli i=0; i<k;  i++)
    {
        lli x, y; cin>>x>>y;
        adj[x].push_back(y);
    }

    vector<lli> ans = topologicalOrder(adj);

    for(auto x: ans)
    {
        cout<<x<<" ";
    }

    return 0;
}