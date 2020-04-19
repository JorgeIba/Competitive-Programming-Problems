#include <bits/stdc++.h>

using namespace std;

vector<bool> sieve(1005, true);
vector<int> primes;

void getPrimes() //Sieve to get all primes smaller than 1000
{
    for(int i = 2; i<=1000; i+=2) sieve[i] = false;
    for(int i = 3; i*i<=1000; i+=2)
    {
        if(sieve[i])
        {
            for(int j = i*i; j<=1000; j+= 2*i)
            {
                sieve[j] = false;
            }
        }
    }
    for(int i = 0; i <= 1000; i++)
    {
        if(sieve[i]) primes.push_back(i);
    }
}

int binaryPower(long long int a, long long int b, int mod) //Function to get a binary modular exponentiation 
{
    long int res = 1;
    a = a%mod;
    while(b)
    {
        if(b&1) res = (res*a)%mod;
        b>>=1;
        a = (a * a)%mod;
    }
    return res;
}


int getMin(int p) //Get the minimum "t of the solution 10^t mod p = 1
{
    int minimum = INT_MAX;
    int x = p-1;
    while(~x&1)
    {
        if( binaryPower(10,x,p)==1  )
        {
            minimum = min(minimum, x);
        }
        x>>=1;
    }
    if( binaryPower(10,x,p) == 1  )
    {
        minimum = min(minimum, x);
    }
    return minimum;
}


int main()
{
    getPrimes();
    int MAX = -1, res = -1;
    for(auto p: primes)
    {
        if(p<6) continue;
        int minOfP = getMin(p);
        if(minOfP > MAX )
        {
            MAX = minOfP;
            res = p;
        }
    }
    cout<<res<<endl;
    return 0;
}