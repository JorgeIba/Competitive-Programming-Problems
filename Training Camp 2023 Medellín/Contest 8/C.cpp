#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

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
using namespace __gnu_pbds;


const lli MOD_1 = 1e9 + 7, P_1 = 31, PI_1 = 129032259ll; 
const lli MOD_2 = 1824261409, P_2 = 53, PI_2 = 1411221090; 

template<lli MOD, lli P, lli PI>
struct Hash {
    
	vector<lli> h,pi;
	Hash(string& s){
		assert((P*PI)%MOD==1);
		h.resize(s.size()+1);
		pi.resize(s.size()+1);
		h[0] = 0;
		pi[0] = 1;
		lli p = 1;
		forr(i,1,SZ(s)){
			h[i] = (h[i-1] + p*s[i-1]%MOD);
            if(h[i] >= MOD) h[i] -= MOD;

			pi[i] = pi[i-1] * PI %MOD;
			p = p*P %MOD;
		}
	}
	//returns the hash of substring [s,e)
	int get(int s, int e){
		return ((h[e] - h[s] + MOD))*pi[s] % MOD;
	}
};

// gp_hash_table<lli, int> safe_hash_table; // va a madres
// cc_hash_table<int, int> hash_table; // Este va más a madres
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
        
        return hash1;
    }
};

int main () {
	//fastIO();
	
	string s, t; cin>>s>>t;
    auto s_rev = s; reverse(all(s_rev));

    int n = SZ(s);
    int m = SZ(t);

    auto s_rev_hash_1 = Hash<MOD_1, P_1, PI_1>(s_rev);
    auto s_hash_1 = Hash<MOD_1, P_1, PI_1>(s);
    auto t_hash_1 = Hash<MOD_1, P_1, PI_1>(t);
    
    auto s_rev_hash_2 = Hash<MOD_2, P_2, PI_2>(s_rev);
    auto s_hash_2 = Hash<MOD_2, P_2, PI_2>(s);
    auto t_hash_2 = Hash<MOD_2, P_2, PI_2>(t);

    auto get_hash_t = [&](int l, int r) -> pair<int,int> {
        return {t_hash_1.get(l, r), t_hash_2.get(l, r)};
    };

    auto get_hash_s = [&](int l, int r) -> pair<int,int> {
        return {s_hash_1.get(l, r), s_hash_2.get(l, r)};
    };

    auto get_hash_s_rev = [&](int l, int r) -> pair<int,int> {
        return {s_rev_hash_1.get(l, r), s_rev_hash_2.get(l, r)};
    };


    for(char c = 'a'; c <= 'z'; c++){
        int count_cs = count(all(s), c);
        int count_ct = count(all(t), c);
        if(count_ct > 0 && count_cs == 0){
            cout << -1 << endl;
            return 0;
        }
    }

    gp_hash_table<pair<int,int>, pair<int,int>, hash_pair> hashes_s_rev;
    gp_hash_table<pair<int,int>, pair<int,int>, hash_pair> hashes_s;
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            // auto hassh_s = s_hash.get(i, j+1);
            // int hassh_s_rev = s_rev_hash.get(i, j+1);

            hashes_s[ get_hash_s(i, j+1) ] = {i, j};
            hashes_s_rev[ get_hash_s_rev(i, j+1) ] = {n-i-1, n-j-1};
        }
    }



    // auto check = [&](int lt, int rt) -> pair<int,int> {
    //     int sizee = rt-lt+1;
    //     auto hash_sub = t_hash.get(lt, rt+1);
    //     for(int l = 0; l <= n_2 - sizee; l++){
    //         if(s_hash.get(l, l + sizee) == hash_sub){
    //             // debugg(sizee);
    //             // debugg(hash_sub);
    //             // debugg(s_hash.get(l, l + sizee));
            
    //             int r = l + sizee-1;

    //             if(l >= n_1){
    //                 // debugg(l);
    //                 // debugg(r);

    //                 // debugg(n_2 - l - 1);
    //                 // debugg(n_2 - r - 1);

    //                 return {n_2-l-1, n_2-r-1};
    //             } else {
    //                 return {l, r};
    //             }
    //         }
    //     }
    //     return {-1, -1};
    // };

    // auto bin = [&](int start) {
    //     int l = start, r = n_2, ans = l;
    //     while(l <= r){
    //         int mid = (l+r)/2;
    //         auto [l_a, r_a] = check(l, mid);
    //         if(l_a != -1){
    //             ans = mid;
    //             l = mid+1;
    //         } else{
    //             r = mid-1;
    //         }
    //     }
    //     // debugg(ans);

    //     return ans;
    // };


    vector< pair<int,int> > ans;
    for(int i = 0; i < m; ){
        int j_1 = i;
        while(j_1 < m && hashes_s.find( get_hash_t(i, j_1+1)) != hashes_s.end())
            j_1++;

        int j_2 = i;
        while(j_2 < m && hashes_s_rev.find( get_hash_t(i, j_2+1)) != hashes_s_rev.end())
            j_2++;
        

        if(j_1 > j_2){
            auto [l, r] = hashes_s[ get_hash_t(i, j_1)];

            ans.push_back({l, r});
        } else {
            auto [l, r] = hashes_s_rev[ get_hash_t(i, j_2)];

            ans.push_back({l, r});
        }
        

        i = max(j_1, j_2);
    }
    cout << SZ(ans) << endl;
    for(auto [l, r]: ans) cout << l+1 << " " << r+1 << endl;
    



	return 0;
}

