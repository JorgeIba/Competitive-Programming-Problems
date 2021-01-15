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

const int maxN = 1e6+5;

int main () {
	//fastIO();
    primesSieve(maxN);
    vector<lli> prefix(maxN);
    for(int i = 2; i<maxN; i++)
    {
        prefix[i] = prefix[i-1] + isPrime[i];
    }

    lli n, t; cin>>n>>t;
    lli S, P, C; cin>>S>>P>>C;
    lli p=0, c=0;
    
    lli cuantasVueltas = t / n;
    p =  ((p + (prefix[n] * cuantasVueltas%n)))%n;
    t -= n*cuantasVueltas;

    lli aux = (p + cuantasVueltas)%n;
    c = (c - aux) %n;
    if(c < 0) c += n;

    for(; t>0; t--)
    {
        S--;
        if(S == 0) S = n;
        if(isPrime[S]) p = (p+1)%n;
        else if(S != 1) c = (c+1)%n;
    }
    
    P = (P-p)%n;
    C = (C+c)%n;
    if(P < 0) P+=n;

    if(P == 0) P = n;
    if(C == 0) C = n;
    assert(S >= 1 && S<=n && P >= 1 && P<=n && C >= 1 && C<=n);
    cout << S << " " << P << " " << C << endl;
    
    


	return 0;
}