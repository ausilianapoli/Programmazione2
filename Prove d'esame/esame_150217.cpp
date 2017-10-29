#include <iostream>
#include <math.h>

using namespace std;

class Monomio{

	private:
		int grado, coeff;

	public:
		Monomio(int g, int c) : grado(g), coeff(c) {}

		void setGrado(int g){grado=g;}
		void setCoeff(int c){coeff=c;}

		int getGrado() const{return grado;}
		int getCoeff() const{return coeff;}

		void print(){
			cout<<*this;
			cout<<endl;
		}

		int valuta(int x){
			int p=pow(x, this->getGrado());
			return this->getCoeff()*p;
		}

		friend ostream& operator << (ostream &out, const Monomio &m){
			return out<<m.getCoeff()<<"x("<<m.getGrado()<<")";
		}
};

template <class H> class Node{

	private:
		H* key;
		Node<H>* next;

	public:
		Node(H* k=0, Node<H>* _n=0) : key(new H(*k)), next(_n) {}

		void setKey(H* k){key=k;}
		void setNext(Node<H>* n){next=n;}

		H* getKey() const{return key;}
		Node<H>* getNext() const{return next;}
};

class Polinomio{

	private:
		Node<Monomio>* head;
		int *C;
		int n;

		bool PolinomioNullo(){
			if(!head) return true;

			Node<Monomio>* tmp=head;
			int count=0;
			while(tmp){
				if(head->getKey()->getCoeff() == 0) count++;
				tmp=tmp->getNext();
			}
			if(count==n) return true;

			return false;
		}

	public:
		Polinomio(){
			head=0;
		}

		Polinomio(int *_C, int _n){
			C=_C;
			n=_n;
			Monomio* t=new Monomio(n-1, C[0]);
			head=new Node<Monomio>(t);
			Node<Monomio>* memHead=head;
			for(int i=1; i<n; i++){
				Monomio* tmp=new Monomio(n-i-1, C[i]);
				Node<Monomio>* aux=new Node<Monomio>(tmp);
				head->setNext(aux);
				head=aux;
			}
			head=memHead;
		}

		int valuta(int x){
			if(!head) return -9999;

			int result=0;
			Node<Monomio>* aux=head;
			while(aux){
				result+=aux->getKey()->valuta(x);
				aux=aux->getNext();
			}
			return result;
		}

		void print(){
			Node<Monomio>* aux=head;
			while(aux){
				cout<<"("<<*aux->getKey()<<") ";
				if(aux->getNext()) cout<<"+ ";
				aux=aux->getNext();
			}
			cout<<endl;
		}

		Polinomio* add(Monomio* m){
			if(!head) return this;
			*this+*m;
			return this;
		}

		Polinomio* add(Polinomio* p){
			if(!head || p->PolinomioNullo()) return this;

			*this+*p;
			return this;
		}

		Polinomio* mul(Polinomio* p){
			if(!head || p->PolinomioNullo()) return this;

			(*this) * (*p);
			return this;
		}

		Polinomio operator + (Monomio &m){
			//polinomio vuoto
			if(!head){
				head=new Node<Monomio>(&m);
			}

			//in testa
			else if(m.getGrado() >= head->getKey()->getGrado()){
				if(head->getKey()->getGrado() == m.getGrado()) head->getKey()->setCoeff(head->getKey()->getCoeff()+m.getCoeff());
				else head=new Node<Monomio>(&m, head);
			}

			//standard
			else{
				Node<Monomio>* back=head;
				Node<Monomio>* aux=head->getNext();
				while(aux && m.getGrado() < aux->getKey()->getGrado()){
					back=aux;
					aux=aux->getNext();
				}
				if(aux){
					if(aux->getKey()->getGrado() == m.getGrado()) aux->getKey()->setCoeff(aux->getKey()->getCoeff()+m.getCoeff());
					else{
						Node<Monomio>* current=new Node<Monomio>(&m, aux);
						back->setNext(current);
					}
				}
				else{
					Node<Monomio>* current=new Node<Monomio>(&m);
					back->setNext(current);
				}
			}
			return *this;
		}

		Polinomio operator + (const Polinomio &p){
			Node<Monomio>* headP=p.head;
			while(headP){
				*this+*headP->getKey();
				headP=headP->getNext();
			}
			return *this;
		}

		Polinomio operator * (const Polinomio &p){
			Polinomio* nuovo=new Polinomio();
			Node<Monomio>* headQ=head;
			while(headQ){
				Node<Monomio>* headP=p.head;
				while(headP){
					int c=headQ->getKey()->getCoeff() * headP->getKey()->getCoeff();
					int g=headQ->getKey()->getGrado() + headP->getKey()->getGrado();
					Monomio* tmp=new Monomio(g, c);
					*nuovo+*tmp;
					headP=headP->getNext();
				}
				headQ=headQ->getNext();
			}
			*this=*nuovo;
			return *this;
		}

};

int main(){

	Monomio* a=new Monomio(2, 3);
	Monomio* b=new Monomio(1, -2);
	a->print();
	//b->print();
	cout<<a->valuta(2)<<endl;
	cout<<a->valuta(3)<<endl;

	int C[3]={1, 2, 3};
	Polinomio* q=new Polinomio(C, 3);
	//q->print();
	q->add(a)->add(b);
	q->print();
	cout<<q->valuta(2)<<endl;

	int D[4]={1, -2, 3, -2};
	Polinomio* p=new Polinomio(D, 4);
	p->print();
	p->add(q);
	p->print();
	cout<<p->valuta(1)<<endl;

	int E[2]={1, 2};
	int F[2]={2, -2};

	Polinomio* r=new Polinomio(E, 2);
	Polinomio* t=new Polinomio(F, 2);
	r->print();
	t->print();
	r->mul(t);
	r->print();
	r->mul(t);
	r->print();
	cout<<r->valuta(2)<<endl;
}