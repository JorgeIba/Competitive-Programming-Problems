#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


int main () {
	//fastIO();
	
    int n; cin>>n;
    map< string, array<int, 3> > socks;

    map< string, int > side_to_id = {
        {"left", 0},
        {"right", 1},
        {"any", 2}
    };

    forn(i, n) {
        string s, t;
        int many; 
        cin>>s>>t>>many;

        socks[s][side_to_id[t]] += many;
    }

    map< string, bool > taken;

    int ans = 0;
    for(auto &[name, quantities]: socks) {
        if(quantities[0] || quantities[1]) {
            taken[name] = true;
            int maxi = max(quantities[0], quantities[1]);
            ans += maxi;
            if(quantities[0] == maxi) quantities[0] = 0;
            else quantities[1] = 0;
        }
    }

    for(auto &[name, quantities]: socks){
        if(!taken[name]) {
            if(quantities[2]) {
                ans++;
                quantities[2]--;
                taken[name] = true;
            }
        }
    }

    bool is_ans = false;
    for(auto &[name, quantities]: socks){
        if(quantities[0] || quantities[1] || quantities[2]) {
            assert(taken[name]);
            is_ans = true;
            ans++;
            break;
        }
    }


    if(is_ans) {
        cout << ans << endl;
    } else{
        cout << "impossible" << endl;
    }


    






	return 0;
}

