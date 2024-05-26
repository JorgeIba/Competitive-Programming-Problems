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


void main_(){
	string s; cin>>s;
    lli x; cin>>x;

    int n = SZ(s);

    vector<int> order(n);
    stack<pair<int,int>> st;
    for(int i = 0, j = 0; i <= n; i++){
        int val = (i < n ? s[i]  : 0);
        while(!st.empty() && st.top().first > val) {
            order[st.top().second] = j++;
            st.pop();
        }

        st.push({val, i});
    }

    int curr_sz = n;
    int take_off = 0;
    while(curr_sz < x) {
        x -= curr_sz;
        curr_sz--;
        take_off++;
    }

    // debugg(curr_sz);
    // debugg(take_off);
    // debugg(x);

    string new_s;
    for(int i = 0; i < n; i++){
        if(order[i] < take_off) {

        } else new_s.push_back(s[i]);
    }
    cout << new_s[x-1];
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

