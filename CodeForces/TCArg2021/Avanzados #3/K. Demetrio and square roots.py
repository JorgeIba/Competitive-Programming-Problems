import decimal

n, k = map(int, input().split())

n = decimal.Decimal(n)

ans_v = str(n.sqrt(decimal.Context( k + 11 ))).split('.')

ans_decimal = 0

if len(ans_v) > 1:
    ans_decimal = ans_v[1][0:k]
else:
    ans_decimal = "".join([str(0) for i in range(k)])

#print(n.sqrt(decimal.Context(k+10)))
print(ans_v[0] + '.' + ans_decimal)




