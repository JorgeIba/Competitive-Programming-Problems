#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


lli n;
const lli INF = 1e18;

struct Task {
    lli t, d, idx;
    Task() {}
    Task(lli t, lli d, lli idx): t(t), d(d), idx(idx) {}
};


bool calcDist(const vector<Task> &tasks, vector<lli> &dists){
    bool ans = true;
    lli total_time = 0;
    for(int i = 0; i < n; i++) {
        Task x = tasks[i];
        if(x.t + total_time > x.d)
            ans = false;
        total_time += x.t;
        dists[x.idx] = x.d - total_time;   
    }
    return ans;
}


int main () {
	fastIO();

    cin>>n;
    vector< Task > tasks(n);

    for(int i = 1; i <= n; i++) {
        lli t, d; cin>>t>>d;
        tasks[i-1] = {t, d, i};
    }


    sort(all(tasks), [&](Task a, Task b) {
        return a.d < b.d || (a.d == b.d && a.idx < b.idx);
    });


    vector<lli> dists(n+1);

    bool ans = calcDist(tasks, dists);


    if(!ans) {
        cout << "*" << endl;
        return 0;
    }


    
    for(int i = 0; i < n; i++) {
        lli min_free_time = INF;
        Task min_task = {0,0,0};
        int idx_min = -1;
        for(int j = i; j < n; j++) {
            Task current = tasks[j];
            if(min_free_time - current.t >= 0) {
                // cout << current.idx << " can " << endl;
                // is posible to put this at the beginning
                if(min_task.idx == 0 || current.idx < min_task.idx) {
                    min_task = current;
                    idx_min = j;
                }
            }

            min_free_time = min(min_free_time, dists[current.idx]);
        }

        if(min_task.idx != 0) {
            tasks.erase(tasks.begin() + idx_min);
            tasks.insert(tasks.begin() + i, min_task);
        }

        bool ans = calcDist(tasks, dists);
        assert(ans == true);
    }

    for(auto x: tasks) {
        cout << x.idx << " ";
    }

	return 0;
}

