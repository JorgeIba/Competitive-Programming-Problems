#include <bits/stdc++.h>
#define lli long long int

using namespace std;

struct evento
{
    lli x, y, type; //type 1 -> slot, type 2 -> coins
    lli index;
};

bool compare(evento a, evento b)
{
    if(a.type != b.type)
    {
        if(a.x == b.x)
        {
            if(a.y == b.y)
            {
                return a.type > b.type;
            }
            return a.y > b.y;
        }
    }
    else
    {
        if(a.x == b.x)
        {
            if(a.y == b.y)
            {
                return a.index > b.index;
            }
            return a.y > b.y;
        }
    }
    
    return a.x < b.x;
}

lli MAXN = 100010;
const lli INF = 1000000000LL;
vector<lli> ST(2*MAXN, INF);


lli query(lli l, lli r)
{
    lli res = INF;
    for(l+=MAXN, r+=MAXN; l<=r; l>>=1, r>>=1)
    {
        if(l&1) res = min(res, ST[l++]);   
        if(~r&1) res = min(ST[r--],res);
    }
    return res;
}

void update(lli index, lli value)
{
    index += MAXN;
    ST[index] = min(value, ST[index]);
    for(; index; index>>=1)
    {
        ST[index>>1] = min(ST[index], ST[index^1]);
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector< evento > eventos(n);
    lli i = 1;
    for(auto &x: eventos)
    {
        cin>>x.x>>x.y;
        x.type = 1;
        x.index = i++;
    }
    lli m; cin>>m;
    eventos.resize(n+m);
    for(int i = n; i<m+n; i++)
    {
        cin>>eventos[i].x>>eventos[i].y;
        eventos[i].type = 2;
    }
    sort(eventos.begin(), eventos.end(), compare);
    /*
    for(auto x: eventos)
    {
        cout<<x.x<<" "<<x.y<<" "<<x.type<<" "<<x.index<<endl;
    }
    */
    
    lli res = 0;
    for(int i = n + m - 1; i>=0; i--)
    {
        evento a = eventos[i];
        if(a.type == 1)
        {
            update(a.y, a.index);
        }
        if(a.type == 2)
        {
            res += query(1, a.y);
        }
    }
    cout<<res<<endl;

    return 0;
}
