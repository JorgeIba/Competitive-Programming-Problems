import math
string = ""

for i in range(1, 100000):
    string+=str(i)
    if(len(string) >= 100000):
        print("smn")
        break
#print(int(string[0])* int(string[9])* int(string[99]) * int(string[999]) * int(string[9999]) * int(string[99999]) * int(string[999999]))