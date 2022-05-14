import math
INF = 1e18

def canReach(v, d):
    return v*v - 2*d >= 0

def time_reach(boost, positions):
    v_curr = boost
    x_curr = 0
    new_pos = positions[1:]

    total_time = 0

    for pos in new_pos:
        d = pos - x_curr
        if not canReach(v_curr, d):
            return INF
        
        discr = v_curr*v_curr - 2*d
        time_1 = v_curr - math.sqrt(discr)

        x_curr = pos
        v_curr = (v_curr - time_1) + boost
        total_time += time_1
    
    
    return total_time 

L, n, limit = map(int, input().split())
positions = list(map(int, input().split()))
positions.append(L)


l, r, ans = 0, 2*L, 2*L

for i in range( 1000 ):
    mid = (l+r)/2;
    time = time_reach(mid, positions)
    if(time < limit):
        ans = mid
        r = mid
    else:
        l = mid

# print(round(ans, 20))

print( "{:.20f}".format(round(ans, 20))  )