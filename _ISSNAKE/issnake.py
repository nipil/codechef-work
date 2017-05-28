
def issnake(width, plate, cells, snake, snake_index, cur_x, cur_y):
    # print("-" * (snake_index + 1))

    # print("width", width)

    # print("cur")
    # i = -1
    # for s in plate:
    #     i += 1
    #     print(i, s)

    # print("snake", snake_index, snake)
    # print("cur", cur_x, cur_y)

    # set current step as "viewed"
    plate[cur_y][cur_x] = '*'
    snake[snake_index] = (cur_x, cur_y)
    snake_index += 1

    # print("next")
    # i = -1
    # for s in plate:
    #     i += 1
    #     print(i, s)
    # print("snake", snake_index, snake)

    # test goto-top
    if cur_y > 0 and plate[cur_y - 1][cur_x] == '#':
        # print("top")
        res = issnake(width, plate, cells, snake,
                      snake_index, cur_x, cur_y - 1)
        if res:
            return True

    # test bottom
    if cur_y < 1 and plate[cur_y + 1][cur_x] == '#':
        # print("bottom")
        res = issnake(width, plate, cells, snake,
                      snake_index, cur_x, cur_y + 1)
        if res:
            return True

    # test left
    if cur_x > 0 and plate[cur_y][cur_x - 1] == '#':
        # print("left")
        res = issnake(width, plate, cells, snake,
                      snake_index, cur_x - 1, cur_y)
        if res:
            return True

    # test right
    if cur_x < width - 1 and plate[cur_y][cur_x + 1] == '#':
        # print("right")
        res = issnake(width, plate, cells, snake,
                      snake_index, cur_x + 1, cur_y)
        if res:
            return True

    # nothing matches
    # print("nothing")

    if snake_index == cells:
        # print("good length !!")
        return True

    # reset current step as "unviewed"
    snake_index -= 1
    snake[snake_index] = None
    plate[cur_y][cur_x] = '#'

    # print("snake back", snake_index, snake)

    return False


def solve(width, plate):
    # print("n", width)

    # i = -1
    # for s in plate:
    #     i += 1
    #     print(i, s)

    # find start
    sx = None
    sy = None
    double = False
    i = -1
    while i < n:
        i += 1
        if i >= n:
            break
        # manage full present
        if plate[0][i] == '#' and plate[1][i] == '#':
            double = True
            # print("full")
            continue
        # manage full absent
        if plate[0][i] == '.' and plate[1][i] == '.':
            # search on
            if double:
                # print("empty-after-double")
                print("yes")
                return
            else:
                # print("empty")
                continue
        # manage single
        # print("single")
        sx = i
        if plate[0][i] == '#':
            sy = 0
        else:
            sy = 1

        # clear previous as it is indeed valid (rect)
        for j in range(i):
            plate[0][j] = '.'
            plate[1][j] = '.'

        break

    # manage end of loop
    # print("maxloop")
    if i == n:
        if double:
            print("yes")
        else:
            print("no")
        return

    # print("n", width)
    # i = -1
    # for s in plate:
    #     i += 1
    #     print(i, s)

    # count snake cells
    cells = 0
    for i in range(width):
        if plate[0][i] == '#':
            cells += 1
        if plate[1][i] == '#':
            cells += 1
    # print("cells", cells)

    # study snake from given point
    # print("start", sx, sy)

    snake = [None] * (2 * width)

    # print(snake)
    result = issnake(width, plate, cells, snake, 0, sx, sy)
    # print("result", result)
    if result:
        print("yes")
    else:
        print("no")


T = int(input())
assert(T >= 1)
assert(T <= 500)

# print("T [%d]" % T)
for i in range(T):
    # print("==== i [%d/%d]" % (i + 1, T))

    n = int(input())
    assert(n >= 1)
    assert(n <= 500)

    top = list(input())
    # print(top)

    bottom = list(input())
    # print(bottom)

    plate = [top, bottom]
    # print(plate)
    assert(len(plate) == 2)
    assert(len(plate[0]) == n)
    assert(len(plate[1]) == n)

    solve(n, plate)
