from itertools import permutations

permutations = ["".join(p) for p in (permutations("0123456789"))]

primes = [2, 3, 5, 7, 11, 13, 17]


total_special = []
for p in permutations:
    is_special = 0
    for i in range(1, 7+1):
        is_special += int(p[i: i+3]) % primes[i-1]

    if is_special == 0:
        total_special.append(int(p))

print(sum(total_special), total_special)

