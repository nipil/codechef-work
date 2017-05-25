n = int(input())
# print("= [%d] samples" % n)
for i in range(n):
    # print("== sample [%d/%d]" % (i + 1, n))

    l = int(input())
    # print("length [%d]" % l)

    h = 1 + (l >> 1)
    # print("half+1 [%d]" % h)

    s = input()
    # print("strips [%s]" % s)

    a = map(int, s.split())

    if l % 2 == 0:
        print("no")  # length
        continue

    x = 1
    t = 0

    valid = True
    for v in a:

        # print(x, v)

        if x == 1 and v != 1:

            valid = False  # first
            break

        if x <= h:
            t += 1
        else:
            t -= 1

        # print("x [%d] v[%d] t[%d]" % (x, v, t))

        if t != v:
            valid = False  # different
            break

        x += 1

    if valid:
        print("yes")
    else:
        print("no")
