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

typedef pair<lli, lli> point;
#define x first
#define y second

point operator-(const point &a, const point &b) {
    return {a.x - b.x, a.y - b.y};
}

lli operator*(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}

vector< point > convexHull(vector<point> P) {
    int n = SZ(P);
    sort(all(P));
    vector< point > L, U;
    for(int i = 0; i < n; i++) {
        while(SZ(L) >= 2 && (L[SZ(L) - 1] - L[SZ(L) - 2]) * (P[i] - L[SZ(L) - 2]) > 0)
            L.pop_back();

        L.push_back(P[i]);
    }

    for(int i = n-1; i >= 0; i--) {
        while(SZ(U) >= 2 && (U[SZ(U) - 1] - U[SZ(U) - 2]) * (P[i] - U[SZ(U) - 2]) > 0)
            U.pop_back();
            
        U.push_back(P[i]);
    }

    swap(L, U);
    L.pop_back();
    U.pop_back();
    
    L.insert(L.end(), all(U));
    return L;
}

int main () {
    // fastIO();
    int n; cin>>n;
    vector< point > points(n);

    for(auto &p: points) {
        cin>>p.x>>p.y;
    }

    map<point, vector<int>> indices;
    forn(i, n) {
        indices[points[i]].push_back(i);
    }

    auto ch = convexHull(points);

    sort(all(ch));
    ch.erase(unique(all(ch)), ch.end());

    vector<int> ans;
    for(auto p: ch) {
        for(auto idx: indices[p]) {
            ans.push_back(idx);
        }
    }

    sort(all(ans));
    for(auto i: ans) {
        cout << i+1 << " ";
    }
    cout << endl;

	return 0;
}

