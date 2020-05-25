// 2017-12-23T16:19+08:00
#ifndef DIRECTED_ACYCLIC_GRAPH_H_INCLUDED
#define DIRECTED_ACYCLIC_GRAPH_H_INCLUDED

#include "../../algutils.h"


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct DirectedAcyclicGraph *DAG;


int DAGInit(DAG *graph, cmp_fn_t match, del_fn_t del);
void DAGFree(DAG *graph);

int DAGInsertVertex(DAG *graph, const void *v);
int DAGInsertEdge(DAG *graph, const void *u, const void *v);
int DAGRemoveVertex(DAG *graph, void **pv);
int DAGRemoveEdge(DAG *graph, void **pu, void **pv);


#ifdef __cplusplus
}
#endif


#endif // DIRECTED_ACYCLIC_GRAPH_H_INCLUDED
