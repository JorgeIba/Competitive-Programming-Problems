import os
from fractions import Fraction as Frac

code = ""
with open(os.path.join(sys.path[0], "my_file.txt"), "r") as f:
    code = f.read().replace("lag", "ans+=1")

print(code)