alphabet = []
for i in range(26):
    alphabet.append(chr(97+i))

def print_state_hex(state) :
    print("____________")
    for i in range(4):
        for j in range(4):
            print(f"{hex(state[i][j])[2:]}|", end='')
        print()
    print("____________")

def transformation_in_blocks(msg) :
    state = []
    for i in range(len(msg)//4):
        sub_block = []
        for j in range(4):
            sub_block.append(ord(msg[i*4+j]))
        state.append(sub_block)
    return state

def add_round_key(state, key):
    print_state_hex(state)
    for i in range(4):
        for j in range(4):
            state[i][j] = state[i][j] ^ key[i][j]
    print_state_hex(state)
    return 0;

def gencirculante(L):
    M = []
    for i in range(len(L)):
        #ligne = copy.copy(ligne)
        ligne = L[len(L)-i:] + L[:len(L)-i]
        M.append(ligne)
    return M

def multbyalpha(b, f):
  t = b << 1
  n = len(bin(f)) - 3
  if t & (1<<n) != 0:
    return t^f
  else:
    return t

def multiplie(b, c, f):
  res = 0
  t = b
  k = c
  while t != 0:
    if (t & 1) != 0:
      res ^= k
    k = multbyalpha(k,f)
    t = t >> 1
  return res

def matmat_f(A,B,P):
  C = []
  for i in range(len(A)):
    L = []
    for j in range(len(B[0])):
      res = 0
      for k in range(len(B)):
        res ^= multiplie(A[i][k],B[k][j],P)
      L.append(res)
    C.append(L)
  return C

def sub_bytes(state, key):
    matrix_cte = gencirculante([1,0,0,0,1,1,1,1])
    vect_cte = [1,1,0,0,0,1,1,0]
    P = 283
    for i in range(4):
        for j in range(4):
            matmat_f(matrix_cte, state[i][j]

def aes(msg, key):
    states = transformation_in_blocks(msg)
    for i in range(len(states)):
        add_round_key(states[i], key)
        for j in range(9):
            sub_bytes(states[i])
            shift_rows(states[i])
            mix_columns(states[i])
            add_round_key(states[i])
        sub_bytes(states[i])
        shift_rows(states[i])
        add_round_key(states[i])


if __name__ == '__main__' :
    text = "Two One Nine Two"
    key = "Thats my Kung Fu"
    text = transformation_in_blocks(text)
    key = transformation_in_blocks(key)
    add_round_key(text, key)

