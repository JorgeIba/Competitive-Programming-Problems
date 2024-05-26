import os, io
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

a = input().decode().rstrip("\r\n")
b = input().decode().rstrip("\r\n")

a_num = int(a)
b_num = int(b)


if a_num < b_num:
    a, b = b, a
    a_num, b_num = b_num, a_num

a = a[::-1]
b = b[::-1]

while len(b) < len(a):
    b += '0'

power = 0
aux = -1
aux2 = -1
carry = 0
for i in range(min(len(a), len(b))):
    sum = ord(a[i]) + ord(b[i]) - 2*ord('0') + carry
    if sum > 9:
        carry = 1
        power = i + 1
        if i + 1 < len(a):
            aux = ord(a[i + 1]) - ord('0') + 1
            aux2 = ord(b[i + 1]) - ord('0') + 1
        else:
            aux = 1
            aux2 = 1
    else:
        carry = 0

if aux == -1:
    print(0)
else:
    c1 = str(aux)
    c2 = str(aux2)
    for i in range(power + 1, len(a)):
        c1 += a[i]
        c2 += b[i]
        # c1 += (ord(a[i]) - ord('0')) * 10 ** (i - power)
        # c2 += (ord(b[i]) - ord('0')) * 10 ** (i - power)
    c1 = c1[::-1]
    c2 = c2[::-1]
    for i in range(power):
        c1 += '0'
        c2 += '0'
    c1 = int(c1)
    c2 = int(c2)
    # print('aux', aux)
    # print('aux2', aux2)
    # print('power', power)
    # print('c1', c1)
    # print('c2', c2)

    print(min(c1 - a_num, c2 - b_num))
