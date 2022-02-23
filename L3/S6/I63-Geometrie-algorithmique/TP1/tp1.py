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
    px = xmin
    for i in range(nbpoints):
        py = horner(px, poly)
        res.append((px, py))
        px += pas
    print(res)
    return res



if __name__ == "__main__":
    cng.init_window(pnom="test", pla=1200, pha=780)
    rec = create_rectangle(1200//2-50, 780//2, 100, 100)
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
    pos_window = (0, 0)
    #for point in extract_points_from_file("points.txt"): 
    #    point = (wc_to_dc(point, view_port, pos_viewport, window, pos_window))
    #    cng.disc(point[0], point[1], 2)

    for point in draw_poly_func(-4, 4, 50, [5,1,2,3]): 
        point = (wc_to_dc(point, view_port, pos_viewport, window, pos_window))
        print(point)
        cng.disc(point[0], point[1], 2)

    cng.main_loop()
