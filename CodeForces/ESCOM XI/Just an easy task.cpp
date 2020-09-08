#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<lli> Phi;
void phiSieve(int n)
{
	Phi.resize(n + 1);
	for(int i = 1; i <= n; ++i) Phi[i] = i;
	for(int i = 2; i <= n; ++i)
		if(Phi[i] == i)
			for(int j = i; j <= n; j += i)
				Phi[j] -= Phi[j] / i;
}

const lli maxN = 2.2 * 1e6;


vector<lli> getDivs(lli n)
{
    vector<lli> divs;
    for(int i = 1; i*i<=n; i++)
    {
        if(n%i == 0)
        {
            divs.push_back(i);
            if(i*i != n)
            {
                divs.push_back(n/i);
            }
        }
    }
    return divs;
}


int main()
{
    fastIO();
    lli n; cin>>n;
    phiSieve(n+1);
    vector< lli > fr(n+1), gcds(n+1);
    for(lli i = 1; i<=n; i++)
    {
        gcds[i] = __gcd(i, n);
    }

    for(int i = 1; i<=n; i++)
    {
        lli gcd = gcds[i];
        if(fr[gcd] != 0) continue;
        else
        {
            vector< lli > divs = getDivs(gcd);
            for(auto d: divs)
            {
                fr[gcd] += d*Phi[n/d];
            }
        }
    }

    cout << fr[n] << " ";
    for(int i = 1; i<n; i++) cout << fr[ gcds[i] ] << " ";
    
    return 0;
}