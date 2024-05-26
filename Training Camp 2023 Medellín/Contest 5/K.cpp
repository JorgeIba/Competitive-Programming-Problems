#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
 
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
using namespace __gnu_pbds;

inline vector< string > separate_line(string line) {
    stringstream ss(line);
    string word;
    vector< string > words;
    while(getline(ss, word, ' ')) {
        words.push_back(word);
    }

    return words;
}



const string ANS = "aaaaaaaaaaa";
int main () {
	fastIO();
    
    int n, m; cin>>n>>m;

    cin.ignore();

    vector< vector< string > > lines;
    forn(i, n){
        string line; getline(cin, line);
        lines.push_back(separate_line(line));
    }


    auto get_ans = [&](int bit, int poss){
        cc_hash_table<string, int, hash<string>> variables;
        variables[ANS] = poss;

        forn(i, n){
            auto name_v = lines[i][0];

            if(SZ(lines[i]) == 3) {
                variables[ name_v  ] = lines[i][2][bit] - '0';
                continue;
            } 

            assert(SZ(lines[i]) == 5);
            if(lines[i][2] == "?") lines[i][2] = ANS;
            if(lines[i][4] == "?") lines[i][4] = ANS;

            auto l = lines[i][2];
            auto r = lines[i][4];
            auto l_bit = variables[l];
            auto r_bit = variables[r];

            auto op = lines[i][3];
            if(op == "AND"){
                variables[name_v] = l_bit and r_bit;
            } else if(op == "OR"){
                variables[name_v] = l_bit or r_bit;
            } else {
                assert(op == "XOR");
                variables[name_v] = l_bit xor r_bit;
            }
        }

        int yes = 0, no = 0;
        for(auto [s, bit]: variables){
            if(s == ANS) continue;
            if(bit) yes++;
            else no++;
        }
        return pair<int,int>{yes, no};
    };


    string maximum(m, '0'), minimum(m, '0');
    for(int i = 0; i < m; i++) {
        auto [yes_1, no_1] = get_ans(i, 1);
        auto [yes_0, no_0] = get_ans(i, 0);

        if(yes_1 > yes_0) {
            maximum[i] = '1';
        } else {
            maximum[i] = '0';
        }

        if(no_1 > no_0){
            minimum[i] = '1';
        } else {
            minimum[i] = '0';
        }
    }

    cout << minimum << endl << maximum << endl;



	return 0;
}

