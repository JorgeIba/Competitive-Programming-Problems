#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define uint unsigned int

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

uint A, B, C, D;

uint f(uint x)
{
	return A*x*x*x + B*x*x + C*x + D;
}

int mapping(int idx)
{
	if( idx % 6 == 1) return 2*((idx-1)/6 - 1)+1;
	else if (idx % 6 == 5) return 2*((idx+1)/6 - 1);
	return -1;
}


//20
const int maxN = (3e8+1) / 3;
bitset<maxN> isPrime;
uint primesSieve(lli n)
{
	uint ans = 0;

	for(lli i: {2, 3})
	{
		lli p = i, k = 0, aux;
				
		while( (aux = n / p) > 0)
		{
			p = p*i;
			k+=aux;
		}
		ans = ans + f(i) * (uint)k;
	}

	for(lli i = 5; i <= n; i += 2)
    {
		if(mapping(i) == -1) continue;

		if(isPrime[mapping(i)] == 0)
        {
			lli p = i, k = 0, aux;
			
			while( (aux = n / p) > 0)
			{
				p = p*i;
				k += aux;
			}
			ans = ans + f(i) * (uint)k;

			if(i * i <= n)
				for(lli j = i * i; j <= n; j += 2 * i)
				{
					if(mapping(j) == -1) continue;
					isPrime[mapping(j)] = 1;
				}
					
		}
	}
	return ans;
}


int main () {
	//fastIO();
	uint n; cin>>n>>A>>B>>C>>D;

	
	cout << primesSieve(n) << endl;

	return 0;
}