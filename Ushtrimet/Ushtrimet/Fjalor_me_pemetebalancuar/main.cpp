#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

struct PemeB
{
    string data;
    PemeB* dj,  *mj;
};
 void shto_nepeme(PemeB *p, string fjala) //funsion qe ben shtimin ne peme si nje peme e kerkimit binar e pabalancuar
{   PemeB * tmp=p, *p2;
    p2=new PemeB;

    p2->dj=0;
    p2->mj=0;
    p2->data=fjala;

        if(p==NULL){

        p=p2;

    }

    else if(p->data < p2->data){

        shto_nepeme(p->dj,fjala);

        if(p->dj==0)

            p->dj=p2;

    }

    else{

        shto_nepeme(p->mj,fjala);

        if(p->mj==0)

            p->mj=p2;

    }

}

void ruajnevektor(PemeB* p, vector<PemeB*> &nodes)    //ruan pointerat e elementeve te pemes ne nje vektor
{

    if (p==NULL)
        return;


    ruajnevektor(p->mj, nodes); //ruan nyjet ne menyre te renditur (Inorder) ne nje vektor
    nodes.push_back(p);
    ruajnevektor(p->dj, nodes);
}


PemeB* peme_ndihmese(vector<PemeB*> &nodes, int fillim,int end)  //funksion rekursiv qe nderton nje peme binare te balancuar me vlerat e vektorit

{

    if (fillim > end)
        return NULL;


    int mes = (fillim + end)/2; //merr elemntin e mesit te vektorit dhe e con ne koke
    PemeB *p = nodes[mes];


    p->mj  = peme_ndihmese(nodes, fillim, mes-1);
    p->dj = peme_ndihmese(nodes, mes+1, end);

    return p;
}


PemeB* pema(PemeB* koka)  // ben konvertimin e  pemes binare te pabalancuar ne peme te balancuar
{
    // ruaj nyjet e pemes binare ne menyre te renditur me ane te funksionit ruajnevektor/
    vector<PemeB *> nodes;
    ruajnevektor(koka, nodes);

    // e nderton pemen e balancuar
    int n = nodes.size();
    return peme_ndihmese(nodes, 0, n-1);
}


bool kerko(PemeB *p,string word) //kerkojme nese ndodhet nje fjale ne peme apo jo
{
    if(p==0) return false;
    if(p->data==word) return true;
    else if(p->data.compare(word)>0) return kerko(p->mj,word);
    else return kerko(p->dj,word);

}
void pasRendore(PemeB *T) //bejme afishimin e pemes ne menyre pasrendore

{

if(T != NULL) {

cout<<T->data<<"\n";

pasRendore(T->mj);

pasRendore(T->dj);

}

}



int main()
{ifstream file;

   PemeB *p=new PemeB;
    string fjale;
    char c;
    bool ndodhet=false;

   file.open("10000fjale.txt"); //hapim file
if(file.is_open())
{
    while(! file.eof())
     {
            c=file.get();


        while(isalpha(c)&& c!=' '&& c!='\n')  //formojme fjalen e rradhes ne file per sa kohe arrijme ne fund te tij
                                //
       {
                                            //nese eshte shkronje karakteri qe lexojme
                fjale= fjale+c;

            c=file.get();

       }

        std::transform(fjale.begin(), fjale.end(), fjale.begin(), ::tolower); //e konvertojme fjalen ne fjale me shkronja te vogla

    ndodhet=kerko(p,fjale); //kontrollpjme nese gjendet ne peme fjala
    if(!ndodhet) //nese nuk ndodhet e shtojme ate
        shto_nepeme(p,fjale);

    fjale.clear();

    }
}
    else cout<<"Gabim ne hapjen e file";

    PemeB *koka=new PemeB; //e kthejme pemen e formuar ne peme te balancuar
    koka=pema(p);

    pasRendore(koka); //bejme afishimin




    return 0;
}
