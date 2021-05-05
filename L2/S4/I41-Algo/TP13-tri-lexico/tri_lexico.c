#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

typedef struct node {
    struct node *next;
    struct node *prec;
    char *str;
} node;

typedef struct list {
    node *head;
    node *queue;
} list;

void print(list L) {
    node *prec = NULL, *curr = L.head;
    printf("[");
    while (curr) {
        printf("%s <-> ", curr->str);
        assert(curr->prec == prec);
        prec = curr;
        curr = curr->next;
    }
    printf("NULL] \n");
}


void push(list *L, char *str) {
    node *new_node = malloc(sizeof(node));
    new_node->str = str;
    new_node->prec = NULL;
    if (L->head == NULL) {
        L->head = new_node;
        new_node->next = NULL;
        L->queue = new_node;
    } else {
        node *tmp = L->head;
        L->head = new_node;
        new_node->next = tmp;
        tmp->prec = new_node;
    }
}


node *pop(list *L) {
    node *head = L->head;
    if (head)
        L->head = head->next;
    if (L->head) 
        L->head->prec = NULL;
    return head;
}

void append(list *L, node *target) {
    if (L->head) {
        node *tmp_queue = L->queue;
        target->next = NULL;
        L->queue = target;
        target->prec = tmp_queue;
        tmp_queue->next = target;
    } else {
        L->head = target;
        L->queue = target;
        target->prec = NULL;
        target->next = NULL;
    }
}

void min_max(list *L, int *min, int *max) {
    *min = strlen(L->head->str), *max = strlen(L->head->str);
    node *curr = L->head;
    int curr_len;
    while (curr) {
        curr_len = strlen(curr->str); 
        if (curr_len > *max)
            *max = curr_len;
        if (curr_len < *min) 
            *min = curr_len;
        curr = curr->next;
    }
}

void concat(list *l, list *l2) {
    if (l->head == NULL) { 
        l->head = l2->head;
        l->queue = l2->queue;
    } else if (l2->head){
        l2->head->prec = l->queue;
        l->queue->next = l2->head;
        l->queue = l2->queue;
    }
}

void push_list(list *l, list *l2) {
    if (l->head == NULL) {
        l->head = l2->head;
        l->queue = l2->queue;
    } else if (l2->head != NULL){
        l2->queue->next = l->head;
        l->head->prec = l2->queue;
        l->head = l2->head;
    }
}

list *partition(list *L,int min,int max) {
    int n = max-min+1, index;
    list *H = malloc(sizeof(list)*(n));
    for (int i = 0; i < n; i++) {
        H[i].head = NULL;
        H[i].queue= NULL;
    }
    node *curr = pop(L);
    while(curr) {
        index = strlen(curr->str);
        append(&H[index-min], curr);
        curr = pop(L);
    }
    return H;
}

void tri_repartition(list *l, int length) {
    list *H = malloc(sizeof(list)*26);
    for (int i = 0; i < 26; i++) {
        H[i].head = NULL;
        H[i].queue = NULL;
    }
    node *curr = pop(l);
    int index;
    while (curr) {
        index = curr->str[length-1]-97; 
        append(&H[index], curr);
        curr = pop(l);
    }
    for (int i = 0; i < 26; i++) {
        concat(l,&H[i]);
    }

}

void tri_lexico(list *l) {
    int min, max;
    min_max(l, &min, &max);
    list *H = partition(l, min, max);
    for (int i = (max-min); i >= 0; i--) {
        push_list(l, &H[i]);
        assert(min+i != 0);
        tri_repartition(l,min+i);

    }
    for (int i = min-1; i > 0; i--) {
        assert(i != 0);
        tri_repartition(l,i);
    }
}

char *random_str_gen(int l) {
    int length = (rand()%l) + 1, key;
    char charset[] = "abcdefghijqlmnopqrstuvwxyz";
    char *str = malloc(sizeof(char)*(length+1));
    for (int i = 0; i < length; i++) {
        key = rand() % 26;
        str[i] = charset[key];
    }
    str[length] = '\0';
    return str;
}

list genlist(int n, int l) {
    list L = {NULL, NULL};
    for(int i = 0; i < n; i++) {
        node *next_node = malloc(sizeof(node));
        next_node->str = random_str_gen(l);
        append(&L, next_node);
    }
    return L;
}
        
int main() {
    srand(1);
    list L = genlist(1000000,35);

    FILE *file = fopen("list2sort.txt","w");
    node *curr = L.head;
    while (curr) {
        fprintf(file, "%s ",curr->str);
        curr = curr->next;
    }
    fclose(file);

    clock_t begin = clock();
    time_t start_time = time(NULL);
    tri_lexico(&L);
    printf("\n--------c tri lexicograpique last %lf %ld----------\n",(double) (clock()-begin)/CLOCKS_PER_SEC, time(NULL) - start_time);

    FILE *file2 = fopen("listsorted.txt","w");
    curr = L.head;
    while (curr) {
        fprintf(file2, "%s ",curr->str);
        curr = curr->next;
    }
    fclose(file2);

    return 0;
}



