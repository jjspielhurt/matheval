#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
using namespace std;
ifstream p("prior.txt");
//returneaza prioritatea operatorului o utilizand fisierul p
int prioritate(char o[5])
{
    bool ok;
    char s[50];
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
void prelucrare(int nrVal, char v1,char v2,char fct[100],double val1,double val2)
{

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
double val1,val2;
cout<<"Dati valoare pentru "<<v1<<":";
cin>>val1;
if(nrVal==2)
{cout<<"Dati valoare pentru "<<v2<<":";
cin>>val2;
}
prelucrare(nrVal,v1,v2,fct,val1,val2);
}

int main()
{
 citire();



    return 0;
}
