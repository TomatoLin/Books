//面试题6：重建二叉树
//题目：输入某二叉树的前序遍历和中序遍历结果，重建出该二叉树
//1.假设输入的前序遍历和中序遍历的结果中都不含重复的数字

#include "BinaryTree.h"
#include <exception>
#include <iostream>
#include <stdio.h>
using namespace std;

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);

//2.假设遍历结果参数存于数组中
BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
	if(preorder == NULL || inorder == NULL || length <= 0)
		return NULL;

	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
	//前序遍历序列的第一个数字是根节点的值
	int rootValue = startPreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = NULL;

	if(startPreorder == endPreorder)
	{
		if(startInorder == endInorder && *startPreorder == *startInorder)
			return root;
		else
			throw std::exception();
	}

	//在中序遍历中找到根节点
	int* rootInorder = startInorder;
	while(rootInorder <= endInorder && *rootInorder != rootValue)
		++ rootInorder;

	if(rootInorder == endInorder && *rootInorder != rootValue)
		throw std::exception();

	int leftLength = rootInorder - startInorder; 
	int* leftPreorderEnd = startPreorder + leftLength;
	if(leftLength > 0)
	{
		//构建左子树
		root->m_pLeft = ConstructCore(startPreorder+1, leftPreorderEnd, startInorder, rootInorder-1);
	}

	if(leftLength < endPreorder - startPreorder)
	{
		// 构建右子树
		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder,
				rootInorder + 1, endInorder);
	}

	return root;
}

// ====================测试代码====================
void Test(const char* testName, int* preorder, int* inorder, int length)
{
	if(testName != NULL)
		printf("%s begins:\n", testName);

	printf("The preorder sequence is: ");
	for(int i = 0; i < length; ++ i)
		printf("%d ", preorder[i]);
	printf("\n");

	printf("The inorder sequence is: ");
	for(int i = 0; i < length; ++ i)
		printf("%d ", inorder[i]);
	printf("\n");

	try
	{
		BinaryTreeNode* root = Construct(preorder, inorder, length);
		//PrintTree(root);
		cout << "前序遍历" << endl;
		PreOrder2(root);

		cout << "中序遍历" << endl;
		InOrder2(root);

		cout << "后序遍历" << endl;
		PostOrder2(root);

		DestroyTree(root);
	}
	catch(std::exception& exception)
	{
		printf("Invalid Input.\n");
	}
}

// 普通二叉树
//              1
//           /     \
//          2       3  
//         /       / \
//        4       5   6
//         \         /
//          7       8
void Test1()
{
	const int length = 8;
	int preorder[length] = {1, 2, 4, 7, 3, 5, 6, 8};
	int inorder[length] = {4, 7, 2, 1, 5, 3, 8, 6};
	//7 4 2 5 8 6 3 1

	Test("Test1", preorder, inorder, length);
}

// 所有结点都没有右子结点
//            1
//           / 
//          2   
//         / 
//        3 
//       /
//      4
//     /
//    5
void Test2()
{
	const int length = 5;
	int preorder[length] = {1, 2, 3, 4, 5};
	int inorder[length] = {5, 4, 3, 2, 1};

	Test("Test2", preorder, inorder, length);
}

// 所有结点都没有左子结点
//            1
//             \
//              2   
//               \
//                3 
//                 \
//                  4
//                   \
//                    5
void Test3()
{
	const int length = 5;
	int preorder[length] = {1, 2, 3, 4, 5};
	int inorder[length] = {1, 2, 3, 4, 5};

	Test("Test3", preorder, inorder, length);
}

// 树中只有一个结点
void Test4()
{
	const int length = 1;
	int preorder[length] = {1};
	int inorder[length] = {1};

	Test("Test4", preorder, inorder, length);
}

// 完全二叉树
// //              1
// //           /     \
// //          2       3  
// //         / \     / \
// //        4   5   6   7
void Test5()
{
	const int length = 7;
	int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
	int inorder[length] = {4, 2, 5, 1, 6, 3, 7};

	Test("Test5", preorder, inorder, length);
}


// 输入空指针
void Test6()
{
	Test("Test6", NULL, NULL, 0);
}

// 输入的两个序列不匹配
void Test7()
{
	const int length = 7;
	int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
	int inorder[length] = {4, 2, 8, 1, 6, 3, 7};

	Test("Test7: for unmatched input", preorder, inorder, length);
}

int main()
{
	Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
}
