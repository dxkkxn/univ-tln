def print_matrice(M):
  for i in range(len(M)):
    print(M[i])
  print("\n")


def det(A):
    all_pivot = 1
    for i in range(len(A)):
        pivot = A[i][i]

        for j in range(i+1, len(A)):
            all_pivot *= pivot
            pivot2 = A[j][i]
            A[j][i] = pivot * pivot2 - pivot2 *  pivot
            print(pivot, pivot2,A[j][i])
            for  k in range(i+1, len(A)):

                A[j][k] = pivot * A[j][k] - pivot2 * A[i][k]
                print(pivot, pivot2,A[j][k])
            print_matrice(A)
    det = 1
    for i in range(len(A)):
        det *= A[i][i]

    if all_pivot == 0:
        return 0
    return det/all_pivot
# A = [[1, 1.5, 2], [2, 3, -5], [3, 4, 5]]
# print(det(A))
# print_matrice([[4, 4, 4], [2, 4, 4], [4, 8, 10]])
# # print(det([[6, 0, 3, 0], [4, 0, 2, 0], [4, 2, 9, 3], [2, 0, 5, 11]]))
# print(
#          det([[3, 0, 1, 3], [0, 2, 0, 3], [3, 6, 2, 14], [0, 0, 0, 6]]),
#          det([[4, 4, 4], [2, 4, 4], [4, 8, 10]]),
#          det([[6, 0, 3, 0], [4, 0, 2, 0], [4, 2, 9, 3], [2, 0, 5, 11]]),
#          det([[24, 30, 6], [8, 25, 5], [8, 25, 17]]),
#          det([[2, 0, 2, 0], [2, 1, 2, 1], [0, 0, 2, 0], [0, 1, 1, 3]]),
#          det([[3, 3, 0], [9, 9, 0], [9, 18, 13]]),
#          det([[3, 2, 1, 0], [3, 5, 4, 6], [6, 7, 6, 8], [0, 0, 0, 6]]),
#          det([[3, 0, 15, 18], [6, 6, 32, 39], [0, 24, 10, 12], [3, 18, 24, 51]]),
#          det([[8, 8, 0], [4, 4, 0], [2, 2, 2]]),
#          det([[20, 5, 10], [20, 35, 46], [4, 1, 26]]) )
def gaus(A):
    diag = min(len(A),len(A[0]))
    print(diag)
    for i in range(diag):
        pivot = A[i][i]
        i_piv = i
        while pivot == 0 :
            pivot = A[i_piv][i]

        for j in range(i+1, len(A)):
            pivot2 = A[j][i]
            A[j][i] = pivot * pivot2 - pivot2 *  pivot
            print(pivot, pivot2,A[j][i])
            for  k in range(i+1, len(A[0])):

                A[j][k] = pivot * A[j][k] - pivot2 * A[i][k]
                print(pivot, pivot2,A[j][k])
            print_matrice(A)

    return A

# print_matrice([[6, 0, 6], [3, 0, 3], [0, 6, 4], [0, 3, 2], [6, 4, 2], [3, 2, 1]])
# print_matrice([[6, 0, 6], [0, 36, 24], [0, 0, -1440], [0, 0, 0], [0, 0, 0], [0, 0, 0]])
print(gaus([[6, 0, 6], [3, 0, 3], [0, 6, 4], [0, 3, 2], [6, 4, 2], [3, 2, 1]]))
