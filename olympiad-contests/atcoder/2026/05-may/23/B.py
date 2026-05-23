n = int(input())
s = list(input().split())

dct = {
    'abc': 2,
    'def': 3,
    'ghi': 4,
    'jkl': 5,
    'mno': 6,
    'pqrs': 7,
    'tuv': 8,
    'wxyz': 9,
}

ans = ""
for string in s:
    for (key, val) in dct.items():
        if string[0] in key:
            ans += str(val)
            break

print(ans)