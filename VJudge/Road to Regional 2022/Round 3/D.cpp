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


typedef vector<lli> poly;

#define INPUT 0
#define OR 1
#define AND 2


vector< pair<lli,lli> > adjList;
vector< lli > type_gate;


poly multiply(poly &a, poly &b) {
    poly c(SZ(a) + SZ(b) - 1);

    for(int i = 0; i < SZ(a); i++) {
        for(int j = 0; j < SZ(b); j++) {
            c[i+j] += a[i] * b[j];
        }
    }

    return c;
}





poly f(int n) {
    if(type_gate[n] == INPUT) {
        return vector<lli>{0, 1};
    } else{
        auto [u, v] = adjList[n];
        poly f_u = f(u), f_v = f(v);
        
         if(type_gate[n] == OR) {
            f_u[0] -= 1;
            f_v[0] -= 1;
            poly ans = multiply(f_u, f_v);
            for(auto &x: ans) x *= -1;
            ans[0] += 1;

            return ans;
        } else {
            return multiply(f_u, f_v);
        }
    }
}


ld eval(const poly &a, ld x) {
    ld sum = 0, mult = 1;
    for(int i = 0; i < SZ(a); i++) {
        sum += 1.0*mult * a[i];
        mult *= x;
    }
    return sum;
}

void solve() {

    int n; cin>>n;
    adjList.clear();
    adjList.resize(n+1);

    type_gate.clear();
    type_gate.resize(n+1);


    for(int i = 1; i <= n; i++){
        int t; cin>>t;
        if(t == 0) {
            type_gate[i] = INPUT;
        } else {
            
            if(t == 1) {
                type_gate[i] = OR;
            } else {
                type_gate[i] = AND;
            }

            int u, v; cin>>u>>v;
            adjList[i] = {u, v};
        }
    }
    

    auto ans_poly = f(n);

    for(auto &x: ans_poly)
        x = 2*x;


    ans_poly[0] -= 1;

    // for(auto x: ans_poly) cout << x << " ";
    // cout << endl;
    
    ld l = 0, r = 1;
    for(int i = 0; i <= 50; i++) {
        ld m1 = l + (r - l) / 3;
        ld m2 = r - (r - l) / 3;
        ld f1 = abs(eval(ans_poly, m1));
        ld f2 = abs(eval(ans_poly, m2));
        
        if (f1 > f2)
            l = m1;
        else
            r = m2;
    }

    

    cout << fixed << setprecision(5) << l << endl;
}



int main () {
	fastIO();

    int t; cin>>t;

    while(t--) solve();

	return 0;
}

