#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


lli next(lli a, lli b, lli c, lli d, lli m, lli X) {
    return (a*X*X*X + b*X*X + c*X + d) % m;
}

string generate_sequence(lli a, lli b, lli c, lli d, lli m, lli X1) {
    string ans;
    for(int i = 0; i < 15; i++) {
        ans += (X1+'0');
            
        X1 = next(a, b, c, d, m, X1);
    }
    return ans;
}


string s;

void solve(VLL nextn) {


    
    lli m = 5;

    map< array<lli, 4>, pair<lli,lli> > values;
    for(int c = 0; c <= 4; c++) {
        for(int d = 0; d <= 4; d++) {
            lli value_1 = (1*c + 1*d) % m;

            lli value_2 = (2*c + 1*d) % m;

            lli value_3 = (3*c + 1*d) % m;

            lli value_4 = (4*c + 1*d) % m;
            values[{value_1, value_2, value_3, value_4}] = {c, d};
        }
    }


    bool flag_break = false;
    for(int a = 0; a <= 4 && !flag_break; a++) {
        for(int b = 0; b <= 4; b++) {
            lli value_1 = (1*a + 1*b) % m;
            lli need_1 = (nextn[1] - value_1 + m) % m;
            

            lli value_2 = (8*a + 4*b) % m;
            lli need_2 = (nextn[2] - value_2 + m) % m;


            lli value_3 = (27*a + 9*b) % m;
            lli need_3 = (nextn[3] - value_3 + m) % m;


            lli value_4 = (64*a + 16*b) % m;
            lli need_4 = (nextn[4] - value_4 + m) % m;

            if(values.count({need_1, need_2, need_3, need_4})){
                auto [c, d] = values[{need_1, need_2, need_3, need_4}];
                // cout << a << " " << b << " " << c << " " << d << endl;

                for(int start = 1; start <= 4; start++) {
                    auto ans = generate_sequence(a, b, c, d, m, start);
                    // cout << ans << " " << s << endl;
                    bool is_ans = true;
                    for(int i = 0; i < (int)s.length(); i++) {
                        if(s[i] != '?' && s[i] != ans[i]) {
                            is_ans = false;
                            break;
                        }
                    }
                    if(is_ans) {
                        cout << a << " " << b << " " << c << " " << d << " " << m << " " << start << endl;
                        exit(0);
                    }
                }
            }
        }
    }

}




int main () {
	//fastIO();

    cin>>s;
    
    int n = s.length();

    vector<lli> nextn(5);
    
    for(int i = 0; i < n-1; i++){
        if(s[i] != '?' && s[i+1] != '?') {
            nextn[ s[i]-'0' ] = s[i+1] - '0';
        }
    }


    for(int a = 1, flag1 = false; a <= 4 && !flag1; a++) {
        if(nextn[1] != 0) {
            a = nextn[1];
            flag1 = true;
        }

        for(int b = 1, flag2 = false; b <= 4 && !flag2; b++) {
            if(nextn[2] != 0) {
                b = nextn[2];
                flag2 = true;
            }


            for(int c = 1, flag3 = false; c <= 4 && !flag3; c++){
                if(nextn[3] != 0) {
                    c = nextn[3];
                    flag3 = true;
                }

                for(int d = 1, flag4 = false; d <= 4 && !flag4; d++){
                    if(nextn[4] != 0) {
                        d = nextn[4];
                        flag4 = true;
                    }

                    solve({0, a, b, c, d});

                }
            }
        }
    }

    cout << "-1 -1 -1 -1 -1 -1" << endl;

    

    



	return 0;
}

