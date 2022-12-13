from functools import cmp_to_key

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

A = [  [[2]], [[6]]  ]

try:
    while True:
        s1 = eval(input())
        s2 = eval(input())
        A.append(s1)
        A.append(s2)

        input()
except EOFError:
    print("DONE READING INPUT")

A = sorted(A, key=cmp_to_key(cmp))
for x in A:
    print(x)

idx2 = -1
idx6 = -1
for i in range(len(A)):
    if cmp([[2]], A[i]) == 0:
        idx2 = i + 1
    if cmp([[6]], A[i]) == 0:
        idx6 = i + 1

print(idx2, idx6, idx2 * idx6)
