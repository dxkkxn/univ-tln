from pocketgl import *
init_window ("premiers pas",500,500)
a=0

for b in range(50):
    current_color(255-b*5,255-b*5,255-b*5)
    box(0,10*b,500,10*b+10)
main_loop()
