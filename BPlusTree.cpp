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
		// Node<KeyT, ValueT> *helpnode = node;
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
			// std::cout<<"i: "<<i<<"i+nodecapacity+1 "<<i+nodecapacity+1<<std::endl;
		}
		newnode->setchilds(newnode->getkey_num(), node->getchilds()[2 * nodecapacity]); //add last child
		// std::cout<<"newnode->getkey_num() "<<newnode->getkey_num()<<"2 * nodecapacity "<<2 * nodecapacity<<std::endl;
		for (int i = 0; i <= newnode->getkey_num(); ++i)
		{
			if(newnode->getchilds() && newnode->getchilds()[i])
			{
		// 	// 	if(newnode->getchilds()[i])
		// 	// 		std::cout<<"childs"<<std::endl;
		// 	// 	else 
		// 	// 		std::cout<<"no child"<<std::endl;
		// 	// 	std::cout<<*newnode<<std::endl;
		// 	// 	// std::cout<<*newnode->getchilds()[i]<<std::endl;
				newnode->getchilds()[i]->setparent(newnode);
			}
		}
		// std::cout<<"REFERENCE";
		// std::cout<<"Node: "<<*node<<"Right reference of node: "<<*node->getright()<<"new node: "<<*newnode<<"left reference newnode: "<<*newnode->getleft();
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
			// std::cout<<"BEFORE----------";
			// std::cout<<"node++++";
			// std::cout<<*node<<std::endl;
			// std::cout<<"node----"<<std::endl;
			// std::cout<<"WTF";
			// if (node->getparent()) std::cout<<*(node->getparent())<<std::endl;
			// std::cout<<"WTF"<<std::endl;
		//if splitting node - root we need to create new one 
		// std::cout<<node<<" "<<this->root<<" ";
		if (node == this->root)
		{
			// std::cout<<std::endl;
			// std::cout<<"---------------------"<<std::endl;
			// std::cout<<"I was here   "<<std::cout;
			// std::cout<<*helpnode<<std::endl;
			// std::cout<<"---------------------"<<std::endl;
			this->root= new Node<KeyT, ValueT>(this->nodecapacity,false);
			//add middle key to new root node and set node and newnode as childs
			this->root->setkeys(0, mid_key); 
			this->root->setvalues(0, mid_value);
			this->root->setchilds(0, node);
			this->root->setchilds(1, newnode);
			this->root->setkey_num(1);
			// this->root->getchilds()[0]->setright(this->root->getchilds()[1]);
			// this->root->getchilds()[1]->setleft(this->root->getchilds()[0]);
			//set parents to node and newnode
			node->setparent(this->root);
			newnode->setparent(this->root);
			//mistake in photos

			// for (int i = 0; i <= newnode->getkey_num(); ++i)
			// {
			// 	if(newnode->getchilds() && newnode->getchilds()[i])
			// 	{

			// 			// std::cout<<*(newnode->getchilds()[i]);
			// 			(newnode->getchilds()[i])->setparent(newnode);
			// 			// if (newnode->getchilds()[i]) std::cout<<"childs";
			// 			// else std::cout<<"no childs";
			// 	}
			// }
		}
		else 
		{
			//remember node parent 
			newnode->setparent(node->getparent()); 
			Node<KeyT, ValueT> *helpparent = node->getparent();
			//set to newnode the same parent
			// std::cout<<"node++++";
			// std::cout<<*node<<std::endl;
			// std::cout<<"node----"<<std::endl;
			// std::cout<<"WTF";
			// std::cout<<*helpparent<<std::endl;
			// std::cout<<"WTF"<<std::endl;
			//find position in parent node to insert middle
			size_t position = 0;
			while (position < helpparent->getkey_num() && (helpparent->getkeys() && helpparent->getkeys()[position] < mid_key))
				++position;
			//reallocate keys 
			for(size_t i = helpparent->getkey_num() ; i >= position +1; i--)
			{
				helpparent->setkeys(i, helpparent->getkeys()[i-1]);
				helpparent->setvalues(i, helpparent->getvalues()[i-1]);
			}
//need to add if we at leaf and do not have childs
			//reallocate children 
			for(size_t i = helpparent->getkey_num() + 1; i >= position +2; i--) //add + 1 to helpparent->getkey_num()
			{
				helpparent->setchilds(i, helpparent->getchilds()[i-1]);
			}
			//insert middle key and children
			helpparent->setkeys(position, mid_key);
			helpparent->setvalues(position, mid_value);
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
	template <typename KeyT,typename ValueT> 
	bool BPlusTree<KeyT,ValueT>::remove(const KeyT& key)
	{
		Node<KeyT, ValueT> *current = findtoinsert(key);
		//if key in node then start delete from key else return wothin npthing to remove
		for (int i = 0; i < current->getkey_num(); ++i)
		{
			if (current->getkeys() && current->getkeys()[i] == key) 
			{
				removeinnode(current, key, 1);
				return true;
			}
		}
		return false;
	}
	template <typename KeyT,typename ValueT> 
	void BPlusTree<KeyT,ValueT>::update(Node<KeyT, ValueT>* current,const KeyT key, const KeyT insertkey)
	{
		// Node<KeyT, ValueT> *help = current->getparent();
		// std::cout<<"KEY: "<<key<<"Replace:"<<insertkey<<std::endl;
		if (current) 
		{
			// size_t position = 0;
			// while(position < current->getkey_num() && current->getkeys()[position] < key) 
			// 	position++;
			for (int i = 0; i < current->getkey_num(); ++i)
			{
				if (current->getkeys()[i] == key) 
				{
					current->setkeys(i, insertkey);
					return;
				}
			}
			// if (current->getparent()) std::cout<<"Parent:"<<*current->getparent();
			if (current->getparent()) this->update(current->getparent(), key, insertkey);
		}
	}
	template <typename KeyT,typename ValueT> 
	void BPlusTree<KeyT,ValueT>::updateall(Node<KeyT, ValueT>* current)
	{
		while(current)
		{
			for (int i = 0; i < current->getkey_num(); ++i)
			{
				if (current->getchilds()[i+1])
				{
					current->setkeys(i, minimumkey(current->getchilds()[i+1]));
				}
			}
			current = current->getparent();
		}

	}
	template <typename KeyT,typename ValueT> 
	KeyT BPlusTree<KeyT,ValueT>::minimumkey(Node<KeyT, ValueT>* current)
	{
		KeyT helpkey = current->getkeys()[0];
		while(current)
		{
			helpkey = current->getkeys()[0];
			current = current->getchilds()[0];
		}
		return helpkey;
	}
	template <typename KeyT,typename ValueT> 
	void BPlusTree<KeyT,ValueT>::removeinnode(Node<KeyT, ValueT>* current, const KeyT key, const size_t flag)
	{
		// std::cout<<"newonekey: "<<key<<std::endl;
		//check another time
		bool ifin=false;
		for (int i = 0; i < current->getkey_num(); ++i)
		{
			if (current->getkeys()[i] == key) 
			{
				ifin=true;
				break;
			}
		}
		if (!ifin) return;

		// std::cout<<*current<<std::endl<<key;
		// std::cout<<"I AM HERE"<<std::endl;

		//find deleting key's position
		size_t position = 0;
		while(position < current->getkey_num() && current->getkeys() && current->getkeys()[position] < key)
			position++;
		// std::cout<<position<<std::endl;
		// std::cout<<"key: "<<key<<"position:"<<position<<std::endl;
		//delete key
		for(size_t i = position; i < current->getkey_num() - 1; i++)
		{
			current->setkeys(i, current->getkeys()[i+1]);
			current->setvalues(i, current->getvalues()[i+1]);
			// std::cout<<" i "<<i<<" "<<current->getkeys()[i]<<" i+1: "<<i+ 1<<" "<<current->getkeys()[i+1]<<std::endl;
		}

//*** if we in leafe and do not need children so else lets see
		if (flag)
		{
			for(size_t i = position + 1; i < current->getkey_num(); i++)
			{
				// if(current->getchilds() && current->getchilds()[i] && current->getchilds()[i+1]) std::cout<<"i: "<<i<<"value: "<<*current->getchilds()[i]<<"i+1: "<<i+1<<"value: "<<*current->getchilds()[i+1]<<std::endl;
				current->setchilds(i, current->getchilds()[i+1]);
			}
		}
		else 
		{
			for(size_t i = position; i < current->getkey_num(); i++)
			{
				// if(current->getchilds() && current->getchilds()[i] && current->getchilds()[i+1]) std::cout<<"i: "<<i<<"value: "<<*current->getchilds()[i]<<"i+1: "<<i+1<<"value: "<<*current->getchilds()[i+1]<<std::endl;
				current->setchilds(i, current->getchilds()[i+1]);
			}
		}
		// std::cout<<"KEY1: "<<key;
		current->setkey_num(current->getkey_num() - 1);
		// std::cout<<"key_num"<<current->getkey_num()<<"nodecapacity"<<nodecapacity - 1;
		// std::cout<<"BEFORE DOING IT";
		// print(0,root);
		if (current->getkey_num() < nodecapacity - 1) //check if we have min elements as if we have leaf that has more than min elements than we can delete safely 
		{
			Node<KeyT, ValueT>* right_sibling = current->getright();
			Node<KeyT, ValueT>* left_sibling = current->getleft();
			if (left_sibling!=nullptr && left_sibling->getkey_num() > nodecapacity - 1) //check if one of siblings has more than min elements
			{
				left_sibling->setkey_num(left_sibling->getkey_num()-1);
				current->setkey_num(current->getkey_num() + 1);
				//rellocate max key from leftsibling to first position in current
				current->setchilds(current->getkey_num(), current->getchilds()[current->getkey_num() - 1]);
				for (int i = current->getkey_num() - 1; i > 0; --i) // забыл что мы сместили уже вершины после удаления
				{
					current->setkeys(i, current->getkeys()[i-1]);
					current->setvalues(i, current->getvalues()[i-1]);
// --check childs
					current->setchilds(i, current->getchilds()[i-1]);
				}
				
//was mistake in indexes
				current->setkeys(0, left_sibling->getkeys()[left_sibling->getkey_num()]);
				current->setvalues(0, left_sibling->getvalues()[left_sibling->getkey_num()]);
// --check childs
				current->setchilds(0, left_sibling->getchilds()[left_sibling->getkey_num() + 1]);
				
				//maybe right update - change key to changed key
				// current->getparent()->setkeys(0, current->getkeys()[?]);
				// std::cout<<"KEY: "<<key<<"Replace:"<<current->getkeys()[0]<<std::endl;
				update(current->getparent(), key,current->getkeys()[0]); 
				
			}
			else if (right_sibling != nullptr && right_sibling->getkey_num() > nodecapacity - 1)
			{
				right_sibling->setkey_num(right_sibling->getkey_num()-1);
				current->setkey_num(current->getkey_num() + 1);

				//rellocate max key from rightsibling to last position in current
//mistake in reallocating indexes
				
				
//--misteke in index max key in left sibling
				current->setkeys(current->getkey_num() - 1, right_sibling->getkeys()[0]);
				current->setvalues(current->getkey_num() - 1, right_sibling->getvalues()[0]);
				current->setchilds(current->getkey_num(), right_sibling->getchilds()[0]);


				for (int i = 0; i < right_sibling->getkey_num(); ++i)
				{
					right_sibling->setkeys(i, right_sibling->getkeys()[i+1]);
					right_sibling->setvalues(i, right_sibling->getvalues()[i+1]);
					right_sibling->setchilds(i, right_sibling->getchilds()[i+1]);
				}
				right_sibling->setchilds(right_sibling->getkey_num(),right_sibling->getchilds()[right_sibling->getkey_num() + 1]);
				
				// current->getparent()->setkeys(?,current->getkeys()[current->getkey_num() - 1]);
				//последний случай сломал этот апдейт мб можно длописать пока оставлю полный
				update(right_sibling, current->getkeys()[current->getkey_num() - 1], right_sibling->getkeys()[0]);
				update(current, key, current->getkeys()[0]); //если удалена была нулевая 
				updateall(current); //пришлось добавить тк 4 случай ломал норм апдейт
			}
			else //if siblings has also min;
			{
				if (left_sibling != nullptr)
				{
					// std::cout<<"I was here"<<std::endl;
					for (int i = 0; i < current->getkey_num(); ++i)
					{
						size_t leftsiblingkey_num = left_sibling->getkey_num();
						left_sibling->setkeys(leftsiblingkey_num, current->getkeys()[i]);
						left_sibling->setvalues(leftsiblingkey_num, current->getvalues()[i]);
						left_sibling->setchilds(leftsiblingkey_num + 1, current->getchilds()[i]); //same question about lost child but probably in leaf we do not have them
						left_sibling->setkey_num(leftsiblingkey_num+=1);
					}
					//надо не забыть удалить всe что было в курент

					left_sibling->setchilds(left_sibling->getkey_num(), current->getchilds()[current->getkey_num()]);

					//reallocating left and right pointers
					left_sibling->setright(current->getright());
					if (current->getright()) current->getright()->setleft(left_sibling);

					//update(left_sibling)
					//надо обновить вершину и пустить удаление уже от нее
					current->setkey_num(0);
					if(current->getparent() && left_sibling->getparent() && (current->getparent() != left_sibling->getparent()))
					{
						//проблемы со случаем на фотке от четверга 
						update(current->getparent(), key, current->getparent()->getkeys()[0]);
						std::cout<<"I was Here 1";
						// updateall(current);
						removeinnode(current->getparent(), current->getparent()->getkeys()[0], 0);
					}
					else
					{
						std::cout<<"I was Here 2";
						// updateall(current);
						// update(current->getparent(), key, left_sibling->getkeys()[left_sibling->getkey_num() - 1]);
						removeinnode(current->getparent(),minimumkey(current), 1); //min_key in current 
					}
					// delete current;
				}//do not check down
				else 
				{
					if (right_sibling!=nullptr)
					{
						std::cout<<"I was Here";
						for(int i = 0;i < right_sibling->getkey_num();i++)
						{
							size_t currentkey_num = current->getkey_num();
							current->setkeys(currentkey_num, right_sibling->getkeys()[i]);
							current->setvalues(currentkey_num, right_sibling->getvalues()[i]);
							current->setchilds(currentkey_num + 1, right_sibling->getchilds()[i]);
							current->setkey_num(currentkey_num+=1);
						}
						if (right_sibling->getchilds()[right_sibling->getkey_num()])
						{
							current->setchilds(current->getkey_num() + 1, right_sibling->getchilds()[right_sibling->getkey_num()]);
							current->setkey_num(current->getkey_num() + 1);
						}
						//не забыть удалить все что было в правой
						//reallocating left and right pointers	

						current->setright(right_sibling->getright());
						if (right_sibling->getright()) right_sibling->getright()->setleft(current);
						// update();
						//update(current);
						// update(current->getpare, right_sibling->getkeys()[0]);
						// right_sibling->setkey_num(0);
						// for (int i = 0; i < current->getkey_num(); ++i)
						// {
						// 	if (current->getchilds() && current->getchilds()[i]) update(current, current->getkeys()[i], current->getchilds()[i+1]->getkeys()[0]);
						// }
						// for (int i = 0; i < current->getparent()->getkey_num(); ++i)
						// {
						// 	if (current->getparent()->getchilds() && current->getparent()->getchilds()[i]) update(current->getparent(), current->getparent()->getkeys()[i], current->getchilds()[i+1]->getkeys()[0]);
						// }
						updateall(current);
						removeinnode(current->getparent(), minimumkey(right_sibling), 1);
						// removeinnode(right_sibling, right_sibling->getkeys()[0], 1);
						// insert(right_sibling->getkeys()[0], right_sibling->getvalues()[0]);
						// delete right_sibling;
					}
				}	
			} 
		}
			if (position == 0) update(current->getparent(), key, current->getkeys()[position]);
			if (root->getkey_num() == 1)
			{
				for (int i = 0; i <= root->getkey_num(); ++i)
				{
					if (root->getchilds() && root->getchilds()[i] && root->getchilds()[1] && root->getchilds()[1]->getkey_num() == 0)
					{
						root = root->getchilds()[0];
						delete root->getchilds()[1];
					}
				}
				// Node<KeyT, ValueT>* help = root->getchilds()[1];
				
				// root->setchilds(1, help);
			}
	}
}
using namespace BPlusTreeN;
template struct BPlusTreeN::Node<int,int>;
template class BPlusTreeN::BPlusTree<int,int>;
// BPlusTreeN::BPlusTree<int,int> *jk = new BPlusTreeN::BPlusTree<int,int>();
int main()
{
		// Node<int, int> *ournode= new Node<int, int>(2, true);
		// ournode->setkey_num(2);
		// Node<int, int> *helpnode= nullptr;
		// ournode->setchilds(0, helpnode);
		// std::cout<<*ournode;



		// BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		// ourtree->insert(27,4);
		// ourtree->insert(52,8);
		// ourtree->insert(20,2);
		// ourtree->insert(42,6);
		// ourtree->insert(93,12);
		// ourtree->insert(7,0);
		// ourtree->insert(14,1);
		// ourtree->insert(21,3);
		// ourtree->insert(34,5);
		// ourtree->insert(47,7);
		// ourtree->insert(64,9);
		// ourtree->insert(72,10);
		// ourtree->insert(91,11);
		// ourtree->insert(97,13);
		// ourtree->print(0,ourtree->getroot());


		//test for deleting key and borrow key from left sibling 
		//  BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		// ourtree->insert(8,4);
		// ourtree->insert(9,8);
		// ourtree->insert(11,2);
		// ourtree->insert(15,6);
		// ourtree->insert(17,12);
		// ourtree->insert(18,0);
		// ourtree->insert(22,1);
		// ourtree->insert(23,3);
		// ourtree->insert(24,5);
		// ourtree->insert(25,555);
		// ourtree->insert(26,666);
		// ourtree->insert(28,888);
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(24)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(25)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());

		//test for deleting key and borrow key from right sibling 
		// BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		// ourtree->insert(8,4);
		// ourtree->insert(9,8);
		// ourtree->insert(11,2);
		// ourtree->insert(15,6);
		// ourtree->insert(17,12);
		// ourtree->insert(18,0);
		// ourtree->insert(22,1);
		// ourtree->insert(23,3);
		// ourtree->insert(24,5);
		// ourtree->insert(25,555);
		// ourtree->insert(26,666);
		// ourtree->insert(28,888);
		// // ourtree->print(0,ourtree->getroot());
		// // std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(15)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(11)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		
		// BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(2);
		// ourtree->insert(8,4);
		// ourtree->insert(9,8);
		// ourtree->insert(11,2);
		// ourtree->insert(15,6);
		// ourtree->insert(17,12);
		// ourtree->insert(18,0);
		// ourtree->insert(22,1);
		// ourtree->insert(23,3);
		// ourtree->insert(24,5);
		// ourtree->insert(25,555);
		// ourtree->insert(26,666);
		// ourtree->insert(28,888);
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(18)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(15)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(8)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// if(ourtree->remove(11)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());

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
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(5)) std::cout<<"Have to remove"<<std::endl;
		// // ourtree->print(0,ourtree->getroot());
		// // std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(7)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// // std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(4)) std::cout<<"Have to remove"<<std::endl;
		// // ourtree->print(0,ourtree->getroot());
		// // std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(3)) std::cout<<"Have to remove"<<std::endl;
		// // ourtree->print(0,ourtree->getroot());
		// // std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(8)) std::cout<<"Have to remove"<<std::endl;
		// // ourtree->print(0,ourtree->getroot());
		// ourtree->insert(33,888);
		// ourtree->insert(19,888);
		// ourtree->insert(20,888);
		// ourtree->insert(110,2);
		// ourtree->insert(111,6);
		// ourtree->insert(1112,12);
		// ourtree->insert(555,0);
		// ourtree->insert(444,1);
		// ourtree->print(0,ourtree->getroot());

		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(1)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(11)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(17)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(16)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(1)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		if(ourtree->remove(15)) std::cout<<"Have to remove"<<std::endl;

		if(ourtree->remove(24)) std::cout<<"Have to remove"<<std::endl;
		if(ourtree->remove(25)) std::cout<<"Have to remove"<<std::endl;
		if(ourtree->remove(44)) std::cout<<"Have to remove"<<std::endl;
		if(ourtree->remove(55)) std::cout<<"Have to remove"<<std::endl;

		if(ourtree->remove(99)) std::cout<<"Have to remove"<<std::endl;
		if(ourtree->remove(23)) std::cout<<"Have to remove"<<std::endl;
		if(ourtree->remove(28)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		ourtree->print(0,ourtree->getroot());

		// std::cout<<"MINKEY:"<<ourtree->minimumkey(ourtree->getroot()->getchilds()[1]);
		// BPlusTree<int,int> *ourtree = new BPlusTree<int,int>(3);
		// ourtree->insert(7,4);
		// ourtree->insert(8,8);
		// ourtree->insert(14,2);
		// ourtree->insert(20,6);
		// ourtree->insert(21,6);
		// ourtree->insert(27,6);
		// // ourtree->insert(34,6);
		// // ourtree->insert(42,6);
		// // ourtree->insert(47,6);
		// // ourtree->insert(48,6);
		// // ourtree->insert(52,6);
		// // ourtree->insert(64,6);
		// // ourtree->insert(72,6);
		// // ourtree->insert(90,6);
		// // ourtree->insert(91,6);
		// // ourtree->insert(93,6);
		// // ourtree->insert(94,6);
		// // ourtree->insert(97,6);
		// ourtree->print(0,ourtree->getroot());
		// if(ourtree->remove(14)) std::cout<<"Have to remove"<<std::endl;
		// if(ourtree->remove(8)) std::cout<<"Have to remove"<<std::endl;
		// if(ourtree->remove(20)) std::cout<<"Have to remove"<<std::endl;
		// // if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// // if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// // if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// // if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// // if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// // if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// // if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// ourtree->print(0,ourtree->getroot());
		// // / std::cout<<"-------NEW TREE!!!---------"<<std::endl;
		// // if(ourtree->remove(9)) std::cout<<"Have to remove"<<std::endl;
		// // ourtree->print(0,ourtree->getroot());
		// // ourtree->insert(17,12);
		// // ourtree->insert(18,0);
		// // ourtree->insert(22,1);
		// // ourtree->insert(23,3);
		// // ourtree->insert(24,5);
		// // ourtree->insert(25,555);
		// // ourtree->insert(26,666);
}