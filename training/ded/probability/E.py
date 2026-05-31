from math import comb

s1 = input()
s2 = input()

wanted = sum(1 if c == '+' else -1 for c in s1)
got = sum(1 if c == '+' else -1 if c == '-' else 0 for c in s2)
n = sum(c == '?' for c in s2)
diff = wanted - got

if abs(diff) <= n:
    print(comb(n, abs(n - diff) // 2) / (1 << n))

else:
    print(0)