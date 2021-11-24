import tkinter as tk

if __name__ == '__main__':
    root = tk.Tk()
    tl = tk.Toplevel(bg="#00ffff")
    frm = tk.Frame(tl, bd=3, bg="green")
    # create a menu button : Fichier with Nouveau, Ouvrir, Sauver, Quitter
    menu_btn = tk.Menubutton(frm, text="Menu")
    menu_btn.menu = tk.Menu(menu_btn)
    menu_btn["menu"] = menu_btn.menu
    menu_btn.menu.add_chekbutton(label="Nouveau")
    menu_btn.menu.add_chekbutton(label="Ouvrir")
    menu_btn.menu.add_chekbutton(label="Quitter")
    menu_btn.pack()
    frm.pack()
    root.mainloop()
