#include <iostream>

using namespace std;

template <class H> class NodeList{
	
	private:
		H key;
		NodeList<H>* next;

	public:
		NodeList(H k, NodeList<H>* n=0){
			key=k;
			next=n;
		}

		void setKey(H k){
			key=k;
		}

		void setNext(NodeList<H>* n){
			next=n;
		}

		H getKey() const{
			return key;
		}

		NodeList<H>* getNext() const{
			return next;
		}

		H* getPtrKey(){ //si usa per restituire il puntatore all'elemento nella search
			return &key;
		}
};


template <class H> class LList{
	
	private:
		NodeList<H> *head, *tail;
		int n;

		NodeList<H>* _search(H x){
			NodeList<H>* aux=head;

			while(aux && x >= aux->getKey()){
				if( x == aux->getKey()){
					return aux;
				}
				aux=aux->getNext();
			}

			return 0;
		}

		void _canc(NodeList<H>* aux){
			if(!aux){
				return;
			}

			//cancellazione in testa
			if(aux == head){
				head=head->getNext();
				delete aux;
				n--;
				return;
			}

			//cancellazione standard e in coda
			NodeList<H>* back=head;
			NodeList<H>* forward=head->getNext();
			while(aux != forward){
				back=forward;
				forward=forward->getNext();
			}
			back->setNext(forward->getNext());
			if(aux==tail){
				tail=back;
			}
			delete aux;
			n--;
			return;

		}

	public:
		LList(){
			head=tail=0;
		}

		int getN() const{
			return n;
		}

		LList<H>* ins(H x){

			//se la lista è vuota
			if(!head){
				head=new NodeList<H>(x, head);
				tail=head;
				n++;
				return this;
			}

			//inserimento in testa
			if(x < head->getKey()){
				head=new NodeList<H>(x, head);
				n++;
				return this;
			}

			//inserimento standard e in coda
			NodeList<H>* back=head;
			NodeList<H>* forward=head->getNext();
			while(forward && x > forward->getKey()){
				back=forward;
				forward=forward->getNext();
			}
			NodeList<H>* aux=new NodeList<H>(x, forward);
			back->setNext(aux);
			if(!forward){
				tail=aux;
			}
			n++;
			return this;

		}

		LList<H>* canc(H x){
			_canc(_search(x));
		}

		H* search(H x){
			NodeList<H>* aux=_search(x);

			return aux ? new H(aux->getKey()) : 0;
		}

		LList<H>* cancAll(H x){
			canc(x);

		    while(_search(x)) canc(x);

		    return this;
		}

		void print() {
			NodeList<H>* aux=head;
			while(aux){
				cout<<aux->getKey()<<" ";
				aux=aux->getNext();
			}
			cout<<endl;
		}

		H getSum() const{
			NodeList<H>* aux=head;
			H s=0;
			while(aux){
				s+=aux->getKey();
				aux=aux->getNext();
			}
			return s;
		}

		H getHead() const{
			return head ? head->getKey() : 9999;
		}

		friend bool operator > (const LList<H> &l1, const LList<H> &l2){
			if(l1.getSum() > l2.getSum()){
				return true;
			}
			if(l1.getSum() == l2.getSum() && l1.getN() > l2.getN()){
				return true;
			}
			if(l1.getSum() == l2.getSum() && l1.getN() == l2.getN() && l1.getHead() > l2.getHead()){
				return true;
			}
			return false;
		}

		friend bool operator < (const LList<H> &l1, const LList<H> &l2){
			return l2 > l1;
		}

		friend bool operator >= (const LList<H> &l1, const LList<H> &l2){
			return !(l1<l2);
		}

		friend bool operator == (const LList<H> &l1, const LList<H> &l2){
			return !(l1<l2) && !(l1>l2);
		}
};

template <class H> class NodeBST{
	
	private:
		H key;
		NodeBST<H> *parent, *left, *right;

	public:
		NodeBST(H k, NodeBST<H>* p=0, NodeBST<H>* l=0, NodeBST<H>* r=0) : key(k), parent(p), left(l), right(r) {}

		void setKey(H k){
			key=k;
		}

		void setParent(NodeBST<H>* p){
			parent=p;
		}

		void setLeft(NodeBST<H>* l){
			left=l;
		}

		void setRight(NodeBST<H>* r){
			right=r;
		}

		H getKey() const{
			return key;
		}

		H* getPtrKey(){
			return &key;
		}

		NodeBST<H>* getParent() const{
			return parent;
		}

		NodeBST<H>* getLeft() const{
			return left;
		}

		NodeBST<H>* getRight() const{
			return right;
		}

		bool isLeaf(){
			return !right && !left;
		}
};


template <class H> class BST{
	
	protected:
		NodeBST<H>* root;

		void _inOrder(NodeBST<H>* aux){
			if(aux){
				_inOrder(aux->getLeft());
				cout<<aux->getKey()<<" ";
				_inOrder(aux->getRight());
			}
		}

		NodeBST<H>* _search(H x){
			NodeBST<H>* aux=root;
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

		NodeBST<H>* _minimum(NodeBST<H>* aux){
			while(aux->getLeft()){
				aux=aux->getLeft();
			}
			return aux;
		}

		void _canc(NodeBST<H>* aux){
			if(aux){

				//caso 1: il nodo è una foglia
				if(aux->isLeaf()){
					NodeBST<H>* parent=aux->getParent();

					//se non è la radice
					if(parent){
						if(parent->getLeft() == aux){
							parent->setLeft(0);
						}
						else{
							parent->setRight(0);
						}
						aux->setParent(0);
					}
					else{
						root=0;
					}
					delete aux;
				}

				//caso 2: il nodo ha un solo figlio
				else if(aux->getLeft()==0 ^ aux->getRight()==0){
					NodeBST<H>* parent=aux->getParent();
					NodeBST<H>* son;
					if(aux->getLeft()){
						son=aux->getLeft();
					}
					else{
						son=aux->getRight();
					}

					if(parent){
						if(parent->getLeft() == aux){
							parent->setLeft(son);
						}
						else{
							parent->setRight(son);
						}
						son->setParent(parent);
					}
					else{
						root=son;
						son->setParent(0);
					}
					delete aux;
				}

				//caso 3: il nodo ha 2 figli
				else{
					NodeBST<H>* min=_minimum(aux->getRight());
					aux->setKey(min->getKey());
					_canc(min);
				}
			}
		}

		NodeBST<H>* _successor(NodeBST<H>* aux){

			if(!aux){
				return 0;
			}

			if(aux->getRight()){
				return _minimum(aux->getRight());
			}

			NodeBST<H>* parent=aux->getParent();
			while(parent && parent->getRight() && parent->getRight()==aux){
				aux=parent;
				parent=parent->getParent();
			}
			return parent;
		}

	public:
		BST(){
			root=0;
		}

		BST<H>* ins(H x){
			if(!root){
				root=new NodeBST<H>(x);
				return this;
			}

			NodeBST<H>* aux=root;
			while(true){
				if(x < aux->getKey()){
					if(!aux->getLeft()){
						NodeBST<H>* current=new NodeBST<H>(x, aux);
						aux->setLeft(current);
						return this;
					}
					else{
						aux=aux->getLeft();
					}
				}
				else{
					if(!aux->getRight()){
						NodeBST<H>* current=new NodeBST<H>(x, aux);
						aux->setRight(current);
						return this;
					}
					else{
						aux=aux->getRight();
					}
				}
			}
		}

		H* minimum(){
			NodeBST<H>* aux=_minimum(root);

			return aux ? new H(aux->getKey()) : 0;
		}

		void print(){
			if(root){
				_inOrder(root);
			}
			cout<<endl;
		}

		H* search(H x){
			NodeBST<H>* aux=_search(x);

			return aux ? new H(aux->getKey()) : 0;
		}

		BST<H>* canc(H x){
			_canc(_search(x));
			return this;
		}

		H* successor(H x){

			NodeBST<H>* aux=_successor(_search(x));

			return aux ? new H(aux->getKey()) : 0;
		}

		BST<H>* cancAll(H x){
			NodeBST<H>* aux=_search(x);
			while(aux){
				_canc(aux);
				aux=_search(x);
			}
			return this;
		}
};

template <class H> class ET : public BST< LList<H> >{
	
	private:
		int k;

		void _canc(H x){
			NodeBST< LList<H> >* root=BST< LList<H> >::root;
			if(!root) return;

			//inizio la ricerca dal nodo minimo
			NodeBST< LList<H> >* min=BST< LList<H> >::_minimum(root);
			while(min){

				//ricerco x nel nodo e cancello tutte le occorenze nel nodo
				//il booleano occorre per sapere se è possibile un cambio del minimo dopo il riordinamento
				bool modified=false;
				if(min->getPtrKey()->search(x)){
					LList<H> tmp=min->getKey();
					BST< LList<H> >::_canc(min);
					tmp.cancAll(x);
					BST< LList<H> >::ins(tmp);
					modified=true;
				}				

				if(!modified) min=BST< LList<H> >::_successor(min);
				else _canc(x);
			}
		}

	public:
		ET(int _k=0){
			k=_k;
			BST< LList<H> >();
		}

		ET<H>* ins(H x){
			NodeBST< LList<H> >* root=BST< LList<H> >::root;
			
			if(!root){
				LList<H>* l=new LList<H>();
				l->ins(x);
				BST< LList<H> >::ins(*l);
				return this;
			}

			NodeBST< LList<H> >* min=BST< LList<H> >::_minimum(root);
					
			if(min->getKey().getN()==k){
				LList<H>* l=new LList<H>();
				l->ins(x);
				BST< LList<H> >::ins(*l);
				return this;
			}
			

			LList<H> tmp=min->getKey();
			tmp.ins(x);
			BST< LList<H> >::_canc(min);
			BST< LList<H> >::ins(tmp);
			return this;
		}

		ET<H>* canc(H x){
			_canc(x);
			return this;
		}

		void print(){
			NodeBST< LList<H> >* root=BST< LList<H> >::root;
			if(root){
				NodeBST< LList<H> >* min=BST< LList<H> >::_minimum(root);
				while(min){
					min->getKey().print();
					min=BST< LList<H> >::_successor(min);
				}
			}
		}
};


int main(){
	
//esercizio 1
	LList<int>* l=new LList<int>();
	l->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
	l->canc(3)->canc(9)->canc(5)->canc(1)->ins(10)->ins(5)->print();
	if(l->search(5)){
		cout<<"elemento 5 presente";
	}
	else{
		cout<<"elemento 5 non presente";
	}
	cout<<endl;
	if(l->search(3)){
		cout<<"elemento 3 presente";
	}
	else{
		cout<<"elemento 3 non presente";
	}
	cout<<endl;

//esecizio 2
	BST<int>* t=new BST<int>();
	t->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
	t->canc(3)->canc(9)->canc(5)->canc(1)->print();
	//t->ins(10)->ins(5)->print();
	if(t->search(5)){
		cout<<"elemento 5 presente";
	}
	else{
		cout<<"elemento 5 non presente";
	}
	cout<<endl;
	if(t->search(3)){
		cout<<"elemento 3 presente";
	}
	else{
		cout<<"elemento 3 non presente";
	}
	cout<<endl;
	int *r=t->minimum();
	if(r){
		cout<<"il valore piu' piccolo e': "<<*r<<endl;
	}
	if(r=t->successor(5)){
		cout<<"il successore di 5 e': "<<*r<<endl;
	}
	if(r=t->successor(3)){
		cout<<"il successore di 3 e': "<<*r<<endl;
	}
	cout<<endl;

//esercizio 3
	ET<int> *b=new ET<int>(3);
	b->ins(3)->ins(8)->ins(6)->ins(10)->ins(9)->ins(5)->print();
	cout<<endl;
	b->ins(11)->ins(13)->ins(18)->ins(2)->ins(1)->ins(4)->print();
	cout<<endl;
	b->canc(11)->canc(13)->canc(18)->canc(9)->ins(14)->print();
	
}