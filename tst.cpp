#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>


using namespace std;

struct przedmiot
{
	int nr;
	string nazwa;
	string stan;
	float zastaw;//zastawienia
	float cena; //w razie niesp³acenia
	int d,m,r; //dzien miesiac rok
	struct przedmiot *nast;
	struct przedmiot *kolejny; //kolejny klienta
	przedmiot();
};


struct klient
{
	string imie;
	string nazwisko;
	float kwota;
	struct klient *nast;
	klient();
	przedmiot *pierwszy_zakupiony;
};


struct przedmioty {
    przedmiot *pierwsza;  // wskaŸnik na pocz¹tek listy
    przedmiot *dodaj_przedmiot ();
    przedmiot  *wyszukaj_unikalny(int numer);
    void przypisz_przedmiot(klient *nowa);
    void usun_przedmiot(klient *pierwszy);
    void sort(int co);
    void wyswietl_przedmioty ();
    przedmiot *wyszukaj_nazwa(string szukana);
    void edytuj_przedmiot();
    void zapisz_przedmioty();
    void wczytaj_przedmioty();
	przedmioty();
};

przedmiot::przedmiot() {
    nast = 0;       // konstruktor
    kolejny = 0;
}


klient::klient() {
    nast = 0;       // konstruktor
    pierwszy_zakupiony = 0;
}
struct lista {
    klient *pierwsza;  // wskaŸnik na pocz¹tek listy
    void dodaj_osobe (przedmioty *sch);
    void usun_osobe ();
    void sortuj(int j);
    void wyswietl_liste (przedmioty *sch);
    klient *wyszukaj_nazwisko();
    klient *wyszukaj_kwota();
    void edytuj(przedmioty *sch);
    void zapisz_klientow();
    void wczytaj_klientow();
    lista();
};

lista::lista() {
    pierwsza = 0;       // konstruktor
}

przedmioty::przedmioty() {
    pierwsza = 0;       // konstruktor
}


przedmiot* przedmioty::wyszukaj_unikalny(int numer)
{
	przedmiot *tmp =  pierwsza;
	while( tmp )
		{
		 	if(tmp->nr == numer)
		 	{
		 		return tmp;
		 		break;
			 }
		tmp= tmp->nast;
		}
}

przedmiot* przedmioty::wyszukaj_nazwa(string szukana)
{
	przedmiot *tmp =  pierwsza;
	while( tmp )
		{
		 	if(tmp->nazwa == szukana)
		 	{
		 		return tmp;
		 		break;
			 }
		tmp = tmp->nast;
		}
}

void przedmioty::przypisz_przedmiot(klient *nowa)
{
	//cout<<endl<<" przpisz przedmiot"<<endl;
	int dodac=1 ,wb,numer;	
	     while(dodac==1)
    {
    	cout << "czy przedmiot znajduje sie juz w bazie? \n1.Tak\n2.Nie";
    	cin >> wb;//fix
    	if(wb ==2 && nowa->pierwszy_zakupiony == 0) { nowa->pierwszy_zakupiony = (dodaj_przedmiot()) ;  }//1.zakupiony
    	else if(wb ==2) // jesli osoba ma juz jakis przedmiot
	    	{
	    		przedmiot *wk = nowa->pierwszy_zakupiony; //1. przedmiot klienta
	    		while( wk->kolejny )
	    		{
	    			wk = wk->kolejny;
				} // wk = ostatni element
				wk->kolejny = (dodaj_przedmiot());
			}
		if(wb == 1) // jesli przedmiot juz istnieje
			{
				
				cout << endl << "podaj unikalny numer przedmiotu ";
				cin >> numer;
				if(nowa->pierwszy_zakupiony == 0) //jesli 1. zakup
						{
						nowa->pierwszy_zakupiony = (wyszukaj_unikalny(numer));
						
						cout<<endl<< (wyszukaj_unikalny(numer))->nazwa  <<endl;;
						
						}
				else {
						przedmiot *w = nowa->pierwszy_zakupiony; //1. przedmiot klienta
				    	while( w->kolejny )
				    	{
				    		w = w->kolejny;
						} 
						w->kolejny = (wyszukaj_unikalny(numer));
					}		
			}
    	cout << "czy dodac kolejny przedmiot do klienta?\n1.Tak\n2.Nie";
    	cin >> dodac;
    	system( "cls" );
	}
}

przedmiot* przedmioty::dodaj_przedmiot()//bez doklienta
{
    przedmiot *nowa = new przedmiot;    // tworzy nowy element listy
 	string nazwa;
	string stan;
	int nr,d,m,r;
	float kwota,cena;
	tm data;
	
    // wype³niamy naszymi danymi
    cout << "podaj unikalny numer przedmiotu ";
    cin >> nr;
    cout << "podaj nazwe przedmiotu\n ";
    cin >> nazwa;
    cout << "podaj stan \n";
    cin >> stan;
    cout << "podaj kwote zastawu "<<endl;
    cin  >> kwota;
    cout << "podaj cene przedmiotu w razie niesp³acenia dlugu ";
    cin >> cena;
    cout << "podaj dzien zastawienia ";
    cin >> d;
    cout << "podaj miesiac zastawienia ";
    cin >> m;
    cout << "podaj rok zastawienia ";
    cin >> r;
    nowa->nr = nr;
    nowa->nazwa = nazwa;
    nowa->stan = stan;
    nowa->zastaw = kwota;
    nowa->cena = cena;
    nowa->d = d;
    nowa->m = m;
    nowa->r = r;
 
    if (pierwsza==0) // sprawdzamy czy to pierwszy element listy
    {
        // je¿eli tak to nowy element jest teraz pocz¹tkiem listy
        pierwsza = nowa;
    }
 
    else
    {
        // w przeciwnym wypadku wêdrujemy na koniec listy
        przedmiot *temp = pierwsza;
 
        while (temp->nast)
        {
            // znajdujemy wskaŸnik na ostatni element
            temp = temp->nast;
        }
 
        temp->nast = nowa;  // ostatni element wskazuje na nasz nowy
        nowa->nast = 0;     // ostatni nie wskazuje na nic
    }
    //juz wstawiony w liste ogolna
	 return nowa;
}

void przedmioty::edytuj_przedmiot()
{
	cout << "podaj unikalny numer przedmiotu ktory chcesz edytowac: ";
	int nr;
	
	cin >> nr;
	przedmiot *tmp = wyszukaj_unikalny(nr);
	cout <<"1.zmien nazwe\n2.zmien stan\n3.zmien kwote zastawu\n4.zmien cene\n5.Zmien date zastawienia";
	cin>>nr;
	switch(nr)
	{
		case 1:
			{
			cout << "podaj nowa nazwe: ";
			string n;
			cin>>n;
			tmp->nazwa = n;
			break;
			}
		case 2:
			{
			cout<<"w jakim stanie jest przedmiot: ";
			string s;
			cin>>s;
			tmp->stan = s;
			break;
			}
		case 3:
			{
			cout <<"podaj kwote zastawu: ";
			float kw;
			cin>>kw;
			tmp->zastaw;	
			break;
			}
		case 4:
			{
			cout << "podaj cene: ";
			float cena;
			cin>>cena;
			tmp->cena = cena;
			break;
			}
		case 5:
			{
			int d,m,r;
			cout << "podaj dzien: ";
			cin>> d;
			cout <<endl<<"podaj miesiac: ";
			cin >> m;
			cout <<endl<<"podaj rok ";
			cin>> r;	
			tmp->d=d; tmp->m=m; tmp->r=r;
			break;
			}
		default: cout <<"bez zmian"<<endl; break;
	}
	cout <<endl;
	
}

void lista::edytuj(przedmioty * sch)
{
	klient *tmp = wyszukaj_nazwisko();
	cout <<"1.zmien imie\n2.zmien nazwisko\n3.zmien kwote\n4.dodaj przedmiot";
	int n;
	float m;
	cin >> n;
	cout << "podaj zamiennik: ";		
	string z;
	switch (n)
	{
		case 1: cin >> z; tmp->imie=z; break;
		case 2: cin >> z; tmp->nazwisko=z; break;
		case 3: cin >>m; tmp->kwota=m; break;
		case 4: sch->przypisz_przedmiot(tmp); break;
	    default: cout <<"bez zmian"<<endl; break;
	}
}

void lista::dodaj_osobe(przedmioty *sch)
{
    klient *nowa = new klient;    // tworzy nowy element listy
 	string imie;
	string nazwisko;
	float kw;
    // wype³niamy naszymi danymi
    cout << "podaj imie\n ";
    cin >> imie;
    cout << "podaj nazwisko \n";
    cin >> nazwisko;
    cout << "podaj kwote wydakow "<<endl;
    cin  >> kw;
    nowa->kwota = kw;//????????

    cout << "czy dodac przedmiot do klienta?\n1.Tak\n2.Nie";
    int dodac,wb,numer;
    cin>>dodac;
	if( dodac == 1) sch->przypisz_przedmiot(nowa);
//	system( "cls" );
    nowa->imie = imie;
    nowa->nazwisko = nazwisko;
    
    if (pierwsza==0) // sprawdzamy czy to pierwszy element listy
    {
        // je¿eli tak to nowy element jest teraz pocz¹tkiem listy
	    pierwsza = nowa;
    }
    else
    {
        // w przeciwnym wypadku wêdrujemy na koniec listy
        klient *temp = pierwsza;
        while (temp->nast)
        {
            // znajdujemy wskaŸnik na ostatni element
            temp = temp->nast;
        }
        temp->nast = nowa;  // ostatni element wskazuje na nasz nowy
        nowa->nast = 0;     // ostatni nie wskazuje na nic
    }
}


void lista::usun_osobe ()
{
	string iu,nu;
	cout <<" podaj imie osoby ktora chcesz usunac ";
	cin >> iu;
	cout << "podaj nazwisko osobby ktora chcesz usunac ";
	cin >>nu;
	klient *tmp, *el;
	 if (pierwsza->imie == iu && pierwsza->nazwisko==nu)//jesli poczatek listy
 	{
	 tmp = pierwsza->nast;
	 delete pierwsza;
	 pierwsza = tmp;
	  }
	tmp = pierwsza;
	while (tmp)
	{
		if( (tmp->nast)->imie == iu && (tmp->nast)->nazwisko == nu)  //gdy imie i nazwisko sie zgadza wskaznik na n-1
		{
			if (tmp->nast->nast==0) tmp->nast = 0; //jesli ostatni element 
        	else tmp->nast = (tmp->nast)->nast;
			break;

		}
		tmp = tmp->nast;
	}
}

void przedmioty::usun_przedmiot(klient *help ) //fix kolejny
{
	cout << "podaj unikalny numer przedmiotu ktory chcesz usunac: ";
	int nr,kupiony = 0;
	cin >> nr;
		
    //klient *help = pierwsza;//klient
    przedmiot *tmp = pierwsza;
    przedmiot *ten = wyszukaj_unikalny(nr);
    if( ten->kolejny != 0) kupiony = 1; //jesli ma kolejnego 
	while(help)
		{
			if(help->pierwszy_zakupiony == ten ) kupiony = 1; //jest pieerwszym_kupionym
		help = help->nast;
		}
if(kupiony == 1) cout <<" Nie mo¿na usun¹æ kupionego przedmiotu! "<<endl;
else{

	if (pierwsza->nr == nr)//jesli jest pierwszym elementem
 	{
	 tmp = pierwsza->nast;
	 delete pierwsza;
	 pierwsza = tmp;
	  }
	else{		
			przedmiot *tmp =  pierwsza;
			while( tmp ) //usuwanie
				{
				 	if((tmp->nast)->nr == nr) // n-1
				 	{
					tmp->nast = (tmp->nast)->nast;
					break;
					 }
				tmp->nast = tmp->nast->nast;
				}
		}
}
}


void lista::wyswietl_liste(przedmioty *sch)
{
    // wskaznik na pierszy element listy
    klient *temp = pierwsza;
 
    // przewijamy wskazniki na nastepne elementy
    while (temp)
    {
    	cout << endl;
        cout << "imie: " << temp->imie << " nazwisko: " << temp->nazwisko << " kwota: "<< temp->kwota<<endl; 
		cout << "przedmioty ";
		if(temp->pierwszy_zakupiony == 0) cout <<"brak ";
		else{
			
				przedmiot *wsk =  temp->pierwszy_zakupiony ;
				cout << wsk->nazwa<< " "; //wyswietl 1. 
				while(wsk->kolejny) 
					{
						cout << wsk->nazwa << " ";
						wsk->kolejny = (wsk->kolejny)->kolejny;
					}
			}
        temp=temp->nast;
    }
    cout << endl;
}

void przedmioty::wyswietl_przedmioty()
{
    // wskaznik na pierszy element listy
    przedmiot *temp = pierwsza;
 
    // przewijamy wskazniki na nastepne elementy
    while (temp)
    {
        cout << "nazwa: " << temp->nazwa << " unikalny numer: "<<temp->nr<< " stan: " << temp->stan << " kwota: "<< temp->zastaw<<" cena: "	<<temp->cena<<" data: "<<temp->d<<"."<<temp->m<<"."<<temp->r<<endl;
        temp=temp->nast;
    }
}

void przedmioty::zapisz_przedmioty()
{
   przedmiot *temp = pierwsza;
	fstream przedmioty;
    przedmioty.open("przedmioty.txt", ios::out | ios::trunc ); //trunc czysci plik
       while (temp)
    {
        przedmioty << "nazwa: " << temp->nazwa << " unikalny numer: "<<temp->nr<< " stan: " << temp->stan << " kwota: "<< temp->zastaw;
	 	przedmioty<<" cena: "<<temp->cena<<" data: "<<temp->d<<" "<<temp->m<<" "<<temp->r<<endl;
        temp=temp->nast;
    }
    przedmioty << endl;
	przedmioty.close();	
}

void przedmioty::sort(int co)
{
	przedmiot *temp = pierwsza;
    przedmiot *help = pierwsza;
	przedmiot *kol;
	string nazwa, stan;
	float kwota,cena;
	int d,m,r;
	for(temp ; temp != NULL; temp = temp->nast)
    	for(help = temp; help != NULL; help = help->nast)
    	if((co==1 && help->nazwa > temp->nazwa) || //wg nazwy
		 (co==2 && help->r > temp->r) ||
		  (co==2 && help->r == temp->r && help->m > temp->m) ||
		   (co==2 && help->r == temp->r && help->m > temp->m && help->d > temp->d) )
    	{
    	 kwota = help->zastaw;
        help->zastaw = temp->zastaw;
        temp->zastaw = kwota;	
        
        cena = help->cena;
        help->cena = temp->cena;
        temp->cena = cena;
        
        nazwa = help->nazwa;
        help->nazwa = temp->nazwa;
        temp->nazwa = nazwa;
        
        stan = help->stan;
        help->stan = temp->stan;
        temp->stan = stan;
        
        d = help->d;
        help->d = temp->d;
        temp->d = d;
        
        m = help->m;
        help->m = temp->m;
        temp->m = m;
		
        r = help->r;
        help->r = temp->r;
        temp->r = r;	
		
		kol = help->kolejny;
		help->kolejny = temp->kolejny;
		temp->kolejny = kol;	        
		}	
}

void lista::sortuj(int j){
    klient *temp = pierwsza;
    klient *help = pierwsza;
    przedmiot *pierw;
 string imie, nazwisko;
    for(temp ; temp != NULL; temp = temp->nast)
        for(help = temp; help != NULL; help = help->nast)
            if((j==1 &&help->kwota > temp->kwota) ||//po kwocie
			    (j==2 && help->nazwisko > temp->nazwisko))  //po nazwisku
			{
                float kwota = help->kwota;
                help->kwota = temp->kwota;
                temp->kwota = kwota;
                
                string nazwisko = help->nazwisko;
                help->nazwisko = temp->nazwisko;
                temp->nazwisko = nazwisko;
                
                imie = help->imie;
                help->imie = temp->imie;
                temp->imie = imie;
                              
                pierw = help->pierwszy_zakupiony;
				help->pierwszy_zakupiony = temp->pierwszy_zakupiony;
				temp->pierwszy_zakupiony = pierw;              
            }
}


klient* lista::wyszukaj_nazwisko()
{
	string szukane;
	cout <<" podaj nazwisko osoby ktorej danych szukasz ";
	cin >> szukane;
	klient *tmp = pierwsza;
	przedmiot *wsk;
	while (tmp)
	{
		int zg = 0; //liczba zgodnych znakow
		for(int i =0; i < szukane.length(); i++) //porowanianie 
		{
			if( szukane[i] != tmp->nazwisko[i] ) //jesli nazw sie nie zgadza
			{
			//	break;
			}
			else{
			zg++;			
			}
		}
		if(  zg == szukane.length())  //gdy  nazwisko sie zgadza
		{
		cout << endl <<"imie: "<< tmp->imie << endl <<"nazwisko: "<<tmp->nazwisko<<endl<<"kwota: "<<tmp->kwota<<endl;
				cout << "przedmioty ";
				if(tmp->pierwszy_zakupiony == 0) cout <<"brak ";
			else{
				wsk =  tmp->pierwszy_zakupiony ;
				cout << wsk->nazwa<< " "; //wyswietl 1. 
				while(wsk->kolejny) 
					{
						cout << wsk->nazwa << " ";
						wsk->kolejny = (wsk->kolejny)->kolejny;
					}
				}
		return tmp;		
		break;
		}
		tmp = tmp->nast;
	}
cout <<endl;	
}

klient* lista::wyszukaj_kwota()
{
	float kwota;
	klient *tmp = pierwsza;
	cout <<"podaj szukana kwote: ";
	cin >>kwota;
	przedmiot *wsk =  tmp->pierwszy_zakupiony ;
	while(tmp)
	{
	if( kwota == tmp->kwota)
		{
			cout << endl <<"imie: "<< tmp->imie << endl <<"nazwisko: "<<tmp->nazwisko<<endl<<"kwota: "<<tmp->kwota<<endl;
					cout << "przedmioty ";
					if(tmp->pierwszy_zakupiony == 0) cout <<"brak ";
				else{
					wsk =  tmp->pierwszy_zakupiony ;
					cout << wsk->nazwa<< " "; //wyswietl 1. 
					while(wsk->kolejny) 
						{
							cout << wsk->nazwa << " ";
							wsk->kolejny = (wsk->kolejny)->kolejny;
						}
					}
		break;
		}	
	tmp = tmp->nast;
		}
	cout <<endl;	
	return tmp;	
}

void lista::zapisz_klientow()///wszsktki
{
	klient *temp = pierwsza;
	fstream klienci;
    klienci.open("klienci.txt", ios::out | ios::trunc ); //trunc czysci plik
    while (temp)
    {
        klienci << "imie: " << temp->imie << " nazwisko: " << temp->nazwisko << " kwota: "<< temp->kwota<<endl; 
		klienci << "przedmioty ";
		if(temp->pierwszy_zakupiony == 0) klienci <<"brak "<<endl;
		else{
			
				przedmiot *wsk =  temp->pierwszy_zakupiony ;
				klienci << wsk->nazwa<< " "; //wyswietl 1. 
				while(wsk->kolejny) 
					{
						klienci << wsk->nazwa << " ";
						wsk->kolejny = (wsk->kolejny)->kolejny;
					}
			}
        temp=temp->nast;
    }
    klienci << endl;	
    klienci.close();	
}

void lista::wczytaj_klientow() 
{	
	fstream klienci;
	klienci.open("klienci.txt", ios::in ); //if( c == imie:) nowa osob, czylo
	string c;
	float kwota;
	int przejscie = 0;
while(!klienci.eof())
{
	klient *nowa = new klient;	
if( klienci.good() == true )
{	
	if(przejscie == 0 )klienci >>c;//imie:napis  tylko dla 1. przejscia petli (inaczej pobrane w 2.petli)
	klienci >> c; //imie
	nowa->imie = c;
	klienci >> c; //nazwisko napis
	klienci >> c;//nazwisko
	nowa->nazwisko = c;
	klienci >> c; // kwota napis
	klienci >> kwota; //kwota
	nowa->kwota = kwota;
	klienci >> c; //przedmioty napis
	while( c != "imie:" && !klienci.eof()) //pobieranie przedmiotow
	{
	//	cout <<"wewnatrz "<<endl;
		klienci >> c;
	//	cout << " czym jest c ? = "<<c<<endl;
	}
	
    if (pierwsza==0) pierwsza = nowa;
    else
	    {
	        // w przeciwnym wypadku wêdrujemy na koniec listy
	        klient *temp = pierwsza;
	        while (temp->nast)
	        {
	            // znajdujemy wskaŸnik na ostatni element
	            temp = temp->nast;
	        }
	        temp->nast = nowa;  // ostatni element wskazuje na nasz nowy
	        nowa->nast = 0;     // ostatni nie wskazuje na nic
	    }	
}
przejscie = 1;
}
	klienci.close();
}

void przedmioty::wczytaj_przedmioty()
{
	fstream przedmioty;
	string c;
	int nr;
	float kwota,cena;
    przedmioty.open("przedmioty.txt", ios::in); //trunc czysci plik	
    while(!przedmioty.eof())
    {
    	przedmiot *nowa = new przedmiot;
    	przedmioty >> c;//nazzwa napis
    	przedmioty >> c;//nazwa
    	nowa->nazwa = c;
    	przedmioty >> c;//unik
    	przedmioty >> c;//num
    	przedmioty >> nr;//unikalny numer
    	nowa->nr = nr;
    	przedmioty >> c;//stannp
    	przedmioty >> c;//stan
    	nowa->stan = c;
    	przedmioty >> c;//kw
    	przedmioty >> kwota;//kwota
    	nowa->zastaw = kwota;
    	przedmioty >> c;//cenanap
    	przedmioty >> cena;//cena
    	nowa->cena;
    	przedmioty >> c; //dat
    	przedmioty >> nr;//d
    	nowa->d = nr;
    	przedmioty >> nr;//m
    	nowa->m = nr;
    	przedmioty >> nr;//r
    	nowa->r = nr;
    	    if (pierwsza==0) pierwsza = nowa;
    else
	    {
	        przedmiot *temp = pierwsza;
	        while (temp->nast)
	        {
	            // znajdujemy wskaŸnik na ostatni element
	            temp = temp->nast;
	        }
	        temp->nast = nowa;  // ostatni element wskazuje na nasz nowy
	        nowa->nast = 0;     // ostatni nie wskazuje na nic
	    }
	}
przedmioty.close();	
}

int main() 
{
	lista *baza = new lista;	
	przedmioty *schowek = new przedmioty;
	schowek->wczytaj_przedmioty(); // z pliku
	baza->wczytaj_klientow();
	int n,m;
while(true)
{
	baza->zapisz_klientow();
	//schowek->zapisz_przedmioty();
	cout << "1. Klienci \n2.Przedmioty\n";
	cin >> n;
	if ( n ==1 )
	{
	  system( "cls" );
	cout << "1. Dodaj klienta \n2.Pokaz klientow wg kwoty zakupow\n3.Pokaz klientow wg nazwisk\n4.Wyszukaj klienta\n5.Usun klienta\n6.Edytuj dane klienta\n";
	cin >> m;
		if( m ==1 )
		{
		system( "cls" );	
		baza->dodaj_osobe(schowek);
		}
		if( m==2 ){
		 baza->sortuj(1);
		 baza->wyswietl_liste(schowek);
		}
		if( m==3 ){
		 baza->sortuj(2);
		 baza->wyswietl_liste(schowek);
		}
		if( m ==4 )
		{
		system( "cls" );	
		cout <<"1.Po nazwisku\n2.Po kwocie";
		cin >>m;
			if(m==1) baza->wyszukaj_nazwisko();
			if(m==2) baza->wyszukaj_kwota();
		}	
		if( m==5 )
		{
		system( "cls" );
		baza->usun_osobe();
		}			
		if( m == 6)
		{
			baza->edytuj(schowek);
		}
	}
	if( n == 2 ) // Przedmioty
	{
		system("cls");
		cout << "1.Dodaj przedmiot\n2.Wyswietl przedmioty\n3.Pokaz posortowane przedmioty\n4.Edytuj przedmiot\n5.Usun przedmiot\n";
		cin >> n; 
		if(n == 1)
		{
			system( "cls" );
			schowek->dodaj_przedmiot();
		}
		if(n == 2)
		{
			schowek->wyswietl_przedmioty();
		}
		if(n == 3)
		{
			int o;
			cout << "1.Wedlug daty\n2.Wedlug nazwy";
			cin >>o;
			schowek->sort(o);
			schowek->wyswietl_przedmioty();
		}
		if(n == 4)
		{
			schowek->edytuj_przedmiot();
		}
		if(n == 5)
		{
			schowek->usun_przedmiot(baza->pierwsza);
		}

	}	
}
}
