#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

class kalkulator { //deklaracja klasy nadrzędnej - kalkulator
public:
    vector<char> dzialania;
    vector<float> wartosci;
    char c;
    float x;

    virtual void wczytywanie_danych() { //deklaracja metody wirtualnej - wczytywanie danych
        cout << "Dostepne operacje: +,-,*,/,^,s,% (pierwiastek w kalkulatorze naukowym obliczny jest z liczby nastepnej a pseudonaukowym z poprzedniej wartosci)\nWprowadz rownanie rozdzielajac znaki operacji od liczb spacjami:"<<endl;
        do {
            switch (cin.peek()) { // pobieranie danych
                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '^':
                case 's': {
                    cin >> c;
                    dzialania.push_back(c);
                    break;
                }
                default:
                    cin >> x;
                    wartosci.push_back(x);
                    break;
            }
        } while (cin.get() != '\n');
    };

    virtual float obliczenia() = 0; //deklaracja metody wirtualnej - obliczenia

    virtual void wypisz() { //deklaracja metody wirtualnej - wypisanie wyniku
        cout << "\nWynik:";
    }
};
class naukowy : public kalkulator { //deklaracja klasy dzidziczącej z klakulator - kalkulator naukowy
public:
    vector<char> d; //lokalne dane analogicze do danych z klasy kalkulator
    vector<float> w;
    char c;
    float x;
    float wynik = 0.f;

    void wczytywanie_danych() { //użycie zmodyfikowanej metody wirtualnej - wczytywanie danych
        kalkulator::wczytywanie_danych();
        d = kalkulator::dzialania;
        w = kalkulator::wartosci;
    };

    float obliczenia() {// użycie metody z klasy naukowy - obliczenia
        int j = d.size();
        for (int i = 0; i < j;) { //pętle wyszukujące odpowiednieoperacje i je wykonujące
            if (d[i] == '^') {
                w[i] = pow(w[i], w[i + 1]);
                w.erase(w.begin() + i + 1);
                d.erase(d.begin() + i);
                j--;
            }
            else if (d[i] == 's') {
                w[i] = sqrt(w[i]);
                d.erase(d.begin() + i);
                j--;
            }
            else
                i++;
        }
        for (int i = 0; i < j;) {
            if (d[i] == '/') {
                w[i] = w[i] / w[i + 1];
                w.erase(w.begin() + i + 1);
                d.erase(d.begin() + i);
                j--;
            }
            else if (d[i] == '*') {
                w[i] = w[i] * w[i + 1];
                w.erase(w.begin() + i + 1);
                d.erase(d.begin() + i);
                j--;
            }
            else if (d[i] == '%') {
                w[i] = (int)w[i] % (int)w[i + 1];
                w.erase(w.begin() + i + 1);
                d.erase(d.begin() + i);
                j--;
            }
            else
                i++;
        }
        for (int i = 0; i < j;) {
            if (d[i] == '-') {
                w[i] = w[i] - w[i + 1];
                w.erase(w.begin() + i + 1);
                d.erase(d.begin() + i);
                j--;
            }
            else if (d[i] == '+') {
                ;
                w[i] = w[i] + w[i + 1];
                w.erase(w.begin() + i + 1);
                d.erase(d.begin() + i);
                j--;
            }
            else
                i++;
        }
        wynik = w[0];
        return wynik; //zwrot wyniku

    }

    void wypisz() {  //użycie zmodyfikowanej metody wirtualnej - wypisanie wyniku
        kalkulator::wypisz();
        cout << wynik << endl;
    };
};
class prosty : public kalkulator {
    char wybor; //deklaracja zmiennych w klasie
    double a;
    double b;
    float wynik = 0.f;
public:
    void wczytywanie_danych() { //użycie metody z klasy prosty - wczytywanie danych
        cout
                << "\nWybierz operacje:\nDodawanie +\nOdejmowanie -\nMnozenie *\nDzielenie /\nModulo %\nPierwiastek 2go stopnia liczby nr.1 s\nPodaj znak operacji:";
        cin >> wybor;
        cout << "Podaj pierwsza liczbe:\n";
        cin >> a;
        cout << "Podaj druga liczbe:\n";
        cin >> b;
    }

    float obliczenia() {// użycie metody z klasy naukowy - obliczenia
        switch (wybor) {
            case 43: {
                wynik = a + b;
                return wynik;
            }
            case 45: {
                wynik = a - b;
                return wynik;
            }
            case 42: {
                wynik = a * b;
                return wynik;
            }
            case 47: {
                wynik = a / b;
                return wynik;
            }
            case 37: {
                wynik = (int)a % (int)b;
                return wynik;
            }
            case 115: {
                wynik = sqrt(a);
                return wynik;
            }
            case 83: {
                wynik = sqrt(a);
                return wynik;
            }
            default:
                cout << "Error - Blad wyboru";
                return 0;
        }
    }

    void wypisz() { //użycie zmodyfikowanej metody wirtualnej - wypisanie wyniku
        kalkulator::wypisz();
        cout << wynik << endl;
    };
};
class pseudonaukowy : public kalkulator {

public:
    vector<char> d;//lokalne dane analogicze do danych z klasy kalkulator
    vector<float> w;
    char c;
    float x;
    float wynik = 0.f;

    void wczytywanie_danych() { //użycie zmodyfikowanej metody wirtualnej - wczytywanie danych
        kalkulator::wczytywanie_danych();
        d = kalkulator::dzialania;
        w = kalkulator::wartosci;
    };

    float obliczenia() {// użycie metody zklasy pseudonaukowy - obliczenia
        int j = 0;
        wynik = w[0];
        for (int i = 0; i < d.size(); i++) {//pętla i switch do obliczenia wyniku
            switch (d[i]) {
                case '+':
                    wynik += w[j + 1];
                    j++;
                    break;
                case '-':
                    wynik -= w[j + 1];
                    j++;
                    break;
                case '*':
                    wynik *= w[j + 1];
                    j++;
                    break;
                case '/':
                    wynik /= w[j + 1];
                    j++;
                    break;
                case '%':
                    wynik = fmod(wynik, w[j + 1]);
                    j++;
                    break;
                case '^':
                    wynik = pow(wynik, w[j + 1]);
                    j++;
                    break;
                case 's':
                    wynik = sqrt(wynik);
                    break;
            }
        }
        return wynik;
    }

    void wypisz() {  //użycie zmodyfikowanej metody wirtualnej - wypisanie wyniku
        kalkulator::wypisz();
        cout << wynik << endl;
    };
};
class wybor { // kalsa wyboru kalkulatora
    int w;
    kalkulator* wsk; //deklaracja wskaźnika polimorficznego na klasę nadrzędną kalkulator
    void funkcje(){ //deklaracja funkcji do wywołania funkcji kalkulatora
        wsk->wczytywanie_danych();
        wsk->obliczenia();
        wsk->wypisz();
    };
public:
    wybor() {
        do {//pętla wyboru
            cout << "1 - Kalkulator prosty; 2 - kalkulator pseudonaukowy; 3 - kalkulator naukowy; 4 - wyjscie; Twoj wybor:";
            cin >> w;
            switch (w) {
                case 1: {
                    prosty p; //stworzenie obiektu konktetnego kalkulatora
                    wsk = &p; //przypisanie wskaźnika
                    funkcje(); //wywołanie funkcji
                    break;
                }
                case 2: {
                    pseudonaukowy ps; //stworzenie obiektu konktetnego kalkulatora
                    wsk = &ps; //przypisanie wskaźnika
                    funkcje(); //wywołanie funkcji
                    break;
                }
                case 3: {
                    naukowy n; //stworzenie obiektu konktetnego kalkulatora
                    wsk = &n; //przypisanie wskaźnika
                    funkcje(); //wywołanie funkcji
                    break;
                }
            }
        } while (w != 4);
    };
};

int main() {
    wybor* wy = new wybor(); //stworzenie obiaktu klasy wybór
    delete wy; //destrukcja obiektu klasy wybór
    return 0;
}
