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

lli f(lli a, lli b, lli c)
{
    return a*a + b*b + c*c + 7*min({a,b,c});
}

void solve()
{
    lli a, b, c, d; cin>>a>>b>>c>>d;
    vector<lli> aux = {a,b,c};
    sort(all(aux));
    reverse(all(aux));

    lli ans = max({f(aux[0] + d, aux[1], aux[2]), f(aux[0], aux[1]+d, aux[2]), f(aux[0], aux[1], aux[2]+d)});

    lli diff = aux[1] - aux[2];
    if(d >= diff)
    {
        aux[2] += diff; //Emparejar el 2 con el 1
        d -= diff;

        diff = aux[0] - aux[1]; // a > b = c
        
        lli mitad = d/2;
        if(mitad >= diff)
        {
            aux[1] += diff, aux[2] += diff;
            d -= 2*diff;
        }
        else
        {
            aux[2] += mitad, aux[1] += mitad;
            d -= 2*mitad;
            aux[2] += d%2;
            d = 0;
            assert(d==0);
        }
        
        if(d > 0) //Distribuir
        {
            lli parte1 = d/3, parte2 = d/3, parte3 = d - parte1 - parte2;
            aux[0] += parte3;
            aux[1] += parte2;
            aux[2] += parte1;
        }
    }

    cout << max(ans, f(aux[0], aux[1], aux[2])) << endl;
}

int main () {
	fastIO();
    lli t; cin>>t;
    while(t--) solve();
    
	return 0;
}