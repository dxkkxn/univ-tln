import tkinter as tk
from tkinter import filedialog


last_x=None
last_y=None
def create_line(event=None):
    global last_x, last_y
    print("create_line", event)
    curr_paint = "paint"+str(listofpaints[-1])
    id_canv = canvas.create_line(last_x, last_y, event.x, event.y, width=5, fill="black",
                                 smooth=True, tags=curr_paint)
    print("newline", listofpaints[-1], id_canv)
    last_x, last_y = event.x, event.y
    return


listofpaints = []
def new_paint(event=None):
    print("new_paint", event)
    global last_x, last_y
    last_x, last_y = event.x, event.y
    if listofpaints == []:
        listofpaints.append(1)
    else :
        listofpaints.append(listofpaints[-1]+1)
    return

def modify_color(event=None, curr_paint="paint1"):
#    curr_paint = "paint"+str(listofpaints[-1])
    canvas.itemconfigure(curr_paint, fill="red")

    global bottom_string_var
    bottom_string_var.set(curr_paint[-1])
    print("Entered")


def reset_color(event=None, curr_paint="paint1"):
#    curr_paint = "paint"+str(listofpaints[-1])
    global bottom_string_var
    bottom_string_var.set("")
    canvas.itemconfigure(curr_paint, fill="black")
    print("Leaved")


def tag_bind_paint(event=None):
    curr_paint = "paint"+str(listofpaints[-1])
    canvas.tag_bind(curr_paint, sequence="<Enter>",
                    func=lambda x :modify_color(x,curr_paint))
    canvas.tag_bind(curr_paint, sequence="<Leave>",
                    func=lambda x :reset_color(x,curr_paint))
    canvas.tag_bind(curr_paint, sequence="<B1-Motion>",
                    func=lambda x :move_paint(x,curr_paint))

    file_menu_ops.entryconfigure(3, state="active")
    print("Bind succeed")


def move_paint(event=None, curr_paint="paint1"):
    print(event.x, event.y, curr_paint)
    print(canvas.coords(curr_paint))
    id_clicked = canvas.find_withtag("current")
    x_0, y_0, x_1, y_1 = canvas.coords(id_clicked)
    canvas.move(curr_paint, event.x-x_0, event.y-y_0)
    # for id_line in canvas.find_withtag(curr_paint):
    #     #x_0, y_0, x_1, y_1 = canvas.coords(id_line)
    #     canvas.move(id_line, event.x-x_0, event.y-y_0)
    #     # canvas.coords(id_line, (event.x-x_0), (event.y-y_0), (event.x-x_1), (event.y-y_1))
    return


def save_as_file(event=None):
    path = filedialog.asksaveasfilename(defaultextension=".paint")
    with open(path, "w") as f:
        for paint in listofpaints:
            curr_paint = "paint"+str(paint)
            f.write(curr_paint+'\n')
            for id_line in canvas.find_withtag(curr_paint):
                f.write(str(canvas.coords(id_line))+'\n')
    print("Succeed")


def open_file(event=None):
    path = filedialog.askopenfilename(filetypes=[("paint","*.paint")])
    with open(path, "r") as f:
        lines = f.read().split('\n')
        for i in range(len(lines)):
            line = lines[i]
            if line.startswith("paint"):
                canvas.event_generate("<Control-B1-ButtonRelease>")
                line = lines[i+1].strip("[]")
                x_0, y_0, x_1, y_1 = [float(x) for x in line.split(", ")]
                canvas.event_generate("<Control-Button-1>", x=x_0, y=y_0)

            elif line.startswith('[') and line.endswith(']'):
                line = line.strip("[]")
                x_0, y_0, x_1, y_1 = [float(x) for x in line.split(", ")]
                canvas.event_generate("<Control-B1-Motion>", x=x_0, y=y_0)
                canvas.event_generate("<Control-B1-Motion>", x=x_1, y=y_1)
            else:
                print(line)
    canvas.event_generate("<Control-B1-ButtonRelease>")
    print("Succeed")

def open_help_window():
    help_window = tk.Toplevel(tl)
    text_widget = tk.Text(help_window)
    text_widget.insert("end", "tkdocs.com")
    text_widget.pack(side="top")

if __name__ == "__main__":
    root = tk.Tk()
    tl = tk.Toplevel()
    top_frame = tk.Frame(tl, bd=3)

    # create a menu button : Fichier with Nouveau, Ouvrir, Sauver, Quitter
    file_menu = tk.Menubutton(top_frame, text="Fichier")
    file_menu_ops = tk.Menu(file_menu)
    file_menu_ops.add_command(label="Nouveau")
    file_menu_ops.add_command(label="Ouvrir", command=open_file)
    file_menu_ops.add_command(label="Sauver", state="disabled", command=save_as_file)
    file_menu_ops.add_separator()
    file_menu_ops.add_command(label="Quitter", command=lambda:tl.destroy())
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
#   menu_bar.add_command(label="Help")
    """
    
    #create button
    btn = tk.Button(top_frame, text="Aide", command= open_help_window)

    #create a Canvas inside a frame
    main_frame = tk.Frame(tl, bg="red") 
    canvas = tk.Canvas(main_frame, height=1000, width=1000, bg="white")
    #link c-mouse1 to create_line
    canvas.bind(sequence="<Control-Button-1>", func=lambda x: new_paint(x))
    canvas.bind(sequence="<Control-B1-Motion>", func=lambda x: create_line(x))
    canvas.bind(sequence="<Control-B1-ButtonRelease>", func=lambda x: tag_bind_paint(x))

    #bottom bar
    bottom_frame = tk.Frame(tl, bd=3, bg="cyan")
    bottom_string_var = tk.StringVar()
    label = tk.Label(bottom_frame, textvariable=bottom_string_var)



    # packings
    #menu_bar.pack()
    btn.pack(side="right")
    file_menu.pack(side="left")
    top_frame.pack(side="top", fill=tk.X)
    canvas.pack()
    main_frame.pack(side="top")
    label.pack(side="left")
    bottom_frame.pack(side="top", fill="x")

#    tl.config(menu=menu_bar)

    root.mainloop()
