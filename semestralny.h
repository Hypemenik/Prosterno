#pragma once
#pragma warning( disable : 4996 )


#include <vector>
#include <string>

using namespace std;


class Ruch {
public:
    Ruch() {
        x = 0;
        y = 0;
        nx = 0;
        ny = 0;
    }
    Ruch(int x, int y, int nx, int ny) {
        this->x = x;
        this->y = y;
        this->nx = nx;
        this->ny = 0;
    }
    int x;
    int y;
    int nx;
    int ny;
};

class Prosterno 
{
protected:
    char plansza[8][9]; // Plansza warcabowa
    bool turaGracza1; // Zmienna okreœlaj¹ca, czyja tura

public:
    Prosterno();
    bool getTura() { return turaGracza1; };
    void rysujPlansze();
    bool ruchMozliwy(Ruch* r );
    void wykonajRuch(Ruch* r);
    bool czyObokPrzeciwnik(Ruch* r);
    void bicieCzarnych(Ruch* r);
    void bicieBialych(Ruch* r);
    bool czyWygrana();
    void znajdzBialy(Ruch* r);
    void znajdzCzarny(Ruch* r);
    void zmienTure()
    {
        turaGracza1 = !turaGracza1;
    }


};




class Gracz   {
private:
    std::string nick;
    int wygrane;

public:
    Gracz* nast = nullptr;
    Gracz() {
        nick = "X";
        this->wygrane = 0;
    }
    Gracz(const Gracz& player) {
        nick = player.nick;
        wygrane = player.wygrane;
    }
    Gracz(std::string nazwa) {
        nick = nazwa;
       this->wygrane = 0;
    }
    ~Gracz() {
        delete nast;
    }
    void setWygrane(int win) {
        wygrane = win;
    }
    std::string getNick() {
        return nick;
    }
    int getWygrane() {
        return wygrane;
    }
   void dodaj_wygrane() {
       wygrane++;
   }
   void wypisz();

};


class Tabela  {
    Gracz* glowa = nullptr;
public:
    Tabela() {};
    void dodajTabele(int wynik, std::string Nick);
    void wypiszTabele();
    void dodajGracza(Gracz player);
   string aktualizacjaTabeli();
};



class PlayerMove : public Ruch {
private:
    char cx;
    char cy;
    char cnx;
    char cny;
public:
    PlayerMove(char x1, char y1, char nx1, char ny1) {
        cx = x1;
        cy = y1;
        cnx = nx1;
        cny = ny1;
        x = zamiana_chara_na_int_x(cx);
        y = zamiana_chara_na_int(cy);
        nx = zamiana_chara_na_int_x(cnx);
        ny = zamiana_chara_na_int(cny);
    };
    int zamiana_chara_na_int(char X);
    int zamiana_chara_na_int_x(char X);

};




class Komputer : public Ruch {

public:
    Komputer() {
        x = 0;
        y = 0;
        nx = 0;
        ny = 0;
    }

};

