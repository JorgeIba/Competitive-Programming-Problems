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

//12
vector<int> lowestPrime;
void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}



vector< pair<lli,lli> > factorize(lli n)
{
    unordered_map<lli,lli> factors;

    while(n > 1)
    {
        lli lp = lowestPrime[n];
        while(n % lp == 0)
        {
            factors[lp]++;
            n /= lp;
        }
    }
    vector<pair<lli,lli>> factors_v;
    for(auto x: factors) factors_v.push_back(x);

    return factors_v;
}


lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a;
        b >>= 1;
        a = a*a;
    }
    return res;
}


vector<lli> getDivs(vector<pair<lli,lli>> &factors)
{
    vector<lli> divs;
    int n = SZ(factors);

    int factors_count = 1;
    for (int i = 0; i < n; ++i)
    {
        factors_count *= 1+factors[i].second;
    }

    divs.resize(factors_count);
    divs[0] = 1;


    int count = 1;
    for (int stack_level = 0; stack_level < n; ++stack_level)
    {
        int count_so_far = count;
        int prime = factors[stack_level].first;
        int exponent = factors[stack_level].second;
        int multiplier = 1;
        for (int j = 0; j < exponent; ++j)
        {
            multiplier *= prime;
            for (int i = 0; i < count_so_far; ++i)
            {
                divs[count++] = divs[i] * multiplier;
            }
        }
    }
    return divs;
}




lli getSolutions(vector<lli> &divs, lli n)
{
    lli sum = 0;
    for(auto d: divs)
    {
        if((n/d + d) % 4 == 0)
        {
            lli k = (n/d + d) / 4;
            lli a = d-k;
            if(a <= 0) continue;
            sum++;

        }
    }
    return sum;
}


int main () {
	//fastIO();
    time_t begin = clock();
    
    const int maxN = 1e6;
    lowestPrimeSieve(maxN);
    
    lli ans = 0;
    for(int i = 1154; i<maxN; i++)
    {
        auto factors = factorize(i);
        auto divs = getDivs(factors);
        lli countSolutions = getSolutions(divs, i);
        if(countSolutions == 10) ans++;
    }
    cout << ans << endl;
    
    cout << "Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;

	return 0;
}

