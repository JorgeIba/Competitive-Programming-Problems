


def mult(vec):
    reversed(vec)
    ans = [0 for i in range(2*len(vec) - 1)]

    for i in range(len(vec)):
        for j in range(len(vec)):
            ans[i+j] += vec[i] * vec[j] % 10
            ans[i+j] %= 10
    return ans


def generate(x):
    a = [int(d) for d in str(x)]
    vec = mult(a)
    number = int("".join( map(str, vec)))
    return number



myDict = {}

for x in range(1, 100):
    
    number = generate(x)
    if myDict.get(number):
        myDict[number] += 1
    else:
        myDict[number] = 1


    """
        if(number == 10):
            print(number, x)
        elif(number == 100):
            print(number, x)
        elif number == 1000:
            print(number, x)
        elif number == 10000:
            print(number, x)
        elif number == 100000:
            print(number, x)
    """


for key, value in myDict.items():
    print(key, value)
