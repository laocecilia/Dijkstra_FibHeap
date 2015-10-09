#include "AdjacencyList.h"

using namespace std;

AdjacencyList::AdjacencyList(int totalVertices, int totalEdges)
{
	numVertices = totalVertices;
	numEdges = totalEdges;
	list = new adjListNode*[numVertices];
	int i;
	for (i=0; i<numVertices; i++)
		list[i] = nullptr;
}

AdjacencyList::~AdjacencyList()
{
	if(list != nullptr)
		delete list;
}

adjListNode* AdjacencyList::createNewAdjListNode(int from, int to, int weight)
{
	/* Create new edge pointer */
	edge* newEdge = new edge;
	newEdge->from = from;
	newEdge->to = to;
	newEdge->weight = weight;
	if (from==to)
		newEdge->dist = 0;
	else
		newEdge->dist = INT_MAX;

	/* Create new adjacency list node */
	adjListNode* newNode = new adjListNode;
	newNode->edgeInfo = newEdge;
	newNode->next = nullptr;

	return newNode;
}

void AdjacencyList::addAdjList(int from, int to, int weight)
{
	/* Create new adjacency list node */
	adjListNode* newNode = createNewAdjListNode(from, to, weight);

	/* Add to adjacency list */
	adjListNode* temp = list[from];
	if (temp == nullptr)
		list[from] = newNode;
	else
	{
		while (temp->next != nullptr)
			temp = temp->next;
		temp->next = newNode;
	}
}

adjListNode* AdjacencyList::getAdjListNode(int index)
{
	return list[index];
}


void AdjacencyList::printAdjList()
{
	int i;
	adjListNode *temp;

	for(i=0; i<numVertices; i++)
	{
		temp = list[i];
		if(temp != nullptr)
		{
			std::cout << i;
			while (temp != nullptr)
			{
				std::cout << "--> " << temp->edgeInfo->to << "(" << temp->edgeInfo->weight << ")";
				temp = temp->next;
			}
		}
		std::cout << std::endl;
	}
}
