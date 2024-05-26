
                for(int k = limit_l; k <= min(q, limit_r); k++) {
                    dp[i][q*d] += dp[i-1][d * (q-k)] % MOD;
                    if(dp[i][q*d] >= MOD) dp[i][q*d] -= MOD;
                }