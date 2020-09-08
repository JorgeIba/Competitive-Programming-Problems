#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bool isPrime(lli n)
{
    if(n < 2) return false;
    if(n == 2 || n == 3) return true;
    if(n%2 == 0 || n%3 == 0) return false;
    for(lli i = 2; i*i<=n; i++)
    {
        if(n%i == 0)
        {
            return false;
        }
    }
    return true;
}


bool isTruncatable(lli n)
{
    if( (to_string(n)).length() == 1  ) return false;
    while(n)
    {
        lli log = log10(n);
        lli lastDigit = n / pow(10, log);
        if(!isPrime(n)) return false;
        n -= lastDigit*pow(10, log);
    }
    return true;
}

int main()
{
    //fastIO();
    queue< lli > q;
    vector< lli > digits = {1, 3, 7, 9};
    q.push(2); q.push(3); q.push(5); q.push(7);

    lli total = 0, cuantity = 0;
    while(!q.empty())
    {
        lli curr = q.front(); q.pop();
        for(auto digit: digits)
        {
            lli possible = 10*curr + digit;
            if(isPrime(possible))
            {
                q.push(possible);
            }
        }
        if(isTruncatable(curr))
        {
            cuantity++;
            total+=curr;
            cout << curr << endl;
        }
    }
    cout << total << endl;
    //cout << cuantity << endl;


    return 0;
}