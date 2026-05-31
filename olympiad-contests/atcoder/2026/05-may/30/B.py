for i in range(int(input())):
    x1, y1, r1, x2, y2, r2 = map(int, input().split())

    flag1 = (x1 - x2) ** 2 + (y1 - y2) ** 2 > (r1 + r2) ** 2
    flag2 = (x2 - x1) ** 2 + (y2 - y1) ** 2 < (r1 - r2) ** 2

    if flag1 or flag2:
        print("No")

    else:
        print("Yes")