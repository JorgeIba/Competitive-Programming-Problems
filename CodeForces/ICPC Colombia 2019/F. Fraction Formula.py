from fractions import *
import sys


def op(frac1, frac2, char):
    if char == "+":
        return frac1 + frac2
    elif char == "-":
        return frac1 - frac2


def main():
    respuestas = ""
    for line in sys.stdin:
        line = "(" + line + ")"
        flagStart = False
        flagEnd = False
        number1, number2, expresion, total = "","","",""
        frac1, frac2, total = Fraction(0), Fraction(0), Fraction(0)

        stack = []

        openBrackets = 0

        for char in line:

            if( char.isnumeric() ):
                if(flagStart == True):
                    number1 += char
                elif(flagEnd == True):
                    number2 += char
                else:
                    flagStart = True
                    number1 += char

            if( char == "/" ):
                flagStart = False
                flagEnd = True

            if( char == "(" or char == "+" or char == "-" or char == ")"):
                if(flagEnd == True):
                    print(stack)
                    last = Fraction(int(number1), int(number2))
                    number1, number2 = "",""
                    flagEnd = False 
                    while( len(stack) > 0 and (stack[-1] == "+" or stack[-1] == "-")):
                        ope = stack[-1]
                        stack.pop()
                        numb = stack[-1]
                        stack.pop()
                        #print(numb, ope, last)
                        last = op(numb, last, ope)
                    while(len(stack) > 0 and stack[-1] == "(" and openBrackets > 0):
                        openBrackets-=1
                        stack.pop()
                    stack.append(last)
                else:
                    if(char == ")"):
                        last = stack[-1]
                        stack.pop()
                        openBrackets += 1
                        while( len(stack) > 0 and (stack[-1] == "+" or stack[-1] == "-")):
                            ope = stack[-1]
                            stack.pop()
                            numb = stack[-1]
                            stack.pop()
                            last = op(numb, last, ope)
                        while(len(stack) > 0 and stack[-1] == "(" and openBrackets > 0):
                            stack.pop()
                        stack.append(last)
                    else:
                        stack.append(char)
        print(stack)
        ans = stack[-1]
        
        respuestas += "{}/{}\n".format(ans.numerator, ans.denominator)
    print(respuestas)

main()