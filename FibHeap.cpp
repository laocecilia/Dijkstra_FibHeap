#include "FibHeap.h"

using namespace std;

FibHeap::FibHeap()
{
	root = nullptr;
	minNode = nullptr;
	trees = 0;
	maxRank = 0;
}

FibHeap::~FibHeap()
{
	if(root != nullptr)
		delete root;

	root = nullptr;
	minNode = nullptr;

}

bool FibHeap::isEmpty()
{
	if (root == nullptr)
		return true;
	return false;
}

FibNode* FibHeap::getMin()
{
	return minNode;
}

FibNode* FibHeap::createFibNode(int nodeNum, int dist)
{
	FibNode* newNode = new FibNode;
	newNode->nodeNum = nodeNum;
	newNode->dist = dist;
	newNode->prevVertex = 0;
	newNode->child = nullptr;
	newNode->leftSib = nullptr;
	newNode->rightSib = nullptr;
	newNode->parent = nullptr;
	newNode->rank = 0;
	newNode->marked = 0;

	return newNode;
}

void FibHeap::insert(FibNode* newNode)
{
	if(root == nullptr)
	{
		root = newNode;
		minNode = newNode;
		trees = 1;
	}
	else
	{
		/* Update root linked list */
		FibNode* temp = root;
		root = newNode;
		root->rightSib = temp;
		temp->leftSib = root;
		
		/* Update minNode if necessary */
		if(newNode->dist < minNode->dist)
		{
			minNode = newNode;
		}
		
		/* Update number of trees */
		trees++;
	}
}

FibNode* FibHeap::deleteMin()
{
	/* Variables */
	FibNode* deleteNode = minNode; // node to delete
	FibNode* childNode = minNode->child; // children nodes
	FibNode* addToRoot = childNode; // node to add to root linked list
	FibNode* temp; // temp pointer

	//std::cout << "---------minNode delete= " << deleteNode->nodeNum << std::endl;
	//printHeap();

	/* Check if minNode is deleteNode */
	if (minNode == deleteNode)
	{	
		if (minNode == root)
			root = root->rightSib;
		else
			minNode == root;
	}

	/* Remove minNode from root linked list */
	if(deleteNode->leftSib != nullptr)
		deleteNode->leftSib->rightSib = deleteNode->rightSib;
	if(deleteNode->rightSib != nullptr)
		deleteNode->rightSib->leftSib = deleteNode->leftSib;
	trees--; // Decrease number of trees on root linked list

	/* Update root if necessary */
	if (deleteNode == root)
		root == nullptr;

	/* Add children to root linked list */
	while(childNode != nullptr)
	{
		addToRoot = childNode;
		childNode = childNode->rightSib;

		/* add node to beginning of root linked list */
		temp = root;
		root = addToRoot;
		root->leftSib = nullptr;
		root->rightSib = temp;
		root->parent = nullptr;
		if (temp != nullptr)
			temp->leftSib = root;
		trees++; // increment number of trees in root linked list
	}

	/* Temporarily make root the minNode */
	minNode = root; // will be updated in linkRoots

	/* Isolate deleteNode and delete it */
	deleteNode->child = nullptr;
	deleteNode->leftSib = nullptr;
	deleteNode->rightSib = nullptr;

	/* linkRoots */
	linkRoots();

	//std::cout << "-------------------After linkRoots" << std::endl;
	//printHeap();
	
	return deleteNode;
}

void FibHeap::linkRoots()
{
	/* Variables */
	FibNode* rankArray[maxRank+trees]; //array of rank pointers
	FibNode* currRoot = root; // start traversal on first element in root linked list
	FibNode* current = nullptr;
	FibNode* temp = nullptr;
	FibNode* parentTree;
	FibNode* childTree;
	int i = 0;

	/* Clear rankArray*/
	for(i=0; i<maxRank+trees; i++)
		rankArray[i] = nullptr;
	
	/* Reset maxRank and recalculate through while loop below */
	maxRank = 0;

	/* Traverse through root linked list */
	while (currRoot != nullptr)
	{
		/* Add roots to rankArray */
		if (rankArray[currRoot->rank] == nullptr)
		{
			rankArray[currRoot->rank] = currRoot;
		
			/* Update maxRank if necessary */
			if (currRoot->rank > maxRank)
				maxRank = currRoot-> rank;

			/* Increment to next node in root linked list */
			currRoot = currRoot->rightSib;
		}
		/* Consolidate trees of same rank */
		else
		{
			/* Save pointer to current tree and the next root to compare */
			current = currRoot;
			currRoot = currRoot->rightSib;
			
			/* Keep combining trees of the same rank */
			while(rankArray[current->rank] != nullptr)
			{
				/* Determine which is the parent tree and which is child tree */
				if ((rankArray[current->rank]->dist) < current->dist)
				{
					parentTree = rankArray[current->rank];
					childTree = current;
				}
				else
				{
					parentTree = current;
					childTree = rankArray[current->rank];

					if(minNode == rankArray[current->rank])
						minNode = current;
				}

				/* Remove tree's link to rankArray */
				rankArray[current->rank] = nullptr;

				/* Update root pointer if necessary */
				if (childTree == root)
					root = childTree->rightSib;

				/* Remove childTree from root linked list */
				if(childTree->leftSib != nullptr)
					childTree->leftSib->rightSib = childTree->rightSib;
				if(childTree->rightSib != nullptr)
					childTree->rightSib->leftSib = childTree->leftSib;
				trees--; // Decrease number of trees in root linked list

				/* Add childTree to parentTree's child linked list*/
				temp = parentTree->child;
				parentTree->child = childTree;
				childTree->rightSib = temp;
				childTree->leftSib = nullptr;
				childTree->parent = parentTree;
				if(temp != nullptr)
					temp->leftSib = childTree;
	
				/* Update parentTree's rank */
				parentTree->rank++;

				/* Update minNode if necessary */
				if((parentTree->dist < minNode->dist) && (parentTree->parent == nullptr))
					minNode = parentTree;

				/* Change current pointer to point to parentTree */
				current = parentTree;
			}

			/* Store consolidated tree into rankArray */
			rankArray[current->rank] = current;

			/* Update maxRank if necessary */
			if (current->rank > maxRank)
				maxRank = current->rank;
		}
	}	
}

void FibHeap::decreaseKey(FibNode* currNode, int value)
{
	/* Variables */
	bool parentMarked = true;
	FibNode* parentNode;
	FibNode* temp;

	/* Check if currNode is valid */
	if (currNode == nullptr)
		return;

	/* Decrease value in node */
	currNode->dist = value;

	/* Update if minnode */
	if (currNode->dist < minNode->dist)
		minNode= currNode;

	/* If parent value is smaller or root, then return */
	if (currNode->parent == nullptr)
		return;
	if (currNode->parent->dist < currNode->dist)
		return;

	/* Check if node is marked and not a root node*/
	while((parentMarked == true) && (currNode->parent != nullptr))
	{
		/* Store parent node */
		parentNode = currNode->parent;

		/* Break currNode from parent tree */
		if (currNode->leftSib != nullptr)
			currNode->leftSib->rightSib = currNode->rightSib;
		else // currNode is parentNode's first child pointer
			parentNode->child = currNode->rightSib;
		if (currNode->rightSib != nullptr)
			currNode->rightSib->leftSib = currNode->leftSib;
		parentNode->rank--; // Decrease number of children in parentNode

		/* Add currNode to root linked list */
		temp = root;
		root = currNode;
		currNode->leftSib = nullptr;
		currNode->rightSib = temp;
		currNode->parent = nullptr;
		currNode->marked = false;
		if (temp != nullptr)
			temp->leftSib = currNode;
		trees++; // Increase number of trees in root linked list

		/* Update minNode if necessary */
		if (currNode->dist < minNode->dist)
			minNode = currNode;

		/* Update currNode to parentNode */
		currNode = parentNode;

		/* Update marked condition */
		parentMarked = currNode->marked;
	}

	/* Mark current node */
	currNode->marked = true;
}

FibNode* FibHeap::findFibNode(int nodeNum)
{
	FibNode* currPtr = root;
	FibNode* temp = root;

	while (currPtr != nullptr)
	{
		/* Check if currPtr is the correct node */
		if (currPtr->nodeNum == nodeNum)
			return currPtr;

		if (currPtr->child != nullptr)
			currPtr = currPtr->child;
		else if (currPtr->rightSib != nullptr)
			currPtr = currPtr->rightSib;
		else if (currPtr->parent != nullptr)
			currPtr = currPtr->parent->rightSib;
		else
			return nullptr;
	}

	return nullptr;
}

void FibHeap::printHeap()
{
	if (root == nullptr)
	{
		cout << "Empty heap " << endl;
		return;
	}

	// Print minNode, trees, and maxRank
	cout << "minNode= " << minNode->nodeNum << ", trees= " << trees << ", maxRank= " << maxRank << endl;

	printHeapHelper(root);
	cout << endl;
}

void FibHeap::printHeapHelper(FibNode* currNode)
{
	if(currNode == nullptr)
		return;
	
	// Print node num
	cout << "nodeNum= " << currNode->nodeNum;
	// Print dist
	cout << ", dist= " << currNode->dist << ", parent= ";
	// Print parent
	if (currNode->parent != nullptr)
		cout << currNode->parent->nodeNum << ", leftSib= ";
	else
		cout << "nullptr, leftSib= ";
	// Print leftSib
	if (currNode->leftSib != nullptr)
		cout << currNode->leftSib->nodeNum << ", rightSib= ";
	else
		cout << "nullptr, rightSib= ";
	//Print rightSib
	if (currNode->rightSib != nullptr)
		cout << currNode->rightSib->nodeNum << ", child= ";
	else
		cout << "nullptr, child= ";
	//Print child
	if(currNode->child != nullptr)
		cout << currNode->child->nodeNum << ", rank= ";
	else
		cout << "nullptr, rank= ";
	//Print rank
	cout << currNode->rank << endl;

	/* Print child nodes, then sibling nodes */
	printHeapHelper(currNode->child);
	printHeapHelper(currNode->rightSib);
}
