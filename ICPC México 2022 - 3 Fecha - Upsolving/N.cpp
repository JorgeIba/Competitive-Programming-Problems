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


int main () {
	//fastIO();

    lli n; cin>>n;

    vector<lli> A(2*n), B(2*n);

    for(int i = 0; i < n; i++) {
        cin>>A[i];
        A[n+i] = A[i];
    }

    for(int i = 0; i < n; i++) {
        cin>>B[i];
        B[n+i] = B[i];
    }

    lli k, l; cin>>k>>l;

    lli sum = 0;
    multiset<lli> bestL, others;
    auto insert_e = [&](lli x) {
        if(SZ(bestL) < l) {
            bestL.insert(x);
            sum += x;
            return;
        }

        lli low = *bestL.begin();
        if(low < x) {
            bestL.erase(bestL.begin());
            sum -= low;
            bestL.insert(x);
            sum += x;


            others.insert(low);
        } else {
            others.insert(x);
        }
    };

    auto pop_e = [&](lli x) {
        if(others.find(x) != others.end()) {
            others.erase(others.find(x));
        } else {
            bestL.erase(bestL.find(x));
            sum -= x;
            if(SZ(others) > 0) {
                lli greater = *others.rbegin();
                others.erase(others.find(greater));

                bestL.insert(greater);
                sum += greater;
            }
        }
    };

    for(int i = n; i < n+k; i++) {
        insert_e(B[i]);
    }

    vector<lli> prefixA = A;
    partial_sum(all(prefixA), begin(prefixA));
    auto getSum = [&](lli l, lli r) {
        return prefixA[r] - (l > 0 ? prefixA[l-1] : 0);
    };


    lli ans = getSum(n, n+k-1) + sum;
    for(int r = n-1, l = n+k-1; r >= n-k; r--, l--) {
        insert_e(B[r]);
        pop_e(B[l]);
    
        ans = max(ans, getSum(r, r+k-1) + sum);
    }

    cout << ans << endl;


	return 0;
}

