#include <bits/stdc++.h>
#define lli long long int
#define ld double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) (int)(s.size())
 
using namespace std;
 

vector< lli > multiply(vector< lli > &a, vector< lli > &b)
{
    lli n = a.size() - 1, t = b.size() - 1;
    vector< lli > ans(n + t + 1);
    //cerr << (n+ t + 1) << endl;
    for(int i = 0; i<= n; i++)
    {
        for(int j = 0; j<=t; j++)
        {
            ans[j+i] += a[i]*b[j];
        }
    }
    return ans;
}
 

int main () {
	fastIO();
    string s; cin>>s;
    lli n = s.length();
    vector< lli > roots;
    char last = s[0];
    for(int i = 1; i<n; i++)
    {
        if(last != s[i])
        {
            roots.push_back(2*i+1);
        }
        last = s[i];
    }
    if(SZ(roots) == 0)
    {
        cout << 0 << endl;
        if(s[0] == 'H')
        {
            cout << 1 << endl;
        }
        else
        {
            cout << -1 << endl;
        }
        return 0;
    }

    vector< vector< lli > > polys;
    for(auto r: roots)
    {
        vector< lli > aux(2);
        aux[1] = 1;
        aux[0] = -r;
        polys.push_back(aux);
    }
    vector< lli > ans = polys[0];
    for(int i = 1; i<SZ(polys); i++)
    {
        ans = multiply(ans, polys[i]);
    }
    lli res = ans[0];
    reverse(all(ans));
    char first = s[0];
    bool sign; // Positivo = true, negativo = false
    if(first == 'A')
    {
        sign = false;
    }
    else
    {
        sign = true;
    }
    cout << (SZ(ans)-1) << endl;
    if((res > 0 && sign) || (res<0 && !sign))
    {
        for(int i = 0; i<SZ(ans); i++)
        {
            cout << ans[i];
            if(i != (SZ(ans) - 1)) cout << " ";
        }
        cout << endl;
    }
    else
    {
        for(int i = 0; i<SZ(ans); i++)
        {
            cout << -ans[i];
            if(i != (SZ(ans) - 1)) cout << " ";
        }
        cout << endl;
    }

	return 0;
}