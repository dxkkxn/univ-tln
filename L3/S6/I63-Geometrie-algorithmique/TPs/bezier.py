import tp1
from math import factorial
from cng import cng

selected = False
curr_point = None
selected_indexs = None
curves_px = None
def move(curves):
    global selected
    global selected_indexs
    global curr_point
    x = cng.get_mouse_x()
    y = cng.get_mouse_y()

    if selected:
        obj_pos = cng.obj_get_position(curr_point)
        x = x - obj_pos[0]
        y = y - obj_pos[1]
        cng.obj_move(curr_point, x, y)
        i = 0
        for curve in curves: 
            if curr_point in curve:
                if curr_point == curve[-1] and 0<= i+1 < len(curves):
                    #m_n
                    m_n = curve[-1]
                    #m_n_plus_one
                    cng.obj_move(curves[i+1][1], x, y)
                    #m_n_moins_one
                    cng.obj_move(curves[i][-2], x, y)
                elif curr_point == curve[-2] and 0<=i+1<len(curves) :
                    #m_n-1 changed
                    print("m_n-1 changed")
                    #mettre a jour m_n_plus_one
                    cng.obj_move(curves[i+1][1], -x, -y)

                elif curr_point == curve[1] and 0<=i-1<len(curves):
                    #m_n+1 has changed
                    #mettre a jour m_n_moins_one_
                    cng.obj_move(curves[i-1][-2], -x, -y)
            i += 1
        for i in range(len(curves)):
            curves_px[i] = update_bezier(curves[i], curves_px[i])
        cng.obj_put_color(curr_point)
        selected = False
    else :
        i = 0
        selected_indexs = []
        for curve in curves:
            for point in curve:
                if cng.obj_picked(point, x, y) :
                    selected = True
                    curr_point = point
                    selected_indexs.append(i)
                    cng.current_color("red")
                    cng.obj_put_color(curr_point)
                    cng.current_color("black")
            i += 1
        if selected is False:
            curve = []
            m_n_4 = (x, y)
            m_n = cng.obj_get_position(curves[-1][-1])
            m_n_moins_1 = cng.obj_get_position(curves[-1][-2])
            m_n_plus_1 = (m_n[0]*2 - m_n_moins_1[0], m_n[1]*2 - m_n_moins_1[1])
            m_n_3 = (m_n_plus_1[0]+50, m_n_plus_1[1]+50)
            new_points = [m_n, m_n_plus_1, m_n_3, m_n_4]
            curve_control_p = []
            curve_control_p.append(curves[-1][-1])
            print(new_points)
            for x, y in new_points[1:]:
                curve_control_p.append(cng.disc(x, y, 9))
            curves.append(curve_control_p)
            curves_px.append(create_bezier(new_points))

    print(selected)

#def update_points_cont(curves): 
#    for i in range(1, len(curves)): 
#        m_n_minus_one = curves[i-1][-2]
#        assert(curves[i-1][-1] == curves[i][0])
#        m_n = curves[i][0]
#        m_n_plus_one = curves[i][1]
#        if m_n != (0.5*(m_n_minus_one[0]+m_n_plus_one[0]), 0.5*(m_n_minus_one[1],)

def newton_bin(n, p):
    return factorial(n)/(factorial(p)*factorial(n-p))

def bernstein_poly(n, p, u):
    return newton_bin(n, p) * u**p * (1-u)**(n-p)

def bezier_poly(points, u):
    n = len(points)
    res = [0, 0]
    for i in range(n):
        berns_poly = bernstein_poly(n-1, i, u)
        res[0] += berns_poly* points[i][0]
        res[1] += berns_poly* points[i][1]
    return res


def update_bezier(curve, old_curve_px):
    points = []
    for point in curve:
        points.append(cng.obj_get_position(point))

    for px in old_curve_px:
        cng.obj_delete(px)

    new_curve_px = []
    u = 0
    while (u < 1) :
        p = bezier_poly(points, u)
        new_curve_px.append(cng.point(*p))
        u+=0.001
    return new_curve_px

def update_bezier(curve, old_curve_px):
    points = []
    for point in curve:
        points.append(cng.obj_get_position(point))

    for px in old_curve_px:
        cng.obj_delete(px)

    new_curve_px = []
    u = 0
    while (u < 1) :
        p = bezier_poly(points, u)
        new_curve_px.append(cng.point(*p))
        u+=0.001
    return new_curve_px
def bezier(points, u):
    if len(points) == 1:
        return points[0]
    else:
        new_points = []
        for i in range(1, len(points)):
            p = ((1-u)*points[i-1][0], (1-u)*points[i-1][1])
            q = (u*points[i][0], u*points[i][1])
            new_points.append((p[0]+q[0], p[1]+q[1]))
#        print(new_points)
        return bezier(new_points, u)

def create_bezier(points):
    u = 0
    curr_curve = []
    while (u < 1) :
        p = bezier_poly(points, u)
        curr_curve.append(cng.point(*p))
        u += 0.001
    return curr_curve


if __name__ == '__main__':
    cng.init_window(pnom="test", pla=1200, pha=780)
    rec = tp1.create_rectangle(1200//2-150, 780//2-150, 300, 300)
    view_port = (tp1.get_size(*cng.obj_get_coord(rec)))
    pos_viewport = (1200//2-150, 780//2-150)
    window = (25, 25)
    pos_window = (0, 0)
    points = [(1,1), (0, 10), (10, -10), (15, 1)]
    proj_p = []
    control_points = []
    for x, y in points:
        p = tp1.wc_to_dc((x,y), view_port, pos_viewport, window, pos_window)
        proj_p.append(p)
        control_points.append(cng.disc(p[0], p[1], 9))
    curves = [control_points]
    print(curves)
    cng.assoc_button(1, lambda: move(curves))
    u = 0
    points = proj_p
    curr_curve = []
    while (u < 1) :
        p = bezier_poly(points, u)
        # p = tp1.wc_to_dc((p[0], p[1]), view_port, pos_viewport, window, pos_window)
        curr_curve.append(cng.point(*p))
        u+=0.001
    curves_px = [curr_curve]
    cng.mainloop()
    # val = [0, 0.2, 0.5, 0.7, 1]
    # points = [(1,0), (2,2), (6,2), (8,2)]
    # for u in val :
    #     p = bezier_poly(points, u)
    #     # p = tp1.wc_to_dc((p[0], p[1]), view_port, pos_viewport, window, pos_window)
    #     # curr_curve.append(cng.point(*p))
    #     print(p)
