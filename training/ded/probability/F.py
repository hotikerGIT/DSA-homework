m, n = map(int, input().split())
ans = 0

for i in range(1, m + 1):
    ans += i * (pow(i / m, n) - pow((i - 1) / m, n))

print(ans)