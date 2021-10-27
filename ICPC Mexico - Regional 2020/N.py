
n = int(input())

initial = input().split(".")

cents = int(initial[1]) % 100

#print(cents)

days = 0


for i in range(n):
    money = input().split(".")
    #print(money)
    cents = (cents + int(money[1])) % 100
    if( cents != 0 ):
        days+=1
    
print(days)
