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
	fastIO();

    int n, m; cin>>n>>m;

    vector<int> A(n+1), B(m+1);
    forr(i, 1, n) cin>>A[i];
    forr(i, 1, m) cin>>B[i];

    auto get_cycles = [](vector<int> perm, int n){
        vector<bool> visited(n+1);
        vector< vector<int> > cycles;
        for(int i = 1; i <= n; i++){
            if(visited[i]) continue;
            int j = i;
            vector< int > cycle;
            do {
                cycle.push_back(j);
                visited[j] = true;
                j = perm[j];
            }while(j != i);
            cycles.push_back(cycle);
        }
        return cycles;
    };

    auto where = [](int pivot, int target, int n) -> pair<int,int> {
        if(pivot < target) {
            return {n - pivot + 1, target - pivot};
        } else {
            return {n - pivot + 1, (n - pivot + 1) + target};
        }
    };

    auto moves_swap = [&where](int i, int j, int n, const vector<int> &pos){
        int ri = pos[i], rj = pos[j];
        // if(ri > rj) swap(ri, rj);
        vector< int > moves;

        moves.push_back(ri);
        tie(ri, rj) = where(ri, rj, n);

        moves.push_back(rj);
        tie(rj, ri) = where(rj, ri, n);

        moves.push_back(ri);
        tie(ri, rj) = where(ri, rj, n);

        return moves;
    };

    auto get_solution = [&moves_swap](vector< vector<int> > cycles, vector<int> pos, int n) {

        vector< int > all_moves;
        for(auto v: cycles){
            for(int i = 0; i < SZ(v)-1; i++){
                int x = v[i], y = v[i+1];
                auto moves = moves_swap(x, y, n, pos);
                
                all_moves.insert(all_moves.end(), all(moves));
                swap(pos[x], pos[y]);
            }
        }
        return all_moves;
    };

    vector<int> pos_A(n+1), pos_B(m+1);
    forr(i, 1, n) pos_A[A[i]] = i;
    forr(i, 1, m) pos_B[B[i]] = i;


    auto cycles_A = get_cycles(A, n);
    auto sol_A = get_solution(cycles_A, pos_A, n);

    auto cycles_B = get_cycles(B, m);
    auto sol_B = get_solution(cycles_B, pos_B, m);

    int total_swaps_A = 0, total_swaps_B = 0;
    for(auto v: cycles_A){
        total_swaps_A += SZ(v) - 1;
    }
    for(auto v: cycles_B){
        total_swaps_B += SZ(v) - 1;
    }

    int n_sol_A = SZ(sol_A);
    int n_sol_B = SZ(sol_B);


    int diff = abs(n_sol_A - n_sol_B);
    // debugg(diff);


    vector< pair<int,int> > ans(5*n, {-1, -1});
    int itr_A = 0;
    for(; itr_A < n_sol_A; itr_A++){
        ans[itr_A].first = sol_A[itr_A];
    }

    int itr_B = 0;
    for(; itr_B < n_sol_B; itr_B++){
        ans[itr_B].second = sol_B[itr_B];
    }

    int k = max(itr_A, itr_B);
    if(diff % 2) {
        if(n % 2 == 0 && m % 2 == 0) {
            cout << -1 << endl;
            return 0;
        }

        if(n % 2 == 1){
            for(; itr_A < n_sol_A + n; itr_A++){
                ans[itr_A].first = 1;
            }
        } else {
            assert(m % 2 == 1);
            for(; itr_B < n_sol_B + m; itr_B++){
                ans[itr_B].second = 1;
            }
        }
        
        // Complete
    } else {
        // Complete
    }


    k = max(itr_A, itr_B);
    cout << k << endl;
    int last = 1;
    assert(abs(k - itr_A) % 2 == 0);
    for(; itr_A < k; itr_A++){
        ans[itr_A].first = last;
        last = (last == 1 ? n : 1);
    }

    last = 1;
    assert(abs(k - itr_B) % 2 == 0);
    for(; itr_B < k; itr_B++){
        ans[itr_B].second = last;
        last = (last == 1 ? m : 1);
    }

    ans.resize(k);
    for(auto [i, j]: ans) cout << i << " " << j << endl;



	return 0;
}

