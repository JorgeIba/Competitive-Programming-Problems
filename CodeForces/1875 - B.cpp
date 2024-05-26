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

const lli INF = 1e9 + 100;

void main_(){
    int n, m, k; cin>>n>>m>>k;
    lli sum_g = 0, sum_j = 0;
    
    vector<lli> j(n);
    for(auto &x: j) {
        cin>>x;
        sum_j += x;
    }

    vector<lli> g(m);
    for(auto &x: g) {
        cin>>x;
        sum_g += x;
    }


    lli mx_j = *max_element(all(j));
    lli mx_g = *max_element(all(g));

    lli mn_j = *min_element(all(j));
    lli mn_g = *min_element(all(g));

    lli all_mx = max(mx_g, mx_j);
    lli all_mn = min(mn_g, mn_j);


    if(mx_g - mn_j > 0){
        if(k == 1){
            sum_g -= (mx_g - mn_j);
            sum_j += (mx_g - mn_j);
        } else if(k % 2 == 0){
            sum_g -= (mx_g - mn_j);
            sum_j += (mx_g - mn_j);


            sum_j -= (all_mx - all_mn);
            sum_g += (all_mx - all_mn);
        } else {
            sum_g -= (mx_g - mn_j);
            sum_j += (mx_g - mn_j);
        }
    } else {
        if(k == 1){ 

        } else if(k == 2){
            sum_j -= (mx_j - mn_g);
            sum_g += (mx_j - mn_g);
        } else if(k % 2 == 1){
            sum_j -= (mx_j - mn_g);
            sum_g += (mx_j - mn_g);

            sum_j += (all_mx - all_mn);
            sum_g -= (all_mx - all_mn);
        } else {
            sum_j -= (mx_j - mn_g);
            sum_g += (mx_j - mn_g);
        }
    }
    

    cout << sum_j << endl;


}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

