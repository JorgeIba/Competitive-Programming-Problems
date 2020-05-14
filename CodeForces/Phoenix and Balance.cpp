#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    lli t; cin>>t;
    vector<lli> pows(31);
    for(int i = 1; i<=30; i++)
    {
        pows[i] = pow(2,i);
    }
    while(t--)
    {
        lli n; cin>>n;
        lli a = 0, b = 0;
        lli l = 1, r = n;
        lli count = 0;
        if(n==2)
        {
            cout<<2<<endl;
            continue;
        }
        while(l<=r)
        {
            if(~count&1) a+= pows[l++] + pows[r--];
            else b += pows[l++] + pows[r--];
            count++;
        }
        cout<< abs(b-a)<<endl;
    
    }

    return 0;
}