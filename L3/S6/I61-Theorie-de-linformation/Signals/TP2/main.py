import math

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

def prob(text : str):
    n = len(text)
    hg = histogram(text)
    res = {}
    for key, val in hg.items():
        res[key] = (val/n)
    return res

def entropie():
    # prob np array ou list avec les probabilités
    res = 0
    for p in prob:
        if p != 0 :
            res += p * math.log2(p)
    res *= -1
    return res

class Server(object):
    def __init__(self, text : str, matrix_g : list[list], matrix_h : list[list]):
        self.text = text
        self.text_list = self.text_to_bin_lst()
        self.matrix_g = matrix_g
        self.k = len(matrix_g)
        self.n = len(matrix_g[0])
        self.matrix_h = matrix_h
        assert(len(matrix_h) ==self.n - self.k)
        assert(len(matrix_h[0]) ==self.n )
        return
    def compression(self):
        self.histogram = self.create_histogram()
        self.huffman_tree = self.create_tree()
        self.compressed_char_dict = {}
        self.binary_code(self.huffman_tree, [])
        self.text_list = self.recreate_text()
        return

    def text_to_bin_lst(self):
        rbin = []
        for c in self.text:
            rbin.extend([int(x) for x in bin(ord(c))[2:]])
        return rbin

    def recreate_text(self):
        rtext = []
        for c in self.text:
            rtext.extend(self.compressed_char_dict[c])
        return rtext
    def create_histogram(self) ->dict :
        histogram = {}
        for char in self.text:
            if char not in histogram:
                histogram[char] = 1
            else :
                histogram[char] += 1
        return histogram

    def create_tree(self):
        nodes = []
        for key, val in self.histogram.items():
            nodes.append(Node(letter = key, val=val))
        while len(nodes) > 1 :
            min1 = min(nodes)
            nodes.remove(min1)
            min2 = min(nodes)
            nodes.remove(min2)
            nodes.append(Node(val=min1.val+min2.val, left=min2, right=min1))
        return nodes[0]

    def binary_code(self, root : Node, curr_lst):
        if root != None:
            if root.left == None and root.right == None:
                assert(root.letter)
                self.compressed_char_dict[root.letter] = curr_lst
            else:
                self.binary_code(root.left, curr_lst+[0])
                self.binary_code(root.right, curr_lst+[1])
        return


    @staticmethod
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

    def encode(self):
        partitioned_lst = []
        i = 0
        while i < len(self.text_list) :
            partitioned_lst.append(self.text_list[i:i+self.k])
            i += self.k
        while len(partitioned_lst[-1]) < self.k:
            partitioned_lst[-1].append(0)
        res = []
        for vect in partitioned_lst :
            res.append(self.mult_matrix([vect], self.matrix_g))
        print(res)


        

        return

def main(): 
    text = "TESTDETI"
    text = "AAAAAAABCCCCCCDDEEEEE"
    G = [[1, 1, 1, 0, 0, 0, 0],
         [1, 0, 0, 1, 1, 0, 0],
         [0, 1, 0, 1, 0, 1, 0],
         [1, 1, 0, 1, 0, 0, 1]]
    H = [[0, 0, 0, 1, 1, 1, 1],
         [0, 1, 1, 0, 0, 1, 1],
         [1, 0, 1, 0, 1, 0, 1]]
    s = Server(text, G, H)
    s.encode()
    # hg = histogram(text)
    # p = prob(text)
    # e = entropie(list(p.values()))
    # tree = create_tree(hg)
    # hc = {}
    # binary_code(tree, hc, "")
    # print(hc)
    # print(p, e)
    # n_hc = {}
    # for key, val in hc.items() :
    #     n_hc[key] = "1234567"
    # print(avg_len(p, hc))
    # print(avg_len(p, n_hc))
    # print(compression_rate(text, hc))


if __name__ == "__main__":
    main()
    
