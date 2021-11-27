//Strahinja Goja RT-8/19 - Igra memorije u c++ programskom jeziku
#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<Windows.h>
using namespace std;
void UnosStrukture();
void KreirajNizove();
void Generisanje_Random_Niza();
void Unos_I_Zamena_Polja();
void Upis_U_Datoteku();
void Citanje_Iz_Datoteke();
void Glavni_Meni();
void Brisanje_Iz_Datoteke();
void Povratak_U_Meni();
void Pocetni_Niz();
void Pomocni_Niz();
void Pomocni_Niz_2();
void Ocisti();
void Sacekaj(int sekunde);
void Ispisi();
void Oslobodi_Memoriju();


struct Ucesnik {
	char ime[20];
	char prezime[20];
	int score;
};

Ucesnik u;
char  **niz_polja, **pomzaniz_polja, **pomniz, **pomniz1, slovo;
int n, i, j, r1, r2, duzina1 = 3, duzina2=2,*niz_random, brpolja;


int main() { //Poziva se funkcija glavni meni, u kojoj se dalje pozivaju funkcije u zavisnosti od odabira opcije
	Glavni_Meni();
}


void Glavni_Meni() { //Glavni meni se prikazuje pri pokretanju programa, radi lakse navigacije
	char izbor;
	Ocisti();
	cout << endl << "            Nadamo se da imate dovoljno memorije na raspolaganju, jer ste upravo startovali igru memorije!" << endl<<endl;
ponovni_unos:
	cout << "                                           ----------------------------- " << endl;
	cout << "                                           --       Glavni Meni:      -- " << endl;
	cout << "                                           ----------------------------- " << endl;
	cout << "                                         *********************************" << endl;
	cout << "                                         *        Nova Igra - n          *" << endl;
	cout << "                                         *   Izlistavanje rezultata - i  *"<<endl;
	cout << "                                         *    Brisanje rezultata - b     *"<<endl;
	cout << "                                         *     Izlaz iz programa - e     *" << endl;
	cout << "                                         *********************************" << endl<<endl<<endl;
	cout << "Da biste odabrali jednu od opcija, potrebno je da unesete slovo koje je naznaceno pored opcije"<<endl<<endl;
	cout << "Unesite slovo:";
	cin >> izbor;
	switch (izbor){//U zavisnosti koje slovo je uneseno, switch poziva odredjene funkcije za dalji rad programa
	case 'n':
		    UnosStrukture();
			KreirajNizove();
			Generisanje_Random_Niza();
	        Unos_I_Zamena_Polja();
	    break;

	case 'i':
			Citanje_Iz_Datoteke();
		break;

	case 'b':
		Brisanje_Iz_Datoteke();
		break;

	case 'e':
		exit(0);
		break;

	default:
		    Ocisti();
			cout << "Niste uneli odgovarajuce slovo" << endl;
			goto ponovni_unos;
	}
}


void Sacekaj(int sekunde) { //Funkcija koja pri pozivu uzima argument int tipa. Zaustavlja dalji rad programa za odredjeno vreme u sekundama koje se prosledjuje kao argument.
	clock_t kraj;
	kraj = clock() + sekunde * CLOCKS_PER_SEC;
	while(clock()<kraj){}
}


void KreirajNizove() { //Dinamicko kreiranje svih potrebnih nizova za dalji rad igre. Duzina svih nizova zavisi od broja koga korisnik unosi.
ponovni_unos_polja:
	cout << "-----------------------------------------------------------------------------------------------------------------"<<endl;
	cout << "Napomena: broj polja mora biti paran, maksimum je 20, ali se preporucuje da bude 10 ili manje, zbog trajanja igre"<<endl;
	cout << "-----------------------------------------------------------------------------------------------------------------"<<endl<<endl;
	cout << "Unesite broj polja igre: ";
	cin >> brpolja;
	cout << brpolja << endl;
	if((brpolja%2)!=0 || brpolja>20){
		cout << "Niste uneli broj polja u naglasenom formatu!" << endl;
		goto ponovni_unos_polja;
	}
	Ocisti();
	niz_polja = new char *[brpolja];
	pomzaniz_polja = new char *[brpolja];
	pomniz = new char *[brpolja];
	pomniz1 = new char *[brpolja];
	niz_random = new int[brpolja];
	for (i = 0; i < brpolja; i++) {
		niz_polja[i] = new char[duzina1];
	}
	if (niz_polja == NULL) {
		cout << "Neuspela dodela dinamicke memorije" << endl;
	}
	for (i = 0; i < brpolja; i++) {
		pomzaniz_polja[i] = new char[duzina2];
	}
	if (pomzaniz_polja == NULL) {
		cout << "Neuspela dodela dinamicke memorije" << endl;
	}
	for (i = 0; i < brpolja; i++) {
		strcpy(niz_polja[i], "A"); //U svaki element ovog niza stringova se unosi string A
	}
	for (i = 0; i < brpolja; i++) {
		_itoa(i + 1, pomzaniz_polja[i], 10); //U svaki element ovog niza upisuju se brojevi koji su konvetovani u karaktere, od nule do broja koji je korisnik uneo.
	}
	for (i = 0; i<brpolja; i++) {
		strcat(niz_polja[i], pomzaniz_polja[i]);//Izvrsava se nadovezivanje na prvog i drugog niza
	}
	for (i = 0; i < brpolja; i++) {
		pomniz[i] = new char[duzina1];
	}
	if (pomniz == NULL) {
		cout << "Neuspela dodela dinamicke memorije" << endl;
	}
	for (i = 0; i < brpolja; i++) {
		pomniz1[i] = new char[duzina1];
	}
	if (pomniz1 == NULL) {
		cout << "Neuspela dodela dinamicke memorije" << endl;
	}
	Pomocni_Niz_2();//Kopira niz polja u pomocni niz odmah nakon kreiranja.
	Pocetni_Niz();
	
}

void Ocisti_Memoriju() {

	for (int i = 0; i < brpolja; i++) {
		delete[] niz_polja[i];
	}
	delete[] niz_polja;


	for (int i = 0; i < brpolja; i++) {
		delete[] pomzaniz_polja[i];
	}
	delete[] pomzaniz_polja;


	for (int i = 0; i < brpolja; i++) {
		delete[] pomniz[i];
	}
	delete[] pomniz;


	for (int i = 0; i < brpolja; i++) {
		delete[] pomniz1[i];
	}
	delete[] pomniz1;

}

void Generisanje_Random_Niza() {//Ova funkcija generise niz sa nasumicnim brojevima u opsegu broj polja*5
	
	srand(time(NULL));
	r1 = rand() % (brpolja*5) + 1; //kreiranje random broja u opsegu broj polja*5
	r2 = 0; //indeks niza u koji se upisuje random broj
	niz_random[r2] = r1; //manuelno postavljanje prvog elementa
	r2 = rand() % brpolja + 1;

	while (niz_random[r2] != NULL) {
		r2 = rand() % brpolja + 1; //posto niz_random po defaultu ima definisane vrednosti null, proveravam da li je u polje sa indeksom r2 vec unet broj
	}

	niz_random[r2] = r1; //automatsko postavljanje ostalih brojeva
	for (i = 0; i<((brpolja/2)-1); i++) {
		r1 = rand() % (brpolja*5) + 1;
		for (j = 0; j < brpolja; j++) {
			while (r1 == niz_random[j]) { //provera da li generisani broj vec postoji u nizu 
				r1 = rand() % (brpolja*5) + 1;
			}

		}
		r2 = rand() % brpolja + 1; //generisanje prvog random indeksa, u koji ce se upisati isti prethodno generisan broj

		while (niz_random[r2] != NULL) { //provera kao i u liniji 53
			r2 = rand() % brpolja + 1;
		}

		niz_random[r2] = r1; // smestanje prvog broja u niz_random
		r2 = rand() % brpolja + 1;

		while (niz_random[r2] != NULL) {
			r2 = rand() % brpolja + 1;
		}

		niz_random[r2] = r1; //smestanje drugog broja u niz 2
	}
}


void Unos_I_Zamena_Polja() {//Odmah nakon prethodne funkcije u kojoj se generise random niz, izvrsava se ova funkcija koja je u sustini sva funkcionalnost igre. Korisnik unosi dva polja gde se iz random niza brojevi pretvaraju u stringove i unose u prvi niz koji sadrzi polja.
	//Funkcija je otporna na nekolicinu gresaka, kao sto je unos polja koje ne postoji ili je vec uneto. Kada korisnik unese dva polja koja nisu ista, niz polja zatvara svoja polja, tj vraca se u prethodno stanje, pomocu pomocnog niza koji je kopija niza polja.
	u.score=0;
	char polje[4], slovo;
	int g, rezultati[2], x = 0, f, t, z;
	bool provformata = false;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t" << "Score: " << u.score << endl;
	Ispisi();//Ispisuje niz prvi put u originalnom stanju
	
	for (g = 0; g < (brpolja/2); g++) {//Unos se izvrsava broj polja/2 puta, jer se unose po dva polja odjednom.
	vratise:
		Pomocni_Niz();//Funkcija kopira trenutno stanje niza, u slucaju da korisnik unese dva polja koja nemaju iste brojeve.
		
		for (i = 0; i < 2; i++) {
			povratak:
			cout << "Unesi " << i + 1 << ". polje (Primer=A1):";
			cin >> polje;
			cout << endl;
			for (j = 0; j < brpolja; j++) {
				if (strcmp(niz_polja[j], polje) == 0) {//Provera da li polje koje je uneto postoji u nizu polja.
					rezultati[x] = niz_random[j];//Ako polje postoji, unosi se u niz koji sadrzi oba uneta polja.
					x++;
					_itoa(niz_random[j], niz_polja[j], 10);//Broj iz random niza se konvertuje u string i upisuje u niz polja
					Ocisti();//Funkcija koja brise sve sto je do tog trenutka upisano u cmd.
					cout <<"\t\t\t\t\t\t\t\t\t\t\t\t\t" << "Score: " << u.score << endl;
					Ispisi();
					provformata = true;//Postavlja da je format tacan, postoji uneto polje
				}
			}
			if (provformata == false) {//Slucaj da uneseno polje ne postoji u nizu polja
				
				cout << "Uneto polje nije u odgovarajucem formatu" << endl;
				goto povratak;//Vraca se na labelu i unosi se polje dok ne bude bilo u ispravnom formatu napisano
			}
			provformata = false;
		}
		x = 0;//indeks niza rezultati se vraca na nulu
		if (rezultati[0] == rezultati[1])//Provera rezultata, da li su uneta polja ista.
		{
			Ocisti();
			u.score += 20;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t" << "Score: " << u.score << endl;
			Ispisi();
			cout << "Bravo, pogodili ste!" << endl << endl;
			
		}
		else{
			for (t = 0; t < brpolja; t++) {//Ako polja nisu ista, niz polja se vraca na pocetne vrednosti preko pomocnog niza
				strcpy(niz_polja[t], pomniz[t]);
			}
			cout << "Niste otvorili dva ista polja"<<endl<<endl;
			u.score -= 5;
			if (u.score < 0) {
				u.score = 0;
			}
			cout << "Imate 3 sekunde da zapamtite otvorena polja, a nakon toga polja se ponovo zatvaraju!";
			Sacekaj(3);
			Ocisti();
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t" << "Score: " << u.score << endl;
			Ispisi();
			goto vratise;//vraca se na pocetak ciklusa za unos polja
		}
	}
	cout << "Cestitamo, uspesno ste zavrsili igru!" << endl;
	cout << "Vas score je: " <<u.score << endl<<endl;
	Upis_U_Datoteku();
	Ocisti_Memoriju();
	Povratak_U_Meni();
	}


void Ispisi() {//Ova funkcija se poziva svaki put kada treba da se ispise niz polja, ispisuje polja u zavisnosti od velicine i deljivosti.
	int z;
	for (z = 0; z < brpolja; z++)
	{
		cout << niz_polja[z] << "\t";
		if ((brpolja % 2) == 0 && brpolja != 18 && brpolja != 12) {
			if (z == ((brpolja / 2) - 1) || z == (brpolja - 1)) {
				cout << endl << endl;
			}
			else if (brpolja > 4 && (brpolja % 4) == 0) {
				if (z == ((brpolja / 4) - 1)) {
					cout << endl << endl;
				}
			    else if ((z == (int)(brpolja / 1.5+1)) && (brpolja!=8)) {
					cout << endl << endl;
				}
				else if ((z == (int)(brpolja / 1.5)) && (brpolja == 8)) {
					cout << endl << endl;
				}
			}
		}
		else if (brpolja ==18 || brpolja ==12) {
			if (z == (brpolja - 1)) {
				cout << endl << endl;
			}
			else if (z==(brpolja/1.5 - 1)) {
				cout << endl << endl;
			}
			else if(z == (brpolja / 3 - 1))
			{
				cout << endl << endl;
			}
		}
	}
	cout << endl;
}


void UnosStrukture(){//Unose se podaci u strukturu, koja se kasnije, kada se dobije i score, upise u datoteku.
	cin.ignore();
	Ocisti();
	cout << endl << "Unesite vase ime: ";
	gets_s(u.ime);
	cout << endl << "Unesite vase prezime: ";
	gets_s(u.prezime);
	Ocisti();
}


void Upis_U_Datoteku(){//Upisuju se podaci strukture u odredjenom formatu.
	ofstream fout;
	fout.open("Rezultati.txt", ios::out | ios::app);
	if (!fout) {
		cout << "Neuspelo otvaranje datoteke"<<endl;
		exit(1);
	}
	fout<< "Ime: " << u.ime << endl;
	fout << "Prezime: " << u.prezime << endl;
	fout << "Broj polja: " << brpolja << endl;
	fout << "Score: " << u.score << endl;
	fout << "------------"<<endl;
	fout.close();
}


void Citanje_Iz_Datoteke(){//Citaju se podaci iz datoteke i ispisuju u cmd karakter po karakter
	ifstream fin;
	Ocisti();
	char c;
	fin.open("Rezultati.txt", ios::in | ios::_Nocreate);
	if (!fin) {
		cout << "Neuspelo otvaranje datoteke" << endl;
		exit(1);
	}
	
	if ((c = fin.get()) == EOF) {
		cout<< endl << "Lista rezultata je prazna!" << endl<<endl;
	}
	fin.seekg(0);
	while((c=fin.get())!=EOF){
		cout << c;
	}
	fin.close();
	Povratak_U_Meni();
}


void Brisanje_Iz_Datoteke() {//Pri pozivu brisu se svi podaci iz datoteke.
	ofstream fout;
	if (!fout) {
		cout << "Neuspelo otvaranje datoteke" << endl;
		exit(1);
	}
	fout.open("Rezultati.txt", ios::out | ios::trunc);
	fout.close();
	Ocisti();
	cout << "Brisanje uspesno!"<<endl<<endl;
	Povratak_U_Meni();
}


void Povratak_U_Meni() {//Poziva se pri zavrsetku igre, nakon izlistavanja i brisanja, koja program vraca na pocetni meni programa, radi ponavljanja neke radnje ili izlaska iz samog programa.
ponovo:
	cout << "g - povratak u glavni meni" << endl << endl;
	cout << "Unesite slovo:";
	cin >> slovo;
	switch (slovo) {
	case 'g':
		Glavni_Meni();
		break;
	default:
		cout<< endl << "Niste uneli odgovarajuce slovo" << endl;
		goto ponovo;
	}
}


void Pomocni_Niz_2() {
	int f;
	for (f = 0; f < brpolja; f++) {
		strcpy(pomniz1[f], niz_polja[f]);
	}
}

void Pomocni_Niz(){
	int f;
	for (f = 0; f < brpolja; f++) {
		strcpy(pomniz[f], niz_polja[f]);
	}

}


void Pocetni_Niz() {//Postavlja pocetne vrednosti nizova pri startovanju igre.
	int f, i;
	for (f = 0; f < brpolja; f++) {
		strcpy(niz_polja[f], pomniz1[f]);
	}
	for (i = 0; i < brpolja; i++) {
		niz_random[i] = NULL;
	}
}


void Ocisti() {//Koristeci Windows.h predprocesorsku direktivu, ova funkcija brise sve podatke koji su do tog trenutka bili upisani u cmd
	COORD topLeft = { 0,0 };
	HANDLE konzola = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ekran;
	DWORD upisano;

	GetConsoleScreenBufferInfo(konzola, &ekran);
	FillConsoleOutputCharacterA(konzola, ' ', ekran.dwSize.X * ekran.dwSize.Y, topLeft, &upisano);
	FillConsoleOutputAttribute(konzola, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, ekran.dwSize.X * ekran.dwSize.Y, topLeft, &upisano);
	SetConsoleCursorPosition(konzola, topLeft);
}