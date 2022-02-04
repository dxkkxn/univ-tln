from cng import cng

rec = None
def move_rectangle():
    cng.obj_move(rec, 20, 20)

def wc_to_dc(point, view_port, pos_viewport, window, pos_window):
    px, py = point
    vx, vy = view_port
    wx, wy = window
    tvx, tvy = pos_viewport
    twx, twy = pos_window
    #res_px = px*(vx/wx) + (tvx*vx)/wx - twy
    #res_py = py*(vy/wy) + (tvy*vy)/wy - twx

    res_px = px*(vx/wx) + (tvx*wx-twx*vx)/wx 
    res_py = py*(vy/wy) + (tvy*wy-twy*vy)/wy 
    return res_px, res_py

def create_rectangle(posx, posy, l, h):
    global rec
    rec = cng.rectangle(posx, posy, posx+l, posy+h)
    cng.assoc_button(1, move_rectangle)

def get_size(p1x, p1y, p2x, p2y):
    l = abs(p1x - p2x)
    h = abs(p1y - p2y)

    return h, l

def extract_points_from_file(filename):
    with open(filename) as f:
        data = [line.strip().split(' ') for line in f.read().strip().split('\n')]
        res = []
        for line in data :
            res.append((int(line[0]), int(line[1])))
    return res
        
def horner(x, poly): 
    res = poly[-1]
    i = -2
    while(i >= -len(poly)) : 
        res = res * x + poly[i]
        i -= 1
    return res
def test(x):
    return 3*x**3+2*x**2+ 1*x + 5

def draw_poly_func(xmin, xmax, nbpoints, poly):
    pas = (xmax-xmin)/nbpoints
    res = []
    for i in range(nbpoints):
        px = xmin+pas
        py = horner(px, poly)
        res.append((px, py))
    print(res)
    return res



if __name__ == "__main__":
    cng.init_window(pnom="test", pla=1200, pha=780)
    create_rectangle(1200//2-50, 780//2, 100, 100)
    cng.box(0, 0, 10, 10)
    view_port = (get_size(*cng.obj_get_coord(rec)))
    pos_viewport = (1200//2-50, 780//2)
    print(pos_viewport, cng.obj_get_coord(rec))
    #window = (6,6)
    #pos_window = (-3, -3)
    #p1, p2 = (wc_to_dc((-1,-1), view_port, pos_viewport, window, pos_window), 
    #          wc_to_dc((1,1), view_port, pos_viewport, window, pos_window))
    #cng.box(p1[0], p1[1], p2[0], p2[1])
    #print(p1, p2)
    window = (44, 44)
    pos_window = (-22, -22)
    #for point in extract_points_from_file("points.txt"): 
    #    point = (wc_to_dc(point, view_port, pos_viewport, window, pos_window))
    #    cng.disc(point[0], point[1], 2)

    for point in draw_poly_func(-4, 4, 50, [5,1,2,3]): 
        point = (wc_to_dc(point, view_port, pos_viewport, window, pos_window))
        print(point)
        cng.disc(point[0], point[1], 2)

    cng.main_loop()
