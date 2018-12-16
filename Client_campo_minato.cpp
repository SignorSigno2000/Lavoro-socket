#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

using namespace std;

#define MAXN 20

char campo2[MAXN][MAXN]={'\0'};

void matrice(char buff[])
{
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<MAXN;j++)
			campo2[i][j]=buff[i*MAXN+j+1];
}

void matrice1(char buff[])
{
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<MAXN;j++)
			campo2[i][j]=buff[i*MAXN+j];
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
			//sleep(10);
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

int main(int argc, char** argv)
{
    int sockfd, portno, n;
    char server_ip[100];
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[512];
    if (argc < 3) {
       cout<<"impostare indirizzo  host porta \n";
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);    
    if (sockfd < 0) 
        cout<<"errore apertura socket\n";
    strncpy(server_ip,argv[1],20);
    if (server_ip == NULL) {
        cout<<"errore non trovo host\n";
        exit(0);
    }
    memset(&serv_addr,0,sizeof(serv_addr)); //azzero la struttura serv_addr
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(server_ip);
//inet_addr converte un indirizzo Internet in formato dot in un numero binario in formato network by order
    
    serv_addr.sin_port = htons(portno);//converte un ntero senza segno da formato host by order a network by order
    if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) 
        {cout<<"errore di connessione\n";
        exit(-1);
        }
        //write your code here
    cout << "Inserisci il livello di difficoltà" << endl;
    do
    {
        cin.getline(buffer, 4);
    }while(strcmp(buffer, "dfa")!=0 && strcmp(buffer, "dme")!=0 && strcmp(buffer, "ddi")!=0);
    n = write(sockfd, buffer, 4);
    n = read(sockfd, buffer, 401);
    while(buffer[0]!='W' && buffer[0]!='L')
    {
        //play
        if(buffer[0] != 'P' && buffer[0] != 'L' && buffer[0] != 'W')
            matrice1(buffer);
        else
            matrice(buffer);
        show_all();
        cout << "Vuoi inserire una Coordinata(C) o una Bomba(B)." << endl;
        char scelta;
        do
        {
            cin >> scelta;
            fflush(stdin);
        }while(scelta!='C' && scelta!='B');

        int x;
        int y;
        if(scelta=='C')
        {
            cout << "Inserisci le coordinate x" << endl;
            do
            {
                cin >> y;
                fflush(stdin);
            }while(y<1 || y>MAXN+1);
            cout << "Inserisci le coordinate y" << endl;
            do
            {
                cin >> x;
                fflush(stdin);
            }while(x<0 || x>MAXN);
            buffer[0]='C';
            buffer[1]=x;
            buffer[2]=y;
            buffer[3]='\0';
            n = write(sockfd, buffer, 4);
            n = read(sockfd, buffer, 402);
        }
        else
        {
            cout << "Inserisci le coordinate x" << endl;
            do
            {
                cin >> x;
                fflush(stdin);
            }while(x<0 || x>MAXN);
            cout << "Inserisci le coordinate y" << endl;
            do
            {
                cin >> y;
                fflush(stdin);
            }while(y<0 || y>MAXN);
            buffer[0]='B';
            buffer[1]=x;
            buffer[2]=y;
            buffer[3]='\0';
            n = write(sockfd, buffer, 4);
            n = read(sockfd, buffer, 402);
        }
    }
    if(buffer[0]=='W')
        cout << "Hai vinto" << endl;
    else
        cout << "Hai perso" << endl;
    matrice(buffer);
    /*cout<<"inserisci il messaggio\n";
    	    	  memset(st1,0,256); //azzero il buffer
    cin.getline(st1,255);
    n = write(sockfd,st1,strlen(st1));
    if (n < 0) 
         cout<<"errore di scrittura nel socket\n";
    memset(st1,0,256); //azzero il buffer
    n = read(sockfd,st1,255);
    if (n < 0) 
         cout<<"errore di lettura dal socket\n";
    cout<<st1<<"\n";    */
    close(sockfd); 
       return 0;
}