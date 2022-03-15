#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

###############################################################
# portage de planet.c

from OpenGL.GL import *  # exception car prefixe systematique
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys

###############################################################
# variables globales
year, day, hour,x_pos, y_pos, z_pos = 0, 0, 0, 5, 5, 5
quadric = None

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
    glShadeModel(GL_SMOOTH)
#    # definition of a quadric
    quadric = gluNewQuadric()
    # specify draw syle for quadrics
    gluQuadricDrawStyle(quadric, GLU_FILL)


def display():
    #glClearDepth(0)
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    #glColor4i (252, 236, 10, 255)

    blue = [1.0, 1.0, 1.0, 1.0]
    yellow = [0.7, .4, 0, 1]
    glPushMatrix()
    gluLookAt(x_pos, y_pos, z_pos, #pos camera 
              -5+x_pos, -5+y_pos, -5+z_pos, # look at
              0, 1, 0) #up vector
    #glPushMatrix()
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, [1.0, 1.0, 0, 1.0])
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
    #glFlush()

def reshape(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    if width <= height:
        #glOrtho(-2.5, 2.5, -2.5*height/width, 2.5*height/width, -1000.0, 1000.0)
        gluPerspective(100, width/height, 1, 1000)
    else:
        glOrtho(-2.5*width/height, 2.5*width/height, -2.5, 2.5, -10.0, 10.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

def keyboard(key, x, y):
    global day, year, hour, x_pos, y_pos, z_pos
    if key == b'j':
        day = (day + 10) % 360
#    elif key == 'J':
#        day = (day - 10) % 360
    elif key == b'a':
        year = (year + 5) % 360

    elif key == b'h':
        hour = (hour + 10) % 360

    elif key == b't':
        year = (year + 1) % 360
        hour = (hour + 20) % 360
        day = (day + 10) % 360
#    elif key == 'A':
#        year = (year - 5) % 360
    elif key == b'x':
        x_pos+=1
    elif key == b'X':
        x_pos-=1

    elif key == b'y':
        y_pos+= 1
    elif key == b'Y':
        y_pos-= 1

    elif key == b'z':
        z_pos += 1
    elif key == b'Z':
        z_pos -= 1
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
