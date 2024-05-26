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


const int MAXN = 410;
int works[3][MAXN][MAXN];

int main () {
	// fastIO();

    int n; cin>>n;

    vector<int> time_between(n);
    for(auto &x: time_between) cin>>x;

    const int PERSONS = 3;
    vector< vector<int> > attraction_time(PERSONS);
    for(int i = 0; i < PERSONS; i++) {
        attraction_time[i].resize(n);
        for(auto &x: attraction_time[i]) cin>>x;
    } 

    auto get_ranges = [&](int who) {
        vector< vector< pair<int,int> > > ranges_who(n);

        for(int start = 0; start < n; start++) {
            lli Time = 0;
            int curr = start;
            do {
                ranges_who[curr].push_back({Time, Time + attraction_time[who][curr]});
                Time += attraction_time[who][curr] + time_between[curr];
                curr = (curr + 1) % n;
            }while(curr != start);
        }

        return ranges_who;
    };

    auto ranges_A = get_ranges(0);
    auto ranges_B = get_ranges(1);
    auto ranges_C = get_ranges(2);

    forn(i, n){
        forn(j, n){
            works[0][i][j] = 1;
            works[1][i][j] = 1;
            works[2][i][j] = 1;
        }
    }

    typedef vector<vector<pair<int,int>>> type_ranges;
    #define l first
    #define r second

    auto intersect = [&](auto a, auto b) {
        if(a.r <= b.l || b.r <= a.l) return false;
        return true;
    };

    auto calc = [&](int who_1, int who_2, int idx, const type_ranges &ranges_1, const type_ranges &ranges_2) {
        for(int start_1 = 0; start_1 < n; start_1++) {
            for(int start_2 = 0; start_2 < n; start_2++) {
                for(int curr = 0; curr < n; curr++) {

                    auto ranges_curr_1 = ranges_1[curr][start_1];
                    auto ranges_curr_2 = ranges_2[curr][start_2];

                    if(intersect(ranges_curr_1, ranges_curr_2))
                        works[idx][start_1][start_2] = 0;
                }
            }
        }
    };

    calc(0, 1, 0, ranges_A, ranges_B);
    calc(0, 2, 1, ranges_A, ranges_C);
    calc(1, 2, 2, ranges_B, ranges_C);

    forn(start_1, n) {
        forn(start_2, n) {
            forn(start_3, n){

                if(!works[0][start_1][start_2]) continue;

                if(!works[1][start_1][start_3]) continue;

                if(!works[2][start_2][start_3]) continue;

                cout << start_1+1 << " " << start_2 + 1 << " " << start_3 + 1 << endl;
                return 0;
            }
        }
    }

    cout << "impossible" << endl;
	return 0;
}

