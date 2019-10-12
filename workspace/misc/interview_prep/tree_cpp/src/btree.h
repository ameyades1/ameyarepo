#ifndef __BTREE_H__
#define __BTREE_H__

/*
 * SYSTEM INCLUDES
 */
#include <vector>


/*
 * PROJECT INCLUDES
 */
#include "btree_node.h"


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
				void PreorderTraversal(CNode<T>* node);
				void PostorderTraversal(CNode<T>* node);
				void ReverseInorderTraversal(CNode<T>* node);
};


		template <typename T>
CBinaryTree<T>::CBinaryTree()
{
		root = NULL;
		height = 0;
		num_nodes = 0;

}

		template <typename T>
CBinaryTree<T>::CBinaryTree(CNode<T>* node)
{
		root = node;
}

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

		template <typename T>
void CBinaryTree<T>::InitBST(std::vector<T> vec)
{
		for (auto i: vec) {
				root = InsertNodeBST(root, CNode<T>(i));
		}
}


		template <typename T>
void CBinaryTree<T>::InorderTraversal(CNode<T>* node)
{
		if(node == NULL)
				return;

		InorderTraversal(node->pleft);
		std::cout << node->data << " ";
		InorderTraversal(node->pright);

}

		template <typename T>
void CBinaryTree<T>::PreorderTraversal(CNode<T>* node)
{
		if(node == NULL)
				return;

		std::cout << node->data << " ";
		PreorderTraversal(node->pleft);
		PreorderTraversal(node->pright);

}

		template <typename T>
void CBinaryTree<T>::PostorderTraversal(CNode<T>* node)
{
		if(node == NULL)
				return;

		PostorderTraversal(node->pleft);
		PostorderTraversal(node->pright);
		std::cout << node->data << " ";

}


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
