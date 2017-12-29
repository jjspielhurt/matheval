#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
using namespace std;
ifstream p("prior.txt");
int tipOperator;
float opd[100];
int lung,i,topOpr=0,topOpd=0,ok=0,j;

struct stivaOperatori{
char c[10]; }opr[100];

//returneaza prioritatea operatorului o utilizand fisierul p
int prioritate(char o[10])
{
    char s[50];
    p.clear();
    p.seekg(0);
    while(!p.eof())
    {
        p.getline(s,50);

        if(strstr(s,o)!=NULL)
        {
            return int(s[0]-48);

        }
    }
    return -1;
}

float aplicOper(float termen1,float termen2,char o[10])
{
    if(strcmp(o,"(")==0||strcmp(o,")")==0) return termen1;
    //operatori binari
    if(strcmp(o,"+")==0) return termen1+termen2;
    if(strcmp(o,"-")==0) return termen1-termen2;
    if(strcmp(o,"*")==0) return termen1*termen2;
    if(strcmp(o,"/")==0) return termen1/termen2;
    if(strcmp(o,"mod")==0) return int(termen1)%int(termen2);
    if(strcmp(o,"=")==0) return termen1==termen2;
    if(strcmp(o,"#")==0) return !(termen1==termen2);
    if(strcmp(o,">")==0) return termen1>termen2;
    if(strcmp(o,"<")==0) return termen1<termen2;
    if(strcmp(o,"and")==0) return termen1&&termen2;
    if(strcmp(o,"or")==0) return termen1||termen2;
    if(strcmp(o,"xor")==0) return (termen1!=termen2)&&(termen1==0||termen2==0);
    if(strcmp(o,"min")==0) return min(termen1,termen2);
    if(strcmp(o,"max")==0) return max(termen1,termen2);
    if(strcmp(o,"^")==0)
    { float v=1;
        for(int i=0;i<termen2;i++)
            v=v*termen1;
        return v;
    }

    //operatori unari
    tipOperator=1;
    if(strcmp(o,"sin")==0) return sin(termen1);
    if(strcmp(o,"cos")==0) return cos(termen1);
    if(strcmp(o,"tan")==0) return tan(termen1);
    if(strcmp(o,"cot")==0) return 1/tan(termen1);

    if(strcmp(o,"asin")==0) return asin(termen1);
    if(strcmp(o,"acos")==0) return acos(termen1);
    if(strcmp(o,"atan")==0) return atan(termen1);
    if(strcmp(o,"acot")==0) return 3.14159/2-atan(termen1);

    if(strcmp(o,"ln")==0) return log(termen1);
    if(strcmp(o,"sqrt")==0) return sqrt(termen1);
    if(strcmp(o,"abs")==0) return abs(termen1);
    if(strcmp(o,"floor")==0) return floor(termen1);
    if(strcmp(o,"ceil")==0) return ceil(termen1);
    if(strcmp(o,"round")==0) return round(termen1);
    if(strcmp(o,"exp")==0) return exp(termen1);

}
//aplica operatorul din varful stivei de operatori pe operanzi
void aplicaOpTop()
{ float rez;
    tipOperator=2;
              if(topOpd>1) rez=aplicOper(opd[topOpd],opd[topOpd-1],opr[topOpr].c);
              else{rez=aplicOper(opd[topOpd],0,opr[topOpr].c);
                   if(tipOperator==2) {
                        cout<<"Expresie gresita.Operatorul de pe pozitia "<<i<<" necesita mai multe variabile sau constante";
                    topOpd=0;
                    return ;
                    }
                  }

                   topOpd--;
                   topOpr--;
            if(tipOperator==2) topOpd--;
              topOpd++;
              opd[topOpd]=rez;
}

/* opr stiva operatorilor cu topOpr
   opd stiva operanzilor cu topOpd
*/
float prelucrare(int nrVal, char v1,char v2,char fct[100],float val1,float val2)
{
char o[10];
   lung=strlen(fct);
   strcpy(opr[0].c,"(");
   topOpd=0;
   topOpr=0;
   i=0;
  do
   {
       while(i<lung&&topOpr>=0)
       { //verificam daca este inchidere de paranteza
           if(fct[i]==')')
            { while(strcmp(opr[topOpr].c,"(")!=0)
                aplicaOpTop();
                topOpr--;
            }
       //verificam daca e operand si adaugam in stiva opd valorile pt operanzi
       else if(fct[i]==v1)
       {topOpd++;
           opd[topOpd]=val1;
       }
       else if(nrVal==2&&fct[i]==v2)
       {    topOpd++;
           opd[topOpd]=val2;
       }
       //verificam daca e numar si adougam valoarea in stiva de operanzi
       else if(fct[i]>='0'&&fct[i]<='9')
       {
            topOpd++;
           opd[topOpd]=fct[i]-48;
       }
       //daca e operator updatam stiva op
       else
       { //verificam daca avem operator de tip sin,cos,sqrt,tg,etc.
        o[0]=fct[i];
        j=1;
            if(fct[i]>='a'&&fct[i]<='z')
           {
               ok=1;

               while(ok==1&&i<lung)
               {i++;
                if(fct[i]>='a'&&fct[i]<='z')
                    {
                    o[j]=fct[i];
                    j++;
                    }
                else ok=0;
               }
               i--;
           }
           o[j]=NULL;
            //in o stocam valoarea operatorului curent
           if(prioritate(o)>prioritate(opr[topOpr].c)||strcmp(o,"(")==0)
           { //daca prioritatea operatorului curent > proritatea operatorului din varful stivei atunci il putem adauga in stiva
            //la fel si daca avem deschidere de paranteza
               topOpr++;
               strcpy(opr[topOpr].c,o);

           }
           else
           { //altfel trebuie aplicat operatorul din varful stivei
               while(prioritate(o)<=prioritate(opr[topOpr].c)&&topOpr>0)
                    aplicaOpTop();
                topOpr++;
                strcpy(opr[topOpr].c,o);
           }
       }
       i++;
       }
       aplicaOpTop();
   }
   while(topOpr>0);
   return opd[topOpd];


}
/*citirea datelor de la tastatura
nrVal -numarul de variabile (1 sau 2)
v1,v2-numele variabilelor
val1,val2-valorile variabilelor v1,v2
*/
int citire()
{
    char v1,v2,fct[100];
int nrVal;
cout<<"Dati numarul de variabile(1/2):";
cin>>nrVal;
cout<<"Dati numele variabilei 1:";
cin>>v1;
if(nrVal==2)
{cout<<"Dati numele variabilei 2:";
cin>>v2;
}
cout<<"Dati functia:";
cin.get();
cin.get(fct,100);
float val1,val2, val3, val4;
cout<<"Dati intervalul de valori pentru "<<v1<<". Introduceti doua valori pentru interval: ";
cin>>val1>>val2;
if(nrVal==2)
{cout<<"Dati intervalul de valori pentru "<<v2<<". Introduceti doua valori pentru interval: ";
cin>>val3>>val4;
}
int nr_puncte;
cout<<"Dati numarul de puncte: ";
cin>>nr_puncte;

float precizie1, precizie2,i,j;

precizie1=(val2-val1)/nr_puncte;
int k=1;
if(nrVal==1)
     {
         for(i=val1; i<val2; i+=precizie1)
         {cout<<k<<". f("<<i<<") = "<<prelucrare(nrVal,v1,v2,fct,i,0)<<endl;
            k++;
         }
     }
    else
    {
        precizie2=(val4-val3)/nr_puncte;
        j=val3;
        for(i=val1; i<val2; i+=precizie1,j+=precizie2)
                {cout<<k<<". f("<<i<<","<<j<<") = "<<prelucrare(nrVal,v1,v2,fct,i,j)<<endl;
                k++;
                }

    }
}

int main()
{

citire();

    return 0;
}
