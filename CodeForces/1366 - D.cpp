#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MAX = 3165;

//12
vector<lli> lowestPrime;
void lowestPrimeSieve(lli n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(lli i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}


pair<lli,lli> fact(lli n)
{
    lli aux = n;
    vector<lli> factores;
    while( n>1 && factores.size() < 2)
    {
        lli lp = lowestPrime[n];
        factores.push_back(lp);
        while(n % lp == 0)
            n/= lp;
    }
    if(factores.size() == 2)
    {
        if(aux&1)
        {
            lli num1 = factores[0], num2 = factores[1];
            return {num1, num2};
        }
        else
        {
            lli aux2 = aux;
            while(~aux&1)
                aux>>=1;
            return{2, aux};
        }
        
    }
    else return {-1,-1};
}


int main()
{
    fastIO();
    lowestPrimeSieve(MAX);
    lli n; cin>>n;
    vector<lli> nums(n), res1(n), res2(n);
    for(auto &x: nums)
    {
        cin>>x;
    }

    for(int i =0; i<n; i++)
    {
        tie(res1[i], res2[i]) = fact(nums[i]);
    }

    for(auto x: res1) cout<<x<<" ";
    cout<<endl;
    for(auto x: res2) cout<<x<<" ";

    

    return 0;
}