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


typedef vector<ld> poly;

const ld eps = 1e-9;
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

poly operator*(const poly &a, const poly &b){
    poly c(SZ(a) + SZ(b) - 1);
    for(int i = 0; i < SZ(a); i++){
        for(int j = 0; j < SZ(b); j++) {
            c[i+j] += a[i] * b[j];
        }
    }
    return c;
}

poly integrate(const poly &a) {
    int n = SZ(a);
    poly ia(n+1);
    for(int i = n-1; i >= 0; i--) {
        ia[i+1] = a[i] / (i+1);
    }
    return ia;
}

ld eval(const poly &a, ld x) {
    ld ans = 0, p = 1;
    for(auto c: a){
        ans += p * c;
        p = x * p;
    }
    return ans;
}


int main () {
	// fastIO();
    int n; cin>>n;

    vector< pair<ld, ld> > ranges(n);
    for(auto &[l, r]: ranges) cin>>l>>r;


    vector< ld > events;
    for(auto [l, r]: ranges) {
        events.push_back(l);
        events.push_back(r);
    }

    sort(all(events));
    // events.erase(unique(all(events)), events.end());

    auto contains = [&](pair<ld,ld> test, pair<ld,ld> rang){
        auto [l, r] = test;
        auto [l2, r2] = rang;
        // return l2 <= l && r <= r2;
        return leq(l2, l) && leq(r, r2);
    };  


    /*
    
        int(x, r) = (r-x) / (b-a)
                  = r/(b-a) - 1/ (b-a) * x
    */

    int m = SZ(events);
    ld ans = 0;
    for(int i = 0; i < m-1; i++) {
        ld l = events[i];
        ld r = events[i+1];

        if(!contains({l, r}, ranges[0])) continue;

        auto [L, R] = ranges[0];
        poly p = {1.0 / (R - L)};
        for(int j = 1; j < n; j++) {
            auto [a, b] = ranges[j];
            if(leq(r, a)) continue; // probability of 1
            if(contains({l, r}, ranges[j])) { // Está dentro del rango
                // Ahora quiero saber, si mi x está fija, cuál es la proba de que el otro wey me verguee
                // cout << "OK: [" << l << ", " << r << "] --- [" << a << ", " << b << "]" << endl;
                poly t = {b / (b-a), -1.0 / (b-a)};
                p = p * t;
            } else {
                assert(b <= l);
                p = {0};
            }
        }

        poly pdf = integrate(p);
        ans += (eval(pdf, r) - eval(pdf, l));

        // cout << l << " --- " << r << " ----> ";
        // for(auto c: p) cout << c << " ";
        // cout << " === " << eval(pdf, r) << " - " << eval(pdf, l) << endl;
    }

    cout << fixed << setprecision(10) <<  ans << endl;

	return 0;
}

