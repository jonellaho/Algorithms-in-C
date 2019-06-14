#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;
struct node{

       string fjala;
       struct node *next;

};
bool gjendet(node *l,string fjale){ //funksion bulean qe ben kerkimin e fjales ne liste
    bool u_gjet=false;
  if(l==NULL) return u_gjet;
  if(l->fjala==fjale) {u_gjet=true;
  return u_gjet;}
  else return gjendet(l->next,fjale);

}
void shto_fjale(node *l,string word){ //funskion qe shton nje fjale ne liste
   node *add= new node;
   add->fjala=word;
   add->next=NULL;

    if(l==NULL) l=add;
    else{
        add->next=l->next;
        l->next=add;
        }



}
void afisho_fjalet(node *l)  //afishon fjalet e fjalorit qe jane cuar ne liste
{
    node *tmp=new node;
    tmp=l;

    while(tmp!=NULL)
    {
        cout<<tmp->fjala<<" ";
        tmp=tmp->next;
    }

}

int main()
{
  ifstream file;

   node *l=new node;

    string fjale;
   char c;
   bool ndodhet=true;

   file.open("10000fjale.txt"); //hapim file per te lexuar
  if(file.is_open())
 {
   while(!file.eof())
    {
        c=file.get();
        //formojme fjalen e rradhes ne file
            while(isalpha(c))
            {
                fjale= fjale+c;
                        c=file.get();

            }
                    //cout<<fjale;
            std::transform(fjale.begin(), fjale.end(), fjale.begin(), ::tolower); // konvertimin e fjales me shkronja te vogla
            ndodhet=gjendet(l,fjale); //kontollojme nese ndodhet ne liste
            if(!ndodhet)

                    shto_fjale(l,fjale); //nese jo e shtojme

            fjale.clear(); //vazhdojme me fjalen tjeter deri ne fund te file
        }



}

else cout<<"Gabim ne hapjen e file"<<endl;

file.close();

    afisho_fjalet(l); //afishojme listen
    return 0;
}














