/*skaner.c
Krzysztof Nachszon Lipa-Izdebski
Jesien 2014 (5774-5775)
wersja: 1.0

version for compilation:
gcc (GCC) 4.9.3
Copyright (C) 2015 Free Software Foundation, Inc.
 
Program bada polaczenie do danego hosta x na porcie y
host jest pierwszym argumentem wiersza polecen
numer portu jest drugim argumentem wiersza polecen

Wywolanie programu:
skaner host port

Program obsluguje format hosta zarowno jako adres ip
oraz jako nazwe domenowa

W przypadku adresu IP adresowanie gniazda korzysta z funkcji inet_addr:
klient.sin_addr.s_addr=inet_addr(ip_number)

W przypadku nazwy domenowej adresowanie gniazda korzysta konwersji
liczb na format sieciowy:
klient_sin_addr.s_addr=*((unsigned long*)host->h_addr)

Rozpoznanie formatu wprowadzonego adresu opiera sie
na badaniu kazdego znaku tablicy tab_host_name pod katem
okreslenia, czy tablica zawiera litery

Wartosc funkcji connect przyporzadkowana jest zmiennej connect_value
Badanie tej zmiennej formuluje komunikat o porazce lub
sukcesie polaczenia

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

int main(int argc, char *argv[]){
	if (argc==1)
	{
	printf ("<font color=red>Brak argumentow</font><br>");
	printf ("<font color=red>wymagane argumenty: host i port </font><br>");
	return 1;
	}

	 if (argc==2)
        {
        printf ("<font color=red>Za malo argumentow</font><br>");
        printf ("<font color=red>wymagane argumenty: host i port </font><br>");
        return 1;
        }
		 
	int Klient;
	int port;
	int connect_value;
	struct sockaddr_in klient;
	struct hostent *host;
	char *tab_host_name;
	char tab_localhost_name[32];
	int index;
	int max_index;
	int check_char;
	int max_port=65535;
	int index_port; //adresowanie w przypadku, gdy host jest adresem IP
                klient.sin_addr.s_addr=inet_addr(tab_host_name);
	int max_index_port;
	char *tab_port_name;
	int check_char_port;
	//pobranie nazwy lokalnego hosta
	//do tablicy tab_local_host_name
	gethostname(tab_localhost_name,sizeof(tab_localhost_name));

	//pobranie nazwy zdalnego hosta
	tab_host_name=argv[1];
	port=atoi(argv[2]);
	if (port>65535)
	{
	 printf ("<font color=red>Nieprawidlowa wartosc</font><br>");
        printf ("<font color=red>wymagane wartosci 0-%d </font><br>",max_port);
        return 1;
        }
	
	tab_port_name=argv[2];
	max_index_port=strlen(tab_port_name);
	max_index=strlen(tab_host_name);
	
	 for(index_port=0,check_char_port=0;index_port<=max_index_port;index_port++)
{

                if ( !isdigit(tab_port_name[index_port]) )
{
                        check_char_port++;

}


}
        if (check_char_port!=1)
{


	 printf ("<font color=red>Nieprawidlowy typ danych</font><br>");
        printf ("<font color=red>wymagane wartosci 0-%d </font><br>",max_port);
        return 1;


}
	
	/*Obsluga nieznanego hosta
	jezeli wartosc inna niz NULL
	instrukcja przyporzadkowania obowiazuje
	nie nalezy wywolywac jej po raz drugi
	*/
	if ((host=gethostbyname(tab_host_name))==NULL){

		printf ("<P align=center><b>Host %s z hosta %s jest nierozpoznawalny<br></br></b></P>\n", tab_host_name,tab_localhost_name);

		return 1;

	}
	

	//parametryzujemy gniazdko
	Klient=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);

	//sprawdzamy, czy drugi argument zawiera litery 
	//kropka z punktu widzenia biblioteki ctype.h nie jest litera 
	//jezeli nie zawiera, to inkrementujmy zmienna check_char
	//zmienna index (bedaca indeksem tablicy tab_host_name)
	//jest inkrementowana w kazdej iteracji
	//w zwiazku z tym jezeli po zakonczeniu dzialania petli okaze sie,
	//ze wartosci index i check_char sa sobie rowne
	//to oznacza, ze wartosc tab_host_name nie zawiera liter
	//czyli jest adresem IP 
	for(index=0,check_char=0;index<=max_index;index++){

		if (!isalpha(tab_host_name[index])){
			check_char++;

}


}
	if (check_char==index){

		
		//adresowanie w przypadku, gdy host jest adresem IP	
		klient.sin_addr.s_addr=inet_addr(tab_host_name);


}else{

		//adresowanie w przypadku, gdy host jest nazwa
		klient.sin_addr.s_addr=*((unsigned long*)host->h_addr);

}
		
		klient.sin_port=htons(port);
		klient.sin_family=AF_INET;

		//jezeli polaczenie istnieje, coonect zwroci o
		//jezeli polaczenie nie istnieje, connect zwroci inna wartosc (najprawdopodobniej ujemna)
		connect_value=connect(Klient,(struct sockaddr*)&klient,sizeof(klient));

		
		//znaczniki html uzyte w funkcji printf beda prawidlowo interpretowane
		//przez przegadarke
		if (connect_value != 0 ){
			printf("<font color=red><P align=center>Connection %s -> %s (port %d): Failed</font><br></br></P>\n",tab_localhost_name,tab_host_name,port);
		}else{
			printf ("<font color=green><P align=center>Connection %s -> %s (port %d): Successful</font><br></br></P>\n",tab_localhost_name,tab_host_name,port);
		}

		close(Klient);

	

		EXIT_SUCCESS;
	
	
}
