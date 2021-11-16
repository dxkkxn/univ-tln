import tkinter as tk
def normalize_name(ch):
    """
    Takes a str in paramater with spaces and in small case and return the str 
    without spaces and in CamelCase
    """
    ch = ch.split(' ')
    res = ""
    for element in ch: 
        res += element.capitalize()
    return res   

def normalize_nb(nb):
    nb = nb.strip()
    nb = nb.split()
    for i in range(len(nb)):
        nb[i] = int(nb[i])
    return nb



def parser():
    """
    Read file rgb.txt and return a dictionary with every name and its
    RGB value
    """
    res = {}
    with open("/etc/X11/rgb.txt") as f:
        data = f.read()
        data = data.split('\n')
        data.pop(0)
        data.pop(-1)
        for element in data: 
            element = element.split('\t')
            # formating
            if (len(element) == 3):
                nb_str, void, name = element
            else :
                assert(len(element) == 4)
                nb_str, nb_str_2, void, name = element
                nb_str = nb_str+nb_str_2

            # duplicate check

            # all names in CamelCase
            if(name[0].isupper() is False):
                name = normalize_name(name)
            rgb = normalize_nb(nb_str)
            if name not in res: 
                res[name] = rgb
            else:
                assert(res[name]==rgb)
        return res;

def print_key_with_spaces(key):
    """ 
    Print a str in CamelCase whit spaces between 
    each word 
    """
    print(key[0], end="", sep= "")
    for char in key[1:]: 
        if char.isupper() is False:
            print(char, end = "", sep="")
        else:
            print(" ", char, end = "", sep="")
    print(" ", end="", sep="")


if __name__ == '__main__':
    dico = parser()
    sorted_dict_keys = sorted(dico.keys())
    print(sorted_dict_keys)
    for key in sorted_dict_keys: 
        print_key_with_spaces(key);
        print(dico[key])

    root = tk.Tk()
    tl = tk.Toplevel(bg="#00ffff")
    sv = tk.StringVar()
    canv = tk.Canvas(tl, highlightbackground="red", bg="yellow")
    sv.set("Hello World")
    frm = tk.Frame(tl, bd=3, bg="green")
    label = tk.Label(tl, textvariable=sv)
    btn_ok = tk.Button(frm, text="Ok")
    btn_annuler = tk.Button(frm, text="Annuler")
    btn_ok.pack()
    btn_annuler.pack()
    canv.pack() 
    label.pack()
    frm.pack()
    root.mainloop()
