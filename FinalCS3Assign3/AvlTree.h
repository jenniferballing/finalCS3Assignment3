#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream> 
#include <assert.h>
#include <sstream>
#include "GameState.h"
#include "Board.h"

using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x  
// bool contains( x )     --> Return true if x is present
// TreeType findMin( )  --> Return smallest item
// TreeType findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// TreeType  removeMin  -->  You are not allowed simply to do a find Min and then a remove on that value.  
//                            That would require that you traverse the tree twice  (once to find and once to delete).  We want a true removeMin that 
//                            only traverses in order to delete.
// ******************ERRORS********************************


//HINT:   The class you use as TreeType must have overloaded operators for > == and <.
//        nullptr is another way of saying NULL.  It has some interesting properties for implicit conversions.
//        && is an "rvalue reference".  They are beyond the scope of this class.  A good explanation is at http://thbecker.net/articles/rvalue_references/section_01.html

template <typename TreeType>
class AvlTree
{
public:
	AvlTree() : root{ nullptr }
	{ }

	AvlTree(const AvlTree & rightSide) : root{ nullptr }
	{
		root = clone(rightSide.root);
	}

	AvlTree(AvlTree && rightSide) : root{ rightSide.root }
	{
		rightSide.root = nullptr;
	}

	~AvlTree()
	{
		makeEmpty();
	}

	/**
	* Deep copy.
	*/
	AvlTree & operator=(const AvlTree & rightSide)
	{
		AvlTree copy = rightSide;
		std::swap(*this, copy);
		return *this;
	}

	/**
	* Move.
	*/
	AvlTree & operator=(AvlTree && rightSide)
	{
		std::swap(root, rightSide.root);

		return *this;
	}
	string toString()
	{
		assert(!isEmpty());
		return toString(root, " ");
	}

	/**
	* Find the smallest item in the tree.
	* Throw UnderflowException if empty.
	*/
	const TreeType & findMin() const
	{
		assert(!isEmpty());
		return findMin(root)->element;
	}

	/**
	* Find the largest item in the tree.

	*/
	const TreeType & findMax() const
	{
		assert(!isEmpty()) :
			return findMax(root)->element;
	}

	/**
	* Returns true if x is found in the tree.
	*/
	bool contains(const TreeType & x) const
	{
		return contains(x, root);
	}

	/**
	* Test if the tree is logically empty.
	* Return true if empty, false otherwise.
	*/
	bool isEmpty() const
	{
		return root == nullptr;
	}

	/**
	* Print the tree contents in sorted order.
	*/
	void printTree() const
	{
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printTree(root);
	}

	/**
	* Make the tree logically empty.
	*/
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	* x into the tree; duplicates are ignored.
	*/
	void insert(const TreeType & x)
	{
		insert(x, root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	* && is termed an rvalue reference.
	* a good explanation is at http://thbecker.net/articles/rvalue_references/section_01.html
	*/
	void insert(TreeType && x)
	{
		insert(std::move(x), root);
	}

	void insert(GameState &x)
	{
		insert(x, root);
	}

	/**
	* Remove x from the tree. Nothing is done if x is not found.
	*/
	void remove(const TreeType & x)
	{
		remove(x, root);
	}

	void removeMin()
	{
		removeMin(root);
	}

private:
	struct AvlNode
	{
		TreeType element;
		AvlNode   *left;
		AvlNode   *right;
		int       height;

		AvlNode(const TreeType & ele, AvlNode *lt, AvlNode *rt, int h = 0)
			: element{ ele }, left{ lt }, right{ rt }, height{ h } { }

		AvlNode(TreeType && ele, AvlNode *lt, AvlNode *rt, int h = 0)
			: element{ std::move(ele) }, left{ lt }, right{ rt }, height{ h } { }
	};

	AvlNode *root;

	AvlNode* findParent(int desiredEl)
	{
		assert(!isEmpty());
		return findParent(root, NULL, desiredEl);
	}


	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(const TreeType & x, AvlNode * & t)
	{
		if (t == nullptr)
			t = new AvlNode{ x, nullptr, nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);

		balance(t);
	}

	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(TreeType && x, AvlNode * & t)
	{
		if (t == nullptr)
			t = new AvlNode{ std::move(x), nullptr, nullptr };
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (t->element < x)
			insert(std::move(x), t->right);

		balance(t);
	}

	/*void insert(GameState &game, AvlNode *&t)
	{
		if (t == NULL)
		{
			AvlNode *newNode = new AvlNode(game, NULL, NULL);
		}
		else if (t->element.getExpectedMoves() > game.getExpectedMoves())
			insert(game, t->left);
		else if (t->element.getExpectedMoves() < game.getExpectedMoves())
			insert(game, t->left);
		balance(t);
	}*/


	/**
	* Internal method to remove from a subtree.
	* x is the item to remove.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void remove(const TreeType & x, AvlNode * & t)
	{
		if (t == nullptr)
			return;   // Item not found; do nothing

		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr) // Two children
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			AvlNode *oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}

		balance(t);
	}

	void removeMin(AvlNode *t)
	{
		if (t == NULL)return;
		if (t->left == NULL && t->right == NULL)
		{
			AvlNode *parentOfT = findParent(t->element);
			if (parentOfT == NULL) return;
			parentOfT->left = NULL;
		}
		else if (t->left == NULL && t->right != NULL)
		{
			AvlNode *parentOfT = findParent(t->element);
			if (parentOfT == NULL) return;

			rotateWithRightChild(t);
			parentOfT->left = t;
			t->left = NULL;
			delete t->left;
			return;
			balance(t);
		}
		if (t->left != NULL)removeMin(t->left);

		return;
	}

	AvlNode* findParent(AvlNode *t, AvlNode *parent, int desiredEl)
	{
		if (t == NULL) return NULL;
		if (parent == NULL) return NULL;
		if (t->element == desiredEl) return parent;
		if (t->element > desiredEl) return findParent(t->left, t, desiredEl);
		if (t->element < desiredEl) return findParent(t->right, t, desiredEl);
	}

	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance(AvlNode * & t)
	{
		if (t == nullptr)
			return;

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
		if (height(t->left->left) >= height(t->left->right))
			rotateWithLeftChild(t);
		else
			doubleWithLeftChild(t);
		else
		if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
		if (height(t->right->right) >= height(t->right->left))
			rotateWithRightChild(t);
		else
			doubleWithRightChild(t);

		t->height = max(height(t->left), height(t->right)) + 1;
	}

	string toString(AvlNode * t, string indent)
	{
		string left, right, current;
		if (t == NULL) return "";

		stringstream sp;
		sp << t->element;
		sp >> current;

		if (t->left != NULL) left = "\n" + toString(t->left, indent + "  ");//create left string
		else left = "";

		if (t->right != NULL) right = "\n" + toString(t->right, indent + "  ");//create right string
		else right = "";

		return right + indent + current + indent + left + "\n"; //combine strings and print with indent		
	}

	/**
	* Internal method to find the smallest item in a subtree t.
	* Return node containing the smallest item.
	*/
	AvlNode * findMin(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}

	/**
	* Internal method to find the largest item in a subtree t.
	* Return node containing the largest item.
	*/
	AvlNode * findMax(AvlNode *t) const
	{
		if (t != nullptr)
		while (t->right != nullptr)
			t = t->right;
		return t;
	}


	/**
	* Internal method to test if an item is in a subtree.
	* x is item to search for.
	* t is the node that roots the tree.
	*/
	bool contains(const TreeType & x, AvlNode *t) const
	{
		if (t == nullptr)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}
	/****** NONRECURSIVE VERSION*************************
	bool contains( const TreeType & x, AvlNode *t ) const
	{
	while( t != nullptr )
	if( x < t->element )
	t = t->left;
	else if( t->element < x )
	t = t->right;
	else
	return true;    // Match

	return false;   // No match
	}
	*****************************************************/

	/**
	* Internal method to make subtree empty.
	*/
	void makeEmpty(AvlNode * & t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	/**
	* Internal method to print a subtree rooted at t in sorted order.
	*/
	void printTree(AvlNode *t) const
	{
		if (t != nullptr)
		{
			printTree(t->left);
			cout << t->element << endl;
			printTree(t->right);
		}
	}

	/**
	* Internal method to clone subtree.
	*/
	AvlNode * clone(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode{ t->element, clone(t->left), clone(t->right), t->height };
	}
	// Avl manipulations
	/**
	* Return the height of node t or -1 if nullptr.
	*/
	int height(AvlNode *t) const
	{
		return t == nullptr ? -1 : t->height;
	}

	int max(int leftSide, int rightSide) const
	{
		return leftSide > rightSide ? leftSide : rightSide;
	}

	/**
	* Rotate binary tree node with left child.
	* For AVL trees, this is a single rotation for case 1.
	* Update heights, then set new root.
	*/
	void rotateWithLeftChild(AvlNode * & k2)
	{
		AvlNode *leftK = k2->left;
		k2->left = leftK->right;
		leftK->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		leftK->height = max(height(leftK->left), k2->height) + 1;
		k2 = leftK;
	}

	/**
	* Rotate binary tree node with right child.
	* For AVL trees, this is a single rotation for case 4.
	* Update heights, then set new root.
	*/
	void rotateWithRightChild(AvlNode * & k1)
	{
		AvlNode *rightK = k1->right;
		k1->right = rightK->left;
		rightK->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		rightK->height = max(height(rightK->right), k1->height) + 1;
		k1 = rightK;
	}

	/**
	* Double rotate binary tree node: first left child.
	* with its right child; then node k3 with new left child.
	* For AVL trees, this is a double rotation for case 2.
	* Update heights, then set new root.
	*/
	void doubleWithLeftChild(AvlNode * & k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	/**
	* Double rotate binary tree node: first right child.
	* with its left child; then node k1 with new right child.
	* For AVL trees, this is a double rotation for case 3.
	* Update heights, then set new root.
	*/
	void doubleWithRightChild(AvlNode * & k1)
	{
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}
};

#endif