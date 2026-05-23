s = "HelloWorld"
n = int(input())

res = ""
for i in range(10):
    if i == n - 1: continue
    res += s[i]

print(res)