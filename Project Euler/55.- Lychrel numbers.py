
def is_palindromo(n):
    return str(n) == str(n)[::-1]


limit_iterations = 50
lychrels = []


def is_lychrel(n):
    aux_n = n

    for i in range(limit_iterations):
        n += int(str(n)[::-1])
        if is_palindromo(n):
            return False
        
    lychrels.append(aux_n)
    return True



limit = 10000

for i in range(limit):
    is_lychrel(i)

print(len(lychrels))


