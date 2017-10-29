#include <iostream>
#define DIM 7

using namespace std;


class SDCode{

	private:
		const char *cab;
		int fir;

	public:
		SDCode(const char *c, int f) : cab(c), fir(f) {}

		void setCab(const char* c){
			cab=c;
		}

		void setFir(int f){
			fir=f;
		}

		const char* getCab() const{
			return cab;
		}

		int getFir() const{
			return fir;
		}

		friend bool operator < (const SDCode &x, const SDCode &y){
            int count=0;
            for(int i=0; i<10; i++){
                int a=x.getCab()[i];
                int b=y.getCab()[i];
                if(a<b){
                    return true;
                }
                else if(a==b){
                    count++;
                }
                else{
                    return false;
                }
            }

			if(count==10 && x.getFir() < y.getFir()){
				return true;
			}
			//return false;
		}

		friend bool operator > (const SDCode &x, const SDCode &y){
			return y<x;
		}

		friend bool operator == (const SDCode &x, const SDCode &y){
			return !(x<y) && !(x>y);
		}

		friend bool operator != (const SDCode &x, const SDCode &y){
			return !(x==y);
		}

		friend bool operator <= (const SDCode &x, const SDCode &y){
			return !(x>y);
		}

		friend bool operator >= (const SDCode &x, const SDCode &y){
			return !(x<y);
		}

		friend ostream& operator << (ostream &out, const SDCode &x){
			return out<<"("<<x.getCab()<<", "<<x.getFir()<<")";
		}

};


template <class H> class Queue{

	protected:
		int n;
		H **v;
		int front, rear;

		bool _isFull(){
			return n==DIM ? true : false;
		}

		bool _isEmpty(){
			return n==0 ? true : false;
		}



	public:
		Queue(){
			v=new H*[DIM];
			n=0;
			front=rear=0;
		}

		int getN() const{
			return n;
		}

		Queue<H>* enqueue(H x){
			if(!_isFull()){
				v[rear]=new H(x);
				rear=(rear+1)%DIM;
				n++;
				return this;
			}
			cout<<"Queue Overflow"<<endl;
			return this;
		}

		Queue<H>* dequeue(){
			if(!_isEmpty()){
				front=(front+1)%DIM;
				n--;
				return this;
			}
			cout<<"Queue Underflow"<<endl;
			return this;
		}

		void print(){
			if(!_isEmpty()){
                int i=front;
                while(i!=rear){
					cout<<*v[i]<<" ";
				    i=(i+1)%DIM;
                }
			}
			cout<<endl;
		}

};


class SDSet : public Queue<SDCode> {

    private:

        void _quicksort(int left, int right){
            SDCode pivot=*v[((left+right)/2)%DIM];
            int i=left%DIM, j=right%DIM,counterI=left,counterJ=right;

            while(counterI<=counterJ){
                while(*v[i]<pivot){
                    i=(i+1)%DIM;
                    counterI++;
                }
                while(*v[j]>pivot){
                    j=j-1;
                    if(j<0) j=DIM-1;
                    counterJ--;
                }
                if(counterI<=counterJ){
                    SDCode* tmp=v[i];
                    v[i]=v[j];
                    v[j]=tmp;
                    i=(i+1)%DIM;
                    counterI++;
                    j=j-1;
                    if(j<0) j=DIM-1;
                    counterJ--;
                }
            }

            if(left<counterI){
                _quicksort(left, counterJ);
            }
            if(right>counterI){
                _quicksort(counterI, right);
            }
        }


	public:
		SDSet(){
			Queue<SDCode>();
		}

        void sort(){
            _quicksort(front, front+n-1);
        }
};


int main(){

	SDCode *a = new SDCode("XXXXXXCF01", 10089);
    SDCode *b = new SDCode("XXXXXXCF02", 10063);
    SDCode *c = new SDCode("XXXXXXCF01", 10089);
    SDCode *d = new SDCode("XXXXXXCF02", 10089);
    SDCode *e = new SDCode("XXXXXXCF03", 10089);
    SDCode *f = new SDCode("XXXXXXCF01", 10063);

    //2 punti
    if( *a < *b) cout << "True"; else cout << "False"; //True
    if( *a < *c) cout << "True"; else cout << "False"; //False
    cout << endl;

    //2 punti
    if( *a <= *c) cout << "True"; else cout << "False"; //True
    if( *c <= *e) cout << "True"; else cout << "False"; //True
    cout << endl;

    //2 punti
    if( *a >= *b) cout << "True"; else cout << "False"; //False
    if( *c >= *e) cout << "True"; else cout << "False"; //False
    cout << endl;

    //2 punti
    if( *a == *c) cout << "True"; else cout << "False"; //True
    if( *c == *e) cout << "True"; else cout << "False"; //False
    cout << endl;

    //2 punti
    if( *a != *c) cout << "True"; else cout << "False"; //False
    if( *c != *e) cout << "True"; else cout << "False"; //True
    cout << endl;



    //4 punti
    Queue<int> *s = new Queue<int>();
    s->enqueue(2)->enqueue(3)->enqueue(12)->enqueue(4)->enqueue(9)->enqueue(5);
    s->print();  //2, 3, 12, 4, 9, 5
    cout << endl;


    //4 punti
    s->dequeue()->dequeue()->dequeue()->dequeue();
    s->print();  //9, 5
    cout << endl;

    //4 punti
    s->enqueue(1)->enqueue(6)->enqueue(23)->enqueue(27);
    s->print();  //9, 5, 1, 6, 23, 27
    cout << endl;


    //2 punti
    SDSet *q = new SDSet();
    q->enqueue(*a);
    q->enqueue(*b);
    q->enqueue(*c);
    q->enqueue(*d);
    q->dequeue();
    q->enqueue(*f);
    q->dequeue();
    q->enqueue(*a);
    q->enqueue(*b);
    q->enqueue(*c);
    q->dequeue();
    q->dequeue();
    q->enqueue(*d);
    q->print(); //("CF02",63), ("CF01",89), ("CF02",89), ("CF01",63)
    cout<<q->getN()<<endl;
    cout << endl;

    q->sort();
    q->print(); //("CF01",63), ("CF01",89), ("CF02",63), ("CF02",89),
    cout << endl;
 }




 /*//esercizio 1

	char cab[11]="G34TRdfe12";
    int fir=39541;
    SDCode *a=new SDCode(cab, fir);
    SDCode *b=new SDCode("G34TRxcVF2", 34893);
    SDCode *c=new SDCode("G34TRxcVF2", 34891);

    if(*a < *b){
        cout<<"True";
    }
    else{
        cout<<"False";
    }

    cout<<endl;

    if(*a >= *b){
        cout<<"True";
    }
    else{
        cout<<"False";
    }

    cout<<endl;

    if(*a == *c){
        cout<<"True";
    }
    else{
        cout<<"False";
    }

    cout<<endl;

    if(*a <= *c){
        cout<<"True";
    }
    else{
        cout<<"False";
    }

    cout<<endl;
*/
    /*if(*a < *c){
        cout<<"True";
    }
    else{
        cout<<"False";
    }

    cout<<endl;

    if(*b < *c){
        cout<<"True";
    }
    else{
        cout<<"False";
    }

    cout<<endl;

    if(*b > *c){
        cout<<"True";
    }
    else{
        cout<<"False";
    }

    cout<<endl;

    cout<<*a<<endl;
    cout<<*b<<endl;
    cout<<*c<<endl;
*/
/*//esercizio 2

    //4 punti                               //errore
    Queue<int> *q = new Queue<int>();
    q->enqueue(2)->enqueue(3)->enqueue(12)->enqueue(4)->enqueue(9)->enqueue(5);
    q->dequeue()->dequeue();
    q->print();
    q->enqueue(2)->enqueue(3);
    q->print();
    cout << endl;



    //2 punti
    SDSet *s = new SDSet();
    q->enqueue(*a)->enqueue(*b)->enqueue(*c);
    q->print(); */

