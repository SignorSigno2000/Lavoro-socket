#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fstream>

//FUNZIONI CHE AVEVO CREATO IN UNA LIBRERIA MA SU UBUNTU QUELLA LIBRERIA HA PROBLEMI
#define MAXN 20
#define character '@'
#define characterB '#'

using namespace std;

int campo[MAXN][MAXN] = { 0 };
char campo2[MAXN][MAXN];

void incrementa_vicini(int x, int y)
{
	if (x == 0)
	{
		if (y == 0)
		{
			campo[x][y + 1]++;
			campo[x + 1][y + 1]++;
			campo[x + 1][y]++;
		}
		else if (y == MAXN - 1)
		{
			campo[x + 1][y - 1]++;
			campo[x][y - 1]++;
			campo[x + 1][y]++;
		}
		else
		{
			campo[x][y + 1]++;
			campo[x][y - 1]++;
			campo[x + 1][y]++;
			campo[x + 1][y + 1]++;
			campo[x + 1][y - 1]++;
		}
	}
	else if (x == MAXN - 1)
	{
		if (y == 0)
		{
			campo[x][y + 1]++;
			campo[x - 1][y + 1]++;
			campo[x - 1][y]++;
		}
		else if (y == MAXN - 1)
		{
			campo[x - 1][y - 1]++;
			campo[x][y - 1]++;
			campo[x - 1][y]++;
		}
		else
		{
			campo[x][y + 1]++;
			campo[x][y - 1]++;
			campo[x - 1][y]++;
			campo[x - 1][y + 1]++;
			campo[x - 1][y - 1]++;
		}
	}
	else
	{
		if (y == 0)
		{
			campo[x][y + 1]++;
			campo[x + 1][y]++;
			campo[x + 1][y + 1]++;
			campo[x - 1][y]++;
			campo[x - 1][y + 1]++;
		}
		else if (y == MAXN - 1)
		{
			campo[x][y - 1]++;
			campo[x + 1][y]++;
			campo[x + 1][y - 1]++;
			campo[x - 1][y]++;
			campo[x - 1][y - 1]++;
		}
		else
		{
			campo[x][y + 1]++;
			campo[x][y - 1]++;
			campo[x + 1][y]++;
			campo[x + 1][y + 1]++;
			campo[x + 1][y - 1]++;
			campo[x - 1][y + 1]++;
			campo[x - 1][y]++;
			campo[x - 1][y - 1]++;
		}
	}
}

void show_allB()
{
	char char2=character;
	cout << "\t    ";
	for (int i = 0; i < MAXN; i++)
	{
		if (i < 9)
			cout << i + 1 << "  ";
		else
			cout << i + 1 << ' ';
	}
	cout << endl << endl;
	for (int i = 0; i < MAXN; i++)
	{
		if (i < 9)
			cout << "\t " << i + 1 << "  ";
		else
			cout << "\t " << i + 1 << ' ';
		for (int j = 0; j < MAXN; j++)
		{
			if(campo[i][j] == 0)
				cout << char2 << "  ";
			else if (campo[i][j] < 10)
				cout << campo[i][j] << "  ";
			else
				cout << 'B' << "  ";
		}
		cout << endl;
	}
}

void show_all()
{
	cout << "\t     ";
	for (int i = 0; i < MAXN; i++)
	{
		if (i < 9)
			cout << i + 1 << "  ";
		else
			cout << i + 1 << ' ';
	}
	cout << endl << endl;
	for (int i = 0; i < MAXN; i++)
	{
		if (i < 9)
			cout << "\t  " << i + 1 << "   ";
		else
			cout << "\t  " << i + 1 << "  ";
		for (int j = 0; j < MAXN; j++)
		{
			cout << campo2[i][j] << "  ";
			sleep(10);
		}
		cout << ' ' << i + 1 << endl;
	}
	cout << "\t      ";
	for (int i = 0; i < MAXN; i++)
	{
		if (i < 9)
			cout << i + 1 << "  ";
		else
			cout << i + 1 << ' ';
	}
	cout << endl << endl;
}

int calcolo_campo(char i)
{
	int valore;
	int mine;
	if (i == '1')
		mine = 25;
	else if (i == '2')
		mine = 50;
	else
		mine = 100;
	valore = (MAXN*MAXN) - mine;
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < mine; i++)
	{
		x = rand() % MAXN;
		y = rand() % MAXN;
		if (campo[x][y] >= 10)
			i--;
		else
		{
			campo[x][y] = 10;
			incrementa_vicini(x, y);
		}
	}
    return valore;
}

void inizializza()
{
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			campo2[i][j] = 'X';
}



bool click(unsigned int x, unsigned int y, unsigned int &numeri)
{
	if (campo2[x][y] == characterB)
	{
		return true;
	}
	if (campo[x][y] == 0)
	{
		if (campo2[x][y] == character)
			numeri++;
		campo2[x][y] = character;
		numeri--;
		if (x == 0)
		{
			if (y == 0)
			{
				if (campo[x][y + 1] < 10 && campo2[x][y + 1] == 'X')
					click(x, y + 1, numeri);
				if (campo[x + 1][y] < 10 && campo2[x + 1][y] == 'X')
					click(x + 1, y, numeri);
				if (campo[x + 1][y + 1] < 10 && campo2[x + 1][y + 1] == 'X')
					click(x + 1, y + 1, numeri);
			}
			else if (y == MAXN - 1)
			{
				if (campo[x][y - 1] < 10 && campo2[x][y - 1] == 'X')
					click(x, y - 1, numeri);
				if (campo[x + 1][y - 1] < 10 && campo2[x + 1][y - 1] == 'X')
					click(x + 1, y - 1, numeri);
				if (campo[x + 1][y] < 10 && campo2[x + 1][y] == 'X')
					click(x + 1, y, numeri);
			}
			else
			{

				if (campo[x][y + 1] < 10 && campo2[x][y + 1] == 'X')
					click(x, y + 1, numeri);
				if (campo[x + 1][y] < 10 && campo2[x + 1][y] == 'X')
					click(x + 1, y, numeri);
				if (campo[x + 1][y + 1] < 10 && campo2[x + 1][y + 1] == 'X')
					click(x + 1, y + 1, numeri);
				if (campo[x][y - 1] < 10 && campo2[x][y - 1] == 'X')
					click(x, y - 1, numeri);
				if (campo[x + 1][y - 1] < 10 && campo2[x + 1][y - 1] == 'X')
					click(x + 1, y - 1, numeri);
			}
		}
		else if (x == MAXN - 1)
		{
			if (y == 0)
			{
				if (campo[x][y + 1] < 10 && campo2[x][y + 1] == 'X')
					click(x, y + 1, numeri);
				if (campo[x - 1][y] < 10 && campo2[x - 1][y] == 'X')
					click(x - 1, y, numeri);
				if (campo[x - 1][y + 1] < 10 && campo2[x - 1][y + 1] == 'X')
					click(x - 1, y + 1, numeri);
			}
			else if (y == MAXN - 1)
			{
				if (campo[x][y - 1] < 10 && campo2[x][y - 1] == 'X')
					click(x, y - 1, numeri);
				if (campo[x - 1][y - 1] < 10 && campo2[x - 1][y - 1] == 'X')
					click(x - 1, y - 1, numeri);
				if (campo[x - 1][y] < 10 && campo2[x - 1][y] == 'X')
					click(x - 1, y, numeri);
			}
			else
			{
				if (campo[x][y - 1] < 10 && campo2[x][y - 1] == 'X')
					click(x, y - 1, numeri);
				if (campo[x][y + 1] < 10 && campo2[x][y + 1] == 'X')
					click(x, y + 1, numeri);
				if (campo[x - 1][y] < 10 && campo2[x - 1][y] == 'X')
					click(x - 1, y, numeri);
				if (campo[x - 1][y + 1] < 10 && campo2[x - 1][y + 1] == 'X')
					click(x - 1, y + 1, numeri);
				if (campo[x - 1][y - 1] < 10 && campo2[x - 1][y - 1] == 'X')
					click(x - 1, y - 1, numeri);
			}
		}
		else
		{
			if (y == 0)
			{
				if (campo[x][y + 1] < 10 && campo2[x][y + 1] == 'X')
					click(x, y + 1, numeri);
				if (campo[x + 1][y] < 10 && campo2[x + 1][y] == 'X')
					click(x + 1, y, numeri);
				if (campo[x + 1][y + 1] < 10 && campo2[x + 1][y + 1] == 'X')
					click(x + 1, y + 1, numeri);
				if (campo[x - 1][y] < 10 && campo2[x - 1][y] == 'X')
					click(x - 1, y, numeri);
				if (campo[x - 1][y + 1] < 10 && campo2[x - 1][y + 1] == 'X')
					click(x - 1, y + 1, numeri);
			}
			else if (y == MAXN - 1)
			{
				if (campo[x][y - 1] < 10 && campo2[x][y - 1] == 'X')
					click(x, y - 1, numeri);
				if (campo[x + 1][y] < 10 && campo2[x + 1][y] == 'X')
					click(x + 1, y, numeri);
				if (campo[x + 1][y - 1] < 10 && campo2[x + 1][y - 1] == 'X')
					click(x + 1, y - 1, numeri);
				if (campo[x - 1][y] < 10 && campo2[x - 1][y] == 'X')
					click(x - 1, y, numeri);
				if (campo[x - 1][y - 1] < 10 && campo2[x - 1][y - 1] == 'X')
					click(x - 1, y - 1, numeri);
			}
			else
			{
				if (campo[x][y - 1] < 10 && campo2[x][y - 1] == 'X')
					click(x, y - 1, numeri);
				if (campo[x][y + 1] < 10 && campo2[x][y + 1] == 'X')
					click(x, y + 1, numeri);
				if (campo[x + 1][y] < 10 && campo2[x + 1][y] == 'X')
					click(x + 1, y, numeri);
				if (campo[x + 1][y - 1] < 10 && campo2[x + 1][y - 1] == 'X')
					click(x + 1, y - 1, numeri);
				if (campo[x + 1][y + 1] < 10 && campo2[x + 1][y + 1] == 'X')
					click(x + 1, y + 1, numeri);
				if (campo[x - 1][y] < 10 && campo2[x - 1][y] == 'X')
					click(x - 1, y, numeri);
				if (campo[x - 1][y + 1] < 10 && campo2[x - 1][y + 1] == 'X')
					click(x - 1, y + 1, numeri);
				if (campo[x - 1][y - 1] < 10 && campo2[x - 1][y - 1] == 'X')
					click(x - 1, y - 1, numeri);
			}
		}
		return true;
	}
	else if (campo[x][y] >= 10)
	{
		cout << "Hai sbagliato...hai cliccato una bomba." << endl;
		return false;
	}
	else
	{
		if (campo2[x][y] != 'X')
			numeri++;
		campo2[x][y] = campo[x][y] + '0';
		numeri--;
		return true;
	}
}

void scrivi_file()
{
	ofstream ofile("prova.txt");
	ofile << "\t    ";
	for (int i = 0; i < MAXN; i++)
	{
		if (i < 9)
			ofile << i + 1 << "  ";
		else
			ofile << i + 1 << ' ';
	}
	ofile << endl;
	for (int i = 0; i < MAXN; i++)
	{
		if (i < 9)
			ofile << "\t " << i + 1 << "  ";
		else
			ofile << "\t " << i + 1 << ' ';
		for (int j = 0; j < MAXN; j++)
		{
			if (campo[i][j] < 10)
				ofile << campo[i][j] << "  ";
			else
				ofile << 'B' << "  ";
		}
		ofile << endl;
	}
	return;
}

bool controlloB()
{
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			if (campo2[i][j] == characterB && campo[i][j] < 10)
			{
				cout << "Hai sbagliato hai indicato la posizione di una bomba sbagliata." << endl;
				return true;
			}
	return false;
}

void replace_all()
{
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			if (campo[i][j] >= 10)
				campo2[i][j] = 'B';
			else
				campo2[i][j] = campo[i][j];

}

void function(char sup)
{
	
	system("color 5e");
	unsigned int numeri = 0;
	numeri = calcolo_campo(sup);
	inizializza();
	bool control = true;
	int x, y;
	scrivi_file();
	char scelta;
	int bombe = MAXN * MAXN - numeri;
	do
	{
		system("cls");
		show_all();
		cout << "Vuoi segnalare una bomba(B) oppure vuoi inserire una coordinata di un numero(C)?" << endl;
		do
		{
			cin >> scelta;
			fflush(stdin);
		} while (scelta != 'B' && scelta != 'C');
		if (scelta == 'C')
		{
			fflush(stdin);
			cout << "Inserisci le coordinate x" << endl;
			do
			{
				cin >> x;
			} while (x > MAXN || x <= 0);
			cout << "Inserisci le coordinate y" << endl;
			do
			{
				cin >> y;
			} while (y > MAXN || y <= 0);
			control = click((y - 1), (x - 1), numeri);
			if (numeri <= 0)
				control = false;
		}
		else
		{
			cout << "Inserisci le coordinate x" << endl;
			do
			{
				cin >> y;
			} while (y > MAXN && y <= 0);
			cout << "Inserisci le coordinate y" << endl;
			do
			{
				cin >> x;
			} while (x > MAXN && x <= 0);
			x--;
			y--;
			if (campo2[x][y] != 'X')
				cout << "Il carattere è gia stato visualizzato" << endl;
			else if (bombe > 1)
			{
				bombe--;
				campo2[x][y] = characterB;
			}
			else
			{
				bombe--;
				control = controlloB();
			}
		}
	} while (control);
	if (!control)
	{
		system("cls");
		if (numeri < 0)
		{
			cout << "Errore all'interno del programma" << endl;
		}
		else if (numeri == 0)
		{
			cout << "Hai vinto complimenti" << endl;
			system("color 3e");
		}
		else
		{
			system("color Cf");
			cout << "Queste erano le posizioni delle bombe" << endl;
			show_allB();
		}
	}
	system("pause");
}

void matriceToArray(char buffer[])
{
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<MAXN;j++)
			buffer[i*MAXN + j] = campo2[i][j];

}

void shift(char buffer[])
{
	for(int i=MAXN;i>=0;i--)
		for(int j=MAXN;j>=0;j--)
			buffer[i*MAXN + j] = buffer[i*MAXN +j -1];
}

int main(int argc, char **argv)
{
	int sockfd, newsockfd, portno, clilen;
	char buffer[512];
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;

	int n;
	if (argc < 2) {
		cout << "errore,numero di porta richiesto\n";
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/* si crea il socket; il parametro di ritorno è un intero
	AF_INET :tipo di dominio usato ;dominio internet
	SOCK_STREAM:tipo di comunicazione;socket a connessione TCP
	0: se ci fossero più protocolli associati al tipo di socket questo parametro permette di specificarne uno
	0 rappresenta il valore di default*/

	if (sockfd < 0)
		cout << "errore di apertura del socket\n";
	memset(&serv_addr, 0, sizeof(serv_addr)); //azzero la struttura serv_addr
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;		//inizializzo la struttura con l'indirizzo famiglia IP ed il
										//numero di porta etc 
										//serv_addr.sin_addr.s_addr = INADDR_ANY;//Indirizzo generico (0.0.0.0)
										// Qualsiasi indirizzo IP di una delle interfacce
										// di rete del servere è accettato. Se invece si usa:
	inet_aton("127.0.0.1", &(serv_addr.sin_addr));/////indirizzo 127.0.0.1 local host
	serv_addr.sin_port = htons(portno);
	//La funzione htons (Host to Network) converte un numero nel formato del computer locale,host by order,
	// in quello della rete,
	//Network by order,(il formato Network by order utilizza la memorizzazione Big-Endian
	// e cioè la memorizzazione inizia dal byte più significativo
	// a quello meno siginficativo in contrapposizione al formato Host by order
	// che usa il Little Indian e cioè la memorizzazione inizia dal byte meno significativo al più siginficativo). 

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		//con la bind si assegna l'indirizzo IP e la porta al socket creato
		cout << "errore di collegamento\n";

	//La funzione bind assegna un indirizzo locale ad un socket. È usata cioè per specificare la prima parte 
	//dalla coppia di socket(server-client). 

	listen(sockfd, 5);
	/*si mette il socket in modalità di ascolto delle connessioni
	sockfd  è il descrittore del socket ,5 è la lunghezza della coda(richieste simultanee che si possono
	accettare in coda  mentre il server sta servendo una richiesta.*/

	clilen = sizeof(cli_addr);
	/*cli_addr è la struttura dati in cui vengono memorizzati IP e porta del client*/

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);

	/* questa funzione è la corrispettiva della connect del client ed è quella che effettivamente apre
	la connessione dal lato server.
	sockfd è il vecchio socket aperto e su cui il server sta ascoltando in attesa di connessioni; si chiama socket di
	ascolto.
	(struct sockaddr_in *) &cli_addr è un puntatore a memorizzazione locale in cui porre le informazioni provenienti dal
	client. Quando arriva una richesta di connessione arriva un pacchetto che contiene le quattro informazioni essenziali:
	indirizzo IP del client - numero di porta del client ;indirizzo IP del server - porta del server.
	la funzione accept è sincrona e bloccante;
	il server sospende ogni operazione finchè non arriva dalla rete unarichiesta da parte di un client.
	In quel momento il server esegue  il servizio richiesto dal client usando per la comunicazione
	il nuovo socket ( newsockfd) che si chiama socket di servizio */
	if (newsockfd < 0)
		cout << "errore su accept()\n";
	memset(buffer, 0, 256); //azzero il buffer

	//leggo il primo pacchetto che il client mi invia
	n = read(newsockfd, buffer, 10);
	buffer[0] = toupper(buffer[0]);
	if (buffer[0] == 'D')
	{
		//controllo che il numero passato sia accettabile altrimenti setto la difficoltà ad m
		if (buffer[1] != 'f' && buffer[1] != 'm' && buffer[1] != 'd')
		{
			cout << "La difficoltà è sbagliata, verrà scelta come difficoltà M." << endl;
			buffer[1]='m';
		}

		if(buffer[1]=='f')
			buffer[1]='1';
		else if(buffer[1]=='m')
			buffer[1]='2';
		else
			buffer[1]='3';
			
		cout << "La difficoltà selezionata è: " << buffer[1] << endl;
		
		//richiamo la funzione che crea il campo e ritorna quanti numeri che non sono bombe ci sono all'interno della matrice
		unsigned int numeri=calcolo_campo(buffer[1]);
		//calcolo quante bombe ci sono
		int bombe = MAXN * MAXN - numeri;
		
		//inizializzo la matrice di gioco
		inizializza();
		bool control = true;
		int x, y;
		//scrivi_file();//solo per debug
		char scelta;
		//scrivo la tabella la prima volta
		do
		{
			matriceToArray(buffer);
			n = write(newsockfd, buffer, 401);//passo la tabella piena di 'X'
			if (n < 0)
				cout << "Errore scrittura socket" << endl;
		} while (n<0);
		do
		{
			//leggo cosa mi risponde
			do
			{
				n = read(newsockfd, buffer, 10);
				if (n < 0)
					cout << "Errore lettura socket" << endl;
			} while (n < 0);


			x = buffer[1];
			y = buffer[2];

			cout << "X --> " << x << endl;
			cout << "Y --> " << y << endl;
			x--;
			y--;
			cout << "X --> " << x << endl;
			cout << "Y --> " << y << endl;

			//controllo se ha selezionato una coordinata o una bomba
			if (buffer[0] == 'C')
			{//ha selezionato coordinata
				//salvo in x e y gli indici
				cout << "Coordinata" << endl;
				//controllo se i valori sono troppo grandi o troppo piccoli
				if ((x >= MAXN || x < 0) && (y >= MAXN || y < 0))
				{
					cout << "I valori non sono giusti." << endl;
				}
				else
				{
					//richiamo la funzione che simula il "click" sinistro del mouse
					control = click(x, y, numeri);
					
					//controllo se ha trovato tutti i numeri
					if (numeri <= 0)
						control = false;
				}
			}
			else
			{//ha selezionato bomba
				//imposto le coordinate
				cout << "Bomba" << endl;
				//controllo se ha già "cliccato" quel carattere
				if (campo2[x][y] != 'X')
					cout << "Il carattere è gia scoperto" << endl;
				else if (bombe > 1)
				{
					//se non è stato cliccato e le bombe sono più di 1
					//decrementa bombe e inserisce nella matrice il carattere che sostituisce la "bandierina"
					bombe--;
					campo2[x][y] = characterB;
				}
				else
				{
					//altrimenti resta solo 1 bomba
					//decremento il contatore e poi richiamo la funzione che controlla se ha
					//inserito le bandierine nella posizione giusta
					bombe--;
					control = controlloB();
					if (!control)
						numeri = 0;
				}
			}
			if (!control)//se control è false vuol dire che è finito il gioco
			{
				replace_all();//sistema la matrice campo2
				if (numeri < 0)//bug
					cout << "Errore all'interno del programma" << endl;
				else if (numeri == 0)//ha vinto
				{
					matriceToArray(buffer);
					shift(buffer);
					buffer[401]='\0';
					cout << buffer << endl;
					buffer[0]='W';
					n = write(newsockfd, buffer, 402);//scrive al client
					cout << "Il giocatore ha vinto" << endl;//avvisa che il giocatore ha vinto
				}
				else
				{
					matriceToArray(buffer);
					shift(buffer);
					buffer[401]='\0';
					cout << buffer << endl;
					buffer[0]='L';
					n = write(newsockfd, buffer, 402);//scrive al client
					cout << "Il giocatore ha perso" << endl;//avvisa che il giocatore ha perso
				}
			}
			else
			{
				matriceToArray(buffer);
				shift(buffer);
				buffer[401]='\0';
				cout << buffer << endl;
					buffer[0]='P';
				n = write(newsockfd, buffer, 402);
			}

			if (n < 0)
				cout << "Errore nella lettura//scrittura dal//nel socket" << endl;
		} while (control);
	}
	close(newsockfd);
	close(sockfd);
	return 0;
}

