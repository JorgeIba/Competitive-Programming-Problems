import math
import re


t = int(input())

def convert_under(match):
    if(match.group(1) and match.group(2)):
        return "<i>{}</i>".format(match.group(0)[1:-1])
        
def convert_bold(match):
    if(match.group(1) and match.group(2)):
        return "<b>{}</b>".format(match.group(0)[1:-1])



for test in range(t):
    s = input()

    ss = re.sub(r"(_).*?(_)", convert_under, s)

    ss = re.sub(r"(\*).*?(\*)", convert_bold, ss)

    print(ss)