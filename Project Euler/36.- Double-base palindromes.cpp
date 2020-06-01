#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bool isBaseTen(string s)
{
    lli l = 0, r = s.length()-1;
    while(l<=r)
    {
        if(s[l++] != s[r--]) return false;
    }
    return true;
}

bool isBaseTwo(string s, lli t)
{
    lli l = s.length()-t, r = s.length()-1;
    while(l<=r)
    {
        if(s[l++] != s[r--]) return false;
    }
    return true;
}

bool isPalindromic(lli n)
{
    lli t = log2(n) + 1;
    bitset<20> aux = n;
    string an = aux.to_string();
    return isBaseTen( to_string(n)) && isBaseTwo(an,t);
}



int main()
{
    
    fastIO();
    lli sum = 0;
    for(int i =1; i<1000000; i+=2)
    {
        if(isPalindromic(i) && i%10)
        {
            sum+=i;
        }
    }
    cout<<sum<<endl;
    
    return 0;
}