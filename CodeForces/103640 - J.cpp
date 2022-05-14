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

#define point pair<int,int>
#define x first
#define y second


int w, h; 


bool isExtrem(point a) {
    return (a.x == w || a.x == 0 || a.y == h || a.y == 0);
}


int main () {
	fastIO();
    cin>>w>>h;

    int n; cin>>n;

    vector< pair<point, int> > up, down, left, right;

    for(int i = 0; i < n; i++) {
        point p1, p2;
        cin>>p1.x>>p1.y>>p2.x>>p2.y;

        if(!(isExtrem(p1) && isExtrem(p2))) continue;

        if(p1.x == 0) left.push_back( {p1,i+1} );
        else if(p1.x == w) right.push_back( {p1, i+1} );
        else if(p1.y == 0) down.push_back( {p1, i+1} );
        else if(p1.y == h) up.push_back( {p1, i+1} );

        if(p2.x == 0) left.push_back( {p2, i+1} );
        else if(p2.x == w) right.push_back( {p2, i+1} );
        else if(p2.y == 0) down.push_back( {p2, i+1} );
        else if(p2.y == h) up.push_back( {p2, i+1} );
    }


    sort(all(left), [&](pair<point,int> a, pair<point,int> b){
        return a.first.y > b.first.y;
    });
    sort(all(down), [&](pair<point,int> a, pair<point,int> b){
        return a.first.x < b.first.x;
    });
    sort(all(right), [&](pair<point,int> a, pair<point,int> b){
        return a.first.y < b.first.y;
    });
    sort(all(up), [&](pair<point,int> a, pair<point,int> b){
        return a.first.x > b.first.x;
    });


    vector<int> order;
    for(auto x: left) order.push_back(x.second);
    for(auto x: down) order.push_back(x.second);
    for(auto x: right) order.push_back(x.second);
    for(auto x: up) order.push_back(x.second);



    stack<lli> s;
    vector<bool> fr(n+1);

    bool ans = true;

    for(auto x: order) {
        if(!s.empty()) {
            if(fr[x]) {
                if(s.top() == x) {
                    s.pop();
                } else {
                    ans = false;
                }
            }  else {
                s.push(x);
                fr[x] = true;
            }
        } else {
            assert(!fr[x]);
            s.push(x);
            fr[x] = true;
        }
    }


    cout << (ans ? "Y" : "N") << endl;

	return 0;
}

