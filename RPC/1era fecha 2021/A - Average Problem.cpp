#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)

using namespace std;

typedef long double ld;
typedef long long int lli;
typedef vector<int> vi;

int main(){
  int t;
  cin >> t;
  while(t--){
    int a, s;
    cin >> a >> s;
    lli tot = 0, sum = 0;
    vector<lli> v(a);
    forn(i, a){
      cin >> v[i];
      tot += v[i];
    }
    forn(i, s){
      sum = 0;
      forn(j, a){
        lli x;
        cin >> x;
        sum += x * v[j];
      }
      //cout << "cal: " <<cal << endl; 
      //cal = 100.0 * cal / sum;
      //cout << "cal: " <<cal << endl; 
      lli cal = (sum / (5 *tot)) * 5;
      lli low = (sum - tot * cal);
      lli high = (tot * (cal + 5) - sum);
      lli ncal;
      if(low <= high)
        ncal = cal;
      else
        ncal = cal + 5;
      if(sum == (ncal * tot)) cout << ncal << " SAME" << endl;
      else if(sum > (ncal * tot)) cout << ncal << " DOWN" << endl;
      else cout << ncal << " UP" << endl;
    }
    cout << endl;
  }
  return 0;
}