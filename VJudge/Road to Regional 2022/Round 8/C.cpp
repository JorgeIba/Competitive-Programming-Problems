#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


int ask(int up, int down, int left, int right) {
    cout << "? " << up << " " << down << " " << left << " " << right << endl;
    cout.flush();
    int ans; cin>>ans;
    return ans;
}



int main () {
	//fastIO();
	int n; cin>>n;

    int l = 1, r = n, ans_row = 0;

    while(l <= r){
        int mid = l + (r-l)/2;
        int how_many = ask(l, mid, 1, n);
        int expected = mid - l + 1;

        
        if(how_many == expected) {
            l = mid+1;
            ans_row = mid;
        } else {
            r = mid-1;
        }
    }


    l = 1, r = n;
    int ans_col = 0;
    while(l<=r){
        int mid = l + (r-l)/2;
        int how_many = ask(1, n, l, mid);
        int expected = mid - l + 1;

        if(how_many == expected){
            l = mid+1;
            ans_col = mid;
        } else {
            r = mid-1;
        }
    }


    cout << "! " << ans_row+1 << " " << ans_col+1 << endl;


	return 0;
}

