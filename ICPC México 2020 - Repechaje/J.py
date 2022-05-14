import math
import fractions

t = int(input())

def mini(A,B):
  gcd = math.gcd(A,B)

  A//=gcd
  B//=gcd

  return A, B


def lcm(A, B):
  return (A * B) // math.gcd(A,B)

def lcm_fractions(F1, F2):
  lcm1 = lcm(F1.denominator, F2.denominator)
  F1 = F1 * (lcm1 // F1.denominator)
  F2 = F2 * (lcm1 // F2.denominator)
  return fractions.Fraction(lcm(F1.numerator, F2.numerator), lcm1)


def get_valid_turn(n, m):
  F1 = fractions.Fraction(360, n)
  F2 = fractions.Fraction(360, m)

  ans = lcm_fractions(F1, F2)
  ans = lcm_fractions(ans, fractions.Fraction(30, 1))

  assert(ans.denominator == 1)

  return ans
  

for test in range(t):
  C, F, B, S = map(int, input().split())
  valid_turn = get_valid_turn(F, B)


  at_least = 0
  if S*360 % C*valid_turn == 0:
    at_least = int(S*360) // int(C*valid_turn)
  else:
    at_least = (int(S*360) // int(C*valid_turn)) + 1

  #print(at_least)

  total_turn = valid_turn // 30
  print(at_least*total_turn)