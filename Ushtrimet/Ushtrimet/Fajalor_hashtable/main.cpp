#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>


using namespace std;

struct liste
{
    string vlere;
    struct liste *pas;

};


int key(string value){ //llogaritet celesi i fjales duke kthyer shkronje e pare ne numer
     char c= value.at(0);

     int k= (int)(c);

    return k;
    }

int hashfunk(int celes){   //funksioni hash qe llogarit indeksin

   int index=celes% 28;

    return index;

}


bool gjendet(liste *l,string fjale) //kerkim ne liste

{   bool u_gjet=false;

    if(l==0) return u_gjet;

    if(l->vlere==fjale)
    {   u_gjet=true;

    return u_gjet;
    }

  else return gjendet(l->pas,fjale);
}

void afisho_fjalet(liste *l)  //afishon fjalet e fjalorit qe jane cuar ne liste
{
    liste *tmp=new liste;
    tmp=l;

    while(tmp!=NULL)
    {
        cout<<tmp->vlere<<" ";
        tmp=tmp->pas;
    }

}
void shto_fjale(liste *l,string word){ //funskion qe shton nje fjale ne liste
   liste *add= new liste;
   add->vlere=word;
   add->pas=NULL;

    if(l==NULL) l=add;
    else{
        add->pas=l->pas;
        l->pas=add;
        }



}






int main()
{

    ifstream file;

    char c;
   string fjale;
    bool ndodhet=true;

    liste *hashtab[28];

    for(int i=0; i<28; i++)
    {
         hashtab[i]=NULL;
        }

  file.open("10000fjale.txt");
if(file.is_open())
{
    while(! file.eof())
    {
        c=file.get();
        while( isalpha(c) && c!=' ' && c!='\n')  //formojme fjalen e rradhes nga file
        {   fjale= fjale+c;
            c=file.get();

        }
        if( fjale != ""){
         std::transform(fjale.begin(), fjale.end(), fjale.begin(), ::tolower);

        int celes=key(fjale);
        int index=hashfunk(celes); //llogarisim celesin dhe indeksin

        ndodhet=gjendet(hashtab[index],fjale);
        if(!ndodhet)
        {
           if ( hashtab[index] == NULL)
           hashtab[index]=new liste;

            shto_fjale(hashtab[index],fjale); //nese nuk ndodhet e cojme te lista qe ndodhet ne indeksin
                                            //e caktuar ne tabelen hash


        }

        fjale.clear();
        }

    }
}

else cout<<"Gabim ne hapjen e file"<<endl;




     for(int i=0; i<28; i++)

{
   liste *l = hashtab[i];  //bejme afishimin e te gjitha listave me elemente ne tabelen hash
       if ( l!=NULL)
       {


        afisho_fjalet(l);
        cout<<"\n";

}



}


file.close();


    return 0;
}
