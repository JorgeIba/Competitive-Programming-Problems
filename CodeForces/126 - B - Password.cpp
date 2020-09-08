#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<lli> powers, hashSum;
lli p = 31, mod = 1e9+7;
lli n;
string s; 

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = (res*a)%mod;
        b>>=1;
        a = (a*a)%mod;
    }
    return res;
}


void prec()
{
    powers.resize(n+1);
    powers[0] = 1;
    powers[1] = p;
    for(int i = 2; i<=n; i++)
    {
        powers[i] = (powers[i-1]*p)%mod;
    }

    hashSum.resize(n+1);
    hashSum[0] = (s[0]*powers[n])%mod;
    for(int i = 1; i<n; i++)
    {
        hashSum[i] = (hashSum[i-1] + s[i]*powers[n - i])%mod;
    }
}

lli getHashSubstring(lli l, lli r)
{
    //lli aux = (hashSum[j] - hashSum[i-1]);
    //return aux<0?aux+mod: aux;
    return (hashSum[r] - hashSum[l-1]);
}

bool isEqual(lli mid)
{
    lli aux = ((hashSum[n-1] - hashSum[(n-1)-mid]) * powers[n-mid])%mod;
    if(aux<0) aux+=mod;
    return hashSum[mid-1] == aux;
}

bool check(lli mid)
{
    if(!isEqual(mid))
    {
        return false;
    }
    //cerr << "Si llegue " << mid << endl;
    lli l = 1, r = mid;
    while(r<n-1)
    {
        lli aux = (getHashSubstring(l, r) * powers[l])%mod;
        if(aux<0) aux += mod;
        if(aux == hashSum[mid-1])   return true;
        r++;
        l++;
    }
    return false;
}




int main()
{
    fastIO();
    cin>>s;
    n = s.length();
    prec();
    vector< lli > candidates;
    for(int i = 0; i<n-1; i++)
    {
        if(isEqual(i))
        {
            candidates.push_back(i);
        }
    }

    //for(auto x: candidates) cout << x << " ";

    lli l = 0, r = candidates.size()-1, ans = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( check( candidates[mid] )  )
        {
            ans = candidates[mid];
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    if(ans == -1) cout << "Just a legend\n";
    else
    {
        for(int i = 0; i<ans; i++)
        {
            cout << s[i];
        }cout << endl;
    }
    
    
    return 0;
}