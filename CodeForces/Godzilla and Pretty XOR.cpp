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
    O(d) -> !zeros
    O(d + d) -> zeros
*/
const int LOG_D = 30;
vector<lli> basis(LOG_D); 
lli sz_basis = 0;

void insert_vector(lli mask, bool zeros = false) //Zeros -> make zeros above basis[i]
{
    for(int i = LOG_D-1; i>=0; i--)
    {
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i])
        {
            basis[i] = mask;
			sz_basis++;

			if(!zeros) return;

			for(int j = 0; j<LOG_D; j++)
			{
				if(j==i) continue;
				if(j < i)
				{
					if(basis[i] & (1LL << j)) basis[i] ^= basis[j];
				}
				else
				{
					if(basis[j] & (1LL << i)) basis[j] ^= basis[i];
				}
			}
            return;
        }
        mask ^= basis[i];
    }
}

int main () {
	fastIO();
    lli n; cin>>n;
    set<lli> check;

    for(int i = 0; i<n; i++)
    {
        lli t, k; cin>>t>>k;
        if(t == 1)
        {
            if(check.count(k)) continue;
            insert_vector(k, true);
        }
        else
        {
            lli ans = 0;
            vector<lli> masks;
            k--;
            for(int d = 0; d<LOG_D; d++)
            {
                if(basis[d]) masks.push_back(basis[d]);
            }
            for(int j = 0; j<LOG_D; j++)
            {
                if(k & (1LL << j)) ans ^= masks[j];
            }
            cout << ans << endl;
        }
        

    }

	return 0;
}