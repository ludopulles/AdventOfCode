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
    return len(a) - len(b)

A = [ [[2]], [[6]] ]

idx, partA = 0, 0
try:
    while True:
        idx += 1
        s1 = eval(input())
        s2 = eval(input())

        if cmp(s1, s2) <= 0:
            partA += idx
        A += [s1, s2]

        input()
except EOFError:
    pass

idx2, idx6 = 0, 0
A = sorted(A, key=cmp_to_key(cmp))

for i in range(len(A)):
    if cmp([[2]], A[i]) == 0:
        idx2 = i + 1
    if cmp([[6]], A[i]) == 0:
        idx6 = i + 1

print("Part A:", partA)
print("Part B:", idx2 * idx6)
