//i valori di output dati nella consegna del compito sono validi se si effettua l'inserimento in coda nella lista circolare
//però nella consegna del compito è scritto che l'inserimento deve avvenire alla destra del nodo di accesso e quindi non in coda
//l'output di questo svolgimento si riferisce a quest'ultimo metodo

#include <iostream>

using namespace std;

template <class H> class Node{
	
	private:
		H *key;
		Node<H> *next, *prev;

	public:
		Node(H k, Node<H> *n=0, Node<H> *p=0) : key(new H(k)), next(n), prev(p) {}

		void setKey(H *k){ key=k; }
		void setNext(Node<H> *n){ next=n; }
		void setPrev(Node<H> *p){ prev=p; }

		H* getKey() const{ return key; }
		Node<H>* getNext() const{ return next; }
		Node<H>* getPrev() const{ return prev; }
};

template <class H> class List{
	
	protected:
		Node<H> *head, *tail;

		Node<H>* _search(H *x){
			Node<H>* aux=head;
			while(aux){
				if(x == aux->getKey()) return aux;
				aux=aux->getNext();
			}
			return 0;
		}

	public:
		List(){
			head=tail=0;
		}

		void insert(H *x){
			if(!head){
				head=new Node<H>(*x, head);
				tail=head;
				return;
			}
			Node<H>* aux=new Node<H>(*x, head);
			head->setPrev(aux);
			head=aux;
		}

		void del(H *x){
			Node<H>* aux=_search(x);
			if(!aux) return;

			//eliminazione in testa
			if(aux == head){
				head=head->getNext();
				if(head) head->setPrev(0);
				aux->setNext(0);
			}
			//eliminazione standard e in coda
			else{
				aux->getPrev()->setNext(aux->getNext());
				if(aux->getNext()) aux->getNext()->setPrev(aux->getPrev());
				aux->setPrev(0);
				aux->setNext(0);
			}
			delete aux;
		}

		void print(){
			Node<H>* aux=head;
			while(aux){
				cout<<*aux->getKey()<<" ";
				aux=aux->getNext();
			}
			cout<<endl;
		}
};


template <class H> class CL{
	
	private:
		Node<H> *head, *tail;
		int size;

		void _refreshHead(H x){ //per l'inserimento sfrutta il valore passato come parametro
			if(x > *head->getKey()){
				head=_search(x);
				tail=head->getPrev();
			}
		}

		void _refreshHead2(){ //per la cancellazione fa la ricerca del massimo per far puntare la nuova head correttamente
			H max = *head->getKey();
			Node<H>* aux=head->getNext();
			while(aux && aux!=head){
				if(*aux->getKey() > max) max=*aux->getKey();
				aux=aux->getNext();
			}
			head=_search(max);
			tail=head->getPrev();
		}

		Node<H>* _search(H x){
			Node<H>* aux=head;
			if(!aux) return 0;

			do{
				if(x == *aux->getKey()) return aux;
				aux=aux->getNext();
			}
			while(aux && aux!=head);

			return 0;
		}

		void _del(Node<H>* aux){
			if(!aux) return;

			//casi particolari dimensione
			if(size==1){
				head=0;
				tail=0;
			}
			else if(size==2){
				head=aux->getNext();
				head->setNext(0);
				head->setPrev(0);
				tail=head;
			}
			//casi particolari posizione
			else if(aux==head){
				head=head->getNext();
				head->setPrev(tail);
				tail->setNext(head);
				_refreshHead2();
			}
			else if(aux==tail){
				tail=tail->getPrev();
				tail->setNext(head);
				head->setPrev(tail);
			}
			//caso standard
			else{
				Node<H>* back=aux->getPrev();
				Node<H>* forward=aux->getNext();
				back->setNext(forward);
				forward->setPrev(back);
			}
			delete aux;
			size--;
		}

	public:
		CL(){
			head=tail=0;
			size=0;
		}

		int getSize() const{ return size; }

		void insert(H x){
			if(!head){
				head=new Node<H>(x, head);
				tail=head;
				size++;
				return;
			}

			if(size>1){
				/*if(x > *head->getKey()){
					Node<H>* aux=new Node<H>(x, head, tail);
					tail->setNext(aux);
					head->setPrev(aux);
					head=aux;
				}
				else{*/
					Node<H>* aux=new Node<H>(x, head->getNext(), head);
					head->getNext()->setPrev(aux);
					head->setNext(aux);
				//}
			}
			else{
				/*if(x > *head->getKey()){
					Node<H>* aux=new Node<H>(x, head, head);
					head->setNext(aux);
					head->setPrev(aux);
					head=aux;
				}
				else{*/
					Node<H>* aux=new Node<H>(x, head, head);
					head->setNext(aux);
					head->setPrev(aux);
					tail=aux;
				//}
			}
			size++;
			_refreshHead(x);
		}

		void del(H x){
			_del(_search(x));
		}

		void delAll(H x){
			Node<H>* aux=_search(x);
			while(aux){
				_del(aux);
				aux=_search(x);
			}
		}

		void print(){
			Node<H>* aux=head;
			if(aux){
				do{
					cout<<*aux->getKey()<<" ";
					aux=aux->getNext();
				}
				while(aux && aux!=head);
			}
			cout<<endl;
		}
};

template <class H> class LOL : public List< CL<H> >{
	
	private:
		int k;

	public:
		LOL(int _k){
			List< CL<H> >();
			k=_k;
		}

		void insert(H x){
			Node< CL<H> >* head=List< CL<H> >::head;
			if(!head || head->getKey()->getSize()==k){
				CL<H>* tmp=new CL<H>();
				tmp->insert(x);
				List< CL<H> >::insert(tmp);
			}
			else{
				head->getKey()->insert(x);
			}
		}

		void del(H x){
			Node< CL<H> >* head=List< CL<H> >::head;

			while(head){
				head->getKey()->delAll(x);
				Node< CL<H> >* tmp=head->getNext();
				if(head->getKey()->getSize() == 0) List< CL<H> >::del(head->getKey());
				head=tmp;
			}
		}

		void print(){
			Node< CL<H> >* head=List< CL<H> >::head;
			while(head){
				head->getKey()->print();
				head=head->getNext();
			}
			cout<<endl;
		}

};

int main(){

	/*List<int>* l=new List<int>();

	int a=5;
	int b=3;
	int c=10;
	int d=2;

	l->insert(&a);
	l->insert(&b);
	l->insert(&c);
	l->insert(&d);
	l->print();
	l->del(&c);
	l->del(&a);
	l->del(&d);
	l->del(&b);
	l->print();*/

	/*CL<int>* cl=new CL<int>();
	cl->insert(22);
	cl->insert(10);
	cl->insert(4);
	cl->insert(9);
	cl->insert(25);
	cl->insert(7);
	cl->insert(4);
	cl->insert(9);
	cl->insert(25);
	cl->insert(7);
	cl->insert(25);
	cl->insert(7);
	cl->insert(7);
	cl->print();
	cl->del(22);
	//cl->del(9);
	//cl->del(25);
	//cl->del(7);
	cl->del(20);
	cl->insert(20);
	//cl->del(10);
	cl->del(4);
	cl->print();
	cl->delAll(7);
	cl->delAll(9);
	cl->delAll(25);
	cl->print();
	/*cl->del(25);
	cl->print();
	cl->del(25);
	cl->print();*/

	LOL<int>* lcl=new LOL<int>(4);
	lcl->insert(2);
	lcl->insert(3);
	lcl->insert(1);
	lcl->insert(5);
	lcl->insert(3);
	lcl->insert(7);
	lcl->insert(6);
	lcl->insert(1);
	lcl->insert(2);
	lcl->insert(4);
	lcl->insert(5);
	lcl->insert(3);
	lcl->insert(2);
	lcl->insert(1);
	lcl->print();

	lcl->del(5);
	lcl->del(1);
	lcl->del(2);
	lcl->print();
}