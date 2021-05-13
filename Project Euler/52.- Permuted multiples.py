
def verify(nums):
    n = len(nums)
    for i in range(1,n):
        if(sorted(str(nums[i-1])) != sorted(str(nums[i]))):
            return False
    return True


maxN = int(1e6)

for x in range(10, maxN):
    if verify([x, 2*x, 3*x, 4*x, 5*x]):
        print(x)
        break