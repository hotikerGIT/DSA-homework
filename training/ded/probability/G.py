from math import comb

n, m, h = map(int, input().split())
s = list(map(int, input().split()))

n -= 1
s[h - 1] -= 1
total = sum(s)

if total < n:
    print(-1)

else:
    print(1 - comb(total - s[h - 1], n) / comb(total, n))