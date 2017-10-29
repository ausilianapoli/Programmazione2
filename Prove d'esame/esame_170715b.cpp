#include <iostream>

using namespace std;

template <class H> class MSTree{
	
	public:
		virtual void printInput() = 0;
		virtual void printOutput() = 0;
		virtual int height() = 0;
		virtual int calls() = 0;
};


template <class H> class Node{
	
	private:
		H *in, *out;
		Node<H> *parent, *left, *right;
		int n;

	public:
		Node(H *_in, int _n, Node<H> *p=0, Node<H> *l=0, Node<H> *r=0) : in(_in), n(_n), parent(p), left(l), right(r){
			out=0;
		}

		void setOut(H *o){ out=o; }
		void setParent(Node<H> *p){ parent=p;}
		void setLeft(Node<H> *l){ left=l; }
		void setRight(Node<H> *r){ right=r; }

		H* getIn() const{ return in; }
		H* getOut() const{ return out; }
		int getN() const{ return n; }
		Node<H>* getParent() const{ return parent; }
		Node<H>* getLeft() const{ return left; }
		Node<H>* getRight() const{ return right; }

		bool isLeaf(){ return !left && !right; }
};


template <class H> class MyMSTree : public MSTree<H>{
	
	private:
		Node<H> *root;

		void _split(H *A, int na, H* &B, int &nb, H* &C, int &nc){

			nb=na/2;
			nc=na-nb;

			B=new H[nb];
			C=new H[nc];

			for(int i=0; i<nb; i++)	B[i]=A[i];

			for(int i=nb; i<na; i++) C[i-nb]=A[i];
		}

		Node<H>* _builTree(H *A, int na){

			if(na==1){
				return new Node<H>(A, na);
			}

			H *B, *C;
			int nb, nc;

			_split(A, na, B, nb, C, nc);

			Node<H>* node=new Node<H>(A, na);

			Node<H>* left=_builTree(B, nb);
			Node<H>* right=_builTree(C, nc);

			node->setLeft(left);
			node->setRight(right);
			left->setParent(node);
			right->setParent(node);

			return node;
		}

		void merge(H *A, int na, H *B, int nb, H* &C, int &nc){

			nc=na+nb;

			int ia=0, ib=0, ic=0;

			C=new H[nc];

			while(ia<na && ib<nb){
				if(A[ia]<B[ib]) C[ic++]=A[ia++];
				else C[ic++] = B[ib++];
			}

			while(ia<na) C[ic++]=A[ia++];

			while(ib<nb) C[ic++]=B[ib++];
		}

		void _fillOuputs(Node<H>* node){
			if(node->isLeaf()) node->setOut(node->getIn());
			
			else{
				_fillOuputs(node->getLeft());
				_fillOuputs(node->getRight());

				H *A, *B, *C;
				int na, nb, nc;

				A=node->getLeft()->getOut();
				na=node->getLeft()->getN();

				B=node->getRight()->getOut();
				nb=node->getRight()->getN();

				merge(A, na, B, nb, C, nc);

				node->setOut(C);
			}
		}

		int _height(Node<H>* aux){
			if(!aux) return -1;

			int h1=_height(aux->getLeft());
			int h2=_height(aux->getRight());

			return (h1>h2 ? h1 : h2)+1;
		}

		int _calls(Node<H>* aux){
			if(!aux) return 0;

			int n1=_calls(aux->getLeft());
			int n2=_calls(aux->getRight());

			return n1+n2+1;
		}

	public:
		MyMSTree(H *A, int na){
			root=_builTree(A, na);
			_fillOuputs(root);
		}

		void printInput(){
			if(root){
				H *input=root->getIn();
				int ni=root->getN();

				for(int i=0; i<ni; i++) cout<<input[i]<<" ";
			}
			cout<<endl;
		}

		void printOutput(){
			if(root){
				H *output=root->getOut();
				int no=root->getN();

				for(int i=0; i<no; i++) cout<<output[i]<<" ";
			}
			cout<<endl;
		}

		int height(){
			return _height(root);
		}

		int calls(){
			return _calls(root);
		}
};


int main(){

	int A[]={7,9,1,2,8,4,10,3,5,12,15,11,23,6};
	int na=sizeof(A)/sizeof(A[0]);

	MyMSTree<int> *mst = new MyMSTree<int>(A, na);
	
	cout<<"Input: ";
	mst->printInput();

	cout<<"\nOutput: ";
	mst->printOutput();

	cout<<"\nHeight: "<<mst->height();

	cout<<"\n\nCalls: "<<mst->calls();
}