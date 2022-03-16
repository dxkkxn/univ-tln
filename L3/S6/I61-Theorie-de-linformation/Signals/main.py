import random

def print_matrix(matrix): 
    for line in matrix:
        print(line)
    return 

def mult_matrix(H, G):
    """
     matrix multiplication H * G
    """
    lines_h = len(H) 
    cols_h = len(H[0])
    lines_g = len(G) 
    cols_g = len(G[0])
    assert(cols_h == lines_g)

    C = []
    i = 0
    while (i < len(H)):
        j = 0
        l = []
        while (j < len(G[0])):
            k = 0
            res = 0
            while(k < lines_g):
                res ^= H[i][k] * G[k][j]
                k += 1
            l.append(res)
            j += 1
        C.append(l)
        i += 1
    return C

def int_to_bin_lst(num, length):
    l = []
    while num:
        l.append(num&1)
        num >>= 1
    while (len(l) < length):
        l.append(0)

    l.reverse()
    return l
def transpose(matrix):
    res = []
    for i in range(len(matrix[0])):
        new_line = []
        for j in range(len(matrix)):
            new_line.append(matrix[j][i])
        res.append(new_line)
    return res

def decode(encoded_msg, matrix):
    decoded_msg = [0]*len(matrix)
    for i in range(len(matrix[0])):
        nb_one = 0
        found = (None, None)
        for j in range(len(matrix)):
            if (matrix[j][i]) :
                nb_one += 1
                found = (j, i)
            if nb_one > 1:
                break;
        if nb_one == 1: 
            decoded_msg[found[0]] = encoded_msg[0][found[1]]
    
    return decoded_msg
            
def injection(nb_lines, matrix):
    chosen_lines = [-1]*nb_lines
    i = 0
    while i < nb_lines:
        rand = random.randint(0, len(matrix)-1)
        if rand not in chosen_lines:
            chosen_lines[i] = rand
            i+=1

    print(chosen_lines)
    for i in range(len(chosen_lines)):
        print(f"{chosen_lines[i]} : {matrix[chosen_lines[i]]}", end=" -> ")
        matrix[chosen_lines[i]][random.randint(0, len(matrix[0])-1)] = random.randint(0,1)
        print(matrix[chosen_lines[i]])

    return matrix

def main():
#    G = [[1, 0, 0, 0, 1, 1, 1],
#         [0, 1, 0, 0, 1, 0, 1],
#         [0, 0, 1, 0, 1, 1, 0],
#         [0, 0, 0, 1, 0, 1, 1]]
#    
#    H = [[0, 1, 1, 1, 1,   1, 0, 0],
#         [1, 1, 0, 1, 0,   0, 1, 0],
#         [1, 0, 1, 1, 0,   0, 0, 1]]

    
    G = [[1, 1, 0, 1, 0, 0, 0],
         [0, 1, 1, 0, 1, 0, 0],
         [1, 1, 1, 0, 0, 1, 0],
         [1, 0, 1, 0, 0, 0, 1]]

    H = [[1, 0, 0, 1, 0, 1, 1],
         [0, 1, 0, 1, 1, 1, 0],
         [0, 0, 1, 0, 1, 1, 1]]

    A = [[1,0,1], 
         [1,1,1],
         [0,0,1]]

    B = [[1,0,1], 
         [0,1,0],
         [1,0,1]]
    #print_matrix(mult_matrix(A, B))
    #print_matrix(transpose(G))

    # generate all message
    k = 4
    print(int_to_bin_lst(6, 10))
    encoded_matrix = []
    for i in range(2**k):
        bin_num = int_to_bin_lst(i, k)
        encoded = mult_matrix([bin_num], G)
        trans_encoded = transpose(encoded)
        control = mult_matrix(H, trans_encoded)
        decoded = decode(encoded, G)
        print(bin_num, " -> ", encoded, " -> ", control, " -> ", decoded)
        encoded_matrix.append(encoded[0])

    print_matrix(encoded_matrix)
    print("\n")
    
    for msg in (injection(4, encoded_matrix)):
        trans_encoded = transpose([msg])
        control = mult_matrix(H, trans_encoded)
        print(control)




if __name__ == "__main__":
    main()

