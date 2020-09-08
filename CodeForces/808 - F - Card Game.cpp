#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

struct Edge{
    lli to, flow = 0, capacity;
    Edge* res;
    Edge(lli to, lli capacity): to(to), capacity(capacity) {}
    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

struct Card{
    lli p, c, l;
    Card(): p(0), c(0), l(0) {}
    Card(lli p, lli c, lli l): p(p), c(c), l(l) {}

    bool operator<(Card a) const{
        return p < a.p;
    }
};

vector< vector< Edge* > > adjList;
vector< Card > cards;
lli n, k; 

void addEdge(lli u, lli v, lli capacity)
{
    Edge* uv = new Edge(v, capacity);
    Edge* vu = new Edge(u, 0);
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}


vector< lli > dis, pos;
const lli INF = numeric_limits<int>::max();

lli blockingFlow(lli u, lli t, lli minimo)
{
    if(u==t) return minimo;
    for(lli &i = pos[u]; i<adjList[u].size(); i++)
    {
        Edge* v = adjList[u][i];
        if(v->capacity > v->flow && dis[u] + 1 == dis[v->to])
        {
            lli f = blockingFlow(v->to, t, min(minimo, v->capacity - v->flow));
            if(f>0)
            {
                v->addFlow(f);
                return f;
            }
        }
    }
    return 0;  
}


lli dinic(lli s, lli t)
{
    lli maxFlow = 0;
    dis[t] = 0;
    while(dis[t] != -1)
    {
        fill(all(dis), -1);
        queue<lli> q;
        q.push(s);
        dis[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge* v: adjList[u])
            {
                if(dis[v->to] == -1 && v->capacity > v->flow)
                {
                    dis[v->to] = dis[u] + 1;
                    q.push(v->to);
                }
            }
        }
        if(dis[t] != -1)
        {
            lli f = 0;
            fill(all(pos), 0);
            while(f = blockingFlow(s, t, INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;
}


vector< bool > isPrime;

void sieve(lli n)
{
    isPrime.resize(n+1, true);
    isPrime[0] = isPrime[1] = false;
    for(lli i = 4; i<=n; i += 2) isPrime[i] = false;
    for(lli i = 3; i<=n; i+=2)
        if(isPrime[i])
            for(lli j = i*i; j<=n; j+=2*i)
                isPrime[j] = false;
        
}

bool check(lli level)
{
    //adjList.clear(); adjList.resize(n+1);
    vector< Card > pares, impares;
    lli total = 0;
    for(int i = 0; i<n; i++)
    {
        if(cards[i].l <= level){
            total += cards[i].p;
            if(cards[i].c & 1)
                impares.push_back(cards[i]);
            else
                pares.push_back(cards[i]);
        }
    }
    lli ni = SZ(impares), np = SZ(pares);
    lli sz = ni + np;

    adjList.clear(); adjList.resize(sz+3);
    dis.clear(); dis.resize(sz+3, -1);
    pos.clear(); pos.resize(sz+3, 0);

    lli s = 0, t = ni + np + 1;
    for(int i = 1; i<=ni; i++)
    {
        for(int j = 1; j<=np; j++)
        {
            if(isPrime[impares[i-1].c + pares[j-1].c])
            {
                addEdge(i, ni+j, INF);
            }
        }
    }
    for(int i = 1; i<=ni; i++)
    {
        addEdge(s, i, impares[i-1].p);
    }
    for(int i = 1; i<=np; i++)
    {
        addEdge(ni+i, t, pares[i-1].p);
    }
    lli maxFlow = dinic(s, t);
    lli res = total - maxFlow;
    //cerr << total << " " << maxFlow <<" "<< res << " " << k << endl;
    if(res >= k)
    {
        return true;
    }
    else
    {
        return false;
    }

}

int main () {
	fastIO();
    sieve(250000);
    cin>>n>>k;
    Card maximoUno;
    for(int i = 0; i<n; i++)
    {
        lli p, c, l; cin>>p>>c>>l;
        if(c == 1){
            maximoUno = max(maximoUno, {p, c, l});
        }
        else
        {
            cards.push_back({p, c, l});
        }
    }
    if(maximoUno.p != 0) cards.push_back(maximoUno);

    if(cards.size() == 1)
    {
        if(cards[0].p >= k)
        {
            cout << cards[0].l << endl;
        }
        else
        {
            cout << -1 << endl;
        }
        return 0;
    }

    //cout << check(2) << endl;
    //cout << check(3) << endl;
    //cout << check(4) << endl;

    
    lli l = 1, r = 1000000, res = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if(check(mid))
        {
            res = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }

    cout << res << endl;

	return 0;
}