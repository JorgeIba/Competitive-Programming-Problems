lli query(lli u, lli k)
{
    lli depthK = depth[u] - k;
    lli res = cost[u][0];
    //lli res = INF;
    //cout<<" "<<depth[u] << " " << depthK << endl;
    for(int i = logN; i>=0; i--)
    {
        if(depth[u] >= depthK + (1<<i))
        {
            res = min(res, cost[u][i+1]);
            //cout<<" ASD " << i << " " << cost[u][i] << endl;

            u = parent[u][i];
        }
    }
    return res;
}