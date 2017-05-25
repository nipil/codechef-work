import re

r = re.compile("^(\.*(H\.*T))*\.*$")

n = int(input())
# print("n [%d]" % n)
for i in range(n):
    # print("i [%d]" % i)
    l = int(input())
    # print("l [%d]" % l)
    s = input()
    # print("s [%s]" % s)
    if r.match(s) is None:
        print("Invalid")
    else:
        print("Valid")
