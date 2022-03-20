#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

###############################################################
# portage de planet.c

from OpenGL.GL import *  # exception car prefixe systematique
from OpenGL.GLU import *
from OpenGL.GLUT import *
from math import sin, cos
import sys

###############################################################
# variables globales
year, day, hour,x_pos, y_pos, z_pos = 0, 0, 0, 0, 0, 5
quadric = None
DISPLAY_GRID = False

############################################################## # 
blue = []

def init():
    global quadric
    # clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0)
    diffuse = [0.7, 0.7, 0.7, 1.0]
    specular = [0.001, 0.001, 0.001, 1.0]
    pos = [1, 1, 1, 0]
#    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white)
#    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, 9.0) 

    #glEnable(GL_COLOR_MATERIAL)
    glEnable(GL_DEPTH_TEST)
    glDepthFunc(GL_LESS)
    glClearDepth(1)

    glEnable(GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_POSITION, pos)
    glEnable(GL_LIGHTING)
#    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse)
#    glLightfv(GL_LIGHT0, GL_SPECULAR, specular)
#    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1)
    glShadeModel(GL_FLAT)
#    # definition of a quadric
    quadric = gluNewQuadric()
    # specify draw syle for quadrics
    gluQuadricDrawStyle(quadric, GLU_FILL)

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

def display():
    #glClearDepth(0)
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    #glColor4i (252, 236, 10, 255)

    blue = [1.0, 1.0, 1.0, 1.0]
    yellow = [0.7, .4, 0, 1]
    glPushMatrix()
    gluLookAt(x_pos, y_pos, z_pos, #pos camera
              0, 0, 0, # look at
              0, 1, 0) #up vector

    if DISPLAY_GRID :
        display_grid()

    #glPushMatrix()
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, [1.0, 1.0, 0, 1.0])
    # glTranslate(2, 2, 2)
    gluSphere(quadric, 1.0, 20, 16)
    glRotatef(year, 0.0, 1.0, 0.0)
    glTranslatef(2.0, 0.0, 0.0)
    glRotatef(day, 0.0, 1.0, 0.0)

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, [91/255, 123/255, 227/255, 1.0])
    gluSphere(quadric, 0.2, 10, 8)

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, [255/255, 255/255, 255/255, 1.0])
    glRotatef(hour, 0.0, 1.0, 0.0)
    glTranslatef(0.5, 0.0, 0.0)
    gluSphere(quadric, 0.1, 10, 8)

    glPopMatrix()

    glutSwapBuffers()
    print(x_pos, y_pos, z_pos)
    #glFlush()

def reshape(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    print(width, height)
    #if width <= height:
        #glOrtho(-2.5, 2.5, -2.5*height/width, 2.5*height/width, -1000.0, 1000.0)
    gluPerspective(90, width/height, 1, 10000)
    # else:
    #     glOrtho(-2.5*width/height, 2.5*width/height, -2.5, 2.5, -10.0, 10.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

def keyboard(key, x, y):
    global day, year, hour, x_pos, y_pos, z_pos, DISPLAY_GRID
    if key == b'd':
        day = (day + 10) % 360
#    elif key == 'J':
#        day = (day - 10) % 360
    elif key == b'y':
        year = (year + 5) % 360

    elif key == b'w':
        hour = (hour + 10) % 360

    elif key == b'a':
        year = (year + 1) % 360
        hour = (hour + 20) % 360
        day = (day + 10) % 360
    elif key == b'g':
        if  DISPLAY_GRID == True:
            DISPLAY_GRID = False
        else :
            DISPLAY_GRID = True
#    elif key == 'A':
#        year = (year - 5) % 360
    # elif key == b'x':
    #     x_pos+=1
    # elif key == b'X':
    #     x_pos-=1

    # elif key == b'y':
    #     y_pos+= 1
    # elif key == b'Y':
    #     y_pos-= 1

    # elif key == b'z':
    #     z_pos += 1
    # elif key == b'Z':
    #     z_pos -= 1
    elif key == b'z':
        z_pos+=1
    elif key == b'Z':
        z_pos-=1
    elif key == b'h':
        #x_pos+=1
        #z_pos -=1
        radius = 10
        x, z = x_pos, z_pos
        x_pos = x * cos(0.1) - z * sin(0.1)
        z_pos = z * cos(0.1) + x * sin(0.1)
    elif key == b'l':
        #x_pos-=1
        #z_pos-=1
        radius = 10
        x, z = x_pos, z_pos
        x_pos = x * cos(-0.1) - z * sin(-0.1)
        z_pos = z * cos(-0.1) + x * sin(-0.1)
    elif key == b'j':
        #y_pos+=1
        #z_pos-=1
        y, z = y_pos, z_pos
        y_pos = y * cos(0.1) - z * sin(0.1)
        z_pos = z * cos(0.1) + y * sin(0.1)
    elif key == b'k':
        #y_pos-=1
        #z_pos-=1
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
    # initialization GLUT library
    glutInit()
    # initialization display mode RGBA mode and double buffered window
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA |GLUT_DEPTH )

    # creation of top-level window
    WIN = glutCreateWindow('planet')

    glutReshapeWindow(512, 512)

    glutReshapeFunc(reshape)
    glutDisplayFunc(display)
    glutKeyboardFunc(keyboard)

    init()

    glutMainLoop()
