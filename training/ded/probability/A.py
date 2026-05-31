n, k, m = map(int, input().split())

bad = 1
for i in range(min(n, m)):
    bad *= (n - k - i) / (n - i)

print(1 - max(bad, 0))