#include <iostream>

using namespace std;


template <class H> class NodeList{
	
	private:
		H key;
		NodeList<H> *next;

	public:
		NodeList(H k, NodeList<H> *n) : key(k), next(n) {}

		void setKey(H k){
			key=k;
		}

		void setNext(NodeList<H> *n){
			next=n;
		}

		H getKey() const{
			return key;
		}

		NodeList<H>* getNext() const{
			return next;
		}
};


template <class H> class Stack{
	
	private:
		NodeList<H> *top, *current;
		int size;

	public:
		Stack(){
			top=current=0;
			size=0;
		}

		H* begin(){
			current=top;
			return current ? new H(current->getKey()) : 0;
		}

		H* next(){
			current=current->getNext();
			return current ? new H(current->getKey()) : 0;
		}

		int getSize() const{
			return size;
		}

		H getSum() const{
			NodeList<H>* aux=top;
			H sum=0;
			while(aux){
				sum+=aux->getKey();
				aux=aux->getNext();
			}
			return sum;
		}

		H* getTop() const{
			return top ? new H(top->getKey()) : 0;
		}

		Stack<H>* ins(H x){
			top=new NodeList<H>(x, top);
			size++;
			return this;
		}

		H* pop(){
			if(!top){
				return 0;
			}
			NodeList<H>* aux=top;
			top=top->getNext();
			H* tmp=new H(aux->getKey());
			delete aux;
			size--;
			return tmp;
		}

		int search(H x){
			NodeList<H>* aux=top;
			while(aux){
				if(x == aux->getKey()){
					return 1;
				}
				aux=aux->getNext();
			}
			return 0;
		}

		void print(){
			NodeList<H>* aux=top;
			while(aux){
				cout<<aux->getKey()<<" ";
				aux=aux->getNext();
			}
			cout<<endl;
		}

		friend bool operator > (const Stack<H> &s1, const Stack<H> &s2){
			if(s1.getSum() > s2.getSum()){
				return true;
			}
			if(s1.getSum() == s2.getSum() && s1.getSize() > s2.getSize()){
				return true;
			}
			if(s1.getSum() == s2.getSum() && s1.getSize() == s2.getSize() && *s1.getTop() > *s2.getTop()){
				return true;
			}
			return false;
		}

		friend bool operator < (const Stack<H> &s1, const Stack<H> &s2){
			return s2>s1;
		}

		friend bool operator == (const Stack<H> &s1, const Stack<H> &s2){
			return !(s1<s2) && !(s1<s2);
		}

		friend ostream& operator << (ostream &out, Stack<H> &obj){
			for(H* it=obj.begin(); it; it=obj.next()){
				out<<*it<<" ";
			}
			return out;
		}

		friend bool operator == (Stack<H> &obj, const H &x){
			for(H* it=obj.begin(); it; it=obj.next()){
				if(*it == x){
					return true;
				}
			}
			return false;
		}
};




template <class H> class NodeBST{
	
	private:
		H key;
		NodeBST<H> *parent, *left, *right;

	public:
		NodeBST(H k, NodeBST<H> *p=0, NodeBST<H> *l=0, NodeBST<H> *r=0) : key(k), parent(p), left(l), right(r) {}

		void setKey(H k){
			key=k;
		}

		void setParent(NodeBST<H>* p){
			parent=p;
		}

		void setLeft(NodeBST<H> *l){
			left=l;
		}

		void setRight(NodeBST<H> *r){
			right=r;
		}

		H getKey() const{
			return key;
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
			return !left && !right;
		}
};


template <class H> class BST{
	
	private:
		NodeBST<H>* root;
		NodeBST<H>* current;

		void _print(NodeBST<H>* aux){
			if(aux){
				_print(aux->getLeft());
				cout<<aux->getKey()<<" ";
				_print(aux->getRight());
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
			while(aux && aux->getLeft()){
				aux=aux->getLeft();
			}
			return aux;
		}

		void _del(NodeBST<H>* aux){
			if(aux){

				//caso 1: il nodo è una foglia
				if(aux->isLeaf()){
					NodeBST<H>* parent=aux->getParent();
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

				//caso 2: il nodo ha un figio
				else if(aux->getLeft()==0 ^ aux->getRight()==0){
					NodeBST<H>* son;
					if(aux->getLeft()){
						son=aux->getLeft();
					}
					else{
						son=aux->getRight();
					}
					NodeBST<H>* parent=aux->getParent();
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
					}
					delete aux;
				}

				//caso 3: il nodo ha due figli
				else{
					NodeBST<H>* min=_minimum(aux->getRight());
					aux->setKey(min->getKey());
					_del(min);
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
			current=0;
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
						NodeBST<H>* tmp=new NodeBST<H>(x, aux);
						aux->setLeft(tmp);
						return this;
					}
					else{
						aux=aux->getLeft();
					}
				}
				else{
					if(!aux->getRight()){
						NodeBST<H>* tmp=new NodeBST<H>(x, aux);
						aux->setRight(tmp);
						return this;
					}
					else{
						aux=aux->getRight();
					}
				}
			}
		}

		int search(H x){
			NodeBST<H>* aux=_search(x);
			return aux ? 1 : 0;
		}

		H* minimum(){
			NodeBST<H>* aux=_minimum(root);
			return aux ? new H(aux->getKey()) : 0;
		}

		BST<H>* del(H x){
			_del(_search(x));
			return this;
		}

		void print(){
			_print(root);
			cout<<endl;
		}

		H* successor(H x){
			NodeBST<H>* aux=_successor(_search(x));
			return aux ? new H(aux->getKey()) : 0;
		}

		H* begin(){
			current=_minimum(root);
			return current ? new H(current->getKey()) : 0;
		}

		H* next(){
			current=_successor(current);
			return current ? new H(current->getKey()) : 0;
		}
};





template <class H> class BrikTree{
	
	public:
		virtual BrikTree<H>* ins(H x) = 0;
		virtual BrikTree<H>* push(H x) = 0;
		virtual H* pop() = 0;
		virtual int search(H x) = 0;
		virtual void print() = 0;
};


template <class H> class MyBrikTree : public BrikTree<H>{
	
	private:
		BST< Stack<H> >* MBT;
		int n;

	public:
		MyBrikTree(){
			MBT=new BST< Stack<H> >();
			n=0;
		}

		BrikTree<H>* ins(H x){
			Stack<H>* s=new Stack<H>();
			s->ins(x);
			MBT->ins(*s);
			n++;
			return this;
		}

		BrikTree<H>* push(H x){
			Stack<H>* s=MBT->begin();
			if(!s){
				return ins(x);
			}
			MBT->del(*s);
			s->ins(x);
			MBT->ins(*s);
			return this;
		}

		int search(H x){
			for(Stack<H>* it=MBT->begin(); it; it=MBT->next()){
				if(*it == x){
					return 1;
				}
			}
			return 0;
		}

		H* pop(){
			Stack<H>* s=MBT->begin();
			if(!s){
				return 0;
			}
			MBT->del(*s);
			H* val=s->pop();
			if(s->getSize()==0){
				MBT->del(*s);
				n--;
			}
			else{
				MBT->ins(*s);
			}
			return val;
		}

		void print(){
			for(Stack<H>* it=MBT->begin(); it; it=MBT->next()){
				cout<<*it<<endl;
			}
			cout<<endl;
		}
};

int main(){

	/*BST<int>* b=new BST<int>();
	b->ins(10)->ins(5)->ins(14)->ins(7)->ins(15)->ins(13)->ins(2);
	b->print();
	cout<<b->search(5)<<"\t"<<b->search(17)<<endl;
	cout<<*b->minimum()<<endl;
	b->del(10)->del(14)->del(2);
	b->print();
	cout<<*b->successor(5)<<"\t"<<b->successor(10)<<endl;

	Stack<int>* s=new Stack<int>();
	s->ins(5)->ins(4)->ins(7)->ins(7)->ins(15)->ins(13)->ins(2);
	s->print();
	s->pop()->pop()->ins(4)->pop();
	s->print();
	cout<<s->getSize()<<"\t"<<s->getSum()<<"\t"<<*s->getTop()<<endl;
	//cout<<*s<<endl;
	cout<<endl;*/

	MyBrikTree<int>* bt=new MyBrikTree<int>();
	bt->ins(15)->ins(12)->ins(6)->ins(9)->ins(10)->ins(4)->ins(2)->ins(30)->ins(23)->ins(11);
	bt->print();
	
	/*cout<<"12: "<<bt->search(12)<<"\t 20: "<<bt->search(20)<<endl;
	bt->push(99);
	bt->print();
	bt->push(98);
	bt->print();
	cout<<"pop: "<<*bt->pop()<<endl;
	bt->print();
	cout<<"pop: "<<*bt->pop()<<endl;
	bt->print();
	cout<<"pop: "<<*bt->pop()<<endl;
	bt->print();
	cout<<"pop: "<<*bt->pop()<<endl;
	bt->print();*/

	for(int i=0; i<4; i++){
		int *val=bt->pop();
		bt->push(*val);
	}
	bt->print();
}