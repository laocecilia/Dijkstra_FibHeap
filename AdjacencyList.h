#ifndef __ADJACENCYLIST_H_
#define __ADJACENCYLIST_H_

#include <iostream>
#include <climits>

typedef struct edge
{
	int from;
	int to;
	int weight;
	int dist;
}edge;

typedef struct adjListNode
{
	edge* edgeInfo;
	struct adjListNode* next;
}adjListNode;

class AdjacencyList
{
	private:
		int numVertices;
		int numEdges;
		adjListNode** list; 
	
	public:
		AdjacencyList(int totalVertices, int totalEdges);
		~AdjacencyList();
		adjListNode* createNewAdjListNode(int from, int to, int weight);
		void addAdjList(int from, int to, int weight);
		adjListNode* getAdjListNode(int index);
		void printAdjList();
};

#endif
