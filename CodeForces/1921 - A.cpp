#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

int main () {
	fastIO();
    int t; cin>>t;


    while(t--) {
        vector< pair<int,int> > points(4);
        for(auto &p: points) cin>>p.first>>p.second;

        sort(all(points));

        lli area = abs(points[0].first - points[1].first) + abs(points[0].second - points[1].second);

        cout << area * area << endl;
    }


	return 0;
}

