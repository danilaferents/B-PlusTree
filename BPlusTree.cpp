//
//  BPlusTree.cpp
//  
//
//  Created by Ferents Danila.
//
#include "BPlusTree.hpp"
namespace BPlusTreeN
{
	//find leaf to insert value and key
	template <typename KeyT,typename ValueT> 
	Node<KeyT,ValueT>* BPlusTree<KeyT,ValueT>::findtoinsert(const KeyT& key)
	{
		Node<KeyT, ValueT> *current = this->root; //start froom root node
		while (current->getleaf() != true) //need to reach leaf
		{
			for (int i = 0; i <= current->getkey_num(); ++i) //go through all keys in every level
			{
				// std::cout<<"i: "<<i;
				if ((i == current->getkey_num() || (current->getkeys() && key < current->getkeys()[i]))) 
				{
					current = current->getchilds()[i]; 
					break;
				}
			}
			// if (current->getleaf() != true) std::cout<<"1";
		}
		return current;
	}
	//split is appropriate when node has 2 * nodecapacity keys
	template <typename KeyT,typename ValueT> 
	void BPlusTree<KeyT,ValueT>::split(Node<KeyT,ValueT> *node)
	{
		//redirecting right and left pointers
		Node<KeyT, ValueT> *newnode = new Node<KeyT, ValueT>(this->nodecapacity,node->getleaf());
		newnode->setright(node->getright());
		if (node->getright()) node->getright()->setleft(newnode); //check if right node not nullptr
		node->setright(newnode);
		newnode->setleft(node);

		//realocating nodecapacity - 1 keys and their values to newnode
		KeyT mid_key = node->getkeys()[nodecapacity];
		ValueT mid_value = node->getvalues()[nodecapacity];
		newnode->setkey_num(nodecapacity-1);
		node->setkey_num(nodecapacity);  
//need to check if we in leaf and do not have to reallocate values
		for (int i = 0; i < newnode->getkey_num(); ++i)
		{
			newnode->setkeys(i,node->getkeys()[i+nodecapacity+1]);
			newnode->setvalues(i,node->getvalues()[i+nodecapacity+1]);
			newnode->setchilds(i, node->getchilds()[i+nodecapacity+1]); // maybe check for leaf
		}
		newnode->setchilds(newnode->getkey_num(), node->getchilds()[2 * nodecapacity]);//add last child
//letter decide about what to do with children
		//if splitting node is leafe we need to add middle value to newnode values
		if (node->getleaf()) 
		{
			newnode->setkey_num((newnode->getkey_num())+1);
			newnode->setleaf(true);
			//reallocating values and keys
			for(int j = newnode->getkey_num()-1; j>0;j--)
			{
				newnode->setkeys(j, newnode->getkeys()[j-1]);
				newnode->setvalues(j, newnode->getvalues()[j-1]);
			}
			//setting middle value to newnode values
			newnode->setkeys(0, mid_key);
			newnode->setvalues(0, mid_value);
		}

		//if splitting node - root we need to create new one 
		if (node == this->root)
		{
			this->root= new Node<KeyT, ValueT>(this->nodecapacity,false);
			//add middle key to new root node and set node and newnode as childs
			this->root->setkeys(0, mid_key); 
			this->root->setvalues(0, mid_value);
			this->root->setchilds(0, node);
			this->root->setchilds(1, newnode);
			this->root->setkey_num(1);
			//set parents to node and newnode
			node->setparent(this->root);
			newnode->setparent(this->root);
		}
		else 
		{
			//remember node parent 
			Node<KeyT, ValueT> *helpparent = node->getparent();
			//set to newnode the same parent
			newnode->setparent(helpparent); 

			//find position in parent node to insert middle
			size_t position = 0;
			while (position < helpparent->getkey_num() && (helpparent->getkeys() && helpparent->getkeys()[position] < mid_key))
				++position;
			//reallocate keys 
			for(size_t i = helpparent->getkey_num(); i >= position +1; i--)
			{
				helpparent->setkeys(i, helpparent->getkeys()[i-1]);
			}
//need to add if we at leaf and do not have childs
			//reallocate children 
			for(size_t i = helpparent->getkey_num(); i >= position +2; i--)
			{
				helpparent->setchilds(i, helpparent->getchilds()[i-1]);
			}
			//insert middle key and children
			helpparent->setkeys(position, mid_key);
			helpparent->setchilds(position+1, newnode);
			helpparent->setkey_num(helpparent->getkey_num()+1);
			//split in case parrent now has more keys that allowed
			if (helpparent->getkey_num() == 2 * this->nodecapacity)
				split(helpparent);
		}
	}

	//intersection of key and value
	template <typename KeyT,typename ValueT> 
	bool BPlusTree<KeyT,ValueT>::insert(const KeyT& key,const ValueT& value)
	{
		//if tree is emrty add as root
		if (root == nullptr)
		{
			Node<KeyT, ValueT> *newroot = new Node<KeyT, ValueT>(this->nodecapacity,true);
			newroot->setkeys(0,key);
			newroot->setvalues(0,value);
			newroot->setkey_num(1);
			root = newroot;
			return true;
		}
		//find leaf to insert
		Node<KeyT, ValueT>* curleaf = findtoinsert(key);
		//if key in keys return false
		if (curleaf->iskeyinnode(key))
			return false;

		//find position to insert
		size_t position = 0;
		while(position < curleaf->getkey_num() && (curleaf->getkeys() && curleaf->getkeys()[position] < key))
			position++;

		

		//reallocate keys and values
		for (int i = curleaf->getkey_num(); i > position; i--)
		{
			if (curleaf->getkeys()) curleaf->setkeys(i, curleaf->getkeys()[i-1]);
			if (curleaf->getvalues()) curleaf->setvalues(i, curleaf->getvalues()[i-1]);
		}

		size_t help = curleaf->getkey_num();
		help++;
		curleaf->setkey_num(help);
		
		//add key and value			
		curleaf->setkeys(position, key);
		curleaf->setvalues(position, value);
		//start split if we have overflow
		if (curleaf->getkey_num() == (2 * nodecapacity))
			split(curleaf);
		return true;
	}

	//print tree
	template <typename KeyT,typename ValueT> 
	void BPlusTree<KeyT,ValueT>::print(size_t k, Node<KeyT, ValueT>* curleaf)
	{
		if (!curleaf) return;

		for (int i = 0; i < k; ++i)
		{
			std::cout<<"*";
		}
		std::cout<<*curleaf;
		if (curleaf->getleaf()) return;
		for (int i = 0; i <=curleaf->getkey_num(); ++i)
		{
			// std::cout<<"k: "<<k<<"i: "<<i<<std::endl;
			if (curleaf->getchilds()) print(k+1,curleaf->getchilds()[i]);
		}
	}
}
using namespace BPlusTreeN;
// template struct BPlusTreeN::Node<int,int>;
// template class BPlusTreeN::BPlusTree<int,int>;
// BPlusTreeN::BPlusTree<int,int> *jk = new BPlusTreeN::BPlusTree<int,int>();
// int main()
// {
// 	// Node<char,int> *root = new Node<char,int>(2,true);
// 	BPlusTree<char,int> *ourtree = new BPlusTree<char,int>(2);
// 	ourtree->insert('d',3);
// 	// if (!ourtree->getroot()) std::cout<<"nullptr";
// 	ourtree->insert('c',6);
// 	// std::cout<<ourtree->getroot()->getkey_num();
// 	// std::cout<<ourtree->getcapacity();
// 	// std::cout<<ourtree->getroot()->getkeys()[2];
// 	// for (int i = 0; i <=ourtree->getroot()->getkey_num(); ++i)
// 	// 	{
// 	// 		if((ourtree->getroot()->getchilds()[i])) 
// 	// 		{
// 	// 			for (int j = 0; j < ourtree->getroot()->getchilds()[i]->getkey_num(); ++j)
// 	// 			{
// 	// 				if (ourtree->getroot()->getchilds()[i]->getkeys()) 
// 	// 				{
// 	// 					std::cout<<((ourtree->getroot()->getchilds()[i]->getkeys())[j])<<std::endl;
// 	// 				}
// 	// 			}
// 	// 		}
// 	// 	}
// 	ourtree->print(0,ourtree->getroot());
// }