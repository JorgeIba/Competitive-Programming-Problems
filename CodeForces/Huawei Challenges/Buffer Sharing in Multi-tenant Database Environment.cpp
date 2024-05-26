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


struct Limit{
    int ql, qbase, qr;
    Limit() {}
    Limit(int ql, int qbase, int qr): ql(ql), qbase(qbase), qr(qr) {}
};


// INPUTS
const int MAXN = 10;
int priorities[MAXN+5];
int priorities_by_size[MAXN+5];
int database_sizes[MAXN+5];
Limit limits[MAXN+5];


template<typename T = int>
struct Manager{
    int N;

    Manager(){}
    Manager(int n): N(n) {}

    unordered_map<int,int> tenants[MAXN+5];

    unordered_map<int,T> weighted_sum[MAXN+5];
    set< pair<T,int> > least_weight_active[MAXN+5];

    int total_error = 0;

    int get_key(int t, int p) {
        assert(tenants[t].count(p));
        return tenants[t][p];
    }

    int exists(int t, int p) {
        return tenants[t].count(p);
    }

    void update_weight_active(int t, int p, int t_n) {

    };

    int get_least_weight(int t) {
        auto [weight, least] = *least_weight_active[t].begin();
        assert(tenants[t].count(least));

        return least;
    };

    void remove(int t, int p) {
        assert(exists(t, p));

        tenants[t].erase(p);
        T weight = weighted_sum[t][p];
        assert(least_weight_active[t].count({weight, p}));
        least_weight_active[t].erase({weight, p});
    }

    T get_weight(int t, int p) {
        return weighted_sum[t][p];
    }

    void assign_page_in_buffer(int t, int p, int space) {
        tenants[t][p] = space;  
    };

    int get_actives(int t) {
        assert(SZ(tenants[t]) == SZ(least_weight_active[t]));
        return SZ(tenants[t]);
    }
};


struct ManagerFreq: public Manager<int>{
    ManagerFreq() {}
    ManagerFreq(int n): Manager<int>(n) {

    }

    void update_weight_active(int t, int p, int t_n) {
        using super = Manager<int>;
    
        int old_weight = super::weighted_sum[t][p];

        super::least_weight_active[t].erase({old_weight, p});

        super::weighted_sum[t][p]++;
        int curr_weight = weighted_sum[t][p];
                
        super::least_weight_active[t].insert({curr_weight, p});
    };
};


struct ManagerLRU: public Manager<int>{
    ManagerLRU() {}
    ManagerLRU(int n): Manager<int>(n) {}

    void update_weight_active(int t, int p, int t_n) {
        using super = Manager<int>;

        int old_weight = super::weighted_sum[t][p];

        super::least_weight_active[t].erase({old_weight, p});

        super::weighted_sum[t][p] = t_n;
        int curr_weight = super::weighted_sum[t][p];
                
        super::least_weight_active[t].insert({curr_weight, p});
    };
};


set<int> availables;

int n, q, m;


// new space, who before, page before
template<typename T>
tuple<int,int,int> update(int t, int p, int test, Manager<T> &Man) {
    if(Man.exists(t, p)){
        auto space_p = Man.get_key(t, p);

        return {space_p, -1, -1};
    }

    if(Man.get_actives(t) >= limits[t].qr) { // tienes que quitarte a ti mismo
        auto least = Man.get_least_weight(t);
        auto space_least = Man.get_key(t, least);

        Man.total_error++;
        return {space_least, t, least};
    }

    if(!availables.empty()) {
        auto space = *availables.begin();

        return {space, -2, -2};
    }

    // quita de otra persona
    vector< tuple<int,int, T> > spaces;
    forr(i, 1, n) {
        if(limits[i].ql < Man.get_actives(i)) {
            auto least_i = Man.get_least_weight(i);
            auto weight_i = Man.get_weight(i, least_i);
            spaces.push_back({i, least_i, weight_i});
        }
    }

    sort(all(spaces), [&](auto a, auto b) {
        auto [t_a, l_a, w_a] = a;
        auto [t_b, l_b, w_b] = b;
        return w_a < w_b;
    });

    auto [t_i, least_i, _] = spaces[0];
    auto space_least = Man.get_key(t_i, least_i);

    Man.total_error++;
    return {space_least, t_i, least_i};
}




int main () {
	// fastIO();

    cin>>n>>q>>m;
    forr(i, 1, n) {
        cin>>priorities[i];
    }

    forr(i, 1, n){
        cin>>database_sizes[i];
    }

    forr(i, 1, n) {
        int ql, qbase, qr; cin>>ql>>qbase>>qr;
        limits[i] = {ql, qbase, qr};
    }

    
    forr(i, 1, q) availables.insert(i);

    vector<pair<int,int>> sorted_databases;
    forr(i, 1, n) sorted_databases.push_back({i, database_sizes[i]});
    sort(all(sorted_databases), [&](auto a, auto b) {
        return a.second < b.second;
    });

    forn(i, n) {
        auto [ten, sz] = sorted_databases[i];
        priorities_by_size[ten] = i+1;
    }

    ///////////////////////////////

    ManagerFreq FreqMan(n);
    ManagerLRU  LRUMan(n);


    bool freq_active = true;

    int last = 0;
    forr(test, 1, m){
        int t, p; cin>>t>>p;

        auto update_pages = [&](int space, int old_ten, int old_page) {
            LRUMan.update_weight_active(t, p, test);
            LRUMan.assign_page_in_buffer(t, p, space);

            FreqMan.update_weight_active(t, p, test);
            FreqMan.assign_page_in_buffer(t, p, space);


            if(old_ten == -2) {
                availables.erase(space);
            } else if(old_ten != -1) {
                LRUMan.remove(old_ten, old_page);
                FreqMan.remove(old_ten, old_page);
            }
        };


        auto [space_lru,  who_taken_lru,  which_taken_lru]  = update(t, p, test, LRUMan);
        auto [space_freq, who_taken_freq, which_taken_freq] = update(t, p, test, FreqMan);
        
        if(freq_active) {
            update_pages(space_freq, who_taken_freq, which_taken_freq);
            cout << space_freq << endl;
            cout.flush();
        } else {
            update_pages(space_lru, who_taken_lru, which_taken_lru);
            cout << space_lru << endl;
            cout.flush();
        }


        if(freq_active){
            if((ld) FreqMan.total_error / (test - last) > 0.2) {
                freq_active = false;
                LRUMan.total_error = 0;
                FreqMan.total_error = 0;
                last = test;
            }
        } else {
            if((ld) LRUMan.total_error / (test - last) > 0.6) {
                freq_active = true;
                FreqMan.total_error = 0;
                LRUMan.total_error = 0;
                last = test;
            }
        }
    }



	return 0;
}