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


lli daysInCycle(int today, lli days_left) {

    if(today == 0) {
        if(days_left <= 30) {
            return 30 - days_left;
        } else if(days_left <= 60) {
            return 60 - days_left;
        } else if(days_left <= 91){
            return 91 - days_left;
        } else {
            return daysInCycle(today, days_left % 91);
        }
    } else if(today == 2) {
        if(days_left <= 30) {
            return 30 - days_left;
        } else if( days_left <= 61) {
            return 61 - days_left;
        } else if(days_left <= 91) {
            return 91 - days_left;
        } else {
            return daysInCycle(today, days_left % 91);
        }
    } else {
        if(days_left <= 31) {
            return 31 - days_left;
        } else if(days_left <= 61) {
            return 61 - days_left;
        } else if(days_left <= 91) {
            return 91 - days_left;
        } else {
            return daysInCycle(today, days_left % 91);
        }
    }
}

lli daysNoCycle(int today, lli days_left) {
    if(today == 1) {
        if(days_left <= 30) {
            return 30 - days_left;
        } else if(days_left <= 62) {
            return 62 - days_left;
        } else {
            return daysInCycle(0, days_left - 62 );
        }
    } else {
        if(days_left <= 32) {
            return 32 - days_left;
        } else {
            return daysInCycle(0, days_left - 32 );
        }
    }

}



int main () {
	//fastIO();

    map<string, int> which_day;
    which_day["Mon"] = 0;
    which_day["Tue"] = 1;
    which_day["Wed"] = 2;
    which_day["Thu"] = 3;
    which_day["Fri"] = 4;
    which_day["Sat"] = 5;
    which_day["Sun"] = 6;


    string day;
    int n; cin>>day>>n;
    int today = which_day[day];

    vector<lli> days(n);
    for(auto &x: days) cin>>x;


    lli ansT = 1e18;
    for(auto d: days) {
        lli day_was = (today - d) % 7;
        if(day_was < 0) day_was += 7;

        
        // good one
        if(day_was % 2 == 0) {
            ansT = min(ansT, daysInCycle(day_was, d));
        } else {
            ansT = min(ansT, daysNoCycle(day_was, d));
        }
    }

    cout << ansT << endl;

	return 0;
}

