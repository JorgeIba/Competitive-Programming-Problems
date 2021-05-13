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

const int LOG_D = 20;


struct State
{
    lli size_basis;
    vector<lli> basis;
    State() {}
    State(lli size_basis, VLL basis): size_basis(size_basis), basis(basis) {}
};

vector<lli> basis(LOG_D); 
lli sz_basis = 0;
const lli MOD = 1e9+7;

void insert_vector(lli mask) //Zeros -> make zeros above basis[i]
{
    for(int i = LOG_D-1; i>=0; i--)
    {
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i])
        {
            basis[i] = mask;
			sz_basis++;
            return;
        }
        mask ^= basis[i];
    }
}

bool is_part(lli mask, VLL basis)
{
    for(int i = LOG_D-1; i>=0; i--)
    {
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i])
            return false;
        mask ^= basis[i];
    }
    return true;
}

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % MOD;
        b>>=1;
        a = a*a%MOD;
    }
    return res;
}

int main () {
	fastIO();
    lli n, q; cin>>n>>q;
    vector<lli> nums(n);
    vector< State > states(n);

    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        insert_vector(x);
        states[i] = State(sz_basis, basis);
    }

    while(q--)
    {
        lli l, x; cin>>l>>x;
        if(is_part(x, states[l-1].basis))
        {
            cout << binPow(2, l - states[l-1].size_basis) << endl;
        }
        else
        {
            cout << 0 << endl;
        }
        
    }
    
	return 0;
}