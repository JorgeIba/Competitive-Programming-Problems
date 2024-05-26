#include<bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl '\n'
#define forn(i, n) for(int i = 0; i < (n); i++) 
#define forr(i, a, b) for(int i = (a); i <= (b); i++) 
#define SZ(a) (int) a.size()
#define pb push_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;


typedef vector<lli> Poly;
#define point pair<int,int>
#define x first
#define y second


point operator+(point a, point b){
    return {a.x + b.x, a.y + b.y};
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}


int main() {
    // fastIO();

    int n; cin>>n;

    vector< point > players(2);
    forn(i, 2) 
        cin>>players[i].x>>players[i].y;


    vector< point > moves(n);
    for(auto &p: moves) cin>>p.x>>p.y;


    auto get_inverse = [&](auto p) -> point{
        return {-p.x, -p.y};
    };

    auto is_inside = [&](point p) {
        return 1 <= p.x && p.x <= n && 1 <= p.y && p.y <= n;
    };


    auto is_reachable = [&](point origin, point target) {
        set < point > reachable;
        for(auto p: moves) {
            point bob_reach = target + get_inverse(p);
            if(is_inside(bob_reach))
                reachable.insert( bob_reach );
        }
        for(auto p: moves) {
            point alice_reach = origin + p;
            if(!is_inside(alice_reach)) continue;

            if(reachable.count(alice_reach)){
                return 1;
            }
        }
        return 0;
    };


    if(is_reachable(players[0], players[1])) {
        cout << "Alice wins" << endl;
        return 0;
    }


    if(n <= 1000) {
        vector< vector<int> > mat(n+1, vector<int>(n+1));

        for(auto move_1: moves){
            auto bob_next_1 = players[1] + move_1;
            if(!is_inside(bob_next_1)) continue;
            for(auto move_2: moves) {
                auto bob_next_2 = bob_next_1 + move_2;
                if(!is_inside(bob_next_2)) continue;


                mat[bob_next_2.x][bob_next_2.y] = 1;
            }
            mat[bob_next_1.x][bob_next_1.y] = 1;
        }

        auto [x_alice, y_alice] = players[0];
        auto [x_bob, y_bob] = players[1];
        mat[x_bob][y_bob] = 1;
        mat[x_alice][y_alice] = 1;

        for(int x = 1; x <= n; x++) {
            for(int y = 1; y <= n; y++) {
                if(!mat[x][y]) {
                    cout << "tie " <<  x << " " << y << endl;
                    return 0;
                }
            }
        }

        cout << "Bob wins" << endl;
        return 0;
    }

    const int TRIES = 120;
    for(int Try = 0; Try < TRIES; Try++){
        int x = aleatorio(1, n);
        int y = aleatorio(1, n);
        pair<int,int> p = {x, y};

        if(p == players[0] || p == players[1]) continue;


        if(!is_reachable(players[1], p)) {
            cout << "tie " << x << " " << y << endl;
            return 0;
        }
    }

    // assert(false);
    cout << "Bob wins" << endl;


    return 0;
}