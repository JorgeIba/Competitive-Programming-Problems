#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<lli> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(lli i = 4; i <= n; i += 2) isPrime[i] = false;
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

const lli maxN = 1e6;
lli a, b, k; 

bool check(lli poss)
{
    lli l = a, r = a, primes = 0;
    for(; r<a+poss; r++)
    {
        if(isPrime[r]) primes++;
    }
    if(isPrime[r]) primes++;
    //cerr << l << " " << r << " " << primes << endl;
    if(primes < k) return false;
    while(r<b)
    {
        if(isPrime[l])
        {
            primes--;
        }
        if(isPrime[r+1])
        {
            primes++;
        }
        l++, r++;
        //cerr << l << " " << r << " " << primes << endl;
        if(primes < k) return false;
    }
    return true;
}



int main()
{
    fastIO();
    primesSieve(maxN + 100);
    cin>>a>>b>>k;
    if(!check(b-a))
    {
        cout << -1 << endl;
    }
    else
    {
        //cout << check(2) << endl;
        
        lli l = 0, r = b-a, ans = -1;
        while(l<=r)
        {
            lli mid = l + (r-l)/2;
            if(check(mid))
            {
                ans = mid;
                r = mid-1;                    
            }
            else
            {
                l = mid + 1;
            }
        }
        assert(ans != -1);
        cout << (ans+1) << endl;
    }
    
    
    


    

    return 0;
}