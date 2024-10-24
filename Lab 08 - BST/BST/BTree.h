#ifndef BTREE_H
#define BTREE_H
#include "BSTInterface.h"

template<typename T>
class BTree : public
{
public:
	BSTInterface(void) {}
	virtual ~BSTInterface(void) {}

	/** Return true if node added to BST, else false */
	virtual bool addNode(const T&) = 0;

	/** Return true if node removed from BST, else false */
	virtual bool removeNode(const T&) = 0;

	/** Return true if BST cleared of all nodes, else false */
	virtual bool clearTree() = 0;

	/** Return a level order traversal of a BST as a string */
	vi

#endif //BTREE_H
