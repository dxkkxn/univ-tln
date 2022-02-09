import tp1
from cng import cng

def points_sline(p1, p2, step):
    slope = (p2[1]-p1[1])/(p2[0]- p1[0])
    b = p1[1]-slope*p1[0]
    print(slope, b)
    res = []
    xt = p1[0]
    while (xt <= p2[0]) :
        res.append((xt, slope*xt+ b))
        xt += step
    return res

def draw_line_naive(p1, p2, step, view_port, pos_viewport, window, pos_window):
    slope = (p2[1]-p1[1])/(p2[0]- p1[0])
    p1_proj = tp1.wc_to_dc(p1, view_port, pos_viewport, window, pos_window)
    p2_proj = tp1.wc_to_dc(p2, view_port, pos_viewport, window, pos_window)
    xt = p1_proj[0]
    b = p1_proj[1]-slope*p1_proj[0]
    while (xt <= p2_proj[0]) :
        point = (xt, slope*xt+b)
        cng.point(point[0], point[1])
        xt += step
    return

def besenham(p1, p2):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1]
    dec = dx - 2*dy
    x, y = p1
    while(x <= p2[0]):
        cng.point(x, y)
        if (dec < 0) : 
            dec += 2*dx
            y += 1
        dec -= 2*dy
        x += 1
    return


if __name__ == '__main__': 
    cng.init_window(pnom="test", pla=1200, pha=780)
    rec = tp1.create_rectangle(1200//2-150, 780//2-150, 300, 300)
    view_port = (tp1.get_size(*cng.obj_get_coord(rec)))
    pos_viewport = (1200//2-150, 780//2-150)
    window = (45, 45)
    pos_window = (0, 0)
    p1 = (1, 1)
    p2 = (300, 90)
    draw_line_naive(p1, p2, 0.1, view_port, pos_viewport, window, pos_window)
    print(points_sline(p1, p2, 1))
    p1_proj = tp1.wc_to_dc(p1, view_port, pos_viewport, window, pos_window)
    p2_proj = tp1.wc_to_dc(p2, view_port, pos_viewport, window, pos_window)
    besenham(p1_proj, p2_proj)
    cng.main_loop()
     
