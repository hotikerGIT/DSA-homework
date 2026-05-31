a = 7 - max(map(int, input().split()))
division = 6

if a % 2 == 0:
    a //= 2
    division //= 2

if a % 3 == 0:
    a //= 3
    division //= 3

print(f'{a}/{division}')