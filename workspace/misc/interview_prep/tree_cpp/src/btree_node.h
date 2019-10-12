#ifndef __BTREE_NODE_H__
#define __BTREE_NODE_H__

/*
 * SYSTEM INCLUDES
 */


/*
 * Class Binary Tree Node
 */
template <typename T>
class CNode {
		public:
				T data;
				CNode* pleft;
				CNode* pright;

				CNode();
				~CNode();
				CNode(CNode* node);
				CNode(const CNode<T>& node);
				CNode(T data);

};


/*
 * Implementation Binary Tree Node Methods
 */
		template <typename T>
CNode<T>::CNode()
{
		data   = 0;
		pleft  = NULL;
		pright = NULL;
}

		template <typename T>
CNode<T>::CNode(T d)
{
		data   = d;
		pleft  = NULL;
		pright = NULL;
}

		template <typename T>
CNode<T>::~CNode()
{
}


		template <typename T>
CNode<T>::CNode(CNode* node)
{
		data   = node->data;
		pleft  = node->pleft;
		pright = node->pright;
}

		template <typename T>
CNode<T>::CNode(const CNode<T>& node)
{
		data   = node.data;
		pleft  = node.pleft;
		pright = node.pright;
}



#endif
