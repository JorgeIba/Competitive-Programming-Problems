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



lli best_ans(map<int, vector<pair<int,int>>> ys, map<int,lli> xs){

    multiset< lli > xs_vals;
    for(auto [x, vals]: xs) {
        xs_vals.insert(vals);
    }


    auto best_k = [&](int k){
        auto itr = xs_vals.rbegin();
        lli best = 0;
        forn(i, k) {
            if(itr == xs_vals.rend()) break;
            best += *itr;
            itr++;
        }
        return best;
    };

    lli first_option = best_k(3);

    lli second_option = 0;
    for(auto [y, vec_x_v]: ys){
        lli val_y = 0;
        for(auto [x, val]: vec_x_v){
            int old = xs[x];
            int new_x = xs[x] - val;
            val_y += val;

            auto itr_aux = xs_vals.find(old);
            assert(itr_aux != xs_vals.end());
            xs_vals.erase(itr_aux);
            xs_vals.insert(new_x);
        }


        second_option = max(second_option, val_y + best_k(2));

        for(auto [x, val]: vec_x_v){
            int old = xs[x] - val;
            int new_x = xs[x];

            auto itr_aux = xs_vals.find(old);
            assert(itr_aux != xs_vals.end());
            xs_vals.erase(itr_aux);
            xs_vals.insert(new_x);
        }
    }

    return max(first_option, second_option);
}


int main () {
	fastIO();
	
    int n; cin>>n;
    
    
    vector< array<lli, 3> > monsters(n);
    forn(i, n){
        lli x, y, v; cin>>x>>y>>v;        
        monsters[i] = {x, y, v};
    }


    map<int, vector<pair<int,int>>> ys;
    map<int, lli> xs;

    for(auto [x, y, v]: monsters){
        ys[y].push_back({x, v});
        xs[x] += v;
    }

    lli first_option = best_ans(ys, xs);


    ys.clear();
    xs.clear();

    for(auto [x, y, v]: monsters){
        ys[x].push_back({y, v});
        xs[y] += v;
    }

    lli second_option = best_ans(ys, xs);

    cout << max(first_option, second_option) << endl;





	return 0;
}

