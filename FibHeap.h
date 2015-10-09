#ifndef __FIBHEAP_H_
#define __FIBHEAP_H

#include <iostream>
#include <climits>

typedef struct FibNode
{
	int nodeNum;
	int dist;
	int prevVertex;
	struct FibNode* child; // linked list of children
	struct FibNode* leftSib; // left sibling
	struct FibNode* rightSib; // right sibling
	struct FibNode* parent; // parent node
	int rank; // number of children
	bool marked;
}FibNode;

class FibHeap
{
	private:
		FibNode* root; // linked list of roots
		FibNode* minNode; // points to the node of minimum value
		int trees; //number of trees
		int maxRank; // highest number of child nodes held by a root

	public:
		FibHeap();
		~FibHeap();
		bool isEmpty();
		FibNode* getMin();
		FibNode* createFibNode(int nodeNum, int data);
		void insert(FibNode* newNode);
		FibNode* deleteMin();
		void linkRoots();
		void decreaseKey(FibNode* currNode, int value);
		FibNode* findFibNode(int numNode);
		
		void printHeap();
		void printHeapHelper(FibNode* currNode);
};

#endif
