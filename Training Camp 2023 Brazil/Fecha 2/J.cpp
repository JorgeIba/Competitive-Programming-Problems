#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

/*
Parametric Self-Dual Simplex method
Solve a canonical LP:
    min or max: to_min 
    s.t: 
    A_i <= restr_i
    **A_i = a x_0 + b x_1 + ...
    x >= 0
    O(m*(n+m)), n = size of to_min, m = size of restr
*/

typedef vector<ld> Vec;
typedef vector<Vec> Mat;

const ld eps = 1e-15, oo = 1e18;

pair<Vec, ld> simplexMethodPD(const Mat &A, const Vec &restr, const Vec &to_min, bool mini = true){
    int n = to_min.size(), m = restr.size();
    Mat T(m + 1, Vec(n + m + 1));
    vector<int> base(n + m), row(m);
 
    for(int j = 0; j < m; ++j){
        for(int i = 0; i < n; ++i)
            T[j][i] = A[j][i];
        row[j] = n + j;
        T[j][n + j] = 1;
        base[n + j] = 1;
        T[j][n + m] = restr[j];
    }
 
    for(int i = 0; i < n; ++i)
        T[m][i] = to_min[i] * (mini ? 1 : -1);
 
    while(true){
        int p = 0, q = 0;
        for(int i = 0; i < n + m; ++i)
            if(T[m][i] <= T[m][p])
                p = i;
 
        for(int j = 0; j < m; ++j)
            if(T[j][n + m] <= T[q][n + m])
                q = j;
 
        ld t = min(T[m][p], T[q][n + m]);
 
        if(t >= -eps){
            Vec x(n);
            for(int i = 0; i < m; ++i)
                if(row[i] < n) x[row[i]] = T[i][n + m];
            return {x, T[m][n + m] * (mini ? -1 : 1)}; // optimal
        }
 
        if(t < T[q][n + m]){
            // tight on to_min -> primal update
            for(int j = 0; j < m; ++j)
                if(T[j][p] >= eps)
                    if(T[j][p] * (T[q][n + m] - t) >= T[q][p] * (T[j][n + m] - t))
                        q = j;
 
            if(T[q][p] <= eps)
                return {Vec(n), oo * (mini ? 1 : -1)}; // primal infeasible
        }else{
            // tight on restr -> dual update
            for(int i = 0; i < n + m + 1; ++i)
                T[q][i] = -T[q][i];
 
            for(int i = 0; i < n + m; ++i)
                if(T[q][i] >= eps)
                    if(T[q][i] * (T[m][p] - t) >= T[q][p] * (T[m][i] - t))
                        p = i;
 
            if(T[q][p] <= eps)
                return {Vec(n), oo * (mini ? -1 : 1)}; // dual infeasible
        }
 
        for(int i = 0; i < m + n + 1; ++i)
            if(i != p) T[q][i] /= T[q][p];
 
        T[q][p] = 1; // pivot(q, p)
        base[p] = 1;
        base[row[q]] = 0;
        row[q] = p;
 
        for(int j = 0; j < m + 1; ++j){
            if(j != q){
                ld alpha = T[j][p];
                for(int i = 0; i < n + m + 1; ++i)
                    T[j][i] -= T[q][i] * alpha;
            }
        }
    }
 
    return {Vec(n), oo};
}


int main () {
    fastIO();
    
    int n; cin>>n;
    vector< pair<lli,lli> > taps(n);


    lli sum_ai = 0, sum_t_ai = 0;
    for(int i = 0; i < n; i++){
        lli t, a, b; cin>>t>>a>>b;
        sum_ai += a;
        sum_t_ai += t*a;
        taps[i] = {t, b - a};
    }

    Mat A(n+2*2, Vec(n));

    for(int i = 0; i < n; i++){
        A[i][i] = 1;
    }

    for(int i = 0; i < n; i++) {
        A[n][i] = 1;
    }

    for(int i = 0; i < n; i++) {
        A[n+1][i] = -1;
    }

    for(int i = 0; i < n; i++) {
        A[n+2][i] = taps[i].first;
    }

    for(int i = 0; i < n; i++) {
        A[n+3][i] = -taps[i].first;
    }


    Vec to_min(n, 1);

    int q; cin>>q;

    while(q--) {
        lli T, L; cin>>T>>L;

        lli C = L - sum_ai;
        lli D = T*L - sum_t_ai;

        Vec rest(n+2*2);
        for(int i = 0; i < n; i++) {
            rest[i] = taps[i].second;
        }

        rest[n] = C;
        rest[n+1] = -C;

        rest[n+2] = D;
        rest[n+3] = -D;


        auto ans = simplexMethodPD(A, rest, to_min);

        if(ans.second == -oo || ans.second == oo) {
            cout << "no" << endl;
        } else {
            cout << "yes" << endl;
        }
    }


    return 0;
}