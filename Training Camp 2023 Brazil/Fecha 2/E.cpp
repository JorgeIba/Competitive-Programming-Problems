#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

const char P = 'P', N = 'N', NON = '-';

struct point{
    lli x, y;
    char type;
    point(){}
    point(lli x, lli y, lli type): x(x), y(y), type(type) {}
};

const lli INF = 1e15;


int main () {
	//fastIO();
    
    int n; cin>>n;

    vector< point > points(n);
    for(auto &p: points) 
        cin>>p.x>>p.y>>p.type;

    auto transform = [&](point p){
        point ans;
        lli x = p.x, y = p.y;
        char type = p.type;
        ans.x = 2*x + y;
        ans.y = y - 2*x;
        ans.type = type;
        return ans;
    };

    for(auto &p: points) p = transform(p);


    sort(all(points), [&](auto p1, auto p2){
        if(p1.x != p2.x) return p1.x < p2.x;
        return p1.y < p2.y;
    });



    bool impossible = false;
    lli min_y_n = INF;
    for(auto &[x, y, type]: points){
        if(type == N) {
            min_y_n = min(min_y_n, y);
        } else if(type == P) {
            if(y >= min_y_n) {
                impossible = true;
                break;
            }
        } else {
            if( y >= min_y_n )
                type = N;  
        }
    }

    if(impossible) {
        cout << "impossible" << endl;
        return 0;
    }

    vector< point > res;
    for(auto p: points) {
        if(p.type != N) res.push_back(p);
    }

    sort(all(res), [&](auto p1, auto p2){
        if(p1.x != p2.x) return p1.x > p2.x;
        return p1.y > p2.y;
    });


    lli max_y_p = -INF, max_y_q = -INF;
    lli ans = 0;
    for(auto &[x, y, type]: res){
        if(type == P) {
            if(y > max_y_p){
                ans++;

                if(y < max_y_q){
                    // Need transform - to P
                    max_y_p = max_y_q;
                    max_y_q = -INF;
                } else {
                    max_y_p = y;
                }
            }
        } else {
            max_y_q = max(max_y_q, y);
        }
    }

    cout << ans << endl;






	return 0;
}

