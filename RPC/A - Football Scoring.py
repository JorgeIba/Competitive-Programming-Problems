
score1, score2 = 0, 0

T, F, S, P, C = map(int, input().split())
score1 = 6*T + 3*F + 2*S + 1*P + 2*C


T, F, S, P, C = map(int, input().split())
score2 = 6*T + 3*F + 2*S + 1*P + 2*C


print(score1, score2)