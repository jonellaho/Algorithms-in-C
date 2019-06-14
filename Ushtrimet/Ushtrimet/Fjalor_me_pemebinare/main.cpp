#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>


using namespace std;

struct peme{             //ndertojme strukturen e pemes

    std::string fjale;

    struct peme *dj, *mj;

};

void shto_nepeme(peme *p, string fjala)  //funksion qe shton ne peme nje fjale te re
{   peme * tmp=p, *p2;
    p2=new peme;

    p2->dj=NULL;
    p2->mj=NULL;
    p2->fjale=fjala;

        if(p==NULL){

        p=p2;

    }

    else if(p->fjale < p2->fjale){

        shto_nepeme(p->dj,fjala);

        if(p->dj==NULL)

            p->dj=p2;

    }

    else{

        shto_nepeme(p->mj,fjala);

        if(p->mj==NULL)

            p->mj=p2;

    }

}


bool kerko(peme *p,string word)
{
    if(p==0) return false;

    if(p->fjale==word) return true;

    else if(p->fjale >word ) return kerko(p->mj,word);

    else return kerko(p->dj,word);

}
void pasRendore(peme *T)

{

if(T != NULL) {

cout<<T->fjale<<"\n";

pasRendore(T->mj);

pasRendore(T->dj);

}

}



int main()
{ifstream file;

   peme *p=new peme;
  // string line;
    string fjale;
    char c;
    bool ndodhet=true;

   file.open("10000fjale.txt");
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
    std::transform(fjale.begin(), fjale.end(), fjale.begin(), ::tolower);


    ndodhet=kerko(p,fjale);
    if(!ndodhet)
        shto_nepeme(p,fjale);

    fjale.clear();

    }

}

    else cout<<"Gabim ne hapjen e file"<<endl;





     file.close();

    pasRendore(p);


    return 0;
}
