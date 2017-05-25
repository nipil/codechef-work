import sys

tok = sys.stdin.read().split()

t = int(tok.pop(0))
# print("= [%d] samples" % t)
for i in range(t):
    # print("== sample [%d/%d]" % (i + 1, t))

    n = int(tok.pop(0))
    q = int(tok.pop(0))
    # print("N=%d Q=%d" % (n, q))

    s = list(map(int, tok[0:n]))
    # print("snakes' lengths", s)

    tok = tok[n:]
    # print("token remaining", tok)

    for j in range(q):
        # print("=== search [%d/%d]" % (j + 1, q))

        k = int(tok.pop(0))
        # print("target %d" % k)

        l = list(s)
        l.sort(reverse=True)
        # print("lengths", l)

        assert(len(l) == n)

        c = 0

        while len(l) > 0:
            nothing_done = True

            # print("head", l[0], "target", k)

            # remove long enough head
            while len(l) > 0 and l[0] >= k:
                c += 1
                e = l.pop(0)
                # print("removing head=%d, now count=%d len=%d" % (e, c, len(l)))
                nothing_done = False

            # if longest can eat shortest
            if len(l) > 0 and l[0] > l[-1]:
                e = l.pop()
                l[0] += 1
                # print("removed tail, now longest=%d smalest=%d length=%d" % (l[0], l[-1], len(l)))

                nothing_done = False

            if nothing_done:
                # print("finished")
                break

        print(c)

sys.exit(0)
