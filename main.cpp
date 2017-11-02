#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;
clock_t start,stop;
double czas=0;

double czas2=0;

//tworzymy wezel

struct wezel{

wezel * next;
wezel * left;
wezel * right;
char a;
int count;

};

//tworzymy liste

void lista(wezel * & root, string s){
start = clock();
unsigned int n,i;
char b;
wezel * p;
bool t;
root = NULL;                    // tworzona jest pusta lista
for(i=0; i<s.length();i++){
p=root;
while(p&&(p->a !=s[i])) p=p->next;  //szukany jest znak s[i]
if(!p){

	p=new wezel;                    //nowy wêze³
	p->next =root;
	p->left =NULL;
	p->right =NULL;
	p->a =s[i];
	p->count =0;
	root=p;                         // wêzê³ umiejscowiony jest na pocz¹tku listy
	}
	p->count++;                     //inkrementujemy licznik wyst¹pieñ znaku
	}

do{                                 //sortujemy rosn¹co
t=true;
p=root;
while (p->next){
if(p->count>p->next->count){
	b=p->a;
	p->a=p->next->a;
	p->next->a=b;
	n=p->count;
	p->count=p->next->count;
	p->next->count=n;
	t=false;
	}
	p=p->next;
	}
 } while(!t);
  stop=clock();
 czas= (double) (stop-start) /CLOCKS_PER_SEC;




}

//tworzymy drzewo Huffmana

void drzewo(wezel*&root){


wezel *p, *r, *w1, *w2;

while(true){

	w1=root;
	w2=w1->next;                // pobieramy z listy dwa pocz¹tkowe wêz³y
if(!w2) break;                  //koniec, jeœli jest tylko jeden element
root=w2->next;
	p=new wezel;                //tworzymy nowy wêze³
	p->left=w1;
	p->right=w2;
	p->count=w1->count+w2->count;

if(!root || (p->count<=root->count)){
	p->next=root;
	root=p;
	continue;
}


r=root;
while(r->next&&(p->count>r->next->count)) r=r->next;
p->next=r->next;
r->next=p;
 }

}

//pokazujemy zawartosc drzewa Huffmana

void pokaz(wezel*p, string d){

if(!p->left) cout<<p->a<<" "<<d<<endl;

else{
pokaz(p->left,d+"0");
pokaz(p->right,d+"1");

 }

}

//kodowanie

bool kod(char  t,wezel*p,string d){
if(!p->left){
	if(t!=p->a) return false;
	else{
	cout<<d;
	return true;
 }
}

else return kod(t,p->left,d+"0") || kod(t,p->right,d+"1");


}

//kod Huffmana

void kodH(wezel*root, string s){
start = clock();

for(unsigned int i=0;i<s.length();i++) // kodowane s¹ poszczególne znaki
kod(s[i],root,"");
 stop=clock();
 czas2= (double) (stop-start) /CLOCKS_PER_SEC;

}

//usuwamy drzewo

void usun(wezel*y){
if(y){
usun(y->left); //usuwane jest lewe poddrzewo
usun(y->right); //usuwane jest prawe poddrzewo
delete y;       //usuwany jest wêzê³
 }
}



int main(){

wezel*root;

fstream plik;

plik.open("plik1.txt", ios::in); //otwieramy plik do odczytu
    if(plik.good()==false){     // sprawdzamy, czy plik zosta³ poprawnie otwarty
        cout<<"plik nie istnieje!"<<endl;
        exit(0);
    }
    string s;
    getline(plik,s);        //wczytujemy dane z pliku
    plik.close();           //zamykamy plik




lista(root,s);              //tworzymy listê
drzewo(root);              //tworzymy drzewo Huffmana
pokaz(root,"");             //  wyœwietlane s¹ kody znaków
kodH(root,s);               //kodowanie i wyœwietlanie wyniku
usun(root);             //usuwanie drzewa

  cout<<endl<<"przechodzenie po liscie zajelo "<<czas<<" s"<<endl;
    cout<<"kodowanie znakow  zajelo "<<czas2<<" s"<<endl;

return 0;
}


