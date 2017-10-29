#include <iostream>

using namespace std;

template <class H> class Node{
	
	private:
		H key;
		int prior;
		Node<H> *parent, *left, *right;

	public:
		Node(H k, int pr, Node<H> *p=0, Node<H> *l=0, Node<H> *r=0) : key(k), prior(pr), parent(p), left(l), right(r) {}

		void setKey(H k){key=k;}
		H getKey() const{return key;}

		void setPrior(int p){prior=p;}
		int getPrior() const{return prior;}

		void setParent(Node<H> *p){parent=p;}
		Node<H>* getParent() const{return parent;}

		void setLeft(Node<H> *l){left=l;}
		Node<H>* getLeft() const{return left;}

		void setRight(Node<H> *r){right=r;}
		Node<H>* getRight() const{return right;}

		bool isLeaf() const{return !left && !right;}
};

template <class H> class PBT{
	
	public:
		virtual PBT<H>* ins(int p, H x) = 0;
		virtual H find(int p) = 0;
		virtual void print() = 0;
		virtual PBT<H>* del(H x) = 0;
};

template <class H> class MyPBT : public PBT<H>{
	
	private:
		Node<H> *root;

		Node<H>* _minimum(Node<H>* aux){
			while(aux && aux->getLeft()) aux=aux->getLeft();
			return aux;
		}

		Node<H>* _maximum(Node<H>* aux){
			while(aux && aux->getRight()) aux=aux->getRight();
			return aux;
		}

		Node<H>* _predecessor(Node<H>* aux){
			if(!aux) return 0;

			if(aux->getLeft()) return _maximum(aux->getLeft());

			Node<H>* parent=aux->getParent();
			while(parent && parent->getLeft() && parent->getLeft() == aux){
				aux=parent;
				parent=parent->getParent();
			}
			return parent;
		}

		Node<H>* _searchPr(int p){
			Node<H>* aux=root;
			while(aux){
				if(p < aux->getPrior()) aux=aux->getLeft();
				else if(p > aux->getPrior()) aux=aux->getRight();
				else return aux;
			}
			return 0;
		}

		Node<H>* _searchKey(H x){
			Node<H>* aux=_maximum(root);
			while(aux){
				if(x == aux->getKey()) return aux;
				aux=_predecessor(aux);
			}
			return 0;
		}

		void _del(Node<H>* aux){
			if(aux){

				//caso 1: il nodo è una foglia
				if(aux->isLeaf()){
					Node<H>* parent=aux->getParent();
					if(parent){
						if(parent->getLeft() == aux) parent->setLeft(0);
						else parent->setRight(0);
						aux->setParent(0);
					}
					else root=0;
					delete aux;
				}

				//caso 2: il nodo ha un solo figlio
				else if(aux->getLeft() == 0 ^ aux->getRight() == 0){
					Node<H>* son;
					if(aux->getLeft()) son=aux->getLeft();
					else son=aux->getRight();
					Node<H>* parent=aux->getParent();
					if(parent){
						if(parent->getLeft() == aux) parent->setLeft(son);
						else parent->setRight(son);
						son->setParent(parent);
					}
					else root=son;
					delete aux;
				}

				//caso 3: il nodo ha due figli
				else{
					Node<H>* min=_minimum(aux->getRight());
					aux->setKey(min->getKey());
					aux->setPrior(min->getPrior());
					_del(min);
				}
			}
		}

	public:
		MyPBT(){
			root=0;
		}

		PBT<H>* ins(int p, H x){
			//albero vuoto
			if(!root){
				root=new Node<H>(x, p);
				return this;
			}

			//ricerca elemento con uguale priorità
			if(_searchPr(p)) return this;

			Node<H>* aux=root;
			while(true){
				if(p < aux->getPrior()){
					if(!aux->getLeft()){
						Node<H>* current=new Node<H>(x, p, aux);
						aux->setLeft(current);
						return this;
					}
					else aux=aux->getLeft();
				}
				else{
					if(!aux->getRight()){
						Node<H>* current=new Node<H>(x, p, aux);
						aux->setRight(current);
						return this;
					}
					else aux=aux->getRight();
				}
			}
		}

		H find(int p){
			Node<H>* aux=_searchPr(p);
			return aux ? aux->getKey() : 0;
		}

		void print(){
			Node<H>* aux=_maximum(root);
			while(aux){
				cout<<aux->getKey()<<" ";
				aux=_predecessor(aux);
			}
			cout<<endl;
		}

		PBT<H>* del(H x){
			_del(_searchKey(x));
			return this;
		}
};

int main(){

	MyPBT<int>* pt=new MyPBT<int>();
	pt->del(8);
	pt->ins(10, 5)->ins(7, 3)->ins(8, 13)->ins(13, 1)->ins(6, 2)->ins(9, 7);
	pt->print();
	cout<<"search Priority 7: "<<pt->find(7)<<"\tsearch Priority 11: "<<pt->find(11)<<endl;
	pt->del(13)->del(1);
	pt->print();
}