#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Event
{
    lli type, longMax, longMin, idx; // type = 1 -> rango, type = 2 -> puente
    Event(lli type, lli longMax, lli longMin, lli idx): type(type), longMax(longMax), longMin(longMin), idx(idx) {}
    Event():type(0), longMax(0), longMin(0), idx(0) {}
};

bool cmp(Event a, Event b)
{
    if(a.longMin == b.longMin)
    {
        if(a.type == b.type)
        {
            return a.longMax < b.longMax;
        }
        return a.type < b.type;
    }
    return a.longMin < b.longMin;
}


int main()
{
    fastIO();
    lli n, m; cin>>n>>m;
    vector< pair<lli,lli> > rangos(n);
    for(int i = 0; i<n; i++)
    {
        lli l, r; cin>>l>>r;
        rangos[i] = {l, r};
    }
    vector< Event > eventos;
    for(int i = 1; i<n; i++) // Agrego los eventos de updates
    {
        lli mx = rangos[i].second - rangos[i-1].first;
        lli mn = rangos[i].first - rangos[i-1].second;
        Event E(1, mx, mn, i);
        eventos.push_back(E);
    }

    for(int i = 1; i<=m; i++) // Agrego los eventos de queries
    {
        lli longitud; cin>>longitud;
        Event E(2, 0, longitud, i);
        eventos.push_back(E);
    }

    sort(all(eventos), cmp);
    set< pair<lli,lli> > check;
    vector< lli > ans(n+1, -1);


    for(Event E: eventos)
    {
        if(E.type == 1) // Update
        {
            check.insert({E.longMax, E.idx});
        }
        else // Query
        {
            auto itr = check.upper_bound({E.longMin, -1});
            if(itr == check.end())
                continue;
            
            pair< lli, lli > aux =  *itr;
            ans[ aux.second  ] =  E.idx;
            check.erase(itr);
        }
    }

    bool flag = true;
    for(int i = 1; i<n; i++)
    {
        if(ans[i] == -1) // Si hay un par de ciudades que no les pude asignar
        {
            cout << "No\n"; return 0;
        }
    }
    

    cout << "Yes\n";
    for(int i = 1; i<n; i++)
    {
        cout << ans[i] << " ";
    }   
    
    return 0;
}