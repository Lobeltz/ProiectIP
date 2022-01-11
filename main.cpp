#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <graphics.h>
#include <winbgim.h>
#include<stack>
#define MAX_VEC 5000
using namespace std;

ifstream fin ("CalcRO.in");
ofstream fout ("CalcRO.out");

struct BigInt   //Numere mari
{
    int v[100] = { 0 };
    bool semn = 0;
    int operatie = 0;
};
BigInt numar1_bigint,numar2_bigint,numar3_bigint,vector1_bigint[100],vector2_bigint[100],vector3_bigint[100];

struct Real     //Numere reale
{
    double n = 0;
    int operatie = 0;
};
Real rezultat_real,vector1_real[100],vector2_real[100],vector3_real[100];

char sir_cifre_mari[50][20] = { "unu","doi","trei","patru","cinci","sase","sapte","opt","noua","zece","unsprezece","doisprezece","treisprezece",
                                "paisprezece","cinsprezece","saisprezece","saptisprezece","optisprezece","nouasprezece","douazeci","treizeci",
                                "patruzeci","cincizeci","saizeci","saptezeci","optzeci","nouazeci","o suta","sute","o mie","mii","un milion","milioane",
                                "un miliard","miliarde","un bilion","bilioane","un trilion","trilioane","un cvadrilion","cvadrilioane","un catralion",
                                "catralioane","un cvintilion","cvintilioane","un sextilion","sextilioane"
                              };
char sir_operatori[10] = { '`','+','-','*','/','=','(',')' };
char caractere_valide_cifre[20]= {'1','2','3','4','5','6','7','8','9','0','+','-','*','x','/',':','(',')',' '};
char caractere_valide_litere[200]= {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz _,?"};

char cuvInutile[100][100] = {"Care","care","Ce","ce", "Cat","cat","Cum","cum", "este", "sunt", "rezultatul","egal", "cu", "lui", "?", "dintre", "la"},
                            cuvInm[10][20] = {"inmultire", "inmultirii", "inmultirea", "produs", "produsul", "produsului"},
                                    cuvAdun[10][20] = {"suma", "sumei", "adunare", "adunarea", "adunarii"},
                                            cuvScad[10][20] = {"scadere", "scaderii","scaderea", "diferenta", "diferentei"},
                                                    cuvImp[10][20] = {"impartire", "impartirea","raport","raportul"};
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
int ok, aFostcuvCheie,k;
char vecCuv[5000][10000],rez[1000];

char* transfLitCif(char *s);
void introdVec(char *s);
char* evaluatorLit(char vecCuv[5000][10000]);
char* evaluatorBig(char vecCuv[5000][10000]);

void conversie (long long int x, BigInt& nr); // converteste un int in BigInt
void add_left_Big (BigInt& nr, int x); // Adauga cifra x la stanga numarului
void add_right_Big (BigInt& nr, int x); // Adauga cifra x la dreapta numarului
void clear_Big (BigInt& nr);// Face ca toate valorile unui BigInt sa fie 0
bool mai_mare_Big (BigInt numar1, BigInt numar2); //Compara doua BigInt

void citire_Big (char sir[], BigInt vector[], int& lungime);  //Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de BigInt
void citire_Real (char sir[], Real vector[], int& lungime);  //Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de Real
void afisare_Big (BigInt nr);// Afiseaza un BigInt in cifre
void afisare_Real (Real x);//Afiseaza un numar Real
void afisare_ro_Big (BigInt numar, int poz, int pas);  //Afiseaza un BigInt in litere (se apeleaza astfel: afisare_ro_Big (numar, 1 , numar.v[0]) )
void memorare_ro_Big (BigInt numar, int poz, int pas, char sir_caractere[]);   //Memoreaza un BigInt intr-un sir de caractere
void afisare_ro_Real (Real x);//Afiseaza un Real in litere
void memorare_ro_Real (Real x, char sir_caractere[]); //Memoreaza un Real intr-un sir de caractere
void afisare_ro_sir_Big (BigInt vector[], int lungime); //Traduce un vector de BigInt in limba romana (vecotrul trebuie sa aiba forma prefixata)
void memorare_ro_sir_Big (BigInt vector[], int lungime, char sir_caractere[]);  //Traduce un vector de BigInt in limba romana si il pune intr-un sir de caractere (vecotrul trebuie sa aiba forma prefixata)
void afisare_ro_sir_Real (Real vector[], int lungime); //Traduce un vector de Real in limba romana (vecotrul trebuie sa aiba forma prefixata)
void memorare_ro_sir_Real (Real vector[], int lungime, char sir_caractere[]);  //Traduce un vector de Real in limba romana si il pune intr-un sir de caractere (vecotrul trebuie sa aiba forma prefixata)

void adunare_Big (BigInt& nr1, BigInt& nr2, BigInt& nr3);  // Calculeaza suma a doua BigInt
void scadere_Big (BigInt& numar1, BigInt& numar2, BigInt& rezultat);  // Calculeaza diferenta a doua BigInt
void scadere_secundara_Big (BigInt& numar1, BigInt& numar2, BigInt& rezultat, bool semn);   // Functie secundara pentru scadere, calculeaza propiu-zis diferenta a doua numere pozitive primul avand mai multe cifre
void inmultire_Big (BigInt& numar1, BigInt& numar2, BigInt& rezultat);  //Inumlteste doua BigInt
void inmultire_secundara_Big (BigInt& numar1, int cifra, BigInt& rezultat, int zero);   //Functie secundara pentru inmultire, calculeaza produsul dintre un BigInt si o cifra si adauga un numar specificat de zerouri
void impartire_Big (BigInt deimpartit, BigInt impartitor, BigInt& cat);  //Calculeaza catul impartirii naturale a doua BigInt
void impartire_secundara_Big (BigInt& nr1, int x, BigInt& nr2);  //Imparte un BigInt la o cifra  (nefolosit)

int prio_Big (BigInt Operator);//Calculeaza prioritate operatorilor pentru conversia postfixata
int prio_Real (Real nr);//Calculeaza prioritate operatorilor pentru conversia postfixata
void infix_to_postfix_Big (BigInt vector1[], BigInt vector2[], int& lungime);  //Transforma vectorul 1 de BigInt cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
void infix_to_postfix_Real (Real vector1[], Real vector2[], int& lungime);  //Transforma vectorul 1 de Real cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
BigInt eval_postfix_Big (BigInt vector[], int lungime); //Evalueaza o expresie postfixata si returneaza rezultatul
Real eval_postfix_Real (Real vector[], int lungime); //Evalueaza o expresie postfixata si returneaza rezultatul
void infix_to_prefix_Big (BigInt vector1[], BigInt vector2[], int& lungime);  //Transforma vectorul 1 de BigInt cu forma infixata in vectorul 2 cu forma prefixata
void infix_to_prefix_Real (Real vector1[], Real vector2[], int& lungime);  //Transforma vectorul 1 de Real cu forma infixata in vectorul 2 cu forma prefixata
void evaluare(char sir_caractere[]);//Verifica corectitudinea unei expresii matematice

int done;

void meniu1();
void meniuZecim();
void meniuBig();
void meniu2();
void meniuLitBig();
void meniuLitZec();
void meniuCifBig();
void meniuCifZec();
void muzica(int windowS);
void despre(int windowS);
void ajutor(int windowS);

int pozitiex_text_scris = 200, pozitiey_text_scris = 100, pozitiex_text_afisat = 100, pozitiey_text_afisat = 300;
int text_style = 6, text_size1 = 16, text_size2 = 16;
int eroare, limita_cifre = 60, limita_caractere_rand = 75;

void meniuLitBig()
{
    settextstyle(text_style,HORIZ_DIR,text_size1+3);
    cleardevice();
    setcolor(15);
    readimagefile("scris.jpg",0,0,1920,1080);
    {
        char caracter,String[MAX_VEC]= {0};
        int sfarsit_string=0;
        bool not_escaped=1;
        short x,y;

        while(kbhit())getch();
        while(caracter!=13 || caracter!=27)
        {
            caracter=getch();
            if(caracter==13)
            {
                settextstyle(text_style,HORIZ_DIR,text_size2);//enter
                introdVec(String);
                BigInt numar;
                char sir[MAX_VEC]= {0},sir2[MAX_VEC]= {0};
                strcpy(sir,evaluatorBig(vecCuv));
                for(int i=0; i<strlen(sir); i++)
                    add_right_Big(numar,sir[i]-'0');
                memorare_ro_Big(numar,1,numar.v[0],sir2);
                int nrc=0,i,j;
                char temp[MAX_VEC]= {0};
                setcolor(3);
                while(sir2[nrc+i]!='\0') // punere pe mai multe randuri
                {
                    if(i==40)
                    {
                        while(sir2[nrc+i]!=' ')
                            i--;
                        for(j=0; j<i; j++)
                            temp[j]=sir2[nrc+j];
                        nrc=nrc+i;
                        temp[i]='\0';
                        i=0;
                        outtextxy(pozitiex_text_afisat,pozitiey_text_afisat+nrc,temp);
                    }
                    i++;
                }
                for(j=0; j<i; j++)
                    temp[j]=sir2[nrc+j];
                nrc=nrc+i;
                temp[i]='\0';
                i=0;
                outtextxy(pozitiex_text_afisat,pozitiey_text_afisat+nrc,temp);

                //outtextxy(pozitiex_text_afisat,pozitiey_text_afisat,sir2); Daca nu vreau pe mai multe randuri
                break;
            }
            if(caracter==27)        //escape
            {
                not_escaped=0;
                break;
            }
            if(caracter==8)  //backspace
            {
                readimagefile("scris.jpg",0,0,1920,1080);
                String[sfarsit_string-1]=NULL;
                sfarsit_string--;
                outtextxy(pozitiex_text_scris,pozitiey_text_scris,String);
                continue;
            }
            else if(strchr(caractere_valide_litere,caracter)==0) continue;
            String[sfarsit_string]=caracter;
            String[sfarsit_string+1]=NULL;
            //outtextxy(pozitiex_text_scris,pozitiey_text_scris,String);
            int nrc2=0,j2=0,i2=0,nr_randuri=0;
            char temp2[MAX_VEC]= {0};
            while(String[nrc2+i2]!='\0') //punere pe mai multe randuri
            {
                if(i2==50)
                {

                    while(String[nrc2+i2]!=' ')
                        i2--;
                    for(j2=0; j2<i2; j2++)
                        temp2[j2]=String[nrc2+j2];
                    nrc2=nrc2+i2;
                    temp2[i2]='\0';
                    i2=0;
                    outtextxy(pozitiex_text_scris,pozitiey_text_scris+nr_randuri*40,temp2);
                    nr_randuri++;
                }
                i2++;
            }
            for(j2=0; j2<i2; j2++)
                temp2[j2]=String[nrc2+j2];
            nrc2=nrc2+i2;
            temp2[i2]='\0';
            i2=0;
            outtextxy(pozitiex_text_scris,pozitiey_text_scris+nr_randuri*40,temp2);
            sfarsit_string++;
        }

        while(1 && not_escaped)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                if(x<=156 && y<=140)
                {
                    not_escaped=0;
                    break;
                }
            }
        }
        eroare=0;
    }
    memset(vecCuv,NULL, sizeof vecCuv),k=0,ok=0, aFostcuvCheie=0,memset(rez,NULL, sizeof rez);
    meniuBig();
}
void meniuLitZec()
{
    settextstyle(text_style,HORIZ_DIR,text_size1);
    cleardevice();
    setcolor(15);
    readimagefile("scris.jpg",0,0,1920,1080);

    {
        char caracter,String[MAX_VEC]= {0};
        int sfarsit_string=0;
        bool not_escaped=1;
        short x,y;


        while(kbhit())getch();
        while(caracter!=13 || caracter!=27)
        {
            caracter=getch();
            if(caracter==13)        //enter
            {
                settextstyle(text_style,HORIZ_DIR,text_size2);
                introdVec(String);
                BigInt numar,numar2;
                char sir1[MAX_VEC]= {0},sir2[MAX_VEC]= {0},sir3[MAX_VEC]= {0};
                strcpy(sir1,evaluatorLit(vecCuv));
                for(int i=0; i<strlen(sir1) && sir1[i]!='.'; i++)
                    add_right_Big(numar,sir1[i]-'0');
                memorare_ro_Big(numar,1,numar.v[0],sir2);
                int i=0;
                if(strchr(sir1,'.')!=0)
                {
                    i+=2;
                    for(; i<strlen(sir1); i++)
                            add_right_Big(numar2,sir1[i]-'0');

                    memorare_ro_Big(numar2,1,numar2.v[0],sir3);
                    strcat(sir2,"virgula ");
                    strcat(sir2,sir3);
                }

                char sir4[1000]="este ";
                strcat(sir4,sir2);
                cout<<endl<<sir4;
                int nrc=0,j;
                i=0;
                char temp[MAX_VEC]= {0};
                setcolor(3);
                while(sir4[nrc+i]!='\0') // punere pe mai multe randuri
                {
                    if(i==40)
                    {
                        while(sir4[nrc+i]!=' ')
                            i--;
                        for(j=0; j<i; j++)
                            temp[j]=sir4[nrc+j];
                        nrc=nrc+i;
                        temp[i]='\0';
                        i=0;
                        outtextxy(pozitiex_text_afisat,pozitiey_text_afisat+nrc*2,temp);
                    }
                    i++;
                }
                for(j=0; j<i; j++)
                    temp[j]=sir4[nrc+j];
                nrc=nrc+i;
                temp[i]='\0';
                i=0;
                outtextxy(pozitiex_text_afisat,pozitiey_text_afisat+nrc*2,temp);
                break;
            }
            if(caracter==27)        //escape
            {
                not_escaped=0;
                break;
            }

            if(caracter==8)  //backspace
            {
                readimagefile("scris.jpg",0,0,1920,1080);
                String[sfarsit_string-1]=NULL;
                sfarsit_string--;
                outtextxy(pozitiex_text_scris,pozitiey_text_scris,String);
                continue;
            }
            else if(strchr(caractere_valide_litere,caracter)==0) continue;

            String[sfarsit_string]=caracter;
            String[sfarsit_string+1]=NULL;
            //outtextxy(pozitiex_text_scris,pozitiey_text_scris,String);//punere pe mai multe randuri
            int nrc2=0,j2=0,i2=0,nr_randuri=0;
            char temp2[MAX_VEC]= {0};
            while(String[nrc2+i2]!='\0') //punere pe mai multe randuri
            {
                if(i2==60)
                {
                    while(String[nrc2+i2]!=' ')
                        i2--;
                    for(j2=0; j2<i2; j2++)
                        temp2[j2]=String[nrc2+j2];
                    nrc2=nrc2+i2;
                    temp2[i2]='\0';
                    i2=0;
                    outtextxy(pozitiex_text_scris,pozitiey_text_scris+nr_randuri*40,temp2);
                    nr_randuri++;
                }
                i2++;
            }
            for(j2=0; j2<i2; j2++)
                temp2[j2]=String[nrc2+j2];
            nrc2=nrc2+i2;
            temp2[i2]='\0';
            i2=0;
            outtextxy(pozitiex_text_scris,pozitiey_text_scris+nr_randuri*40,temp2);
            sfarsit_string++;
        }

        while(1 && not_escaped)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                if(x<=156 && y<=140)
                {
                    not_escaped=0;
                    break;
                }
            }
        }
        eroare=0;
    }
    memset(vecCuv,NULL, sizeof vecCuv),k=0,ok=0, aFostcuvCheie=0,memset(rez,NULL, sizeof rez);
    meniuZecim();
}

void meniuCifBig ()
{
    settextstyle (text_style, HORIZ_DIR, text_size1);
    cleardevice ();
    setcolor(15);
    readimagefile ("scris.jpg", 0, 0, 1920, 1080);

    {
        char caracter,String[MAX_VEC]= {0};
        bool not_escaped = 1;
        short x, y;
        int sfarsit_string = 0;

        while ( kbhit () )getch ();
        while ( caracter != 13 || caracter != 27 )
        {

            caracter = getch ();
            if ( caracter == 13 )         //enter
            {
                int lungime = 0, lungime_totala = 0;
                char sir_auxiliar[MAX_VEC] = { 0 }, sir_complet[MAX_VEC] = { 0 }, sir_auxiliar2[MAX_VEC] = { 0 };
                settextstyle (text_style, HORIZ_DIR, text_size2);

                evaluare (String);
                citire_Big (String, vector1_bigint, lungime);
                lungime_totala = lungime;

                infix_to_postfix_Big (vector1_bigint, vector2_bigint, lungime_totala);
                numar1_bigint = eval_postfix_Big (vector2_bigint, lungime_totala);
                infix_to_prefix_Big (vector1_bigint, vector3_bigint, lungime);
                memorare_ro_sir_Big (vector3_bigint, lungime, sir_auxiliar);
                memorare_ro_Big (numar1_bigint, 1, numar1_bigint.v[0], sir_auxiliar2);

                strcat (sir_complet, sir_auxiliar);
                strcat (sir_complet, "este ");
                strcat (sir_complet, sir_auxiliar2);

                if ( eroare == 0 )
                {
                    settextstyle (text_style, HORIZ_DIR, text_size1);
                    int nrc=0,i=0,j=0;
                    char temp[MAX_VEC]= {0};
                    setcolor(3);
                    while(sir_complet[nrc+i]!='\0') // punere pe mai multe randuri
                    {
                        if(i==40)
                        {
                            while(sir_complet[nrc+i]!=' ')
                                i--;
                            for(j=0; j<i; j++)
                                temp[j]=sir_complet[nrc+j];
                            nrc=nrc+i;
                            temp[i]='\0';
                            i=0;
                            outtextxy(pozitiex_text_afisat,pozitiey_text_afisat+nrc*2-100,temp);
                        }
                        i++;
                    }
                    for(j=0; j<i; j++)
                        temp[j]=sir_complet[nrc+j];
                    nrc=nrc+i;
                    temp[i]='\0';
                    i=0;
                    outtextxy(pozitiex_text_afisat,pozitiey_text_afisat+nrc*2+20-100,temp);
                }
                else
                {
                    if ( eroare == 1 ) outtextxy (pozitiex_text_afisat, pozitiey_text_afisat, "EROARE: IMPARTIRE LA 0");
                    else if ( eroare ) outtextxy (pozitiex_text_afisat, pozitiey_text_afisat, "EROARE: SINTAXA GRESITA");
                }
                break;
            }
            else if ( caracter == 27 )         //escape
            {
                not_escaped = 0;
                break;
            }
            else if ( caracter == 8 )   //backspace
            {
                readimagefile ("scris.jpg", 0, 0, 1920, 1080);
                String[sfarsit_string - 1] = NULL;
                sfarsit_string--;
                outtextxy (pozitiex_text_scris, pozitiey_text_scris, String);
                continue;
            }
            else if ( strchr (caractere_valide_cifre, caracter) == 0 ) continue;

            String[sfarsit_string] = caracter;
            String[sfarsit_string + 1] = NULL;
            outtextxy (pozitiex_text_scris, pozitiey_text_scris, String);
            sfarsit_string++;
            if( sfarsit_string > limita_cifre )
            {
                setcolor(3);
                outtextxy (pozitiex_text_afisat, pozitiey_text_afisat, "EROARE: OPERATIE PREA LUNGA");
                break;
            }
        }

        while ( 1 && not_escaped )
        {
            if ( ismouseclick (WM_LBUTTONDOWN) )
            {
                clearmouseclick (WM_LBUTTONDOWN);
                x = mousex ();
                y = mousey ();
                if ( x <= 156 && y <= 140 )
                {
                    break;
                }
            }
        }

        clear_Big (numar1_bigint);
        clear_Big (numar2_bigint);
        clear_Big (numar3_bigint);
        for ( int i = 0; i <= 100; i++ )
        {
            clear_Big (vector1_bigint[i]);
            clear_Big (vector2_bigint[i]);
            clear_Big (vector3_bigint[i]);
        }
        eroare = 0;
    }
    meniuBig ();
}
void meniuCifZec ()
{
    settextstyle (text_style, HORIZ_DIR, text_size1);
    cleardevice ();
    setcolor(15);
    readimagefile ("scris.jpg", 0, 0, 1920, 1080);
    {
        char caracter,String[MAX_VEC] = { 0 } ;
        int sfarsit_string = 0;
        bool not_escaped = 1;
        short x, y;

        while ( kbhit () )getch ();
        while ( caracter != 13 || caracter != 27 )
        {

            caracter = getch ();
            if ( caracter == 13 )         //enter
            {
                int lungime = 0, lungime_totala = 0;
                char sir_auxiliar[MAX_VEC] = { 0 }, sir_complet[MAX_VEC] = { 0 }, sir_auxiliar2[MAX_VEC] = { 0 };
                settextstyle (text_style, HORIZ_DIR, text_size2);

                evaluare (String);
                citire_Real (String, vector1_real, lungime);
                lungime_totala = lungime;

                infix_to_postfix_Real (vector1_real, vector2_real, lungime_totala);
                rezultat_real = eval_postfix_Real (vector2_real, lungime_totala);
                infix_to_prefix_Real (vector1_real, vector3_real, lungime);
                memorare_ro_sir_Real (vector3_real, lungime, sir_auxiliar);
                memorare_ro_Real (rezultat_real, sir_auxiliar2);

                strcat (sir_complet, sir_auxiliar);
                strcat (sir_complet, "este ");
                strcat (sir_complet, sir_auxiliar2);

                if ( eroare == 0 )
                {
                    settextstyle (text_style, HORIZ_DIR, text_size1);
                    int nrc=0,i=0,j=0;
                    char temp[MAX_VEC]= {0};
                    setcolor(3);
                    while(sir_complet[nrc+i]!='\0') // punere pe mai multe randuri
                    {
                        if(i==40)
                        {
                            while(sir_complet[nrc+i]!=' ')
                                i--;
                            for(j=0; j<i; j++)
                                temp[j]=sir_complet[nrc+j];
                            nrc=nrc+i;
                            temp[i]='\0';
                            i=0;
                            outtextxy(pozitiex_text_afisat,pozitiey_text_afisat+nrc*2-100,temp);
                        }
                        i++;
                    }
                    for(j=0; j<i; j++)
                        temp[j]=sir_complet[nrc+j];
                    nrc=nrc+i;
                    temp[i]='\0';
                    i=0;
                    outtextxy(pozitiex_text_afisat,pozitiey_text_afisat+nrc*2+20-100,temp);
                }
                else
                {
                    if ( eroare == 1 ) outtextxy (pozitiex_text_afisat, pozitiey_text_afisat, "EROARE: IMPARTIRE LA 0");
                    else if ( eroare ) outtextxy (pozitiex_text_afisat, pozitiey_text_afisat, "EROARE: SINTAXA GRESITA");
                }
                break;
            }
            else if ( caracter == 27 )          //escape
            {
                not_escaped = 0;
                break;
            }
            else if ( caracter == 8 )          //backspace
            {
                readimagefile ("scris.jpg", 0, 0, 1920, 1080);
                String[sfarsit_string - 1] = NULL;
                sfarsit_string--;
                outtextxy (pozitiex_text_scris, pozitiey_text_scris, String);
                continue;
            }
            else if ( strchr (caractere_valide_cifre, caracter) == 0 ) continue;

            String[sfarsit_string] = caracter;
            String[sfarsit_string + 1] = NULL;
            outtextxy (pozitiex_text_scris, pozitiey_text_scris, String);
            sfarsit_string++;
            if (sfarsit_string > limita_cifre )
            {
                setcolor(3);
                outtextxy (pozitiex_text_afisat, pozitiey_text_afisat, "EROARE: OPERATIE PREA LUNGA");
                break;
            }
        }

        while ( 1 && not_escaped )
        {
            if ( ismouseclick (WM_LBUTTONDOWN) )
            {
                clearmouseclick (WM_LBUTTONDOWN);
                x = mousex ();
                y = mousey ();
                if ( x <= 156 && y <= 140 )
                {
                    break;
                }
            }
        }

        for ( int i = 0; i <= 99; i++ )
        {
            vector1_real[i].n = 0;
            vector2_real[i].n = 0;
            vector3_real[i].n = 0;
            vector1_real[i].operatie = 0;
            vector2_real[i].operatie = 0;
            vector3_real[i].operatie = 0;
        }
        rezultat_real.n = 0;
        rezultat_real.operatie = 0;
        eroare = 0;
    }

    meniuZecim();
}

void meniuBig()
{
    short x,y;
    cleardevice();
    readimagefile("zecim.jpg",0,0,1920,1080);

    while(1)
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x<=156 && y<=140) meniu2();
            else if(x>=623 && x<=1247 && y>=280 && y<=389) meniuLitBig();
            else if(x>=623 && x<=1247 && y>=545 && y<=654) meniuCifBig();
        }
}
void meniuZecim()
{
    short x,y;
    cleardevice();
    readimagefile("zecim.jpg",0,0,1920,1080);

    while(1)
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x<=156 && y<=140) meniu2();
            else if(x>=623 && x<=1247 && y>=280 && y<=389) meniuLitZec();
            else if(x>=623 && x<=1247 && y>=545 && y<=654) meniuCifZec();
        }
}

void meniu2()
{
    short x,y;
    setbkcolor(0);
    cleardevice();
    settextstyle(text_style,HORIZ_DIR,text_size1);
    setcolor(15);
    readimagefile("meniu2.jpg",0,0,1920,1080);

    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>=342 && x<=1558 && y>=280 && y<=390)
                meniuZecim();
            else if(x>=342 && x<=1558 && y>=514 && y<=623)
                meniuBig();
            else if(x<=156 && y<=140)
                meniu1();
        }
    }
}
void meniu1()
{
    int windowS;
    short startJoc=0;
    short x,y;
    windowS=initwindow(1920,1080,"CalcRO",true);
    settextstyle(text_style,HORIZ_DIR,text_size1);
    cleardevice();
    readimagefile("Start2.jpg",0,0,1920,1080);

    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>=1800&& y<=125) exit(0);
            else if(x>=1800 && y>=140 && y<=245) muzica(windowS);
            else if(x>=1452 && x<=1699 && y>=997) despre(windowS);
            else if(x>=1698 && y>=997) ajutor(windowS);
            else if(x<=420 && y>=955) meniu2();
        }
    }
}

void muzica (int windowS)
{
    int windowM, x, y;
    windowM = initwindow (835, 450, "Muzica");
    readimagefile ("muz.jpg", 0, 0, 835, 450);
    rectangle (150, 130, 425, 300);
    rectangle (425, 130, 700, 300);

    while ( 1 )
    {
        if ( ismouseclick (WM_LBUTTONDOWN) )
        {
            clearmouseclick (WM_LBUTTONDOWN);
            x = mousex ();
            y = mousey ();
            if ( x >= 150 && x <= 425 && y >= 130 && y <= 300 ) PlaySound (TEXT ("background_music.wav"), NULL, SND_FILENAME | SND_ASYNC);
            else if ( x >= 425 && x <= 700 ) PlaySound (TEXT ("background_music2.wav"), NULL, SND_FILENAME | SND_ASYNC);
            else if ( x >= 775 && y >= 75 && y <= 150 )PlaySound (NULL, NULL, SND_ASYNC);
            else if ( x >= 775 && y <= 75 )
            {
                closegraph (windowM);
                setcurrentwindow (windowS);
                return;
            }
        }
    }
}

void ajutor(int windowS){
    int windowA, x, y;
    bool click=false;
    windowA=initwindow(1035,650,"Ajutor");
    readimagefile("ajutor.jpg",0,0,1035,650);
    do{
        if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex(); y=mousey();
            if(x>=935 && y<=75) {
                click=true;
                closegraph(windowA);
            }
        }
    }while(!click);
    setcurrentwindow(windowS);
}
void despre (int windowS)
{
    int windowD, x, y;
    windowD = initwindow (1035, 650, "Despre");
    readimagefile ("despre.jpg", 0, 0, 1035, 650);

    while ( 1 )
    {
        if ( ismouseclick (WM_LBUTTONDOWN) )
        {
            clearmouseclick (WM_LBUTTONDOWN);
            x = mousex ();
            y = mousey ();
            if ( x >= 935 && y <= 75 )
            {
                closegraph (windowD);
                setcurrentwindow (windowS);
                return;
            }
        }
    }
}

/////////////////////////////////////////////

// converteste un int in BigInt
void conversie (long long int x, BigInt& numar)
{
    long long int putere = 1;
    int numar_cif = 1;
    if ( x < 0 )
    {
        numar.semn = 1;
        x = -x;
    }
    while ( x >= putere )
    {
        putere *= 10;
        numar_cif++;
    }
    numar_cif--;
    numar.v[0] = numar_cif;
    while ( numar_cif )
    {
        numar.v[numar_cif--] = x % 10;
        x /= 10;
    }
}

// Adauga cifra x la stanga numarului
void add_left_Big (BigInt& numar, int x)
{
    for ( int i = 1; i <= numar.v[0]; i++ ) numar.v[i + 1] = numar.v[i];
    numar.v[1] = x;
    numar.v[0]++;
}
// Adauga cifra x la dreapta numarului
void add_right_Big (BigInt& numar, int x)
{
    if ( numar.v[0] == 0 && x == 0 ) return;
    numar.v[0]++;
    numar.v[numar.v[0]] = x;
}

// Face ca toate valorile unui BigInt sa fie 0
void clear_Big (BigInt& numar)
{
    for ( int i = 0; i < 100; i++ ) numar.v[i] = 0;
    numar.semn = 0;
    numar.operatie = 0;
}

//Compara doua BigInt
bool mai_mare_Big (BigInt numar1, BigInt numar2)
{
    if ( numar1.v[0] > numar2.v[0] ) return 1;
    if ( numar2.v[0] > numar1.v[0] ) return 0;
    for ( int i = 1; i <= numar1.v[0]; i++ )
    {
        if ( numar1.v[i] == numar2.v[i] ) continue;
        return ( numar1.v[i] > numar2.v[i] );
    }
    return 0;
}


//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de BigInt
void citire_Big (char sir[], BigInt vector[], int& lungime)
{
    int pozitie = 1;
    bool operatie = 0; //doi operatori unul dupa altul
    for ( int i = 0; i <= strlen (sir); i++ )
    {
        if ( sir[i] >= 48 && sir[i] <= 57 )   //cifra
        {
            operatie = 0;
            if ( vector[pozitie].operatie ) pozitie++;
            add_right_Big (vector[pozitie], ( (int)sir[i] - '0' ));
        }
        else if ( sir[i] == '+' )
        {
            if ( operatie == 1 )
            {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 1;// +
        }
        else if ( sir[i] == '-' )
        {
            if ( operatie == 1 )
            {
                if ( vector[pozitie + 1].semn == 1 )
                {
                    fout << "EROARE DE SINTAXA";
                    break;
                }
                vector[pozitie + 1].semn = 1;
            }
            else
            {
                operatie = 1;
                pozitie++;
                vector[pozitie].operatie = 2; // -
            }
        }
        else if ( sir[i] == '*' || sir[i] == 'x' )
        {
            if ( operatie == 1 )
            {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 3; // * x
        }
        else if ( sir[i] == '/' || sir[i] == ':' )
        {
            if ( operatie == 1 )
            {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 4; // / :
        }
        else if ( sir[i] == '(' )
        {
            if ( pozitie != 1 ) pozitie++;
            vector[pozitie].operatie = 6; // (
        }
        else if ( sir[i] == ')' )
        {
            if ( pozitie != 1 ) pozitie++;
            vector[pozitie].operatie = 7; // )
        }
    }
    lungime = pozitie;
}
//Parseaza un sir de caractere si salveaza numerele si operatiile intr-un vector de Real
void citire_Real (char sir[], Real vector[], int& lungime)
{

    int pozitie = 1;
    bool operatie = 0; //doi operatori unul dupa altul
    for ( int i = 0; i <= strlen (sir); i++ )
    {
        if ( sir[i] >= 48 && sir[i] <= 57 )   //cifra
        {
            operatie = 0;
            if ( vector[pozitie].operatie ) pozitie++;
            vector[pozitie].n = vector[pozitie].n * 10 + ( (int)sir[i] - '0' ); //adaug cifra la dreapta numarului
        }
        else if ( sir[i] == '+' )
        {
            if ( operatie == 1 )
            {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 1;// +
        }
        else if ( sir[i] == '-' )
        {
            if ( operatie == 1 )
            {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 2; // -

        }
        else if ( sir[i] == '*' || sir[i] == 'x' )
        {
            if ( operatie == 1 )
            {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 3; // * x
        }
        else if ( sir[i] == '/' || sir[i] == ':' )
        {
            if ( operatie == 1 )
            {
                fout << "EROARE DE SINTAXA";
                break;
            }
            operatie = 1;
            pozitie++;
            vector[pozitie].operatie = 4; // / :
        }
        else if ( sir[i] == '(' )
        {
            if ( pozitie != 1 ) pozitie++;
            vector[pozitie].operatie = 6; // (
        }
        else if ( sir[i] == ')' )
        {
            if ( pozitie != 1 ) pozitie++;
            vector[pozitie].operatie = 7; // )
        }
    }
    lungime = pozitie;
}

// Afiseaza un BigInt in cifre
void afisare_Big (BigInt numar)
{
    if ( numar.operatie )
    {
        fout << sir_operatori[numar.operatie];
    }
    else
    {
        if ( numar.v[0] == 0 )
        {
            fout << '0';
            return;
        }
        if ( numar.semn ) fout << '-';
        for ( int i = 1; i <= numar.v[0]; i++ )
        {
            fout << numar.v[i];
        }
    }
}

//Afiseaza un numar Real
void afisare_Real (Real x)
{
    if ( x.operatie ) fout << sir_operatori[x.operatie];
    else fout << setprecision (6) << x.n;
}

//Afiseaza un BigInt in litere (se apeleaza astfel: afisare_ro_Big (numar, 1 , numar.v[0]) )
void afisare_ro_Big (BigInt numar, int poz, int pas)
{
    if ( numar.operatie )
    {
        if ( numar.operatie == 1 ) fout << "plus ";
        else if ( numar.operatie == 2 ) fout << "minus ";
        else if ( numar.operatie == 3 ) fout << "ori ";
        else if ( numar.operatie == 4 ) fout << "impartit la ";
        return;
    }
    if ( numar.v[0] == 0 )
    {
        fout << "zero ";
        return;
    }
    if ( numar.semn )
    {
        fout << "minus ";
        numar.semn = 0;
    }
    if ( pas == 1 )                                     //pozitia unitatilor
    {
        if ( numar.v[poz] ) fout << sir_cifre_mari[numar.v[poz] - 1] << ' ';
    }
    else if ( pas == 2 )                                //pozitia zecilor
    {
        if ( numar.v[poz] == 0 )
        {
            afisare_ro_Big (numar, poz + 1, 1);
        }
        else if ( numar.v[poz] == 1 )                   //10-19
        {
            fout << sir_cifre_mari[numar.v[poz + 1] + 9] << ' ';
        }
        else                                            //20-99
        {
            fout << sir_cifre_mari[numar.v[poz] + 17] << ' ';
            if ( numar.v[poz + 1] ) fout << "si " << sir_cifre_mari[numar.v[poz + 1] - 1] << ' ';
        }
    }
    else if ( pas == 3 )                                //pozitia sutelor
    {
        if ( numar.v[poz] == 0 )
        {
            afisare_ro_Big (numar, poz + 1, 2);
        }
        else if ( numar.v[poz] == 1 )                   //100-199
        {
            fout << sir_cifre_mari[27] << ' ';
            afisare_ro_Big (numar, poz + 1, 2);
        }
        else                                            //200-999
        {
            if ( numar.v[poz] == 2 ) fout << "doua ";
            else fout << sir_cifre_mari[numar.v[poz] - 1] << ' ';
            fout << sir_cifre_mari[28] << ' ';
            afisare_ro_Big (numar, poz + 1, 2);
        }
    }
    else if ( ( pas - 1 ) % 3 == 0 )                    //unitate
    {
        if ( numar.v[poz] == 0 )
        {
            afisare_ro_Big (numar, poz + 1, pas - 1);
        }
        else if ( numar.v[poz] == 1 )
        {
            fout << sir_cifre_mari[pas / 3 * 2 + 27] << ' ';
            afisare_ro_Big (numar, poz + 1, pas - 1);
        }
        else
        {
            if ( numar.v[poz] == 2 )
            {
                fout << "doua " << sir_cifre_mari[pas / 3 + 28] << ' ';
            }
            else if ( numar.v[poz] )
            {
                fout << sir_cifre_mari[numar.v[poz] - 1] << ' ';
                fout << sir_cifre_mari[pas / 3 * 2 + 28] << ' ';
            }
            afisare_ro_Big (numar, poz + 1, pas - 1);
        }
    }
    else if ( ( pas - 2 ) % 3 == 0 )                    //zeci
    {
        if ( numar.v[poz] == 0 )
        {
            afisare_ro_Big (numar, poz + 1, pas - 1);
        }
        else if ( numar.v[poz] == 1 )
        {
            afisare_ro_Big (numar, poz, 2);
            if ( numar.v[poz] )
            {
                fout << ' ' << sir_cifre_mari[pas / 3 * 2 + 28] << ' ';
            }
            afisare_ro_Big (numar, poz + 2, pas - 2);
        }
        else
        {
            afisare_ro_Big (numar, poz, 2);
            if ( numar.v[poz] )
            {
                fout << "de " << sir_cifre_mari[pas / 3 * 2 + 28] << ' ';
            }
            afisare_ro_Big (numar, poz + 2, pas - 2);
        }
    }
    else                                                //sute
    {
        if ( numar.v[poz] == 0 )
        {
            afisare_ro_Big (numar, poz + 1, pas - 1);
        }
        else if ( numar.v[poz] == 1 )
        {
            afisare_ro_Big (numar, poz, 3);
            if ( numar.v[poz] )
            {
                fout << "de " << sir_cifre_mari[pas / 3 * 2 + 26] << ' ';
            }
            afisare_ro_Big (numar, poz + 3, pas - 3);
        }
        else
        {
            afisare_ro_Big (numar, poz, 3);
            if ( numar.v[poz] )
            {
                fout << "de " << sir_cifre_mari[pas / 3 * 2 + 26] << ' ';
            }
            afisare_ro_Big (numar, poz + 3, pas - 3);
        }
    }
}
//Memoreaza un BigInt intr-un sir de caractere
void memorare_ro_Big (BigInt numar, int poz, int pas, char sir_caractere[])
{
    if ( numar.operatie )
    {
        if ( numar.operatie == 1 ) strcat (sir_caractere, "plus ");
        else if ( numar.operatie == 2 ) strcat (sir_caractere, "minus ");
        else if ( numar.operatie == 3 ) strcat (sir_caractere, "ori ");
        else if ( numar.operatie == 4 ) strcat (sir_caractere, "impartit la ");
        else if ( numar.operatie == 5 ) strcat (sir_caractere, "egal ");
        return;
    }
    else
    {
        if ( numar.v[0] == 0 )
        {
            strcat (sir_caractere, "zero ");
            return;
        }
        if ( numar.semn )
        {
            strcat (sir_caractere, "minus ");
            numar.semn = 0;
        }
        if ( pas == 1 )                                     //pozitia unitatilor
        {
            if ( numar.v[poz] )
            {
                strcat (sir_caractere, sir_cifre_mari[numar.v[poz] - 1]);
                strcat (sir_caractere, " ");
            }
        }
        else if ( pas == 2 )                                //pozitia zecilor
        {
            if ( numar.v[poz] == 0 )
            {
                memorare_ro_Big (numar, poz + 1, 1, sir_caractere);
            }
            else if ( numar.v[poz] == 1 )                   //10-19
            {
                strcat (sir_caractere, sir_cifre_mari[numar.v[poz + 1] + 9]);
                strcat (sir_caractere, " ");
            }
            else                                            //20-99
            {
                strcat (sir_caractere, sir_cifre_mari[numar.v[poz] + 17]);
                strcat (sir_caractere, " ");
                if ( numar.v[poz + 1] )
                {
                    strcat (sir_caractere, "si ");
                    strcat (sir_caractere, sir_cifre_mari[numar.v[poz + 1] - 1]);
                    strcat (sir_caractere, " ");
                }
            }
        }
        else if ( pas == 3 )                                //pozitia sutelor
        {
            if ( numar.v[poz] == 0 )
            {
                memorare_ro_Big (numar, poz + 1, 2, sir_caractere);
            }
            else if ( numar.v[poz] == 1 )                   //100-199
            {
                strcat (sir_caractere, sir_cifre_mari[27]);
                strcat (sir_caractere, " ");
                memorare_ro_Big (numar, poz + 1, 2, sir_caractere);
            }
            else                                            //200-999
            {
                if ( numar.v[poz] == 2 )
                {
                    strcat (sir_caractere, "doua ");
                }
                else
                {
                    strcat (sir_caractere, sir_cifre_mari[numar.v[poz] - 1]);
                    strcat (sir_caractere, " ");
                }
                strcat (sir_caractere, sir_cifre_mari[28]);
                strcat (sir_caractere, " ");
                memorare_ro_Big (numar, poz + 1, 2, sir_caractere);
            }
        }
        else if ( ( pas - 1 ) % 3 == 0 )                    //unitate
        {
            if ( numar.v[poz] == 0 )
            {
                memorare_ro_Big (numar, poz + 1, pas - 1, sir_caractere);
            }
            else if ( numar.v[poz] == 1 )
            {
                strcat (sir_caractere, sir_cifre_mari[pas / 3 * 2 + 27]);
                strcat (sir_caractere, " ");
                memorare_ro_Big (numar, poz + 1, pas - 1, sir_caractere);
            }
            else
            {
                if ( numar.v[poz] == 2 )
                {
                    strcat (sir_caractere, "doua ");
                    strcat (sir_caractere, sir_cifre_mari[pas / 3 * 2 + 28]);
                    strcat (sir_caractere, " ");
                }
                else if ( numar.v[poz] )
                {
                    strcat (sir_caractere, sir_cifre_mari[numar.v[poz] - 1]);
                    strcat (sir_caractere, " ");
                    strcat (sir_caractere, sir_cifre_mari[pas / 3 * 2 + 28]);
                    strcat (sir_caractere, " ");
                }
                memorare_ro_Big (numar, poz + 1, pas - 1, sir_caractere);
            }
        }
        else if ( ( pas - 2 ) % 3 == 0 )                    //zeci
        {
            if ( numar.v[poz] == 0 )
            {
                memorare_ro_Big (numar, poz + 1, pas - 1, sir_caractere);
            }
            else if ( numar.v[poz] == 1 )
            {
                memorare_ro_Big (numar, poz, 2, sir_caractere);
                if ( numar.v[poz] )
                {
                    strcat (sir_caractere, " ");
                    strcat (sir_caractere, sir_cifre_mari[pas / 3 * 2 + 28]);
                    strcat (sir_caractere, " ");
                }
                memorare_ro_Big (numar, poz + 2, pas - 2, sir_caractere);
            }
            else
            {
                memorare_ro_Big (numar, poz, 2, sir_caractere);
                if ( numar.v[poz] )
                {
                    strcat (sir_caractere, "de ");
                    strcat (sir_caractere, sir_cifre_mari[pas / 3 * 2 + 28]);
                    strcat (sir_caractere, " ");
                }
                memorare_ro_Big (numar, poz + 2, pas - 2, sir_caractere);
            }
        }
        else                                                //sute
        {
            if ( numar.v[poz] == 0 )
            {
                memorare_ro_Big (numar, poz + 1, pas - 1, sir_caractere);
            }
            else if ( numar.v[poz] == 1 )
            {
                memorare_ro_Big (numar, poz, 3, sir_caractere);
                if ( numar.v[poz] )
                {
                    strcat (sir_caractere, "de ");
                    strcat (sir_caractere, sir_cifre_mari[pas / 3 * 2 + 26]);
                    strcat (sir_caractere, " ");
                }
                memorare_ro_Big (numar, poz + 3, pas - 3, sir_caractere);
            }
            else
            {
                memorare_ro_Big (numar, poz, 3, sir_caractere);
                if ( numar.v[poz] )
                {
                    strcat (sir_caractere, "de ");
                    strcat (sir_caractere, sir_cifre_mari[pas / 3 * 2 + 26]);
                    strcat (sir_caractere, " ");
                }
                memorare_ro_Big (numar, poz + 3, pas - 3, sir_caractere);
            }
        }
    }
}

//Afiseaza un Real in litere
void afisare_ro_Real (Real x)
{
    double intreg, fractionar;
    BigInt intregB, fractionarB;
    int precizie = 1;

    fractionar = modf (x.n, &intreg);

    fractionar *= 10;
    while ( (int)fractionar > 0 && precizie < 7 )
    {
        add_right_Big (fractionarB, (int)fractionar);
        fractionar -= (int)fractionar;
        fractionar *= 10;
        precizie++;
    }

    conversie (intreg, intregB);
    afisare_ro_Big (intregB, 1, intregB.v[0]);
    if ( fractionarB.v[0] )
    {
        fout << "virgula ";
        afisare_ro_Big (fractionarB, 1, fractionarB.v[0]);
    }
}
//Memoreaza un Real intr-un sir de caractere
void memorare_ro_Real (Real x, char sir_caractere[])
{
    double intreg, fractionar;
    BigInt intregB, fractionarB;
    int precizie = 1;

    fractionar = modf (x.n, &intreg);

    fractionar *= 10;
    while ( (int)fractionar > 0 && precizie < 7 )
    {
        add_right_Big (fractionarB, (int)fractionar);
        fractionar -= (int)fractionar;
        fractionar *= 10;
        precizie++;
    }
    char auxiliar[MAX_VEC] = { 0 };
    conversie (intreg, intregB);
    memorare_ro_Big (intregB, 1, intregB.v[0], auxiliar);
    strcat (sir_caractere, auxiliar);
    if ( fractionarB.v[0] )
    {
        char auxiliar2[MAX_VEC] = { 0 };
        strcat (sir_caractere, "virgula ");
        memorare_ro_Big (fractionarB, 1, fractionarB.v[0], auxiliar2);
        strcat (sir_caractere, auxiliar2);
    }
}

//Traduce un vector de BigInt in limba romana (vecotrul trebuie sa aiba forma prefixata)
void afisare_ro_sir_Big (BigInt vector[], int lungime)
{
    int ultima_operatie = 5, penultima_operatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- )
    {
        if ( vector[i].operatie )
        {
            if ( vector[i].operatie == 1 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 1;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "suma dintre ";
            }
            else if ( vector[i].operatie == 2 )
            {

                penultima_operatie = ultima_operatie;
                ultima_operatie = 2;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "diferenta dintre ";
            }
            else if ( vector[i].operatie == 3 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 3;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "produsul dintre ";
            }
            else if ( vector[i].operatie == 4 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 4;
                impartire = 1;
            }
        }
        else                                                                        //numar
        {
            if ( i != 1 )
            {
                afisare_ro_Big (vector[i], 1, vector[i].v[0]);
                if ( impartire == 0 )
                {
                    if ( vector[i - 1].operatie != ultima_operatie ) fout << "si ";
                    else fout << ',';
                }
            }
            else afisare_ro_Big (vector[i], 1, vector[i].v[0]);
            if ( impartire )
            {
                fout << "impartit la ";
            }
            impartire = 0;
        }
    }
}
//Traduce un vector de BigInt in limba romana si il pune intr-un sir de caractere (vecotrul trebuie sa aiba forma prefixata)
void memorare_ro_sir_Big (BigInt vector[], int lungime, char sir_caractere[])
{
    int ultima_operatie = 5, penultima_operatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- )
    {
        if ( vector[i].operatie )
        {
            if ( vector[i].operatie == 1 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 1;
                if ( ultima_operatie == penultima_operatie );
                else
                {
                    strcat (sir_caractere, "suma dintre ");
                }
            }
            else if ( vector[i].operatie == 2 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 2;
                if ( ultima_operatie == penultima_operatie );
                else
                {
                    strcat (sir_caractere, "diferenta dintre ");
                }
            }
            else if ( vector[i].operatie == 3 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 3;
                if ( ultima_operatie == penultima_operatie );
                else
                {
                    strcat (sir_caractere, "produsul dintre ");
                }
            }
            else if ( vector[i].operatie == 4 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 4;
                impartire = 1;
            }
        }
        else                                                                        //numar
        {
            if ( i != 1 )
            {
                char auxiliar[MAX_VEC] = { 0 };
                memorare_ro_Big (vector[i], 1, vector[i].v[0], auxiliar);
                strcat (sir_caractere, auxiliar);
                if ( impartire == 0 )
                {
                    if ( vector[i - 1].operatie != ultima_operatie )
                    {
                        strcat (sir_caractere, "si ");
                    }
                    else
                    {
                        strcat (sir_caractere, ",");
                    }
                }
            }
            else
            {
                char auxiliar[MAX_VEC] = { 0 };
                memorare_ro_Big (vector[i], 1, vector[i].v[0], auxiliar);
                strcat (sir_caractere, auxiliar);
            }
            if ( impartire )
            {
                strcat (sir_caractere, "impartit la ");
            }
            impartire = 0;
        }
    }
}

//Traduce un vector de Real in limba romana (vecotrul trebuie sa aiba forma prefixata)
void afisare_ro_sir_Real (Real vector[], int lungime)
{
    int ultima_operatie = 5, penultima_operatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- )
    {
        if ( vector[i].operatie )
        {
            if ( vector[i].operatie == 1 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 1;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "suma dintre ";
            }
            else if ( vector[i].operatie == 2 )
            {

                penultima_operatie = ultima_operatie;
                ultima_operatie = 2;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "diferenta dintre ";
            }
            else if ( vector[i].operatie == 3 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 3;
                if ( ultima_operatie == penultima_operatie );
                else
                    fout << "produsul dintre ";
            }
            else if ( vector[i].operatie == 4 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 4;
                impartire = 1;
            }
        }
        else                                                                        //numar
        {
            if ( i != 1 )
            {
                afisare_ro_Real (vector[i]);
                if ( impartire == 0 )
                {
                    if ( vector[i - 1].operatie != ultima_operatie ) fout << "si ";
                    else fout << ',';
                }
            }
            else afisare_ro_Real (vector[i]);
            if ( impartire )
            {
                fout << "impartit la ";
            }
            impartire = 0;
        }
    }
}
//Traduce un vector de Real in limba romana si il pune intr-un sir de caractere (vecotrul trebuie sa aiba forma prefixata)
void memorare_ro_sir_Real (Real vector[], int lungime, char sir_caractere[])
{
    int ultima_operatie = 5, penultima_operatie = 6;
    bool impartire = 0;
    for ( int i = lungime; i > 0; i-- )
    {
        if ( vector[i].operatie )
        {
            if ( vector[i].operatie == 1 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 1;
                if ( ultima_operatie == penultima_operatie );
                else
                {
                    strcat (sir_caractere, "suma dintre ");
                }
            }
            else if ( vector[i].operatie == 2 )
            {

                penultima_operatie = ultima_operatie;
                ultima_operatie = 2;
                if ( ultima_operatie == penultima_operatie );
                else
                {
                    strcat (sir_caractere, "diferenta dintre ");
                }
            }
            else if ( vector[i].operatie == 3 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 3;
                if ( ultima_operatie == penultima_operatie );
                else
                {
                    strcat (sir_caractere, "produsul dintre ");
                }
            }
            else if ( vector[i].operatie == 4 )
            {
                penultima_operatie = ultima_operatie;
                ultima_operatie = 4;
                impartire = 1;
            }
        }
        else                                                                        //numar
        {
            if ( i != 1 )
            {
                char auxiliar[MAX_VEC] = { 0 };
                memorare_ro_Real (vector[i], auxiliar);
                strcat (sir_caractere, auxiliar);
                if ( impartire == 0 )
                {
                    if ( vector[i - 1].operatie != ultima_operatie ) strcat (sir_caractere, "si ");
                    else strcat (sir_caractere, ",");
                }
            }
            else
            {
                char auxiliar[MAX_VEC]= { 0 };
                memorare_ro_Real (vector[i], auxiliar);
                strcat (sir_caractere, auxiliar);
            }
            if ( impartire )
            {
                strcat (sir_caractere, "impartit la ");
            }
            impartire = 0;
        }
    }
}


// Calculeaza suma a doua BigInt
void adunare_Big (BigInt& numar1, BigInt& numar2, BigInt& rezultat)
{
    if ( numar1.semn > numar2.semn )                            //(-a) + b = b - a
    {
        numar1.semn = 0;
        scadere_Big (numar2, numar1, rezultat);
        numar1.semn = 1;
        return;
    }
    else if ( numar1.semn < numar2.semn )                       //a + (-b) = a - b
    {
        numar2.semn = 0;
        scadere_Big (numar1, numar2, rezultat);
        numar2.semn = 1;
        return;
    }
    else if ( numar1.semn ) rezultat.semn = 1;                  // (-a) + (-b) = -(a + b)
    else rezultat.semn = 0;                                     // a + b = a + b
    int lungime, carry = 0;
    if ( numar1.v[0] >= numar2.v[0] )
    {
        lungime = numar1.v[0] - numar2.v[0];
        for ( int i = numar2.v[0]; i >= 1; i-- )
        {
            rezultat.v[i + lungime] = numar1.v[i + lungime] + numar2.v[i] + carry;
            carry = 0;
            if ( rezultat.v[i + lungime] > 9 )
            {
                rezultat.v[i + lungime] %= 10;
                carry = 1;
            }
        }
        for ( int i = lungime; i >= 1; i-- )
        {
            rezultat.v[i] = numar1.v[i] + carry;
            carry = 0;
            if ( rezultat.v[i] > 9 )
            {
                rezultat.v[i] %= 10;
                carry = 1;
            }
        }
        if ( carry )
        {
            for ( int i = numar1.v[0] + 1; i >= 1; i-- ) rezultat.v[i + 1] = rezultat.v[i];
            rezultat.v[1] = 1;
            rezultat.v[0] = numar1.v[0] + 1;
        }
        else rezultat.v[0] = numar1.v[0];
    }
    else adunare_Big (numar2, numar1, rezultat);
}

// Calculeaza diferenta a doua BigInt
void scadere_Big (BigInt& numar1, BigInt& numar2, BigInt& rezultat)
{
    if ( numar1.semn < numar2.semn )                 // a - (-b) = a + b
    {
        numar2.semn = 0;
        adunare_Big (numar1, numar2, rezultat);
        numar2.semn = 1;
        return;
    }
    else if ( numar1.semn > numar2.semn )           // (-a) - b = -(a + b)
    {
        numar1.semn = 0;
        adunare_Big (numar1, numar2, rezultat);
        numar1.semn = 1;
        rezultat.semn = 1;
        return;
    }
    else if ( numar1.semn )                       // (-a) - (-b) = b - a
    {
        numar2.semn = 0;
        numar1.semn = 0;
        scadere_Big (numar2, numar1, rezultat);
        numar2.semn = 1;
        numar1.semn = 1;
        return;
    }                                            // a - b = a - b
    if ( numar2.v[0] > numar1.v[0] ) scadere_secundara_Big (numar2, numar1, rezultat, 1);    //b>a
    else if ( numar1.v[0] == numar2.v[0] )
    {
        int ok = 0;
        for ( int i = 1; i <= numar1.v[0]; i++ )
        {
            if ( numar1.v[i] > numar2.v[i] )
            {
                scadere_secundara_Big (numar1, numar2, rezultat, 0);                              //a>b
                break;
            }
            else if ( numar2.v[i] > numar1.v[i] )
            {
                scadere_secundara_Big (numar2, numar1, rezultat, 1);                      //b>a
                break;
            }
        }
    }
    else scadere_secundara_Big (numar1, numar2, rezultat, 0);                                   //a>b
}
// Functie secundara pentru scadere, calculeaza propiu-zis diferenta a doua numere pozitive primul avand mai multe cifre
void scadere_secundara_Big (BigInt& numar1, BigInt& numar2, BigInt& rezultat, bool semn)
{
    int lungime, carry = 0, contor_zero = 0;
    lungime = numar1.v[0] - numar2.v[0];
    for ( int i = numar2.v[0]; i >= 1; i-- )
    {
        rezultat.v[i + lungime] = numar1.v[i + lungime] - numar2.v[i] - carry;
        carry = 0;
        if ( rezultat.v[i + lungime] < 0 )
        {
            rezultat.v[i + lungime] += 10;
            carry = 1;
        }
    }
    for ( int i = lungime; i >= 1; i-- )
    {
        rezultat.v[i] = numar1.v[i] - carry;
        carry = 0;
        if ( rezultat.v[i] < 0 )
        {
            rezultat.v[i] += 10;
            carry = 1;
        }
    }
    for ( int i = 1; i <= numar1.v[0]; i++ )
    {
        if ( rezultat.v[i] ) break;
        contor_zero++;
    }
    rezultat.v[0] = numar1.v[0] - contor_zero;
    for ( int i = 1; i <= numar1.v[0]; i++ ) rezultat.v[i] = rezultat.v[i + contor_zero];
    rezultat.semn = semn;
}

//Inumlteste doua BigInt
void inmultire_Big (BigInt& numar1, BigInt& numar2, BigInt& rezultat)
{
    BigInt rezultat_auxiliar;
    for ( int i = 1; i <= numar2.v[0]; i++ )
    {
        BigInt auxiliar;
        inmultire_secundara_Big (numar1, numar2.v[( numar2.v[0] - i + 1 )], auxiliar, i - 1);
        adunare_Big (rezultat, auxiliar, rezultat_auxiliar);
        rezultat = rezultat_auxiliar;
    }
    if ( numar1.semn != numar2.semn ) rezultat.semn = 1; // a * (-b) || (-a) * b
    else rezultat.semn = 0;                             // a * b || (-a) * (-b)
}
//Functie secundara pentru inmultire, calculeaza produsul dintre un BigInt si o cifra si adauga un numar specificat de zerouri
void inmultire_secundara_Big (BigInt& numar1, int cifra, BigInt& rezultat, int zero)
{
    if ( cifra < 0 )                 // a * -x = -ax
    {
        cifra = -cifra;
        rezultat.semn = 1;
    }
    int carry = 0;
    for ( int i = numar1.v[0]; i >= 1; i-- )
    {
        rezultat.v[i] = numar1.v[i] * cifra + carry;
        carry = 0;
        if ( rezultat.v[i] > 9 )
        {
            carry = rezultat.v[i] / 10;
            rezultat.v[i] %= 10;
        }
    }
    if ( carry )
    {
        for ( int i = numar1.v[0] + 1; i >= 1; i-- ) rezultat.v[i + 1] = rezultat.v[i];
        rezultat.v[1] = carry;
        rezultat.v[0] = numar1.v[0] + 1;
    }
    else rezultat.v[0] = numar1.v[0];
    for ( int i = numar1.v[0] + 2; i <= numar1.v[0] + 1 + zero; i++ ) rezultat.v[i] = 0;
    rezultat.v[0] += zero;
}

//Calculeaza catul impartirii naturale a doua BigInt
void impartire_Big (BigInt deimpartit, BigInt impartitor, BigInt& cat)
{
    if ( impartitor.v[0] == 0 )
    {
        eroare = 1;
        return;
    }
    BigInt suma, cat_auxiliar, adunare_cat;
    int putere = 1, preamare = 1;
    adunare_cat.v[1] = 1;
    while ( putere > 0 )
    {
        BigInt auxiliar_suma;
        adunare_Big (suma, impartitor, auxiliar_suma);
        if ( mai_mare_Big (auxiliar_suma, deimpartit) )
        {
            putere--;
            impartitor.v[0]--;
            preamare = 0;
        }
        else
        {
            suma = auxiliar_suma;
            BigInt auxiliar_cat;
            adunare_cat.v[0] = putere;
            adunare_Big (cat_auxiliar, adunare_cat, auxiliar_cat);
            cat_auxiliar = auxiliar_cat;
            if ( preamare )
            {
                putere++;
                impartitor.v[0]++;
            }
        }
    }
    cat = cat_auxiliar;
}

//Imparte un BigInt la o cifra  (nefolosit)
void impartire_secundara_Big (BigInt& nr1, int x, BigInt& nr2)
{
    int div = 0, poz = 1;
    if ( nr1.semn == 0 && x < 0 ) nr2.semn = 1;
    else if ( nr1.semn == 1 && x > 0 ) nr2.semn = 1;
    if ( x < 0 ) x = -x;
    for ( int i = 1; i <= nr1.v[0]; i++ )
    {
        div *= 10;
        div += nr1.v[i];
        if ( div < x )
        {
            poz++;
            continue;
        }
        else
        {
            int rez = div / x;
            nr2.v[poz++] = rez;
            div = div % x;
        }
    }
    nr2.v[0] = poz - 1;
    if ( nr2.v[1] == 0 )
    {
        for ( int i = 1; i <= nr2.v[0]; i++ ) nr2.v[i] = nr2.v[i + 1];
        nr2.v[0]--;
    }
}


//Calculeaza prioritate operatorilor pentru conversia postfixata
int prio_Big (BigInt Operator)
{
    if ( Operator.operatie == 1 || Operator.operatie == 2 ) return 2; // + || -
    if ( Operator.operatie == 3 || Operator.operatie == 4 ) return 3; // * || /
    if ( Operator.operatie == 6 || Operator.operatie == 7 ) return 4; // ( || )
    return 0;
}
//Calculeaza prioritate operatorilor pentru conversia postfixata
int prio_Real (Real nr)
{
    if ( nr.operatie == 1 || nr.operatie == 2 ) return 2; // + || -
    if ( nr.operatie == 3 || nr.operatie == 4 ) return 3; // * || /
    if ( nr.operatie == 6 || nr.operatie == 7 ) return 4; // ( || )
    return 0;
}
//Transforma vectorul 1 de BigInt cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
void infix_to_postfix_Big (BigInt vector1[], BigInt vector2[], int& lungime)
{
    BigInt stiva[150], auxiliar;
    int inceput_coada1 = 1, sfarsit_coada1 = lungime + 1, inceput_coada2 = 1, sfarsit_coada2 = 1, varf_stiva = 1;
    while ( inceput_coada1 < sfarsit_coada1 )
    {
        auxiliar = vector1[inceput_coada1];
        inceput_coada1++;
        if ( auxiliar.operatie == 0 )
        {
            vector2[sfarsit_coada2++] = auxiliar;
        }
        else
        {
            if ( auxiliar.operatie == 7 )
            {
                while ( stiva[varf_stiva].operatie != 6 )
                {
                    vector2[sfarsit_coada2] = stiva[varf_stiva];
                    sfarsit_coada2++;
                    varf_stiva--;
                }
                varf_stiva--;
                lungime -= 2;
            }
            else
            {
                while ( varf_stiva > 1 && stiva[varf_stiva].operatie != 6 && ( prio_Big (stiva[varf_stiva]) >= prio_Big (auxiliar) ) )
                {
                    vector2[sfarsit_coada2++] = stiva[varf_stiva];
                    varf_stiva--;
                }
                varf_stiva++;
                stiva[varf_stiva] = auxiliar;
            }
        }
    }
    while ( varf_stiva > 1 )
    {
        vector2[sfarsit_coada2++] = stiva[varf_stiva];
        varf_stiva--;
    }
}
//Transforma vectorul 1 de Real cu forma infixata in vectorul 2 cu forma postfixata. Functia actualizeaza lungimea
void infix_to_postfix_Real (Real vector1[], Real vector2[], int& lungime)
{
    Real stiva[150], auxiliar;
    int inceput_coada1 = 1, sfarsit_coada1 = lungime + 1, inceput_coada2 = 1, sfarsit_coada2 = 1, varf_stiva = 1;
    while ( inceput_coada1 < sfarsit_coada1 )
    {
        auxiliar = vector1[inceput_coada1];
        inceput_coada1++;
        if ( auxiliar.operatie == 0 )
        {
            vector2[sfarsit_coada2++] = auxiliar;
        }
        else
        {
            if ( auxiliar.operatie == 7 )
            {
                while ( stiva[varf_stiva].operatie != 6 )
                {
                    vector2[sfarsit_coada2] = stiva[varf_stiva];
                    sfarsit_coada2++;
                    varf_stiva--;
                }
                varf_stiva--;
                lungime -= 2;
            }
            else
            {
                while ( varf_stiva > 1 && stiva[varf_stiva].operatie != 6 && ( prio_Real (stiva[varf_stiva]) >= prio_Real (auxiliar) ) )
                {
                    vector2[sfarsit_coada2++] = stiva[varf_stiva];
                    varf_stiva--;
                }
                varf_stiva++;
                stiva[varf_stiva] = auxiliar;
            }
        }
    }
    while ( varf_stiva > 1 )
    {
        vector2[sfarsit_coada2++] = stiva[varf_stiva];
        varf_stiva--;
    }
}

//Evalueaza o expresie postfixata si returneaza rezultatul
BigInt eval_postfix_Big (BigInt vector[], int lungime)
{
    BigInt stiva[150], auxiliar, operand_stanga, operand_dreapta;
    int varf_stiva = 0, inceput_coada = 1;
    while ( inceput_coada <= lungime )
    {
        auxiliar = vector[inceput_coada];
        inceput_coada++;
        if ( auxiliar.operatie == 0 )
        {
            varf_stiva++;
            stiva[varf_stiva] = auxiliar;
        }
        else
        {
            BigInt val;
            operand_dreapta = stiva[varf_stiva];
            varf_stiva--;
            operand_stanga = stiva[varf_stiva];
            varf_stiva--;
            if ( auxiliar.operatie == 1 ) adunare_Big (operand_stanga, operand_dreapta, val);
            else if ( auxiliar.operatie == 2 ) scadere_Big (operand_stanga, operand_dreapta, val);
            else if ( auxiliar.operatie == 3 ) inmultire_Big (operand_stanga, operand_dreapta, val);
            else if ( auxiliar.operatie == 4 ) impartire_Big (operand_stanga, operand_dreapta, val);
            varf_stiva++;
            stiva[varf_stiva] = val;
        }
    }
    return stiva[1];
}
//Evalueaza o expresie postfixata si returneaza rezultatul
Real eval_postfix_Real (Real vector[], int lungime)
{
    Real stiva[100], auxiliar, operand_stanga, operand_dreapta;
    int varf_stiva = 0, inceput_coada = 1;
    while ( inceput_coada <= lungime )
    {
        auxiliar = vector[inceput_coada];
        inceput_coada++;
        if ( auxiliar.operatie == 0 )
        {
            varf_stiva++;
            stiva[varf_stiva] = auxiliar;
        }
        else
        {
            operand_dreapta = stiva[varf_stiva];
            varf_stiva--;
            operand_stanga = stiva[varf_stiva];
            varf_stiva--;
            varf_stiva++;
            if ( auxiliar.operatie == 1 ) stiva[varf_stiva].n = operand_stanga.n + operand_dreapta.n;
            else if ( auxiliar.operatie == 2 ) stiva[varf_stiva].n = operand_stanga.n - operand_dreapta.n;
            else if ( auxiliar.operatie == 3 ) stiva[varf_stiva].n = operand_stanga.n * operand_dreapta.n;
            else if ( auxiliar.operatie == 4 )
            {
                stiva[varf_stiva].n = operand_stanga.n / operand_dreapta.n;
                if(operand_dreapta.n==0)
                eroare=1;
            }

        }
    }
    return stiva[1];
}

//Transforma vectorul 1 de BigInt cu forma infixata in vectorul 2 cu forma prefixata
void infix_to_prefix_Big (BigInt vector1[], BigInt vector2[], int& lungime)
{
    BigInt stiva[100];
    for ( int i = 1; i <= lungime; i++ )
    {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        else if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
        stiva[lungime + 1 - i] = vector1[i];
    }
    infix_to_postfix_Big (stiva, vector2, lungime);
    for ( int i = 1; i <= lungime; i++ )
    {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
    }
    for ( int i = 1; i <= lungime; i++ )
    {
        vector1[i] = vector1[lungime + 1 - i];
    }
}
//Transforma vectorul 1 de Real cu forma infixata in vectorul 2 cu forma prefixata
void infix_to_prefix_Real (Real vector1[], Real vector2[], int& lungime)
{
    Real stiva[100];
    for ( int i = 1; i <= lungime; i++ )
    {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        else if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
        stiva[lungime + 1 - i] = vector1[i];
    }
    infix_to_postfix_Real (stiva, vector2, lungime);
    for ( int i = 1; i <= lungime; i++ )
    {
        if ( vector1[i].operatie == 6 ) vector1[i].operatie = 7;
        if ( vector1[i].operatie == 7 ) vector1[i].operatie = 6;
    }
    for ( int i = 1; i <= lungime; i++ )
    {
        vector1[i] = vector1[lungime + 1 - i];
    }
}

//Verifica corectitudinea unei expresii matematice
void evaluare (char sir_caractere[])
{
    bool este_operand = 0;
    int numar_paranteze = 0, numar_cifre = 0;
    for ( int i = 0; i < strlen (sir_caractere); i++ )
    {
        if ( sir_caractere[i] >= 48 && sir_caractere[i] <= 57 )
        {
            este_operand = 1;
            numar_cifre++;
            if ( numar_cifre > 9 )
            {
                eroare = 9;
                return;
            }
        }
        else if ( sir_caractere[i] == '+' || sir_caractere[i] == '-' || sir_caractere[i] == '*' || sir_caractere[i] == 'x' || sir_caractere[i] == '/' || sir_caractere[i] == ':' )
        {
            numar_cifre = 0;
            if ( este_operand == 0 )
            {
                eroare = 3;
                return;
            }
            este_operand = 0;
        }
        else if ( sir_caractere[i] == '(' )
        {
            if ( este_operand )
            {
                eroare = 4;
                return;
            }
            numar_paranteze++;
        }
        else if ( sir_caractere[i] == ')' )
        {
            if ( este_operand == 0 )
            {
                eroare = 5;
                return;
            }
            if ( numar_paranteze > 0 )numar_paranteze--;
            else
            {
                eroare = 6;
                return;
            }
            este_operand = 1;
        }
    }
    if ( numar_paranteze )
    {
        eroare = 7;
        return;
    }
    if ( este_operand == 0 ) eroare = 8;
}

/////////////////////////////////////

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
            nrp++;
            siFlag=0;
        }
        else if (eScad(cuv))
        {
            strcpy(vecCuv[k], "-");
            nrp++;
            siFlag=0;
        }
        else if (eInm(cuv))
        {
            strcpy(vecCuv[k], "*");
            nrp++;
            siFlag=0;
        }
        else if (eImp(cuv))
        {
            strcpy(vecCuv[k], "/");
            nrp++;
            siFlag=0;
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
            }
            else if(cOP=='/')
            {
                r=(double)(stod(s[v-1],nullptr));
                v--;
                r/=(double)(stod(s[v+1],nullptr));
                v--;
                sprintf(buffer,"%f",r);
                strcpy(s[v],buffer);
            }
        }
    }
    strcpy(rez,s[1]);// Practic am calculat pe baza unei stive si am tot continuat pana cand rezultatul final se afla pe prima pozitie
    int ok=0,i;
    for(i=strlen(rez)-1; i>=0 && rez[i]!='.'; i--) //pentru a nu avea cazuri de felul 5.00000, ci 5 sau 2.760200, ci 2.7602, eliminam 0-urile
        if(rez[i]!='0')
        {
            ok=1;
            break;
        }
        else
            strcpy(rez+i,rez+i+1);
    if(!ok)strcpy(rez+i,rez+i+1);//daca nu s-a gasit alta cifre in afara de 0 in dreapta virgulei, eliminam virgula
    return rez;
}
char* evaluatorBig (char vecCuv[5000][10000])//Calculeaza ecuatia pentru numere in big int
{
    char s[1000][100];
    int v = 0;
    stack<char> op;
    for ( int i = 0; i < k; i++ )
    {
        if ( vecCuv[i][0] == '*' )
            op.push ('*');
        else if ( vecCuv[i][0] == '+' )
            op.push ('+');
        else if ( vecCuv[i][0] == '/' )
            op.push ('/');
        else if ( vecCuv[i][0] == '-' )
            op.push ('-');
        strcpy (s[++v], vecCuv[i]);
        BigInt p;
        if ( s[v][0] == ')' )
        {
            v--;
            BigInt r, p, aux;
            char cOP = op.top ();
            op.pop ();
            if ( cOP == '*' )
            {

                conversie (1, r);
                while ( s[v][0] != '*' )
                {
                    conversie (( stoi (s[v], nullptr) ), p);
                    inmultire_Big (r, p, aux);
                    r = aux;
                    clear_Big (aux);
                    v--;
                }
                char sir1[MAX_VEC] = { 0 };
                //char* pointer=sir1;
                for ( int i = 0; i < r.v[0]; i++ )
                    itoa (r.v[i + 1], sir1 + i, 10);
                strcpy (s[v], sir1);
                //strcpy(s[v],to_string().c_str());//o functie
            }
            else if ( cOP == '+' )
            {
                clear_Big (r);
                while ( s[v][0] != '+' )
                {
                    BigInt aux2;
                    conversie (stoi (s[v],nullptr), aux);
                    adunare_Big (r, aux, aux2);
                    r = aux2;
                    v--;
                    clear_Big (aux);
                }
                char sir1[MAX_VEC] = { 0 };
                //char* pointer=sir1;
                for ( int i = 0; i < r.v[0]; i++ )
                    itoa (r.v[i + 1], sir1 + i, 10);
                strcpy (s[v], sir1);
                //strcpy (s[v] , to_string (r).c_str ());
            }
            else if ( cOP == '-' )
            {
                conversie (stoi (s[v], nullptr), aux);
                r = aux;
                //r = ( stoi (s[v] , nullptr) );
                v--;
                clear_Big (aux);
                conversie (stoi (s[v], nullptr), aux);
                BigInt aux2;
                scadere_Big (r, aux, aux2);
                r = aux2;
                //r -= ( stoi (s[v] , nullptr) );
                v--;
                if ( r.semn == 1 ) r.semn = 0;
                else r.semn = 1;
                //r *= -1;
                char sir1[MAX_VEC] = { 0 };
                for ( int i = 0; i < r.v[0]; i++ )
                    itoa (r.v[i + 1], sir1 + i, 10);
                strcpy (s[v], sir1);
                //strcpy (s[v] , to_string (r).c_str ());
            }
            else if ( cOP == '/' )
            {
                clear_Big (r);
                conversie (stoi (s[v - 1], nullptr), r);
                //r = ( stoi (s[v - 1] , nullptr) );
                v--;
                clear_Big (aux);
                conversie (stoi (s[v + 1], nullptr), aux);
                BigInt aux2;
                impartire_Big (r, aux, aux2);
                r = aux2;
                //r /= ( stoi (s[v + 1] , nullptr) );
                v--;
                char sir1[MAX_VEC] = { 0 };
                for ( int i = 0; i < r.v[0]; i++ )
                    itoa (r.v[i + 1], sir1 + i, 10);
                strcpy (s[v], sir1);
                //strcpy (s[v] , to_string (r).c_str ());
            }
        }
    }
    strcpy (rez, s[1]);
    return rez;
}

int main()
{
    meniu1();
    closegraph();
    return 0;
}
