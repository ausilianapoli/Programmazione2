#include <iostream>

using namespace std;

class Candidato{

private:
	const char* CF;
	int v, r, e;

public:
	Candidato(const char* _CF, int _v, int _r, int _e):CF(_CF), v(_v), r(_r), e(_e){}

	int getV() const{
		return v;
	}

	int getR() const{
		return r;
	}

	int getE() const{
		return e;
	}

	const char* getCF() const{
		return CF;
	}

	void setCF(const char* _CF){
		CF=_CF;
	}

	void setV(int _v){
		v=_v;
	}

	void setR(int _r){
		r=_r;
	}

	void setE(int _e){
		e=_e;
	}

	friend bool operator <(const Candidato &Ci, const Candidato &Cj){
		if(Ci.getV()>Cj.getV()){
			return true;
		}
		if(Ci.getV()==Cj.getV() && Ci.getR()>Cj.getR()){
			return true;
		}
		if(Ci.getV()==Cj.getV() && Ci.getR()==Cj.getR() && Ci.getE()<Cj.getE()){
			return true;
		}
		//restituisco false se non ho restituito true in precedenza cioè nel caso in cui i candidati siano uguali oppure Ci.getE()>Cj.getE()
		return false;
	}

	friend bool operator>(const Candidato &Ci, const Candidato &Cj){
		return Cj<Ci;
	}

	friend bool operator==(const Candidato &Ci, const Candidato &Cj){
		return !(Ci<Cj) && !(Ci>Cj);
	}

	friend bool operator !=(const Candidato &Ci, const Candidato &Cj){
		return !(Ci==Cj);
	}

	friend bool operator <=(const Candidato &Ci, const Candidato &Cj){
		return !(Ci>Cj);
	}

	friend bool operator >=(const Candidato &Ci, const Candidato &Cj){
		return !(Ci<Cj);
	}

	friend ostream& operator<<(ostream &stream, const Candidato &c){//stream è il valore di output
		stream<<c.getCF();
		return stream;
	}

};

template <class H> class Element{
	
	private:
		H key;
		Element<H>* next;

	public:
		Element(H k, Element<H> *n=0):key(k), next(n){}

		H getKey(){
			return key;
		}

		Element<H>* getNext(){
			return next;
		}

		void setKey(H k){
			key=k;
		}

		void setNext(Element<H>* n){
			next=n;
		}
};

template <class H> class Lista{
	
	protected:
		Element<H>* head;

		Element<H>* _search(H k){
			if(!head){ //si può anche togliere perché se aux è 0 ritorna sempre 0
				return 0;
			}

			Element<H>* aux=head;

			while(aux!=0 && aux->getKey()<k){
				aux=aux->getNext();
			}

			if(!aux){ //nel caso in cui ho letto tutta la lista e non ho trovato l'elemento
				return 0;
			}
			if(aux->getKey()>k){
				return 0;
			}
			if(aux->getKey()==k){
				return aux;
			}
			 //si può riscrivere più compatto con if else
			/*if(aux && aux->getKey()===k){
				return aux;
			}
			else{
				return 0;
			}*/
		}

	public:
		Lista(){
			head=0;
		}

		Lista<H>* ins(H k){
			if(!head){
				head=new Element<H>(k);
				return this;
			}
			if(k<head->getKey()){//inserimento in testa
				head=new Element<H>(k, head);
				return this;
			}
			Element<H>* prev=0;
			Element<H>* succ=head;

			while(succ && k>succ->getKey()){
				prev=succ;
				succ=succ->getNext();
			}

			Element<H>* node=new Element<H>(k, succ);
			prev->setNext(node);
			return this;

		}

		H search(H k){
			Element<H>* node=_search(k);

			if(node){
				return node->getKey();
			}
		}

		Lista<H>* del(H k){
			Element<H>* node=_search(k);

			if(!node){
				return this;
			}

			if(node==head){//cancellazione in testa
				head=head->getNext();
				delete node;
				return this;
			}

			Element<H> *pred=head;
			
			while(pred->getNext()!=node){
				pred=pred->getNext();
			}
			pred->setNext(node->getNext());
			delete node;
			return this;
		}

		Lista<H>* print(){
			if(head){
				Element<H>* aux=head;
				while(aux){
					cout<<aux->getKey()<<" ";
					aux=aux->getNext();
				}
				cout<<endl;
			}
			return this;
		}
};


class Graduatoria : public Lista<Candidato>{

	public:
		Graduatoria(){
			Lista<Candidato>(); //richiama il costruttore della classe madre
		}

		Candidato search(int posizione){
			Element<Candidato> *aux=head;

			for(int i=1; aux && i<posizione; i++){
				aux=aux->getNext();
			}
			if(aux){
				return aux->getKey();
			}
		}



};


int main(){

	int v=89;
	int r=60;
	int e=27;
	Candidato *a=new Candidato("GTRSDF94S03C351J", v, r, e);
	Candidato *b=new Candidato("FGTSER95Y05H351T", 63, 63, 24);
	Candidato *c=new Candidato("RYUASD93R12E353H", 89, 60, 25);

	if(*a<*b){
		cout<<"True"<<endl;;
	}
	else{
		cout<<"False"<<endl;
	}

	if(*a>=*b){
		cout<<"True"<<endl;
	}
	else{
		cout<<"False"<<endl;
	}

	if(*a==*c){
		cout<<"True"<<endl;
	}
	else{
		cout<<"False"<<endl;
	}

	if(*a<=*c){
		cout<<"True"<<endl;
	}
	else{
		cout<<"False"<<endl;
	}

	Lista<int> *l=new Lista<int>();
	l->ins(2)->ins(3)->ins(12)->ins(4)->ins(9)->ins(5);
	l->del(3)->del(6)->print();

	Graduatoria *g=new Graduatoria();
	g->ins(*a)->ins(*b)->ins(*c);
	g->print();
	cout<<endl;
	cout<<g->search(2);
	

}