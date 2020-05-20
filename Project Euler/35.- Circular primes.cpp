#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<lli> lp;
void sieve(lli n)
{
    vector<lli> primes;
    lp.resize(n+1, 0);

    for(int i = 2; i<=n; i++)
    {
        if(!lp[i])
        {
            lp[i] = i;
            primes.push_back(i);
        }
        for(auto p: primes)
        {
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]) break;
        }

    }
}

bool isPrime(lli n)
{
    return lp[n] == n;
}



vector<lli> convert(lli n)
{
    vector<lli> res;
    while(n)
    {
        res.push_back(n%10);
        n/=10;
    }
    reverse(all(res));
    return res;
}

lli Rotate(vector<lli> convertNum, lli jumps)
{
    lli n = convertNum.size();
    vector<lli> aux(n, 0);
    for(int i = 0; i<n; i++)
    {
        aux[ (i+jumps)%n ] = convertNum[i];
    }
    lli num = 0, pot = 1;
    for(int i = n-1; i>=0; i--)
    {
        num += aux[i]*pot;
        pot*=10;
    }
    return num;
}

vector<bool> check(1000000, true);

bool isCircular(lli n)
{
    vector<lli> convertNum = convert(n);
    lli res = n%10;
    if(res != 1 && res != 3 && res != 7 && res != 9) return false;

    for(int i = 2; i<n; i++)
    {
        lli num = Rotate(convertNum, i);
        if( check[num] && !isPrime(num)  )
        {
            return false;
        }
        check[num] = false;
    }
    return true;
}



int main()
{
    //fastIO();
    lli contador = 0;
    sieve(1000000);
    for(int i = 2; i<=1000000; i++)
    {
        if(isCircular(i))
        {
            contador++;
        }
    }
    cout<< (contador + 2) <<endl; // 2 y 5 

    return 0;
}