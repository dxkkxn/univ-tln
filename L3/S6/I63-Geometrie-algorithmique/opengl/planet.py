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
year, day = 0, 0
quadric = None

############################################################## # 

blue = [1.0, 1.0, 1.0, 1.0]
yellow = [1, 1, 0, 1]
def init():
    global quadric
    # clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0)
    diffuse = [0.7, 0.7, 0.7, 1.0]
    specular = [0.001, 0.001, 0.001, 1.0]
    pos = [1, 1, 1, 0]
#    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white)
#    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, 9.0) 

    glEnable(GL_LIGHTING)
    glEnable(GL_COLOR_MATERIAL)

    glEnable(GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_POSITION, pos)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse)
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular)
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1)
    glShadeModel(GL_SMOOTH)
#    # definition of a quadric
    quadric = gluNewQuadric()
    # specify draw syle for quadrics
    gluQuadricDrawStyle(quadric, GLU_FILL)


def display():
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glColor4f (1.0, 1.0, 1.0, 1.0)

    glPushMatrix()
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow)
    gluSphere(quadric, 1.0, 20, 16)
    glRotatef(year, 0.0, 1.0, 0.0)
    glTranslatef(2.0, 0.0, 0.0)
    glRotatef(day, 0.0, 1.0, 0.0)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue)
    gluSphere(quadric, 0.2, 10, 8)
    glPopMatrix()

    glutSwapBuffers()

def reshape(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    if width <= height:
        glOrtho(-2.5, 2.5, -2.5*height/width, 2.5*height/width, -10.0, 10.0)
    else:
        glOrtho(-2.5*width/height, 2.5*width/height, -2.5, 2.5, -10.0, 10.0)
    glMatrixMode(GL_MODELVIEW)

def keyboard(key, x, y):
    global day, year
    if key == b'j':
        day = (day + 10) % 360
#    elif key == 'J':
#        day = (day - 10) % 360
    elif key == b'a':
        year = (year + 5) % 360
#    elif key == 'A':
#        year = (year - 5) % 360
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH | GLUT_LUMINANCE)

    # creation of top-level window
    WIN = glutCreateWindow('planet')

    glutReshapeWindow(512,512)

    glutReshapeFunc(reshape)
    glutDisplayFunc(display)
    glutKeyboardFunc(keyboard)

    init()

    glutMainLoop()
