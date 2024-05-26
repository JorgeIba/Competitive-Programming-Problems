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
	//fastIO();

    int n; cin>>n;

    vector< pair<int,int> > pairs;
    for(int i = 1; i <= 2*n; i += 2) {
        pairs.push_back({i, i+1});
    }


    auto validator = [&](const vector<int> &vec){
        lli sum = 0;
        deque<lli> dq;
        pair<lli,lli> sums = {-1, -1};
        for(int i = 0; i < 2*n + n; i++){
            auto num = vec[i%(2*n)];
            if(SZ(dq) < n){
                dq.push_back(num);
                sum += num;
                continue;
            }

            lli front = dq.front();
            dq.pop_front();
            sum -= front;

            dq.push_back(num);
            sum += num;

            if(sums.first == -1) sums.first = sum;
            else if(sums.second == -1) sums.second = sum;


            if(sums.first != -1 && abs(sum - sums.first) > 1) return false;
            if(sums.second != -1 && abs(sum - sums.second) > 1) return false;
        }

        return true;
    };


    vector<int> option_1(2*n), option_2(2*n);

    bool f = false;
    for(int i = 0; i < n; i++){
        auto [x, y] = pairs[i];
        if(f) swap(x, y);

        option_1[i] = x;
        option_1[i+n] = y;


        f = !f;
    }

    f = true;
    for(int i = 0; i < n; i++){
        auto [x, y] = pairs[i];
        if(f) swap(x, y);

        option_2[i] = x;
        option_2[i+n] = y;


        f = !f;
    }


    if(validator(option_1)){
        cout << "YES" << endl;
        for(auto x: option_1) cout << x << " ";
        cout << endl;
    }else if(validator(option_2)){
        cout << "YES" << endl;
        for(auto x: option_2) cout << x << " ";
        cout << endl;
    } else {
        cout << "NO" << endl;
    }




	return 0;
}

