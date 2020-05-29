#include <bits/stdc++.h>
#define lli long long int

using namespace std; 

int main()
{
  string s, t;
  cin>>s>>t;
  int ss = s.length(), ts = t.length();
  vector< vector<lli> > dp(ss+1, vector<lli>(ts+1));
  //dp[i][j] -> lo mejor que se puede hacer con s de tama;o i y con t de tama;o j

  for(int i = 1; i <= ss; i++)
    for(int j = 1; j<= ts; j++)
    {
      if(s[i-1] == t[j-1]){
        dp[i][j] = dp[i-1][j-1] + 1;
        continue;
      }
      dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    }
  
  lli counter = 0;
  string res;
  lli i = ss, j = ts;
  while(counter < dp[ss][ts])
  {
    if(dp[i][j] == dp[i-1][j])
    {
      i--;
    }
    else if(dp[i][j] == dp[i][j-1])
    {
      j--;
    }
    else
    {
      res.push_back(s[i-1]);
      counter++; i--; j--;
      continue;
    }
  }
  reverse(res.begin(), res.end());
  cout<<res<<endl;
}
