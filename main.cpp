#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <graphics.h>
#include <winbgim.h>
#define MAX_VEC 5000
using namespace std;

ifstream fin ("CalcRO.in");
ofstream fout ("CalcRO.out");

struct BigInt { //Numere mari
    int v[100] = { 0 };
    bool semn = 0;
    int operatie = 0;
};
BigInt N1,N2,N3,v1[100],v2[100],v3[100];

struct Real {   //Numere reale
    double n = 0;
    int operatie = 0;
};
Real rezultat_real,V1[100],V2[100],V3[100];

char sir_cifre_mari[50][20] = { "unu","doi","trei","patru","cinci","sase","sapte","opt","noua","zece","unsprezece","doisprezece","treisprezece",
                            "paisprezece","cinsprezece","saisprezece","saptisprezece","optisprezece","nouasprezece","douazeci","treizeci",
                            "patruzeci","cincizeci","saizeci","saptezeci","optzeci","nouazeci","o suta","sute","o mie","mii","un milion","milioane",
                            "un miliard","miliarde","un bilion","bilioane","un trilion","trilioane","un cvadrilion","cvadrilioane","un catralion",
                            "catralioane","un cvintilion","cvintilioane","un sextilion","sextilioane" };
char sir_operatori[10] = { '`','+','-' ,'*' ,'/' ,'=' ,'(' ,')' };
char caractere_valide_cifre[20]={'1','2','3','4','5','6','7','8','9','0','+','-','*','x','/',':','(',')',' '};
char caractere_valide_litere[200]={"abcdefghijklmnopqrstuvwxyz _"};

char cuvInutile[100][100] = {"Care", "Ce", "Cat","Cum", "este", "sunt", "rezultatul","egal", "cu", "lui", "?", "dintre"},
                            cuvInm[10][20] = {"inmultire", "inmultirii", "inmultirea", "produs", "produsul", "produsului"},
                                    cuvAdun[10][20] = {"suma", "sumei", "adunare", "adunarea", "adunarii"},
                                            cuvScad[10][20] = {"scadere", "scaderii","scaderea", "diferenta", "diferentei"},
                                                    cuvImp[10][20] = {"impartire", "impartirea"};
char num[100][100] = {"o", "un", "unu", "doi", "doua", "trei", "patru", "cinci", "sase", "sapte", "opt", "noua", "zece",
                      "unsprezece", "doisprezece", "treisprezece", "paisprezece",
                      "cincisprezece", "saisprezece", "saptesprezece", "optsprezece", "nouasprezece", "douazeci",
                      "treizeci", "patruzeci", "cincizeci", "saizeci", "saptezeci", "optzeci", "nouazeci"
                     };
int numCif[100] = {1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50, 60, 70,
                   80, 90
                  };
char cuvCheie[100][100] = {"suta", "sute", "mie", "mii", "milion", "milioane"};
int cuvCheieCif[100] = {100, 100, 1000, 1000, 1000000, 1000000};
int ok, aFostcuvCheie;
char vecCuv[5000][10000],rez[1000];

char* transfLitCif(char *s);
void introdVec(char *s);
char* evaluator(char vecCuv[5000][10000]);

void conversie (long long int x , BigInt& nr);// converteste un int in BigInt
void addlBIG (BigInt& nr , int x);// Adauga cifra x la stanga numarului
void addrBIG (BigInt& nr , int x);// Adauga cifra x la dreapta numarului
void clearBIG (BigInt& nr);// Face ca toate valorile unui BigInt sa fie 0
bool maimareBIG (BigInt numar1 , BigInt numar2);//Compara doua BigInt

void citireBIG (char sir[] , BigInt vector[] , int& lungime);//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de BigInt
void citireREAL (char sir[] , Real vector[] , int& lungime);//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de Real
void afisareBIG (BigInt nr);// Afiseaza un BigInt in cifre
void afisareREAL (Real x);//Afiseaza un numar Real
void afisareROBIG (BigInt numar , int poz , int pas);//Afiseaza un BigInt in litere (se apeleaza astfel: afisareROBIG (numar, 1 , numar.v[0]) )
void memorareROBIG (BigInt numar , int poz , int pas , char sir_caractere[]);//Memoreaza un BigInt intr-un sir de caractere
void afisareROREAL (Real x);//Afiseaza un Real in litere
void memorareROREAL (Real x , char sir_caractere[]);//Memoreaza un Real intr-un sir de caractere
void afisareROsirBIG (BigInt vector[] , int lungime);//Traduce un vector de BigInt in limba romana (vecotrul trebuie sa aiba forma prefixata)
void memorareROsirBIG (BigInt vector[] , int lungime , char sir_caractere[]);//Traduce un vector de BigInt in limba romana si il pune intr-un sir de caractere (vecotrul trebuie sa aiba forma prefixata)
void afisareROsirREAL (Real vector[] , int lungime);//Traduce un vector de Real in limba romana (vecotrul trebuie sa aiba forma prefixata)
void memorareROsirREAL (Real vector[] , int lungime , char sir_caractere[]);//Traduce un vector de Real in limba romana si il pune intr-un sir de caractere (vecotrul trebuie sa aiba forma prefixata)

void adunareBIG (BigInt& nr1 , BigInt& nr2 , BigInt& nr3);// Calculeaza suma a doua BigInt
void scadereBIG (BigInt& numar1 , BigInt& numar2 , BigInt& rezultat);// Calculeaza diferenta a doua BigInt
void scaderesecundaraBIG (BigInt& numar1 , BigInt& numar2 , BigInt& rezultat , bool semn);// Functie secundara pentru scadere, calculeaza propiu-zis diferenta a doua numere pozitive primul avand mai multe cifre
void inmultireBIG (BigInt& numar1 , BigInt& numar2 , BigInt& rezultat);//Inumlteste doua BigInt
void inmultiresBIG (BigInt& numar1 , int cifra , BigInt& rezultat , int zero);//Functie secundara pentru inmultire, calculeaza produsul dintre un BigInt si o cifra si adauga un numar specificat de zerouri
void impartireBIG (BigInt deimpartit , BigInt impartitor , BigInt& cat);//Calculeaza catul impartirii naturale a doua BigInt
void impartiresBIG (BigInt& nr1 , int x , BigInt& nr2);//Imparte un BigInt la o cifra  (nefolosit)

int prioBIG (BigInt Operator);//Calculeaza prioritate operatorilor pentru conversia postfixata
int prioREAL (Real nr);//Calculeaza prioritate operatorilor pentru conversia postfixata
void infixtopostfixBIG (BigInt vector1[] , BigInt vector2[] , int& lungime);//Transforma vectorul 1 de BigInt cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
void infixtopostfixREAL (Real vector1[] , Real vector2[] , int& lungime);//Transforma vectorul 1 de Real cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
BigInt evalpostfixBIG (BigInt vector[] , int lungime);//Evalueaza o expresie postfixata si returneaza rezultatul
Real evalpostfixREAL (Real vector[] , int lungime);//Evalueaza o expresie postfixata si returneaza rezultatul
void infixtoprefixBIG (BigInt vector1[] , BigInt vector2[] , int& lungime);//Transforma vectorul 1 de BigInt cu forma infixata in vectorul 2 cu forma prefixata
void infixtoprefixREAL (Real vector1[] , Real vector2[] , int& lungime);//Afiseaza un Real in litere
void evaluare(char sir_caractere[]);

int pozitie_text_x=300,pozitie_text_y=100;
int eroare;

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

    char caracter,String[MAX_VEC];
    int sfarsit_string=0;
    bool not_escaped=1;
    short x,y;

    while(kbhit())getch();
    while(caracter!=13 || caracter!=27){
        if(caracter==13){       //enter
           settextstyle(1,HORIZ_DIR,2);//enter
            introdVec(String);
            outtextxy(100,500,evaluatorBig(vecCuv)); //pune codul tau aici; sirul de caractere va fi salvat in variabila String[]


            break;
        }
        if(caracter==27){       //escape
            not_escaped=0;
            break;
        }
        caracter=getch();
        if(strchr(caractere_valide_litere,caracter)==0) continue;
        String[sfarsit_string]=caracter;
        String[sfarsit_string+1]=NULL;
        outtextxy(pozitie_text_x,pozitie_text_y,String);
        sfarsit_string++;
    }
    while(1 && not_escaped){
        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920) {
                break;
            }
        }
    }
    eroare=0;
    meniuBig();
}
void meniuLitZec()
{
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    readimagefile("back.jpg",900,800,1020,920);

    char caracter,String[MAX_VEC];
    int sfarsit_string=0;
    bool not_escaped=1;
    short x,y;

    while(kbhit())getch();
    while(caracter!=13 || caracter!=27){
        if(caracter==13){       //enter
            settextstyle(1,HORIZ_DIR,2);
            introdVec(String);
            outtextxy(100,500,evaluatorLit(vecCuv));
		//pune codul tau aici; sirul de caractere va fi salvat in variabila String[]


            break;
        }
        if(caracter==27){       //escape
            not_escaped=0;
            break;
        }
        caracter=getch();
        if(strchr(caractere_valide_litere,caracter)==0) continue;
        String[sfarsit_string]=caracter;
        String[sfarsit_string+1]=NULL;
        outtextxy(pozitie_text_x,pozitie_text_y,String);
        sfarsit_string++;
    }
    while(1 && not_escaped){
        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920) {
                break;
            }
        }
    }
    eroare=0;
    meniuZecim();
}
void meniuCifBig(){
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    readimagefile("back.jpg",900,800,1020,920);

    char caracter,String[MAX_VEC];
    int sfarsit_string=0;
    bool not_escaped=1;
    short x,y;

    while(kbhit())getch();
    while(caracter!=13 || caracter!=27){
        if(caracter==13){       //enter
            evaluare(String);
            settextstyle(1,HORIZ_DIR,2);
            int l=0,ltot=0;
            char sir_auxiliar[MAX_VEC],sir_complet[MAX_VEC];
            for (int i=0;i<=MAX_VEC;i++) sir_auxiliar[i]=NULL;
            for (int i=0;i<=MAX_VEC;i++) sir_complet[i]=NULL;
            citireBIG(String,v1,l);
            ltot=l;
            infixtopostfixBIG(v1,v2,ltot);
            N1=evalpostfixBIG(v2,ltot);
            infixtoprefixBIG(v1,v3,l);
            memorareROsirBIG(v3,l,sir_auxiliar);
            strcpy(sir_complet+strlen(sir_complet),sir_auxiliar);
            for (int i=0;i<=MAX_VEC;i++) sir_auxiliar[i]=NULL;
            strcpy(sir_complet+strlen(sir_complet),"este ");
            memorareROBIG(N1,1,N1.v[0],sir_auxiliar);
            strcpy(sir_complet+strlen(sir_complet),sir_auxiliar);

            // DE EDITAT SIRUL ESTE IN sir_complet
            if(eroare==0) outtextxy(100,500,sir_complet);
            else {
                if (eroare==1) outtextxy(100,500,"EROARE: Impartire la 0");
                else if(eroare) outtextxy(100,500,"EROARE: Sintaxa Gresita");
            }

            for (int i=0;i<=MAX_VEC;i++) sir_auxiliar[i]=NULL;
            for (int i=0;i<=MAX_VEC;i++) sir_complet[i]=NULL;

            break;
        }
        if(caracter==27){       //escape
            not_escaped=0;
            break;
        }
        caracter=getch();
        if(strchr(caractere_valide_cifre,caracter)==0) continue;
        String[sfarsit_string]=caracter;
        String[sfarsit_string+1]=NULL;
        outtextxy(pozitie_text_x,pozitie_text_y,String);
        sfarsit_string++;
    }
    while(1 && not_escaped){
        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920) {
                break;
            }
        }
    }

    clearBIG(N1);clearBIG(N2);clearBIG(N3);
    for(int i=0;i<=100;i++){
        clearBIG(v1[i]);
        clearBIG(v2[i]);
        clearBIG(v3[i]);
    }
    eroare=0;

    meniuBig();
}
void meniuCifZec(){
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    readimagefile("back.jpg",900,800,1020,920);

    char caracter,String[MAX_VEC];
    int sfarsit_string=0;
    bool not_escaped=1;
    short x,y;

    while(kbhit())getch();
    while(caracter!=13 || caracter!=27){
        if(caracter==13){       //enter
            evaluare(String);
            settextstyle(1,HORIZ_DIR,2);
            int l=0,ltot=0;
            char sir_auxiliar[MAX_VEC],sir_complet[MAX_VEC];
            for (int i=0;i<=MAX_VEC;i++) sir_auxiliar[i]=NULL;
            for (int i=0;i<=MAX_VEC;i++) sir_complet[i]=NULL;
            citireREAL(String,V1,l);
            ltot=l;
            infixtopostfixREAL(V1,V2,ltot);
            rezultat_real=evalpostfixREAL(V2,ltot);
            infixtoprefixREAL(V1,V3,l);
            memorareROsirREAL(V3,l,sir_auxiliar);
            strcpy(sir_complet+strlen(sir_complet),sir_auxiliar);
            for (int i=0;i<=MAX_VEC;i++) sir_auxiliar[i]=NULL;
            strcpy(sir_complet+strlen(sir_complet),"este ");
            memorareROREAL(rezultat_real,sir_auxiliar);
            strcpy(sir_complet+strlen(sir_complet),sir_auxiliar);


            // DE EDITAT SIRUL ESTE IN sir_complet
            if(eroare==0) outtextxy(100,500,sir_complet);
            else {
                if (eroare==1) outtextxy(100,500,"EROARE: Impartire la 0");
                else if(eroare) outtextxy(100,500,"EROARE: Sintaxa Gresita");
            }

            eroare=0;
            for (int i=0;i<=MAX_VEC;i++) sir_auxiliar[i]=NULL;
            for (int i=0;i<=MAX_VEC;i++) sir_complet[i]=NULL;

            break;
        }
        if(caracter==27){       //escape
            not_escaped=0;
            break;
        }
        caracter=getch();
        if(strchr(caractere_valide_cifre,caracter)==0) continue;
        String[sfarsit_string]=caracter;
        String[sfarsit_string+1]=NULL;
        outtextxy(pozitie_text_x,pozitie_text_y,String);
        sfarsit_string++;
    }
    while(1 && not_escaped){

        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>900 && x<1020 && y>800 && y<920) {
                break;
            }
        }
    }

    for(int i=0;i<=99;i++){
        V1[i].n=0; V2[i].n=0; V3[i].n=0;
        V1[i].operatie=0; V2[i].operatie=0; V3[i].operatie=0;
    }
    rezultat_real.n=0; rezultat_real.operatie=0;
    eroare=0;

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
    setbkcolor(1);
    cleardevice();
    short x,y;
    //readimagefile("fundal.jpg",0,0,1920,1080);
    settextstyle(1,HORIZ_DIR,5);
    setcolor(10);
    setbkcolor(1);
    outtextxy(530,300,"Rezultate cu numere zecimale");
    outtextxy(600,500,"Rezultate cu numere mari");
    readimagefile("back.jpg",900,800,1020,920);

    //line(530,299,1376,299);
    //line(1377,299,1377,340);
    //line(600,499,1325,499);
    //line(1326,500,1326,540);
    while(1)
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
    setbkcolor(1);
    settextstyle(1,HORIZ_DIR,5);
    cleardevice();
    short startJoc=0;
    short x,y;
    //readimagefile("fundal.jpg",0,0,1920,1080);
    readimagefile("start.jpg",600,200,1320,500);
    readimagefile("exit.jpg",800,600,1120,800);
    while(1)
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

// converteste un int in BigInt
void conversie (long long int x , BigInt& numar) {
    long long int putere = 1;
    int numar_cif = 1;
    if ( x < 0 ) {
        numar.semn = 1;
        x = -x;
    }
    while ( x >= putere ) {
        putere *= 10;
        numar_cif++;
    }
    numar_cif--;
    numar.v[0] = numar_cif;
    while ( numar_cif ) {
        numar.v[numar_cif--] = x % 10;
        x /= 10;
    }
}

// Adauga cifra x la stanga numarului
void addlBIG (BigInt& numar , int x) {
    for ( int i = 1; i <= numar.v[0]; i++ ) numar.v[i + 1] = numar.v[i];
    numar.v[1] = x;
    numar.v[0]++;
}
// Adauga cifra x la dreapta numarului
void addrBIG (BigInt& numar , int x) {
    if ( numar.v[0] == 0 && x == 0 ) return;
    numar.v[0]++;
    numar.v[numar.v[0]] = x;
}

// Face ca toate valorile unui BigInt sa fie 0
void clearBIG (BigInt& numar) {
    for ( int i = 0; i < 100; i++ ) numar.v[i] = 0;
    numar.semn = 0;
    numar.operatie = 0;
}

//Compara doua BigInt
bool maimareBIG (BigInt numar1 , BigInt numar2) {
    if ( numar1.v[0] > numar2.v[0] ) return 1;
    if ( numar2.v[0] > numar1.v[0] ) return 0;
    for ( int i = 1; i <= numar1.v[0]; i++ ) {
        if ( numar1.v[i] == numar2.v[i] ) continue;
        return ( numar1.v[i] > numar2.v[i] );
    }
    return 0;
}


//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de BigInt
void citireBIG (char sir[] , BigInt vector[] , int& lungime) {
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
            if ( pozitie != 1 ) pozitie++;
            vector[pozitie].operatie = 6; // (
        }
        else if ( sir[i] == 41 ) {
            if ( pozitie != 1 ) pozitie++;
            vector[pozitie].operatie = 7; // )
        }
    }
    lungime = pozitie;
}
//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de Real
void citireREAL (char sir[] , Real vector[] , int& lungime) {

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
            if ( pozitie != 1 ) pozitie++;
            vector[pozitie].operatie = 6; // (
        }
        else if ( sir[i] == 41 ) {
            if ( pozitie != 1 ) pozitie++;
            vector[pozitie].operatie = 7; // )
        }
    }
    lungime = pozitie;
}

// Afiseaza un BigInt in cifre
void afisareBIG (BigInt numar) {
    if ( numar.operatie ) {
        fout << sir_operatori[numar.operatie];
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

//Afiseaza un numar Real
void afisareREAL (Real x) {
    if ( x.operatie ) fout << sir_operatori[x.operatie];
    else fout << setprecision (15) << x.n;
}

//Afiseaza un BigInt in litere (se apeleaza astfel: afisareROBIG (numar, 1 , numar.v[0]) )
void afisareROBIG (BigInt numar , int poz , int pas) {
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
        if ( numar.v[poz] ) fout << sir_cifre_mari[numar.v[poz] - 1] << ' ';
    }
    else if ( pas == 2 ) {                              //pozitia zecilor
        if ( numar.v[poz] == 0 ) {
            afisareROBIG (numar , poz + 1 , 1);
        }
        else if ( numar.v[poz] == 1 ) {                 //10-19
            fout << sir_cifre_mari[numar.v[poz + 1] + 9] << ' ';
        }
        else {                                          //20-99
            fout << sir_cifre_mari[numar.v[poz] + 17] << ' ';
            if ( numar.v[poz + 1] ) fout << "si " << sir_cifre_mari[numar.v[poz + 1] - 1] << ' ';
        }
    }
    else if ( pas == 3 ) {                              //pozitia sutelor
        if ( numar.v[poz] == 0 ) {
            afisareROBIG (numar , poz + 1 , 2);
        }
        else if ( numar.v[poz] == 1 ) {                 //100-199
            fout << sir_cifre_mari[27] << ' ';
            afisareROBIG (numar , poz + 1 , 2);
        }
        else {                                          //200-999
            if ( numar.v[poz] == 2 ) fout << "doua ";
            else fout << sir_cifre_mari[numar.v[poz] - 1] << ' ';
            fout << sir_cifre_mari[28] << ' ';
            afisareROBIG (numar , poz + 1 , 2);
        }
    }
    else if ( ( pas - 1 ) % 3 == 0 ) {                  //unitate
        if ( numar.v[poz] == 0 ) {
            afisareROBIG (numar , poz + 1 , pas - 1);
        }
        else if ( numar.v[poz] == 1 ) {
            fout << sir_cifre_mari[pas / 3 * 2 + 27] << ' ';
            afisareROBIG (numar , poz + 1 , pas - 1);
        }
        else {
            if ( numar.v[poz] == 2 ) {
                fout << "doua " << sir_cifre_mari[pas / 3 + 28] << ' ';
            }
            else if ( numar.v[poz] ) {
                fout << sir_cifre_mari[numar.v[poz] - 1] << ' ';
                fout << sir_cifre_mari[pas / 3 * 2 + 28] << ' ';
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
                fout << ' ' << sir_cifre_mari[pas / 3 * 2 + 28] << ' ';
            }
            afisareROBIG (numar , poz + 2 , pas - 2);
        }
        else {
            afisareROBIG (numar , poz , 2);
            if ( numar.v[poz] ) {
                fout << "de " << sir_cifre_mari[pas / 3 * 2 + 28] << ' ';
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
                fout << "de " << sir_cifre_mari[pas / 3 * 2 + 26] << ' ';
            }
            afisareROBIG (numar , poz + 3 , pas - 3);
        }
        else {
            afisareROBIG (numar , poz , 3);
            if ( numar.v[poz] ) {
                fout << "de " << sir_cifre_mari[pas / 3 * 2 + 26] << ' ';
            }
            afisareROBIG (numar , poz + 3 , pas - 3);
        }
    }
}
//Memoreaza un BigInt intr-un sir de caractere
void memorareROBIG (BigInt numar , int poz , int pas,char sir_caractere[]) {
    if ( numar.operatie ) {
        if ( numar.operatie == 1 ) strcpy (sir_caractere + strlen (sir_caractere) ,"plus ");
        else if ( numar.operatie == 2 ) strcpy (sir_caractere + strlen (sir_caractere) ,"minus ");
        else if ( numar.operatie == 3 ) strcpy (sir_caractere + strlen (sir_caractere) , "ori ");
        else if ( numar.operatie == 4 ) strcpy (sir_caractere + strlen (sir_caractere) ,"impartit la ");
        else if ( numar.operatie == 5 ) strcpy (sir_caractere + strlen (sir_caractere) ,"egal ");
        return;
    }
    else{
        if ( numar.v[0] == 0 ) {
            strcpy (sir_caractere + strlen (sir_caractere) ,"zero ");
            return;
        }
        if ( numar.semn ) strcpy (sir_caractere + strlen (sir_caractere) ,"minus ");
        if ( pas == 1 ) {                                   //pozitia unitatilor
            if ( numar.v[poz] ) {
                strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[numar.v[poz] - 1]);
                strcpy (sir_caractere + strlen (sir_caractere) ," ");
            }
        }
        else if ( pas == 2 ) {                              //pozitia zecilor
            if ( numar.v[poz] == 0 ) {
                memorareROBIG (numar , poz + 1 , 1,sir_caractere);
            }
            else if ( numar.v[poz] == 1 ) {                 //10-19
                strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[numar.v[poz + 1] + 9]);
                strcpy (sir_caractere + strlen (sir_caractere) ," ");
            }
            else {                                          //20-99
                strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[numar.v[poz] + 17]);
                strcpy (sir_caractere + strlen (sir_caractere) , " ");
                if ( numar.v[poz + 1] ) {
                    strcpy (sir_caractere + strlen (sir_caractere) ,"si ");
                    strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[numar.v[poz + 1] - 1]);
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                }
            }
        }
        else if ( pas == 3 ) {                              //pozitia sutelor
            if ( numar.v[poz] == 0 ) {
                memorareROBIG (numar , poz + 1 , 2,sir_caractere);
            }
            else if ( numar.v[poz] == 1 ) {                 //100-199
                strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[27]);
                strcpy (sir_caractere + strlen (sir_caractere) ," ");
                memorareROBIG (numar , poz + 1 , 2,sir_caractere);
            }
            else {                                          //200-999
                if ( numar.v[poz] == 2 ) {
                    strcpy (sir_caractere + strlen (sir_caractere) ,"doua ");
                }
                else {
                    fout << sir_cifre_mari[numar.v[poz] - 1] << ' ';
                    strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[numar.v[poz] - 1]);
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                }
                strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[28]);
                strcpy (sir_caractere + strlen (sir_caractere) ," ");
                memorareROBIG (numar , poz + 1 , 2,sir_caractere);
            }
        }
        else if ( ( pas - 1 ) % 3 == 0 ) {                  //unitate
            if ( numar.v[poz] == 0 ) {
                memorareROBIG (numar , poz + 1 , pas - 1,sir_caractere);
            }
            else if ( numar.v[poz] == 1 ) {
                strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[pas / 3 * 2 + 27]);
                strcpy (sir_caractere + strlen (sir_caractere) ," ");
                memorareROBIG (numar , poz + 1 , pas - 1,sir_caractere);
            }
            else {
                if ( numar.v[poz] == 2 ) {
                    strcpy (sir_caractere + strlen (sir_caractere) ,"doua ");
                    strcpy (sir_caractere + strlen (sir_caractere) ,sir_cifre_mari[pas / 3 + 28]);
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                }
                else if ( numar.v[poz] ) {
                    strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[numar.v[poz] - 1]);
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                    strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[pas / 3 * 2 + 28]);
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                }
                memorareROBIG (numar , poz + 1 , pas - 1,sir_caractere);
            }
        }
        else if ( ( pas - 2 ) % 3 == 0 ) {                  //zeci
            if ( numar.v[poz] == 0 ) {
                memorareROBIG (numar , poz + 1 , pas - 1,sir_caractere);
            }
            else if ( numar.v[poz] == 1 ) {
                memorareROBIG (numar , poz , 2,sir_caractere);
                if ( numar.v[poz] ) {
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                    strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[pas / 3 * 2 + 28]);
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                }
                memorareROBIG (numar , poz + 2 , pas - 2,sir_caractere);
            }
            else {
                memorareROBIG (numar , poz , 2,sir_caractere);
                if ( numar.v[poz] ) {
                    strcpy (sir_caractere + strlen (sir_caractere) ,"de ");
                    strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[pas / 3 * 2 + 28]);
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                }
                memorareROBIG (numar , poz + 2 , pas - 2,sir_caractere);
            }
        }
        else {                                              //sute
            if ( numar.v[poz] == 0 ) {
                memorareROBIG (numar , poz + 1 , pas - 1,sir_caractere);
            }
            else if ( numar.v[poz] == 1 ) {
                memorareROBIG (numar , poz , 3,sir_caractere);
                if ( numar.v[poz] ) {
                    strcpy (sir_caractere + strlen (sir_caractere) ,"de ");
                    strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[pas / 3 * 2 + 26]);
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                }
                memorareROBIG (numar , poz + 3 , pas - 3,sir_caractere);
            }
            else {
                memorareROBIG (numar , poz , 3,sir_caractere);
                if ( numar.v[poz] ) {
                    strcpy (sir_caractere + strlen (sir_caractere) ,"de ");
                    strcpy (sir_caractere + strlen (sir_caractere) , sir_cifre_mari[pas / 3 * 2 + 26]);
                    strcpy (sir_caractere + strlen (sir_caractere) ," ");
                }
                memorareROBIG (numar , poz + 3 , pas - 3,sir_caractere);
            }
        }
    }
}

//Afiseaza un Real in litere
void afisareROREAL (Real x) {
    double intreg , fractionar;
    BigInt intregB , fractionarB;
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
//Memoreaza un Real intr-un sir de caractere
void memorareROREAL (Real x,char sir_caractere[]) {
    double intreg , fractionar;
    BigInt intregB , fractionarB;
    int precizie = 1;

    fractionar = modf (x.n , &intreg);

    fractionar *= 10;
    while ( (int)fractionar > 0 && precizie < 10 ) {
        addrBIG (fractionarB , (int)fractionar);
        fractionar -= (int)fractionar;
        fractionar *= 10;
        precizie++;
    }
    char auxiliar[MAX_VEC];
    for ( int i = 0; i < MAX_VEC; i++ ) auxiliar[i] = NULL;
    conversie (intreg , intregB);
    memorareROBIG (intregB , 1 , intregB.v[0],auxiliar);
    strcpy (sir_caractere + strlen (sir_caractere) , auxiliar);
    if ( fractionarB.v[0] ) {
        char auxiliar2[MAX_VEC];
        for ( int i = 0; i < MAX_VEC; i++ ) auxiliar2[i] = NULL;
        //fout << "virgula ";
        strcpy (sir_caractere + strlen (sir_caractere) , "virgula ");
        memorareROBIG (fractionarB , 1 , fractionarB.v[0],auxiliar2);
        strcpy (sir_caractere + strlen (sir_caractere) , auxiliar2);
    }
}

//Traduce un vector de BigInt in limba romana (vecotrul trebuie sa aiba forma prefixata)
void afisareROsirBIG (BigInt vector[] , int lungime) {
    int ultima_operatie = 5 , penultima_operatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- ) {
        if ( vector[i].operatie ) {
            if ( vector[i].operatie == 1 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 1;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "suma dintre ";
            }
            else if ( vector[i].operatie == 2 ) {

                penultima_operatie = ultima_operatie;
                ultima_operatie = 2;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "diferenta dintre ";
            }
            else if ( vector[i].operatie == 3 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 3;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "produsul dintre ";
            }
            else if ( vector[i].operatie == 4 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 4;
                impartire = 1;
            }
        }
        else {                                                                      //numar
            if ( i != 1 ) {
                afisareROBIG (vector[i] , 1 , vector[i].v[0]);
                if ( impartire == 0 ) {
                    if ( vector[i - 1].operatie != ultima_operatie ) fout << "si ";
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
//Traduce un vector de BigInt in limba romana si il pune intr-un sir de caractere (vecotrul trebuie sa aiba forma prefixata)
void memorareROsirBIG (BigInt vector[] , int lungime,char sir_caractere[]) {
    int ultima_operatie = 5 , penultima_operatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- ) {
        if ( vector[i].operatie ) {
            if ( vector[i].operatie == 1 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 1;
                if ( ultima_operatie == penultima_operatie );
                else {
                    strcpy (sir_caractere + strlen (sir_caractere) ,"suma dintre " );
                }
            }
            else if ( vector[i].operatie == 2 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 2;
                if ( ultima_operatie == penultima_operatie );
                else {
                    strcpy (sir_caractere + strlen (sir_caractere) ,"diferenta dintre " );
                }
            }
            else if ( vector[i].operatie == 3 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 3;
                if ( ultima_operatie == penultima_operatie );
                else {
                    strcpy (sir_caractere + strlen (sir_caractere) ,"produsul dintre ");
                }
            }
            else if ( vector[i].operatie == 4 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 4;
                impartire = 1;
            }
        }
        else {                                                                      //numar
            if ( i != 1 ) {
                char aux[MAX_VEC];
                for ( int j = 0; j < MAX_VEC; j++ ) aux[j] = NULL;
                memorareROBIG (vector[i] , 1 , vector[i].v[0],aux);
                strcpy (sir_caractere + strlen (sir_caractere) ,aux );
                if ( impartire == 0 ) {
                    if ( vector[i - 1].operatie != ultima_operatie ) {
                        strcpy (sir_caractere + strlen (sir_caractere) ,"si ");
                    }
                    else {
                        strcpy (sir_caractere + strlen (sir_caractere) ,",");
                    }
                }
            }
            else {
                char aux[MAX_VEC];
                for ( int j = 0; j < MAX_VEC; j++ ) aux[j] = NULL;
                memorareROBIG (vector[i] , 1 , vector[i].v[0] , aux);
                strcpy (sir_caractere + strlen (sir_caractere) , aux);
            }
            if ( impartire ) {
                strcpy (sir_caractere + strlen (sir_caractere) , "impartit la ");
            }
            impartire = 0;
        }
    }
}

//Traduce un vector de Real in limba romana (vecotrul trebuie sa aiba forma prefixata)
void afisareROsirREAL (Real vector[] , int lungime) {
    int ultima_operatie = 5 , penultima_operatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- ) {
        if ( vector[i].operatie ) {
            if ( vector[i].operatie == 1 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 1;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "suma dintre ";
            }
            else if ( vector[i].operatie == 2 ) {

                penultima_operatie = ultima_operatie;
                ultima_operatie = 2;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "diferenta dintre ";
            }
            else if ( vector[i].operatie == 3 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 3;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "produsul dintre ";
            }
            else if ( vector[i].operatie == 4 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 4;
                impartire = 1;
            }
        }
        else {                                                                      //numar
            if ( i != 1 ) {
                afisareROREAL (vector[i]);
                if ( impartire == 0 ) {
                    if ( vector[i - 1].operatie != ultima_operatie ) fout << "si ";
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
//Traduce un vector de Real in limba romana si il pune intr-un sir de caractere (vecotrul trebuie sa aiba forma prefixata)
void memorareROsirREAL (Real vector[] , int lungime , char sir_caractere[]) {
    int ultima_operatie = 5 , penultima_operatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- ) {
        if ( vector[i].operatie ) {
            if ( vector[i].operatie == 1 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 1;
                if ( ultima_operatie == penultima_operatie );
                else {
                    strcpy (sir_caractere + strlen (sir_caractere) , "suma dintre ");
                }
            }
            else if ( vector[i].operatie == 2 ) {

                penultima_operatie = ultima_operatie;
                ultima_operatie = 2;
                if ( ultima_operatie == penultima_operatie );
                else {
                    strcpy (sir_caractere + strlen (sir_caractere) , "diferenta dintre ");
                }
            }
            else if ( vector[i].operatie == 3 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 3;
                if ( ultima_operatie == penultima_operatie );
                else {
                    strcpy (sir_caractere + strlen (sir_caractere) , "produsul dintre ");
                }
            }
            else if ( vector[i].operatie == 4 ) {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 4;
                impartire = 1;
            }
        }
        else {                                                                      //numar
            if ( i != 1 ) {
                char auxiliar[MAX_VEC];
                for ( int j = 0; j < MAX_VEC; j++ ) auxiliar[j] = NULL;
                memorareROREAL (vector[i],auxiliar);
                strcpy (sir_caractere + strlen (sir_caractere) , auxiliar);
                if ( impartire == 0 ) {
                    if ( vector[i - 1].operatie != ultima_operatie ) strcpy (sir_caractere + strlen (sir_caractere) , "si ");
                    else strcpy (sir_caractere + strlen (sir_caractere) , ",");
                }
            }
            else {
                char auxiliar[150];
                for ( int j = 0; j <= 149; j++ ) auxiliar[j] = NULL;
                memorareROREAL (vector[i] , auxiliar);
                strcpy (sir_caractere + strlen (sir_caractere) , auxiliar);
            }
            if ( impartire ) {
                strcpy (sir_caractere + strlen (sir_caractere) , "impartit la ");
            }
            impartire = 0;
        }
    }
}


// Calculeaza suma a doua BigInt
void adunareBIG (BigInt& numar1 , BigInt& numar2 , BigInt& rezultat) {
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

// Calculeaza diferenta a doua BigInt
void scadereBIG (BigInt& numar1 , BigInt& numar2 , BigInt& rezultat) {
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
void scaderesecundaraBIG (BigInt& numar1 , BigInt& numar2 , BigInt& rezultat , bool semn) {
    int lungime , carry = 0 , contor_zero = 0;
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
        contor_zero++;
    }
    rezultat.v[0] = numar1.v[0] - contor_zero;
    for ( int i = 1; i <= numar1.v[0]; i++ ) rezultat.v[i] = rezultat.v[i + contor_zero];
    rezultat.semn = semn;
}

//Inumlteste doua BigInt
void inmultireBIG (BigInt& numar1 , BigInt& numar2 , BigInt& rezultat) {
    BigInt rezultat_auxiliar;
    for ( int i = 1; i <= numar2.v[0]; i++ ) {
        BigInt aux;
        inmultiresBIG (numar1 , numar2.v[( numar2.v[0] - i + 1 )] , aux , i - 1);
        adunareBIG (rezultat , aux , rezultat_auxiliar);
        rezultat = rezultat_auxiliar;
    }
    if ( numar1.semn != numar2.semn ) rezultat.semn = 1; // a * (-b) || (-a) * b
    else rezultat.semn = 0;                             // a * b || (-a) * (-b)
}
//Functie secundara pentru inmultire, calculeaza produsul dintre un BigInt si o cifra si adauga un numar specificat de zerouri
void inmultiresBIG (BigInt& numar1 , int cifra , BigInt& rezultat , int zero) {
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

//Calculeaza catul impartirii naturale a doua BigInt
void impartireBIG (BigInt deimpartit , BigInt impartitor , BigInt& cat) {
    if ( impartitor.v[0] == 0 ) {
        eroare=1;
        return;
    }
    BigInt suma , cat_auxiliar , adunare_cat;
    int putere = 1 , preamare = 1;
    adunare_cat.v[1] = 1;
    while ( putere > 0 ) {
        BigInt auxiliar_suma;
        adunareBIG (suma , impartitor , auxiliar_suma);
        if ( maimareBIG (auxiliar_suma , deimpartit) ) {
            putere--;
            impartitor.v[0]--;
            preamare = 0;
        }
        else {
            suma = auxiliar_suma;
            BigInt auxiliar_cat;
            adunare_cat.v[0] = putere;
            adunareBIG (cat_auxiliar , adunare_cat , auxiliar_cat);
            cat_auxiliar = auxiliar_cat;
            if ( preamare ) {
                putere++;
                impartitor.v[0]++;
            }
        }
    }
    cat = cat_auxiliar;
}

//Imparte un BigInt la o cifra  (nefolosit)
void impartiresBIG (BigInt& nr1 , int x , BigInt& nr2) {
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
int prioBIG (BigInt Operator) {
    if ( Operator.operatie == 1 || Operator.operatie == 2 ) return 2; // + || -
    if ( Operator.operatie == 3 || Operator.operatie == 4 ) return 3; // * || /
    if ( Operator.operatie == 6 || Operator.operatie == 7 ) return 4; // ( || )
    return 0;
}
//Calculeaza prioritate operatorilor pentru conversia postfixata
int prioREAL (Real nr) {
    if ( nr.operatie == 1 || nr.operatie == 2 ) return 2; // + || -
    if ( nr.operatie == 3 || nr.operatie == 4 ) return 3; // * || /
    if ( nr.operatie == 6 || nr.operatie == 7 ) return 4; // ( || )
    return 0;
}
//Transforma vectorul 1 de BigInt cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
void infixtopostfixBIG (BigInt vector1[] , BigInt vector2[] , int& lungime) {
    BigInt stiva[150] , auxiliar;
    int inceput_coada1 = 1 , sfarsit_coada1 = lungime + 1 , inceput_coada2 = 1 , sfarsit_coada2 = 1 , varf_stiva = 1;
    while ( inceput_coada1 < sfarsit_coada1 ) {
        auxiliar = vector1[inceput_coada1];  inceput_coada1++;
        if ( auxiliar.operatie == 0 ) {
            vector2[sfarsit_coada2++] = auxiliar;
        }
        else {
            if ( auxiliar.operatie == 7 ) {
                while ( stiva[varf_stiva].operatie != 6 ) {
                    vector2[sfarsit_coada2] = stiva[varf_stiva];
                    sfarsit_coada2++; varf_stiva--;
                }
                varf_stiva--;
                lungime -= 2;
            }
            else {
                while ( varf_stiva > 1 && stiva[varf_stiva].operatie != 6 && ( prioBIG (stiva[varf_stiva]) >= prioBIG (auxiliar) ) ) {
                    vector2[sfarsit_coada2++] = stiva[varf_stiva];
                    varf_stiva--;
                }
                varf_stiva++;
                stiva[varf_stiva] = auxiliar;
            }
        }
    }
    while ( varf_stiva > 1 ) {
        vector2[sfarsit_coada2++] = stiva[varf_stiva];
        varf_stiva--;
    }
}
//Transforma vectorul 1 de Real cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
void infixtopostfixREAL (Real vector1[] , Real vector2[] , int& lungime) {
    Real stiva[150] , auxiliar;
    int inceput_coada1 = 1 , sfarsit_coada1 = lungime + 1 , inceput_coada2 = 1 , sfarsit_coada2 = 1 , varf_stiva = 1;
    while ( inceput_coada1 < sfarsit_coada1 ) {
        auxiliar = vector1[inceput_coada1];  inceput_coada1++;
        if ( auxiliar.operatie == 0 ) {
            vector2[sfarsit_coada2++] = auxiliar;
        }
        else {
            if ( auxiliar.operatie == 7 ) {
                while ( stiva[varf_stiva].operatie != 6 ) {
                    vector2[sfarsit_coada2] = stiva[varf_stiva];
                    sfarsit_coada2++; varf_stiva--;
                }
                varf_stiva--;
                lungime -= 2;
            }
            else {
                while ( varf_stiva > 1 && stiva[varf_stiva].operatie != 6 && ( prioREAL (stiva[varf_stiva]) >= prioREAL (auxiliar) ) ) {
                    vector2[sfarsit_coada2++] = stiva[varf_stiva];
                    varf_stiva--;
                }
                varf_stiva++;
                stiva[varf_stiva] = auxiliar;
            }
        }
    }
    while ( varf_stiva > 1 ) {
        vector2[sfarsit_coada2++] = stiva[varf_stiva];
        varf_stiva--;
    }
}

//Evalueaza o expresie postfixata si returneaza rezultatul
BigInt evalpostfixBIG (BigInt vector[] , int lungime) {
    BigInt stiva[100] , auxiliar , operand_stanga , operand_dreapta;
    int varf_stiva = 0 , inceput_coada = 1;
    while ( inceput_coada <= lungime ) {
        auxiliar = vector[inceput_coada]; inceput_coada++;
        if ( auxiliar.operatie == 0 ) {
            varf_stiva++;
            stiva[varf_stiva] = auxiliar;
        }
        else {
            BigInt val;
            operand_dreapta = stiva[varf_stiva]; varf_stiva--;
            operand_stanga = stiva[varf_stiva]; varf_stiva--;
            if ( auxiliar.operatie == 1 ) adunareBIG (operand_stanga , operand_dreapta , val);
            else if ( auxiliar.operatie == 2 ) scadereBIG (operand_stanga , operand_dreapta , val);
            else if ( auxiliar.operatie == 3 ) inmultireBIG (operand_stanga , operand_dreapta , val);
            else if ( auxiliar.operatie == 4 ) impartireBIG (operand_stanga , operand_dreapta , val);
            varf_stiva++;
            stiva[varf_stiva] = val;
        }
    }
    return stiva[1];
}
//Evalueaza o expresie postfixata si returneaza rezultatul
Real evalpostfixREAL (Real vector[] , int lungime) {
    Real stiva[100] , auxiliar , operand_stanga , operand_dreapta;
    int varf_stiva = 0 , inceput_coada = 1;
    while ( inceput_coada <= lungime ) {
        auxiliar = vector[inceput_coada]; inceput_coada++;
        if ( auxiliar.operatie == 0 ) {
            varf_stiva++;
            stiva[varf_stiva] = auxiliar;
        }
        else {
            operand_dreapta = stiva[varf_stiva]; varf_stiva--;
            operand_stanga = stiva[varf_stiva]; varf_stiva--;
            varf_stiva++;
            if ( auxiliar.operatie == 1 ) stiva[varf_stiva].n = operand_stanga.n + operand_dreapta.n;
            else if ( auxiliar.operatie == 2 ) stiva[varf_stiva].n = operand_stanga.n - operand_dreapta.n;
            else if ( auxiliar.operatie == 3 ) stiva[varf_stiva].n = operand_stanga.n * operand_dreapta.n;
            else if ( auxiliar.operatie == 4 ) stiva[varf_stiva].n = operand_stanga.n / operand_dreapta.n;

        }
    }
    return stiva[1];
}

//Transforma vectorul 1 de BigInt cu forma infixata in vectorul 2 cu forma prefixata
void infixtoprefixBIG (BigInt vector1[] , BigInt vector2[] , int& lungime) {
    BigInt stiva[100];
    for ( int i = 1; i <= lungime; i++ ) {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        else if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
        stiva[lungime + 1 - i] = vector1[i];
    }
    infixtopostfixBIG (stiva , vector2 , lungime);
    for ( int i = 1; i <= lungime; i++ ) {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
    }
    for ( int i = 1; i <= lungime; i++ ) {
        vector1[i] = vector1[lungime + 1 - i];
    }
}
//Transforma vectorul 1 de Real cu forma infixata in vectorul 2 cu forma prefixata
void infixtoprefixREAL (Real vector1[] , Real vector2[] , int& lungime) {
    Real stiva[100];
    for ( int i = 1; i <= lungime; i++ ) {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        else if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
        stiva[lungime + 1 - i] = vector1[i];
    }
    infixtopostfixREAL (stiva , vector2 , lungime);
    for ( int i = 1; i <= lungime; i++ ) {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
    }
    for ( int i = 1; i <= lungime; i++ ) {
        vector1[i] = vector1[lungime + 1 - i];
    }
}

void evaluare (char sir_caractere[]) {
	bool este_operand = 0;
	int numar_paranteze = 0,numar_cifre=0;
	for ( int i = 0; i < strlen (sir_caractere); i++ ) {
		if ( sir_caractere[i] >= 48 && sir_caractere[i] <= 57 ) {
			este_operand = 1;
			numar_cifre++;
			if(numar_cifre>9){
                eroare=9;
                return;
			}
		}
		else if ( sir_caractere[i] == (char)43 || sir_caractere[i] == 45 || sir_caractere[i] == 42 || sir_caractere[i] == 120 || sir_caractere[i] == 47 || sir_caractere[i] == 58 ) {
            numar_cifre=0;
			if ( este_operand == 0 ) {
				eroare = 3;
				return;
			}
			este_operand = 0;
		}
		else if ( sir_caractere[i] == 40 ) {
			if ( este_operand ) {
				eroare = 4;
				return;
			}
			numar_paranteze++;
		}
		else if ( sir_caractere[i] == 41 ) {
			if ( este_operand == 0 ) {
				eroare = 5;
				return;
			}
			if ( numar_paranteze > 0 )numar_paranteze--;
			else {
				eroare = 6;
				return;
			}
			este_operand = 1;
		}
	}
	if ( numar_paranteze ) {
		eroare = 7;
		return;
	}
	if ( este_operand == 0 ) eroare = 8;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
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
char* evaluatorLit(char vecCuv[5000][10000]) // Calculeaza ecuatia din vectorul de mai sus (PENTRU NUMERE CU VIRGULA)
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
char* evaluatorBig(char vecCuv[5000][10000])//Calculeaza ecuatia pentru numere in big int
{
    char s[1000][100];
    int v = 0;
    stack<char> op;
    for(int i=0;i<k;i++)
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
            int r = 0;
            char cOP = op.top();
            op.pop();
            if(cOP == '*')
            {
                r=1;
                while(s[v][0]!='*')
                {
                    r=r*(stoi(s[v],nullptr));
                    v--;
                }
                strcpy(s[v],to_string(r).c_str());
            }
            else if(cOP=='+')
            {
                r=0;
                while(s[v][0]!='+')
                {
                    r=r+(stoi(s[v],nullptr));
                    v--;
                }
                strcpy(s[v],to_string(r).c_str());
            }
            else if(cOP=='-')
            {
                r=(stoi(s[v],nullptr));
                v--;
                r-=(stoi(s[v],nullptr));
                v--;
                r*=-1;
                strcpy(s[v],to_string(r).c_str());
            }
            else if(cOP=='/')
            {
                r=(stoi(s[v-1],nullptr));
                v--;
                r/=(stoi(s[v+1],nullptr));
                v--;
                strcpy(s[v],to_string(r).c_str());
            }
        }
    }
    strcpy(rez,s[1]);
    return rez;
}

*/
