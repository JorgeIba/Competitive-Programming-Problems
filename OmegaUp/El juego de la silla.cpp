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

template<class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool flag = 0;
    while (!isdigit(c)) {
        if (c == '-')
            flag = 1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x = flag ? -x : x;
}
 
template<class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}


int main () {
	//fastIO();
    int n; read(n);
    vector<int> nums(n);
    for(auto &x: nums) read(x);

    sort(all(nums));


    int q; read(q);
    while(q--)
    {
        int test; read(test);

        auto itr_lower = lower_bound(all(nums), test);
        auto itr_upper = upper_bound(all(nums), test);
    
        if(*itr_lower == test){
            cout << 0 << endl;
            continue;
        }

        if(itr_upper == nums.end()) itr_upper--;
        if(itr_lower == nums.begin()) itr_lower++;

        int lower = *(--itr_lower), upper = *itr_upper;

        //cerr << lower << " " << test << " " << upper << endl;
        

        int minimum = min(abs(lower - test), abs(upper - test));
        
        write(minimum);
        printf("\n");
        //cout << minimum << endl;
    }
    
	return 0;
}