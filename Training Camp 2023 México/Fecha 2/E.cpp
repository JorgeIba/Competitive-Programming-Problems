#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


string query(int x, int y){
    cout << x << " " << y << endl;
    string color; cin>>color;
    cout.flush();
    return color;
}



int main () {
	//fastIO();
	
    int n; cin>>n;

    const int Y = 10;

    int l = 0, r = 1e9;

    string color_begin = query(l, Y);
    int last_begin = l, last_other = r; 

    for(int i = 0; i < n-1; i++){

        int mid = (l + r) / 2;

        string color = query(mid, Y);

        if(color == color_begin) {
            last_begin = mid;
            l = mid;
        } else {
            last_other = mid;
            r = mid;
        }
    }

    cout << last_begin << " " << 11 << " " << last_other << " " << 9 << endl;



	return 0;
}

