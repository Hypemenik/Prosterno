#include "semestralny.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

#pragma warning( disable : 4996 )


using namespace std;



Prosterno::Prosterno() {
    // Inicjalizacja planszy
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if ((i == 0) &&  j % 2 == 1)
            {
                if (i < 2)
                    plansza[i][j] = 'X';
                continue;
            }
            if ((i == 1) && j % 2 == 0)
            {
                if (i < 2)
                    plansza[i][j] = 'X';
                continue;
            }
            
            if ((i + j) % 2 == 0)
            {
                // Pionki gracza 1
                 if (i > 5)
                    plansza[i][j] = 'O'; // Pionki gracza 2
                else
                    plansza[i][j] = ' '; // Puste pola
            }
            else
            {
                plansza[i][j] = ' '; // Puste pola
            }
        }
    }

   turaGracza1 = true; // Tura gracza 1 na pocz¹tku gry
}

void Prosterno::rysujPlansze() {

    std::cout << "   A B C D E F G H I" << std::endl;
    std::cout << "  -------------------" << std::endl;

    for (int i = 0; i < 8; ++i)
    {
        std::cout << i + 1 << " |";
        for (int j = 0; j < 9; ++j)
        {
            std::cout << plansza[i][j] << "|";
        }
        std::cout << " " << i + 1 << std::endl;
        std::cout << "  -------------------" << std::endl;
    }

    std::cout << "   A B C D E F G H I" << std::endl;
}




bool Prosterno::ruchMozliwy(Ruch* r){
    // Sprawdzanie, czy ruch jest mo¿liwy
    if (r->nx < 0 || r->ny < 0 || r->nx >= 8 || r->ny >= 9 )
        return false; // Poza granicami planszy

    if (plansza[r->nx][r->ny] != ' ')
        return false; // Cel zajêty

    char pionek = plansza[r->x][r->y];
    int dx = r->nx - r->x;
    int dy = r->ny - r->y;

    // Sprawdzanie, czy ruch jest zgodny z zasadami gry
    if (pionek == 'X' && getTura()== false)
    {
        if (std::abs(dx) == 1 && std::abs(dy)==1) // Zwyk³y ruch o 1 pole na ukos
            return true;
    }
    else if (pionek == 'O' && getTura() == true) {
        if (std::abs(dx) == 1 && std::abs(dy) == 1) // Zwyk³y ruch o 1 pole na ukos
            return true;
    }

    return false;

}
bool Prosterno::czyObokPrzeciwnik(Ruch* r) { //sprawdzenie czy obok jest inny pionek ktorego mozna zbic
    bool tura;
    tura = getTura();
    int licznik = 0; //sprawdza ile jest obok przecziwnych pionkow
    if (tura == true) { // ruch bialych jesli tak sprawdza gorne wartosci
        char gorny = plansza[r->nx - 1][r->ny];
        char prawy = plansza[r->nx][r->ny + 1];
        char lewy = plansza[r->nx][r->ny - 1];
        if (gorny == 'X')
            licznik++;
        if (prawy == 'X')
            licznik++;
        if (lewy == 'X')
            licznik++;
    }
    if (tura == false) {// ruch czarnych jesli tak sprawdza dolne wartosci

        char dolny = plansza[r->nx + 1][r->ny];
        char prawy = plansza[r->nx][r->ny + 1];
        char lewy = plansza[r->nx][r->ny - 1];
        if (dolny == 'O')
            licznik++;
        if (prawy == 'O')
            licznik++;
        if (lewy == 'O')
            licznik++;
    }

    if (licznik > 0) {
        return true;
    }
    return false;
}

void Prosterno::znajdzBialy(Ruch* r) //ruch komputera znajduje najblizszy bialy ktory moze sie ruszyc
{
    
        for (int x = 1; x < 7; ++x) {
            for (int y = 1; y < 8; ++y) {
                if (plansza[x][y] == 'O' && (plansza[x-1][y+1] == ' ' || plansza[x-1][y-1] == ' ')) {
                    r->x = x;
                    r->y = y;
                    if (plansza[x - 1][y + 1] == ' ') {
                        r->nx = x - 1;
                        r->ny = y + 1;
                        break;
                    }
                    else {
                        r->nx = x - 1;
                        r->ny = y - 1;
                        break;
                    }
                }
            }
        }
   

}

void Prosterno::znajdzCzarny(Ruch* r) //ruch komputera znajduje najblizszy czarny ktory moze sie ruszyc
{

    for (int x = 1; x < 7; ++x) {
        for (int y = 1; y < 8; ++y) {
            if (plansza[x][y] == 'X' && (plansza[x + 1][y + 1] == ' ' || plansza[x + 1][y - 1] == ' ')) {
                r->x = x;
                r->y = y;
                if (plansza[x + 1][y + 1] == ' ') {
                    r->nx = x + 1;
                    r->ny = y + 1;
                    break;
                }
                else {
                    r->nx = x + 1;
                    r->ny = y - 1;
                    break;
                }
            }
        }
    }


}

void Prosterno::bicieCzarnych(Ruch* r) {
   /* char gorny = plansza[nx - 1][ny];
    char prawy = plansza[nx][ny + 1];
    char lewy = plansza[nx][ny - 1];*/

    if (plansza[r->nx - 1][r->ny] == 'X') { // bicie pionka co jest pole wyzej od bialego 
        if (plansza[r->nx - 3][r->ny] == 'X' || r->nx-1==0 || r->nx - 2 == 0  ) {
            cout << "\nBrak miejsc dla X pionka usuniety zostaje z planszy z tego powodu\n";
            plansza[r->nx - 1][r->ny] = ' ';
        }
        else {
            plansza[r->nx - 1][r->ny] = ' ';
            if (r->ny + 1 != 8 && r->ny - 1 != 0 && r->ny + 2 != 8 && r->ny - 2 != 0) { //sprawdanie czy wychodzi za pole jesli nie to 2 pola dalej przesuniety zbity pionek jest
                plansza[r->nx - 3][r->ny] = 'X';
            }
        }
    }
    if (plansza[r->nx][r->ny + 1] == 'X') { // bicie pionka ktory jest na prawo od bialego
        if(plansza[r->nx][r->ny+3] == 'X') {
        cout << "\nBrak miejsc dla X pionka usuniety zostaje z planszy z tego powodu\n";
        plansza[r->nx][r->ny + 1] = ' ';
        }
        else {
            plansza[r->nx][r->ny + 1] = ' ';
            if (r->ny + 1 != 8 && r->ny - 1 != 0 && r->ny + 2 != 8 && r->ny - 2 != 0) { //sprawdanie czy wychodzi za pole jesli nie to 2 pola dalej przesuniety zbity pionek jest
                plansza[r->nx][r->ny + 3] = 'X';
            }
        }
    }
    if (plansza[r->nx][r->ny - 1] == 'X') { // bicie pionka ktory jest na lewo od bialego
        if (plansza[r->nx][r->ny - 3] == 'X') {
            cout << "\nBrak miejsc dla X pionka usuniety zostaje z planszy z tego powodu\n";
            plansza[r->nx][r->ny - 1] = ' ';
        }
        else {
            plansza[r->nx][r->ny - 1] = ' ';
            if (r->ny + 1 != 8 && r->ny - 1 != 0 && r->ny + 2 != 8 && r->ny - 2 != 0) { //sprawdanie czy wychodzi za pole jesli nie to 2 pola dalej przesuniety zbity pionek jest
                plansza[r->nx][r->ny - 3] = 'X';
            }
            
        }
    }
}

void Prosterno::bicieBialych(Ruch *r) {
    /* char gorny = plansza[nx - 1][ny];
     char prawy = plansza[nx][ny + 1];
     char lewy = plansza[nx][ny - 1];*/

    if (plansza[r->nx + 1][r->ny] == 'O' ) {  // bicie pionka co jest pole nizej od czarnego
        if (plansza[r->nx + 3][r->ny] == 'O' || r->nx + 1 == 7 || r->nx + 2 == 7)  {
            cout << "\nBrak miejsc dla O pionka usuniety zostaje z planszy z tego powodu\n";
            plansza[r->nx + 1][r->ny] = ' ';
           
        }
        else {
            plansza[r->nx + 1][r->ny] = ' ';
            if (r->ny + 1 != 8 && r->ny - 1 != 0 && r->ny + 2 != 8 && r->ny - 2 != 0) { //sprawdanie czy wychodzi za pole jesli nie to 2 pola dalej przesuniety zbity pionek jest
                plansza[r->nx + 3][r->ny] = 'O'; //?? 
            }
            
        }
    }
    if (plansza[r->nx][r->ny + 1] == 'O') { // bicie pionka co jest prawo od czarnego
        if (plansza[r->nx][r->ny + 3] == 'O') {
            cout << "\nBrak miejsc dla O pionka usuniety zostaje z planszy z tego powodu\n";
            plansza[r->nx][r->ny + 1] = ' ';
        }
        else {
            plansza[r->nx][r->ny + 1] = ' ';
            
            if (r->ny + 1 != 8 && r->ny - 1 != 0 && r->ny + 2 != 8 && r->ny - 2 != 0 ) { //sprawdanie czy wychodzi za pole jesli nie to 2 pola dalej przesuniety zbity pionek jest
                plansza[r->nx][r->ny + 3] = 'O';
            }
        }
    }
    if (plansza[r->nx][r->ny - 1] == 'O') { // bicie pionka co jest na lewo od czarnego
        if (plansza[r->nx][r->ny - 3] == 'O') {
            cout << "\nBrak miejsc dla O pionka usuniety zostaje z planszy z tego powodu\n";
            plansza[r->nx][r->ny - 1] = ' ';
        }
        else {
            plansza[r->nx][r->ny - 1] = ' ';
            if (r->ny + 1 != 8 && r->ny - 1 != 0 && r->ny + 2 != 8 && r->ny - 2 != 0) { //sprawdanie czy wychodzi za pole jesli nie to 2 pola dalej przesuniety zbity pionek jest
                plansza[r->nx][r->ny - 3] = 'O';
            }
        }
    }
}

void Prosterno::wykonajRuch(Ruch *r) {
    // Wykonanie ruchu
        plansza[r->nx][r->ny] = plansza[r->x][r->y];
        plansza[r->x][r->y] = ' ';

        // Sprawdzenie i wykonanie bicia przeciwnika
        bool obok;
        obok = czyObokPrzeciwnik(r);
        if (obok == true) { //bicie 
            if (std::abs(r->nx - r->x) == 1 && std::abs(r->ny - r->y) == 1)
            {
                if (getTura() == true) {
                    bicieCzarnych(r);
                }
                else if (getTura() == false) {
                    bicieBialych(r);
                }
            }
        }
}

bool Prosterno::czyWygrana() {
    // Sprawdzanie warunku zwyciêstwa dla gracza 1
    bool gracz1Wygral = true;
   bool gracz2Wygral = true;
    for (int i = 0; i < 8; ++i)
    {   
        for (int j = 0; j < 9; ++j)
        {   
            if (plansza[0][j] == 'O') {
                return gracz2Wygral;
            }
            if (plansza[7][j] == 'X') {
                return gracz1Wygral;
            }
            if (plansza[i][j] == 'O')
            {
                gracz1Wygral = false;
                break;
            }
        }
    }

    if (gracz1Wygral)
        return true;

    // Sprawdzanie warunku zwyciêstwa dla gracza 2
    
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {   
            if (plansza[0][j] == 'O') {
                return gracz2Wygral;
            }
            if (plansza[i][j] == 'X')
            {
                gracz2Wygral = false;
                break;
            }
        }
        if (!gracz2Wygral)
            break;
    }

    return gracz2Wygral;
}

int PlayerMove::zamiana_chara_na_int(char X) { 
    int ruch;
    if (X == 'A' || X == 'a') {
        ruch = 0;
    }
    else if (X == 'B' || X == 'b') {
        ruch = 1;
    }
    else if (X == 'C' || X == 'c') {
        ruch = 2;
    }
    else if (X == 'D' || X == 'd') {
        ruch = 3;
    }
    else if (X == 'E' || X == 'e') {
        ruch = 4;
    }
    else if (X == 'F' || X == 'f') {
        ruch = 5;
    }
    else if (X == 'G' || X == 'g') {
        ruch = 6;
    }
    else if (X == 'H' || X == 'h') {
        ruch = 7;
    }
    else if (X == 'I' || X == 'i') {
        ruch = 8;
    }
    else {
        ruch = 10; //poza plansza
        return ruch;
    }
    return ruch;
}
int PlayerMove::zamiana_chara_na_int_x(char X) {
    int ruch;
    if (X == '1') {
        ruch = 0;
    }
    else if (X == '2') {
        ruch = 1;
    }
    else if (X == '3') {
        ruch = 2;
    }
    else if (X == '4') {
        ruch = 3;
    }
    else if (X == '5') {
        ruch = 4;
    }
    else if (X == '6') {
        ruch = 5;
    }
    else if (X == '7') {
        ruch = 6;
    }
    else if (X == '8') {
        ruch = 7;
    }
    else {
        ruch = 10; //poza plansza
        return ruch;
    }
    return ruch;
}


void Tabela::dodajTabele(int wynik, std::string nazwa) {

    if (glowa == nullptr) {
        glowa = new Gracz(nazwa);
        glowa->setWygrane(wynik);
        return;
    }
    else {
        Gracz* aktualne = glowa;
        while (aktualne->nast != nullptr) {
            aktualne = aktualne->nast;
        }
        aktualne->nast = new Gracz(nazwa);
        aktualne->nast->setWygrane(wynik);
    }

}

void Tabela::wypiszTabele() {
    Gracz* aktualny = glowa;
    std::cout << "\n--------------------------------------------------------\n ";
    cout << "                 WYNIKI GRACZY                                     \n";
    while (aktualny != nullptr) {
         aktualny->wypisz();
         aktualny = aktualny->nast;
    }
}

void Gracz::wypisz() {
    std::string Nick = getNick();
    int wygrane = getWygrane();
    std::cout << "\nNazwa gracza: " << Nick << "      Wygrane: " << wygrane;
}

void Tabela::dodajGracza(Gracz player) {
    Gracz* aktualny = glowa;
    while (aktualny != nullptr) {
        if (player.getNick() == aktualny->getNick()) {
            aktualny->setWygrane(aktualny->getWygrane() + player.getWygrane());
            return;
        }
        else if (aktualny->nast == nullptr) {
            aktualny->nast = new Gracz(player);
            return;
        }
        aktualny = aktualny->nast;
    }
}

string Tabela::aktualizacjaTabeli() {
    string tekst;
    Gracz* aktualny = glowa;
    while (aktualny != nullptr) {
        int liczba;
        string zamiana;
        tekst += aktualny->getNick();
        tekst += " ";
        liczba =  aktualny->getWygrane();
        zamiana = to_string(liczba);
        tekst += zamiana;

        tekst += "\n";
        aktualny = aktualny->nast;
    }
    return tekst;
}