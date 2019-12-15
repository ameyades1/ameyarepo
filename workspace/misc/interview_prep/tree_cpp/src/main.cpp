
/*
 * SYSTEM INCLUDES
 */
#include <iostream>

/*
 * PROJECT INCLUDES
 */
#include "btree.h"

int main(int argc, char* argv[])
{
		CBinaryTree<int> tree;
		std::vector<int> data = {10,5,7,8,9,1,3};
		
		tree.InitBST(data);
	
		std::cout << "Inorder traversal: \n";
		tree.InorderTraversal(tree.GetRoot());
		std::cout << "\n\n";

		std::cout << "Preorder traversal: \n";
		tree.PreorderTraversal(tree.GetRoot());
		std::cout << "\n\n";
		
		std::cout << "Postorder traversal: \n";
		tree.PostorderTraversal(tree.GetRoot());
		std::cout << "\n\n";

		std::cout << "Reverse Inorder traversal: \n";
		tree.ReverseInorderTraversal(tree.GetRoot());
		std::cout << "\n\n";
		
		std::cout << "Inserting node 6\n";
		tree.InsertNodeBST(tree.GetRoot(), CNode<int>(6));
		
		std::cout << "Inorder traversal: \n";
		tree.InorderTraversal(tree.GetRoot());
		std::cout << "\n\n";
		
		std::cout << "Inorder traversal Non Recursive: \n";
		tree.InorderTraversalStack(tree.GetRoot());
		std::cout << "\n\n";

		return 0;
}

