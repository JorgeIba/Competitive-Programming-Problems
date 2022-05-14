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


int main () {
	//fastIO();

    lli n, k; cin>>n>>k;

    string floor1, floor2; cin>>floor1>>floor2;

    vector<lli> first_floor, second_floor;


    for(int i = 1; i <= n; i++) 
        if(floor1[i-1] == '1') second_floor.push_back(i);

    for(int i = 1; i <= n; i++) 
        if(floor2[i-1] == '1') first_floor.push_back(i);



    lli sum_up = 0, sum_down = 0;
    for(auto x: first_floor) sum_up += x;
    for(auto x: second_floor) sum_down += x;


    lli ans = 1e9, ans_f = -1, ans_i = -1;


    // in first floor
    for(int i = 1; i <= n; i++) {
        lli ans_max = 0;
        for(auto x: first_floor) {
            ans_max = max(ans_max, abs(i-x));
        }
        for(auto x: second_floor) {
            ans_max = max(ans_max, x + k + i);
        }
        if(ans_max < ans) {
            
            ans_f = 1, ans_i = i;
            ans = ans_max;
        }
        
    }
    


    for(int i = 1; i <= n; i++) {
        lli ans_max = 0;
        for(auto x: second_floor) {
            ans_max = max(ans_max, abs(i-x));
        }
        for(auto x: first_floor) {
            ans_max = max(ans_max, x + k + i);
        }
        if(ans_max < ans) {
            ans_f = 2, ans_i = i;
            ans = ans_max;
        }
        
    }

    cout << ans << endl;
    cout << ans_f << " " << ans_i << endl;




	return 0;
}

