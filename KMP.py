# Function to calculate the longest proper prefix of pattern[0...i] wich is also a suffix of the substring
def PrefixFunction(pattern, n):
    pi = [0 for i in range(n)]
    for i in range(1, n):
        j = pi[i-1]
        while j > 0 and pattern[i] != pattern[j]:
            j = pi[j-1]
        if pattern[i] == pattern[j]:
            j += 1
        pi[i] = j
    return pi


string_a = input("Insert the whole string ")
pattern = input("Insert the pattern to look ")
n, m = len(string_a), len(pattern)

pi = PrefixFunction(pattern, m)

listAppears = []

j = 0
for i in range(n):
    while j > 0 and string_a[i] != pattern[j]:
        j = pi[j-1]
    if string_a[i] == pattern[j]:
        j += 1
    if(j == m):
        listAppears.append(i-m+1)
        j = pi[j-1]
        

if len(listAppears) != 0:
    print("The index where pattern appears: ")
    for idx in listAppears:
        print(idx, end=" ")
else:
    print("The pattern isn't in the string")

