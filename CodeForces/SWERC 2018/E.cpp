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

lli n;



int main () {
	//fastIO();
    cin>>n;
    vector<ld> points(n);
    vector<string> cities(n);

    vector<ld> minimos(n), maximos(n);
    
    ld suma = 0;
    for(int i = 0; i<n; i++){
        cin>>cities[i]>>points[i];
        suma += points[i];
        maximos[i] = min((ld)points[i] + 0.49, (ld)100.0);
        minimos[i] = max((ld)points[i] - 0.5, (ld)0.0);
    }
    
    ld upper = 0, lower = 0;
    for(auto x: minimos) lower += x;
    for(auto x: maximos) upper += x;

    cerr << lower << " " << upper << endl;

    if(upper < 100.0 || lower > 100.0){
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << fixed << setprecision(2);

    vector<ld> ans(2);
    for(int i = 0; i<n; i++)
    {
        ld auxU = upper - maximos[i];
        ld restante = 100.0 - auxU;
        ans[0] = max(minimos[i], restante);
        
        ld auxL = lower - minimos[i];
        restante = 100.0 - auxL;
        ans[1] = min(maximos[i], restante);

        cout << cities[i] << " " << ans[0] << " " << ans[1] << endl;
    }
    






	return 0;
}