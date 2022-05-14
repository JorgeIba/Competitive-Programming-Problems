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


lli pointsInside(lli radius) {
    lli ans = 0;
    for(lli x = 1; x <= radius; x++) {
        lli l = 0, r = radius, filled = 0;
        while(l <= r) {
            lli mid = l + (r-l)/2;
            if( x*x + mid*mid <= radius*radius)
            {
                filled = mid;
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
        ans += filled;
    }
    (ans += radius) *= 4;
    return ans + 1;
}

lli pointsInCircunference(lli radius) {
    lli ans = 0;
    for(lli x = 1; x < radius; x++) {
        lli l = 0, r = radius, can = 0;
        while(l <= r) {
            lli mid = l + (r-l)/2;
            lli dist = x*x + mid*mid;
            if(dist == radius*radius){
                can = true;
                break;
            }else if( dist < radius*radius){
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
        ans += can;
    }
    (ans += 1) *= 4;
    return ans;
}

int main () {
	//fastIO();

    
    lli k, d; cin>>k>>d;

    if(d >= k) {
        cout << pointsInside(k+d) << endl;
    } else {
        lli outside = pointsInside(k+d) - pointsInside(k);
        lli inside = pointsInside(k) - pointsInside(k-d);
        lli in_line = pointsInCircunference(k-d);
        cout << outside + inside + in_line << endl;
        // cout << outside << " " <<  in_line  << " " <<  inside  << endl;
    }



	return 0;
}

