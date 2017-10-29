#include <iostream>

using namespace std;

class Studente{

	private:
		const char* matricola;
		int v, r, e;

	public:
		Studente(const char* m, int _v, int _r, int _e) : matricola(m), v(_v), r(_r), e(_e) {}

		void setMatricola(const char* m){matricola=m;}
		const char* getMatricola() const{return matricola;}

		void setV(int _v){v=_v;}
		int getV() const{return v;}

		void setR(int _r){r=_r;}
		int getR() const{return r;}

		void setE(int _e){e=_e;}
		int getE() const{return e;}

		friend bool operator < (const Studente &Si, const Studente &Sj){
			if(Si.getV() > Sj.getV()) return true;
			if(Si.getV() == Sj.getV() && Si.getR() > Sj.getR()) return true;
			if(Si.getV() == Sj.getV() && Si.getR() == Sj.getR() && Si.getE() < Sj.getE()) return true;
			else return false;
		}

		friend bool operator >(const Studente &Si, const Studente &Sj){
			return Sj<Si;
		}

		friend bool operator == (const Studente &Si, const Studente &Sj){
			return !(Si>Sj) && !(Si<Sj);
		}

		friend bool operator != (const Studente &Si, const Studente &Sj){
			return !(Si==Sj);
		}

		friend bool operator <= (const Studente &Si, const Studente &Sj){
			return !(Si>Sj);
		}

		friend bool operator >= (const Studente &Si, const Studente &Sj){
			return !(Si<Sj);
		}

		friend ostream& operator << (ostream &out, const Studente &S){
			return out<<S.getMatricola();
		}

};

template <class H> class Node{
	
	private:
		H key;
		Node<H> *parent, *left, *right;

	public:
		Node(H k, Node<H> *p=0, Node<H> *l=0, Node<H> *r=0) : key(k), parent(p), right(r), left(l) {}

		void setKey(H k){key=k;}
		H getKey() const{return key;}

		void setParent(Node<H> *p){parent=p;}
		Node<H>* getParent() const{return parent;}

		void setLeft(Node<H> *l){left=l;}
		Node<H>* getLeft() const{return left;}

		void setRight(Node<H> *r){right=r;}
		Node<H>* getRight() const{return right;}
};

template <class H> class BST{
	
	protected:
		Node<H> *root;
		int n;

		void _print(Node<H>* aux){
			if(aux){
				_print(aux->getLeft());
				cout<<aux->getKey()<<" ";
				_print(aux->getRight());
			}
		}

		Node<H>* _search(H x){
			Node<H>* aux=root;
			while(aux){
				if(x < aux->getKey()) aux=aux->getLeft();
				else if(x > aux->getKey()) aux=aux->getRight();
				else return aux;
			}
			return 0;
		}

	public:
		BST(){
			root=0;
			n=0;
		}

		int getN() const{return n;}

		BST<H>* ins(H x){
			if(!root){
				root=new Node<H>(x);
				n++;
				return this;
			}

			Node<H>* aux=root;
			while(true){
				if(x <= aux->getKey()){
					if(!aux->getLeft()){
						Node<H>* current=new Node<H>(x, aux);
						aux->setLeft(current);
						n++;
						return this;
					}
					else aux=aux->getLeft();
				}
				else{
					if(!aux->getRight()){
						Node<H>* current=new Node<H>(x, aux);
						aux->setRight(current);
						n++;
						return this;
					}
					else aux=aux->getRight();
				}
			}
		}

		H* search(H x){
			Node<H>* aux=_search(x);
			return aux ? new H(aux->getKey()) : 0;
		}

		void print(){
			_print(root);
			cout<<endl;
		}
};

class Valutazione : public BST<Studente>{

	private:
		Node<Studente>* _minimum(Node<Studente>* aux){
			while(aux && aux->getLeft()) aux=aux->getLeft();
			return aux;
		}

		Node<Studente>* _successor(Node<Studente>* aux){
			if(!aux) return 0;

			if(aux->getRight()) return _minimum(aux->getRight());

			Node<Studente>* parent=aux->getParent();
			while(parent && parent->getRight() && parent->getRight() == aux){
				aux=parent;
				parent=parent->getParent();
			}
			return parent;
		}

	public:
		Valutazione() : BST<Studente>() {}

		Studente* search(int pos){
			if(pos > this->getN()) return 0;

			int i=1;
			Node<Studente>* aux=_minimum(root);
			while(i < pos && aux){
				aux=_successor(aux);
				i++;
			}
			return aux ? new Studente(aux->getKey()) : 0;
		}
};


int main(){

	int v=89, r=60, e=27;
	Studente *a=new Studente("X81000123", v, r, e);
	Studente *b=new Studente("X81000452", 63, 63, 24);
	Studente *c=new Studente("X81000104", 89, 60, 25);

	if(*a < *b) cout<<"True"<<endl; //true
	else cout<<"False"<<endl;

	if(*a >= *b) cout<<"True"<<endl; //false
	else cout<<"False"<<endl;

	if(*a == *c) cout<<"True"<<endl; //false
	else cout<<"False"<<endl;

	if(*a <= *c) cout<<"True"<<endl; //false
	else cout<<"False"<<endl;

	if(*b > *c) cout<<"True"<<endl; //true
	else cout<<"False"<<endl;

	if(*c != *b) cout<<"True"<<endl; //true
	else cout<<"False"<<endl;

	cout<<*a<<endl;
	cout<<*b<<endl;
	cout<<*c<<endl;

	BST<int>* t=new BST<int>();
	t->ins(2)->ins(3)->ins(12)->ins(4)->ins(9)->ins(5)->print();
	cout<<"search 5: "<<*t->search(5)<<"\tsearch 10: "<<t->search(10)<<endl;

	Valutazione* val=new Valutazione();
	val->ins(*a)->ins(*b)->ins(*c);
	val->print();
	cout<<*val->search(2)<<endl;
	cout<<*val->search(1)<<endl;
	cout<<val->search(4)<<endl;
}