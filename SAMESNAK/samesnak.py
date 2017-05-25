import sys

n = int(input())
for i in range(n):

    # print(i + 1, "/", n)

    x11, y11, x12, y12 = map(int, input().split())
    x21, y21, x22, y22 = map(int, input().split())

    # print("A", "\t", "B", "\t", "C", "\t", "D")
    # print(x11, "\t", x12, "\t", x21, "\t", x22)
    # print(y11, "\t", y12, "\t", y21, "\t", y22)

    if x11 == x21 and y11 == y21:
        print("yes")
        # print("AC")
        continue

    if x12 == x22 and y12 == y22:
        print("yes")
        # print("BD")
        continue

    if x11 == x22 and y11 == y22:
        print("yes")
        # print("AD")
        continue

    if x12 == x21 and y12 == y21:
        print("yes")
        # print("BC")
        continue

    # horizontal
    if y11 == y12 and y12 == y21 and y21 == y22:

        if (x21 - x11) * (x21 - x12) <= 0:
            print("yes")
            # print("H A<C<B")
            continue

        if (x22 - x11) * (x22 - x12) <= 0:
            print("yes")
            # print("H A<D<B")
            continue

        if (x11 - x21) * (x11 - x22) <= 0:
            print("yes")
            # print("H C<A<D")
            continue

        if (x12 - x21) * (x12 - x22) <= 0:
            print("yes")
            # print("H C<B<D")
            continue

    # vertical
    if x11 == x12 and x12 == x21 and x21 == x22:

        if (y21 - y11) * (y21 - y12) <= 0:
            print("yes")
            # print("V A<C<B")
            continue

        if (y22 - y11) * (y22 - y12) <= 0:
            print("yes")
            # print("V A<D<B")
            continue

        if (y11 - y21) * (y11 - y22) <= 0:
            print("yes")
            # print("V C<A<D")
            continue

        if (y12 - y21) * (y12 - y22) <= 0:
            print("yes")
            # print("V C<B<D")
            continue

    print("no")
