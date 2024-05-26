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



const lli maxN = 120;
//29
void GaussJordanZ2(vector< bitset<maxN> > &equations, vector<bitset<maxN>> &ans)
{
	int rows = SZ(equations), cols = maxN;
	for(int i = 0, j = 0; (i < rows) && (j < cols); j++)
	{
		int selected = -1;
		
		for(int k = i; k<rows; k++)
			if(equations[k][j])
				selected = k;
		
		if(selected == -1) continue;
		
		swap(equations[i], equations[selected]);
		swap(ans[i], ans[selected]);

		for(int k = 0; k<rows; k++)
		{
			if(k != i && equations[k][j])
			{
				equations[k] ^= equations[i];
				ans[k] ^= ans[i];
			}
		}
		i++;
	}
}


//20
vector<lli> primes;
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
				for(lli j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}



int main () {
	//fastIO();
    primesSieve(550);
    lli t, m; cin>>t>>m;

    vector<lli> nums(m);
    for(auto &x: nums) cin>>x;

    
    vector<lli> factorBase(t);
    for(int i = 0; i < t; i++) factorBase[i] = primes[i];


    vector< bitset<maxN> > M(m);
    vector< bitset<maxN>> INV(m);

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < t; j++) {
            auto num = nums[i];
            while(num % factorBase[j] == 0) {
                num /= factorBase[j];
                M[i][j].flip();
            }
        }
        INV[i][i].flip();
    }

    GaussJordanZ2(M, INV);

    lli basis = 0;
    for(int i = 0; i < m; i++) {
        auto bs = M[i];
        if(bs.count() == 0 && INV[i].count() > 0) {
            basis++;
        }
    }

    __int128 ans = 1;

    cout << ((ans << basis) - 1) << endl;

	return 0;
}

