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

vector<lli> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			primes.push_back(i);
			if(i * i <= n)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}

const int maxN = 1e6+5;

bool valid(lli p, lli k)
{
    if (k % p == p-2) return true;
    return false;
}


map<lli,vector<int>> ans;
set<lli> seen;
void process() // (k+2) = p*q
{
    for(auto p: primes)
    {
        for(lli i = 1; i*p < maxN; i++)
        {
            if(seen.count(i*p - 2)) ans[i*p-2].push_back(p);
        }
    }
}


int main () {
	fastIO();
    primesSieve(maxN);
    
    lli t; cin>>t;
    vector<lli> q(t);
    for(auto &x: q)
    {
        cin>>x;
        seen.insert(x);
    }

    process();

    for(auto x:q)
    {
        if(SZ(ans[x]))
        {
            for(int i = 0; i< SZ(ans[x]); i++)
            {
                cout << ans[x][i];
                if(i < SZ(ans[x]) - 1) cout << " ";
            }
            cout << endl;
        }
        else{
            cout << -1 << endl;
        }

    }

	return 0;
}