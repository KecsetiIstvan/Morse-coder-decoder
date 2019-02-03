#include "keresofa.h"
#include "dconsole.h"
#include <iomanip>

using namespace std;
char fajl[100]="morse.txt";
fstream f(fajl);

//Kecseti István 514/2

faKod a;
faKarakter b;

void SetConsoleCursorVisible(bool lathato){
//Beállítja a kurzor láthatóságát, stackowerflow-os magiiiic
    HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out,&cursorInfo);
    cursorInfo.bVisible=lathato;
    SetConsoleCursorInfo(out,&cursorInfo);
}
void SetConsoleInfo(int hatterszin,int magassag,int szelesseg,bool kurzorLathato,char* fejlec){
//Beállítja a kurzor láthatóságát, a console ablak méretét, háttérszínét illetve a fejlécfeliratát
    SetConsoleCursorVisible(kurzorLathato);
    bgcolor(hatterszin);
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect;
    rect.Top=0;
    rect.Left=0;
    rect.Bottom=magassag;
    rect.Right=szelesseg;
    SetConsoleWindowInfo(handle,1, &rect);
    title(fejlec);

}
void kilepes(){
//Kilép a programból
    exit(1);
}
void keret(int magassag,int szelesseg,int elvalasztoViszintes,int elvalasztoFuggoleges){
//Megrajzolja a console-os ablak keretét
    for(int i=0;i<szelesseg;i++){
        gotoxy(i,0);
        cout<<char(219);
    }

    for(int i=0;i<szelesseg;i++){
        gotoxy(i,magassag);
        cout<<char(219);
    }

    for(int i=0;i<=magassag;i++){
        gotoxy(szelesseg,i);
        cout<<char(219);
    }

    for(int i=0;i<magassag;i++){
        gotoxy(0,i);
        cout<<char(219);
    }
    if(elvalasztoViszintes!=0)
        for(int i=0;i<szelesseg;i++){
            gotoxy(i,elvalasztoViszintes);
            cout<<char(219);
        }
    if(elvalasztoFuggoleges!=0)
        for(int i=elvalasztoViszintes;i<magassag;i++){
            gotoxy(elvalasztoFuggoleges,i);
            cout<<char(219);
        }
}
void fomenurajz(int hatter,int szin,int komment,int cim,int magassag,int szelesseg,int elvalasztoViszintes){
//Kirajzolja a főmenü elemeit
    gotoxy(szelesseg/2-10,elvalasztoViszintes/2);
    textcolor(hatter);
    cout<<"MORSE KODER-DEKODER";
    textcolor(hatter);
    gotoxy(1,elvalasztoViszintes-1);
    cout<<"Keszitette: KECSETI ISTVAN";
    gotoxy(szelesseg/2-10,elvalasztoViszintes+4);
    textcolor(hatter+cim);
    cout<<"A FORDITO MENUJE";
    gotoxy(szelesseg/2-16,elvalasztoViszintes+6);
    cout<<"===========================";
    textcolor(hatter+szin);
    gotoxy(szelesseg/2-16,elvalasztoViszintes+8);
    cout<<"Morse kod szovegge alakitas";
    gotoxy(szelesseg/2-16,elvalasztoViszintes+10);
    cout<<"Szoveg morse kodda alakitas";
    gotoxy(szelesseg/2-13,elvalasztoViszintes+12);
    cout<<"Morse ABC megtekintese";
    gotoxy(szelesseg/2-12,elvalasztoViszintes+14);
    cout<<"Hasznalati utmutato";
    textcolor(hatter+cim);
    gotoxy(szelesseg/2-16,elvalasztoViszintes+16);
    cout<<"===========================";
    textcolor(hatter+komment);
    gotoxy(1,magassag-2);
    cout<<"A menuben valo manoverezes a fel es le nyilakkal, menupont valasztas az enter lenyomasaval tortenik.";
    gotoxy(1,magassag-1);
    cout<<"Kilepes az ESC billentyuvel.";
}
int  menunavigacio(int hatter,int mutato,int elvalasztoViszintes){
//A menüben mozgó fel-le nyilakért illetve azért felel hogy enter lenyomásakor visszaadja hogy éppen mit választpttunk
    int kivalasztott=1;
    int mutatomagassag=elvalasztoViszintes+8;
    int bizgeralo=0;
    while(true){
        bizgeralo++;
        if(bizgeralo<=3){
            gotoxy(70,mutatomagassag);
            textcolor(hatter+mutato);
            cout<<"  ";
            gotoxy(68,mutatomagassag);
            textcolor(hatter+mutato);
            cout<<"<<";
             gotoxy(33,mutatomagassag);
            textcolor(hatter+mutato);
            cout<<"  ";
            gotoxy(35,mutatomagassag);
            textcolor(hatter+mutato);
            cout<<">>";
        }
        else if(bizgeralo==6) bizgeralo=0;
             else{
                 gotoxy(68,mutatomagassag);
                 textcolor(hatter+mutato);
                 cout<<"  ";
                 gotoxy(70,mutatomagassag);
                 textcolor(hatter+mutato);
                 cout<<"<<";
                 gotoxy(35,mutatomagassag);
                 textcolor(hatter+mutato);
                 cout<<"  ";
                 gotoxy(33,mutatomagassag);
                 textcolor(hatter+mutato);
                 cout<<">>";
             }
        if(GetAsyncKeyState(VK_UP)){
            gotoxy(68,mutatomagassag);
            textcolor(hatter+mutato);
            cout<<"    ";
            gotoxy(33,mutatomagassag);
            textcolor(hatter+mutato);
            cout<<"    ";
            mutatomagassag-=2;
            kivalasztott--;
            if(kivalasztott==0){
                kivalasztott=4;
                mutatomagassag=elvalasztoViszintes+14;
            }
        }
        if(GetAsyncKeyState(VK_DOWN)) {
            gotoxy(68,mutatomagassag);
            textcolor(hatter+mutato);
            cout<<"    ";
            gotoxy(33,mutatomagassag);
            textcolor(hatter+mutato);
            cout<<"    ";
            mutatomagassag+=2;
            kivalasztott++;
            if(kivalasztott==5){
                kivalasztott=1;
                mutatomagassag=elvalasztoViszintes+8;
            }
        }
        if(GetAsyncKeyState(VK_RETURN)){
            delay(100);
            if(GetAsyncKeyState(VK_RETURN))
                return kivalasztott;
        }
          if(GetAsyncKeyState(VK_ESCAPE))
            kilepes();
        delay(133);
    }
}
void helpMenu(int hatter,int szin, int komment,int magassag,int szelesseg){
//Kiírja a segítség menüpontot
    keret(magassag,szelesseg,0,0);
    textcolor(hatter+komment);
    gotoxy(1,magassag-1);
    cout<<"A fomenube valo visszalepeshez hasznald az ESC billentyut!";
    gotoxy(szelesseg/2-7,3);
    cout<<"Hasznalati utmutato";

    textcolor(hatter+szin);
    gotoxy(3,8);
    cout<<"A program a morse kodot kepes leforditani szovegge, illetve kepes visszafele is alakitani szoveget morse";
    gotoxy(3,9);
    cout<<"kodda.";
    gotoxy(3,12);
    cout<<"A morse kod leforditasara lehetosegunk van, olyan modon hogy egy morse";
    gotoxy(3,13);
    cout<<"kodot, rovid es hosszu kopogasok sorat, melyek, a rovid kopogas '.' karakter, a hosszu kopogas pedig '-',";
    gotoxy(3,14);
    cout<<"adunk meg a bemeneti mezoben ez kerul leforditasra ENTER lenyomasa utan. Ket kod kozott egy ENTER";
    gotoxy(3,15);
    cout<<"leutes kotelezo, kulonben csak az elso kodot fogja ertelmezni a rendszer.";
    gotoxy(3,16);
    cout<<"Egy kodot, pl legyen A=-.- és B=..., ha le szeretnenk forditani";
    gotoxy(3,17);
    cout<<"olyan kodot mely ezen ket karaktert tartalmazza ilyen modon kell megadnunk a forditando kodot: ";
    gotoxy(3,18);
    cout<<"-.- ENTER ... ENTER ... ENTER -.-";
    gotoxy(3,19);
    cout<<"Tehat az Enter leutesevel, ez a fentiek alapjan ABBA-ra fordul le es jelenik meg a kimeneti mezonkben";

    gotoxy(3,21);
    cout<<"A szoveg morse kodda alakitasa valamivel egyszerubb. Itt a betuket egyesevel kell megadnunk";
    gotoxy(3,22);
    cout<<"vagyis ket karakter kozott ENTER leutese szukseges egymas mellett szavak kozott lehet ket enter, ezutobbi";
    gotoxy(3,23);
    cout<<"elmaradhat akar. Az eredmeny kodot a fent kikotottekenek megfeleloen fogjuk megkapni.";
    gotoxy(3,24);
    cout<<"Mindket forditas soran lehetosegunk van kilepni, elsonel a Q billentyuvel, ekkor a forditas csak a Q-ig";
    gotoxy(3,25);
    cout<<"zajlik. A forditas csakis akkor tortenik amikor a felhasznalo lenyomta az ENTER billentyut.";

    while(true)
        if(GetAsyncKeyState(VK_ESCAPE)){
            delay(150);
            return;
        }

}
void abcMenu(int hatter,int szin, int komment,int magassag,int szelesseg){
//Megjeleníti az abc menüpontot azonos fájlt használva bemenetnek mint a feltoltés fájlja.
    textcolor(hatter+komment);
    gotoxy(1,magassag-2);
    cout<<"A fomenube valo visszatereshez";
    gotoxy(1,magassag-1);
    cout<<"hasznald az ESC billentyut!";
    gotoxy(szelesseg/2-7,1);
    cout<<"Morse ABC ";
    textcolor(hatter+szin);
    int mag=5;
    int szel=3;
    fstream g(fajl);
    struct c{
        char kar;
        string ko;
    }k[150],seged;
    int i=-1;
    while(!g.eof()){
        i++;
        g>>k[i].kar>>k[i].ko;
    }
    g.close();
    for(int j=0;j<i;j++)
        for(int h=j+1;h<=i;h++)
        {
            if(k[j].kar >=k[h].kar){
              seged.kar=k[j].kar;
              seged.ko=k[j].ko;
              k[j].kar=k[h].kar;
              k[j].ko=k[h].ko;
              k[h].kar=seged.kar;
              k[h].ko=seged.ko;
            }
        }
    for(int j=0;j<=i;j++){
        gotoxy(szel,mag);
        mag++;
        if(mag==magassag-5){
            mag=5;
            szel=szelesseg/2+2;
        }
        cout<<k[j].kar<<" == "<<k[j].ko<<endl;
    }
    while(true)
        if(GetAsyncKeyState(VK_ESCAPE)){
            delay(150);
            return;
        }
}
void feltolt(){
//Beolvassa a bemeneti adatokat és beleépíti őket két fába, egyikbe a kulcsok a kódok, másikban pedig a betuk konstans értékei

    a.beszur(' '," ");
    char kar;
    string ko;
    while(f>>kar>>ko){
        a.beszur(kar,ko);
        b.beszur(kar,ko);
    }
    b.beszur(' '," ");
}
void abcTOmorse(int hatter,int szin, int komment,int magassag,int szelesseg){
//Szoveget fordít le morse kódra és írja ki
    textcolor(hatter+komment);
    gotoxy(1,magassag-2);
    cout<<"A fomenube valo visszatereshez";
    gotoxy(1,magassag-1);
    cout<<"hasznalj az '\\' karakter!";
    gotoxy(szelesseg/2-12,1);
    cout<<"Szoveg morse kodda alakitasa ";
    textcolor(hatter+szin);
    gotoxy(3,7);
    cout<<"Karakter:";
    char x;
    int mag=9;
    while(!false){
        gotoxy(4,mag);
        mag++;
        cin>>x;
        if(x=='\\'){
            return;
        }
        x=toupper(x);
        gotoxy(szelesseg/2+2,mag);
        bool megvan;
        b.keres(x,megvan);
        if(!megvan)
            cout<<"'"<<x<<"' egy nem letezo karakter!";
        else cout<<x<<" = "<<b.keres(x,megvan);
    }
}
bool valid(string a){
//Leteszteli hogy egy morse kód csak - és . karakterket tartalmaz-e
    for(unsigned int i=0;i<a.length();i++)
        if(a[i]!='-' and a[i]!='.')
            return false;
    return true;

}
void morseTOabc(int hatter,int szin, int komment,int magassag,int szelesseg){
//Morse kódot fordít karakterekre.
    textcolor(hatter+komment);
    gotoxy(1,magassag-2);
    cout<<"A fomenube valo visszatereshez";
    gotoxy(1,magassag-1);
    cout<<"hasznald a Q billentyut majd ENTER!";
    gotoxy(szelesseg/2-12,1);
    cout<<"Morse kod szovegge alakitasa ";
    textcolor(hatter+szin);
    gotoxy(3,7);
    cout<<"Morse kod:";
    int mag=9;
    while(!false){
    gotoxy(4,mag);
    string x;
    cin>>x;
    if(x=="Q" or x=="q"){
        return;
    }
    if(valid(x)){
        gotoxy(szelesseg/2+2,mag);
        bool megvan;
        mag++;
        a.keres(x,megvan);
        if(!megvan)
            cout<<"'"<<x<<"' egy nem letezo karakter kodja!";
        else cout<<setw(5)<<x<<" = "<<a.keres(x,megvan);
    }
    else {
        cout<<"Helytelen kod!";
        delay(1000);
        return;
    }
    }
}
int main(){
    feltolt();
    int magassag=35;
    int szelesseg=110;
    int hatter=128; //240
    int szin=0;
    int komment=15;
    int mutato=12;
    int cim=0;
    char *cimSor="Morse kod/dekod-er";
    while(true){
        delay(150);
        clrscr();
        SetConsoleInfo(hatter,magassag,szelesseg,false,cimSor);
        keret(magassag,szelesseg,10,0);
        fomenurajz(hatter,szin,komment,cim,magassag,szelesseg,10);
        int kivalasztott=menunavigacio(hatter,mutato,10);
        switch(kivalasztott){
        case 1:{
                clrscr();
                SetConsoleInfo(hatter,magassag,szelesseg,true,cimSor);
                keret(magassag,szelesseg,2,szelesseg/2);
                morseTOabc(hatter,szin,komment,magassag,szelesseg);
                kivalasztott=0;
                break;
        }
        case 2:{
                clrscr();
                SetConsoleInfo(hatter,magassag,szelesseg,true,cimSor);
                keret(magassag,szelesseg,2,szelesseg/2);
                abcTOmorse(hatter,szin,komment,magassag,szelesseg);
                break;
            }
        case 3:{
                clrscr();
                SetConsoleInfo(hatter,magassag,szelesseg,false,cimSor);
                keret(magassag,szelesseg,2,szelesseg/2);
                abcMenu(hatter,szin,komment,magassag,szelesseg);
            }
            break;
        case 4:{
                clrscr();
                SetConsoleInfo(hatter,magassag,szelesseg,false,cimSor);
                keret(magassag,szelesseg,6,0);
                helpMenu(hatter,szin,komment,magassag,szelesseg);
            }
            break;
    }
    }
    return 0;
}
