#ifndef __BTREE_H__
#define __BTREE_H__

/*
 * SYSTEM INCLUDES
 */
#include <vector>
#include <stack>

/*
 * PROJECT INCLUDES
 */
#include "btree_node.h"


/*
 * Class Binary Tree
 */
template <typename T>
class CBinaryTree {
		private:
				CNode<T>* root;
				uint64_t height;
				uint64_t num_nodes;

				CBinaryTree(CNode<T> node);
				CBinaryTree(CBinaryTree* tree) {};
				void delete_subtree(CNode<T>* node);

		public:
				CBinaryTree();
				CBinaryTree(CNode<T>* node);
				~CBinaryTree();
				CNode<T>* GetRoot(){return root;};

				CNode<T>* InsertNodeBST(CNode<T>* root, const CNode<T>& data);
				void InitBST(std::vector<T> vec);

				void InorderTraversal(CNode<T>* node);
				void InorderTraversalStack(CNode<T>* node);
				void PreorderTraversal(CNode<T>* node);
				void PostorderTraversal(CNode<T>* node);
				void ReverseInorderTraversal(CNode<T>* node);
};


/*
 * Default constructor
 */
		template <typename T>
CBinaryTree<T>::CBinaryTree()
{
		root = NULL;
		height = 0;
		num_nodes = 0;

}

/*
 * Copy constructor
 */

		template <typename T>
CBinaryTree<T>::CBinaryTree(CNode<T>* node)
{
		root = node;
}


/*
 * Delete a subtree for specified node
 */
		template <typename T>
void CBinaryTree<T>::delete_subtree(CNode<T>* node)
{
		if(node == NULL)
				return;

		if(node->pleft)
				delete_subtree(node->pleft);

		if(node->pright)
				delete_subtree(node->pright);

		if(node)
				delete node;
		node = NULL;
}


/*
 * Destructor
 */
		template <typename T>
CBinaryTree<T>::~CBinaryTree()
{
		if(root) {
				delete_subtree(root);
		}
}


/*
 * BST tree node insertion
 * Left <= Node < Right
 */
		template <typename T>
CNode<T>* CBinaryTree<T>::InsertNodeBST(CNode<T>* cur_root, const CNode<T>& node)
{
		CNode<T>* ptrav, *ptemp;
		if(cur_root == NULL) {
				cur_root = new CNode<T>(node);
				return cur_root;
		}
		else {
				ptrav = cur_root;

				while(ptrav) {
						ptemp = ptrav;

						if(node.data <= ptrav->data)
								ptrav = ptrav->pleft;
						else
								ptrav = ptrav->pright;
				}

				if(node.data <= ptemp->data)
						ptemp->pleft = new CNode<T>(node);
				else
						ptemp->pright = new CNode<T>(node);

				return root;
		}

}


/*
 * Initialize the BST with supplied vector
 */
		template <typename T>
void CBinaryTree<T>::InitBST(std::vector<T> vec)
{
		for (auto i: vec) {
				root = InsertNodeBST(root, CNode<T>(i));
		}
}


/*
 * Inorder traversal recursive
 */
		template <typename T>
void CBinaryTree<T>::InorderTraversal(CNode<T>* node)
{
		if(node == NULL)
				return;

		InorderTraversal(node->pleft);
		std::cout << node->data << " ";
		InorderTraversal(node->pright);

}


/*
 * Inorder traversal non-recursive
 */
		template <typename T>
void CBinaryTree<T>::InorderTraversalStack(CNode<T>* node)
{
		if(node == NULL)
				return;

		std::stack<CNode<T>*> stack;
		do {

				while(node) {
						stack.push(node->pleft);
						stack.push(node);
						stack.push(node->pright);
						if(node) node = node->pleft;
				}

				CNode<T>* temp = stack.top();
				if(node) std::cout << node->data << " ";
				stack.pop();

		}while(!stack.empty());
}


/*
 * Preorder traversal recursive
 */
		template <typename T>
void CBinaryTree<T>::PreorderTraversal(CNode<T>* node)
{
		if(node == NULL)
				return;

		std::cout << node->data << " ";
		PreorderTraversal(node->pleft);
		PreorderTraversal(node->pright);

}


/*
 * Postorder traversal recursive
 */
		template <typename T>
void CBinaryTree<T>::PostorderTraversal(CNode<T>* node)
{
		if(node == NULL)
				return;

		PostorderTraversal(node->pleft);
		PostorderTraversal(node->pright);
		std::cout << node->data << " ";

}


/*
 * Reverse inorder traversal recursive
 */
		template <typename T>
void CBinaryTree<T>::ReverseInorderTraversal(CNode<T>* node)
{
		if(node == NULL)
				return;

		ReverseInorderTraversal(node->pright);
		std::cout << node->data << " ";
		ReverseInorderTraversal(node->pleft);

}

#endif
