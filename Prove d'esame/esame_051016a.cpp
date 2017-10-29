#include <iostream>

using namespace std;

template <class H> class NodeList{
	
	private:
		H* key;
		NodeList<H> *next;

	public:
		NodeList(H *k=0, NodeList<H> *n=0) : key(new H(*k)), next(n) {}

		void setKey(H *k){key=k;}
		void setNext(NodeList<H> *n){next=n;}

		H* getKey() const{return key;}
		NodeList<H>* getNext() const{return next;}
};

template <class H> class LList{
	
	protected:
		NodeList<H> *head;

		NodeList<H>* _search(H x){
			NodeList<H>* aux=head;
			while(aux && x >= *aux->getKey()){
				if(x == *aux->getKey()) return aux;
				aux=aux->getNext();
			}
			return 0;
		}

	public:
		LList(){
			head=0;
		}

		LList<H>* ins(H x){
			//lista vuota
			if(!head){
				head=new NodeList<H>(&x);
				return this;
			}

			//in testa
			if(x <= *head->getKey()){
				head=new NodeList<H>(&x, head);
				return this;
			}

			//standard
			NodeList<H>* back=head;
			NodeList<H>* forward=head->getNext();
			while(forward && x >= *forward->getKey()){
				back=forward;
				forward=forward->getNext();
			}
			NodeList<H>* aux=new NodeList<H>(&x, forward);
			back->setNext(aux);
			return this;
			return this;
		}

		LList<H>* canc(H x){
			NodeList<H>* aux=_search(x);

			if(!aux) return this;

			//in testa
			if(aux == head){
				head=head->getNext();
				delete aux;
				return this;
			}

			//standard
			NodeList<H>* back=head;
			NodeList<H>* forward=head->getNext();
			while(forward){
				if(aux == forward){
					back->setNext(forward->getNext());
					delete aux;
					return this;
				}
				back=forward;
				forward=forward->getNext();
			}
			return this;
		}

		H* search(H x){
			NodeList<H>* aux=_search(x);
			return aux ? aux->getKey() : 0;
		}

		void print(){
			NodeList<H>* aux=head;
			while(aux){
				cout<<*aux->getKey()<<" ";
				aux=aux->getNext();
			}
			cout<<endl;
		}

		void cancNode(NodeList<H>* aux){
			if(!aux) return;

			//in testa
			if(aux == head){
				head=head->getNext();
				delete aux;
				return;
			}

			//standard
			NodeList<H>* back=head;
			NodeList<H>* forward=head->getNext();
			while(forward){
				if(aux == forward){
					if(forward->getNext()) back->setNext(forward->getNext());
					else back->setNext(0);
					delete aux;
					return;
				}
				back=forward;
				forward=forward->getNext();
			}
			return;
		}

};


template <class H> class NodeBST{
	
	private:
		H *key;
		NodeBST<H> *parent, *left, *right;

	public:
		NodeBST(H *k=0, NodeBST<H> *p=0, NodeBST<H> *l=0, NodeBST<H> *r=0) : key(new H(*k)), parent(p), left(l), right(r) {}

		void setKey(H *k){key=k;}
		void setParent(NodeBST<H> *p){parent=p;}
		void setLeft(NodeBST<H> *l){left=l;}
		void setRight(NodeBST<H> *r){right=r;}

		H* getKey() const{return key;}
		NodeBST<H>* getParent() const{return parent;}
		NodeBST<H>* getLeft() const{return left;}
		NodeBST<H>* getRight() const{return right;}

		bool isLeaf() const{!right && !left;}
};

template <class H> class BST{
	
	private:
		NodeBST<H> *root;

		NodeBST<H>* _minimum(NodeBST<H>* aux) const{
			if(!aux) return 0;
			if(!aux->getLeft()) return aux;
			return _minimum(aux->getLeft());
		}

		NodeBST<H>* _search(H x){
			NodeBST<H>* aux=root;
			while(aux){
				if(x < *aux->getKey()) aux=aux->getLeft();
				else if(x > *aux->getKey()) aux=aux->getRight();
				else return aux;
			}
			return 0;
		}

		NodeBST<H>* _successor(NodeBST<H>* aux){
			if(!aux) return 0;

			if(aux->getRight()) return _minimum(aux->getRight());

			NodeBST<H>* parent=aux->getParent();
			while(parent && parent->getRight() && parent->getRight() == aux){
				aux=parent;
				parent=parent->getParent();
			}
			return parent;
		}

		void _canc(NodeBST<H>* aux){
			if(aux){

				//caso 1: il nodo è una foglia
				if(!aux->getLeft() && !aux->getRight()){
					NodeBST<H>* parent=aux->getParent();
					if(parent){
						if(parent->getLeft() == aux) parent->setLeft(0);
						else parent->setRight(0);
						aux->setParent(0);
					}
					else root=0;
					delete aux;
				}

				//caso 2: il nodo ha un solo figlio
				else if(aux->getLeft()==0 ^ aux->getRight()==0){
					NodeBST<H>* son;
					if(aux->getLeft()) son=aux->getLeft();
					else son=aux->getRight();
					NodeBST<H>* parent=aux->getParent();
					if(parent){
						if(parent->getLeft() == aux) parent->setLeft(son);
						else parent->setRight(son);
						son->setParent(parent);
						aux->setLeft(0);
						aux->setRight(0);
						aux->setParent(0);
					}
					else root=son;
					delete aux;
				}

				//caso 3: il nodo ha due figli
				else{
					NodeBST<H>* min=_minimum(aux->getRight());
					aux->setKey(min->getKey());
					_canc(min);
				}
			}
		}

		int _height(NodeBST<H>* aux) const{
			if(!aux) return -1;

			int h1=_height(aux->getLeft());
			int h2=_height(aux->getRight());

			return (h1 > h2 ? h1 : h2) + 1;
		}

		void _print(NodeBST<H>* aux){
			if(aux){
				_print(aux->getLeft());
				cout<<*aux->getKey()<<" ";
				_print(aux->getRight());
			}
		}

	public:
		BST(){
			root=0;
		}

		BST<H>* ins(H x){
			if(!root){
				root=new NodeBST<H>(&x);
				return this;
			}

			NodeBST<H>* aux=root;
			while(true){
				if(x <= *aux->getKey()){
					if(!aux->getLeft()){
						NodeBST<H>* current=new NodeBST<H>(&x, aux);
						aux->setLeft(current);
						return this;
					}
					else aux=aux->getLeft();
				}
				else{
					if(!aux->getRight()){
						NodeBST<H>* current=new NodeBST<H>(&x, aux);
						aux->setRight(current);
						return this;
					}
					else aux=aux->getRight();
				}
			}
		}

		BST<H>* canc(H x){
			_canc(_search(x));
			return this;
		}

		void canAll(H x){
			NodeBST<H>* aux=_search(x);
			while(aux){
				_canc(aux);
				aux=_search(x);
			}
		}

		H* minimum() const{
			NodeBST<H>* aux=_minimum(root);
			return aux ? aux->getKey() : 0;
		}

		H* search(H x){
			NodeBST<H>* aux=_search(x);
			return aux ? aux->getKey() : 0;
		}

		H* successor(H x){
			NodeBST<H>* aux=_successor(_search(x));
			return aux ? aux->getKey() : 0;
		}

		int height() const{
			return _height(root);
		}

		void print(){
			_print(root);
			cout<<endl;
		}

		friend bool operator > (const BST<H> &t1, const BST<H> &t2){
			if(t1.height() > t2.height()) return true;
			if(t1.height() == t2.height() && *t1.minimum() > *t2.minimum()) return true;
			return false;
		}

		friend bool operator < (const BST<H> &t1, const BST<H> &t2){
			return t2>t1;
		}

		friend bool operator >= (const BST<H> &t1, const BST<H> &t2){
			return !(t1<t2);
		}

		friend bool operator <= (const BST<H> &t1, const BST<H> &t2){
			return !(t1>t2);
		}

		friend bool operator == (const BST<H> &t1, const BST<H> &t2){
			return !(t1<t2) && !(t1>t2);
		}
};

template <class H> class IF : public LList< BST<H> >{
	
	private:
		int k;

		void _canc(H x){
			NodeList< BST<H> >* head=LList< BST<H> >::head;

			while(head){
				bool modified=false; // per sapere se l'albero è stato modificato o no
				//verifico se è presente la chiave
				if(head->getKey()->search(x)){
					BST<H>* t=head->getKey();
					t->canAll(x);
					LList< BST<H> >::cancNode(head);
					LList< BST<H> >::ins(*t);
					modified=true;
				}
				if(modified) _canc(x);
				else head=head->getNext();
			}
		}

	public:
		IF(int _k) : k(_k) {
			LList< BST<H> >::head=0;
		}

		IF<H>* ins(H x){
			NodeList< BST<H> >* head=LList< BST<H> >::head;
			if(!head || head->getKey()->height() == k){
				BST<H>* t=new BST<H>();
				t->ins(x);
				LList< BST<H> >::ins(*t);
				return this;
			}

			BST<H>* t=head->getKey();
			t->ins(x);
			LList< BST<H> >::canc(*head->getKey());
			LList< BST<H> >::ins(*t);
			return this;
		}

		IF<H>* canc(H x){
			NodeList< BST<H> >* head=LList< BST<H> >::head;
			if(!head) return this;
			_canc(x);
			return this;
		}

		void print(){
			NodeList< BST<H> >* head=LList< BST<H> >::head;
			while(head){
				head->getKey()->print();
				head=head->getNext();
			}
			cout<<endl;
		}
};

int main(){

	LList<int>* l=new LList<int>();
	/*l->canc(99)->print();
	l->ins(99)->ins(100)->print();
	l->canc(99)->canc(100)->print();*/
	l->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
	l->canc(3)->canc(9)->canc(5)->canc(1)->ins(10)->ins(5)->print();
	if(l->search(5)) cout << "elemento 5 presente";
	else cout << "elemento 5 non presente";
	cout<<endl;
	if(l->search(3)) cout << "elemento 3 presente";
	else cout << "elemento 3 non presente";
	cout<<endl;

	cout<<endl;

	BST<int>* t=new BST<int>();
	t->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
	t->canc(3)->canc(9)->canc(5)->canc(1)->ins(10)->ins(5)->print();
	if(t->search(5)) cout << "elemento 5 presente";
	else cout << "elemento 5 non presente";
	cout<<endl;
	if(t->search(3)) cout << "elemento 3 presente";
	else cout << "elemento 3 non presente";
	cout<<endl;
	int* r=t->minimum();
	if(r) cout<<"il valore piu' piccolo e': "<<*r<<endl;
	if(r=t->successor(5)) cout << "il successore di 5 e' " <<*r<<endl;
	if(r=t->successor(3)) cout << "il successore di 3 e' " <<*r<<endl;
	cout<<"Altezza: "<<t->height()<<endl;
	/*t->ins(5)->print();
	t->canAll(5);
	t->print();*/

	cout<<endl;

	IF<int>* b=new IF<int>(3);
	b->ins(3)->ins(14)->ins(2)->ins(5)->ins(8)->ins(9)->print();
	b->ins(4)->ins(7)->ins(11)->ins(5)->ins(6)->ins(12)->print();
	b->canc(11)->canc(3)->canc(2)->canc(9)->ins(9)->print();
}