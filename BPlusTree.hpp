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
			// void freeNode()
			// {
			// 	// std::cout<<"1 ";
			// 	delete [] keys;
			// 	keys = nullptr;
			// 	delete [] values;
			// 	values = nullptr;
			// 	delete [] childs;
			// 	childs = nullptr;
			// 	if (!leaf)
			// 	{
			// 		for (int i = 0; i <=key_num; ++i)
			// 		{
			// 			if(childs && childs[i]) delete childs[i];
			// 		}
			// 		delete [] childs;
			// 	}
			// 	else 
			// 	{
			// 		delete [] childs;
			// 	}
			// }
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
				
				// root->freeNode();
				// delete root;
				// root = nullptr;
			}
			// BPlusTree(const size_t& ourcapacity,Node<KeyT, ValueT>* ourroot)
			// {
			// 	nodecapacity=ourcapacity;
			// 	root=ourroot;
			// }
			bool insert(const KeyT&, const ValueT&);
			void fix();
			Node<KeyT, ValueT>* fixinnode(Node<KeyT, ValueT>*);
			void print(size_t,  Node<KeyT, ValueT>*);
			bool remove(const KeyT&);
			bool lazyremove(const KeyT&);
			bool lazyinsert(const KeyT&, const ValueT&);
			Node<KeyT,ValueT> *getroot()
			{
				return this->root;
			};
			size_t getcapacity()
			{
				return nodecapacity;
			}
	    private:
	    	int nodecapacity;
	    	Node<KeyT,ValueT> *root;
	    	void removeinnode(Node<KeyT, ValueT>*, const KeyT, const size_t);
	    	Node<KeyT,ValueT> *findtoinsert(const KeyT&);
	    	void split(Node<KeyT,ValueT>*);
	    	void update(Node<KeyT, ValueT>* current,const KeyT key,const KeyT insertkey);
	    	KeyT minimumkey(Node<KeyT, ValueT>* current);
			void updateall(Node<KeyT, ValueT>* current);
			void updatenow(Node<KeyT, ValueT>* current);
			void lazyinserttoleftsiblings(Node<KeyT, ValueT>* left, Node<KeyT, ValueT>* current, size_t position, const KeyT& key, const ValueT& value, const bool dead);
			void lazyinserttorightsiblings(Node<KeyT, ValueT>* left, Node<KeyT, ValueT>* current, size_t position, const KeyT& key, const ValueT& value, const bool dead);
			void  currentdeletedinsert(Node<KeyT, ValueT>* current,const KeyT& key,const ValueT& value);
	    	// void initializeNode(Node<KeyT,ValueT>*);
	  //   	void freeNode(Node<KeyT,ValueT>);
			// };
		};
}
#endif /* BPlusTree_hpp */
