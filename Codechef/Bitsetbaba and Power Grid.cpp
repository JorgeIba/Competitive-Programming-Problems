#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

/*
    If very test case, don't forget
    init basis and sz_basis
*/
const int LOG_D = 30;

vector<lli> basis(LOG_D); 
lli sz_basis = 0;

void insert_vector(lli mask)
{
    for(int i = LOG_D-1; i>=0; i--)
    {
        if(!(mask & (1<<i))) continue;

        if(!basis[i])
        {
            basis[i] = mask;
            sz_basis++;
            return;
        }
        mask ^= basis[i];
    }
}

void solve()
{
    int k, m; cin>>k>>m;
    fill(all(basis), 0);
    sz_basis = 0;

    for(int i = 0; i<m; i++)
    {
        lli mask; cin>>mask;
        insert_vector(mask);
    }

    cout << (1<<(k-sz_basis)) << endl;
}

int main () {
	fastIO();
    lli t; cin>>t;
    while(t--) solve();
    
	return 0;
}