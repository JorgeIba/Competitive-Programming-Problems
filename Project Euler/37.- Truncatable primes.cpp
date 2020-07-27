#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< bool > isPrime;

void sieve(lli n)
{
    isPrime.resize(n+1, true);
    isPrime[0] = isPrime[1] = false;
    for(lli i = 4; i<=n; i+=2) isPrime[i] = false;

    for(lli i = 3; i<=n; i+=2) 
    {
        if(isPrime[i])
        {
            for(lli j = i*i; j <= n; j+= 2*i)
            {
                isPrime[j] = false;
            }
        }
    }
}

const lli maxN = 1e8;

bool isTruncatable(lli n)
{
    lli aux1 = n;
    while(aux1)
    {
        if(!isPrime[aux1]) return false;   
        aux1 /= 10;
    }
    lli aux2 = n;
    while(aux2)
    {
        lli log = log10(aux2);
        lli lastDigit = aux2 / pow(10, log);
        if(!isPrime[aux2]) return false;
        aux2 -= lastDigit*pow(10, log);
    }


    return true;
}

int main()
{
    //fastIO();
    sieve(maxN);
    lli suma = 0, cont = 0;
    for(int i = 10; i<=maxN; i++)
    {
        if(isTruncatable(i))
        {
            suma += i;
            cont++;
            if(cont == 11) break;
        }
    }
    cout << suma << endl;
    cout << cont << endl;

    return 0;
}