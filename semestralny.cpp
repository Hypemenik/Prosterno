#include <iostream>
#include "semestralny.h"
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <fstream>

#pragma warning( disable : 4996 )



using namespace std;


int main() {
    Prosterno gra; // Tworzenie obiektu gry w prosterno
    Ruch* ruch; // wskaznik na klase ruch ktory bedzie bral ruch od gracza lub od komputera
    //Podanie nickow graczy
    cout << "-----------------------------------------" << endl;
    cout << "WITAM W GRZE PROSTERNO" << endl;
    cout << "\n\nPodaj nick gracza dla bialych pionkow: ";

    string nazwa_graczab;
    cin >> nazwa_graczab;
    Gracz graczB(nazwa_graczab); //tworzenie obiektu gracz i przypisanie do niego nicku 

    cout << "\n\nPodaj nick gracza dla czarnych pionkow: "; //tworzenie obiektu gracz i przypisanie do niego nicku 
    string nazwa_graczac;
    cin >> nazwa_graczac;
    Gracz graczC(nazwa_graczac);
    

    while (true) //start gry
    {
        Sleep(500);
        system("CLS");
        gra.rysujPlansze(); // Wyœwietlanie planszy

        //wypisuje kogo tura
        if (gra.getTura()) {
            cout << "\nRuch bialych(gracza: " << graczB.getNick() << ")\n";
        }
        else {
            cout << "\nRuch czarnych(gracza: " << graczC.getNick() << ")\n";
        }

        // Wprowadzanie ruchu od gracza
        char x, y, nx, ny;
        char ruchx;
        char ruchnx;
        char kolumna;
        char kolumna2;
        std::cout << "Podaj wspolrzedne pionka, ktory chcesz przesunac (A-I 1-8) wpisz X i X aby komputer wykonal ruch: ";
        std::cin >> kolumna >> ruchx;

        if (kolumna != 'X' && ruchx != 'X') { 
            std::cout << "Podaj wspolrzedne docelowe (A-I 1-8): ";
            std::cin >> kolumna2 >> ruchnx;

            //ruch gracza
            x = ruchx;
            y = kolumna;
            nx = ruchnx;
            ny = kolumna2;
            PlayerMove move(x, y, nx, ny); //tworzenie obiektu ruch gracza
            ruch = &move;   
        }

        else {
            //ruch komputera
            Komputer ai;
            ruch = &ai;
            if (gra.getTura()) {
                gra.znajdzBialy(ruch);
            }
            else {
                gra.znajdzCzarny(ruch);
            }
        }



        //Wykonanie ruchu
        if (gra.ruchMozliwy(ruch))
        {
            // Aktualizacja planszy
            gra.wykonajRuch(ruch);

            // Sprawdzenie warunku zwyciêstwa
            if (gra.czyWygrana())
            {
                gra.rysujPlansze();
                std::cout << "Koniec gry. Zwyciezyl gracz " << (gra.getTura() ? graczB.getNick() : graczC.getNick()) << "!" << std::endl;
                gra.getTura() ? graczB.dodaj_wygrane() : graczC.dodaj_wygrane();
                break;
            }

            // Zmiana tury
            gra.zmienTure();
        }
        else
        {
            std::cout << "Nieprawidlowy ruch. Sprobuj ponownie." << std::endl;
        }
    }


    //Wypisanie wynikow roznych graczy z pliku tabela2
    Sleep(5000);
    system("CLS");

    Tabela score;
    string nazwa;
    int wygrane;
    ifstream file("tabela2.txt");
    if (file.is_open()) {
        while (file>> nazwa>>wygrane) {
            {   
                score.dodajTabele(wygrane , nazwa); //tworzenie listy dynamicznej w obiekcie score ktora z pliku przypisuje do jednej zmienej nick a do drugiej liczbe wygranych
            }
        }
    }
    file.close();
    score.dodajGracza(graczB); //dodanie do listy graczy jesli juz ten nick sie znajduje w pliku to dodaje liczbe wygranych
    score.dodajGracza(graczC); //dodanie do listy graczy jesli juz ten nick sie znajduje w pliku to dodaje liczbe wygranych

    score.wypiszTabele(); //wypisanie tabeli wynikow graczy
    
    std::ofstream plik("tabela2.txt");
    if (plik) {
        // Wyczyszczenie pliku
        plik.open("tabela2.txt", std::ios::out | std::ios::trunc);
        plik.close();

        // Otwarcie pliku w trybie "a" (append) do dodawania nowej zawartoœci
        plik.open("tabela2.txt", std::ios::out | std::ios::app);
        plik << score.aktualizacjaTabeli(); //do pliku tabela2 jest wpisywana cala lista dynamiczna zaktualizowana w ktorej sa nicki i wygrane graczy
        plik.close();

    }
    else {
        std::cout << "B³¹d otwierania pliku." << std::endl;
    }
 

    cout << "\n\n\n-----------------Koniec Programu------------------";
    return 0;
}
