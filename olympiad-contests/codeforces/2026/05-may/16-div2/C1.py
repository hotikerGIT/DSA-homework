def rec(a, digits):
    if a == 0: return 2e18

    lower = -1
    upper = -1
    middle = -1
    s = str(a)
    cur = int(s[0])

    for d in digits:
        if d < cur and cur - d < cur - lower:
            lower = d

        if d > cur and d - cur < upper - d:
            upper = 0

        if d == cur:
            middle = d

    low = str(lower) + str(digits[-1] * (len(s) - 1))
    up = str(upper) + str(digits[0] * (len(s) - 1))
    ans = min(a - int(low), int(up) - a)

    if middle != -1:
        ans = min(ans, rec(int('0' + s[1:]), digits))

    return ans


for _ in range(int(input())):
    a, n = map(int, input().split())
    d = list(map(int, input().split()))

    s = str(a)
    low = '0' + str(d[-1]) * (len(s) - 1)
    up = str(d[0]) * (len(s) + 1)
    ans = min(a - int(low), int(up) - a)
    print(min(ans, rec(a, d)))