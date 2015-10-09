#include "Dijkstra.h"

AdjacencyList* createAdjList(struct Graph* graph, int V, int E)
{
	/* Declare variables */
	int i=0;

	/* Initialize adjacency list to store graph information */
	AdjacencyList *adjList = new AdjacencyList(V, E);

	for(i=0; i<E; i++)
	{
		adjList->addAdjList(graph->edge[i].pos, graph->edge[i].dest, graph->edge[i].weight);

	}
	adjList->printAdjList();
	return adjList;
}


edge** dijkstra(AdjacencyList *adjList, int totalVertices, int start)
{
	/* Variables */
	FibHeap heap; // minHeap as the priority queue
	edge** output = new edge*[totalVertices]; // output array to hold info of shortest distances */
	FibNode* newNode;
	FibNode* minNode;
	FibNode* findNode;
	edge* newEdge;
	adjListNode* currAdjListNode;
	int i;


	/* Clear output array*/
	for(i=0; i<totalVertices;i++)
	{
		output[i] = nullptr;
	}

	/* Create new edge for start point */
	newEdge = new edge;
	newEdge->from = start;
	newEdge->to = start;
	newEdge->weight = 0;
	newEdge->dist = 0;
	output[start] = newEdge;
	
	/* Create fibNode and insert into minHeap for every vertex */
	for(i=0; i<totalVertices; i++)
	{
		/* Create fibNode */
		if (i == start)
			newNode = heap.createFibNode(i,0);
		else
			newNode = heap.createFibNode(i, INT_MAX);

		/* Add to minHeap */
		heap.insert(newNode);
	}
	
	while(!heap.isEmpty())
	{
		minNode = heap.deleteMin(); // u = EXTRACT-MIN{Q}
		/* Create new edge to put into output */
		newEdge = new edge;
		newEdge->from = minNode->prevVertex;
		newEdge->to = minNode->nodeNum;
		newEdge->weight = -1;
		newEdge->dist = minNode->dist;
		output[minNode->nodeNum] = newEdge; // S= S U {u}

		/* Traverse through every vertex of minNode and relax the edges*/
		currAdjListNode = adjList->getAdjListNode(minNode->nodeNum);
		while(currAdjListNode != nullptr)
		{
			findNode = heap.findFibNode(currAdjListNode->edgeInfo->to); // find vertex in priority queue
			if(findNode != nullptr) // vertex is still in priority queue
			{
				/* Relax the edge */
				if(findNode->dist > (minNode->dist + currAdjListNode->edgeInfo->weight))
				{
					heap.decreaseKey(findNode, (minNode->dist + currAdjListNode->edgeInfo->weight));
					findNode->prevVertex = minNode->nodeNum;
				}
			}
			currAdjListNode = currAdjListNode->next;
		}

		delete minNode;
	}

	return output;

}


contestant** dijkstra2(AdjacencyList *adjList, int totalVertices, int start)
{
	/* Variables */
	contestant** output = new contestant*[totalVertices]; // output array to hold info of shortest distances */
	contestant* newNode;
	contestant* minNode;
	contestant* findNode;
	contestant* newContestant;
	adjListNode* currAdjListNode;
	int i;


	/* Clear output array*/
	for(i=0; i<totalVertices;i++)
	{
		output[i] = nullptr;
	}

	/* Create new edge for start point */
	newContestant = new contestant;
	newContestant->id = start;
	newContestant->score = start;
	output[start] = newContestant;
	
	/* Add every vertex to heap */
	for(i=0; i<totalVertices; i++)
	{
		/* Create fibNode */
		if (i == start)
			insertContestant(i+1,0);
		else
			insertContestant(i+1,INT_MAX);
	}

	while(!isEmpty())
	{
		contestant* minNode = eliminateWeakest(); // u = EXTRACT-MIN{Q}
		/* Create new edge to put into output */
		newContestant = new contestant;
		newContestant->id= minNode->id-1;
		newContestant->score = minNode->score;
		output[minNode->id-1] = newContestant; // S= S U {u}

		/* Traverse through every vertex of minNode and relax the edges*/
		currAdjListNode = adjList->getAdjListNode(minNode->id-1);
		while(currAdjListNode != nullptr)
		{
			findNode = showLocation(currAdjListNode->edgeInfo->to+1); // check if vertex is present in heap
			if(findNode != nullptr) // vertex is still in priority queue
			{
				/* Relax the edge */
				if(findNode->score > (minNode->score + currAdjListNode->edgeInfo->weight))
				{
					losePoints(findNode->id, (minNode->score + currAdjListNode->edgeInfo->weight));
				}
			}
			currAdjListNode = currAdjListNode->next;
		}

		delete minNode;
	}
	return output;

} /* End Dijkstra2 */

void printOutput(edge** output, int size)
{
	int i;

	std::cout << "OUTPUT:" << std::endl;
	for(i=0; i<size; i++)
	{
		std::cout << output[i]->from << "->" << output[i]->to << ", dist= " << output[i]->dist << std::endl;
	}
}

void printDijkstra2(contestant** output, int size)
{
	int i;
	std::cout << "DIJKSTRA2 OUTPUT:" << std::endl;
	for (i=0; i<size; i++)
	{
		std::cout << output[i]->id << ", dist= " << output[i]->score << std::endl;
	}
}