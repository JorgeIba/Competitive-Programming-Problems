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


const int OFFSET = 1e3;
const int WIDTH  = 100;
const int HEIGHT = 100;
const int DEPTH  = 100;

const ld PI = acos(-1);
const ld eps = 1e-12;

int main () {
	//fastIO();

    int n; cin>>n;
    int s; cin>>s;


    #define circle tuple<ld,ld,ld,ld>

    vector< circle > circles(n);
    for(auto &[r, x, y, z]: circles) {
        cin>>r>>x>>y>>z;
        r /= OFFSET;
        x /= OFFSET;
        y /= OFFSET;
        z /= OFFSET;
    }


    auto integ = [&](ld r, ld center_x, ld p) {
        ld x = min(r, abs(center_x - p) );
        return PI * (r*r * x - x*x*x / 3);
    };

    auto volume_circle = [&](ld r, ld center_x, ld p_left, ld p_right) -> ld {
        if(p_right < center_x) {
            return integ(r, center_x, p_left) - integ(r, center_x, p_right);
        } else if(p_left > center_x) {
            return integ(r, center_x, p_right) - integ(r, center_x, p_left);
        } else {
            // assert(p_left <= center_x && center_x <= p_right);
            return integ(r, center_x, p_left) + integ(r, center_x, p_right);
        }
    };

    auto get_volume_circles = [&](ld left, ld right) {
        ld total_volume = 0;
        for(auto [r, x, y, z]: circles) {
            ld volume = volume_circle(r, z, left, right);
            total_volume += volume;
        }
        return total_volume;
    };


    auto volume_in_range = [&](ld left, ld right){
        ld volume_slice = (right - left) * HEIGHT * DEPTH;
        ld volume_circles = get_volume_circles(left, right);

        return volume_slice - volume_circles;
    };


    ld total = volume_in_range(0, WIDTH);
    ld target_volume = total / s;

    vector<ld> ans;
    ld left = 0;
    for(int i = 0; i < s; i++){

        ld l = left, r = DEPTH;
        while(r-l > eps) {
            ld mid = (l+r)/2;
            ld volume = volume_in_range(left, mid);
            if(volume >= target_volume) {
                r = mid;
            } else {
                l = mid;
            }
        }

        ans.push_back(r - left);
        left = r;
    }

    for(auto x: ans) cout << fixed << setprecision(15) << x << " ";
    cout << endl;



	return 0;
}

