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
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


map< string, int > day_to_n = {
    {"Monday",    0},
    {"Tuesday",   1},
    {"Wednesday", 2},
    {"Thursday",  3},
    {"Friday",    4},
    {"Saturday",  5},
    {"Sunday",    6},
};

const int MAX_D = 3e6;
const int MAXN = 2e5+100;

bool holy_days[MAX_D];

array<bool, 7> employees[MAXN];
vector<int> projects[MAXN];
set<int> current_working[MAXN];
int index[MAXN];
bool someone_work[7];

int main () {
	fastIO();
	
    int n, m, k; cin>>n>>m>>k;

    forn(i, n) {
        int l; cin>>l;
        forn(j, l) {
            string s; cin>>s;
            employees[i][ day_to_n[s] ] = true;
            someone_work[ day_to_n[s] ] = true;
        }
    }

    forn(i, m) {
        int d; cin>>d; d--;
        if(d > MAX_D) continue;
        holy_days[d] = true;
    }

    forn(i, k) {
        int q; cin>>q;
        projects[i].resize(q);
        forn(j, q) {
            cin>>projects[i][j];
            projects[i][j]--;
        }
    }

    vector< set< int > > actives(7);
    forn(i, k) {
        auto worker = projects[i][  index[i]  ];
        current_working[worker].insert(i);

        forn(j, 7) if(employees[worker][j]) {
            actives[j].insert(worker);
        }
    }


    vector<int> ans(k);
    for(int day = 0; day < MAX_D; day++) {
        if(holy_days[day]) continue;

        if(actives[day % 7].empty()) continue;

        vector<int> worker_to_add;
        vector<int> worker_to_remove;
        vector< pair<int,int> > to_add;

        for(const auto &worker: actives[day % 7]) {
            worker_to_remove.push_back(worker);

            int name_day = day % 7;

            if(employees[worker][name_day]) { // Este día si chambea
                auto iter = current_working[worker].begin();
                int project_worker = *iter;
                current_working[worker].erase(iter);

                if(!current_working[worker].empty()) {
                    worker_to_add.push_back(worker);
                }

                index[project_worker]++;

                if(index[project_worker] == SZ(projects[project_worker])) {
                    ans[project_worker] = day;
                } else {
                    auto next_worker = projects[project_worker][ index[project_worker] ];
                    // current_working[next_worker].insert(project_worker);
                    to_add.push_back({next_worker, project_worker});
                    worker_to_add.push_back(next_worker);
                }
            } else {
                assert(false);
            }
        }

        for(auto worker: worker_to_remove) {
            forn(i, 7) if(employees[worker][i]) {
                actives[i].erase(worker);
            }
        }

        for(auto worker: worker_to_add) {
            forn(i, 7) if(employees[worker][i]) {
                actives[i].insert(worker);
            }
        }


        for(const auto &[worker, project]: to_add) 
            current_working[worker].insert(project);
    }


    forn(i, k) cout << ans[i] + 1 << " ";
    cout << endl;

	return 0;
}

