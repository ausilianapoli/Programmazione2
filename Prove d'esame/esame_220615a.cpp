#include <iostream>

using namespace std;

template <class H> class Node{
	
	private:
		H key;
		Node<H> *colonna, *riga;
		int pos;

	public:
		Node(H k, int p, Node<H> *c=0, Node<H> *r=0) : key(k), pos(p), colonna(c), riga(r) {}

		void setKey(H k){key=k;}
		H getKey() const{return key;}

		void setPos(int p){pos=p;}
		int getPos() const{return pos;}

		void setColonna(Node<H>* c){colonna=c;}
		Node<H>* getColonna() const{return colonna;}

		void setRiga(Node<H> *r){riga=r;}
		Node<H>* getRiga() const{return riga;}
};

template <class H> class LMatrix{
	
	public:
		virtual LMatrix<H>* set(int i, int j, H x) = 0;
		virtual H get(int i, int j) = 0;
		virtual void reset (int i, int j) = 0;
		virtual void print() = 0;
		virtual LMatrix<H>* multiply(LMatrix<H>* A) = 0;
		virtual int search(H x) = 0;
		virtual int getN() const = 0;
		virtual int getM() const = 0;
};

template <class H> class MyLMatrix : public LMatrix<H>{
	
	private:
		Node<H> *head;
		int n, m;

		int _search(Node<H>* aux, int r, H x){
			if(!aux) return r;

			Node<H>* tmp=aux;
			while(tmp){
				if(tmp->getKey() == x) r++;
				tmp=tmp->getRiga();
			}

			r=_search(aux->getColonna(), r, x);
		}

	public:
		MyLMatrix(int n, int m){
			this->n=n;
			this->m=m;

			//setto la head come origine della matrice
			head=new Node<H>(0,0);

			//costruisco la colonna
			Node<H>* current=head;
			for(int i=1; i<n; i++){
				Node<H>* aux=new Node<H>(0,i);
				current->setColonna(aux);
				current=aux;
			}

			//costruisco le righe
			current=head;
			while(current){
				Node<H>* tmp=current;
				for(int i=1; i<m; i++){
					Node<H>* aux=new Node<H>(0, i);
					tmp->setRiga(aux);
					tmp=aux;
				}
				current=current->getColonna();
			}

			//collegamento nodi fra di essi
			Node<H>* c1=head->getRiga();
			Node<H>* c=head->getColonna();
			Node<H>* c2=c->getRiga();
			while(c2){
				Node<H>* back=c1;
				Node<H>* forward=c2;
				while(forward){
					back->setColonna(forward);
					back=back->getRiga();
					forward=forward->getRiga();
				}
				c1=c2;
				c=c->getColonna();
				if(c) c2=c->getRiga();
				else c2=0;
			}
		}

		int getN() const{return n;}
		int getM() const{return m;}

		LMatrix<H>* set(int i, int j, H x){
			if(i>n || j >m) return this;

			Node<H>* aux=head;
			if(i>0){
				for(int l=0; l<i; l++) aux=aux->getColonna();
			}
			if(j>0){
				for(int l=0; l<j; l++) aux=aux->getRiga();
			}
			aux->setKey(x);

			return this;
		}

		H get(int i, int j){
			if(i>n || j>m) return -9999;

			Node<H>* aux=head;
			if(i>0){
				for(int l=0; l<i; l++) aux=aux->getColonna();
			}
			if(j>0){
				for(int l=0; l<j; l++) aux=aux->getRiga();
			}
			return aux->getKey();
		}

		void reset(int i, int j){
			if(i>n || j>m) return;

			Node<H>* aux=head;
			if(i>0){
				for(int l=0; l<i; l++) aux=aux->getColonna();
			}
			if(j>0){
				for(int l=0; l<j; l++) aux=aux->getRiga();
			}
			return aux->setKey(0);
		}

		void print(){
			Node<H>* colonne=head;
			while(colonne){
				Node<H>* righe=colonne;
				while(righe){
					cout<<righe->getKey()<<" ";
					righe=righe->getRiga();
				}
				cout<<endl;
				colonne=colonne->getColonna();
			}
			cout<<"----------"<<endl;
		}

		LMatrix<H>* multiply(LMatrix<H>* A){
			if(this->getM() != A->getN()) return this;
			
			MyLMatrix<H> result=MyLMatrix<H>(this->getN(), A->getM());
			//result.print();

			int k=0;
			while(k < result.getM()){
				int j=0;
				while(j < this->getN()){
					int i=0;
					H sum=0;
					while(i < this->getM()){
						H prodotto = this->get(j, i) * A->get(i, k);
						sum+=prodotto;
						i++;
					}
					result.set(j, k, sum);
					j++;
				}
				k++;
			}

			result.print();

			return this;
		}

		int search(H x){
			int r=_search(head, 0, x);
			return r;
		}

};

int main(){

	MyLMatrix<int>* lm=new MyLMatrix<int>(3, 4);
	//lm->print();
	lm->set(0, 0, 7);
	lm->set(1, 0, 0);
	lm->set(2, 0, 6);
	lm->set(0, 1, 9);
	lm->set(1, 1, 0);
	lm->set(2, 1, 0);
	lm->set(0, 2, 1);
	lm->set(1, 2, 2);
	lm->set(2, 2, 8);
	lm->set(0, 3, 0);
	lm->set(1, 3, 3);
	lm->set(2, 3, 0);
	lm->print();
	/*cout<<lm->get(0, 0)<<endl;
	cout<<lm->get(2, 2)<<endl;
	cout<<lm->get(4, 0)<<endl;
	lm->reset(2, 2);
	cout<<lm->get(2, 2)<<endl;
	lm->print();*/

	MyLMatrix<int>* lm2=new MyLMatrix<int>(4, 2);
	//lm2->print();
	lm2->set(0, 0, 1);
	lm2->set(1, 0, 0);
	lm2->set(2, 0, 3);
	lm2->set(3, 0, 7);
	lm2->set(0, 1, 2);
	lm2->set(1, 1, 0);
	lm2->set(2, 1, 0);
	lm2->set(3, 1, 1);
	lm2->print();

	cout<<"LMatrix A * LMatrix B = "<<endl;
	lm->multiply(lm2);

	cout<<"search 0: "<<lm->search(0)<<"\tsearch 9: "<<lm->search(9)<<"\tsearch 5: "<<lm->search(5)<<endl;

}