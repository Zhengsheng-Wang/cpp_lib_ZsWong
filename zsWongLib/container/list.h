#pragma once
#ifndef ZSWONGLIST
#define ZSWONGLIST

#include <iostream>
#include <stdexcept>

namespace zsWong{
	template <typename T> class List;
	template <typename T> std::ostream& operator << (std::ostream& os, List<T> &li);
	template <typename T> class Node{
		friend class List<T>;
		friend std::ostream& operator<<<T>(std::ostream&, List<T>&);

		public:
		Node& operator=(const Node &n){
			//assignment operator func
			data = n.data;
			pNext = n.pNext;
			pPrev = n.pPrev;
		}
		Node(const T &d): data(d){
		}
		Node(const Node &node) : data(node.data), 
			pNext(node.pNext), pPrev(node.pPrev){}
		~Node(){}

		private:
		T data;   
		Node *pNext = nullptr, *pPrev = nullptr;
	};

	template <typename T> class List{
		friend std::ostream& operator<<<T>(std::ostream& os, List<T> &li);

		public:
		List& operator=(const List &liOri){
			{
				int i = 0;
				Node<T> *p = pFirst;
				while(i < nLen - 1){
					Node<T> *p2 = p->pNext;
					delete p;
					p = p2;
					++i;
				}
				delete p;
			}

			{
				if(liOri.nLen == 0){
					nLen = 0;
					pFirst = nullptr;
					pLast = nullptr;
				}
				else{
					nLen = liOri.nLen;
					pFirst = new Node<T>(liOri.pFirst->data);
					Node<T> *p = pFirst;
					int i = 0;
					while(i < nLen - 1){
						Node<T> *p2 = new Node<T>(liOri.get(++i));
						p2->pPrev = p;
						p->pNext = p2;
						p = p2;
					}
					pLast = p;
				}
			}
			return *this;
		}
		List(const List &liOri){
			if(liOri.nLen > 0){
				Node<T> *p = liOri.pFirst;
				int i = 0;
				while(i < liOri.nLen - 1){
					push(p->data);
					p = p->pNext;
					++i;
				}
				push(p->data);
			}
		}
		List(){
		}
		~List(){
			if(nLen == 0){
				return;
			}
			if(nLen == 1){
				delete pFirst;
				return;
			}

			int nInd = 0;
			while(nInd < nLen - 1){
				Node<T> *pNode = pFirst->pNext;
				delete pFirst;
				pFirst = pNode;
				++nInd;
			}
			delete pFirst; //�ͷ�pLast
		}

		List& push(const T &data){
			Node<T> *pNode = new Node<T>(data);
			if(nLen == 0){
				//if push the first node in this list
				pFirst = pNode;
				pLast = pNode;
				++nLen;
				return *this;
			}

			//Or just append this data behind pLast
			pLast->pNext = pNode;
			pNode->pPrev = pLast;
			pLast = pNode;
			++nLen;
			return *this;
		}
		List& append(const List &li){
			//append a sub list 
			if(li.nLen == 0){
				//if the length of the sublist is zero, then return this list immediately
				return *this;
			}

			//or 
			Node<T> *p = li.pFirst;
			int i = 0;
			while(i < li.nLen){
				push(p->data);
				p = p->pNext;
				++i;
			}

			return *this;
		}

		T get(const int &nInd) const{
			//get a copy of the value indicated by nInd
			checkIndexValid(nInd);  

			Node<T> *pNode = pFirst;
			int i = 0;
			while(i < nInd){
				pNode = pNode->pNext;
				++i;
			}
			
			return pNode->data;
		}
		void insert(const int &nInd, const T &data){
			//insert a data in the index of nInd
			checkIndexValid(nInd);    //check whether this nInd is valid

			Node<T> *pNode = new Node<T>(data);
			if(nInd == 0){
				//if insert at the first index
				pNode->pNext = pFirst;
				pFirst->pPrev = pNode;
				pFirst = pNode;
			}
			else{
				//insert at the body of this list
				Node<T> &pNodeCur = getNodeRef(nInd);
				pNode->pPrev = pNodeCur.pPrev; 
				pNode->pNext = &pNodeCur;
				pNodeCur.pPrev->pNext = pNode;
				pNodeCur.pPrev = pNode;  
			}

			++nLen;  
		}
		void set(const int &nInd, const T &t){
			//set the value at nInd to t
			checkIndexValid(nInd);

			Node<T> &n = getNodeRef(nInd);  //get the reference of the node at nInd
			n.data = t;
		}

		int getLength() const{
			return nLen;
		}

		private:
		void checkIndexValid(const int &nInd) const{
			try{
				if(nInd >= nLen || nInd < -1){
					throw std::out_of_range("Required index out of range\n");
				}
			}
			catch(std::out_of_range &e){
				std::cerr << e.what();
				std::terminate();
			}
		}

		Node<T>& getNodeRef(const int &nInd){
			//get a reference of the node at nInd
			int i = 0;
			Node<T> *p = pFirst;
			while(i < nInd){
				p = p->pNext;
				++i;
			}
			return *p;
		}

		private:
		int nLen = 0;  
		Node<T> *pFirst = nullptr, *pLast = nullptr;  
	};
	template <typename T> std::ostream& operator<<(std::ostream& os, List<T> &li){
		zsWong::Node<T> *p = li.pFirst;
		for(int i = 0; i != li.nLen; ++i){
			os << p->data << " ";
			p = p->pNext;
		}
		return os;
	}
}

#endif // ZSWONGLIST

