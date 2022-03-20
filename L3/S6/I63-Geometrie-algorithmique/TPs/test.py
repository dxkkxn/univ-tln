from cng import cng
import tp1

def move(): 
    global rec, selected
    x = cng.get_mouse_x()
    y = cng.get_mouse_y()
    
    if cng.obj_picked(rec, x, y) and not selected : 
        selected = True
    elif selected:
        obj_pos = cng.obj_get_position(rec)
        x = x - obj_pos[0]
        y = y - obj_pos[1]
        cng.obj_move(rec, x, y)
        selected = False
    print(selected)
        

selected = False

cng.init_window(pnom="test", pla=1200, pha=780)
rec = cng.box(1200//2-50, 780//2, 1200//2-50+100, 780//2+100)
cng.assoc_button(1, move)

cng.mainloop()
