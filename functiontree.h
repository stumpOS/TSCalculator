#pragma once
#ifndef FUNCTIONTREE_H_
#define FUNCTIONTREE_H_
#include <stdexcept>
#include "Symbol.h"
/**
 * FunctionTree builds a tree from a sequence of symbols.
 * The location where the symbol is added is dependent upon
 * the rank of the symbol and THE STATE OF THE CLIENT PROGRAM.
 * The rank indicates the order of the operation in a defined
 * order of operations (PEMDAS). The state of the client program
 * dictates how a leaf is added to another leaf (left or right)
**/
template<class T>
class FunctionTree
{
public:
	typedef Symbol<T> Symbol;
	class Node
	{
		friend class FunctionTree<T>;
	public:
		Node(){_left=NULL;_right=NULL;_data=0;}
		Node(Symbol* sym):_symbol(sym){_left=NULL;_right=NULL;_data=0;}
		virtual ~Node(){}
		T &GetNodeContents(){return _data;}
		void SetNodeContents(T const& data){_data = data;}
		void Fire()
		{
			T arg1 = (_left!=NULL? _left->GetNodeContents():0);
			T arg2 = (_right!=NULL? _right->GetNodeContents():0);

			_data = _symbol->Fire(arg1, arg2);
		}

		Symbol* GetSymbol(){return _symbol;}
		void SetSymbol(Symbol *symbol){_symbol = symbol;}
		bool IsLeaf()
		{
			if(_symbol->GetRank()<0)
				return true;
			else
				return false;
		}
	private:
		Symbol *_symbol;
		T _data;
		Node *_right;
		Node *_left;
	};
	FunctionTree(){_root = NULL;}
	struct ParentRightChildPair
	{
		ParentRightChildPair(Node *p,Node *r):_parent(p),_rightChild(r){}
		Node *_parent;
		Node *_rightChild;
	};
	virtual ~FunctionTree()
	{
		if(_root != NULL)
		{
			Clear(&_root);
		}
	}
	void Clear(){Clear(&_root);}

	void Insert(Symbol *symbol)
	{
		if(_root==NULL)
		{
			_root = new Node(symbol);
		}
		else
		{
			if(symbol->GetRank()<0)
				AddLeaf(symbol);
			else
				AddOperator(symbol);
		}
	}
	T Evaluate()
	{
		Evaluate(_root);
		return _root->GetNodeContents();
	}
private:
	void Evaluate(Node *current)
	{
		if(current->_left!=NULL)
		{
			Evaluate(current->_left);
		}
		if(current->_right!=NULL)
		{
			Evaluate(current->_right);
		}
		current->Fire();
	}
	void AddLeaf(Symbol *symbol)
	{
		Node *right_most = GetRightMost(_root);
		right_most->_right = new Node(symbol);	
	}
	Node *GetRightMost(Node *parent)
	{
		if(parent->_right != NULL)
			return GetRightMost(parent->_right);
		else
			return parent;
	}
	void AddOperator(Symbol *symbol)
	{
		ParentRightChildPair nodesToRotate(NULL,_root);
		FindFirstLesserRightChild(nodesToRotate,symbol);
			
		if(nodesToRotate._parent == NULL)
		{
			AddAsNewRoot(symbol);
		}
		else 
		{
			Rotate(nodesToRotate,symbol);
		}
	}
	void AddAsNewRoot(Symbol *symbol)
	{
		Node *newRoot = new Node(symbol);
		newRoot->_left = _root;
		_root = newRoot;
	}

	void Rotate(ParentRightChildPair &nodesToRotate, Symbol *symbol)
	{
		Node *newParent = new Node(symbol);
		nodesToRotate._parent->_right = newParent;
		newParent->_left = nodesToRotate._rightChild;
	}
	void FindFirstLesserRightChild(ParentRightChildPair &current,Symbol *symbol)
	{
		if(!(*(current._rightChild->GetSymbol()) < *symbol))
		{
			if(current._rightChild->_right != NULL)
			{
				Node *newParent = current._rightChild;
				current._rightChild = current._rightChild->_right;
				current._parent = newParent;
				FindFirstLesserRightChild(current,symbol);
			}
		}
	}
	void Clear(Node **root)
	{
		if((*root)->_left!=NULL)
		{
			Clear(&(*root)->_left);
		}
		if((*root)->_right!=NULL)
		{
			Clear(&(*root)->_right);
		}
		delete *root;
		*root = NULL;
	}
	Node *_root;

};

#endif