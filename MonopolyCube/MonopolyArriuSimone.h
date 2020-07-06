#ifndef MONOPOLYARRIUSIMONE_H_INCLUDED
#define MONOPOLYARRIUSIMONE_H_INCLUDED



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define DIM 24 ///dimensione stringhe
#define MOLTIPLICATORE_PEDAGGIO 2000 ///variabile che viene moltiplicata per il pedaggio da pagare
#define MIN_DADI 1
#define MAX_DADI 6
#define BUDGET_TOT 12000
#define COSTO_SCRIVANIA 50
#define COSTO_TENDA 100
#define AULE_DISPONIBILI 24
#define DIM_TAB 40




typedef enum{PEDINA,CORONA,FUNGO,TAPPO,MACCHINA,CUORE,VASO,DITO} Segnaposto; ///creo tipo enum per creare 8 segnaposti per i giocatori

typedef enum{AULA,TASSA,SFIGA,ALTRO_TIPO} Tipo_Casella; ///creo tipo enum per creare i tipi di caselle presenti

typedef enum{PRIMO,SECONDO,TERZO,QUARTO} Tipo_Sfiga; ///creo tipo enum per indicare la tipologia delle sfighe

///creo struttura che definisce i dettagli di una partita, creo nuovo tipo 'Partita'
typedef struct
{
    int n_giocatori;
    int n_turni;
    int giocatore_attivo;

} Partita;

///creazione struttura relativa alle informazioni di un giocatore, creao nuovo tipo 'Giocatore'
typedef struct
{
    char nome[DIM+1];
    Segnaposto s_posto;
    int budget;
    int pul_bagno;
    int n_aule;
    int pos;
    int prop_aule;

}Giocatore;

///creazione struttura relativa alle informazioni sulle sfighe, creo nuovo tipo 'Sfiga'
typedef struct
{
    Tipo_Sfiga t_sfiga;///indica se è di primo, secondo, terzo o quarto tipo di sfiga
    char sfighe[150];
    int tassa;///costo tassa normale sfiga
    int tassa_aule;
    int tassa_scrivanie;
    int tassa_tende;
    int nuova_posizione;

}Sfiga;

///creo struttura relativa alle informazioni di un aula, creo nuovo tipo 'Aula'
typedef struct
{
    int costo_aula;
    int pedaggio;
    int pedaggio_scrivania;
    int pedaggio_tenda;
    char nome_aula[DIM+1];
    Tipo_Casella t_casella;
    bool flag_scrivania;
    bool flag_tenda;
    int proprietario;

} Aula;


void Nuova_Partita(Aula* vett); ///prototipo funzione che genera una nuova partita

void stampa_tabellone(Aula* vett); ///prototipo procedura che stampa il tabellone

Giocatore popola_giocatore(Giocatore* gioc,int n);///prototipo funzione che popola i giocatori

void assegna_aule(Aula* vett,int n, int n_gioc); ///prototipo procedura che assegna random le aule ai giocatori

void assegna_scrivania(Aula * vett); ///prototipo procedura che assegna il flag scrivania ad 1/3 delle aule

void conta_aule(Giocatore* gioc,Aula* vett, int n_gioc); ///procedura che conta le aule dei giocatori

void assegna_budget(Giocatore* gioc,Aula* vett, int n_gioc);///procedura che assegna il budget ad ogni giocatore

Sfiga* CaricaSfighe(Giocatore* giocatori, int i, int num,Aula* tab); ///funzione che carica le sfighe dal file di testo

void Gioco(Partita* partita, Giocatore * giocatori, Aula* vett, int num); ///procedura che implementa una parte fondamentale del gioco

void turni_bagno(int i, Giocatore* giocatori); ///procedura che gestisce i turni nei bagni dei giocatori

void controlla_aula(Aula * vett,Giocatore* giocatori,int i, int num); ///procedura utilizzata nel quarto tipo di sfighe, per verificare in che casella sia finito il giocatore

bool ControllaAssegnaTerreni(Aula* terreno,int n_gioc,int fine,int g_controllo); ///controlla che i terreni siano assegnati in modo equo

void mostra_pedina(Giocatore* giocatori, int i); ///procedura che stampa la pedina del giocatore

void Carica_Partita(Aula * vett); ///procedura che carica una partita salvata

void casella_aula(Giocatore* giocatori, Aula * vett, int i, int num); ///procedura che riguarda le azioni da fare su un'aula

void casella_sfiga(Giocatore* giocatori, Aula * vett, int i, int num); ///procedura che riguarda le azioni da fare su una sfiga

void casella_tassa(Giocatore* giocatori, Aula * vett, int i); ///procedura che riguarda le azioni da fare su una tassa

void casella_altro_tipo(Giocatore* giocatori, Aula * vett, int i); ///procedura che riguarda le azioni da fare su una casella di altro tipo











#endif // MONOPOLYARRIUSIMONE_H_INCLUDED
