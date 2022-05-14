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


struct segment{
    lli l, r, c;
    segment(): l(0), r(0), c(0) {}
    segment(lli l, lli r, lli c): l(l), r(r), c(c) {}

    bool is_bigger(segment a){
        return (r-l+1) < (a.r - a.l + 1);
    }

    bool is_equal(segment a){
        return (r-l+1) == (a.r-a.l+1);
    }

    lli get_size(){
        return r-l+1;
    }
};


void solve(){
    lli n; cin>>n;
    segment left, right, one;


    for(int i = 0; i<n; i++)
    {
        lli l, r, c; cin>>l>>r>>c;
        segment s = segment(l, r, c);


        if(one.l == 0) one = s;
        if(left.l == 0) left = s;
        if(right.r == 0) right = s;


        if(one.is_bigger(s)) one = s;
        if(one.is_equal(s)) {
            if(s.c < one.c) one = s;
        }

        if(s.l < left.l) 
        {
            left = s;
        }
        else if(s.l == left.l)
        {
            if(s.c < left.c) left = s;
        }


        if(s.r > right.r)
        {
            right = s;

        }
        else if(s.r == right.r){
            if(s.c < right.c) right = s;
        }


        segment combined = segment(left.l, right.r, left.c+right.c);
        if(one.get_size() > combined.get_size()){
            cout << one.c << endl;
        } else if(one.get_size() < combined.get_size()){
            cout << combined.c << endl;
        } else {
            cout << min(one.c, combined.c) << endl;
        }        
    }

}


int main () {
	 fastIO();
    lli t; cin>>t;

    while(t--) solve();


	return 0;
}

