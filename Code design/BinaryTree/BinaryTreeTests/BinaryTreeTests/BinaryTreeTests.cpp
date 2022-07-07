#include "CppUnitTest.h"
#include "../CDDS_BinaryTree/BinaryTree.h"
#include "../CDDS_BinaryTree/TreeNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTreeTests
{
	TEST_CLASS(BinaryTreeTests)
	{
	public:
		
		TEST_METHOD(Insert)
		{
			BinaryTree bintree;
			bintree.Insert(5);
			Assert::AreEqual(bintree.GetRoot()->GetData(), 5);
		}

		TEST_METHOD(IsEmpty) 
		{
			BinaryTree bintree;
			Assert::AreEqual(bintree.IsEmpty(), true);
		}

		TEST_METHOD(IsEmpty2) 
		{
			BinaryTree bintree;
			bintree.Insert(2);
			Assert::AreEqual(bintree.IsEmpty(), false);
		}

		TEST_METHOD(Find)
		{
			BinaryTree bintree;
			bintree.Insert(10);
			bintree.Insert(8);
			Assert::AreEqual(bintree.Find(8)->GetData(), bintree.GetRoot()->GetLeft()->GetData());
		}
	};
}
