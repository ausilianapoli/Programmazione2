#include <iostream>

using namespace std;

template <class H> class NodeList{
	
	private:
		H* key;
		NodeList<H> *next, *prev;

	public:

		NodeList(H* k, NodeList<H> *n=0, NodeList<H> *p=0) : key(k), next(n), prev(p) {}

		void setKey(H* k){
			key=k;
		}

		void setNext(NodeList<H>* n){
			next=n;
		}

		void setPrev(NodeList<H>* p){
			prev=p;
		}

		H* getKey() const{
			return key;
		}

		NodeList<H>* getNext() const{
			return next;
		}

		NodeList<H>* getPrev() const{
			return prev;
		}
};

template <class H> class List{
	
	private:
		NodeList<H>* _search(H *x){
			NodeList<H>* aux=head;
			while(aux){
				if(x == aux->getKey()){
					return aux;
				}
				aux=aux->getNext();
			}
			return 0;
		}

	protected:
		NodeList<H> *head, *tail;

	public:
		List(){
			head=tail=0;
		}

		void insert(H *x){
			if(!head){
				head=new NodeList<H>(x);
				tail=head;
				return;
			}
			NodeList<H>* aux=new NodeList<H>(x, head);
			head->setPrev(aux);
			head=aux;
		}

		void del(H *x){
			NodeList<H>* current=_search(x);

			if(current){

				//eliminazione in testa
				if(current == head){
					head=head->getNext();
					if(head){
						head->setPrev(0);
					}
				}

				//eliminazione in coda
				else if(current == tail){
					tail=tail->getPrev();
					tail->setNext(0);
				}

				//eliminazione standard
				else{
					current->getPrev()->setNext(current->getNext());
					current->getNext()->setPrev(current->getPrev());
				}

				delete current;
			}
		}

		void print(){
			NodeList<H>* aux=head;
			while(aux){
				cout<<*aux->getKey()<<" ";
				aux=aux->getNext();
			}
			cout<<endl;
		}
};

template <class H> class NodeTree{
	
	private:
		H key;
		NodeTree<H> *parent, *left, *right;

	public:
		NodeTree(H k, NodeTree<H> *p=0, NodeTree<H> *l=0, NodeTree<H> *r=0) : key(k), parent(p), left(l), right(r) {}

		void setKey(H k){
			key=k;
		}

		void setParent(NodeTree<H>* p){
			parent=p;
		}

		void setLeft(NodeTree<H>* l){
			left=l;
		}

		void setRight(NodeTree<H>* r){
			right=r;
		}

		H getKey() const{
			return key;
		}

		NodeTree<H>* getParent() const{
			return parent;
		}

		NodeTree<H>* getLeft() const{
			return left;
		}

		NodeTree<H>* getRight() const{
			return right;
		}

		bool isLeaf(){
			return !right && !left;
		}
};

template <class H> class BST{
	
	private:
		NodeTree<H> *root;
		int n;

		void _inOrder(NodeTree<H>* aux){
			if(aux){
				_inOrder(aux->getLeft());
				cout<<aux->getKey()<<" ";
				_inOrder(aux->getRight());
			}
		}

		NodeTree<H>* _search(H x){
			NodeTree<H>* aux=root;
			while(aux){
				if(x < aux->getKey()){
					aux=aux->getLeft();
				}
				else if(x > aux->getKey()){
					aux=aux->getRight();
				}
				else{
					return aux;
				}
			}
			return 0;
		}

		NodeTree<H>* _min(NodeTree<H>* aux){
			while(aux && aux->getLeft()){
				aux=aux->getLeft();
			}
			return aux ? aux : 0;
		}

		void _del(NodeTree<H>* aux){
			if(aux){

				//caso 1: il nodo è una foglia
				if(aux->isLeaf()){
					NodeTree<H>* parent=aux->getParent();
					if(parent){
						if(parent->getLeft() == aux){
							parent->setLeft(0);
						}
						else{
							parent->setRight(0);
						}
						aux->setParent(0);
						n--;
						delete aux;
					}
					else{
						root=0;
						n--;
						delete aux;
					}
				}

				//caso 2: il nodo ha un solo figlio
				else if(aux->getLeft()==0 ^ aux->getRight()==0){
					NodeTree<H>* parent=aux->getParent();
					NodeTree<H>* son;
					if(aux->getLeft()){
						son=aux->getLeft();
						aux->setLeft(0);
					}
					else{
						son=aux->getRight();
						aux->setRight(0);
					}
					if(parent){
						if(parent->getLeft() == aux){
							parent->setLeft(son);
						}
						else{
							parent->setRight(son);
						}
						son->setParent(parent);
						n--;
						delete aux;
					}
					else{
						root=son;
						son->setParent(0);
						n--;
						delete aux;
					}
				}

				//caso 3: il nodo ha due figli
				else{
					NodeTree<H>* min=_min(aux->getRight());
					aux->setKey(min->getKey());
					_del(min);
				}
			}
		}

	public:
		BST(){
			root=0;
			n=0;
		}

		int getSize(){
			return n;
		}

		void insert(H x){
			if(!root){
				root=new NodeTree<H>(x);
				n++;
				return;
			}

			NodeTree<H>* aux=root;
			while(true){
				if(x < aux->getKey()){
					if(!aux->getLeft()){
						NodeTree<H>* current=new NodeTree<H>(x, aux);
						aux->setLeft(current);
						n++;
						return;
					}
					else{
						aux=aux->getLeft();
					}
				}
				else{
					if(!aux->getRight()){
						NodeTree<H>* current=new NodeTree<H>(x, aux);
						aux->setRight(current);
						n++;
						return;
					}
					else{
						aux=aux->getRight();
					}
				}
			}
		}

		void print(){
			if(root){
				_inOrder(root);
			}
			cout<<endl;
		}

		bool search(H x){
			NodeTree<H>* aux=_search(x);
			return aux ? 1 : 0;
		}

		H* min(){
			NodeTree<H>* aux=_min(root);
			return aux ? new H(aux->getKey()) : 0;
		}

		void del(H x){
			_del(_search(x));
		}

		void delAll(H x){
			NodeTree<H>* aux=_search(x);
			while(aux){
				_del(aux);
				aux=_search(x);
			}
		}
};


template <class H> class LOT : public List< BST<H> >{
	
	private:
		int k;

	public:
		LOT(int k){
			this->k=k;
			List< BST<H> >();
		}

		void insert(H x){
			NodeList< BST<H> >* head=List< BST<H> >::head;
			if(!head || head->getKey()->getSize() == k){
				BST<H>* t=new BST<H>();
				t->insert(x);
				List< BST<H> >::insert(t);
			}
			else{
				head->getKey()->insert(x);
			}
		}

		void del(H x){
			NodeList< BST<H> >* aux=List< BST<H> >::head;
			while(aux){
				aux->getKey()->delAll(x);
				if(aux->getKey()->getSize() == 0){
					NodeList< BST<H> >*tmp=aux->getNext();
					List< BST<H> >::del(aux->getKey());
					aux=tmp;
				}
				else{
					aux=aux->getNext();
				}
			}
		}

		void print(){
			NodeList< BST<H> >* aux=List< BST<H> >::head;
			while(aux){
				aux->getKey()->print();
				aux=aux->getNext();
			}
			cout<<endl;
		}
};


int main(){

	/*List<int>* l=new List<int>();

	int a=2;
	int b=5;
	int c=10;

	l->insert(&a);
	l->insert(&b);
	l->insert(&c);
	l->print();
	l->del(&b);
	l->del(&a);
	l->del(&c);
	l->print();*/

	/*BST<int>* b=new BST<int>();
	b->insert(50);
	b->insert(25);
	b->insert(70);
	b->insert(30);
	cout<<"n: "<<b->getSize()<<endl;
	b->print();
	cout<<b->search(25)<<endl;
	cout<<b->search(41)<<endl;
	cout<<*b->min()<<endl;

	b->del(70);
	b->del(50);

	b->print();
	cout<<"n: "<<b->getSize()<<endl;

	b->insert(41);
	b->insert(41);
	b->print();
	b->delAll(41);
	b->print();*/

	LOT<int>* lt=new LOT<int>(4);

	lt->insert(2);
	lt->insert(3);
	lt->insert(1);
	lt->insert(5);
	lt->insert(3);
	lt->insert(7);
	lt->insert(6);
	lt->insert(1);
	lt->insert(2);
	lt->insert(4);
	lt->insert(5);
	lt->insert(3);
	lt->insert(2);
	lt->insert(1);
	lt->print();
	lt->del(5);
	lt->del(1);
	lt->del(2);
	lt->print();

}