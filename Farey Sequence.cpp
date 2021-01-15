#include <iostream>
#include <vector>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

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

const int maxN = 1e6;

int main () {
	fastIO();
    phiSieve(maxN+1);
    vector<lli> sumPhi(maxN+1);
    for(int i = 1; i<=maxN; i++)
    {
        sumPhi[i] = sumPhi[i-1] + Phi[i];
    }

    while(true)
    {
        int n; cin>>n;
        if(!n) break;
        cout << sumPhi[n] - 1 << endl;
    }

    
	return 0;
}