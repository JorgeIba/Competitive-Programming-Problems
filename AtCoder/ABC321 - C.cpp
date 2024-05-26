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

vector< string > options;
void generate(string option){
    options.push_back(option);

    int limit_lower = (option.empty() ? -1 : option.back() - '0') + 1;

    for(int d = limit_lower; d <= 9; d++){
        auto aux = option;
        aux.push_back(d + '0');
        generate(aux);
    }
}


int main () {
	//fastIO();
	

    generate({});

    for(auto &s: options){
        reverse(all(s));
    }

    vector<lli> ans;
    for(auto s: options){
        if(s.empty()) continue;
        ans.push_back(stoll(s));
    }

    sort(all(ans));
    // for(auto x: ans) cout << x << " ";


    int k; cin>>k;
    cout << ans[k] << endl;


	return 0;
}

