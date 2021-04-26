import random, time, copy
def min_max (L):
    min_val = L[0]
    max_val = L[0]
    for i in range(len(L)):
        if (L[i] < min_val):
            min_val = L[i]
        elif (L[i] > max_val):
            max_val = L[i]
    return min_val,max_val


def histogramme (L, min_val, max_val):
    H = [0]*(max_val-min_val+1)
    for i in range(len(L)):
        H[L[i]-min_val]+= 1
    return H

def counting_sort(L):
    min_val, max_val = min_max(L)
    k = 0
    H = histogramme(L, min_val, max_val);
    for i in range(len(H)):
        for j in range(H[i]):
            L[k] = (i + min_val)
            k+=1
    return L

def gen_l(n,l):
    L = []
    for i in range(n):
        L.append(random.randrange(0,l))
    return L

L = gen_l(8000, 10)
L_ = copy.copy(L)
start_time_cs = time.time()
counting_sort(L)
print(f"counting sort last {time.time() - start_time_cs}")
start_time_bs = time.time()
L_.sort()
print(f"builtin sort last {time.time() - start_time_bs}")
print(L == L_)
