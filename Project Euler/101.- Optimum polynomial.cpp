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

lli interpolation(vector< pair<lli,lli> > points, lli k)
{
    lli n = SZ(points);

    ld ans = 0;
    for(int i = 0; i<n; i++)
    {
        ld num = 1, den = 1;
        for(int j = 0; j<n; j++)
        {
            if(i == j) continue;
            num *= (k - points[j].first);
            den *= (points[i].first - points[j].first);
        }
        ans += (points[i].second * num) / den;
    }
    return round(ans);
}

lli eval(VLL U, lli x)
{
    lli ans = 0, p = 1;
    for(int i = 0; i<SZ(U); i++)
    {
        ans += p*U[i];
        p *= x;
    }
    return ans;
}

int main () {
	//fastIO();

    lli degree = 10;
    VLL U(11);
    for(int i = 0; i<=10; i++) U[i] = (i & 1 ? -1: 1);
    //VLL U(4); U[3] = 1;

    vector<pair<lli,lli>> points;
    lli ans = 0;
    for(int i = 1; i<=degree; i++)
    {
        points.push_back({i, eval(U, i)});
        ans += interpolation(points, i+1);
        cout << interpolation(points, i+1) << endl;
    }
    cout << ans << endl;


    
	return 0;
}