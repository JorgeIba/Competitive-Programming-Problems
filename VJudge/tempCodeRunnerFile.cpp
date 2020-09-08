#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


const lli MAXN = 30000;
const lli INF = numeric_limits<int>::max();

vector<int> lowestPrime;
vector<int> primes;
vector<int> res(MAXN);

void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
    for(int i = 2; i<=n; i++)
    {
        if(lowestPrime[i] == i) primes.push_back(i);
    }
}


lli fact(lli n)
{
    lli ans = 0;
    lli prev = -1;
    lli x = n;
    while(x!=1)
    {
        lli lowest = lowestPrime[x];
        if(prev == lowest) 
        {
            return 0;    
        }
        ans++;
        prev = lowest;
        x/=lowest;
    }
    return ans;
}

void prec()
{
    for(int i = 2; i<MAXN-1; i++)
    {
        res[i] = fact(i);
    }
}

int main()
{
    //fastIO();
    lowestPrimeSieve(MAXN);
    prec();
    lli n; 
    while(true)
    {
        cin>>n;
        if(n==-1) return 0;
        cout<<endl;
        if(n==1) cout<<"M(1) = 1";
        else
        {
            if(res[n] == 0)
                cout<<"M("<<n<<") = "<<0;
            else
                cout<<"M("<<n<<") = "<<(res[n]%2==0?1:-1);
        }
    }

    return 0;
}