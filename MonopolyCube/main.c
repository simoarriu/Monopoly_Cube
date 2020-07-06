#include "MonopolyArriuSimone.h"

int main()
{
    ///creo un array di strutture di tipo Aula per creare il tabellone di gioco, inizializzo le 40 caselle, indicando il costo, il pedaggio,
    ///il pedaggio con scrivania, con tenda, il nome della casella, il tipo di casella, un flag che indica se vi è una scrivania e un altro
    ///per la tenda, infine il valore che ne indica il proprietario.
    Aula tabellone[DIM_TAB]={
        {0,0,0,0,"Via!",ALTRO_TIPO,false,false,-1},
        {60,3,6,12,"Aula G",AULA,false,false,-1},
        {0,0,0,0,"Sfiga!",SFIGA,false,false,-1},
        {60,3,6,12,"Aula C",AULA,false,false,-1},
        {80,4,8,16,"Aula F",AULA,false,false,-1},
        {0,100,0,0,"Tasse!",TASSA,false,false,-1},
        {100,5,10,20,"Aula Studio",AULA,false,false,-1},
        {0,0,0,0,"Sfiga!",SFIGA,false,false,-1},
        {100,5,10,20,"SIMAZ",AULA,false,false,-1},
        {120,6,12,24,"Lab T",AULA,false,false,-1},
        {0,0,0,0,"Bagni",ALTRO_TIPO,false,false,-1},
        {140,7,14,28,"VAX",AULA,false,false,-1},
        {0,0,0,0,"Sfiga!",SFIGA,false,false,-1},
        {140,7,14,28,"G.A.R.",AULA,false,false,-1},
        {160,8,16,32,"Biblioteca",AULA,false,false,-1},
        {0,150,0,0,"Tasse!",TASSA,false,false,-1},
        {180,5,10,20,"Aula B",AULA,false,false,-1},
        {0,0,0,0,"Sfiga!",SFIGA,false,false,-1},
        {180,9,18,36,"Segreteria",AULA,false,false,-1},
        {200,10,20,40,"Aula A",AULA,false,false,-1},
        {0,0,0,0,"Corridoio",ALTRO_TIPO,false,false,-1},
        {220,11,22,44,"Ufficio Scateni",AULA,false,false,-1},
        {0,0,0,0,"Sfiga!",SFIGA,false,false,-1},
        {220,11,22,44,"Bagno Prof.",AULA,false,false,-1},
        {240,12,24,48,"Aula D",AULA,false,false,-1},
        {0,250,0,0,"Tasse!",TASSA,false,false,-1},
        {260,13,26,52,"Lab 3",AULA,false,false,-1},
        {0,0,0,0,"Sfiga!",SFIGA,false,false,-1},
        {260,13,26,52,"Lab 4",AULA,false,false,-1},
        {280,14,28,56,"Lab M",AULA,false,false,-1},
        {0,0,0,0,"BatCaverna",ALTRO_TIPO,false,false,-1},
        {300,15,30,60,"Aula M Fisica",AULA,false,false,-1},
        {0,0,0,0,"Sfiga!",SFIGA,false,false,-1},
        {300,15,30,60,"Aula M Chimica",AULA,false,false,-1},
        {320,16,32,64,"Aula M Matematica",AULA,false,false,-1},
        {0,350,0,0,"Tasse!",TASSA,false,false,-1},
        {360,18,36,72,"Bar Rotondo",AULA,false,false,-1},
        {0,0,0,0,"Sfiga!",SFIGA,false,false,-1},
        {360,18,36,72,"Aula Anatomica",AULA,false,false,-1},
        {400,20,40,80,"Aula Costa",AULA,false,false,-1}

    };

    //Giocatore* new_game; ///creo variabile che conterrà la nuova partita

    ///ciclo do-while tramite il quale controllo che la scelta iniziale sia corretta

    bool controllo;
    int scelta;
    printf("MonopolyCube\n");
    do
    {

        controllo=true;
        printf("1)Nuova partita\n");
        printf("2)Carica partita\n");
        printf("3)Esci\n");
        scanf("%d",&scelta);
        getchar();
        if((scelta>3)&&(scelta>0))
        {
            printf("Scelta non possibile\n");
            controllo=false;
        }

        ///switch case in base alla scelta dell'utente
        switch(scelta)
        {
            case 1:
                {
                    Nuova_Partita(tabellone); ///inizio nuova partita
                }; break;
            case 2:
                {
                    Carica_Partita(tabellone);///caricamento partita salvata
                };break;
            case 3:
                 exit(0); ///uscita dal programma
                  break;

        }
    }while(controllo==false);

    return 0;
}
