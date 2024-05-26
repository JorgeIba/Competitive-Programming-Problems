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
	
    int n, a, b; cin>>n>>a>>b; a--, b--;

    if(a > b) swap(a, b);

    vector< pair<int,int> > rounds(n/2);
    for(int i = 0; i < n; i += 2){
        rounds[i/2] = {i, i+1};
    }


    int j = 0;
    while(n ^ (1 << j)) j++;


    for(int round = 1; round <= j; round++){
        for(auto [a_1, b_1]: rounds){
            if(a == a_1 && b == b_1) {
                if(round == j)
                    cout << "Final!" << endl;
                else
                    cout << round << endl;
                return 0;
            }
        }

        vector< pair<int,int> > next_round;
        for(int i = 0; i < SZ(rounds); i+=2){
            auto [a_1, b_1] = rounds[i];
            auto [a_2, b_2] = rounds[i+1];

            int pass_1 = 0;
            if(a_1 == a || b_1 == a)
                pass_1 = a;
            else if(a_1 == b || b_1 == b)
                pass_1 = b;
            else 
                pass_1 = a_1;

            int pass_2 = 0;
            if(a_2 == a || b_2 == a)
                pass_2 = a;
            else if(a_2 == b || b_2 == b)
                pass_2 = b;
            else
                pass_2 = a_2;

            next_round.push_back({pass_1, pass_2});
        }
        rounds = next_round;
    }

    assert(false);





	return 0;
}

