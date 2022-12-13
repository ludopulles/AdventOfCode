def cmp(a, b):
    if type(a) is int and type(b) is int:
        return a - b

    if type(a) is int:
        a = [a]
    if type(b) is int:
        b = [b]

    # a, b are lists
    for i in range(min(len(a), len(b))):
        res = cmp(a[i], b[i])
        if res != 0:
            return res

    if len(a) < len(b):
        return -1
    if len(a) == len(b):    
        return 0
    if len(a) > len(b):
        return +1

    exit("WHAT")

idx = 0
ans = 0
while True:
    idx += 1

    s1 = eval(input())
    s2 = eval(input())

    if cmp(s1, s2) <= 0:
        ans += idx
        print(idx, "=>", ans)

    input()
