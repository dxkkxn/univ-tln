#!/usr/bin/env python3

#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

###############################################################
# portage de planet.c

from OpenGL.GL import *  # car prefixe systematique
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys
# from Image import open
from PIL import Image
from math import cos, sin

###############################################################
# variables globales
year, day = 0, 0  # Terre
luna, periode = 0, 0  # Lune
quadric = None
SOLEIL, TERRE, ATERRE, LUNE = 1, 2, 3, 4  # ID astre, planete, satellite
texture_planet = [None for i in range(5)]

DISPLAY_GRID = False

year, day, hour, x_pos, y_pos, z_pos = 0, 0, 0, 0, 0, 20
quadric = None

###############################################################
# chargement des textures

def load_texture(filename, ident):
    global texture_planet
    image = Image.open(filename)  # retourne une PIL.image

    ix = image.size[0]
    iy = image.size[1]
    # image = image.tostring("raw", "RGBX", 0, -1)
    image = image.tobytes("raw", "RGBX", 0, -1)

    # 2d texture (x and y size)
    # BUG (?)
    #glBindTexture(GL_TEXTURE_2D, glGenTextures(1, texture_planete[ident]))
    texture_planet[ident] = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, int(texture_planet[ident]))

    glPixelStorei(GL_UNPACK_ALIGNMENT,1)
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ix, iy, 0, GL_RGBA, GL_UNSIGNED_BYTE, image)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    # commente car alpha blinding (cf. atmosphere)
    #glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)

###############################################################
# creation des composants du systeme

def display_grid():
    glBegin(GL_LINES);

    n = 90
    for i in range(-n, n):
        # x, y
        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(i, -n, 0.0);
        glVertex3f(i, n, 0.0);

        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(-n, i, 0.0);
        glVertex3f(n, i, 0.0);

        #x, z
        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(i, 0.0, -n);
        glVertex3f(i, 0.0, n);

        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(-n, 0.0, i);
        glVertex3f(n, 0.0, i);

        #y, z
        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(0.0, i, -n);
        glVertex3f(0.0, i, n);

        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(0.0, -n, i);
        glVertex3f(0.0, n, i);

    glEnd()
    return

def create_planet(radius):
    ambient = (0.1, 0.1, 0.1, 1.0)
    diffuse = (0.8, 0.8, 0.8, 1.0)
    Black = (0.0, 0.0, 0.0, 1.0)
    sph1 = gluNewQuadric()

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse)
    glMaterialfv(GL_FRONT, GL_SPECULAR, Black)
    glMaterialfv(GL_FRONT, GL_EMISSION, ambient)
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0)

    gluQuadricDrawStyle(sph1, GLU_FILL)
    gluQuadricNormals(sph1, GLU_SMOOTH)
    gluQuadricTexture(sph1, GL_TRUE)
    gluSphere(sph1, radius, 100, 80)
    return

def create_sun(radius):
    ambient = (0.1, 0.1, 0.1, 1.0)
    diffuse = (0.8, 0.8, 0.8, 1.0)
    Black = (0.0, 0.0, 0.0, 1.0)
    sph2 = gluNewQuadric()

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse)
    glMaterialfv(GL_FRONT, GL_SPECULAR, Black)
    glMaterialfv(GL_FRONT, GL_EMISSION, ambient)
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0)

    gluQuadricDrawStyle(sph2, GLU_FILL)
    gluQuadricNormals(sph2, GLU_SMOOTH)
    gluQuadricTexture(sph2, GL_TRUE)
    gluSphere(sph2, radius, 100, 80)
    return

###############################################################
# affichage

def display_sun():
    glBindTexture(GL_TEXTURE_2D, texture_planet[1])
    create_sun(5.0)
    return

def display_earth():
    glBindTexture(GL_TEXTURE_2D, texture_planet[2])
    create_planet(1.0)
    return

def display_atmosphere():
    # glBindTexture(GL_TEXTURE_2D, texture_planet[3])


    diffuse = (0.9, 0.8, 0.8, 0.8)
    ambient = (0.3, 0.3, 0.3, 0.3)
    specular = (0.9, 0.8, 0.8, 0.8)
    sph1 = gluNewQuadric()

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse)
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient)
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular)


    gluQuadricDrawStyle(sph1, GLU_FILL)
    gluQuadricNormals(sph1, GLU_SMOOTH)
    gluQuadricTexture(sph1, GL_TRUE)

    glEnable(GL_BLEND);
    #glDepthMask (GL_FALSE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND)
    glBlendFunc( GL_ONE, GL_SRC_ALPHA);

    gluSphere(sph1, 1.3, 100, 80)

    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE)
    return

def display_moon():
    glBindTexture(GL_TEXTURE_2D, texture_planet[4])
    create_planet(0.3)
    return


###############################################################
#

def init_texture():
    pass

def init():
    # clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0)
    diffuse = [1.0, 1.0, 1.0, 1.0]
    specular = [0.001, 0.001, 0.001, 1.0]
    pos = [0, 0, 0, 1]
    ambient = [1.0, 1.0, 1.0, 1.0]
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_LIGHTING)
    glEnable(GL_TEXTURE_2D)

    glDepthFunc(GL_LESS)
    glClearDepth(1)

    glEnable(GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_POSITION, pos)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glShadeModel(GL_SMOOTH)
    quadric = gluNewQuadric()
    gluQuadricDrawStyle(quadric, GLU_FILL)
    load_texture("sun.bmp", 1)
    load_texture("earth.bmp", 2)
    load_texture("atmosphere.bmp", 3)
    load_texture("moon.bmp", 4)
    return

def display():
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glPushMatrix()
    gluLookAt(x_pos, y_pos, z_pos, #pos camera
              0, 0, 0, # look at
              0, 1, 0) #up vector

    if DISPLAY_GRID :
        display_grid()
    display_sun()
    glRotatef(year, 0.0, 1.0, 0.0)
    glTranslatef(10.0, 0.0, 0.0)
    glRotatef(day, 0.0, 1.0, 0.0)
    display_earth()
    display_atmosphere()
    glRotatef(hour, 0.0, 1.0, 0.0)
    glTranslatef(1.5, 0.0, 0.0)
    display_moon()
    # gluQuadricDrawStyle(quadric, GLU_FILL)
    # gluSphere(sph2, 7.0, 200, 160)

    glPopMatrix()
    glutSwapBuffers()
    return

def reshape(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(110, width/height, 3, 100)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    return


def keyboard(key, x, y):
    global day, year, hour, x_pos, y_pos, z_pos, DISPLAY_GRID
    if key == b'd':
        day = (day + 10) % 360
    elif key == b'y':
        year = (year + 5) % 360
    elif key == b'w':
        hour = (hour + 10) % 360
    elif key == b'a':
        year = (year + 1) % 360
        hour = (hour + 25) % 360
        day = (day + 10) % 360
    elif key == b'z':
        z_pos+=1
    elif key == b'Z':
        z_pos-=1
    elif key == b'g':
        DISPLAY_GRID = not DISPLAY_GRID
    elif key == b'h':
        radius = 10
        x, z = x_pos, z_pos
        x_pos = x * cos(0.1) - z * sin(0.1)
        z_pos = z * cos(0.1) + x * sin(0.1)
    elif key == b'l':
        radius = 10
        x, z = x_pos, z_pos
        x_pos = x * cos(-0.1) - z * sin(-0.1)
        z_pos = z * cos(-0.1) + x * sin(-0.1)
    elif key == b'j':
        y, z = y_pos, z_pos
        y_pos = y * cos(0.1) - z * sin(0.1)
        z_pos = z * cos(0.1) + y * sin(0.1)
    elif key == b'k':
        y, z = y_pos, z_pos
        y_pos = y * cos(-0.1) - z * sin(-0.1)
        z_pos = z * cos(-0.1) + y * sin(-0.1)
    elif key == b'\033':
        glutDestroyWindow(WIN)
        sys.exit(0)
    glutPostRedisplay()  # indispensable en Python
    return

###############################################################
# MAIN

if __name__ == "__main__":
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA |GLUT_DEPTH )
    WIN = glutCreateWindow('textures')
    glutReshapeWindow(512, 512)
    glutDisplayFunc(display)
    glutReshapeFunc(reshape)
    glutKeyboardFunc(keyboard)
    init()
    print(glGetString(GL_VERSION))
    glutMainLoop()
