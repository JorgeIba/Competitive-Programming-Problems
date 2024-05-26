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
    int n; cin>>n;

    vector<lli> A(n), B(n);

    for(auto &x: A) cin>>x;
    for(auto &x: B) cin>>x;



    vector<lli> scoreA(n), scoreB(n);
    for(int i = 0; i < n; i++) {
        scoreA[i] = A[i]-1;
    }

    for(int i = 0; i < n; i++) {
        scoreB[i] = B[i]-1;
    }

    vector<pair<lli,int>> score(n);
    for(int i = 0; i < n; i++) {
        score[i].first = scoreA[i] + scoreB[i];
        score[i].second = i;
    }

    sort(all(score));
    reverse(all(score));

    lli scoreTotalA = 0, scoreTotalB = 0;
    for(int i = 0, turn = true; i < n; i++, turn = !turn) {
        if(turn){
            scoreTotalA += scoreA[score[i].second];
        } else {
            scoreTotalB += scoreB[score[i].second];
        }
    }

    cout << scoreTotalA - scoreTotalB << endl;

}

int main () {
	fastIO();

	int t = 1; 
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}

