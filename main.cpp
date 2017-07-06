#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

void wprowadzenieKandydatow()
{
	cout << "Wprowadzanie kandydatow" << endl;
	
	// Deklaracja stringow do wprowadzenia danych
	string imie_i_nazwisko, partia;
	
	// Deklaracja strumienia zapisu do pliku
	ofstream plik("kandydaci.txt");
	
	// Definicja zmiennych czy kontynuowac wprowadzanie kolejno partii i kandydatow;
	char czy_kontynuowac_partia = 't', czy_kontynuowac_kandydat = 't';
	
	// Petla wykonywana dopoki zmienna czy_kontynuowac_partia jest rowna 'T' lub 't'
	while (czy_kontynuowac_partia == 't' || czy_kontynuowac_partia == 'T')
	{
		cout << "Podaj nazwe partii politycznej: ";
		getline(cin, partia);
	
		// Petla wykonywana dopoki zmienna czy_kontynuowac jest rowna 'T' lub 't', zmienna i jako licznik uczestnika
		for (unsigned int i = 1; czy_kontynuowac_kandydat == 't' || czy_kontynuowac_kandydat == 'T'; i++)
		{
			cout << "Podaj imie i nazwisko kandydata: ";
			getline(cin, imie_i_nazwisko);
			
			// Zapis do pliku
			plik << i << endl << imie_i_nazwisko << endl << partia << endl;
			
			cout << "Wprowadzono kandydata. Czy dodac kolejnego kandydata w tej partii? [T/N]: ";
			cin >> czy_kontynuowac_kandydat;
			cin.ignore();
		}
		
		// Zresetowanie zmiennej czy kontynuowac kandydat
		czy_kontynuowac_kandydat = 't';
		
		cout << "Czy dodac kolejna partie polityczna? [T/N]: ";
		cin >> czy_kontynuowac_partia;
		cin.ignore();
	}
	
	plik.close();
}

void statystyki()
{
	cout << "Statystyki kandydatow" << endl;
	
	// Deklaracja strumienia odczytu z pliku
	ifstream plik("kandydaci.txt");
	
	// Liczba glosow kazdego z kandydatow
	unsigned int liczba_kandydatow = 0;
	string kandydat_numer[100];
	string kandydat_imie_i_nazwisko[100];
	string kandydat_partia[100];
	unsigned int kandydat_wynik[100];
	
	// Liczba glosow partii
	unsigned int liczba_partii = 0;
	string partia[20];
	unsigned int partia_wynik[20];
	
	// Suma wszystkich glosow (do obliczen procentowych)
	unsigned int suma_glosow = 0;
	
	// Wyzerowanie tablicy z wynikami partii
	for (unsigned int i = 0; i < 20; i++)
	{
		partia_wynik[i] = 0;
	}
	
	// Czytanie kazdej linii z pliku kandydaci.txt
	for (unsigned int i = 0; getline(plik, kandydat_numer[i]); i++)
	{
		// Pobranie danych kandydata oraz partii
		getline(plik, kandydat_imie_i_nazwisko[i]);
		getline(plik, kandydat_partia[i]);

		// Wyswietlenie danych kandydata
		cout << kandydat_numer[i] << ". " << kandydat_imie_i_nazwisko[i] << " - " << kandydat_partia[i] << ": " << endl;
		
		cout << "Podaj liczbe glosow kandydata: ";
		cin >> kandydat_wynik[i];
		
		// Zliczanie glosow partii
		// Wyzerowanie zmiennej pomocniczej
		unsigned int przetwarzana_partia = 0;
		bool czy_dodac_partie = true;
		
		// Petla sprawdzajaca czy partia juz jest dodana
		for (unsigned int j = 0; j < liczba_partii; j++)
		{
			// Sprawdzenie czy partia kandydata juz istnieje
			if (partia[j] == kandydat_partia[i])
			{
				// Jezeli tak to ustawienie indeksu elementu w tablicy partia[] do zmiennej przetwarzana_partia
				przetwarzana_partia = j;
				
				// Ustawienie flagi istnienia partii w tablicy
				czy_dodac_partie = false;
			}
		}
		
		// Jezeli partia nie istnieje to dodanie jej do tablicy partii
		if (czy_dodac_partie)
		{
			// Przypisanie nazwy partii do zmiennej
			partia[liczba_partii] = kandydat_partia[i];
			
			// Zmiana przetwarzanej partii
			przetwarzana_partia = liczba_partii;
			
			// Zwiekszenie licznika wszystkich partii
			liczba_partii++;
		}
		
		// Dodanie glosow w przetwarzanej partii
		partia_wynik[przetwarzana_partia] += kandydat_wynik[i];
		
		// Podliczenie wszystkich glosow
		suma_glosow += kandydat_wynik[i];
		
		// Liczba kandydatow
		liczba_kandydatow++;
	}
	
	// Wyswietlenie wynikow wszystkich partii
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "- Wyniki wyborow - partie -----------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Razem wszystkich oddanych glosow glosow: " << suma_glosow << " = 100%" << endl;
	
	// Zmienna pomocnicza
	unsigned int glosow;
	
	for (unsigned int i = 0; i < liczba_partii; i++)
	{
		// Wyliczenie procentowe
		glosow = partia_wynik[i] * 100 / suma_glosow;
		
		cout << partia[i] << " - razem glosow: " << partia_wynik[i] << " = ~" << glosow << "%" << endl;
	}
	
	// Zmienne pomocnicze do sortowania
	unsigned int tmp_wynik;
	string tmp_numer;
	string tmp_imie_i_nazwisko;
	string tmp_partia;
	
	// Wysortowanie wynikow kandydatow (sortofanie babelkowe)
	bool dalej = true;
	while (dalej) //sortuj az wszystko posortowane
	{
		dalej = false;
		for (unsigned int i = 0 ; i < liczba_kandydatow - 1; i++)
		{
			if (kandydat_wynik[i] < kandydat_wynik[i + 1]) 
			{
				tmp_wynik = kandydat_wynik[i];
				kandydat_wynik[i] = kandydat_wynik[i + 1];
				kandydat_wynik[i + 1] = tmp_wynik;
				
				tmp_numer = kandydat_numer[i];
				kandydat_numer[i] = kandydat_numer[i + 1];
				kandydat_numer[i + 1] = tmp_numer;
				
				tmp_imie_i_nazwisko = kandydat_imie_i_nazwisko[i];
				kandydat_imie_i_nazwisko[i] = kandydat_imie_i_nazwisko[i + 1];
				kandydat_imie_i_nazwisko[i + 1] = tmp_imie_i_nazwisko;
				
				tmp_partia = kandydat_partia[i];
				kandydat_partia[i] = kandydat_partia[i + 1];
				kandydat_partia[i + 1] = tmp_partia;
				
				dalej = true;
			}
		}
	}
	
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "- Wyniki wyborow - kandydaci --------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Razem wszystkich oddanych glosow glosow: " << suma_glosow << " = 100%" << endl;
	
	// Wyswietlenie wynikow kandydatow
	for (unsigned int i = 0; i < liczba_kandydatow; i++)
	{
		// Wyliczenie procentowe
		glosow = kandydat_wynik[i] * 100 / suma_glosow;
		
		// Wyswietlenie tylko kandydatow z glosami powyzej 5%
		if (glosow > 5)
		{
			cout << kandydat_numer[i] << ". " << kandydat_imie_i_nazwisko[i] << " - " << kandydat_partia[i] << " - razem glosow: " << kandydat_wynik[i] << " = ~" << glosow << "%" << endl;
		}
	}
}

int main(int argc, char *argv[])
{
    // Menu startowe
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "-- Program WYBORY 2011. Copyright by Krzysztof Krysiak. All rights reserved. --" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "1 - Wprowadzenie kandydatow do pliku (kandydaci.txt)" << endl;
    cout << "2 - Wprowadzenie liczby glosow do kazdego z kandydatow," << endl;
    cout << "    statystyki oraz zapis wynikow do pliku (wyniki.txt)" << endl;
    cout << "0 - Wyjscie z programu" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    // Deklaracja zmiennej akcji
    char akcja;
    cout << "Wybierz akcje do wykonania (podaj numer): ";
    cin >> akcja;
	cin.ignore();
    
    if (akcja == '0') // Jezeli wybrano opcje wyjscia z programu
    {
        cout << "Zamykam program" << endl;
    }
    else if (akcja == '1') // Jezeli wybrano opcje wprowadzenia danych kandydatow do pliku
    {
        wprowadzenieKandydatow();
    }
    else if (akcja == '2') // Jezeli wybrano opcje wprowadzenia liczby glosow i statystyk
    {
        statystyki();
    }
    else
    {
        cout << "Wybrano niepoprawna akcje, zamykam program" << endl;
    }

    system("PAUSE");
    return EXIT_SUCCESS;
}
