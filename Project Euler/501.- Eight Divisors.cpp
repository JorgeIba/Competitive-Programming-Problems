#include <bits/stdc++.h>

#define lli long long int
#define ll long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9 + 7;
const lli MAX = 1e6;

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

lli N, m;
vector<lli> lo, hi;

lli &at(lli x)
{
    if(x <= m) return lo[x];
		return hi[N / x];
}

lli pi_0(){
	vector<lli> values;
    lo.resize(m+1); hi.resize(m+1);
	for(int i = 1; i <= m; ++i){
		values.push_back(i);
		if(N / i != i) values.push_back(N / i);
	}
	sort(all(values), greater<lli>());
	for(lli n : values){
		at(n) = n-1;
	}
	for(lli p: primes)
	{
		if(p>m) break;
		for(lli n : values){
			if(n < p*p) break;
			at(n) -= (at(n/p) - at(p-1));
		}
	}
	return at(N);
}



int main()
{
    fastIO();
    primesSieve(MAX);
    cin>>N; //n = 1000000000000 for the problem
    clock_t begin = clock();
    m = sqrt(N);
    pi_0();
    lli l = pow(N, 1.0 / 7);
    lli res = at(l); // p^7

    for(auto p: primes)
    {
        lli t= p*p*p;
        if(N/t == 0) break;
        res += at(N/t);
        if(t*p <= N)
        {
            res--;
        }
    } //p^3 * p


    for(lli i = 0; i<primes.size(); i++)
    {
        lli p1 = primes[i];
        if( p1*p1*p1 > N ) break;
        for(lli j = i+1; j<primes.size(); j++)
        {
            lli p2 = primes[j];
            lli aux = N / (p1*p2);
            if( p2 > sqrt(N/p1) ) break;
            res += (at(aux) - at(p2));
        }
    }// p*p*p

    clock_t end = clock();
    cout<<res<<" "<<(double)(end - begin)/(CLOCKS_PER_SEC)<<endl;


    return 0;
}