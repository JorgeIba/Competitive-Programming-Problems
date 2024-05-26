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


const int M = 8;
const int MAXLOG = 30;

int dist[1 << M][1 << (2*M)];
// map<int,int> dist[1 << M];

int encode(const vector< pair<int,int> > &state) {
    int n = SZ(state);
    int mask = 0;
    for(int i = 0; i < n; i++) {
        auto [bx, by] = state[i];
        int position = 2*i;
        if(by)
            mask |= (1LL << position);
        if(bx)
            mask |= (1LL << (position+1));

        // int mask_i = 2*bx + by;
        // int position = 2*i;
        // mask |= (mask_i << position);
    }
    return mask;
}

void bfs(const vector<int> &x, const vector<int> &y, const vector<int> &m, int id) {
    int n = SZ(x);
    vector< pair<int,int> > curr(n);
    for(int i = 0; i < n; i++) curr[i] = {x[i], y[i]};

    queue< vector< pair<int,int> > > q;
    dist[id][encode(curr)] = 0;
    q.push(curr);

    auto get_next = [&](const vector< pair<int,int> > &curr) {
        vector< vector<pair<int,int> > > options(4);
        for(int i = 0; i < n; i++){
            auto [x, y] = curr[i];
            options[0].push_back({x & y, y});
            options[1].push_back({x | y, y});
            options[2].push_back({x, x ^ y});
            options[3].push_back({x, y ^ m[i]});
        }
        return options;
    };

    while(!q.empty()) {
        auto u = q.front(); q.pop();
        auto next = get_next(u);

        for(auto option: next) {
            int code = encode(option);
            if(dist[id][code] != -1) continue;
            // if(dist[id].count(code)) continue;
            
            dist[id][code] = dist[id][encode(u)] + 1;

            q.push(option);
        }
    }
}

void calcAll(){
    memset(dist, -1, sizeof(dist));

    forn(mask, 1 << M) {
        vector<int> a, b, m;

        for(int j = 0; j < M; j++) {
            if(mask & (1 << j)) {
                int bm = j % 2;
                int bb = (j/2) % 2;
                int ba = (j/4) % 2;
                a.push_back(ba);
                b.push_back(bb);
                m.push_back(bm);
            }
        }

        bfs(a, b, m, mask);
    }
}

void main_(){
    int a, b, c, d, m; cin>>a>>b>>c>>d>>m;
    
    map<int, set< pair<int,int> >> position_to_change;
    int mask = 0;
    for(int i = 0; i < MAXLOG; i++) {
        int ba = (a>>i) & 1;
        int bb = (b>>i) & 1;
        int bm = (m>>i) & 1;

        int bc = (c>>i) & 1;
        int bd = (d>>i) & 1;

        int position = 4 * ba + 2 * bb + bm;
        mask |= (1 << position);

        position_to_change[position].insert({bc, bd});
    }
    
    for(auto [group, to_change]: position_to_change) {
        if(SZ(to_change) > 1) {
            cout << -1 << endl;
            return;
        }
    }

    vector< pair<int,int> > final_state;
    for(auto [position, to_change]: position_to_change) {
        auto final_position = *to_change.begin();
        final_state.push_back(final_position);
    }

    int ans = dist[mask][encode(final_state)];
    cout << ans << endl;
}

int main () {
	fastIO();
    calcAll();

	int t = 0; 
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}

