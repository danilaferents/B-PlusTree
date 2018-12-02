//
//  BPlusTree.hpp
//  
//
//  Created by Ferents Danila.
//

#ifndef BPlusTree_hpp
#define BPlusTree_hpp
#include <iostream>
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
			ValueT *values;
			Node *left;
			Node *right;
		public:
			Node(const size_t &capacity,const bool &ourbool)
			{
				leaf=ourbool;
				key_num=0;
				keys=new KeyT(2*capacity);
				parent=nullptr;
				childs=new Node<KeyT,ValueT>*[2*capacity];
				for (int i = 0; i < 2*capacity; ++i)
				{
					childs[i]=nullptr;
				}
				left=nullptr;
				right=nullptr;
				values=new ValueT(2*capacity);
			}
			Node(const size_t &capacity,const bool &ourbool,const KeyT& key, const ValueT& value)
			{
				leaf=ourbool;
				key_num=0;
				keys=new KeyT(2*capacity);
				keys[0] = key;
				parent=nullptr;
				childs=new Node<KeyT,ValueT>*[2*capacity];
				for (int i = 0; i <=2*capacity; ++i)
				{
					childs[i]=nullptr;
				}
				left=nullptr;
				right=nullptr;
				values=new ValueT(2*capacity);
				values[0] = value;
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
				if (this->keys) return this->keys;
				return nullptr;
			}
			void setkeys(const size_t& index,const KeyT& keyvalue)
			{
				if (this->keys) this->keys[index] = keyvalue;
			}
			Node *getparent()
			{
				if(this->parent) return this->parent;
				return nullptr;
			}
			void setparent(Node* currentparent)
			{
				return void(parent = currentparent);
			}
			Node **getchilds()
			{
				if (this->childs) return this->childs;
				return nullptr;
			}
			void setchilds(const size_t& index,Node * insertnode)
			{
				if (this->childs) this->childs[index] = insertnode;
			}
			ValueT *getvalues()
			{
				if(this->values) return this->values;
				return nullptr;
			}
			void setvalues(const size_t& index, const ValueT& insertvalue)
			{
				if (this->values) this->values[index] = insertvalue;
			}
			Node *getleft()
			{
				if(this->left) return this->left;
				return nullptr;
			}
			void setleft(Node *insertleft)
			{
				this->left=insertleft;
			}
			Node *getright()
			{
				if(this->left) return this->left;
				return nullptr;
			}
			void setright(Node *insertright)
			{
				this->right = insertright;
			}
			friend std::ostream& operator<<(std::ostream& os, Node& current)
	        {
	        	// if (current.getleaf() == true) std::cout<<"true";
	        	// else std::cout<<"false";
	        	for (int i = 0; i < current.getkey_num(); ++i)
	        	{
	        		if(current.getkeys()) os<<current.getkeys()[i]<<" ";
	        	}
	        	// os<<"||";
	        	os<<std::endl;
	            return os;
	        }
	};
	template <typename KeyT,typename ValueT> 
	class BPlusTree
	{
		public:
			BPlusTree()
			{
				nodecapacity=0;
				root=nullptr;
			}
			BPlusTree(const size_t& ourcapacity,Node<KeyT, ValueT>* ourroot)
			{
				nodecapacity=ourcapacity;
				root=ourroot;
			}
			bool insert(const KeyT&, const ValueT&);
			void remove (const KeyT&);
			void split(Node<KeyT,ValueT>*);
			Node<KeyT,ValueT> *findtoinsert(const KeyT&);
			void print(size_t,  Node<KeyT, ValueT>*);
			Node<KeyT,ValueT> *getroot()
			{
				return this->root;
			};
	    private:
	    	int nodecapacity;
	    	Node<KeyT,ValueT> *root;
	    	// void initializeNode(Node<KeyT,ValueT>*);
	  //   	void freeNode(Node<KeyT,ValueT>);
			// };
		};
}
#endif /* BPlusTree_hpp */
