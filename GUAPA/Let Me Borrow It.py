dp = [1, 1]

for i in range(2, 10005):
    dp.append(dp[i-1] + dp[i-2])


t = int(input())

for q in range(t):
    n = int(input())
    print(dp[n])