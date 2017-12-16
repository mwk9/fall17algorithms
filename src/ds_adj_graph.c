#include "ds_adj_graph.h"

AdjNode * adjnode_new_node(int dest)
{
	AdjNode * n = NULL;
	n = (AdjNode *)malloc(sizeof(AdjNode));
	if (!n)
	{
		slog("Error: could not allocate memory for a new AdjNode!");
		return NULL;
	}

	memset(n, 0, sizeof(AdjNode));
	n->destination = dest;
	n->next = NULL;
	return n;
}

AdjGraph * adjgraph_new(int numVerts)
{
	AdjGraph * grape = NULL;
	int i = 0;
	grape = (AdjGraph *)malloc(sizeof(AdjGraph));
	if (!grape)
	{
		slog("Error: could not allocate memory for a new AdjGraph!");
		return NULL;
	}
	memset(grape, 0, sizeof(AdjGraph));
	grape->numVertices = numVerts;

	grape->adjacencyList = (AdjList *)malloc(sizeof(AdjList) * numVerts);
	if (!grape->adjacencyList)
	{
		slog("Error: could not allocate memory for a new AdjGraph's adjacency list!");
		free(grape);
		return NULL;
	}
	memset(grape->adjacencyList, 0, sizeof(AdjList) * numVerts);
	
	return grape;
}

AdjGraph * adjgraph_add_edge(AdjGraph * graph, int src, int dest)
{
	AdjNode * new_node = NULL;

	if (!graph)
	{
		slog("Error: cannot add an edge to a null graph");
		return graph;
	}
	if (src < 0 || src > graph->numVertices - 1)
	{
		slog("Error: source node (%i) out of range (%i)", src, graph->numVertices);
		return graph;
	}
	if (dest < 0 || dest > graph->numVertices - 1)
	{
		slog("Error: destination node (%i) out of range (%i)", dest, graph->numVertices);
		return graph;
	}

	new_node = adjnode_new_node(dest);
	if (!new_node)
	{
		//slog in adj_new_node
		return graph;
	}
	new_node->destination = dest;
	new_node->next = graph->adjacencyList[src].head;
	graph->adjacencyList[src].head = new_node;

	return graph;
}

void adjgraph_print(AdjGraph * graph)
{
	int i = 0;
	AdjNode * iterator = NULL;

	if (!graph)
	{
		slog("Error: cannot print a null graph!");
		return;
	}

	slog("\n\nCurrent info of graph:\n==================================");
	for (i = 0; i < graph->numVertices; i++)
	{
		iterator = graph->adjacencyList[i].head;
		while (iterator != NULL)
		{
			printf("(%d -> %d)\t", i, iterator->destination);
			iterator = iterator->next;
		}
		printf("\n");
	}
}
