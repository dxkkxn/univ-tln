import tkinter as tk

if __name__ == '__main__':
    root = tk.Tk()
    tl = tk.Toplevel(bg="#00ffff")
    top_frame = tk.Frame(tl, bd=3)

    # create a menu button : Fichier with Nouveau, Ouvrir, Sauver, Quitter
    file_menu = tk.Menubutton(top_frame, text="Fichier")
    file_menu_ops = tk.Menu(file_menu)
    file_menu_ops.add_command(label="Nouveau")
    file_menu_ops.add_command(label="Ouvrir")
    file_menu_ops.add_command(label="Sauver")
    file_menu_ops.add_separator()
    file_menu_ops.add_command(label="Quitter")
    file_menu["menu"] = file_menu_ops
    """
    menu_bar = tk.Menu(top_frame)
    file_menu = tk.Menu(menu_bar, tearoff=0)
    file_menu.add_command(label="Nouveau")
    file_menu.add_command(label="Ouvrir")
    file_menu.add_command(label="Sauver")
    file_menu.add_separator()
    file_menu.add_command(label="Quitter")
    menu_bar.add_cascade(label="Fichier", menu=file_menu)
    menu_bar.add_separator()
    menu_bar.add_separator()
    menu_bar.add_separator()
    menu_bar.add_separator()
    menu_bar.add_separator()
#    menu_bar.add_command(label="Help")
    """
    
    #create button
    btn = tk.Button(top_frame, text="Aide")

    #create a Canvas inside a frame
    main_frame = tk.Frame(tl, bg="red") 
    canvas = tk.Canvas(main_frame, height=500, width=500, bg="green")
    # packings
    #menu_bar.pack()
    btn.pack(side="right")
    file_menu.pack(side="left")
    top_frame.pack(side="top", fill=tk.X)
    canvas.pack()
    main_frame.pack(side="top")

#    tl.config(menu=menu_bar)

    root.mainloop()
