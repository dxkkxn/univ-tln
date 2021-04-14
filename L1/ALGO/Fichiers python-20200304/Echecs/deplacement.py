
def cases_fou(col,lig):
    c=col+1
    l=lig+1
    L=[]
    while 0<=c<=7 and 0<=l<=7:
        L+=[(c,l)]
        c+=1
        l+=1
    c=col+1
    l=lig-1
    while 0<=c<=7 and 0<=l<=7:
        L+=[(c,l)]
        c+=1
        l=l-1
    c=col-1
    l=lig+1
    while 0<=c<=7 and 0<=l<=7:
        L+=[(c,l)]
        c=c-1
        l+=1
    c=col-1
    l=lig-1
    while 0<=c<=7 and 0<=l<=7:
        L+=[(c,l)]
        c=c-1
        l=l-1
    return L
def cases_tour(col,lig):
    L=[]
    c=col+1
    l=lig
    while c<=7:
        L+=[(c,l)]
        c+=1
    c=col-1
    l=lig
    while c>=0:
        L+=[(c,l)]
        c=c-1
    c=col
    l=lig+1
    while l<=7:
        L+=[(c,l)]
        l+=1
    c=col
    l=lig-1
    while l>=0:
        L+=[(c,l)]
        l=l-1
    return L



    """Retourne la liste des indices (col,lig) des cases où peut se
    déplacer une tour positionnée sur la case (col, lig)

    Ex: tour en (5,3)
    - - - - - - - - - -
    |           x     |
    |           x     |
    |           x     |
    | x x x x x T x x |
    |           x     |
    |           x     |
    |           x     |
    |           x     |
    - - - - - - - - - -

    """


def cases_reine(col,lig):
    L=[]
    L+=cases_fou(col,lig)
    L+=cases_tour(col,lig)

    """Retourne la liste des indices (col,lig) des cases où peut se
    déplacer un fou positionnée sur la case (col, lig)

    Ex: dame en (6,1)
    - - - - - - - - - -
    |           x x x |
    | x x x x x x D x |
    |           x x x |
    |         x   x   |
    |       x     x   |
    |     x       x   |
    |   x         x   |
    | x           x   |
    - - - - - - - - - -

    """
    return L

def cases_roi(col,lig):
    L=[]
    c=col
    l=lig
    if  0<=c<=7 and 0<=l-1<=7:
        L+=[(c,l-1)]
    if  0<=c<=7 and 0<=l+1<=7:
        L+=[(c,l+1)]
    if  0<=c-1<=7 and 0<=l<=7:
        L+=[(c-1,l)]
    if  0<=c+1<=7 and 0<=l<=7:
        L+=[(c+1,l)]
    if  0<=c-1<=7 and 0<=l-1<=7:
        L+=[(c-1,l-1)]
    if  0<=c-1<=7 and 0<=l+1<=7:
        L+=[(c-1,l+1)]
    if  0<=c+1<=7 and 0<=l-1<=7:
        L+=[(c+1,l-1)]
    if  0<=c+1<=7 and 0<=l+1<=7:
        L+=[(c+1,l+1)]
    return L

def cases_cavalier(col,lig):
    L=[]
    val=[[1,2],[-1,2],[2,-1],[2,+1],[-2,+1],[-2,-1],[1,-2],[-1,-2],[-2,+1],[-2,-1]]
    for i in val:
        if 0<=col+i[0]<=7 and 0<=lig+i[1]<=7:
            L+=[(col+i[0],lig+i[1])]
    return L

    """Retourne la liste des indices (col,lig) des cases où peut se
    déplacer un fou positionné sur la case (col, lig)

    Ex: cavalier en (3,3)
    - - - - - - - - - -
    |                 |
    |     x   x       |
    |   x       x     |
    |       C         |
    |   x       x     |
    |     x   x       |
    |                 |
    |                 |
    - - - - - - - - - -

    """
    return []

def cases_pion(col,lig):
    L=[]
    if lig==6:
        L=[(col,lig-1),(col,lig-2)]
    else:
        if 0<=lig-1<=7:
            L=[(col,lig-1)]
    return L
    """Retourne la liste des indices (col,lig) des cases où peut se
    déplacer un fou positionné sur la case (col, lig)

    Ex: pions en (1,6) et (5,3)
    - - - - - - - - - -
    |                 |
    |                 |
    |           x     |
    |           P     |
    |   x             |
    |   x             |
    |   P             |
    |                 |
    - - - - - - - - - -

    """
