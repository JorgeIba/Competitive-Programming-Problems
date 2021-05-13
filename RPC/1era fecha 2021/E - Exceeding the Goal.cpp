#include<bits/stdc++.h>
#define lli __int128
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t;
  long long k, s, g;
  cin >> t;
  while(t--){
    cin >> k >> s >> g;
    lli G = g, S = s, K = k;
    lli l = 0, r = 1e6;
    lli sum = -1;
    while(l <= r){
      lli mid = (l+r)/2;
      lli part1 = (mid+1)*S;
      lli part2 = (lli) (mid*(mid+1) / 2);
      part2 *= K;
      if( part2 > G - part1){
        r = mid - 1;
        sum = mid;
      }
      else l = mid + 1;
    }
    //cout << ((sum*(sum+1))/2)*K + S << '\n';
    cout << (long long int)sum+1 << '\n';
  }
  return 0;
}