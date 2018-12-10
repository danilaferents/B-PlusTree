//
//  BPlusTreeTests.cpp
//  
//
//  Created by Ferents Danila.
//
#include <iostream>
#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "BPlusTree.cpp"
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace BPlusTreeN;
namespace  
{	
	template <typename KeyT,typename ValueT> 
	void getvectortocheck(std::vector<KeyT>& ourvector, BPlusTree<KeyT,ValueT>& ourtree)
	{
		Node<KeyT, ValueT>* helpnode = ourtree.getroot();
		while(helpnode->getchilds()[0])
		{
			helpnode = helpnode->getchilds()[0];
		} 
		while(helpnode)
		{
			for (int i = 0; i < helpnode->getkey_num(); ++i)
			{
				ourvector.push_back(helpnode->getkeys()[i]);
			}
			helpnode = helpnode->getright();
		}
	}
    TEST(TestsBinarySearchTree,TestIntersection0)
    {
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		ourtree->insert(1,5);
		ourtree->insert(2,6);
		ourtree->insert(5,7);
		ourtree->insert(9,11);
		ourtree->print(0,ourtree->getroot());
		std::vector<int> answersk={5,1,2,5,9};
		std::vector<int> answersv={7,5,6,7,11};
		size_t k=0;
		ASSERT_EQ((ourtree->getroot()->getkeys())[0], answersk[k]);
		// ASSERT_EQ((ourtree->getroot()->getvalues())[0], answersv[k]);
		k++;
		for (int i = 0; i <=ourtree->getroot()->getkey_num(); ++i)
		{
			if((ourtree->getroot()->getchilds()[i])) 
			{
				for (int j = 0; j < ourtree->getroot()->getchilds()[i]->getkey_num(); ++j)
				{
					if (ourtree->getroot()->getchilds()[i]->getkeys()) 
					{
						ASSERT_EQ(((ourtree->getroot()->getchilds()[i]->getkeys())[j]), answersk[k]);
						if(ourtree->getroot()->getchilds()[i]->getleaf()) ASSERT_EQ(((ourtree->getroot()->getchilds()[i]->getvalues())[j]), answersv[k]);
						k++;
					}
				}
			}
		}
		// ourtree->print(0,ourtree->getroot());
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,TestIntersection1)
    {
		BPlusTree<char,int> *ourtree = new BPlusTree<char,int>(2);
		ourtree->insert('d',3);
		ourtree->insert('c',6);
		ourtree->insert('b',7);
		ourtree->insert('a',11);
		std::vector<int> answersk={'c','a','b','c','d'};
		std::vector<int> answersv={6,11,7,6,3};
		ourtree->print(0,ourtree->getroot());
		size_t k=0;
		ASSERT_EQ((ourtree->getroot()->getkeys())[0], answersk[k]);
		// ASSERT_EQ((ourtree->getroot()->getvalues())[0], answersv[k]);
		k++;
		for (int i = 0; i <=ourtree->getroot()->getkey_num(); ++i)
		{
			if((ourtree->getroot()->getchilds()[i])) 
			{
				for (int j = 0; j < ourtree->getroot()->getchilds()[i]->getkey_num(); ++j)
				{
					if (ourtree->getroot()->getchilds()[i]->getkeys()) 
					{
						ASSERT_EQ(((ourtree->getroot()->getchilds()[i]->getkeys())[j]), answersk[k]);
						if(ourtree->getroot()->getchilds()[i]->getleaf()) ASSERT_EQ(((ourtree->getroot()->getchilds()[i]->getvalues())[j]), answersv[k]);
						k++;
					}
				}
			}
		}
		delete ourtree;
	}

	TEST(TestsBinarySearchTree,TestIntersection2)
    {
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		ourtree->insert(19,55);
		ourtree->insert(3,6);
		ourtree->insert(2,666);
		ourtree->insert(7,3);
		ourtree->insert(25,24);
		ourtree->insert(15,9);
		ourtree->insert(18,15);
		ourtree->insert(5,11);
		ourtree->print(0,ourtree->getroot());
		std::vector<int> answersk={7,19,2,3,5,7,15,18,19,25};
		std::vector<int> answersv={0,0,666,6,11,3,9,15,55,24};
		size_t k=0;
		// ASSERT_EQ((ourtree->getroot()->getkeys())[0], answersk[k]);
		// ASSERT_EQ((ourtree->getroot()->getvalues())[0], answersv[k]);
		// k++;
		for (int i = 0; i < ourtree->getroot()->getkey_num(); ++i)
		{
			ASSERT_EQ((ourtree->getroot()->getkeys())[i], answersk[k]);
			k++;
		}
		for (int i = 0; i <=ourtree->getroot()->getkey_num(); ++i)
		{
			if((ourtree->getroot()->getchilds()[i])) 
			{
				for (int j = 0; j < ourtree->getroot()->getchilds()[i]->getkey_num(); ++j)
				{
					if (ourtree->getroot()->getchilds()[i]->getkeys()) 
					{
						ASSERT_EQ(((ourtree->getroot()->getchilds()[i]->getkeys())[j]), answersk[k]);
						if(ourtree->getroot()->getchilds()[i]->getleaf()) ASSERT_EQ(((ourtree->getroot()->getchilds()[i]->getvalues())[j]), answersv[k]);
						k++;
					}
				}
			}
		}
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,TestIntersection3)
    {
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		ourtree->insert(27,4);
		ourtree->insert(52,8);
		ourtree->insert(20,2);
		ourtree->insert(42,6);
		ourtree->insert(93,12);
		ourtree->insert(7,0);
		ourtree->insert(14,1);
		ourtree->insert(21,3);
		ourtree->insert(34,5);
		ourtree->insert(47,7);
		ourtree->insert(64,9);
		ourtree->insert(72,10);
		ourtree->insert(91,11);
		ourtree->insert(97,13);
		ourtree->print(0,ourtree->getroot());
		// std::vector<int> answersk={42,20,27,7,14,7,15,18,19,25};
		// std::vector<int> answersv={6,0,666,6,11,3,9,15,55,24};
		// size_t k=0;
		// ASSERT_EQ((ourtree->getroot()->getkeys())[0], answersk[k]);
		// ASSERT_EQ((ourtree->getroot()->getvalues())[0], answersv[k]);
		// k++;
		// for (int i = 0; i < ourtree->getroot()->getkey_num(); ++i)
		// {
		// 	ASSERT_EQ((ourtree->getroot()->getkeys())[i], answersk[k]);
		// 	k++;
		// }
		// for (int i = 0; i <=ourtree->getroot()->getkey_num(); ++i)
		// {
		// 	if((ourtree->getroot()->getchilds()[i])) 
		// 	{
		// 		for (int j = 0; j < ourtree->getroot()->getchilds()[i]->getkey_num(); ++j)
		// 		{
		// 			if (ourtree->getroot()->getchilds()[i]->getkeys()) 
		// 			{
		// 				ASSERT_EQ(((ourtree->getroot()->getchilds()[i]->getkeys())[j]), answersk[k]);
		// 				if(ourtree->getroot()->getchilds()[i]->getleaf()) ASSERT_EQ(((ourtree->getroot()->getchilds()[i]->getvalues())[j]), answersv[k]);
		// 				k++;
		// 			}
		// 		}
		// 	}
		// }
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,Deletation0)
    {
		
		//test for deleting key and borrow key from left sibling 
		 BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		ourtree->insert(8,4);
		ourtree->insert(9,8);
		ourtree->insert(11,2);
		ourtree->insert(15,6);
		ourtree->insert(17,12);
		ourtree->insert(18,0);
		ourtree->insert(22,1);
		ourtree->insert(23,3);
		ourtree->insert(24,5);
		ourtree->insert(25,555);
		ourtree->insert(26,666);
		ourtree->insert(28,888);
		ourtree->print(0,ourtree->getroot());
		std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(24)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());
		std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(25)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,Deletation1)
    {
		
		//test for deleting key and borrow key from right sibling 
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		ourtree->insert(8,4);
		ourtree->insert(9,8);
		ourtree->insert(11,2);
		ourtree->insert(15,6);
		ourtree->insert(17,12);
		ourtree->insert(18,0);
		ourtree->insert(22,1);
		ourtree->insert(23,3);
		ourtree->insert(24,5);
		ourtree->insert(25,555);
		ourtree->insert(26,666);
		ourtree->insert(28,888);
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());
		std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(15)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());
		std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(11)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,Deletation2)
    {
		 BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		ourtree->insert(8,4);
		ourtree->insert(9,8);
		ourtree->insert(11,2);
		ourtree->insert(15,6);
		ourtree->insert(17,12);
		ourtree->insert(18,0);
		ourtree->insert(22,1);
		ourtree->insert(23,3);
		ourtree->insert(24,5);
		ourtree->insert(25,555);
		ourtree->insert(26,666);
		ourtree->insert(28,888);
		ourtree->print(0,ourtree->getroot());
		std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(18)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());
		std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(15)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());
		std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(8)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());
		if(ourtree->remove(11)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,Deletation3)
    {
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		ourtree->insert(8,4);
		ourtree->insert(9,8);
		ourtree->insert(11,2);
		ourtree->insert(15,6);
		ourtree->insert(17,12);
		ourtree->insert(18,0);
		ourtree->insert(22,1);
		ourtree->insert(23,3);
		ourtree->insert(24,5);
		ourtree->insert(25,555);
		ourtree->insert(26,666);
		ourtree->insert(28,888);
		ourtree->insert(55,4);
		ourtree->insert(1,8);
		ourtree->insert(4,2);
		ourtree->insert(44,6);
		ourtree->insert(55,12);
		ourtree->insert(3,0);
		ourtree->insert(99,1);
		ourtree->insert(7,3);
		ourtree->insert(5,5);
		ourtree->insert(16,555);
		ourtree->insert(30,666);
		ourtree->insert(32,888);
		std::vector<int> tocheck1={1,3,4,5,7,8,9,11,15,16,17,18,22,23,24,25,26,28,30,32,44,55,99};
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck2.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->remove(5);
		ourtree->remove(7);
		ourtree->remove(4);
		ourtree->remove(3);
		ourtree->remove(8);
		ourtree->remove(11);
		ourtree->remove(17);
		ourtree->remove(16);
		ourtree->remove(1);
		ourtree->remove(9);
		ourtree->remove(15);
		ourtree->remove(24);
		ourtree->remove(25);
		ourtree->remove(44);
		ourtree->remove(55);
		ourtree->remove(99);
		ourtree->remove(23);
		ourtree->remove(28);
		ourtree->remove(32);
		ourtree->remove(26);
		ourtree->remove(30);
		ourtree->remove(22);
		ourtree->remove(18);
		// delete ourtree->getroot();

		ourtree->print(0,ourtree->getroot());
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,Deletation4)
    {
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(3);
		ourtree->insert(8,4);
		ourtree->insert(9,8);
		ourtree->insert(11,2);
		ourtree->insert(15,6);
		ourtree->insert(17,12);
		ourtree->insert(18,0);
		ourtree->insert(22,1);
		ourtree->insert(23,3);
		ourtree->insert(24,5);
		ourtree->insert(25,555);
		ourtree->insert(26,666);
		ourtree->insert(28,888);
		ourtree->insert(55,4);
		ourtree->insert(1,8);
		ourtree->insert(4,2);
		ourtree->insert(44,6);
		ourtree->insert(55,12);
		ourtree->insert(3,0);
		ourtree->insert(99,1);
		ourtree->insert(7,3);
		ourtree->insert(5,5);
		ourtree->insert(16,555);
		ourtree->insert(30,666);
		ourtree->insert(32,888);
		std::vector<int> tocheck1={1,3,4,5,7,8,9,11,15,16,17,18,22,23,24,25,26,28,30,32,44,55,99};
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck2.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->remove(5);
		ourtree->remove(7);
		ourtree->remove(4);
		ourtree->remove(3);
		ourtree->remove(8);
		ourtree->remove(11);
		ourtree->remove(17);
		ourtree->remove(16);
		ourtree->remove(1);
		ourtree->remove(9);
		ourtree->remove(15);
		ourtree->remove(24);
		ourtree->remove(25);
		ourtree->remove(44);
		ourtree->remove(55);
		ourtree->remove(99);
		ourtree->remove(23);
		ourtree->remove(28);
		ourtree->remove(32);
		ourtree->remove(26);
		ourtree->remove(30);
		ourtree->remove(22);
		ourtree->remove(18);
		// delete ourtree->getroot();

		ourtree->print(0,ourtree->getroot());
		std::cout<<"After Deletation";
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,Deletation5)
    {
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(50);
		for (int i = 0; i < 100000; ++i)
		{
			ourtree->insert(i,i);
			tocheck1.push_back(i);
		}
		for (int i = 99999; i >=0 ; --i)
		{
			ourtree->remove(i);
		}
		// delete ourtree->getroot();

		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck2.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,Deletation6)
    {
    	std::ios_base::sync_with_stdio(0); 
		std::cin.tie(0);
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(50);
		for (int i = 0; i < 100000; ++i)
		{
			ourtree->insert(i,i);
			if(i<10000 || i > 60000) tocheck1.push_back(i);
		}
		for (int i = 60000; i >=10000 ; --i)
		{
			ourtree->remove(i);
		}
		// delete ourtree->getroot();

		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck2.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
	}
	TEST(TestsBinarySearchTree,Lazy0)
    {
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		ourtree->insert(8,4);
		ourtree->insert(11,2);
		ourtree->insert(15,6);
		ourtree->insert(17,12);
		ourtree->insert(18,0);		
		ourtree->lazyremove(18);
		ourtree->lazyinsert(22,1);
		ourtree->lazyremove(17);
		ourtree->lazyinsert(18,3);
		ourtree->lazyremove(18);
		ourtree->fix();
		ourtree->lazyremove(15);
		ourtree->fix();
		ourtree->lazyremove(22);
		ourtree->fix();
		ourtree->remove(11);
		ourtree->fix();
		ourtree->remove(8);
		ourtree->fix();
		ourtree->print(0,ourtree->getroot());
		delete ourtree;    	
	}

	TEST(TestsBinarySearchTree,Lazy1)
    {
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(3);
		ourtree->insert(8,4);
		ourtree->insert(9,8);
		ourtree->insert(11,2);
		ourtree->insert(15,6);
		ourtree->insert(17,12);
		ourtree->insert(18,0);
		ourtree->insert(22,1);
		ourtree->insert(23,3);
		ourtree->insert(24,5);
		ourtree->insert(25,555);
		ourtree->insert(26,666);
		ourtree->insert(28,888);
		ourtree->insert(55,4);
		ourtree->insert(1,8);
		ourtree->insert(4,2);
		ourtree->insert(44,6);
		ourtree->insert(55,12);
		ourtree->insert(3,0);
		ourtree->insert(99,1);
		ourtree->insert(7,3);
		ourtree->insert(5,5);
		ourtree->insert(16,555);
		ourtree->insert(30,666);
		ourtree->insert(32,888);
		ourtree->lazyinsert(33,888);
		ourtree->lazyinsert(35,888);
		ourtree->lazyinsert(27,888);
		ourtree->lazyinsert(14,888);
		ourtree->lazyinsert(12,888);
		ourtree->lazyinsert(37,888);
		ourtree->lazyinsert(31,888);
		ourtree->lazyinsert(100,888);
		std::vector<int> tocheck1={1,3,4,5,7,8,9,11,12,14,15,16,17,18,22,23,24,25,26,27,28,30,31,32,33,35,37, 44,55,99,100};
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck2.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->lazyremove(5);
		ourtree->lazyremove(7);
		ourtree->lazyremove(4);
		ourtree->lazyremove(3);
		ourtree->lazyremove(8);
		ourtree->lazyremove(11);
		ourtree->lazyremove(17);
		ourtree->lazyremove(16);
		ourtree->lazyremove(1);
		ourtree->lazyremove(9);
		ourtree->lazyremove(15);
		ourtree->lazyremove(24);
		ourtree->lazyremove(25);
		ourtree->lazyremove(44);
		ourtree->lazyremove(55);
		ourtree->lazyremove(99);
		ourtree->lazyremove(23);
		ourtree->lazyremove(28);
		ourtree->lazyremove(32);
		ourtree->lazyremove(26);
		ourtree->lazyremove(30);
		ourtree->fix();
		ourtree->lazyremove(22);
		ourtree->lazyremove(27);
		ourtree->lazyremove(18);
		ourtree->lazyremove(33);
		ourtree->lazyremove(35);
		ourtree->lazyremove(14);
		ourtree->lazyremove(12);
		ourtree->lazyremove(37);
		ourtree->fix();
		ourtree->lazyremove(31);
		ourtree->lazyremove(100);
		ourtree->fix();
		ourtree->print(0,ourtree->getroot());
		delete ourtree;  	
	}
	TEST(TestsBinarySearchTree,Lazy2)
    {
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(3);
		ourtree->insert(8,4);
		ourtree->insert(9,8);
		ourtree->insert(11,2);
		ourtree->insert(15,6);
		ourtree->insert(17,12);
		ourtree->insert(18,0);
		ourtree->insert(22,1);
		ourtree->insert(23,3);
		ourtree->insert(24,5);
		ourtree->insert(25,555);
		ourtree->insert(26,666);
		ourtree->insert(28,888);
		ourtree->insert(55,4);
		ourtree->insert(1,8);
		ourtree->insert(4,2);
		ourtree->insert(44,6);
		ourtree->insert(55,12);
		ourtree->insert(3,0);
		ourtree->insert(99,1);
		ourtree->insert(7,3);
		ourtree->insert(5,5);
		ourtree->insert(16,555);
		ourtree->insert(30,666);
		ourtree->insert(32,888);
		ourtree->lazyinsert(33,888);
		ourtree->lazyinsert(35,888);
		ourtree->lazyinsert(27,888);
		ourtree->lazyinsert(14,888);
		ourtree->lazyinsert(12,888);
		ourtree->lazyinsert(37,888);
		ourtree->lazyinsert(31,888);
		ourtree->lazyinsert(100,888);
		std::vector<int> tocheck1={1,3,4,5,7,8,9,11,12,14,15,16,17,18,22,23,24,25,26,27,28,30,31,32,33,35,37, 44,55,99,100};
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck2.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->lazyremove(5);
		ourtree->lazyremove(7);
		ourtree->lazyremove(4);
		ourtree->lazyremove(3);
		ourtree->lazyremove(8);
		ourtree->lazyremove(11);
		ourtree->lazyremove(17);
		ourtree->lazyremove(16);
		ourtree->lazyremove(1);
		ourtree->lazyremove(9);
		ourtree->lazyremove(15);
		ourtree->lazyremove(24);
		ourtree->lazyremove(25);
		ourtree->lazyremove(44);
		ourtree->lazyremove(55);
		ourtree->lazyremove(99);
		ourtree->lazyremove(23);
		ourtree->lazyremove(28);
		ourtree->lazyremove(32);
		ourtree->lazyremove(26);
		ourtree->lazyremove(30);
		ourtree->lazyremove(22);
		ourtree->lazyremove(27);
		ourtree->lazyremove(18);
		ourtree->lazyremove(33);
		ourtree->lazyremove(35);
		ourtree->fix();
		ourtree->lazyremove(14);
		ourtree->lazyremove(12);
		ourtree->lazyremove(37);
		ourtree->lazyremove(31);
		ourtree->lazyremove(100);
		ourtree->print(0,ourtree->getroot());
		delete ourtree;  	
	}
	TEST(TestsBinarySearchTree,Lazy3)
    {
    	std::ios_base::sync_with_stdio(0); 
		std::cin.tie(0);
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(1000);
		for (int i = 0; i < 100000; ++i)
		{
			ourtree->lazyinsert(i,i);
			if (i < 80000) tocheck1.push_back(i);
		}
		for (int i = 100000; i >= 80000; --i)
		{
			ourtree->lazyremove(i);
		}
		ourtree->fix();
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck2.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
    }
    TEST(TestsBinarySearchTree,Lazy4)
    {
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(1000);
		for (int i = 0; i < 100000; ++i)
		{
			ourtree->lazyinsert(i,i);
			ourtree->lazyremove(i);
		}
		ourtree->fix();
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
    }
    TEST(TestsBinarySearchTree,Lazy5)
    {
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(500);
		for (int i = 0; i < 5000; ++i)
		{
			ourtree->lazyinsert(i,i);
			if(i<1000 || i>=2000) tocheck1.push_back(i);
		}
		for (int i = 1000; i < 2000; ++i)
		{
			ourtree->lazyremove(i);
		}
		for (int i = 6000; i < 10000; ++i)
		{
			ourtree->insert(i,i);
			tocheck1.push_back(i);
		}
		ourtree->fix();
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck2.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
    }
    TEST(TestsBinarySearchTree,Lazy6)
    {
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(500);
		for (int i = 0; i < 50000; ++i)
		{
			ourtree->lazyinsert(i,i);
			if((i<1567 || i>45777) || (i>=9837 && i<=41222)) tocheck1.push_back(i);
		}
		for (int i = 1567; i < 9837; ++i)
		{
			ourtree->lazyremove(i);
		}
		for (int i = 45777; i > 41222; --i)
		{
			ourtree->remove(i);
		}
		ourtree->fix();
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck2.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
    }
    TEST(TestsBinarySearchTree,Lazy7)
    {
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(50);
		for (int i = 0; i < 50000; ++i)
		{
			ourtree->lazyinsert(i,i);
			if((i<1567 || i>82555) || (i>=9837 && i<=75439)) tocheck1.push_back(i);
		}
		for (int i = 1567; i < 9837; ++i)
		{
			ourtree->lazyremove(i);
		}
		for (int i = 82555; i > 75439; --i)
		{
			ourtree->remove(i);
		}
		ourtree->fix();
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck1.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
    }
     TEST(TestsBinarySearchTree,Lazy8)
    {
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(5);
		for (int i = 0; i < 1000; ++i)
		{
			ourtree->lazyinsert(i,i);
			tocheck1.push_back(i);
		}
		ourtree->fix();
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck1.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		ourtree->print(0,ourtree->getroot());
		delete ourtree;
    }
	 TEST(TestsBinarySearchTree,Lazy9)
    {
    	srand(time(NULL));
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(5);
		for (int i = 0; i < 10000; ++i)
		{
			tocheck1.push_back(i);
		}
		for (int i = 0; i < 2000; ++i)
		{
			int j=rand()%9999;
			int k=rand()%9999;
			int temp = tocheck1[j];
			tocheck1[j] = tocheck1[k];
			tocheck1[k] = temp;
		}
		for (int i = 0; i < tocheck1.size(); ++i)
		{
			ourtree->insert(tocheck1[i], tocheck1[i]);
		}
		
		sort(tocheck1.begin(), tocheck1.end());
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck1.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		for (int i = 2000; i < 8000; ++i)
		{
			ourtree->lazyremove(i);
		}
		ourtree->fix();
		for (int i = 0; i < 2000; ++i)
		{
			ourtree->lazyremove(i);
		}
		ourtree->fix();
		for (int i = 8000; i < 10000; ++i)
		{
			ourtree->remove(i);
		}
		delete ourtree;
    }
     TEST(TestsBinarySearchTree,Lazy10)
    {
    	srand(time(NULL));
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(5);
		for (int i = 0; i < 7889; ++i)
		{
			tocheck1.push_back(i);
		}
		for (int i = 0; i < 6000; ++i)
		{
			int j=rand()%7888;
			int k=rand()%7888;
			int temp = tocheck1[j];
			tocheck1[j] = tocheck1[k];
			tocheck1[k] = temp;
		}
		for (int i = 0; i < tocheck1.size(); ++i)
		{
			ourtree->lazyinsert(tocheck1[i], tocheck1[i]);
		}
		
		sort(tocheck1.begin(), tocheck1.end());
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck1.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		delete ourtree;
    }
    TEST(TestsBinarySearchTree,deletation)
    {
    	srand(time(NULL));
    	std::vector<int> tocheck1={};
		BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(5);
		for (int i = 0; i < 7889; ++i)
		{
			tocheck1.push_back(i);
		}
		for (int i = 0; i < 6000; ++i)
		{
			int j=rand()%7888;
			int k=rand()%7888;
			int temp = tocheck1[j];
			tocheck1[j] = tocheck1[k];
			tocheck1[k] = temp;
		}
		for (int i = 0; i < tocheck1.size(); ++i)
		{
			ourtree->lazyinsert(tocheck1[i], tocheck1[i]);
		}
		sort(tocheck1.begin(), tocheck1.end());
		std::vector<int> tocheck2={};
		getvectortocheck(tocheck2, *ourtree);
		for (int i = 0; i < tocheck1.size(); ++i)
		{
			// std::cout<<tocheck2[i]<<" ";
			ASSERT_EQ(tocheck1[i], tocheck2[i]);
		}
		for (int i = 0; i < 50000; ++i)
		{
			int j=rand()%7888;
			ourtree->remove(j);
		}
		for (int i = 0; i < 7889; ++i)
		{
			ourtree->remove(i);
		}
		delete ourtree;
    }
}
// //g++ -std=c++11 -stdlib=libc++  BPlusTree.cpp BPlusTreeTests.cpp BPlusTree_main.cpp -lgtest -lpthread -o BPlusTreeTests
// //valgrind --leak-check=full --leak-resolution=high ./BPlusTreeTest

