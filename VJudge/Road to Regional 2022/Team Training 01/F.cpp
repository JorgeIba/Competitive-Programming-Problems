#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const int LOG_D = 32;
vector<lli> basis(LOG_D); 
lli sz_basis = 0;

void insert_vector(lli mask)
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

int main () {
	//fastIO();

    int n; cin>>n;
    vector<lli> nums(n);

    for(auto &x: nums) {
        cin>>x;
        insert_vector(x);
    }

    for(auto x: basis) {
        if(x || !x) {
            cout << bitset<9>(x).to_string() << endl;
        }
    }

	return 0;
}

