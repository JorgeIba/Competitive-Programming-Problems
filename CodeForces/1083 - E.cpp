#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

struct rect{
    lli x, y, a; 
    rect(){}
    rect(lli x, lli y, lli a) {}
};

const lli INF = 1e15;

struct Line{
    lli m, b;
    Line(){}
    Line(lli m, lli b): m(m), b(b) {}
    lli eval(lli x){ return m*x + b; }
};

// Assuming slopes are non-decreasing
struct CHTrick{
    vector<Line> CH;

    lli inter(const Line &a, const Line &b){
        lli num = b.b - a.b, den = a.m - b.m;
        return num / den + (num % den ? !((num > 0) ^ ( den > 0)) : 0);
    }

    void add(lli m, lli b){
        Line l(m, b);

        if(SZ(CH) && m == CH.back().m){
            l.b = min(  b, CH.back().b  ); 
            CH.pop_back();
        }

        while( 2 <= SZ(CH) && inter(CH.back(), l) <= inter( CH[ CH.size() - 2 ], CH.back()  ))
            CH.pop_back();

        CH.push_back(l);
    }

    lli query(lli x){
        int l = 0, r = CH.size();
        while(r-l > 1) {
            int mid = l + (r-l)/2;
            if( inter(CH[mid], CH[mid-1]) > x)
                r = mid;
            else 
                l = mid;
        }
        return CH[l].eval(x);
    }
};

int main () {
	fastIO();

    int n; cin>>n;
    vector<rect> rects(n);

    for(auto &r: rects) cin>>r.x>>r.y>>r.a;

    sort(all(rects), [&](auto r_1, auto r_2){
        return r_1.x > r_2.x;
    });


    vector<lli> dp(n+1);

    CHTrick *CHT = new CHTrick();

    CHT->add(0, 0);

    for(int i = 1; i <= n; i++){
        auto [x_i, y_i, a_i] = rects[i-1];
        dp[i] = dp[i-1];
        dp[i] = max(dp[i], x_i * y_i - a_i);
        
        lli aux = x_i * y_i - a_i + CHT->query(-x_i);
        dp[i] = max(dp[i], aux);

        CHT->add(y_i, dp[i]);
    }

    cout << dp[n] << endl;



	return 0;
}

