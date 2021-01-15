#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

VLL getDivisors(lli n)
{
    vector<lli> divs = {1};
    for(lli i = 2; i*i<=n; i++)
    {
        if( n % i == 0)
        {
            divs.push_back(i);
            if( i != n/i) divs.push_back(n/i);
        }
    }
    return divs;
}


int main () {
	fastIO();
    string s; cin>>s;
    int n = s.length();
    vector<lli> divs =  getDivisors(n);

    // i = r % gcd(k, n), gcd(k,n) = divisor de n

    map<lli,lli> processBefore;
    lli ans = 0;
    for(int k = 1; k<n; k++)
    {
        lli g = __gcd(k, n);
        if(processBefore.count(g))
        {
            ans += processBefore[g]; continue;
        } 
        set<lli> forbidden;
        for(int i = 0; i<n; i++)
        {
            if(s[i] == 'P') forbidden.insert( i % g );
        }
        int flag = 0;
        for(int i = 0; i<n; i++)
        {
            if(s[i] == 'R')
            {
                if(forbidden.count(i % g) == 0) flag = 1;
            }
        }
        processBefore[g] = flag;
        ans += flag;
    }
    cout << ans << endl;

    /*
    lli szDivs = SZ(divs);
    sort(all(divs));
    assert(szDivs <= 100);


    vector< set<lli> > forbidden(szDivs);

    for(int i = 0; i<SZ(divs); i++)
    {
        lli d = divs[i];
        for(int j = 0; j<n; j++)
        {
            if(s[j] == 'P')
            {
                forbidden[i].insert(j % d);
            }
        }
    }

    for(auto v: forbidden)
    {
        for(auto x: v) cout << x << " ";
    }
    cout << endl;

    lli ans = 0;
    for(int i = 0; i<SZ(divs); i++)
    {
        bool flag = false;
        lli d = divs[i];
        for(int j = 0; j<n; j++)
        {
            if(s[j] == 'R')
            {
                if(forbidden[i].count(j%d) == 0) flag = true;
            }
        }
        ans += flag;
    }

    cout << ans << endl;
    */
    
	return 0;
}