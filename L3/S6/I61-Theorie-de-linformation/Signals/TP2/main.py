import math

def histogram(text : str): 
    histogram = {}
    for char in text:
        if char not in histogram: 
            histogram[char] = 1
        else :
            histogram[char] += 1
    return histogram

def prob(text : str): 
    n = len(text)
    hg = histogram(text)
    res = {}
    for key, val in hg.items(): 
        res[key] = (val/n)
    return res

def entropie(prob):
    # prob np array ou list avec les probabilités
    res = 0
    for p in prob:
        if p != 0 :
          res += p * math.log2(p)
    res *= -1
    return res 

class Node(object):
    def __init__(self, letter=None, val = None,  left = None, right = None): 
        self.right  = right 
        self.left   = left
        self.val    = val 
        self.letter = letter
    def __str__(self): 
        res = f"{self.letter} : {self.val}"
        return res
    def __lt__(self, other): 
        return self.val < other.val

def print_dfs(root : Node) : 
    if root != None:
        print(root)
        print_dfs(root.left)
        print_dfs(root.right)
    return

def binary_code(root : Node, dico, curr_code): 
    if root != None: 
        print(root)
        if root.left == None and root.right == None:
            assert(root.letter)
            dico[root.letter] = curr_code
        else:
            binary_code(root.left, dico, curr_code+"0")
            binary_code(root.right, dico, curr_code+"1")
    return

def create_tree(hg): 
    nodes = []
    for key, val in hg.items(): 
        nodes.append(Node(letter = key, val=val))
    while len(nodes) > 1 :
        min1 = min(nodes)
        nodes.remove(min1)
        min2 = min(nodes)
        nodes.remove(min2)
        nodes.append(Node(val=min1.val+min2.val, left=min2, right=min1))
        #print(max(nodes))
#        print(min1, min2)
    print_dfs(nodes[0])
    return nodes[0]

def avg_len(prob, huffman_code): 
    assert(len(prob)==len(huffman_code))
    res = 0
    for key, val in huffman_code.items(): 
        res += prob[key]*len(val)
    return res

def compression_rate(text, huffman_code): 
    huffman_len = 0
    for c in text: 
        huffman_len += len(huffman_code[c])
    return huffman_len/(len(text)*7)
    

def main(): 
    text = "TESTDETI"
#    text = "AAAAAAABCCCCCCDDEEEEE"
    hg = histogram(text)
    p = prob(text)
    e = entropie(list(p.values()))
    tree = create_tree(hg)
    hc = {}
    binary_code(tree, hc, "")
    print(hc)
    print(p, e)
    n_hc = {}
    for key, val in hc.items() :
        n_hc[key] = "1234567"
    print(avg_len(p, hc))
    print(avg_len(p, n_hc))
    print(compression_rate(text, hc))

if __name__ == "__main__":
    main()
    
