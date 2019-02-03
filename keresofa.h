#ifndef KERESOFA_H_INCLUDED
#define KERESOFA_H_INCLUDED
#include <iostream>
#include <queue>
#include <fstream>
using namespace std;
struct pont{
    char karakter;
    string kod;
    pont *jobb;
    pont *bal;
};

class faKarakter{
//karakter kulcsa alapú fa
    pont *gyoker;
    void felszabadit(pont* gyok){
    //destruktor
       pont* save;
       for(pont* it =gyok; it != NULL;it=save)
            if(it->bal==NULL){
                save=it->jobb;
                delete it;
            }
        else{
            save=it->bal;
            it->bal=save->jobb;
            save->jobb=it;
        }
    }
    void be(pont*& gy,char karak,string ko){
    //beszúr egy elemet
        if (gy == NULL) {
            gy = new pont;
            gy->jobb = NULL;
            gy->bal = NULL;
            gy->karakter = karak;
            gy->kod=ko;
        }
        else{

            if (karak<gy->karakter){
                be(gy->bal, karak,ko);
            }
            else{
                    if(karak>gy->karakter){
                        be(gy->jobb, karak,ko);
                    }
                    else
                       throw "LetezoKod";
                }
        }
    }
    void kereses(pont *gyok, char x,pont*& p){
        if (gyok == NULL){
            p=NULL;
            return;
        }
        queue<pont *> q;
        q.push(gyok);
        while (!q.empty()){
            pont *akt = q.front();
            if (akt->karakter == x){
                p=akt;
                return;
            }
            q.pop();
            if (akt->bal != NULL)
                q.push(akt->bal);
            if (akt->jobb != NULL)
                q.push(akt->jobb);
        }
        p=NULL;
    }
    void tor(pont*& r, pont* q){
      if (r->jobb != NULL)
        tor(r->jobb, q);
      else {
        q->kod = r->kod;
        q->karakter=r->karakter;
        q = r;
        r = r->bal;
        delete q;
      }
    }
    void torol(char ko,pont*& fa,bool& megvan){
    //Megkeresi a kitorlendp elemet
        pont* q;
        if (fa == NULL) megvan = false;
        else
        if (ko<fa->karakter) torol(ko,fa->bal, megvan);
        else
            if (ko>fa->karakter) torol(ko,fa->jobb,megvan);
            else {
                megvan = true;
                q = fa;
                if (q->jobb == NULL) {
                    fa = q->bal;
                delete q;
                }
                else
                    if (q->bal == NULL) {
                        fa = q->jobb;
                        delete q;
                    }
                    else tor(q->bal, q);
      }
    }
public:
    faKarakter(){
        gyoker=NULL;
    }
    ~faKarakter(){
        felszabadit(gyoker);
    }
    bool ures(){
        return gyoker==NULL;
    }
    void beszur(char karak,string ko){
            be(gyoker,karak,ko);
    }
    string keres(char k, bool& megvan){
        pont* p;
        kereses(gyoker, k, p);
        megvan = (p != NULL);
        if(megvan)
            return p->kod;
    }
    void torles(char k, bool& megvan){
        torol(k,gyoker, megvan);
    }
};
class faKod{
//Kód kulcs alapu bináris keresõfa.
    pont *gyoker;
    void felszabadit(pont* gyok){
      pont* save;
      for(pont* it =gyok; it != NULL;it=save)
        if(it->bal==NULL){
            save=it->jobb;
            delete it;
        }
        else{
            save=it->bal;
            it->bal=save->jobb;
            save->jobb=it;
        }
    }
    void be(pont*& gy,char karak,string ko,int mutato){
        if (gy == NULL) {
            gy = new pont;
            gy->jobb = NULL;
            gy->bal = NULL;
            gy->karakter = karak;
            gy->kod=ko;
        }
        else{

            if (ko[mutato]=='-'){
                be(gy->bal, karak,ko,++mutato);
            }
            else{
                    if(ko[mutato]=='.'){
                        be(gy->jobb, karak,ko,++mutato);
                    }
                    else
                       throw "LetezoKod";
                }
        }
    }
    void kereses(pont *gyok, string x,pont*& p){
        if (gyok == NULL){
            p=NULL;
            return;
        }
        queue<pont *> q;
        q.push(gyok);
        while (!q.empty()){
            pont *akt = q.front();
            if (akt->kod == x){
                p=akt;
                return;
            }
            q.pop();
            if (akt->bal != NULL)
                q.push(akt->bal);
            if (akt->jobb != NULL)
                q.push(akt->jobb);
        }
        p=NULL;
    }
    void tor(pont*& r, pont* q){
      if (r->jobb != NULL)
        tor(r->jobb, q);
      else {
        q->kod = r->kod;
        q->karakter=r->karakter;
        q = r;
        r = r->bal;
        delete q;
      }
    }
    void torol(string ko,pont*& fa,bool& megvan,int mutato){
        pont* q;
        if (fa == NULL) megvan = false;
        else
        if (ko[mutato]=='-') torol(ko,fa->bal, megvan,++mutato);
        else
            if (ko[mutato]=='.') torol(ko,fa->jobb,megvan,++mutato);
            else {
                megvan = true;
                q = fa;
                if (q->jobb == NULL) {
                    fa = q->bal;
                delete q;
                }
                else
                    if (q->bal == NULL) {
                        fa = q->jobb;
                        delete q;
                    }
                    else tor(q->bal, q);
      }
    }
public:
    faKod(){
        gyoker=NULL;
    }
    ~faKod(){
        felszabadit(gyoker);
    }
    bool ures(){
        return gyoker==NULL;
    }
    void beszur(char karak,string ko){
            be(gyoker,karak,ko,0);
    }
    char keres(string k, bool& megvan){
        pont* p;
        kereses(gyoker, k, p);
        megvan = (p != NULL);
        if(megvan)
            return p->karakter;
    }
    void torles(string k, bool& megvan){
        torol(k,gyoker, megvan,0);
    }
};

#endif // KERESOFA_H_INCLUDED
