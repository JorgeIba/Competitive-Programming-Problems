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

vector<int> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
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


bool isSquare(lli n)
{
    ld root = sqrt(n);
    return floor(root) == root;
}


int main () {
	//fastIO();
    int n; cin>>n;
    primesSieve(n);
    for(int i = 9; i<=n; i+=2)
    {
        if(isPrime[i]) continue;

        bool flag = false;
        for(auto p: primes)
        {
            if(p >= i) break;
            int prob = (i - p) / 2;
            if(isSquare(prob)){
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            cout << i << endl;
            return 0;
        }
    }
    
	return 0;
}