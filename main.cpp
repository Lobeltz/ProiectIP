#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <graphics.h>
#include <winbgim.h>
using namespace std;

ifstream fin ("CalcRO.in");
ofstream fout ("CalcRO.out");

struct BIG_INT { //Numere mari
    int v[100] = { 0 };
    bool semn = 0;
    int operatie = 0;
};

BIG_INT N1,N2,N3,v1[100],v2[100],v3[100];

struct REAL {   //Numere reale
    double n = 0;
    int operatie = 0;
};

REAL RezultatReal,V1[100],V2[100],V3[100];
char SirCifreMari[50][20] = { "unu","doi","trei","patru","cinci","sase","sapte","opt","noua","zece","unsprezece","doisprezece","treisprezece","paisprezece","cinsprezece","saisprezece"
                ,"saptisprezece","optisprezece","nouasprezece","douazeci","treizeci","patruzeci","cincizeci","saizeci","saptezeci","optzeci","nouazeci","o suta","sute","o mie","mii",
                "un milion","milioane","un miliard","miliarde","un bilion","bilioane","un trilion","trilioane","un cvadrilion","cvadrilioane","un catralion","catralioane",
                "un cvintilion","cvintilioane","un sextilion","sextilioane" };
char SirOperatori[10] = { '`','+','-' ,'*' ,'/' ,'=' ,'(' ,')' };
char CaractereValideCifre[20]={'1','2','3','4','5','6','7','8','9','0','+','-','*','x','/',':','(',')',' '};
char CaractereValideLitere[200]={"abcdefghijklmnopqrstuvwxyz _"};
int pozitietextx=300,pozitietexty=100;


void conversie (long long int x , BIG_INT& nr);// converteste un int in BIG_INT
void addlBIG (BIG_INT& nr , int x);// Adauga cifra x la stanga numarului
void addrBIG (BIG_INT& nr , int x);// Adauga cifra x la dreapta numarului
void clearBIG (BIG_INT& nr);// Face ca toate valorile unui BIG_INT sa fie 0
bool maimareBIG (BIG_INT numar1 , BIG_INT numar2);//Compara doua BIG_INT

void citireBIG (char sir[] , BIG_INT vector[] , int& lungime);//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de BIG_INT
void citireREAL (char sir[] , REAL vector[] , int& lungime);//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de REAL
void afisareBIG (BIG_INT nr);// Afiseaza un BIG_INT in cifre
void afisareREAL (REAL x);//Afiseaza un numar REAL
void afisareROBIG (BIG_INT numar , int poz , int pas);//Afiseaza un BIG_INT in litere (se apeleaza astfel: afisareROBIG (numar, 1 , numar.v[0]) )
void memorareROBIG (BIG_INT numar , int poz , int pas , char c[]);
void afisareROREAL (REAL x);//Afiseaza un REAL in litere
void memorareROREAL (REAL x , char c[]);
void afisareROsirBIG (BIG_INT vector[] , int lungime);//Traduce un vector de BIG_INT in limba romana (vecotrul trebuie sa aiba forma prefixata)
void memorareROsirBIG (BIG_INT vector[] , int lungime , char c[]);
void afisareROsirREAL (REAL vector[] , int lungime);//Traduce un vector de REAL in limba romana (vecotrul trebuie sa aiba forma prefixata)
void memorareROsirREAL (REAL vector[] , int lungime , char c[]);

void adunareBIG (BIG_INT& nr1 , BIG_INT& nr2 , BIG_INT& nr3);// Calculeaza suma a doua BIG_INT
void scadereBIG (BIG_INT& numar1 , BIG_INT& numar2 , BIG_INT& rezultat);// Calculeaza diferenta a doua BIG_INT
void scaderesecundaraBIG (BIG_INT& numar1 , BIG_INT& numar2 , BIG_INT& rezultat , bool semn);// Functie secundara pentru scadere, calculeaza propiu-zis diferenta a doua numere pozitive primul avand mai multe cifre
void inmultireBIG (BIG_INT& numar1 , BIG_INT& numar2 , BIG_INT& rezultat);//Inumlteste doua BIG_INT
void inmultiresBIG (BIG_INT& numar1 , int cifra , BIG_INT& rezultat , int zero);//Functie secundara pentru inmultire, calculeaza produsul dintre un BIG_INT si o cifra si adauga un numar specificat de zerouri
void impartireBIG (BIG_INT deimpartit , BIG_INT impartitor , BIG_INT& cat);//Calculeaza catul impartirii naturale a doua BIG_INT
void impartiresBIG (BIG_INT& nr1 , int x , BIG_INT& nr2);//Imparte un BIG_INT la o cifra  (nefolosit)

int prioBIG (BIG_INT Operator);//Calculeaza prioritate operatorilor pentru conversia postfixata
int prioREAL (REAL nr);//Calculeaza prioritate operatorilor pentru conversia postfixata
void infixtopostfixBIG (BIG_INT vector1[] , BIG_INT vector2[] , int& lungime);//Transforma vectorul 1 de BIG_INT cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
void infixtopostfixREAL (REAL vector1[] , REAL vector2[] , int& lungime);//Transforma vectorul 1 de REAL cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
BIG_INT evalpostfixBIG (BIG_INT vector[] , int lungime);//Evalueaza o expresie postfixata si returneaza rezultatul
REAL evalpostfixREAL (REAL vector[] , int lungime);//Evalueaza o expresie postfixata si returneaza rezultatul
void infixtoprefixBIG (BIG_INT vector1[] , BIG_INT vector2[] , int& lungime);//Transforma vectorul 1 de BIG_INT cu forma infixata in vectorul 2 cu forma prefixata
void infixtoprefixREAL (REAL vector1[] , REAL vector2[] , int& lungime);//Afiseaza un REAL in litere

int done;
void meniu1();
void meniuZecim();
void meniuBig();
void meniu2();
void meniuLitBig();
void meniuLitZec();
void meniuCifBig();
void meniuCifZec();


 int main(){
    meniu1();
    closegraph();

    return 0;
 }


 void meniuLitBig()
{
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    readimagefile("back.jpg",900,800,1020,920);

    char caracter,String[100];
    int sfarsitString=0;
    bool notEscaped=1;
    short x,y;

    while(kbhit())getch();
    while(caracter!=13 || caracter!=27){
        if(caracter==13){       //enter

            break;
        }
        if(caracter==27){       //escape
            notEscaped=0;
            break;
        }
        caracter=getch();
        if(strchr(CaractereValideLitere,caracter)==0) continue;
        String[sfarsitString]=caracter;
        String[sfarsitString+1]=NULL;
        outtextxy(pozitietextx,pozitietexty,String);
        sfarsitString++;
    }
    while(1 && notEscaped){
        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920) {
                break;
            }
        }
    }
    meniuBig();
}
void meniuLitZec()
{
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    readimagefile("back.jpg",900,800,1020,920);

    char caracter,String[100];
    int sfarsitString=0;
    bool notEscaped=1;
    short x,y;

    while(kbhit())getch();
    while(caracter!=13 || caracter!=27){
        if(caracter==13){       //enter

            break;
        }
        if(caracter==27){       //escape
            notEscaped=0;
            break;
        }
        caracter=getch();
        if(strchr(CaractereValideLitere,caracter)==0) continue;
        String[sfarsitString]=caracter;
        String[sfarsitString+1]=NULL;
        outtextxy(pozitietextx,pozitietexty,String);
        sfarsitString++;
    }
    while(1 && notEscaped){
        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920) {
                break;
            }
        }
    }
    meniuZecim();
}
void meniuCifBig(){
    settextstyle(1,HORIZ_DIR,5);
     cleardevice();
    readimagefile("back.jpg",900,800,1020,920);

    char caracter,String[100];
    int sfarsitString=0;
    bool notEscaped=1;
    short x,y;

    while(kbhit())getch();
    while(caracter!=13 || caracter!=27){
        if(caracter==13){       //enter
            settextstyle(1,HORIZ_DIR,2);
            int l=0,ltot=0;
            char SirAuxiliar[200],SirComplet[250];
            for (int i=0;i<=199;i++) SirAuxiliar[i]=NULL;
            for (int i=0;i<=249;i++) SirComplet[i]=NULL;
            citireBIG(String,v1,l);
            ltot=l;
            infixtopostfixBIG(v1,v2,ltot);
            N1=evalpostfixBIG(v2,ltot);
            infixtoprefixBIG(v1,v3,l);
            memorareROsirBIG(v3,l,SirAuxiliar);
            strcpy(SirComplet+strlen(SirComplet),SirAuxiliar);
            for (int i=0;i<=199;i++) SirAuxiliar[i]=NULL;
            strcpy(SirComplet+strlen(SirComplet),"este ");
            memorareROBIG(N1,1,N1.v[0],SirAuxiliar);
            strcpy(SirComplet+strlen(SirComplet),SirAuxiliar);

            clearBIG(N1);clearBIG(N2);clearBIG(N3);
            for(int i=0;i<=100;i++){
                clearBIG(v1[i]);
                clearBIG(v2[i]);
                clearBIG(v3[i]);
            }

            // DE EDITAT SIRUL ESTE IN SirComplet
            outtextxy(100,500,SirComplet);

            break;
        }
        if(caracter==27){       //escape
            notEscaped=0;
            break;
        }
        caracter=getch();
        if(strchr(CaractereValideCifre,caracter)==0) continue;
        String[sfarsitString]=caracter;
        String[sfarsitString+1]=NULL;
        outtextxy(pozitietextx,pozitietexty,String);
        sfarsitString++;
    }
    while(1 && notEscaped){
        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920) {
                break;
            }
        }
    }
    meniuBig();
}
void meniuCifZec(){
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    readimagefile("back.jpg",900,800,1020,920);

    char caracter,String[100];
    int sfarsitString=0;
    bool notEscaped=1;
    short x,y;

    while(kbhit())getch();
    while(caracter!=13 || caracter!=27){
        if(caracter==13){       //enter
            settextstyle(1,HORIZ_DIR,2);
            int l=0,ltot=0;
            char SirAuxiliar[200],SirComplet[250];
            for (int i=0;i<=199;i++) SirAuxiliar[i]=NULL;
            for (int i=0;i<=249;i++) SirComplet[i]=NULL;
            citireREAL(String,V1,l);
            ltot=l;
            infixtopostfixREAL(V1,V2,ltot);
            RezultatReal=evalpostfixREAL(V2,ltot);
            infixtoprefixREAL(V1,V3,l);
            memorareROsirREAL(V3,l,SirAuxiliar);
            strcpy(SirComplet+strlen(SirComplet),SirAuxiliar);
            for (int i=0;i<=199;i++) SirAuxiliar[i]=NULL;
            strcpy(SirComplet+strlen(SirComplet),"este ");
            memorareROREAL(RezultatReal,SirAuxiliar);
            strcpy(SirComplet+strlen(SirComplet),SirAuxiliar);
            for(int i=0;i<=99;i++){
                V1[i].n=0; V2[i].n=0; V3[i].n=0;
                V1[i].operatie=0; V2[i].operatie=0; V3[i].operatie=0;
            }
            RezultatReal.n=0; RezultatReal.operatie=0;

            // DE EDITAT SIRUL ESTE IN SirComplet
            outtextxy(100,500,SirComplet);
            break;
        }
        if(caracter==27){       //escape
            notEscaped=0;
            break;
        }
        caracter=getch();
        if(strchr(CaractereValideCifre,caracter)==0) continue;
        String[sfarsitString]=caracter;
        String[sfarsitString+1]=NULL;
        outtextxy(pozitietextx,pozitietexty,String);
        sfarsitString++;
    }
    while(1 && notEscaped){

        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920) {
                break;
            }
        }
    }
    meniuZecim();
}
void meniuBig()
{
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    short x,y;
    //readimagefile("fundal.jpg",0,0,1920,1080);
    outtextxy(900,300,"Litere");
    outtextxy(900,550,"Cifre");
    readimagefile("back.jpg",900,800,1020,920);
    while(1)
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920)
                meniu2();
            else
                if(x>530&&x<1376&&y>300&&y<340)
                    meniuLitBig();
            else
                if(x>600&&x<1325&&y>500&&y<600)
                    meniuCifBig();

        }
}
void meniuZecim()
{
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    short x,y;
    //readimagefile("fundal.jpg",0,0,1920,1080);
    outtextxy(900,300,"Litere");
    outtextxy(900,550,"Cifre");
    readimagefile("back.jpg",900,800,1020,920);
    while(1)
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920)
                meniu2();
            else
                if(x>530&&x<1376&&y>300&&y<340)
                    meniuLitZec();
            else
                if(x>600&&x<1325&&y>500&&y<600)
                    meniuCifZec();
        }
}
void meniu2()
{
    setbkcolor(15);
    cleardevice();
    int ok2=0;
    short x,y;
    readimagefile("fundal.jpg",0,0,1920,1080);
    settextstyle(1,HORIZ_DIR,5);
    setcolor(0);
    setbkcolor(15);
    outtextxy(530,300,"Rezultate cu numere zecimale");
    outtextxy(600,500,"Rezultate cu numere mari");
    readimagefile("back.jpg",900,800,1020,920);

    //line(530,299,1376,299);
    //line(1377,299,1377,340);
    //line(600,499,1325,499);
    //line(1326,500,1326,540);
    while(!ok2)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>530&&x<1376&&y>300&&y<340)
                meniuZecim();
            else if(x>600&&x<1325&&y>499&&y<540)
                meniuBig();
            else if(x>900 && x<1020 && y>800 && y<920)
                meniu1();
        }
    }
}
void meniu1()
{
    initwindow(1920,1080,"CalcRO",true);
    setbkcolor(15);
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    short startJoc=0;
    short x,y;
    readimagefile("fundal.jpg",0,0,1920,1080);
    readimagefile("start.jpg",600,200,1320,500);
    readimagefile("exit.jpg",800,600,1120,800);
    while(!done)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>600&&x<1320&&y>200&&y<500)
                meniu2();
            if(x>800&&x<1120&&y>600&&y<800)
                exit(0);
        }
    }
}

 /////////////////////////////////////////////

// converteste un int in BIG_INT
void conversie (long long int x , BIG_INT& numar) {
    long long int putere = 1;
    int numarcif = 1;
    if ( x < 0 ) {
        numar.semn = 1;
        x = -x;
    }
    while ( x >= putere ) {
        putere *= 10;
        numarcif++;
    }
    numarcif--;
    numar.v[0] = numarcif;
    while ( numarcif ) {
        numar.v[numarcif--] = x % 10;
        x /= 10;
    }
}

// Adauga cifra x la stanga numarului
void addlBIG (BIG_INT& numar , int x) {
    for ( int i = 1; i <= numar.v[0]; i++ ) numar.v[i + 1] = numar.v[i];
    numar.v[1] = x;
    numar.v[0]++;
}
// Adauga cifra x la dreapta numarului
void addrBIG (BIG_INT& numar , int x) {
    if ( numar.v[0] == 0 && x == 0 ) return;
    numar.v[0]++;
    numar.v[numar.v[0]] = x;
}

// Face ca toate valorile unui BIG_INT sa fie 0
void clearBIG (BIG_INT& numar) {
    for ( int i = 0; i < 100; i++ ) numar.v[i] = 0;
    numar.semn = 0;
    numar.operatie = 0;
}

//Compara doua BIG_INT
bool maimareBIG (BIG_INT numar1 , BIG_INT numar2) {
    if ( numar1.v[0] > numar2.v[0] ) return 1;
    if ( numar2.v[0] > numar1.v[0] ) return 0;
    for ( int i = 1; i <= numar1.v[0]; i++ ) {
        if ( numar1.v[i] == numar2.v[i] ) continue;
        return ( numar1.v[i] > numar2.v[i] );
    }
    return 0;
}


//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de BIG_INT
void citireBIG (char sir[] , BIG_INT vector[] , int& lungime) {
    int pozitie = 1;
    bool operatie = 0; //doi operatori unul dupa altul
    for ( int i = 0; i <= strlen (sir); i++ ) {
        if ( sir[i] >= 48 && sir[i] <= 57 ) { //cifra
            operatie = 0;
            if ( vector[pozitie].operatie ) pozitie++;
            addrBIG (vector[pozitie] , ( (int)sir[i] - '0' ));
        }
        else if ( sir[i] == 43 ) {
            if ( operatie == 1 ) {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 1;// +
        }
        else if ( sir[i] == 45 ) {
            if ( operatie == 1 ) {
                if ( vector[pozitie + 1].semn == 1 ) {
                    fout << "EROARE DE SINTAXA";
                    break;
                }
                vector[pozitie + 1].semn = 1;
            }
            else {
                operatie = 1;
                pozitie++;
                vector[pozitie].operatie = 2; // -
            }
        }
        else if ( sir[i] == 42 || sir[i] == 120 ) {
            if ( operatie == 1 ) {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 3; // * x
        }
        else if ( sir[i] == 47 || sir[i] == 58 ) {
            if ( operatie == 1 ) {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 4; // / :
        }
        else if ( sir[i] == 40 ) {
            pozitie++;
            vector[pozitie].operatie = 6; // (
        }
        else if ( sir[i] == 41 ) {
            pozitie++;
            vector[pozitie].operatie = 7; // )
        }
    }
    lungime = pozitie;
}
//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de REAL
void citireREAL (char sir[] , REAL vector[] , int& lungime) {

    int pozitie = 1;
    bool operatie = 0; //doi operatori unul dupa altul
    for ( int i = 0; i <= strlen (sir); i++ ) {
        if ( sir[i] >= 48 && sir[i] <= 57 ) { //cifra
            operatie = 0;
            if ( vector[pozitie].operatie ) pozitie++;
            vector[pozitie].n = vector[pozitie].n * 10 + ( (int)sir[i] - '0' ); //adaug cifra la dreapta numarului
        }
        else if ( sir[i] == 43 ) {
            if ( operatie == 1 ) {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 1;// +
        }
        else if ( sir[i] == 45 ) {
            if ( operatie == 1 ) {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 2; // -

        }
        else if ( sir[i] == 42 || sir[i] == 120 ) {
            if ( operatie == 1 ) {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 3; // * x
        }
        else if ( sir[i] == 47 || sir[i] == 58 ) {
            if ( operatie == 1 ) {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 4; // / :
        }
        else if ( sir[i] == 40 ) {
            pozitie++;
            vector[pozitie].operatie = 6; // (
        }
        else if ( sir[i] == 41 ) {
            pozitie++;
            vector[pozitie].operatie = 7; // )
        }
    }
    lungime = pozitie;
}

// Afiseaza un BIG_INT in cifre
void afisareBIG (BIG_INT numar) {
    if ( numar.operatie ) {
        fout << SirOperatori[numar.operatie];
    }
    else {
        if ( numar.v[0] == 0 ) {
            fout << '0';
            return;
        }
        if ( numar.semn ) fout << '-';
        for ( int i = 1; i <= numar.v[0]; i++ ) {
            fout << numar.v[i];
        }
    }
}

//Afiseaza un numar REAL
void afisareREAL (REAL x) {
    if ( x.operatie ) fout << SirOperatori[x.operatie];
    else fout << setprecision (15) << x.n;
}

//Afiseaza un BIG_INT in litere (se apeleaza astfel: afisareROBIG (numar, 1 , numar.v[0]) )
void afisareROBIG (BIG_INT numar , int poz , int pas) {
    if ( numar.operatie ) {
        if ( numar.operatie == 1 ) fout << "plus ";
        else if ( numar.operatie == 2 ) fout << "minus ";
        else if ( numar.operatie == 3 ) fout << "ori ";
        else if ( numar.operatie == 4 ) fout << "impartit la ";
        else if ( numar.operatie == 5 ) fout << "egal ";
        return;
    }
    if ( numar.v[0] == 0 ) {
        fout << "zero ";
        return;
    }
    if ( numar.semn ) fout << "minus ";
    if ( pas == 1 ) {                                   //pozitia unitatilor
        if ( numar.v[poz] ) fout << SirCifreMari[numar.v[poz] - 1] << ' ';
    }
    else if ( pas == 2 ) {                              //pozitia zecilor
        if ( numar.v[poz] == 0 ) {
            afisareROBIG (numar , poz + 1 , 1);
        }
        else if ( numar.v[poz] == 1 ) {                 //10-19
            fout << SirCifreMari[numar.v[poz + 1] + 9] << ' ';
        }
        else {                                          //20-99
            fout << SirCifreMari[numar.v[poz] + 17] << ' ';
            if ( numar.v[poz + 1] ) fout << "si " << SirCifreMari[numar.v[poz + 1] - 1] << ' ';
        }
    }
    else if ( pas == 3 ) {                              //pozitia sutelor
        if ( numar.v[poz] == 0 ) {
            afisareROBIG (numar , poz + 1 , 2);
        }
        else if ( numar.v[poz] == 1 ) {                 //100-199
            fout << SirCifreMari[27] << ' ';
            afisareROBIG (numar , poz + 1 , 2);
        }
        else {                                          //200-999
            if ( numar.v[poz] == 2 ) fout << "doua ";
            else fout << SirCifreMari[numar.v[poz] - 1] << ' ';
            fout << SirCifreMari[28] << ' ';
            afisareROBIG (numar , poz + 1 , 2);
        }
    }
    else if ( ( pas - 1 ) % 3 == 0 ) {                  //unitate
        if ( numar.v[poz] == 0 ) {
            afisareROBIG (numar , poz + 1 , pas - 1);
        }
        else if ( numar.v[poz] == 1 ) {
            fout << SirCifreMari[pas / 3 * 2 + 27] << ' ';
            afisareROBIG (numar , poz + 1 , pas - 1);
        }
        else {
            if ( numar.v[poz] == 2 ) {
                fout << "doua " << SirCifreMari[pas / 3 + 28] << ' ';
            }
            else if ( numar.v[poz] ) {
                fout << SirCifreMari[numar.v[poz] - 1] << ' ';
                fout << SirCifreMari[pas / 3 * 2 + 28] << ' ';
            }
            afisareROBIG (numar , poz + 1 , pas - 1);
        }
    }
    else if ( ( pas - 2 ) % 3 == 0 ) {                  //zeci
        if ( numar.v[poz] == 0 ) {
            afisareROBIG (numar , poz + 1 , pas - 1);
        }
        else if ( numar.v[poz] == 1 ) {
            afisareROBIG (numar , poz , 2);
            if ( numar.v[poz] ) {
                fout << ' ' << SirCifreMari[pas / 3 * 2 + 28] << ' ';
            }
            afisareROBIG (numar , poz + 2 , pas - 2);
        }
        else {
            afisareROBIG (numar , poz , 2);
            if ( numar.v[poz] ) {
                fout << "de " << SirCifreMari[pas / 3 * 2 + 28] << ' ';
            }
            afisareROBIG (numar , poz + 2 , pas - 2);
        }
    }
    else {                                              //sute
        if ( numar.v[poz] == 0 ) {
            afisareROBIG (numar , poz + 1 , pas - 1);
        }
        else if ( numar.v[poz] == 1 ) {
            afisareROBIG (numar , poz , 3);
            if ( numar.v[poz] ) {
                fout << "de " << SirCifreMari[pas / 3 * 2 + 26] << ' ';
            }
            afisareROBIG (numar , poz + 3 , pas - 3);
        }
        else {
            afisareROBIG (numar , poz , 3);
            if ( numar.v[poz] ) {
                fout << "de " << SirCifreMari[pas / 3 * 2 + 26] << ' ';
            }
            afisareROBIG (numar , poz + 3 , pas - 3);
        }
    }
}
void memorareROBIG (BIG_INT numar , int poz , int pas,char c[]) {
    if ( numar.operatie ) {
        if ( numar.operatie == 1 ) strcpy (c + strlen (c) ,"plus ");
        else if ( numar.operatie == 2 ) strcpy (c + strlen (c) ,"minus ");
        else if ( numar.operatie == 3 ) strcpy (c + strlen (c) , "ori ");
        else if ( numar.operatie == 4 ) strcpy (c + strlen (c) ,"impartit la ");
        else if ( numar.operatie == 5 ) strcpy (c + strlen (c) ,"egal ");
        return;
    }
    if ( numar.v[0] == 0 ) {
        strcpy (c + strlen (c) ,"zero ");
        return;
    }
    if ( numar.semn ) strcpy (c + strlen (c) ,"minus ");
    if ( pas == 1 ) {                                   //pozitia unitatilor
        if ( numar.v[poz] ) {
            //fout << SirCifreMari[numar.v[poz] - 1] << ' ';
            strcpy (c + strlen (c) , SirCifreMari[numar.v[poz] - 1]);
            strcpy (c + strlen (c) ," ");
        }
    }
    else if ( pas == 2 ) {                              //pozitia zecilor
        if ( numar.v[poz] == 0 ) {
            memorareROBIG (numar , poz + 1 , 1,c);
        }
        else if ( numar.v[poz] == 1 ) {                 //10-19
            //fout << SirCifreMari[numar.v[poz + 1] + 9] << ' ';
            strcpy (c + strlen (c) , SirCifreMari[numar.v[poz + 1] + 9]);
            strcpy (c + strlen (c) ," ");
        }
        else {                                          //20-99
            //fout << SirCifreMari[numar.v[poz] + 17] << ' ';
            strcpy (c + strlen (c) , SirCifreMari[numar.v[poz] + 17]);
            strcpy (c + strlen (c) , " ");
            if ( numar.v[poz + 1] ) {
                //fout << "si " << SirCifreMari[numar.v[poz + 1] - 1] << ' ';
                strcpy (c + strlen (c) ,"si ");
                strcpy (c + strlen (c) , SirCifreMari[numar.v[poz + 1] - 1]);
                strcpy (c + strlen (c) ," ");
            }
        }
    }
    else if ( pas == 3 ) {                              //pozitia sutelor
        if ( numar.v[poz] == 0 ) {
            memorareROBIG (numar , poz + 1 , 2,c);
        }
        else if ( numar.v[poz] == 1 ) {                 //100-199
            //fout << SirCifreMari[27] << ' ';
            strcpy (c + strlen (c) , SirCifreMari[27]);
            strcpy (c + strlen (c) ," ");
            memorareROBIG (numar , poz + 1 , 2,c);
        }
        else {                                          //200-999
            if ( numar.v[poz] == 2 ) {
                //fout << "doua ";
                strcpy (c + strlen (c) ,"doua ");
            }
            else {
                fout << SirCifreMari[numar.v[poz] - 1] << ' ';
                strcpy (c + strlen (c) , SirCifreMari[numar.v[poz] - 1]);
                strcpy (c + strlen (c) ," ");
            }
            //fout << SirCifreMari[28] << ' ';
            strcpy (c + strlen (c) , SirCifreMari[28]);
            strcpy (c + strlen (c) ," ");
            memorareROBIG (numar , poz + 1 , 2,c);
        }
    }
    else if ( ( pas - 1 ) % 3 == 0 ) {                  //unitate
        if ( numar.v[poz] == 0 ) {
            memorareROBIG (numar , poz + 1 , pas - 1,c);
        }
        else if ( numar.v[poz] == 1 ) {
            //fout << SirCifreMari[pas / 3 * 2 + 27] << ' ';
            strcpy (c + strlen (c) , SirCifreMari[pas / 3 * 2 + 27]);
            strcpy (c + strlen (c) ," ");
            memorareROBIG (numar , poz + 1 , pas - 1,c);
        }
        else {
            if ( numar.v[poz] == 2 ) {
                //fout << "doua " << SirCifreMari[pas / 3 + 28] << ' ';
                strcpy (c + strlen (c) ,"doua ");
                strcpy (c + strlen (c) ,SirCifreMari[pas / 3 + 28]);
                strcpy (c + strlen (c) ," ");
            }
            else if ( numar.v[poz] ) {
                //fout << SirCifreMari[numar.v[poz] - 1] << ' ';
               //fout << SirCifreMari[pas / 3 * 2 + 28] << ' ';
                strcpy (c + strlen (c) , SirCifreMari[numar.v[poz] - 1]);
                strcpy (c + strlen (c) ," ");
                strcpy (c + strlen (c) , SirCifreMari[pas / 3 * 2 + 28]);
                strcpy (c + strlen (c) ," ");
            }
            memorareROBIG (numar , poz + 1 , pas - 1,c);
        }
    }
    else if ( ( pas - 2 ) % 3 == 0 ) {                  //zeci
        if ( numar.v[poz] == 0 ) {
            memorareROBIG (numar , poz + 1 , pas - 1,c);
        }
        else if ( numar.v[poz] == 1 ) {
            memorareROBIG (numar , poz , 2,c);
            if ( numar.v[poz] ) {
                //fout << ' ' << SirCifreMari[pas / 3 * 2 + 28] << ' ';
                strcpy (c + strlen (c) ," ");
                strcpy (c + strlen (c) , SirCifreMari[pas / 3 * 2 + 28]);
                strcpy (c + strlen (c) ," ");
            }
            memorareROBIG (numar , poz + 2 , pas - 2,c);
        }
        else {
            memorareROBIG (numar , poz , 2,c);
            if ( numar.v[poz] ) {
                //fout << "de " << SirCifreMari[pas / 3 * 2 + 28] << ' ';
                strcpy (c + strlen (c) ,"de ");
                strcpy (c + strlen (c) , SirCifreMari[pas / 3 * 2 + 28]);
                strcpy (c + strlen (c) ," ");
            }
            memorareROBIG (numar , poz + 2 , pas - 2,c);
        }
    }
    else {                                              //sute
        if ( numar.v[poz] == 0 ) {
            memorareROBIG (numar , poz + 1 , pas - 1,c);
        }
        else if ( numar.v[poz] == 1 ) {
            memorareROBIG (numar , poz , 3,c);
            if ( numar.v[poz] ) {
                //fout << "de " << SirCifreMari[pas / 3 * 2 + 26] << ' ';
                strcpy (c + strlen (c) ,"de ");
                strcpy (c + strlen (c) , SirCifreMari[pas / 3 * 2 + 26]);
                strcpy (c + strlen (c) ," ");
            }
            memorareROBIG (numar , poz + 3 , pas - 3,c);
        }
        else {
            memorareROBIG (numar , poz , 3,c);
            if ( numar.v[poz] ) {
                //fout << "de " << SirCifreMari[pas / 3 * 2 + 26] << ' ';
                strcpy (c + strlen (c) ,"de ");
                strcpy (c + strlen (c) , SirCifreMari[pas / 3 * 2 + 26]);
                strcpy (c + strlen (c) ," ");
            }
            memorareROBIG (numar , poz + 3 , pas - 3,c);
        }
    }
}

//Afiseaza un REAL in litere
void afisareROREAL (REAL x) {
    double intreg , fractionar;
    BIG_INT intregB , fractionarB;
    int precizie = 1;

    fractionar = modf (x.n , &intreg);

    fractionar *= 10;
    while ( (int)fractionar > 0 && precizie < 10 ) {
        addrBIG (fractionarB , (int)fractionar);
        fractionar -= (int)fractionar;
        fractionar *= 10;
        precizie++;
    }

    conversie (intreg , intregB);
    afisareROBIG (intregB , 1 , intregB.v[0]);
    if ( fractionarB.v[0] ) {
        fout << "virgula ";
        afisareROBIG (fractionarB , 1 , fractionarB.v[0]);
    }
}
void memorareROREAL (REAL x,char c[]) {
    double intreg , fractionar;
    BIG_INT intregB , fractionarB;
    int precizie = 1;

    fractionar = modf (x.n , &intreg);

    fractionar *= 10;
    while ( (int)fractionar > 0 && precizie < 10 ) {
        addrBIG (fractionarB , (int)fractionar);
        fractionar -= (int)fractionar;
        fractionar *= 10;
        precizie++;
    }
    char auxiliar[150];
    for ( int i = 0; i <= 149; i++ ) auxiliar[i] = NULL;
    conversie (intreg , intregB);
    memorareROBIG (intregB , 1 , intregB.v[0],auxiliar);
    strcpy (c + strlen (c) , auxiliar);
    if ( fractionarB.v[0] ) {
        char auxiliar2[150];
        for ( int i = 0; i <= 149; i++ ) auxiliar2[i] = NULL;
        //fout << "virgula ";
        strcpy (c + strlen (c) , "virgula ");
        memorareROBIG (fractionarB , 1 , fractionarB.v[0],auxiliar2);
        strcpy (c + strlen (c) , auxiliar2);
    }
}

//Traduce un vector de BIG_INT in limba romana (vecotrul trebuie sa aiba forma prefixata)
void afisareROsirBIG (BIG_INT vector[] , int lungime) {
    int ultimaoperatie = 5 , penultimaoperatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- ) {
        if ( vector[i].operatie ) {
            if ( vector[i].operatie == 1 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 1;
                if ( ultimaoperatie == penultimaoperatie );
                else
                    fout << "suma dintre ";
            }
            else if ( vector[i].operatie == 2 ) {

                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 2;
                if ( ultimaoperatie == penultimaoperatie );
                else
                    fout << "diferenta dintre ";
            }
            else if ( vector[i].operatie == 3 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 3;
                if ( ultimaoperatie == penultimaoperatie );
                else
                    fout << "produsul dintre ";
            }
            else if ( vector[i].operatie == 4 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 4;
                impartire = 1;
            }
        }
        else {                                                                      //numar
            if ( i != 1 ) {
                afisareROBIG (vector[i] , 1 , vector[i].v[0]);
                if ( impartire == 0 ) {
                    if ( vector[i - 1].operatie != ultimaoperatie ) fout << "si ";
                    else fout << ',';
                }
            }
            else afisareROBIG (vector[i] , 1 , vector[i].v[0]);
            if ( impartire ) {
                fout << "impartit la ";
            }
            impartire = 0;
        }
    }
}
void memorareROsirBIG (BIG_INT vector[] , int lungime,char c[]) {
    int ultimaoperatie = 5 , penultimaoperatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- ) {
        if ( vector[i].operatie ) {
            if ( vector[i].operatie == 1 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 1;
                if ( ultimaoperatie == penultimaoperatie );
                else {
                    //fout << "suma dintre ";
                    strcpy (c + strlen (c) ,"suma dintre " );
                }
            }
            else if ( vector[i].operatie == 2 ) {

                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 2;
                if ( ultimaoperatie == penultimaoperatie );
                else {
                    //fout << "diferenta dintre ";
                    strcpy (c + strlen (c) ,"diferenta dintre " );
                }
            }
            else if ( vector[i].operatie == 3 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 3;
                if ( ultimaoperatie == penultimaoperatie );
                else {
                    //fout << "produsul dintre ";
                    strcpy (c + strlen (c) ,"produsul dintre ");
                }
            }
            else if ( vector[i].operatie == 4 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 4;
                impartire = 1;
            }
        }
        else {                                                                      //numar
            if ( i != 1 ) {
                char aux[200];
                for ( int i = 0; i <= 199; i++ ) aux[i] = NULL;
                memorareROBIG (vector[i] , 1 , vector[i].v[0],aux);
                strcpy (c + strlen (c) ,aux );
                if ( impartire == 0 ) {
                    if ( vector[i - 1].operatie != ultimaoperatie ) {
                        //fout << "si ";
                        strcpy (c + strlen (c) ,"si ");
                    }
                    else {
                        //fout << ',';
                        strcpy (c + strlen (c) ,",");
                    }
                }
            }
            else {
                char aux[200];
                for ( int i = 0; i <= 199; i++ ) aux[i] = NULL;
                memorareROBIG (vector[i] , 1 , vector[i].v[0] , aux);
                strcpy (c + strlen (c) , aux);
            }
            if ( impartire ) {
                //fout << "impartit la ";
                strcpy (c + strlen (c) , "impartit la ");
            }
            impartire = 0;
        }
    }
}
//Traduce un vector de REAL in limba romana (vecotrul trebuie sa aiba forma prefixata)
void afisareROsirREAL (REAL vector[] , int lungime) {
    int ultimaoperatie = 5 , penultimaoperatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- ) {
        if ( vector[i].operatie ) {
            if ( vector[i].operatie == 1 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 1;
                if ( ultimaoperatie == penultimaoperatie );
                else
                    fout << "suma dintre ";
            }
            else if ( vector[i].operatie == 2 ) {

                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 2;
                if ( ultimaoperatie == penultimaoperatie );
                else
                    fout << "diferenta dintre ";
            }
            else if ( vector[i].operatie == 3 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 3;
                if ( ultimaoperatie == penultimaoperatie );
                else
                    fout << "produsul dintre ";
            }
            else if ( vector[i].operatie == 4 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 4;
                impartire = 1;
            }
        }
        else {                                                                      //numar
            if ( i != 1 ) {
                afisareROREAL (vector[i]);
                if ( impartire == 0 ) {
                    if ( vector[i - 1].operatie != ultimaoperatie ) fout << "si ";
                    else fout << ',';
                }
            }
            else afisareROREAL (vector[i]);
            if ( impartire ) {
                fout << "impartit la ";
            }
            impartire = 0;
        }
    }
}
void memorareROsirREAL (REAL vector[] , int lungime , char c[]) {
    int ultimaoperatie = 5 , penultimaoperatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- ) {
        if ( vector[i].operatie ) {
            if ( vector[i].operatie == 1 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 1;
                if ( ultimaoperatie == penultimaoperatie );
                else {
                    strcpy (c + strlen (c) , "suma dintre ");
                }
            }
            else if ( vector[i].operatie == 2 ) {

                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 2;
                if ( ultimaoperatie == penultimaoperatie );
                else {
                    strcpy (c + strlen (c) , "diferenta dintre ");
                }
            }
            else if ( vector[i].operatie == 3 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 3;
                if ( ultimaoperatie == penultimaoperatie );
                else {
                    strcpy (c + strlen (c) , "produsul dintre ");
                }
            }
            else if ( vector[i].operatie == 4 ) {
                penultimaoperatie = ultimaoperatie;
                ultimaoperatie = 4;
                impartire = 1;
            }
        }
        else {                                                                      //numar
            if ( i != 1 ) {
                char auxiliar[150];
                for ( int i = 0; i <= 149; i++ ) auxiliar[i] = NULL;
                memorareROREAL (vector[i],auxiliar);
                strcpy (c + strlen (c) , auxiliar);
                if ( impartire == 0 ) {
                    if ( vector[i - 1].operatie != ultimaoperatie ) strcpy (c + strlen (c) , "si ");
                    else strcpy (c + strlen (c) , ",");
                }
            }
            else {
                char auxiliar[150];
                for ( int i = 0; i <= 149; i++ ) auxiliar[i] = NULL;
                memorareROREAL (vector[i] , auxiliar);
                strcpy (c + strlen (c) , auxiliar);
            }
            if ( impartire ) {
                strcpy (c + strlen (c) , "impartit la ");
            }
            impartire = 0;
        }
    }
}


// Calculeaza suma a doua BIG_INT
void adunareBIG (BIG_INT& numar1 , BIG_INT& numar2 , BIG_INT& rezultat) {
    if ( numar1.semn > numar2.semn ) {                          //(-a) + b = b - a
        numar1.semn = 0;
        scadereBIG (numar2 , numar1 , rezultat);
        numar1.semn = 1;
        return;
    }
    else if ( numar1.semn < numar2.semn ) {                     //a + (-b) = a - b
        numar2.semn = 0;
        scadereBIG (numar1 , numar2 , rezultat);
        numar2.semn = 1;
        return;
    }
    else if ( numar1.semn ) rezultat.semn = 1;                  // (-a) + (-b) = -(a + b)
    else rezultat.semn = 0;                                     // a + b = a + b
    int lungime , carry = 0;
    if ( numar1.v[0] >= numar2.v[0] ) {
        lungime = numar1.v[0] - numar2.v[0];
        for ( int i = numar2.v[0]; i >= 1; i-- ) {
            rezultat.v[i + lungime] = numar1.v[i + lungime] + numar2.v[i] + carry;
            carry = 0;
            if ( rezultat.v[i + lungime] > 9 ) {
                rezultat.v[i + lungime] %= 10;
                carry = 1;
            }
        }
        for ( int i = lungime; i >= 1; i-- ) {
            rezultat.v[i] = numar1.v[i] + carry;
            carry = 0;
            if ( rezultat.v[i] > 9 ) {
                rezultat.v[i] %= 10;
                carry = 1;
            }
        }
        if ( carry ) {
            for ( int i = numar1.v[0] + 1; i >= 1; i-- ) rezultat.v[i + 1] = rezultat.v[i];
            rezultat.v[1] = 1;
            rezultat.v[0] = numar1.v[0] + 1;
        }
        else rezultat.v[0] = numar1.v[0];
    }
    else adunareBIG (numar2 , numar1 , rezultat);
}

// Calculeaza diferenta a doua BIG_INT
void scadereBIG (BIG_INT& numar1 , BIG_INT& numar2 , BIG_INT& rezultat) {
    if ( numar1.semn < numar2.semn ) {               // a - (-b) = a + b
        numar2.semn = 0;
        adunareBIG (numar1 , numar2 , rezultat);
        numar2.semn = 1;
        return;
    }
    else if ( numar1.semn > numar2.semn ) {         // (-a) - b = -(a + b)
        numar1.semn = 0;
        adunareBIG (numar1 , numar2 , rezultat);
        numar1.semn = 1;
        rezultat.semn = 1;
        return;
    }
    else if ( numar1.semn ) {                     // (-a) - (-b) = b - a
        numar2.semn = 0;
        numar1.semn = 0;
        scadereBIG (numar2 , numar1 , rezultat);
        numar2.semn = 1;
        numar1.semn = 1;
        return;
    }                                            // a - b = a - b
    if ( numar2.v[0] > numar1.v[0] ) scaderesecundaraBIG (numar2 , numar1 , rezultat , 1); //b>a
    else if ( numar1.v[0] == numar2.v[0] ) {
        int ok = 0;
        for ( int i = 1; i <= numar1.v[0]; i++ ) {
            if ( numar1.v[i] > numar2.v[i] ) {
                scaderesecundaraBIG (numar1 , numar2 , rezultat , 0);                           //a>b
                break;
            }
            else if ( numar2.v[i] > numar1.v[i] ) {
                scaderesecundaraBIG (numar2 , numar1 , rezultat , 1);                   //b>a
                break;
            }
        }
    }
    else scaderesecundaraBIG (numar1 , numar2 , rezultat , 0);                                //a>b
}
// Functie secundara pentru scadere, calculeaza propiu-zis diferenta a doua numere pozitive primul avand mai multe cifre
void scaderesecundaraBIG (BIG_INT& numar1 , BIG_INT& numar2 , BIG_INT& rezultat , bool semn) {
    int lungime , carry = 0 , contorzero = 0;
    lungime = numar1.v[0] - numar2.v[0];
    for ( int i = numar2.v[0]; i >= 1; i-- ) {
        rezultat.v[i + lungime] = numar1.v[i + lungime] - numar2.v[i] - carry;
        carry = 0;
        if ( rezultat.v[i + lungime] < 0 ) {
            rezultat.v[i + lungime] += 10;
            carry = 1;
        }
    }
    for ( int i = lungime; i >= 1; i-- ) {
        rezultat.v[i] = numar1.v[i] - carry;
        carry = 0;
        if ( rezultat.v[i] < 0 ) {
            rezultat.v[i] += 10;
            carry = 1;
        }
    }
    for ( int i = 1; i <= numar1.v[0]; i++ ) {
        if ( rezultat.v[i] ) break;
        contorzero++;
    }
    rezultat.v[0] = numar1.v[0] - contorzero;
    for ( int i = 1; i <= numar1.v[0]; i++ ) rezultat.v[i] = rezultat.v[i + contorzero];
    rezultat.semn = semn;
}

//Inumlteste doua BIG_INT
void inmultireBIG (BIG_INT& numar1 , BIG_INT& numar2 , BIG_INT& rezultat) {
    BIG_INT rezultatauxiliar;
    for ( int i = 1; i <= numar2.v[0]; i++ ) {
        BIG_INT aux;
        inmultiresBIG (numar1 , numar2.v[( numar2.v[0] - i + 1 )] , aux , i - 1);
        adunareBIG (rezultat , aux , rezultatauxiliar);
        rezultat = rezultatauxiliar;
    }
    if ( numar1.semn != numar2.semn ) rezultat.semn = 1; // a * (-b) || (-a) * b
    else rezultat.semn = 0;                             // a * b || (-a) * (-b)
}
//Functie secundara pentru inmultire, calculeaza produsul dintre un BIG_INT si o cifra si adauga un numar specificat de zerouri
void inmultiresBIG (BIG_INT& numar1 , int cifra , BIG_INT& rezultat , int zero) {
    if ( cifra < 0 ) {               // a * -x = -ax
        cifra = -cifra;
        rezultat.semn = 1;
    }
    int carry = 0;
    for ( int i = numar1.v[0]; i >= 1; i-- ) {
        rezultat.v[i] = numar1.v[i] * cifra + carry;
        carry = 0;
        if ( rezultat.v[i] > 9 ) {
            carry = rezultat.v[i] / 10;
            rezultat.v[i] %= 10;
        }
    }
    if ( carry ) {
        for ( int i = numar1.v[0] + 1; i >= 1; i-- ) rezultat.v[i + 1] = rezultat.v[i];
        rezultat.v[1] = carry;
        rezultat.v[0] = numar1.v[0] + 1;
    }
    else rezultat.v[0] = numar1.v[0];
    for ( int i = numar1.v[0] + 2; i <= numar1.v[0] + 1 + zero; i++ ) rezultat.v[i] = 0;
    rezultat.v[0] += zero;
}

//Calculeaza catul impartirii naturale a doua BIG_INT
void impartireBIG (BIG_INT deimpartit , BIG_INT impartitor , BIG_INT& cat) {
    if ( impartitor.v[0] == 0 ) {
        fout << "Impartire la 0?";
        return;
    }
    BIG_INT suma , catauxiliar , adunarecat;
    int putere = 1 , preamare = 1;
    adunarecat.v[1] = 1;
    while ( putere > 0 ) {
        BIG_INT auxiliarsuma;
        adunareBIG (suma , impartitor , auxiliarsuma);
        if ( maimareBIG (auxiliarsuma , deimpartit) ) {
            putere--;
            impartitor.v[0]--;
            preamare = 0;
        }
        else {
            suma = auxiliarsuma;
            BIG_INT auxiliarcat;
            adunarecat.v[0] = putere;
            adunareBIG (catauxiliar , adunarecat , auxiliarcat);
            catauxiliar = auxiliarcat;
            if ( preamare ) {
                putere++;
                impartitor.v[0]++;
            }
        }
    }
    cat = catauxiliar;
}

//Imparte un BIG_INT la o cifra  (nefolosit)
void impartiresBIG (BIG_INT& nr1 , int x , BIG_INT& nr2) {
    int div = 0 , poz = 1;
    if ( nr1.semn == 0 && x < 0 ) nr2.semn = 1;
    else if ( nr1.semn == 1 && x > 0 ) nr2.semn = 1;
    if ( x < 0 ) x = -x;
    for ( int i = 1; i <= nr1.v[0]; i++ ) {
        div *= 10;
        div += nr1.v[i];
        if ( div < x ) {
            poz++;
            continue;
        }
        else {
            int rez = div / x;
            nr2.v[poz++] = rez;
            div = div % x;
        }
    }
    nr2.v[0] = poz - 1;
    if ( nr2.v[1] == 0 ) {
        for ( int i = 1; i <= nr2.v[0]; i++ ) nr2.v[i] = nr2.v[i + 1];
        nr2.v[0]--;
    }
}


//Calculeaza prioritate operatorilor pentru conversia postfixata
int prioBIG (BIG_INT Operator) {
    if ( Operator.operatie == 1 || Operator.operatie == 2 ) return 2; // + || -
    if ( Operator.operatie == 3 || Operator.operatie == 4 ) return 3; // * || /
    if ( Operator.operatie == 6 || Operator.operatie == 7 ) return 4; // ( || )
    return 0;
}
//Calculeaza prioritate operatorilor pentru conversia postfixata
int prioREAL (REAL nr) {
    if ( nr.operatie == 1 || nr.operatie == 2 ) return 2; // + || -
    if ( nr.operatie == 3 || nr.operatie == 4 ) return 3; // * || /
    if ( nr.operatie == 6 || nr.operatie == 7 ) return 4; // ( || )
    return 0;
}
//Transforma vectorul 1 de BIG_INT cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
void infixtopostfixBIG (BIG_INT vector1[] , BIG_INT vector2[] , int& lungime) {
    BIG_INT Stiva[150] , auxiliar;
    int InceputCoada1 = 1 , SfarsitCoada1 = lungime + 1 , InceputCoada2 = 1 , SfarsitCoada2 = 1 , VarfStiva = 1;
    while ( InceputCoada1 < SfarsitCoada1 ) {
        auxiliar = vector1[InceputCoada1];  InceputCoada1++;
        if ( auxiliar.operatie == 0 ) {
            vector2[SfarsitCoada2++] = auxiliar;
        }
        else {
            if ( auxiliar.operatie == 7 ) {
                while ( Stiva[VarfStiva].operatie != 6 ) {
                    vector2[SfarsitCoada2] = Stiva[VarfStiva];
                    SfarsitCoada2++; VarfStiva--;
                }
                VarfStiva--;
                lungime -= 2;
            }
            else {
                while ( VarfStiva > 1 && Stiva[VarfStiva].operatie != 6 && ( prioBIG (Stiva[VarfStiva]) >= prioBIG (auxiliar) ) ) {
                    vector2[SfarsitCoada2++] = Stiva[VarfStiva];
                    VarfStiva--;
                }
                VarfStiva++;
                Stiva[VarfStiva] = auxiliar;
            }
        }
    }
    while ( VarfStiva > 1 ) {
        vector2[SfarsitCoada2++] = Stiva[VarfStiva];
        VarfStiva--;
    }
}
//Transforma vectorul 1 de REAL cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
void infixtopostfixREAL (REAL vector1[] , REAL vector2[] , int& lungime) {
    REAL Stiva[150] , auxiliar;
    int InceputCoada1 = 1 , SfarsitCoada1 = lungime + 1 , InceputCoada2 = 1 , SfarsitCoada2 = 1 , VarfStiva = 1;
    while ( InceputCoada1 < SfarsitCoada1 ) {
        auxiliar = vector1[InceputCoada1];  InceputCoada1++;
        if ( auxiliar.operatie == 0 ) {
            vector2[SfarsitCoada2++] = auxiliar;
        }
        else {
            if ( auxiliar.operatie == 7 ) {
                while ( Stiva[VarfStiva].operatie != 6 ) {
                    vector2[SfarsitCoada2] = Stiva[VarfStiva];
                    SfarsitCoada2++; VarfStiva--;
                }
                VarfStiva--;
                lungime -= 2;
            }
            else {
                while ( VarfStiva > 1 && Stiva[VarfStiva].operatie != 6 && ( prioREAL (Stiva[VarfStiva]) >= prioREAL (auxiliar) ) ) {
                    vector2[SfarsitCoada2++] = Stiva[VarfStiva];
                    VarfStiva--;
                }
                VarfStiva++;
                Stiva[VarfStiva] = auxiliar;
            }
        }
    }
    while ( VarfStiva > 1 ) {
        vector2[SfarsitCoada2++] = Stiva[VarfStiva];
        VarfStiva--;
    }
}

//Evalueaza o expresie postfixata si returneaza rezultatul
BIG_INT evalpostfixBIG (BIG_INT vector[] , int lungime) {
    BIG_INT Stiva[100] , auxiliar , operandstanga , operanddreapta;
    int varfstiva = 0 , inceputcoada = 1;
    while ( inceputcoada <= lungime ) {
        auxiliar = vector[inceputcoada]; inceputcoada++;
        if ( auxiliar.operatie == 0 ) {
            varfstiva++;
            Stiva[varfstiva] = auxiliar;
        }
        else {
            BIG_INT val;
            operanddreapta = Stiva[varfstiva]; varfstiva--;
            operandstanga = Stiva[varfstiva]; varfstiva--;
            if ( auxiliar.operatie == 1 ) adunareBIG (operandstanga , operanddreapta , val);
            else if ( auxiliar.operatie == 2 ) scadereBIG (operandstanga , operanddreapta , val);
            else if ( auxiliar.operatie == 3 ) inmultireBIG (operandstanga , operanddreapta , val);
            else if ( auxiliar.operatie == 4 ) impartireBIG (operandstanga , operanddreapta , val);
            varfstiva++;
            Stiva[varfstiva] = val;
        }
    }
    return Stiva[1];
}
//Evalueaza o expresie postfixata si returneaza rezultatul
REAL evalpostfixREAL (REAL vector[] , int lungime) {
    REAL Stiva[100] , auxiliar , operandstanga , operanddreapta;
    int varfstiva = 0 , inceputcoada = 1;
    while ( inceputcoada <= lungime ) {
        auxiliar = vector[inceputcoada]; inceputcoada++;
        if ( auxiliar.operatie == 0 ) {
            varfstiva++;
            Stiva[varfstiva] = auxiliar;
        }
        else {
            operanddreapta = Stiva[varfstiva]; varfstiva--;
            operandstanga = Stiva[varfstiva]; varfstiva--;
            varfstiva++;
            if ( auxiliar.operatie == 1 ) Stiva[varfstiva].n = operandstanga.n + operanddreapta.n;
            else if ( auxiliar.operatie == 2 ) Stiva[varfstiva].n = operandstanga.n - operanddreapta.n;
            else if ( auxiliar.operatie == 3 ) Stiva[varfstiva].n = operandstanga.n * operanddreapta.n;
            else if ( auxiliar.operatie == 4 ) Stiva[varfstiva].n = operandstanga.n / operanddreapta.n;

        }
    }
    return Stiva[1];
}

//Transforma vectorul 1 de BIG_INT cu forma infixata in vectorul 2 cu forma prefixata
void infixtoprefixBIG (BIG_INT vector1[] , BIG_INT vector2[] , int& lungime) {
    BIG_INT Stiva[100];
    for ( int i = 1; i <= lungime; i++ ) {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        else if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
        Stiva[lungime + 1 - i] = vector1[i];
    }
    infixtopostfixBIG (Stiva , vector2 , lungime);
    for ( int i = 1; i <= lungime; i++ ) {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
    }
    for ( int i = 1; i <= lungime; i++ ) {
        vector1[i] = vector1[lungime + 1 - i];
    }
}
//Transforma vectorul 1 de REAL cu forma infixata in vectorul 2 cu forma prefixata
void infixtoprefixREAL (REAL vector1[] , REAL vector2[] , int& lungime) {
    REAL Stiva[100];
    for ( int i = 1; i <= lungime; i++ ) {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        else if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
        Stiva[lungime + 1 - i] = vector1[i];
    }
    infixtopostfixREAL (Stiva , vector2 , lungime);
    for ( int i = 1; i <= lungime; i++ ) {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
    }
    for ( int i = 1; i <= lungime; i++ ) {
        vector1[i] = vector1[lungime + 1 - i];
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* transfLitCif(char *s) // Transforma numarul scris in litere in cifre
{
    int i = 0;
    char line[1000]= {0};
    int numar = 0, temp = 0;
    strcpy(line, s);
    char *q = new char[1000]();
    strcpy(q,line);
    char *savepointer = NULL;
    q = strtok_r(line, "_", &savepointer);
    while (q)
    {
        i = 0;
        ok = 0;
        while (num[i][0] != '_' && num[i][0]!='\0')
        {
            if (strcmp(q, num[i]) == 0)
            {
                ok = 1;
                if (aFostcuvCheie)
                {
                    numar = numar + temp;
                    temp = numCif[i];
                }
                else
                    temp = temp + numCif[i];
            }
            i++;
        }
        aFostcuvCheie = 0;
        if (!ok)
        {
            i = 0;
            while (cuvCheie[i][0] != '_' && cuvCheie[i][0]!='\0')
            {
                if (strcmp(q, cuvCheie[i]) == 0)
                {
                    temp = temp * cuvCheieCif[i];
                    aFostcuvCheie = 1;
                }
                i++;
            }
        }
        q = strtok_r(NULL, "_", &savepointer);
    }
    if (ok && !aFostcuvCheie)numar = numar + temp;
    if (!ok && aFostcuvCheie)numar = numar + temp;
    char* t = new char[1000]();
    int k = 0;
    while(numar)
    {
        t[k++] = numar%10+'0';
        numar/=10;
    }
    for(i=0; i<k/2; i++)
        swap(t[i],t[k-i-1]);
    return t;
}
int eCuvInutil(char s[]) //verifica daca e cuvant inutil
{
    int i = 0;
    while (cuvInutile[i][0]!='\0')
    {
        if (strcmp(s, cuvInutile[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

int eSi(char *s)
{
    if (strcmp(s, "si") == 0)
        return 1;
    return 0;
}

int eAdun(char *s)
{
    int i = 0;
    while (cuvAdun[i][0])
    {
        if (strcmp(s, cuvAdun[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

int eScad(char *s)
{
    int i = 0;
    while (cuvScad[i][0])
    {
        if (strcmp(s, cuvScad[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

int eInm(char *s)
{
    int i = 0;
    while (cuvInm[i][0])
    {
        if (strcmp(s, cuvInm[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

int eImp(char *s)
{
    int i = 0;
    while (cuvImp[i][0])
    {
        if (strcmp(s, cuvImp[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

void introdVec(char *s) // Introduce in vector operatorii si operanzii si introduce ')' la finalul domeniului fiecarui operator
{
    int i;
    char prop[25600]= {0}, cuv[10000]= {0};
    char *savepointer = NULL;
    char *p = strtok_r(s, " ", &savepointer);
    int siFlag = 0, nrp = 0;
    while (p)
    {
        strcpy(cuv, p);
        if (eSi(cuv))
        {
            siFlag = 1;
            p = strtok_r(NULL, " ", &savepointer);
            continue;
        }
        if (eCuvInutil(cuv))
        {
            p = strtok_r(NULL, " ", &savepointer);
            continue;
        }
        else if (eAdun(cuv))
        {
            strcpy(vecCuv[k], "+");
            nrp++;siFlag=0;
        }
        else if (eScad(cuv))
        {
            strcpy(vecCuv[k], "-");
            nrp++;siFlag=0;
        }
        else if (eInm(cuv))
        {
            strcpy(vecCuv[k], "*");
            nrp++;siFlag=0;
        }
        else if (eImp(cuv))
        {
            strcpy(vecCuv[k], "/");
            nrp++;siFlag=0;
        }
        else
        {
            if (cuv[strlen(cuv) - 1] == ',')
            {
                cuv[strlen(cuv) - 1] = '\0';
                auto x = transfLitCif(cuv);
                strcpy(vecCuv[k],x);
                delete[] x;
            }
            else
            {
                auto x = transfLitCif(cuv);
                strcpy(vecCuv[k],x);
                delete[] x;
                if (siFlag)
                {
                    if (nrp)
                    {
                        nrp--;
                        k++;
                        strcpy(vecCuv[k], ")");
                    }
                    siFlag=0;
                }
            }
        }
        k++;
        p = strtok_r(NULL, " ", &savepointer);
    }
    while(nrp)
    {
        nrp--;
        strcpy(vecCuv[k], ")");
        k++;
    }
}
char* evaluator(char vecCuv[5000][10000]) // Calculeaza ecuatia din vectorul de mai sus (PENTRU NUMERE CU VIRGULA)
{
    char s[100][100],buffer[100];
    int v = 0;
    stack<char> op;
    for(int i=0; i<k; i++)
    {
        if(vecCuv[i][0]=='*')
            op.push('*');
        else if(vecCuv[i][0]=='+')
            op.push('+');
        else if(vecCuv[i][0]=='/')
            op.push('/');
        else if(vecCuv[i][0]=='-')
            op.push('-');

        strcpy(s[++v],vecCuv[i]);
        if(s[v][0]==')')
        {
            v--;
            double r = 0;
            char cOP = op.top();
            op.pop();
            if(cOP == '*')
            {
                r=1;
                while(s[v][0]!='*')
                {
                    r=r*(double)(stod(s[v],nullptr));
                    v--;
                }
                sprintf(buffer,"%f",r);
                strcpy(s[v],buffer);
                cout<<s[v]<<endl;
            }
            else if(cOP=='+')
            {
                r=0;
                while(s[v][0]!='+')
                {
                    r=r+(double)(stod(s[v],nullptr));
                    v--;
                }
                sprintf(buffer,"%f",r);
                strcpy(s[v],buffer);
                cout<<s[v]<<endl;
            }
            else if(cOP=='-')
            {
                r=(double)(stod(s[v],nullptr));
                v--;
                r-=(double)(stod(s[v],nullptr));
                v--;
                r*=-1.0;
                sprintf(buffer,"%f",r);
                strcpy(s[v],buffer);
                cout<<s[v]<<endl;
            }
            else if(cOP=='/')
            {
                r=(double)(stod(s[v-1],nullptr));
                v--;
                r/=(double)(stod(s[v+1],nullptr));
                v--;
                sprintf(buffer,"%f",r);
                strcpy(s[v],buffer);
                cout<<s[v]<<endl;
            }
        }
    }
    strcpy(rez,s[1]);
    int ok=0,i;
    for(i=strlen(rez)-1;i>=0 && rez[i]!='.';i--)
            if(rez[i]!='0')
            {
                ok=1;
                break;
            }
            else
                strcpy(rez+i,rez+i+1);
    if(!ok)strcpy(rez+i,rez+i+1);
    return rez;

}



