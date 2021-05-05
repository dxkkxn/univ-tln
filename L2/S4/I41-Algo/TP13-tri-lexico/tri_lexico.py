import string, random, copy, time
alphabet = []
for i in range(26):
    alphabet.append(chr(97+i))

def min_max_len(word_list):
    min_word = len(word_list[0])
    max_word = len(word_list[0])
    for word in word_list:
        if len(word) > max_word:
            max_word = len(word)
        if len(word) < min_word:
            min_word = len(word)
    return (min_word,max_word)

def partition(word_list, min_len, max_len):
    H = []
    for i in range(max_len+1):
        H.append([])
    for i in range(len(word_list)):
        curr_word = word_list.pop(0);
        index = len(curr_word)
        H[index].append(curr_word)
    return H

def tri_repartition(word_list, length):
    H = []
    for i in range(26):
        H.append([])
    for i in range(len(word_list)):
        curr_word = word_list.pop(0)
        index = alphabet.index(curr_word[length-1])
        H[index].append(curr_word)
    for i in range(len(H)):
        word_list.extend(H[i])
    return word_list

def tri_lexico(word_list):
    min_len, max_len = min_max_len(word_list)
    P = partition(word_list, min_len, max_len)
    for i in range(max_len, 0, -1):
        word_list[0:0] = (P[i])
        tri_repartition(word_list, i)
    return word_list

def gen_liste(n, l):
    wordlist = []
    for i in range(n):
        size = random.randrange(1,l+1)
        wordlist.append(''.join(random.choice(string.ascii_lowercase) for x in range(size)))
    return wordlist
"""
L = gen_liste(10000, 105)
L1 = copy.deepcopy(L)
start_time_sort = time.time()
L.sort()
print("-------sort %s seconds-------" %(time.time() - start_time_sort))
start_time_lex = time.time()
tri_lexico(L1)
print("-------sort %s seconds-------" %(time.time() - start_time_lex))
print(L1 == L)
"""
with open("list2sort.txt", 'r') as f:
    data = f.read()
    L = data.split(' ')
    L.remove('')

start_time = time.time()
L.sort()
print(f"--------------python sort last {time.time() - start_time}--------")

with open("listsorted.txt", 'r') as f:
    data = f.read()
    L_sortd = data.split(' ')
    L_sortd.remove('')
print(L == L_sortd);




