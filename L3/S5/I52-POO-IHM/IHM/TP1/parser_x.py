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

def modif_sv(event=None):
    id_canv = canv.find_withtag("current")[0]
    txt = canv.gettags(id_canv)[0]
    sv.set(txt)
    return

def color_choice():
    print(f"You chose {sv.get()}")
    print("Destroyed")
    tl.destroy()

if __name__ == '__main__':
    dico = parser()
    sorted_dict_keys = sorted(dico.keys())
    print(sorted_dict_keys)
    exit(0)
    nb_coul = 0
    for key in sorted_dict_keys:
        nb_coul+=1
        print_key_with_spaces(key);
        print(dico[key])
    print(f"nb colors = {nb_coul}")

    col = int((nb_coul**0.5)//1 + 1);
    root = tk.Tk()
    tl = tk.Toplevel(bg="#00ffff")
    tl.grab_set()
    sv = tk.StringVar()
    HEIGHT = col*20
    WIDTH = col*20
    frm1= tk.Frame(tl, bd=3, bg="yellow")
    canv = tk.Canvas(frm1, highlightbackground="red", width=WIDTH, height=col*10, 
                     scrollregion=(0,0,0,HEIGHT))
    scroll_y = tk.Scrollbar(frm1, orient=tk.VERTICAL, command=canv.yview);
    canv.configure(yscrollcommand=scroll_y.set)
    k = 0
    for i in range(0, HEIGHT, 20):
        for j in range(0, WIDTH, 20):
            if (k < len(sorted_dict_keys)) :
                if (sorted_dict_keys[k] == "DebianRed"):
                    k+=1
                else:
                    rec = canv.create_rectangle(i, j, i+20, j+20,
                                                fill=sorted_dict_keys[k], 
                                                tags=(sorted_dict_keys[k],
                                                      "common_tag_col"))
                    k += 1
            else:
                rec = canv.create_rectangle(i, j, i+20, j+20)
    canv.tag_bind("common_tag_col", "<ButtonRelease-1>", modif_sv)
    print(canv.gettags("common_tag_col"))
    frm = tk.Frame(tl, bd=3, bg="green")
    sv.set("Hello World")
    label = tk.Label(tl, textvariable=sv)
    btn_ok = tk.Button(frm, text="Ok", command=color_choice)
    btn_annuler = tk.Button(frm, text="Annuler", command=color_choice)
    label.pack(side="top")
    canv.pack(side="left")
    scroll_y.pack(side="right", fill="y")
    frm1.pack(side="top")
    frm.pack(side="top")
    btn_ok.pack(side="left")
    btn_annuler.pack(side="left")
    root.mainloop()
