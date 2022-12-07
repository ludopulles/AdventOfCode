print(next(min([i for i in range(4, len(A)) if len(set(A[i-4:i])) == 4]) for A in [input()]))
