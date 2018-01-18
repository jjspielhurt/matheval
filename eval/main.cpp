#include "iostream"
#include "cmath"
#include "fstream"
#include "string.h"
#include "operatii.h"
#include "stdlib.h"


using namespace std;
ifstream p("prior.txt");
int tipOperator;
float opd[100];
int lung,topOpr=0,topOpd=0,ok=0;

struct stivaOperatori{
char c[10]; }opr[100];

//returneaza prioritatea operatorului o utilizand fisierul p


int prioritate(char o[10],int i)
{
    char s[100],*q;
    p.clear();
    p.seekg(0);
    while(!p.eof())
    {
        p.getline(s,100);
        q=strstr(s,o);
        if(q!=NULL && *(q-1)==' ' && *(q+strlen(o))==' ' )
            return int(s[0]-48);
    }
    cout<<"Eroare de sintaxa: "<<o<<" de pe pozitia "<<i-strlen(o)+1<<" nu reprezinta un operand sau un operator.";
    exit(0);

}

float aplicOper(float termen1,float termen2,char o[10])
{
    if(strcmp(o,"(")==0||strcmp(o,")")==0) return termen1;

    //operatori binari
    if(strcmp(o,"+")==0) return adunare(termen1,termen2);
    if(strcmp(o,"-")==0) return diferenta(termen1,termen2);
    if(strcmp(o,"*")==0) return inmultire(termen1,termen2);
    if(strcmp(o,"/")==0) return impartire(termen1,termen2);
    if(strcmp(o,"mod")==0) return int(termen1)%int(termen2);
    if(strcmp(o,"=")==0) return termen1==termen2;
    if(strcmp(o,"#")==0) return !(termen1==termen2);
    if(strcmp(o,">=")==0) return termen1>=termen2;
    if(strcmp(o,"<=")==0) return termen1<=termen2;
    if(strcmp(o,">")==0) return termen1>termen2;
    if(strcmp(o,"<")==0) return termen1<termen2;
    if(strcmp(o,"and")==0) return termen1&&termen2;
    if(strcmp(o,"or")==0) return termen1||termen2;
    if(strcmp(o,"xor")==0) return (termen1!=termen2)&&(termen1==0||termen2==0);
    if(strcmp(o,"min")==0) return min(termen1,termen2);
    if(strcmp(o,"max")==0) return max(termen1,termen2);
    if(strcmp(o,"^")==0) return ridicare_la_putere(termen1,termen2);



    //operatori unari
    tipOperator=1;
    if(strcmp(o,"sin")==0) return sin(termen2);
    if(strcmp(o,"cos")==0) return cos(termen2);
    if(strcmp(o,"tan")==0) return tangenta(termen2);
    if(strcmp(o,"cot")==0) return cotangenta(termen2);

    if(strcmp(o,"asin")==0) return arcsin(termen2);
    if(strcmp(o,"acos")==0) return arccos(termen2);
    if(strcmp(o,"atan")==0) return atan(termen2);
    if(strcmp(o,"acot")==0) return PI/2-atan(termen2);

    if(strcmp(o,"ln")==0) return logaritm(termen2);
    if(strcmp(o,"sqrt")==0) return radical(termen2);
    if(strcmp(o,"abs")==0) return abs(termen2);
    if(strcmp(o,"floor")==0) return floor(termen2);
    if(strcmp(o,"ceil")==0) return ceil(termen2);
    if(strcmp(o,"round")==0) return round(termen2);
    if(strcmp(o,"exp")==0) return exponentiala(termen2);

}
//aplica operatorul din varful stivei de operatori pe operanzi

void aplicaOpTop(int i)
{
    float rez;
    tipOperator=2;

    if(topOpd>1)
        rez=aplicOper(opd[topOpd-1],opd[topOpd],opr[topOpr].c);

    else
    {
        rez=aplicOper(0,opd[topOpd],opr[topOpr].c);

        if(tipOperator==2)
        {
            if(opr[topOpr].c[0]!='(')
            {
                cout<<"Expresie gresita. Operatorul de pe pozitia "<<i-1<<" necesita mai multe variabile/constante";
                exit(0);
            }

            if (opr[topOpr].c[0]=='(')
            {
                cout<<"Expresie gresita. Este nevoie de mai multe paranteze.";
                exit(0);
            }

        }

    }

    topOpd--;
    topOpr--;
    if(tipOperator==2)
        topOpd--;
    topOpd++;
    opd[topOpd]=rez;
}

/* opr stiva operatorilor cu topOpr
   opd stiva operanzilor cu topOpd
*/
//functia comp verifica daca incepand de pe pozitia i se gaseste numele unei variabile
bool comp(char v[25],char fun[100], int &i)
{
    int j;
    if(lung<i+strlen(v)) return 0;
    for(j=i; j<strlen(v)+i; j++) if(v[j-i]!=fun[j]) return 0;
    if(j<lung && ((fun[j]>='0' && fun[j]<='9') || (fun[j]>='a' && fun[j]<='z') || (fun[j]>='A' && fun[j]<='Z'))) return 0;
    i=i+strlen(v)-1;
    return 1;
}


float prelucrare(int nrVal, char v1[25],char v2[25],char fct[100],float val1,float val2)
{
    int i,j,par[100],topPar=-1;
    char o[10];
    lung=strlen(fct);
    strcpy(opr[0].c,"(");
    topOpd=0;
    topOpr=0;
    i=0;



    do
    {
       while(i<lung&&topOpr>=0)
       { //adaugam in stiva cu paranteze daca este cazul
                if(i!=lung-1)
                {
                    if(fct[i]=='(')
                    {
                        topPar++;
                        par[topPar]=i;

                    }
                    else
                    {
                        if(fct[i]==')')
                        topPar--;
                        if(topPar<-1)
                        {
                            cout<<"Eroare de sintaxa.Sunt mai multe paranteze inchise decat deschise, prima in plus fiind pe pozitia "<<i;
                            exit(0);
                        }

                    }
                }


           //verificam daca este inchidere de paranteza
           if(fct[i]==')')
           {
               while(strcmp(opr[topOpr].c,"(")!=0)
               aplicaOpTop(i);
               topOpr--;

            }
            //verificam daca e operand si adaugam in stiva opd valorile pt operanzi
            else if(comp(v1,fct,i))
            {
                topOpd++;
                opd[topOpd]=val1;
            }
            else if(nrVal==2&& comp(v2,fct,i))
            {
                topOpd++;
                opd[topOpd]=val2;
            }
            //verificam daca e numar si adougam valoarea in stiva de operanzi
            else if(fct[i]>='0'&&fct[i]<='9')
            {
                topOpd++;
                float num=0,num2=0,pow=1;
                while (fct[i]>='0'&& fct[i]<='9' && i<lung)
                {
                    num=num*10+fct[i]-'0';
                    i++;
                }
                if(fct[i]=='.')
                {
                    i++;
                    while (fct[i]>='0'&& fct[i]<='9' && i<lung)
                    {
                        num2=num2*10+fct[i]-'0';
                        i++;
                        pow*=10;

                    }
                    num=num+num2/pow;
                }

                i--;
                opd[topOpd]=num;
            }
            //daca e operator updatam stiva op
            else
            {
                //verificam daca avem operator de tip sin,cos,sqrt,tg,etc.
                o[0]=fct[i];

                //verificam daca intalnim numar cu semn
                if((o[0]=='+' || o[0]=='-') && (fct[i-1]=='(' || i==0))
                    opd[++topOpd]=0;

                j=1;

                if(fct[i]>='a'&&fct[i]<='z')
                {
                    ok=1;

                    while(ok==1&&i<lung)
                    {
                        i++;
                        if(fct[i]>='a'&&fct[i]<='z')
                        {
                            o[j]=fct[i];
                            j++;
                        }
                        else ok=0;
                    }
                    i--;
                }
                if((fct[i]=='>'||fct[i]=='<')&&fct[i+1]=='='&&i+1<lung)
                {
                    o[j]='=';
                    i++;
                    j++;
                }

                o[j]=NULL;

                if(o[0]!=' ')
                {
                    //in o stocam valoarea operatorului curent
                    if(prioritate(o,i)>prioritate(opr[topOpr].c,i)||strcmp(o,"(")==0)
                    {
                        //daca prioritatea operatorului curent > proritatea operatorului din varful stivei atunci il putem adauga in stiva
                        //la fel si daca avem deschidere de paranteza
                        topOpr++;
                        strcpy(opr[topOpr].c,o);

                    }
                    else
                    {
                        //altfel trebuie aplicat operatorul din varful stivei
                        while(prioritate(o,i)<=prioritate(opr[topOpr].c,i)&&topOpr>0)
                        aplicaOpTop(i);
                        topOpr++;
                        strcpy(opr[topOpr].c,o);
                    }
                }
            }

            i++;
        }
        if(topOpr>0) aplicaOpTop(i);

    } while(topOpr>0);

    if(topPar>-1)
    {
        cout<<"Eroare de sintaxa.Sunt mai multe paranteze deschise decat inchise, ultima in plus fiind pe pozitia "<<par[topPar];
        exit(0);
    }
    if(opd[topOpd]>inf) opd[topOpd]=inf;
    if(opd[topOpd]<-inf) opd[topOpd]=-inf;
    return opd[topOpd];


}

/*citirea datelor de la tastatura
nrVal -numarul de variabile (1 sau 2)
v1,v2-numele variabilelor
val1,val2-valorile variabilelor v1,v2
*/

void verifica_nume_variabila (string &v)
{
    bool ok=0;

    while(!ok)
    {
        ok=1;
        if(v.length()>20)
        {
            cout<<"Numele variabilei este prea lung. Va rugam indroduceti alt nume: ";
            cin>>v;
            ok=0;
        }
        else if(v[0]>='0' && v[0]<='9')
        {
            cout<<"Numele variabilei nu poate incepe cu o cifra. Va rugam introduceti alt nume: ";
            cin>>v;
            ok=0;
        }
        else
        {
            for(int i=0; i<v.length(); i++)
            {
                if((v[i]<'0'||v[i]>'9')&&(v[i]<'a' || v[i]>'z') && (v[i]<'A' || v[i]>'Z'))
                {
                    cout<<"Numele variabilei poate contine doar litere si cifre. Va rugam introduceti alt nume: ";
                    cin>>v;
                    ok=0;
                    i=v.length();
                }
            }
        }
    }

}

void verifica_interval (float &val1, float &val2)
{
    bool ok=0;

    while(ok==0)
    {
        ok=1;
        if(val1>val2)
        {
            cout<<"Interval gresit. Capatul stang al intervalului trebuie sa fie mai mic decat cel drept.\nVa rugam introduceti alte doua valori:";
            cin>>val1>>val2;
            ok=0;
        }
    }
}
void verifica_nr_pcte (int &n)
{
    while(n<=0)
    {
        cout<<"Numarul de puncte trebuie sa fie un numar pozitiv. Va rugam introduceti alt numar: ";
        cin>>n;
    }
}



float precizie (float a, float b, int nr)
{
    if(nr==1) return 0;
    else return (b-a)/(nr-1);

}

struct sol
{
    float fun[5000];
};

sol eval_citire()
{
    sol vec;

    int nrVal=0;
    int l;
    string v;
    char v1[25],v2[25],fct[100];
    float val1,val2, val3, val4;

    while(nrVal!=1 && nrVal!=2)
    {
        cout<<"Dati numarul de variabile (1 sau 2):";
        cin>>nrVal;
    }


    cout<<"Dati numele variabilei 1:";
    cin>>v;
    verifica_nume_variabila(v);
    for(l=0; l<v.length(); l++) v1[l]=v[l];
    v1[v.length()]='\0';



    if(nrVal==2)
    {
        cout<<"Dati numele variabilei 2:";
        cin>>v;
        verifica_nume_variabila(v);
        for(l=0; l<v.length(); l++) v2[l]=v[l];
        v2[v.length()]='\0';

    }

    cout<<"Dati functia:";
    cin.get();
    cin.get(fct,100);


    cout<<"Dati intervalul de valori pentru "<<v1<<". Introduceti doua valori pentru interval: ";
    cin>>val1>>val2;
    verifica_interval(val1,val2);



    if(nrVal==2)
    {
        cout<<"Dati intervalul de valori pentru "<<v2<<". Introduceti doua valori pentru interval: ";
        cin>>val3>>val4;
        verifica_interval(val3,val4);
    }

    int nr_puncte;
    cout<<"Dati numarul de puncte: ";
    cin>>nr_puncte;
    verifica_nr_pcte(nr_puncte);


    float precizie1, precizie2,i,j;
    int lung;
    lung=strlen(fct);
    fct[lung]=')';
    lung++;
    fct[lung]='\0';


    vec.fun[0]=nr_puncte;
    int k;
    precizie1=precizie(val1,val2,nr_puncte);
    if(nrVal==1)
    {

         for(k=1, i=val1; k<=nr_puncte; i+=precizie1,k++)
         {
              vec.fun[k]=prelucrare(nrVal,v1,v2,fct,i,0);
              cout<<k<<". f("<<i<<") = "<<vec.fun[k]<<endl;
              topOpr=0;
              topOpd=0;
         }


    }
    else
    {
        precizie2=precizie(val3,val4,nr_puncte);

        for(k=1, i=val1,j=val3; k<=nr_puncte; i+=precizie1,j+=precizie2,k++)
        {

             vec.fun[k]=prelucrare(nrVal,v1,v2,fct,i,j);
             cout<<k<<". f("<<i<<","<<j<<") = "<<vec.fun[k]<<endl;
             topOpr=0;
             topOpd=0;
        }
    }
}

int main()
{
    sol valori_functie;

    valori_functie=eval_citire();








    return 0;
}
