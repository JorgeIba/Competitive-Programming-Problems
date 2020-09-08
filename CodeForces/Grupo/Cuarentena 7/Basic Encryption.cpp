#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int MOD(lli a, lli mod)
{
    if(a<0) 
    {
        return a%mod + mod;
    }
    else
    {
        return a%mod;
    }
}



int main()
{
    fastIO();
    lli n, r; cin>>n>>r;
    r %= 26;
    cin.ignore();
    forn(i,0,n)
    {
        string s;
        getline(cin, s);
        string res = s;
        for(int i = 0; i<s.length(); i++)
        {
            if(isalpha(s[i]))
            {
                if(islower(s[i]))
                {
                    res[i] = MOD(s[i] - r - 97, 26) + 97;
                }
                else
                {
                    char aux = tolower(s[i]);
                    res[i] = MOD(aux - r - 97, 26) + 97;
                    res[i] = toupper(res[i]);
                }
            }
        }
        cout<<res<<endl;
    }

    return 0;
}