import tp1
from cng import cng

selected = False
curr_point = None
def move(control_points):
    global selected
    global curr_point
    x = cng.get_mouse_x()
    y = cng.get_mouse_y()

    if selected:
        obj_pos = cng.obj_get_position(curr_point)
        x = x - obj_pos[0]
        y = y - obj_pos[1]
        cng.obj_move(curr_point, x, y)
        update_bezier(control_points)
        selected = False
    else :
        for point in control_points:
            if cng.obj_picked(point, x, y) :
                selected = True
                curr_point = point
    print(selected)


def update_bezier(control_p):
    global curr_curve
    points = []
    for point in control_p:
        points.append(cng.obj_get_position(point))

    for px in curr_curve:
        cng.obj_delete(px)

    curr_curve = []
    u = 0
    while (u < 1) :
        p = bezier(points, u)
        curr_curve.append(cng.point(*p))
        u+=0.001
    return

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
        control_points.append(cng.disc(p[0], p[1], 5))
    cng.assoc_button(1, lambda: move(control_points))
    u = 0
    points = proj_p
    curr_curve = []
    while (u < 1) :
        p = bezier(points, u)
        # p = tp1.wc_to_dc((p[0], p[1]), view_port, pos_viewport, window, pos_window)
        curr_curve.append(cng.point(*p))
        u+=0.001
    cng.mainloop()
