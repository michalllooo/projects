
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
char literaL() {
	srand(time(0));
	char litery[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'z' };
	int rozmiar = sizeof(litery);

	if (rozmiar == 0) {
		return 0; // wszystkie wylosowane juz sa
	}

	int indeks = rand() % rozmiar;  // modulo daje zakres 0 do 20
	char wylosowanaLitera = litery[indeks];  //losowanie litery po ineksie 


	for (int i = indeks; i < rozmiar - 1; i++) {
		litery[i] = litery[i + 1];
	}
	rozmiar--;

	return wylosowanaLitera;
}





void timer(int seconds, int& remaining_time, int& is_running) {     //czas, ref do timera , czy uruchomiony
	remaining_time = seconds; // poczatkkowy czas


	//true and true
	while (is_running && remaining_time > 0) {
		std::this_thread::sleep_for(std::chrono::seconds(1)); // watek jest uspiony przez 1s po to zeby po 1s zmiejszyc  remainig_time o 1 , this_thread wskazuj na ten watek
		remaining_time--;
	}if (remaining_time == 0) {
		cout << " \n Koniec czasu! napisz wylosowane litery do konca aby przejsc dalej" << is_running << endl;
	}
	else {
		cout << "|" << endl;
	}
}



int main()
{

	string dalej;
	int seconds;

	int rundy;
	cout << "podaj ile chcesz rund :";
	cin >> rundy;
	int gracze;
	cout << "podaj ile chcesz graczy : ";
	cin >> gracze;

	int kategorieIlosc;
	cout << "podaj ile chcesz kategorii : ";
	cin >> kategorieIlosc;
	cout << "Podaj czas przez ktory bedzie trwala runda (czas podaj w sekundach): ";
	cin >> seconds;
	std::string odpowiedz;
	int odp;
	int* punkty = new int[gracze]();
	int* sumaPunktow = new int[gracze](); //() ustawiaj wartosc na 0
	string* kategorie = new string[kategorieIlosc];
	cin.ignore(); // zeby sie ni bugowało podawanie kategorii
	for (int i = 0; i < kategorieIlosc; i++) {
		cout << "podaj kategorie " << std::endl;
		getline(std::cin, kategorie[i]);

	}
	//wypisanie kategorii
	/*for (int i = 0; i < kategorieIlosc; i++) {
		cout << kategorie[i] <<endl;
	}*/

	for (int r = 0; r < rundy; r++) {
		cout << "napisz cokolwiek aby przejsc dalej" << endl;
		cin >> dalej;
		for (int d = 0; d < 50; d++) {
			cout << "|" << endl;
		}
		cout << "RUNDA " << r + 1 << endl;
		char litera = 0;

		char lit = literaL();
		cout << "wylosowana litera to :" << lit << endl;


		string** odpowiedzi = new string * [gracze];
		for (int i = 0; i < gracze; ++i) {
			odpowiedzi[i] = new string[kategorieIlosc];
		}



		for (int j = 0; j < gracze; j++) {
			cout << "gracz : " << j + 1 << endl;
			int remaining_time; // Zmienna przechowująca pozostały czas
			int is_running = 1;
			std::thread timer_thread(timer, seconds, std::ref(remaining_time), std::ref(is_running)); // Uruchamiamy timer w oddzielnym wątku , ref jest po to zeby nie przekazac kopii zmiennej tylko oryginal przez co wartosc sie zmiany w timerzy wplywaja na oryginał

			timer_thread.detach();  // odlaczenie od watku glownego 


			for (int i = 0; i < kategorieIlosc; i++) {

				std::cout << "Aktualna kategoria: " << kategorie[i] << endl;




				cout << "Napisz odpowiedz zaczynajaca sie od " << lit << " (pisz mala litera) :";
				do {

					getline(cin, odpowiedz);


				} while (odpowiedz[0] != lit);

				odpowiedzi[j][i] = odpowiedz;


				if (remaining_time == 0) {

					do {
						cout << "napisz wylosowane litery do konca aby przejsc dalej" << endl;
						cin >> odpowiedz;
					} while (odpowiedz.size() != 1 || odpowiedz[0] != lit);
					odpowiedzi[j][i] = odpowiedz;
				}

				if (i == kategorieIlosc - 1) {
					is_running = 0;
					for (int k = 0; k < 100; k++) {

						cout << "|" << endl;  //jak wypelnimy kategorie to koniec ( is_running = 0;

					}
					cout << "napisz cokolwiek aby przejsc dalej" << endl;
					cin >> dalej;
					cout << "wylosowana litera to : " << lit << endl;

				}

			}

		}


		string** zaliczone = new string * [gracze];
		for (int i = 0; i < gracze; i++) {
			zaliczone[i] = new string[kategorieIlosc];

		}


		for (int j = 0; j < gracze; j++) {
			cout << "Odpowiedzi gracza " << j + 1 << ":" << endl;
			for (int i = 0; i < kategorieIlosc; i++) {
				cout << kategorie[i] << ": " << odpowiedzi[j][i] << endl;

				string odp;
				cout << "Czy zaliczasz odpowiedź na pytanie " << i + 1 << "? (1-tak, 2-nie): ";
				do {
					cin >> odp;
					if (odp != "1" && odp != "2") {
						cout << "Nie ma takiej mozliowsci. Wprowadź ponownie (1-tak, 2-nie): ";
					}
				} while (odp != "1" && odp != "2");

				if (odp == "1") {
					zaliczone[j][i] = odpowiedzi[j][i];
				}
			}
		}

		for (int i = 0; i < kategorieIlosc; i++) {
			int liczbaZaliczen = 0;
			for (int j = 0; j < gracze; j++) {
				if (zaliczone[j][i] == odpowiedzi[j][i]) {
					liczbaZaliczen++;
				}
			}


			if (liczbaZaliczen > 1) {
				for (int j = 0; j < gracze; j++) {
					if (zaliczone[j][i] == odpowiedzi[j][i]) {
						punkty[j] += 10; // Wszyscy zaliczeni - 10 punktów dla każdego
					}
				}
			}
			else if (liczbaZaliczen == 1) {
				for (int j = 0; j < gracze; j++) {
					if (zaliczone[j][i] == odpowiedzi[j][i]) {
						punkty[j] += 20; // Tylko jeden zaliczony - 20 punktów
					}
				}
			}
		}




		for (int j = 0; j < gracze; j++) {
			cout << "Zaliczone odpowiedzi gracza " << j + 1 << ":" << endl;
			for (int i = 0; i < kategorieIlosc; i++) {
				cout << kategorie[i] << ": " << zaliczone[j][i] << endl;



			}


		}
		cout << "Punkty po rundzie " << r + 1 << ":" << endl;
		for (int i = 0; i < gracze; i++) {
			cout << "Gracz " << i + 1 << ": " << punkty[i] << " punktów" << endl;
		}


	}



}


