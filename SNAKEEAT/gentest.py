import random
import sys

t = random.randint(1,5)

print(t)

for t_i in range(t):
    n = random.randint(1,10**5)
    q = random.randint(1,10**5)
    print (n, q)

    for t_n in range(n):
        if t_n != 0:
            print(" ", end='')
        print(random.randint(1,10**9), end='')
    print()


    for t_q in range(q):
        # print("t_q", t_q)

        print(random.randint(1,10**9))
