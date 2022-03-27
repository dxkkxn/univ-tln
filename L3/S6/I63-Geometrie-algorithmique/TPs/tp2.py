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
    if p1[0] > p2[0] :
        p1, p2 = p2, p1

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

def besenham_oct1(p1, p2):
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

def besenham(p1, p2): 
    x = get_octant(p1, p2)
    print(x, p1, p2)
    if x == 1: 
        besenham_oct1(p1, p2)
    elif x == 2: 
        besenham_oct2(p1, p2)
    elif x == 3: 
        besenham_oct3(p1, p2)
    elif x == 4: 
        besenham_oct4(p1, p2)
    elif x == 5: 
        besenham_oct5(p1, p2)
    elif x == 6: 
        besenham_oct6(p1, p2)
    elif x == 7: 
        besenham_oct7(p1, p2)
    elif x == 8: 
        besenham_oct8(p1, p2)



def get_octant(p1, p2):
    dx = (p2[0] - p1[0])
    dy = (p2[1] - p1[1])
    if (abs(dy) >= abs(dx)): 
        #oct 2 ou 3 ou 6 ou 7
        if (dy > 0 and dx > 0):
            return 2
        if (dy > 0 and dx <= 0):
            return 3
        if (dy < 0 and dx < 0):
            return 6
        if (dy < 0 and dx >= 0):
            return 7
    else :
        #(abs(dx) < abs(dy));
        #oct 1 ou 4 ou 5 ou 8
        if (dy > 0 and dx >= 0):
            return 1
        if (dy > 0 and dx < 0):
            return 4
        if (dy <= 0 and dx < 0):
            return 5
        if (dy < 0 and dx > 0):
            return 8
    print("ERROR OCTANT ", p1, p2)
    exit(-1)

def besenham_oct2(p1, p2):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1]
    dec = dy - 2*dx
    x, y = p1
    while(y <= p2[1]):
        cng.point(x, y)
        if (dec < 0) :
            dec += 2*dy
            x += 1
        dec -= 2*dx
        y += 1
    return

def besenham_oct3(p1, p2):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1]
    dec = dy + 2*dx
    x, y = p1
    while(y <= p2[1]):
        cng.point(x, y)
        if (dec < 0) :
            dec += 2*dy
            x -= 1
        dec += 2*dx
        y += 1
    return

def besenham_oct4(p1, p2):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1]
    dec = -dx - 2*dy
    x, y = p1
    while(x >= p2[0]):
        cng.point(x, y)
        if (dec < 0) : 
            dec -= 2*dx
            y += 1
        dec -= 2*dy
        x -= 1
    return

def besenham_oct5(p1, p2):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1]
    dec = -dx + 2*dy
    x, y = p1
    while(x >= p2[0]):
        cng.point(x, y)
        if (dec < 0) : 
            dec -= 2*dx
            y -= 1
        dec += 2*dy
        x -= 1
    return

def besenham_oct6(p1, p2):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1]
    dec = -dy + 2*dx
    x, y = p1
    while(y >= p2[1]):
        cng.point(x, y)
        if (dec < 0) :
            dec -= 2*dy
            x -= 1
        dec += 2*dx
        y -= 1
    return

def besenham_oct7(p1, p2):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1]
    dec = -dy - 2*dx
    x, y = p1
    while(y >= p2[1]):
        cng.point(x, y)
        if (dec < 0) :
            dec -= 2*dy
            x += 1
        dec -= 2*dx
        y -= 1
    return

def besenham_oct8(p1, p2):
    dx = p2[0] - p1[0]
    dy = p2[1] - p1[1]
    dec = dx + 2*dy
    x, y = p1
    while(x <= p2[0]):
        cng.point(x, y)
        if (dec < 0) : 
            dec += 2*dx
            y -= 1
        dec += 2*dy
        x += 1
    return


if __name__ == '__main__': 
    cng.init_window(pnom="test", pla=1200, pha=780)
    rec = tp1.create_rectangle(1200//2-150, 780//2-150, 300, 300)
    print(cng.obj_get_coord(rec))
    view_port = (tp1.get_size(*cng.obj_get_coord(rec)))
    pos_viewport = (1200//2-150, 780//2-150)
    window = (450, 450)
    pos_window = (0, 0)
#    p1 = (1, 1)
#    p2 = (300, 90)
#    p2_oct2 = (90, 300)
#    p2_oct3 = (-90, 300)
#    p2_oct4 = (-300, 90)
#    p2_oct5 = (-300, -90)
#    p2_oct6 = (-90, -300)
#    p2_oct7 = (90, -300)
#    p2_oct8 = (300, -90)
#    # draw_line_naive(p1, p2, 0.1, view_port, pos_viewport, window, pos_window)
#    # print(points_sline(p1, p2, 1))
#    p1_proj = tp1.wc_to_dc(p1, view_port, pos_viewport, window, pos_window)
#    p2_proj = tp1.wc_to_dc(p2, view_port, pos_viewport, window, pos_window)
#    p2_oct2_proj = tp1.wc_to_dc(p2_oct2, view_port, pos_viewport, window, pos_window)
#    p2_oct3_proj = tp1.wc_to_dc(p2_oct3, view_port, pos_viewport, window, pos_window)
#    p2_oct4_proj = tp1.wc_to_dc(p2_oct4, view_port, pos_viewport, window, pos_window)
#    p2_oct5_proj = tp1.wc_to_dc(p2_oct5, view_port, pos_viewport, window, pos_window)
#    p2_oct6_proj = tp1.wc_to_dc(p2_oct6, view_port, pos_viewport, window, pos_window)
#    p2_oct7_proj = tp1.wc_to_dc(p2_oct7, view_port, pos_viewport, window, pos_window)
#    p2_oct8_proj = tp1.wc_to_dc(p2_oct8, view_port, pos_viewport, window, pos_window)
#
#    besenham(p1_proj, p2_proj)
#    besenham(p1_proj, p2_oct2_proj)
#    besenham(p1_proj, p2_oct3_proj)
#    besenham(p1_proj, p2_oct4_proj)
#    besenham(p1_proj, p2_oct5_proj)
#    besenham(p1_proj, p2_oct6_proj)
#    besenham(p1_proj, p2_oct7_proj)
#    besenham(p1_proj, p2_oct8_proj)
#
#    cng.disc(p1_proj[0], p1_proj[1], 2)
#    cng.disc(p2_proj[0], p2_proj[1], 2)
#    cng.disc(p2_oct2_proj[0], p2_oct2_proj[1], 2)
#    cng.disc(p2_oct3_proj[0], p2_oct3_proj[1], 2)
#    cng.disc(p2_oct4_proj[0], p2_oct4_proj[1], 2)
#    cng.disc(p2_oct5_proj[0], p2_oct5_proj[1], 2)
#    cng.disc(p2_oct6_proj[0], p2_oct6_proj[1], 2)
#    cng.disc(p2_oct7_proj[0], p2_oct7_proj[1], 2)
#    cng.disc(p2_oct8_proj[0], p2_oct8_proj[1], 2)
#    print("p1 : ", p1_proj)
#    print("p2_oct1 : ", p2_proj)
#    print("p2_oct2 : ", p2_oct2_proj)
#    print("p2_oct3 : ", p2_oct3_proj)
#    print("p2_oct4 : ", p2_oct4_proj)
#    print("p2_oct5 : ", p2_oct5_proj)
#    print("p2_oct6 : ", p2_oct6_proj)
#    print("p2_oct7 : ", p2_oct7_proj)
#    print("p2_oct8 : ", p2_oct8_proj)
    # points = [(3, 1), (1, 3), (-1, 3), (-3, 1), (-3, -1), (-1, -3), (1,-3),
    #           (3, -1), (2,0), (2,2), (0,2), (-2,2), (-2, 0), (-2, -2), (0, -2),
    #           (2, -2)]
    # for point in points:
    #     print(get_octant((0,0), point))
    #

    import random
    import time
    random.seed(0)
    N = 20
    for i in range(N):
        x_a, y_a = random.randint(0, 450), random.randint(0, 450)
        x_b, y_b = random.randint(0, 450), random.randint(0, 450)
        p1 = x_a, y_a
        p2 = x_b, y_b
        print(p1, p2)
        cng.current_color("red")
        draw_line_naive(p1, p2, 0.01, view_port, pos_viewport, window, pos_window)
        cng.refresh()
        time.sleep(1)
        p1 = tp1.wc_to_dc((x_a, y_a), view_port, pos_viewport, window, pos_window)
        p2 = tp1.wc_to_dc((x_b, y_b), view_port, pos_viewport, window, pos_window)
        cng.current_color("black")
        besenham(p1, p2)
        cng.refresh()
        time.sleep(1)

    # time.sleep(10)
    # random.seed(0)
    # cng.current_color("black")
    # print("----------------------")
    # for i in range(N):
    #     x_a, y_a = random.randint(0, 450), random.randint(0, 450)
    #     x_b, y_b = random.randint(0, 450), random.randint(0, 450)
    #     print("->",(x_a, y_a), (x_b, y_b))
    #     p1 = tp1.wc_to_dc((x_a, y_a), view_port, pos_viewport, window, pos_window)
    #     p2 = tp1.wc_to_dc((x_b, y_b), view_port, pos_viewport, window, pos_window)
    #     besenham(p1, p2)




        
    cng.main_loop()
