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

const int MAX_SZ = 6;
const int MAX_A = 1e6+10;

int dp[MAX_SZ+1][MAX_A+100];
int fr[MAX_A+100];


auto convert = [](int n) {
    string s_num = to_string(n);
    reverse(all(s_num));
    while( SZ(s_num) < MAX_SZ ) s_num.push_back('0');
    reverse(all(s_num));
    return s_num;
};


int f(int idx, int num) {
    if(idx == MAX_SZ) {
        if(num > MAX_A) return 0;
        return fr[num];
    }
        
    int &ans = dp[idx][num];
    if(ans != -1) return ans;

    ans = 0;
    string s = convert(num);

    int limit = s[idx] - '0';
    for(int d = 0; d <= limit; d++) {
        auto aux = s;
        aux[idx] = d + '0';

        ans += f(idx+1, stoll(aux));
    }

    return ans;
}



int main () {
	fastIO();

    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;
    
    for(auto x: nums) fr[x]++;

    memset(dp, -1, sizeof(dp));

    lli ans = 0;
    for(auto x: nums) {
        string target(MAX_SZ, '0');
        string x_s = convert(x);

        for(int i = 0; i < SZ(x_s); i++) {
            int d_x = x_s[i] - '0';
            int d_target = 9 - d_x;

            target[i] = (d_target + '0');
        }

        int num_target = stoll(target);

        ans += f(0, num_target);
    }

    for(auto x: nums) {
        string s = convert(x);
        bool bad = true;
        for(int i = 0; i < SZ(s); i++){
            int d = s[i] - '0';
            
            if(d + d >= 10) bad = false;
        }
        
        if(bad)
            ans--;
    }

    cout << ans / 2 << endl;
    






	return 0;
}

