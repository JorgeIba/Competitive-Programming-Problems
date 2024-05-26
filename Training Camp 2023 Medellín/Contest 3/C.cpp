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


void main_(){
    string s; cin>>s;
    int n = SZ(s);

    int zeros = count(all(s), '0');
    int ones  = count(all(s), '1');
    if(ones == 0) {
        cout << 0 << endl;
        return;
    } else if(zeros == 0){
        cout << (1LL) * n * n << endl;
        return;
    }

    int longest = 0;
    for(int i = 0; i < n; ){
        if(s[i] == '0'){
            i++;
            continue;
        }
        int j = i;
        while(j < n && s[i] == s[j]) {
            j++;
        }
    
        longest = max(longest, j-i);

        i = j;
    }


    int longest_prefix = 0;
    
    int j = 0;
    while(j < n && s[j] == '1'){
        longest_prefix++;
        j++;
    }


    int longest_suffix = 0;

    j = n-1;
    while(j >= 0 && s[j] == '1') {
        longest_suffix++;
        j--;
    }


    // debugg(longest);
    // debugg(longest_prefix);
    // debugg(longest_suffix);
    longest = max(longest, longest_prefix + longest_suffix);

    lli ans = 0;
    for(int i = 0; i <= longest; i++){
        ans = max(ans, 1LL * (longest-i) * (i+1));
    }
    cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

