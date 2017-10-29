#include <iostream>

using namespace std;

template <class H> class Node{
	
	private:
		H *key;
		Node<H> *next;

	public:
		Node(H *k=0, Node<H> *n=0) : key(new H(*k)), next(n) {}

		void setKey(H* k){key=k;}
		void setNext(Node<H> *n){next=n;}

		H* getKey() const{return key;}
		Node<H>* getNext() const{return next;}
};

template <class H> class List{
	
	protected:
		Node<H> *head, *tail;

	public:
		List(){
			head=tail=0;
		}

		Node<H>* getHead() const{return head;}

		List<H>* ins(H x){
			if(!head){
				head=new Node<H>(&x);
				tail=head;
				return this;
			}

			Node<H>* aux=new Node<H>(&x);

			//in testa
			if(x > *head->getKey()){
				aux->setNext(head);
				head=aux;
				return this;
			}

			//in coda
			if(x < *tail->getKey()){
				tail->setNext(aux);
				tail=aux;
				return this;
			}

			//standard
			Node<H>* forward=head->getNext();
			Node<H>* back=head;
			while(forward && x < *forward->getKey()){
				back=forward;
				forward=forward->getNext();
			}
			if(forward){
				back->setNext(aux);
				aux->setNext(forward);
			}
			return this;
		}

		List<H>* del(H x){
			if(!head) return this;

			//in testa
			if(x == *head->getKey()){
				head=head->getNext();
				return this;
			}

			//in coda e standard
			Node<H>* forward=head->getNext();
			Node<H>* back=head;
			while(forward && x <= *forward->getKey()){
				if(x == *forward->getKey()){
					back->setNext(forward->getNext());
					if(forward == tail) tail=back;
					return this;
				}
				back=forward;
				forward=forward->getNext();
			}

			return this;
		}

		void delNode(Node<H>* aux){
			if(aux){
				head=aux->getNext();
				delete aux;
			}
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


template <class H> class Stack{
	
	private:
		Node<H>* top;
		int n;

	public:
		Stack(){
			top=0;
			n=0;
		}

		int getN() const{return n;}

		Stack<H>* push(H x){
			top=new Node<H>(&x, top);
			n++;
			return this;
		}

		H* pop(){
			if(!top) return 0;

			Node<H>* aux=top;
			top=top->getNext();
			H* val=aux->getKey();
			delete aux;
			n--;
			return val;
		}

		H* getTop() const{return top ? top->getKey() : 0;}
		Node<H>* getNode() const{return top;}

		void print(){
			Node<H>* aux=top;
			while(aux){
				cout<<*aux->getKey()<<" ";
				aux=aux->getNext();
			}
			cout<<endl;
		}

		friend bool operator < (const Stack<H> &s1, const Stack<H> &s2){
			if(*s1.getTop() < *s2.getTop()) return true;
			return false;
		}

		friend bool operator > (const Stack<H> &s1, const Stack<H> &s2){
			return s2<s1;
		}

		friend bool operator <= (const Stack<H> &s1, const Stack<H> &s2){
			return !(s1>s2);
		}

		friend bool operator == (const Stack<H> &s1, const Stack<H> &s2){
			return !(s1<s2) && !(s1>s2);
		}

		friend ostream& operator << (ostream &out, Stack<H> &s){
			Node<H>* aux=s.getNode();
			if(aux){
				out<<"[ ";
				while(aux){
					out<<*aux->getKey()<<" ";
					aux=aux->getNext();
				}
				out<<"]";
			}
			return out;
		}

			
};


template <class H> class MultiStack{
	
	public:
		virtual H* pop() = 0;
		virtual void push(H x) = 0;
		virtual void newPush(H x) = 0;
		virtual void print() = 0;
};

template <class H> class MyMultiStack{
	
	private:
		List< Stack<H> >* ls;

	public:
		MyMultiStack(){
			ls=new List< Stack<H> >();
		}

		void newPush(H x){
			Stack<H>* s=new Stack<H>();
			s->push(x);
			ls->ins(*s);
		}

		void push(H x){
			Node< Stack<H> >* head=ls->getHead();
			if(head){
				head->getKey()->push(x);
				Stack<H> *s=head->getKey();
				ls->del(*head->getKey());
				ls->ins(*s);
			}
		}

		H* pop(){
			Node< Stack<H> >* head=ls->getHead();
			if(head){
				H* val=head->getKey()->pop();
				if(head->getKey()->getN() == 0){
					ls->delNode(head);
					return val;
				}
				Stack<H>* s=head->getKey();
				ls->del(*head->getKey());
				ls->ins(*s);
				return val;
			}
			return 0;
		}

		void print(){
			Node< Stack<H> >* head=ls->getHead();
			while(head){
				cout<<*head->getKey();
				head=head->getNext();
			}
			cout<<endl;
		}
};


int main(){

	/*List<int>* l=new List<int>();
	l->ins(100)->ins(99)->print();
	l->del(100)->del(99)->print();
	l->del(100);
	l->ins(8)->ins(4)->ins(10)->ins(7)->ins(9)->ins(2);
	l->print();
	l->del(5)->del(2)->del(10)->del(7)->ins(1);
	l->print();*/

	/*Stack<int>* s=new Stack<int>();
	s->push(45)->push(47)->push(41)->push(74)->push(23);
	s->print();
	s->pop();
	s->pop();
	s->push(7);
	s->print();*/

	MyMultiStack<int>* MMS=new MyMultiStack<int>();
	MMS->newPush(3);
	MMS->newPush(7);
	MMS->newPush(1);
	MMS->newPush(8);
	//MMS->print();
	MMS->push(5);
	MMS->push(2);
	MMS->push(6);
	MMS->push(1);
	MMS->push(8);
	MMS->push(5);
	MMS->push(6);
	MMS->push(1);
	MMS->push(4);
	//MMS->print();
	for(int i=0; i<5; i++) MMS->pop();
	/*MMS->pop();
	MMS->pop();
	MMS->pop();
	MMS->pop();
	MMS->pop();*/
	MMS->print();

}