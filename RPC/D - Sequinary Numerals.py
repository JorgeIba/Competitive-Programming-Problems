from audioop import reverse
from fractions import Fraction as F

s = input()

s = s[::-1]

base = F(3, 2)

ans = 0
for i in range(len(s)):
    digit = int(s[i])
    ans += digit * (base ** i)

if(ans == int(ans)):
    print(ans)
else:
    ent = int(ans)
    print(ent, ans-ent)




