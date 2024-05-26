import math
import decimal

decimal.getcontext().prec = 100



def f(A, B, time):
	sq = decimal.Decimal(1+time).sqrt()

	return decimal.Decimal(B*time) + A/sq

A, B = map(int, input().split())


analyt = A / (2*B)

analyt = analyt**(2/3) - 1




if analyt < 0:
	print("%.15f" % f(A, B, 0))
else:
	ans_1 = int(math.floor(analyt))
	ans_2 = int(math.ceil(analyt))
	

#	print(analyt, ans_1, ans_2)
	
	ans = min(f(A, B, ans_1), f(A, B, ans_2))
	
	print("%.15f" % ans)

