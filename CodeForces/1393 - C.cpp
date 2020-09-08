#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< lli > cont;
vector< pair<lli,lli> > aux;
lli n; 
const lli maxN = 1e5+10;
bool check(lli mid)
{
    if(mid == 0) return true;
    priority_queue< pair< lli,lli > > pq;
    for(auto x: aux) pq.push(x);
    vector< pair<lli,lli> > ans(n+1);
    for(int i = 1; i<=n; i++)
    {
        if(pq.empty()) return false;
        auto curr = pq.top();
        pq.pop();
        if(ans[i].first > 0)
        {
            pq.push(ans[i]);
        }

        if(curr.first > 1)
        {
            ans[i] = curr;
            if(i+mid >= n)
            {
                return false;
            } 
            curr.first--;
            ans[i+mid] = curr;
        }
        else
        {
            ans[i] = curr;
        }
    }
    return true;
}

void solve()
{
    cin>>n;
    cont.clear(); cont.resize(maxN+100, 0);
    aux.clear();
    forn(i, 0, n)
    {
        lli x; cin>>x;
        cont[x]++;
    }
    for(int i = 1; i<=maxN; i++)
    {
        if(cont[i] > 0)
        {
            aux.push_back({cont[i], i});
        }
    }

    sort(aux.rbegin(), aux.rend());
    //cout << check(1) << endl;
    
    lli l = 0, r = n-1, res = 0;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if(check(mid))
        {
            res = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    cout << (res) << endl;
    
}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();

    
    return 0;
}