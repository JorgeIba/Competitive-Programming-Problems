#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


const int TRHESHOLD = 200;

int main () {
	fastIO();

    int n, m; cin>>n>>m;


    vector< int > generators(n+1);
    for(int i = 1; i <= n; i++) 
        cin>>generators[i];


    vector< vector<int> > adjListAppliance(m+1), adjListGenerators(n+1);

    for(int i = 1; i <= m; i++){
        int c; cin>>c;
        for(int j = 0; j < c; j++){
            int u; cin>>u;
            adjListAppliance[i].push_back(u);
            adjListGenerators[u].push_back(i);
        }
    }

    vector< vector<int> > biggers(m+1);
    vector< lli > sum(m+1), sum2(m+1);

    for(int i = 1; i <= m; i++){
        for(auto v: adjListAppliance[i]){
            if(  SZ(adjListGenerators[v]) > TRHESHOLD ) {
                biggers[i].push_back(v);
            } else {
                sum[i] += generators[v];
                sum2[i] += generators[v] * generators[v];
            }
        }
    }



    int q; cin>>q;
    while(q--){
        int t; cin>>t;
        if(t == 1){
            int idx_gen, x; cin>>idx_gen>>x;
            if(SZ(adjListGenerators[idx_gen]) > TRHESHOLD){
                generators[idx_gen] = x;
            } else {
                int before = generators[idx_gen];
                for(auto v: adjListGenerators[idx_gen]){
                    sum[v] += (x - before);
                    sum2[v] += (1LL*x*x - 1LL*before*before);
                }
                generators[idx_gen] = x;
            }

        } else{
            int idx_appl; cin>>idx_appl;
            lli total_sum = sum[idx_appl], total_sum2 = sum2[idx_appl];
            for(auto v: biggers[idx_appl]){
                total_sum += generators[v];
                total_sum2 += 1LL*generators[v] * generators[v];
            }

            cout << (total_sum*total_sum - total_sum2) / 2 << endl;
        }
    }







	return 0;
}

