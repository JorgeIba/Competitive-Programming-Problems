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


void main_(){
    int m; cin>>m;

    vector< string > ss(3);
    for(auto &s: ss) cin>>s;
    ss[0] = ss[0] + ss[0] + ss[0];
    ss[1] = ss[1] + ss[1] + ss[1];
    ss[2] = ss[2] + ss[2] + ss[2];


    int n = SZ(ss[0]);
    vector< vector<vector<int>> > last(3, vector<vector<int>>(10));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++){
            last[j][ ss[j][i] - '0'  ].push_back(i);
        }
    }

    vector<int> perm = {0, 1, 2};

    int inf = 1e9;
    int ans = inf;
    do{

        int min_time = 1e9;
        for(int d = 0; d < 9; d++){
            set<int> dist;
            int time_d = inf;
            for(auto idx: perm){
                for(auto time_d: last[idx][d]){
                    if(!dist.count(time_d)){
                        dist.insert(time_d);
                        break;
                    }
                }        
            }
            if(SZ(dist) == 3){
                time_d = *dist.rbegin();
            }

            min_time = min(min_time, time_d);
        }
        ans = min(ans, min_time);
    }while(next_permutation(all(perm)));


    cout << (ans != inf ? ans : -1) << endl;

}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

