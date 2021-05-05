#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define False 0
#define True 1

typedef enum type_ops{num, op, op_un} type_ops;

typedef struct token {
    type_ops type;

    float num;
    char op;
} token;

typedef struct node {
    float num;
    struct node *next;
} node;

int is_dot_in_str(char *str) {
    int i = 0, flag = True;
    while (str[i] != '\0' && flag) {
        if (str[i] == '.') 
            flag = False;
        i++;
    }
    return !flag;
}

token str2token(char *str) {
    token new;
    printf("%s %c\n",str,str[0]);
    if (is_dot_in_str(str)) {
        new.num = atof(str);
        new.type = num;
    } else if (isdigit(str[0])) {
        new.num = atof(str);
        new.type = num;
    } else if (str[0] == '_'){
        new.op = str[0];
        new.type = op_un;
    } else {
        printf("%c\n",str[0]);
        new.op = str[0];
        new.type = op;
    }
    return new;
}

token* argv2token(char **argv, int n) {
    token *arr_token = malloc(sizeof(token)*(n));
    for (int i = 0; i < n; i++) {
        arr_token[i] = str2token(argv[i+1]);
    }
    return arr_token;
}

void print_token_arr(token *arr, int n) {
    printf("[");
    for (int i = 0;  i < (n-1); i++) {
        if (arr[i].type == num) 
            printf("%f,", arr[i].num);
        else
            printf("%c,",arr[i].op);
    }
    printf("%c]\n",arr[n-1].op);
}

void empiler(node **head, float num) {
    node *new = malloc(sizeof(node));
    new->num = num;
    new->next = *head;
    *head = new;
}

float depiler(node **head) {
    float tmp = (*head)->num;
    node *new_head = (*head)->next;
    free(*head);
    *head = new_head;
}

void print_pile(node *head) {
    printf(" ________\n");
    while (head) {
        printf("|%f|\n", head->num);
        head = head->next;
    }
    printf(" ________\n\n\n");
}

float operation(float x, float y, char op) {
    float res;
    switch (op) {
        case '_':
            res = x*-1;
            break;
        case '/':
            res = x/y;
            break;
        case '*':
            res = x*y;
            break;
        case '-':
            res = x-y;
            break;
        case '+': 
            res = x+y;
            break;
    }
    return res;
}

float eval(token *arr, int n) {
    node *head_pile = NULL;
    float x,y;
    for(int i = 0; i < n; i++) {
        if (arr[i].type == num) 
            empiler(&head_pile, arr[i].num);
        else if (arr[i].type == op_un) {
            x = depiler(&head_pile);
            empiler(&head_pile, operation(x,0,'_'));
        } else {
            y = depiler(&head_pile);
            x = depiler(&head_pile);
            empiler(&head_pile,operation(x,y,arr[i].op));
        }
        print_pile(head_pile);
    }
    return depiler(&head_pile);
}



int main(int argc, char **argv) {
    token *token_arr = argv2token(argv, argc-1); 
    print_token_arr(token_arr, argc-1);
    float tmp = eval(token_arr, argc-1);
    printf("%f\n", tmp);
}





