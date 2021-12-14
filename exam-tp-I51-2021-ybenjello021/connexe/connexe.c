#include "connexe.h"
int * track;
list_t * comp_arr;
int nb_of_components(graph g) {
    track = calloc(g.nbs, sizeof(int));
    int nbc = 0;
    for(int s = 0; s < g.nbs; s++) {
        if (track[s] == false) {
            simple_browse(s, g);
            nbc += 1;
        }
    }
    free(track);
    return nbc;
}
void simple_browse(int s, graph g) {
    track[s] = true;
    for (int t = 0; t < g.nbs; t++) {
        if(g.mat[s][t] && track[t] == false)
            browse(t, g);
    }
}

list_t browse(uint s, graph g) {
    list_t sommets_list = {NULL, NULL};
    list_t temp;
    track[s] = true;
    for (int t = 0; t < g.nbs; t++) {
        if(g.mat[s][t] && track[t] == false) {
            temp = browse(t,g);
            extend(&sommets_list, &temp);
        }
    }
    return sommets_list;
}

list_t * stats_search(graph g, int n_comp) {
  comp_arr = calloc(n_comp, sizeof(list_t)) ;
  track = calloc(g.nbs, sizeof(int));
  int comp_arr_index = 0;
  for(int s = 0; s < g.nbs; s++) {
      if (track[s] == false) {
          comp_arr[comp_arr_index++]=browse(s, g);
      }
  }
  assert(comp_arr_index == n_comp);
  free(track);
  return comp_arr;
}


int edges_component(graph g, list_t sommets) {
  int count = 0;
  list_elm_t *aux = sommets.head;
  while(aux->next != NULL) {
      count += degree(g, aux->val);
      aux = aux->next;
  }
  return count/2;
}

void stats(graph g) {
  int n_of_components = nb_of_components(g);
  printf("Nombre des composantes connexes dans le graph %d\n", n_of_components);
  printf("Numero | un sommet | taille | arretes \n");
  list_t * p_arr = stats_search(g, n_of_components);
  for (int i=0; i < n_of_components; i++) {
    printf("%d, %d, %d, %d\n", i+1, p_arr[i].head->val, length(p_arr[i]),
           edges_component(g, p_arr[i]));
  }
}

int edges_graph(list_t * sommets, graph g, int p) {
  int count = 0;
  for (int i = 0; i < p; i++) {
    count += edges_component(g, sommets[i]);
  }
  return count;
}

int cycle(graph g) {
  n_of_components = nb_of_components(g);
  list_t * p_arr = stats_search(g, n_of_components);
  int m = edges_graph(p_arr, g, n_of_components);
  int n = g.nbs;
  if (m > n - n_of_components) {
    return -1;
  }
  for (int i=0; i < n_of_components; i++) {
    edges = edges_component(p_arr[i]);
    sommets_comp = length(p_arr[i]);
    if (edges == sommets_comp -1) {
      return p_arr[i].head->val;
    }
  }
}
