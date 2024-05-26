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
	fastIO();

    int n, k; cin>>n>>k;
    vector<int> dices(n);

    for(auto &p: dices) cin>>p;


    deque<int> slide;
    int max_sum = 0, sum = 0;
    for(int i = 0; i < n; i++){
        auto dice = dices[i];

        slide.push_back(dice);
        sum += (dice + 1);

        if(SZ(slide) == k+1){
            sum -= (slide.front()+1);
            slide.pop_front();
        }


        if(SZ(slide) == k && max_sum < sum) {
            max_sum = sum;
        }
    }


    cout << fixed << setprecision(20) << (ld) max_sum / 2 << endl;




	return 0;
}

