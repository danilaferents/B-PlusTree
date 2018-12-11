//
//  BPlusTree.hpp
//  
//
//  Created by Ferents Danila.
//
#ifndef BPlusTree_hpp
#define BPlusTree_hpp
#include <iostream>
#include <vector>
#include <stdio.h>
namespace BPlusTreeN
{

	template <typename KeyT,typename ValueT>
	struct Node 
	{
		private:
			bool leaf;
			size_t key_num;
			KeyT *keys;
			Node *parent;
			Node **childs;
			bool *deads;
			ValueT *values;
			Node *left;
			Node *right;
		public:
			Node()
			{

			}
			Node(const size_t &capacity,const bool &ourbool)
			{
				leaf=ourbool;
				key_num=0;
				keys=new KeyT[2*capacity];
				for (int i = 0; i < 2*capacity; ++i)
				{
					keys[i] = 0;
				}
				deads=new bool[2*capacity];
				for(size_t i = 0; i < 2*capacity; i++)
				{
					deads[i] = false;
				}
				parent=nullptr;
				childs=new Node<KeyT,ValueT>*[2*capacity+1]; //more children 
				for (int i = 0; i <2*capacity+1; ++i)
				{
					childs[i]=nullptr;
				}
				left=nullptr;
				right=nullptr;
				values=new ValueT[2*capacity];
				for (int i = 0; i < 2*capacity; ++i)
				{
					values[i] = 0;
				}
			}
			~Node()
			{
				if (keys) delete[] keys;
				if(values) delete[] values;
				if (childs) delete[] childs;
				if (deads) delete[] deads;
			}
			bool iskeyinnode(const KeyT& findkey)
			{
				for (int i = 0; i < key_num; ++i)
				{
					if(keys && keys[i] == findkey)
					{
						return true;
					}
				}
				return false;
			}
			bool getleaf()
			{
				return this->leaf;
			}
			void setleaf(const bool& currentleaf)
			{
				this->leaf = currentleaf;
			}
			size_t getkey_num()
			{
				return this->key_num;
			}
			void setkey_num(const size_t& nodesize)
			{
				this->key_num = nodesize;
			}
			KeyT *getkeys()
			{
				return this->keys;
			}
			void setkeys(const size_t& index,const KeyT& keyvalue)
			{
				if (this->keys) this->keys[index] = keyvalue;
			}
			Node *getparent()
			{
				return this->parent;
			}
			bool* getdeads()
			{
				return this->deads;
			}
			void setdeads(const size_t& index, const bool& insertbool)
			{
				if (this->deads) this->deads[index] = insertbool;
			}
			void setparent(Node* currentparent)
			{
				this->parent = currentparent;
			}
			Node **getchilds()
			{
				return this->childs;
			}
			void setchilds(const size_t& index,Node * insertnode)
			{
				if (this->childs) this->childs[index] = insertnode;
			}
			ValueT *getvalues()
			{
				return this->values;
			}
			void setvalues(const size_t& index, const ValueT& insertvalue)
			{
				if (this->values) this->values[index] = insertvalue;
			}
			Node *getleft()
			{
				return this->left;
			}
			void setleft(Node *insertleft)
			{
				this->left=insertleft;
			}
			Node *getright()
			{
				return this->right;
			}
			void setright(Node *insertright)
			{
				this->right = insertright;
			}
			friend std::ostream& operator<<(std::ostream& os, Node& current)
	        {
	        	// if (current.getleaf() == true) std::cout<<"true";
	        	// else std::cout<<"false";
	        	// os<<"Keys:"<<std::endl;
	        	for (int i = 0; i < current.getkey_num(); ++i)
	        	{
	        		if(current.getkeys()) os<<current.getkeys()[i]<<" ";
	        		// if(current.getdeads()) os<<current.getdeads()[i]<<" ";
	        		// if(current.getleaf() && current.getvalues()) os<<current.getvalues()[i]<<" ";
	        	}
	        	os<<std::endl;
	        	
		        // 	os<<std::endl<<"Left Sibling: "<<std::endl;
		        // 	if (current.left) 
		        // 	{
		        // 		for (int i = 0; i < current.getleft()->getkey_num(); ++i)
			       //  	{
			       //  		if( current.getleft()->getkeys()) os<<current.getleft()->getkeys()[i]<<" ";
			       //  		// if(current.getleaf() && current.getvalues()) os<<current.getvalues()[i]<<" ";
			       //  	}
		        // 	}
		        // 	else os<<"nullptr"<<std::endl;
		        // 	os<<std::endl<<"Right Sibling: "<<std::endl;
		        // 	if (current.right) 
		        // 	{
		        // 		for (int i = 0; i < current.getright()->getkey_num(); ++i)
			       //  	{
			       //  		if( current.getright()->getkeys()) os<<current.getright()->getkeys()[i]<<" ";
			       //  		// if(current.getleaf() && current.getvalues()) os<<current.getvalues()[i]<<" ";
			       //  	}
		        // 	}
		        // 	else os<<"nullptr"<<std::endl;
	        	// if (current.leaf)
	        	// {	
		        // 	os<<std::endl<<"Values:"<<std::endl;
		        // 	for (int i = 0; i < current.getkey_num(); ++i)
		        // 	{
		        // 		if(current.getvalues()) os<<current.getvalues()[i]<<" ";
		        // 		// if(current.getleaf() && current.getvalues()) os<<current.getvalues()[i]<<" ";
		        // 	}
	        	// }
	        	// os<<std::endl<<"Children: "<<std::endl;
	        	// for (int i = 0; i <= current.getkey_num(); ++i)
	        	// {
	        	// 	if(current.getchilds() && current.getchilds()[i]) 
	        	// 	{
	        	// 		for(int j=0; j <  current.getchilds()[i]->getkey_num(); j++)
	        	// 		{
	        	// 			os<<(current.getchilds()[i]->getkeys()[j])<<" ";
	        	// 		}
	        			
	        	// 	}
	        	// 	else os<<"nullptr ";
	        	// 	os<<"||";
	        	// // 	// if(current.getleaf() && current.getvalues()) os<<current.getvalues()[i]<<" ";
	        	// }
	        	// os<<std::endl<<"Parents: "<<std::endl;
	        	// if (current.getparent()) 
	        	// {
	        	// 	// // os<<*current.getparent();
	        	// 	for(int i = 0; i < current.getparent()->getkey_num();i++)
	        	// 	{
	        	// 		os<<(current.getparent()->getkeys()[i])<<" ";
	        	// 	}
	        		
	        	// }
	        	// else os<<"nullptr"<<std::endl;
	        
	            return os;
	        }
	};
	template <typename KeyT,typename ValueT> 
	class BPlusTree
	{
		public:
			BPlusTree(const size_t& ourcapacity)
			{
				nodecapacity=ourcapacity;
				root=nullptr;
				deadsnumber = 0;
			}
			BPlusTree()
			{

			}
			~BPlusTree()
			{
				if(root)
				{
					if(root->getkey_num() != 0)
					{
						Node<KeyT, ValueT>* helpcurrent = root;
						Node<KeyT, ValueT>* helpchild = root;
						Node<KeyT, ValueT>* helpright = root;
						Node<KeyT, ValueT>* helptogo = root;
						while(helpcurrent)
						{
							helpchild = helpcurrent->getchilds()[0];
							helptogo = helpcurrent;
							while(helptogo)
							{
								helpright = helptogo->getright();
								if (helptogo) delete helptogo;
								helptogo = helpright;
							}
							helpcurrent = helpchild;
						}
					}
					else
					{
						delete root;
					}
				}
			}
			Node<KeyT,ValueT> *getroot()
			{
				return this->root;
			};
			size_t getcapacity()
			{
				return nodecapacity;
			}
			size_t getdeadsnumber()
			{
				return deadsnumber;
			}
	    private:
	    	int nodecapacity;
	    	Node<KeyT,ValueT> *root;
	    	size_t deadsnumber;
	    	//find leaf with key or with space to insert key
			Node<KeyT,ValueT>* findtoinsert(const KeyT& key)
			{
				Node<KeyT, ValueT> *current = this->root; //start froom root node
				while (current->getleaf() != true) //need to reach leaf
				{
					for (int i = 0; i <= current->getkey_num(); ++i) //go through all keys in every level
					{
						if ((i == current->getkey_num() || (current->getkeys() && key < current->getkeys()[i]))) 
						{
							current = current->getchilds()[i]; 
							break;
						}
					}
				}
				return current;
			}

			//update all keys in way to current
			void updateall(Node<KeyT, ValueT>* current)
			{
				while(current)
				{
					for (int i = 0; i < current->getkey_num(); ++i)
					{
						if (current->getchilds()[i+1])
						{
							current->setkeys(i, minimumkey(current->getchilds()[i+1]));
							current->getchilds()[i+1]->setparent(current);
						}
					}
					if (current->getchilds()[0]) current->getchilds()[0]->setparent(current);
					current = current->getparent();
				}

			}

			//find key in way to current and replace it by insertkey
			void update(Node<KeyT, ValueT>* current,const KeyT key, const KeyT insertkey)
			{
				if (current) 
				{
					for (int i = 0; i < current->getkey_num(); ++i)
					{
						if (current->getkeys()[i] == key) 
						{
							current->setkeys(i, insertkey);
							return;
						}
					}
					if (current->getparent()) this->update(current->getparent(), key, insertkey);
				}
			}

			//find min key to current
			KeyT minimumkey(Node<KeyT, ValueT>* current)
			{
				KeyT helpkey = current->getkeys()[0];
				while(current)
				{
					helpkey = current->getkeys()[0];
					current = current->getchilds()[0];
				}
				return helpkey;
			}

			//split is appropriate when node has 2 * nodecapacity keys
			void split(Node<KeyT,ValueT> *node)
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
				bool mid_deads = node->getdeads()[nodecapacity];
				newnode->setkey_num(nodecapacity-1);
				node->setkey_num(nodecapacity);  

				for (int i = 0; i < newnode->getkey_num(); ++i)
				{
					newnode->setkeys(i,node->getkeys()[i+nodecapacity+1]);
					newnode->setdeads(i,node->getdeads()[i+nodecapacity+1]);
					newnode->setvalues(i,node->getvalues()[i+nodecapacity+1]);
					newnode->setchilds(i, node->getchilds()[i+nodecapacity+1]); 
				}
				newnode->setchilds(newnode->getkey_num(), node->getchilds()[2 * nodecapacity]); //add last child
				for (int i = 0; i <= newnode->getkey_num(); ++i)
				{
					if(newnode->getchilds() && newnode->getchilds()[i])
					{
						newnode->getchilds()[i]->setparent(newnode);
					}
				}

				//if splitting node is leafe we need to add middle value to newnode values
				if (node->getleaf()) 
				{
					newnode->setkey_num((newnode->getkey_num())+1);
					newnode->setleaf(true);
					//reallocating values and keys
					for(int j = newnode->getkey_num()-1; j>0;j--)
					{
						newnode->setkeys(j, newnode->getkeys()[j-1]);
						newnode->setdeads(j, newnode->getdeads()[j-1]);
						newnode->setvalues(j, newnode->getvalues()[j-1]);
					}
					//setting middle value to newnode values
					newnode->setkeys(0, mid_key);
					newnode->setdeads(0, mid_deads);
					newnode->setvalues(0, mid_value);
				}

				//if splitting node - root we need to create new one 
				if (node == this->root)
				{
					this->root= new Node<KeyT, ValueT>(this->nodecapacity,false);

					//add middle key to new root node and set node and newnode as childs
					this->root->setkeys(0, mid_key); 
					this->root->setvalues(0, mid_value);
					this->root->setdeads(0, mid_deads);
					this->root->setchilds(0, node);
					this->root->setchilds(1, newnode);
					this->root->setkey_num(1);

					//set parents to node and newnode
					node->setparent(this->root);
					newnode->setparent(this->root);
				}
				else 
				{
					//set to newnode the same parent
					newnode->setparent(node->getparent()); 
					//remember node parent 
					Node<KeyT, ValueT> *helpparent = node->getparent();

					//find position in parent node to insert middle
					size_t position = 0;
					while (position < helpparent->getkey_num() && (helpparent->getkeys() && helpparent->getkeys()[position] < mid_key))
						++position;

					//reallocate keys 
					for(size_t i = helpparent->getkey_num() ; i >= position +1; i--)
					{
						helpparent->setkeys(i, helpparent->getkeys()[i - 1]);
						helpparent->setdeads(i, helpparent->getdeads()[i - 1]);
						helpparent->setvalues(i, helpparent->getvalues()[i - 1]);
					}

					//reallocate children 
					for(size_t i = helpparent->getkey_num() + 1; i >= position +2; i--) //add + 1 to helpparent->getkey_num()
					{
						helpparent->setchilds(i, helpparent->getchilds()[i-1]);
					}

					//insert middle key and children
					helpparent->setkeys(position, mid_key);
					helpparent->setdeads(position, mid_deads);
					helpparent->setvalues(position, mid_value);
					helpparent->setchilds(position+1, newnode);
					helpparent->setkey_num(helpparent->getkey_num()+1);

					//split in case parrent now has more keys that allowed
					if (helpparent->getkey_num() == 2 * this->nodecapacity)
						split(helpparent);
				}
			}

			//insert key in deleted in current
			void  currentdeletedinsert(Node<KeyT, ValueT>* current,const KeyT& key,const ValueT& value)
			{
				// std::cout<<current->getkey_num()<<"   ";
				size_t position = 0;
				while(position < current->getkey_num() && (current->getkeys() && current->getkeys()[position] <= key))
					position++;
				position--;
				// std::cout<<position<<": position  ";
				if (position == -1) return;
				if(current->getdeads()[position])
				{
					current->setkeys(position, key);
					current->setvalues(position, value);
					current->setdeads(position, false);
					return;
				}
				bool checkleft = false;
				size_t leftposition = 0;
				for (int i = position; i >= 0; --i)
				{
					if(current->getdeads()[i])
					{
						checkleft = true;
						leftposition = i;
						break;
					}
				}
				// std::cout<<leftposition<<": leftposition  ";
				if(checkleft)
				{
					for (int i = leftposition; i < position; ++i)
					{
						current->setkeys(i, current->getkeys()[i+1]);
						current->setvalues(i, current->getvalues()[i+1]);
						current->setdeads(i, current->getdeads()[i+1]);
					}
					current->setkeys(position, key);
					current->setvalues(position, value);
					current->setdeads(position, false);
					updateall(current);
					return;
				}
				bool checkright = false;
				size_t rightposition = 0;
				for (int i = position;i < current->getkey_num(); ++i)
				{
					if(current->getdeads()[i])
					{
						checkright = true;
						rightposition = i;
						break;
					}
				}
				// std::cout<<rightposition<<": rightposition  ";
				if(checkright)
				{
					for (int i = rightposition; i > position; --i)
					{
						current->setkeys(i, current->getkeys()[i-1]);
						current->setvalues(i, current->getvalues()[i-1]);
						current->setdeads(i, current->getdeads()[i-1]);
					}
					current->setkeys(position, key);
					current->setvalues(position, value);
					updateall(current);
					return;
				}
			}

			//find space in left siblings replace and insert key
			void lazyinserttoleftsiblings(Node<KeyT, ValueT>* current, Node<KeyT, ValueT>* left, size_t position, const KeyT& key, const ValueT& value, const bool dead)
			{
				// std::cout<<"I was here";
				if (current->getkey_num() < 2*nodecapacity - 1)
				{
					// std::cout<<"position"<<position;
					current->setkeys(position, key);
					current->setdeads(position, dead);
					current->setvalues(position, value);
					current->setkey_num(current->getkey_num() + 1);
					return;
				}
				KeyT helpkey = current->getkeys()[0];
				ValueT helpvalue = current->getvalues()[0];
				bool helpdead = current->getdeads()[0];
				for (int i = 0; i < position - 1; ++i)
				{
					current->setkeys(i, current->getkeys()[i+1]);
					current->setdeads(i, current->getdeads()[i+1]);
					current->setvalues(i, current->getvalues()[i+1]);
				}
				current->setkeys(position - 1, key);
				current->setdeads(position - 1, dead);
				current->setvalues(position - 1, value);
				
				Node<KeyT, ValueT>* helpcurrent = current->getleft();
				if(current != left)
					lazyinserttoleftsiblings(helpcurrent, left, helpcurrent->getkey_num(), helpkey, helpvalue, helpdead);
				updateall(current);
			}

			//find space in right siblings replace and insert key
			void lazyinserttorightsiblings(Node<KeyT, ValueT>* current, Node<KeyT, ValueT>* right, size_t position, const KeyT& key, const ValueT& value, const bool dead)
			{
				if(current->getkey_num() < 2*nodecapacity - 1)
				{
					for (int i = current->getkey_num(); i > 0 ; --i)
					{
						current->setkeys(i, current->getkeys()[i-1]);
						current->setdeads(i, current->getdeads()[i-1]);
						current->setvalues(i, current->getvalues()[i-1]);
					}
					current->setkeys(0, key);
					current->setdeads(0, dead);
					current->setvalues(0, value);
					current->setkey_num(current->getkey_num() + 1);
					return;
				}
				KeyT helpkey = current->getkeys()[current->getkey_num() - 1];
				ValueT helpvalue = current->getvalues()[current->getkey_num() - 1];
				bool helpdead = current->getdeads()[current->getkey_num() - 1];
				for (int i = current->getkey_num(); i > position; --i)
				{
					current->setkeys(i, current->getkeys()[i-1]);
					current->setdeads(i, current->getdeads()[i-1]);
					current->setvalues(i, current->getvalues()[i-1]);
				}
				Node<KeyT, ValueT>* helpcurrent = current->getright();
				if(key < current->getkeys()[current->getkey_num() - 1])
				{
					//because we can have more then 2 nodecapacity - 1 keys
					current->setkeys(position, key);
					current->setvalues(position,  value);
					current->setdeads(position, dead);
					if(current!= right)
						lazyinserttorightsiblings(helpcurrent, right, 0, helpkey, helpvalue, helpdead);
					
				} else 
				lazyinserttorightsiblings(helpcurrent, right, 0 , key, value, dead);
				updateall(current);
			}

			//remove key from current
			void removeinnode(Node<KeyT, ValueT>* current, const KeyT key, const size_t flag)
			{
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
				if (!ifin || !current) return;

				//find deleting key's position
				size_t position = 0;
				while(position < current->getkey_num() && current->getkeys() && current->getkeys()[position] < key)
					position++;

				//delete key
				for(size_t i = position; i < current->getkey_num() - 1; i++)
				{
					current->setkeys(i, current->getkeys()[i+1]);
					current->setdeads(i, current->getdeads()[i+1]);
					current->setvalues(i, current->getvalues()[i+1]);
					// std::cout<<" i "<<i<<" "<<current->getkeys()[i]<<" i+1: "<<i+ 1<<" "<<current->getkeys()[i+1]<<std::endl;
				}

				if (flag)
				{
					for(size_t i = position + 1; i < current->getkey_num(); i++)
					{
						// if(current->getchilds() && current->getchilds()[i] && current->getchilds()[i+1]) std::cout<<"i: "<<i<<"value: "<<*current->getchilds()[i]<<"i+1: "<<i+1<<"value: "<<*current->getchilds()[i+1]<<std::endl;
						current->setchilds(i, current->getchilds()[i+1]);
					}
				}
				else 
				// if(!flag)
				{
					for(size_t i = position; i < current->getkey_num(); i++)
					{
						// if(current->getchilds() && current->getchilds()[i] && current->getchilds()[i+1]) std::cout<<"i: "<<i<<"value: "<<*current->getchilds()[i]<<"i+1: "<<i+1<<"value: "<<*current->getchilds()[i+1]<<std::endl;
						current->setchilds(i, current->getchilds()[i+1]);
					}
				}

				current->setkey_num(current->getkey_num() - 1);
				updateall(current);
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
						for (int i = current->getkey_num() - 1; i > 0; --i) 
						{
							current->setkeys(i, current->getkeys()[i-1]);
							current->setdeads(i, current->getdeads()[i-1]);
							current->setvalues(i, current->getvalues()[i-1]);
							current->setchilds(i, current->getchilds()[i-1]);
						}
						
						current->setkeys(0, left_sibling->getkeys()[left_sibling->getkey_num()]);
						current->setdeads(0, left_sibling->getdeads()[left_sibling->getkey_num()]);
						current->setvalues(0, left_sibling->getvalues()[left_sibling->getkey_num()]);
						current->setchilds(0, left_sibling->getchilds()[left_sibling->getkey_num() + 1]);
						
						update(current->getparent(), key,current->getkeys()[0]); 
						updateall(current);
						
					}
					else if (right_sibling != nullptr && right_sibling->getkey_num() > nodecapacity - 1)
					{
						right_sibling->setkey_num(right_sibling->getkey_num()-1);
						current->setkey_num(current->getkey_num() + 1);

						//rellocate max key from rightsibling to last position in current
						current->setkeys(current->getkey_num() - 1, right_sibling->getkeys()[0]);
						current->setdeads(current->getkey_num() - 1, right_sibling->getdeads()[0]);
						current->setvalues(current->getkey_num() - 1, right_sibling->getvalues()[0]);
						current->setchilds(current->getkey_num(), right_sibling->getchilds()[0]);

						for (int i = 0; i < right_sibling->getkey_num(); ++i)
						{
							right_sibling->setkeys(i, right_sibling->getkeys()[i+1]);
							right_sibling->setdeads(i, right_sibling->getdeads()[i+1]);
							right_sibling->setvalues(i, right_sibling->getvalues()[i+1]);
							right_sibling->setchilds(i, right_sibling->getchilds()[i+1]);
						}
						right_sibling->setchilds(right_sibling->getkey_num(),right_sibling->getchilds()[right_sibling->getkey_num() + 1]);
						
						// current->getparent()->setkeys(?,current->getkeys()[current->getkey_num() - 1]);
						//последний случай сломал этот апдейт мб можно длописать пока оставлю полный
						update(right_sibling, current->getkeys()[current->getkey_num() - 1], right_sibling->getkeys()[0]);
						update(current, key, current->getkeys()[0]); 
						updateall(current); 
					}
					else //if siblings has also min;
					{
						if (left_sibling != nullptr)
						{
							for (int i = 0; i < current->getkey_num(); ++i)
							{
								size_t leftsiblingkey_num = left_sibling->getkey_num();
								left_sibling->setkeys(leftsiblingkey_num, current->getkeys()[i]);
								left_sibling->setdeads(leftsiblingkey_num, current->getdeads()[i]);
								left_sibling->setvalues(leftsiblingkey_num, current->getvalues()[i]);
								left_sibling->setchilds(leftsiblingkey_num + 1, current->getchilds()[i]); //same question about lost child but probably in leaf we do not have them
								left_sibling->setkey_num(leftsiblingkey_num+=1);
							}

							if(!current->getleaf() && current->getchilds()[current->getkey_num()])
							{
								left_sibling->setchilds(left_sibling->getkey_num() + 1, current->getchilds()[current->getkey_num()]);
								left_sibling->setkey_num(left_sibling->getkey_num() + 1);
							}

							//reallocating left and right pointers
							left_sibling->setright(current->getright());
							if (current->getright()) current->getright()->setleft(left_sibling);

							//update(left_sibling)
							//надо обновить вершину и пустить удаление уже от нее
							current->setkey_num(0);
							updateall(left_sibling);
							if(current->getparent() && left_sibling->getparent() && (current->getparent() != left_sibling->getparent()))
							{
								// for (int i = 0; i < current->getparent()->getkey_num(); ++i)
								// {
								// 	current->getparent()->setchilds(i, current->getparent()->getchilds()[i]->getright()); 
								// }			
								// updateall(current->getparent());	
								// std::cout<<"I was Here 1 ";
								// updateall(current);
								removeinnode(current->getparent(), current->getparent()->getkeys()[0], 0);
							}
							else
							{
								// std::cout<<"I was Here 2 ";
								
								// update(current->getparent(), key, left_sibling->getkeys()[left_sibling->getkey_num() - 1]);
								removeinnode(current->getparent(),minimumkey(current), 1);
								 //min_key in current 
								 // if (current) std::cout<<"CURRENT TO DELETE"<<*current;
								 
							}
							if (current)	
							{
								delete current;
								// std::cout<<"Deleted"<<std::endl;
							}
						}
						else 
						{
							if (right_sibling!=nullptr)
							{
								// std::cout<<"I was Here 3 ";
								for(int i = 0;i < right_sibling->getkey_num();i++)
								{
									size_t currentkey_num = current->getkey_num();
									current->setkeys(currentkey_num, right_sibling->getkeys()[i]);
									current->setdeads(currentkey_num, right_sibling->getdeads()[i]);
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
								if (right_sibling) delete right_sibling;
							}
						}	
					} 
				}
					// if (position == 0) update(current->getparent(), key, current->getkeys()[position]);
					if (root->getkey_num() <= 1)
					{
						// std::cout<<"I was Here 4";
						int count = 0;
						for (int i = 0; i <= root->getkey_num(); ++i)
						{
							if (root->getchilds() && root->getchilds()[i])
							{
								count++;
							}
						}
						if (count == 1)
						{
							Node<KeyT, ValueT>* helptodelete = root;
							root = root->getchilds()[0];
							root->setparent(nullptr);
							delete helptodelete;
						}
					}
			}
		public:

			//intersection of key and value
			bool insert(const KeyT& key,const ValueT& value)
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
				

				//find position to insert
				size_t position = 0;
				while(position < curleaf->getkey_num() && (curleaf->getkeys() && curleaf->getkeys()[position] < key))
					position++;
				if(curleaf->getdeads()[position] && curleaf->getkeys()[position] == key)
				{
					curleaf->setdeads(position, false);
					deadsnumber--;
					return true;
				}
				if (curleaf->iskeyinnode(key))
					return false;

				//reallocate keys and values
				for (int i = curleaf->getkey_num(); i > position; i--)
				{
					if (curleaf->getkeys()) curleaf->setkeys(i, curleaf->getkeys()[i-1]);
					if (curleaf->getdeads()) curleaf->setdeads(i, curleaf->getdeads()[i - 1]);
					if (curleaf->getvalues()) curleaf->setvalues(i, curleaf->getvalues()[i-1]);
				}

				size_t help = curleaf->getkey_num();
				help++;
				curleaf->setkey_num(help);

				//add key and value			
				curleaf->setkeys(position, key);
				curleaf->setvalues(position, value);
				curleaf->setdeads(position, false);
				//start split if we have overflow
				if (curleaf->getkey_num() == (2 * nodecapacity))
					split(curleaf);
				return true;
			}

			bool lazyinsert(const KeyT& key,const ValueT& value)
			{
				if (root == nullptr) return insert(key, value);
				Node<KeyT, ValueT>* curleaf = findtoinsert(key);
				// std::cout<<*curleaf;
				if(curleaf->getkey_num() < (2 * nodecapacity - 1))
				{
					// std::cout<<"I was he*/re";
					return insert(key, value); 
				}
				bool check= false;
				for (int i = 0; i < curleaf->getkey_num(); ++i)
				{
					if(curleaf->getdeads()[i])
					{
						check=true;
						break;
					}
				}
				if(check) 
				{
					deadsnumber--;
					currentdeletedinsert(curleaf, key, value);
					return true;
				}
				size_t position = 0;
				while(position < curleaf->getkey_num() && (curleaf->getkeys() && curleaf->getkeys()[position] < key))
					position++;
				// std::cout<<position<<"  ";
				Node<KeyT, ValueT>* right_sibling = curleaf->getright();
				Node<KeyT, ValueT>* left_sibling = curleaf->getleft();
				size_t rightpos = 0;
				bool ifright = false;
				size_t leftpos = 0;
				bool ifleft = false;
				while(right_sibling)
				{
					rightpos++;
					if(right_sibling->getkey_num() < 2 * nodecapacity - 1)
					{
						ifright = true;
						break;
					}
					else
						right_sibling = right_sibling->getright();
				}
				while(left_sibling)
				{
					leftpos++;
					if(left_sibling->getkey_num() < 2 * nodecapacity - 1)
					{
						ifleft = true;
						break;
					}
					else 
						left_sibling = left_sibling->getleft();
				}
				if(!ifleft  && !ifright) return insert(key, value);
				if (!ifleft && ifright) 
				{
					lazyinserttorightsiblings(curleaf, right_sibling, position, key, value, false);
					return true;
				}
				if(ifleft && !ifright)
				{
					lazyinserttoleftsiblings(curleaf, left_sibling, position, key, value, false);
					return true;
				}
				if(leftpos > rightpos)
				{
					lazyinserttorightsiblings(curleaf, right_sibling, position, key, value, false);
					return true;
				}
				else 
				{
					lazyinserttoleftsiblings(curleaf, left_sibling, position, key, value, false);
					return true;
				}
				return false;
			}


			bool remove(const KeyT& key)
			{
				Node<KeyT, ValueT> *current = findtoinsert(key);
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
			
			bool lazyremove(const KeyT& key)
			{
				Node<KeyT, ValueT> *current = findtoinsert(key);
				for (int i = 0; i < current->getkey_num(); ++i)
				{
					if (current->getkeys() && current->getkeys()[i] == key) 
					{
						if (current->getdeads()[i])
							return false;
						else 
						{
							current->setdeads(i, true);
							deadsnumber++;
							if(nodecapacity > 200) 
							{
								if(deadsnumber > 50*nodecapacity) fix();
							}
							else
							{
								if(deadsnumber > 500*nodecapacity) fix();
							}
							return true;
						}
					}
				}
				return false;
			}

			//delete all lazy removed keys
			void fix()
			{
				if (root == nullptr) return;
				Node<KeyT, ValueT>* helptogo = root;
				std::vector<KeyT> k;
				std::vector<ValueT> v;
				while(helptogo->getchilds()[0])
				{
					helptogo = helptogo->getchilds()[0];
				}

				while(helptogo)
				{
					size_t cup = 0;
					for (int i = 0; i < helptogo->getkey_num(); ++i)
					{
						if(!helptogo->getdeads()[i])
						{
							// std::cout<<"1";
							k.push_back(helptogo->getkeys()[i]);
							v.push_back(helptogo->getvalues()[i]);		
							cup++;		
						}
					}
					for (int i = 0; i < cup; ++i)
					{
						helptogo->setkeys(i, k[i]);
						helptogo->setvalues(i, v[i]);
					}
					for (int i = 0; i < 2*nodecapacity; ++i)
					{
						helptogo->setdeads(i, false);
					}
					
					// if (cup>=1) if(k[1] == 37 && k[0] == 27) std::cout<<"dbhwiajbdkwa: "<<cup;
					helptogo->setkey_num(cup);
				 	updateall(helptogo);
					k.clear();
					v.clear();
					cup=0;

					if (helptogo->getright()) helptogo = helptogo->getright();
					else break;
				}
				// std::cout<<*helptogo;
				// std::cout<<"I was here";
				while(helptogo) 
				{
					// std::cout<<"I was here in dhjkahdkl";
					helptogo = fixinnode(helptogo);
				}
			}


			Node<KeyT, ValueT>* fixinnode(Node<KeyT, ValueT>* current)
			{
				// if (current) std::cout<<"CURRENT: "<<*current<<"   CAPAC: "<<current->getkey_num()<<std::endl;
				if (current->getkey_num() >= nodecapacity - 1)
				{
					// std::cout<<"I WAS HERE 666";
					return current->getleft();
				}
				// std::cout<<"I WAS HERE 777"<<nodecapacity;
				//remember how many keys we need
				int currentkey_numdif = nodecapacity - 1 - current->getkey_num();
				Node<KeyT, ValueT>* left_sibling = current->getleft();
				// if (left_sibling) std::cout<<left_sibling->getkey_num();
				Node<KeyT, ValueT>* right_sibling = current->getright();
				int help1 = 0;
				int help2 = 0;
				if (left_sibling)  help1 = (left_sibling->getkey_num() - nodecapacity + 1);
				if (right_sibling) help2 = (right_sibling->getkey_num() - nodecapacity + 1);
				// if (left_sibling) std::cout<<"numdif: : "<<currentkey_numdif<<"  ava"<<help <<"   "<<std::endl;
				//if we have this number of keys in leftsibling borrow them from it
				if(left_sibling && help1 >= currentkey_numdif)
				{
					// std::cout<<"I was here 0";
					current->setkey_num(nodecapacity - 1);
					for (int i = current->getkey_num() - 1; i >=currentkey_numdif ; --i)
					{
						current->setkeys(i, current->getkeys()[i - currentkey_numdif]);
						current->setvalues(i, current->getvalues()[i - currentkey_numdif]);
					}
					for (int i = 0; i < currentkey_numdif; ++i)
					{
						// std::cout<<"I was here";
						current->setkeys(i, left_sibling->getkeys()[left_sibling->getkey_num() - currentkey_numdif + i]);
						current->setvalues(i, left_sibling->getvalues()[left_sibling->getkey_num() - currentkey_numdif + i]);

					}
					left_sibling->setkey_num(left_sibling->getkey_num() - currentkey_numdif);
					updateall(current);
					return left_sibling;
				}
				else if(right_sibling && help2 >= currentkey_numdif)
				{
					// std::cout<<"I was here 1";
					for (int i = 0; i < currentkey_numdif; ++i)
					{
						current->setkeys(i + current->getkey_num(), right_sibling->getkeys()[i]);
						current->setvalues(i + current->getkey_num(), right_sibling->getvalues()[i]);
					}
					for (int i = 0; i < right_sibling->getkey_num() - currentkey_numdif; ++i)
					{
						right_sibling->setkeys(i, right_sibling->getkeys()[i + currentkey_numdif]);
						right_sibling->setvalues(i, right_sibling->getvalues()[i + currentkey_numdif]);
					}
					current->setkey_num(nodecapacity - 1);
					right_sibling->setkey_num(right_sibling->getkey_num() - currentkey_numdif);
					updateall(right_sibling);
					return current->getleft();
				}
				else if(left_sibling && help1 < currentkey_numdif)
				{
					// std::cout<<"i was here 2.0";
					for (int i = 0; i < current->getkey_num(); ++i)
					{
						left_sibling->setkeys(i + left_sibling->getkey_num(), current->getkeys()[i]);
						left_sibling->setvalues(i + left_sibling->getkey_num(), current->getvalues()[i]);
					}
					left_sibling->setkey_num(left_sibling->getkey_num() + current->getkey_num());
					left_sibling->setright(current->getright());
					if(current->getright()) current->getright()->setleft(left_sibling);
					current->setkey_num(0);
					
					if(current->getparent()  && (current->getparent() != left_sibling->getparent()))
					{
						// for (int i = 0; i < current->getparent()->getkey_num(); ++i)
						// {
						// 	current->getparent()->setchilds(i, current->getparent()->getchilds()[i+1]);
						// }
						// updateall(current->getparent());
						// std::cout<<"I was here";
						// std::cout<<"current: "<<*current;
						// std::cout<<"i was here 2.1";
						removeinnode(current->getparent(), current->getparent()->getkeys()[0], 0);
					}
					else 
					{
						// std::cout<<"i was here 2.2";
						removeinnode(current->getparent(), current->getkeys()[0], 1);
					}
					updateall(left_sibling);
					if (current) delete current;
					return left_sibling;
				}
				else if(right_sibling && (help2 < currentkey_numdif)) 
				{
					// std::cout<<"i was here 4";
					for (int i = 0; i < right_sibling->getkey_num(); ++i)
					{
						current->setkeys(i + current->getkey_num(), right_sibling->getkeys()[i]);
						current->setvalues(i + current->getkey_num(), right_sibling->getvalues()[i]);
					}
					current->setkey_num(current->getkey_num() + right_sibling->getkey_num());
					right_sibling->setkey_num(0);
					current->setright(right_sibling->getright());
					if (right_sibling->getright()) right_sibling->getright()->setleft(current);
					removeinnode(current->getparent(), right_sibling->getkeys()[0], 1);
					if(right_sibling) delete right_sibling;
					return current->getleft();
				}
				return nullptr;
			}

			void print(size_t k, Node<KeyT, ValueT>* curleaf)
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
	};
}
#endif /* BPlusTree_hpp */
