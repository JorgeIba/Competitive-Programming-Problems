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


#define point pair<lli,lli>
#define x first
#define y second


int main () {
	// fastIO();

    lli n; cin>>n;
    vector<point> points(n);

    for(auto &p: points) cin>>p.x>>p.y;

    map<tuple<lli,lli,lli>, set<point>> equation_to_counter;
    for(int i = 0; i < n; i++) {
        point a = points[i];
        for(int j = i+1; j < n; j++) {
            point b = points[j];

            lli x1 = a.x, y1 = a.y;
            lli x2 = b.x, y2 = b.y;

            lli A = y1-y2;
            lli B = x2-x1;
            lli C = x2*y1-x1*y2;

            if(A < 0) {
                A *= -1;
                B *= -1;
                C *= -1;
            } else if(A == 0 && B < 0) {
                B *= -1;
                C *= -1;
            }

            lli rho = abs( __gcd( A, __gcd(B, C) ) );

            
            A /= rho;
            B /= rho;
            C /= rho;
            

            equation_to_counter[{A, B, C}].insert(b);
            equation_to_counter[{A, B, C}].insert(a);
        }
    }


    auto nC3 = [](lli n) {
        return n*(n-1)*(n-2)/6;
    };
    auto nC4 = [](lli n) {
        return n*(n-1)*(n-2)*(n-3)/24;
    };

    lli ans = nC4(n);


    lli triangles = 0, lines = 0;
    for(auto eq_set: equation_to_counter) {
        lli n_coll = SZ(eq_set.second);

        triangles += nC3(n_coll) * (n - n_coll);
        lines += nC4(n_coll);
    }


    cout << ans - triangles - lines << endl;


	return 0;
}

