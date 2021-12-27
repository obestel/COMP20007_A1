/*
graph.c

Set of vertices and edges implementation.

Implementations for helper functions for graph construction and manipulation.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "graph.h"
#include "utils.h"
#include "pq.h"

#define INITIALEDGES 32

struct edge;

/* Definition of a graph. */
struct graph {
  int numVertices;
  int numEdges;
  int allocedEdges;
  struct edge **edgeList;
};

/* Definition of an edge. */
struct edge {
  int start;
  int end;
  int cost;
};

struct graph *newGraph(int numVertices){
  struct graph *g = (struct graph *) malloc(sizeof(struct graph));
  assert(g);
  /* Initialise edges. */
  g->numVertices = numVertices;
  g->numEdges = 0;
  g->allocedEdges = 0;
  g->edgeList = NULL;
  return g;
}

/* Adds an edge to the given graph. */
void addEdge(struct graph *g, int start, int end, int cost){
  assert(g);
  struct edge *newEdge = NULL;
  /* Check we have enough space for the new edge. */
  if((g->numEdges + 1) > g->allocedEdges){
    if(g->allocedEdges == 0){
      g->allocedEdges = INITIALEDGES;
    } else {
      (g->allocedEdges) *= 2;
    }
    g->edgeList = (struct edge **) realloc(g->edgeList,
      sizeof(struct edge *) * g->allocedEdges);
    assert(g->edgeList);
  }

  /* Create the edge */
  newEdge = (struct edge *) malloc(sizeof(struct edge));
  assert(newEdge);
  newEdge->start = start;
  newEdge->end = end;
  newEdge->cost = cost;

  /* Add the edge to the list of edges. */
  g->edgeList[g->numEdges] = newEdge;
  (g->numEdges)++;
}

/* Frees all memory used by graph. */
void freeGraph(struct graph *g){
  int i;
  for(i = 0; i < g->numEdges; i++){
    free((g->edgeList)[i]);
  }
  if(g->edgeList){
    free(g->edgeList);
  }
  free(g);
}

//struct solution *graphSolve(struct graph *g, enum problemPart part,
//  int antennaCost, int numHouses){
//  struct solution *solution = (struct solution *)
//    malloc(sizeof(struct solution));
//  assert(solution);
//  if(part == PART_A){
//    /* IMPLEMENT 2A SOLUTION HERE */
//      struct pq *pq ;
//      int cost = 0 ;
//      struct edge *visited[numHouses] ;
//      struct edge *min;
//      pq = newPQ() ;
//      int m;
//      int p ;
//      int i=0 , j  ;
//      int in = 0 ;
////      visited[0]->start = 0;
//
//
//      for (i = 0; i <= 0 ;i++){
//
//        for (j = 0; j <= 9; j++){
//
//          for(m = 0; m <= 9; m++){
//
//              if(g->edgeList[j] != visited[m]){
//            in = 1 ;}
//          }
//            if (in == 1){
//                 enqueue(pq, g->edgeList[j],g->edgeList[j]->cost ) ;}
//                in = 0 ;
//              }
//
//          min = deletemin(pq) ;
//          cost += min->cost ;
//          visited[i] = min ;
//      }
//
//    solution->antennaTotal = numHouses*antennaCost;
//    solution->cableTotal = cost;
//  } else {
//    /* IMPLEMENT 2C SOLUTION HERE */
//    solution->mixedTotal = 0;
//  }
//  return solution;
//}

struct solution *graphSolve(struct graph *g, enum problemPart part,
  int antennaCost, int numHouses){
  struct solution *solution = (struct solution *)
    malloc(sizeof(struct solution));
  assert(solution);
  if(part == PART_A){
    /* IMPLEMENT 2A SOLUTION HERE */
      
      struct edge *min;
      struct pq *pq ;
      pq = newPQ() ;
      int v2 [numHouses+1];
      int cost = 0 ;
      int i, j ,m, p, k, z ;
      int edge_list_length ;
      int in2 = 0 ;
      int in3 = 0;
      int test = 0 ;
      int measure =0 ;
      edge_list_length = g->numEdges;
      
      
      for(z = 0 ; z <=numHouses; z++){
          v2[z] = 0; }
      
      for (i = 0; i <= numHouses-1 ;i++){
      
        for (j = 0; j <= edge_list_length - 1 ; j++){
        
           for (p=0; p<numHouses; p++) {
              if(g->edgeList[j]->end == v2[p]){
                  in2 = 1 ;}
              if(g->edgeList[j]->start == v2[p] ){
                  in3 = 1 ;}
              }
            
            if( in3 + in2   == 1){
                enqueue(pq, g->edgeList[j],g->edgeList[j]->cost );
                measure +=1 ;}
                
            in2 = 0;
            in3 = 0;
        }

          min = deletemin(pq) ;
          cost += min->cost ;
          
          for(k = 0; k <=numHouses - 1; k++){
              if(min->end == v2[k]){
                 test = 1 ;}}
          
          if(test == 1){
              v2[i+1] = min->start;
          } else{
              v2[i+1] = min->end ;}
          
          for(m = 0; m<measure; m++){
              deletemin(pq) ;}
          
          test = 0 ;
          measure = 0 ;
          
      }
    
    solution->antennaTotal = numHouses*antennaCost;
    solution->cableTotal = cost;
      
  } else {
    /* IMPLEMENT 2C SOLUTION HERE */
      struct edge *min;
      struct pq *pq ;
      pq = newPQ() ;
      int v2 [numHouses+1] ;
      int cost = 0 ;
      int i, j ,m, p, k, z ;
      int edge_list_length ;
      int in2 = 0 ;
      int in3 = 0;
      int test = 0 ;
      int measure =0 ;
      edge_list_length = g->numEdges;
      
      
      for(z = 0 ; z <=numHouses; z++){
          v2[z] = 0; }
      
      for (i = 0; i <= numHouses-1 ;i++){
      
        for (j = 0; j <= edge_list_length - 1 ; j++){
        
           for (p=0; p<numHouses; p++) {
              if(g->edgeList[j]->end == v2[p]){
                  in2 = 1 ;}
              if(g->edgeList[j]->start == v2[p] ){
                  in3 = 1 ;}
              }
            
            if( in3 + in2   == 1){
                enqueue(pq, g->edgeList[j],g->edgeList[j]->cost );
                measure +=1 ;}
            
            in2 = 0;
            in3 = 0;
        }

          min = deletemin(pq) ;
          if(min->cost > antennaCost){
              cost += antennaCost;
          } else {
              cost += min->cost ;}
          
          for(k = 0; k <=numHouses - 1; k++){
              if(min->end == v2[k]){
                 test = 1 ;}
          }
          
          if(test == 1){
              v2[i+1] = min->start;
          } else{
              v2[i+1] = min->end ;}
         
          
          for(m = 0; m<measure; m++){
              deletemin(pq) ;}
          
          test = 0 ;
          measure = 0 ;
          
      }
      
      
    solution->mixedTotal = cost;
  }
  return solution;
}





