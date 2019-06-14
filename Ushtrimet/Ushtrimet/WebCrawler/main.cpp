#define CURL_STATICLIB
#define CURL_EXTERN  __declspec(dllexport)
#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include<cstdlib>
#include <vector>
#include <boost/regex.hpp>
#include <fstream>
#include <curl/curl.h>
#include "curl.h";
//#include <curl/types.h>
//#include <curl/easy.h>

using namespace std;


struct rradha{
  std::string adresa;
  struct rradha*next;

};
rradha* push(rradha *koka,std::string url) //funksion per shtimin ne rradhe
{
    rradha *temp=new rradha;
    rradha *fundi;
    temp->adresa=url;
    temp->next=0;

        if(koka==0) koka=temp;

        else
        {
            fundi=koka;
            while(fundi->next!=0)
                fundi=fundi->next;

            fundi->next=temp;
        }
    return koka;
}


std::string pop(rradha *koka) //funksion per heqjen nga rradha
{
   std::string vlera;
    if(koka==0) return 0;

    else
    {   rradha *temp=koka;
        while(temp->next==0)
           { temp=temp->next;

           }

         vlera=temp->adresa;
        delete(temp);

    }
    return vlera;
}
/* merr si parameter stringun e permbajtjes se faqes dhe ben extract te gjithe linqet nese perkojne
me formatin e duhur me te cilin behet kerkimi*/


std::set<std::string> extract_hyperlinks( std::string stringFile )
{
    static const boost::regex hl_regex( "((http|https):\/\/((\w+\.)*(\w*))\/([\w\d]+\/{0,1})+", boost::regex_constants::icase  ) ;


    const std::string text = stringFile;

    return { boost::sregex_token_iterator( text.begin(), text.end(), hl_regex, 1 ),
             boost::sregex_token_iterator{} } ;
}

bool gjendet (rradha *koka,string linku) // funksion qe kontrollon nese nje string ndodhet apo jo ne rradhe
{
    rradha *tmp=new rradha;
    tmp=koka;
    if(tmp==NULL) return false;

    else if(tmp->adresa==linku) return true;
    else return gjendet(tmp->next,linku);
}

string downloadURL(string);


int main(int argc,char* argv[])
{
   ofstream outFile;

    rradha *URL=new rradha; //do ruhen url qe duhen vizituar dhe url qe marrim nag ato qe vizitojme
    rradha *URLvizituar=new rradha; //ruhen url qe jane vizituar

    boost::regex re;
    boost::cmatch matches;

    const std::string url = argv[1] ; //merrt linku i fillimit si argument
    std::string down=downloadURL(url) ;// behet download faqja e caktuar

    std::set<std::string> hypl=extract_hyperlinks(down); //behen extract te gjitha url qe ndodhen ne faqe

    push(URLvizituar,url);// e cojme url e fillomit ne rradhen e url-ve te vizituara

    for(std::set<std::string>::iterator i =hypl.begin();i!=hypl.end();i++)
    {
        push(URL,*i); //cdo url qe eshte bere extract nga faqja e pare cohet te rradha e url-ve

    }

    std::stringstream convert(argv[2]); //marrim thellesine e kerkimit
    int thellesiKerkimi;
    convert>>thellesiKerkimi;


    while(URL!=NULL) //deri ne fund te rradhes se url-ve te pavizituar
{   int c [thellesiKerkimi];
      int thellesi=1;
      int cnt=0;
      if(thellesi<thellesiKerkimi)
    {
        int th=1;


           std::string linku;
                linku=pop(URL); //marrim url e rradhes se pavizituar
            string permbajtja=downloadURL(linku); //bejme download permbajtjen
            std::set<std::string> urlLinks=extract_hyperlinks(permbajtja);
            c[cnt]=urlLinks.size();                                         //extractojme te gjitha linket qe ndodhen aty
   for(std::set<std::string>::iterator i =urlLinks.begin();i!=urlLinks.end();i++)
        {  //linkfillim=extract_hyperlinks(path);
            if(!gjendet(URLvizituar,*i)) //i kontrollojme keto linqe nese jane te vizituar apo jo
                push(URL,*i); //nese sjane e cojme te rradha e url-ve te pavizituara
                else continue;



    }
        push(URLvizituar,linku); //pasi i marrim te gjitha url-te qe ka faqja e cojm ete rradha e vizituar
        th++;
        if(c[cnt]==th)
        {
            c[cnt++];
            thellesi++;


        } //rrisim thellesine

        }

}

    outFile.open("argv[3]");// marrim emrin e direktorise
    while(URLvizituar!=NULL)
    {
        string URLfile=pop(URLvizituar); //te gjithe url e vizituara i cojme ne file
        outFile<<URLfile;
    }



   outFile.close();


    return 0;
}

//procesi  download i faqes
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
string downloadURL(string url)
{
    CURL *curl;
  CURLcode res;
  std::string readBuffer;

 // #difine CURL_STATICLIB
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "url");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

    return readBuffer;

}
}
