from cng import cng 

rec = None
def move_rectangle():
    cng.obj_move(rec, 20, 20, color='white')

def wc_to_dc(point, view_port, pos_viewport, window, pos_window):
    px, py = point
    vx, vy = view_port
    wx, wy = window
    tvx, tvy = pos_viewport
    twx, twy = pos_window
    res_px = px*(vx/wx) + (tvx*vx)/wx + twy
    res_py = py*(vy/wy) + (tvy*vy)/wy + twx
    return res_px, res_py
    

def create_rectangle(posx, posy, l, h):
    global rec
    rec = cng.box(posx, posy, posx+l, posy+h)
    cng.assoc_button(1, move_rectangle)

if __name__  =="__main__":
    cng.init_window(pnom="test", pla=1200, pha=780)
    create_rectangle(1200//2, 780//2, 100, 100)
    
    
    cng.main_loop()
