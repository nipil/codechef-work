
T = int(input())
# assert(T >= 1)
# assert(T <= 100)

# print("T [%d]" % T)
for i in range(T):
    # print("i [%d/%d]" % (i + 1, T))

    n, m = list(map(int, input().split()))
    # assert(n >= 2)
    # assert(n <= 100)

    # assert(m >= 1)
    # assert(m <= (n >> 1))

    # print("n [%d] m[%d]" % (n, m))

    for j in range(m):
        u, v = list(map(int, input().split()))
        # assert(u >= 1)
        # assert(u <= n)
        # assert(v >= 1)
        # assert(v <= n)

    if n % 2 == 0:
        print("yes")
    else:
        print("no")
