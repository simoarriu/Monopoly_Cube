#include "MonopolyArriuSimone.h"

///funzione che stampa il vett di gioco
void stampa_vett(Aula* vett)
{
    int i;
    for(i=0;i<40;i++)
    {
        if(vett[i].proprietario!=-1)
            printf("Casella %d : %s Valore %d Proprietario: %d Flag Scrivania: %d\n", i+1,vett[i].nome_aula,vett[i].costo_aula,vett[i].proprietario, vett[i].flag_scrivania);
    }
}

///funzione con la quale popolo i campi dei giocatori creati
Giocatore popola_giocatore(Giocatore* gioc,int n)
{

    int i,t,j=0;
    for(i=0;i<n;i++)
    {

        printf("Giocatore %d\n", i+1);
        printf("Nome: ");
        scanf("%s",gioc[i].nome);
        getchar();
        int c=2;///variabile usata nel while per verificare che la pedina sia univoca


        while(c==2) ///finchè c==2, ossia che la stessa pedina è usata due volte da due giocatori differenti
        {
            c=0;///azzero la variabile

            printf("Scegli il tuo segnaposto:\n");
        printf("1)Pedina\n");
        printf("2)Corona\n");
        printf("3)Fungo\n");
        printf("4)Tappo\n");
        printf("5)Macchina\n");
        printf("6)Cuore\n");
        printf("7)Vaso\n");
        printf("8)Dito\n");
        scanf("%d",&t);
        getchar();

            gioc[i].s_posto=t-1;

            ///confronto il segnaposto di ogni giocatore con quello appena inserito
            for(j=0;j<n;j++)
            {
                if(gioc[j].s_posto==t-1)
                {
                    c++; ///se viene trovato viene incrementata c
                     if(c==2) ///se c==2 vuol dire che ci sono due giocatori con la stessa pedina, quindi viene fatta reinserire la scelta all'utente
                    {
                        printf("Pedina gia' selezionata, sceglierne un'altra\n\n");
                    }

                }
            }

        }

        ///popolo i restanti campi del giocatore
        gioc[i].budget=0;
        gioc[i].n_aule=0;
        gioc[i].pul_bagno=0;
        gioc[i].pos=0;
        gioc[i].prop_aule=i;
    }

    return * gioc;
}

void assegna_aule(Aula* vett, int n, int n_gioc)///procedura con la quale assegno le aule ai giocatori
{
    int i;
    bool c; ///varibile controllo che i terreni siano assegnati in modo giusto
    for(i=0;i<n;i++)
    {
        if(vett[i].t_casella==AULA)///controllo se la casella è un aula
        {

            do
            {
                 vett[i].proprietario=rand()%(n_gioc);///assegno un numero random da 0 al numero di giocatori in partita al proprietario della casella
                c=ControllaAssegnaTerreni(vett,n_gioc,i,vett[i].proprietario);///richiamo la funzione che controlla l'assegnamento dei terreni
            }while(c==false);

        }
    }
}

bool ControllaAssegnaTerreni(Aula* terreno,int n_gioc,int fine,int gioc_controllo)
{
    int i,controllo;
    int cont_Terreni=0;
    if(n_gioc%2==0)///se il numero di giocatori e' pari
        controllo=AULE_DISPONIBILI/n_gioc;///divido le aule disponibili con il numero di giocatori
    else
        controllo=AULE_DISPONIBILI/n_gioc+1; ///aggiungo +1 per i numeri dispari
    for(i=0;i<fine;i++)
        if(terreno[i].proprietario==gioc_controllo)///se il proprietario del terreno è lo stesso del proprietario passato per parametro
            cont_Terreni++; ///incremento la variabile
    if(cont_Terreni<controllo)/// se i terreni sono minori della variabile controllo
        return true;
    else
        return false;
}



void assegna_scrivania(Aula * vett)///assegno random il flag scrivania ad 1/3 delle aule
{
        int j=0;
        int rand_scrivania=0;
        while(j<8)///j<8 perchè vengono assegnate 8 volte i flag scrivania random
        {
             rand_scrivania=rand()%(DIM_TAB);///genero numero random
             if(vett[rand_scrivania].t_casella==AULA)///se è un aula
             {
                 if(vett[rand_scrivania].flag_scrivania!=true)///controllo che l'aula non abbia già il flag scrivania
                 {
                     vett[rand_scrivania].flag_scrivania=true;///assegno all'aula il flag
                     j++;
                 }

             }
        }
}

void conta_aule(Giocatore* gioc,Aula* vett, int n_gioc) ///conta le aula dei giocatori
{
    int i=0,j=0;
    for(i=0;i<n_gioc;i++)
    {
        for(j=0;j<DIM_TAB;j++)
        {
            if(vett[j].proprietario==gioc[i].prop_aule)///verifico che il proprietario del vettore sia lo stesso del propietario del giocatore
                gioc[i].n_aule++;
        }

    }
}


void assegna_budget(Giocatore* gioc,Aula* vett, int n_gioc) ///assegno budget ai giocatori in base al valore delle loro aule
{
    int val_tot[8]={}; ///vettore che conterrà il valore totale delle aule dei giocatori
    int i,j;

    for(j=0;j<n_gioc;j++)
    {
        for(i=0;i<DIM_TAB;i++)
        {
            if(gioc[j].prop_aule==vett[i].proprietario)///verifico che il proprietario del vettore sia lo stesso del propietario del giocatore
                val_tot[j]+=vett[i].costo_aula;///assegno alla cella del vettore val_tot il costo dell'aula che appartiene a quel giocatore
        }

    }

    for(i=0;i<n_gioc;i++) ///stampo il budget dei giocatori
    {
        printf("Budget di %s: %d\n",gioc[i].nome, gioc[i].budget=(BUDGET_TOT/n_gioc)-(val_tot[i]));
    }
}

void turni_bagno(int i, Giocatore* giocatori) ///gestisco i turni dei bagni
{
    switch(giocatori[i].pul_bagno)
                    {
                        case 1: ///caso in cui è il primo turno in bagno del giocatore
                        {
                          printf("Turni passati in bagno: 1\n");
                          giocatori[i].pul_bagno++;///incrmeento
                        }break;
                        case 2: ///caso in cui sia il secondo turno
                        {
                        printf("Turni passati in bagno: 2\n");
                        giocatori[i].pul_bagno++;///incremento
                        }break;
                        case 3:///caso in cui sia il terzo turno
                        {
                            printf("Turni passati in bagno: 3. Al prossimo turno tira i dadi!\n");
                            giocatori[i].pul_bagno=0;///il giocatore torna attivo e il suo campo dei turni_bagno torna a 0
                        }break;
                    }

}

Sfiga* CaricaSfighe(Giocatore* giocatori, int k, int num,Aula* tab) ///carico del sfighe
{
    FILE * elenco_sfighe; ///creo puntatore file
    Sfiga * vett=NULL; ///vettore di tipo sfiga che conterrà le informazioni lette dal file
    int n_sfiga[4]; ///vettore che conterrà i primi 4 interi letti dal file
    int i=0;
    int somma_sfiga=0;
    elenco_sfighe = fopen("ListaSfighe.txt", "r"); ///apro il file delle sfighe
    if (elenco_sfighe == NULL)
        exit (-1);
    fscanf(elenco_sfighe, "%d ", &n_sfiga[0]);///leggo il primo intero e lo assegno alla prima cella del vettore, così faccio per i seguenti 3 numeri
    fscanf(elenco_sfighe, "%d ", &n_sfiga[1]);
    fscanf(elenco_sfighe, "%d ", &n_sfiga[2]);
    fscanf(elenco_sfighe, "%d", &n_sfiga[3]);
    fscanf(elenco_sfighe,"\n");

    for(i=0;i<4;i++)
    {
        somma_sfiga+=n_sfiga[i]; ///sommo il contenuto del vettore in somma_sfiga
    }

    vett=(Sfiga*)malloc(sizeof(Sfiga)*somma_sfiga); ///per poi allocare dinamicamente il vettore dichiarato prima con dimensione di somma_sfiga

    /// leggo le prime 9 sfighe, quelle del primo tipo
    for(i=0;i<9;i++)
    {
        vett[i].t_sfiga=PRIMO; ///indico il tipo di sfiga
        fscanf(elenco_sfighe,"%d ",&vett[i].tassa);///leggo la tassa da pagare
        fscanf(elenco_sfighe,"%[^\n]s",vett[i].sfighe);///la stringa della sfiga
        fscanf(elenco_sfighe, "\n");
        ///printf("%s/n",&vett[i].sfighe);
        vett[i].tassa_aule=0;
        vett[i].tassa_scrivanie=0;
        vett[i].tassa_tende=0;
        vett[i].nuova_posizione=0;
    }

    ///leggo il secondo tipo di sfiga
    for(i=9;i<18;i++)
    {
        vett[i].t_sfiga=SECONDO;
        fscanf(elenco_sfighe,"%d ",&vett[i].tassa_aule);///leggo tassa per il numero di aule, per le scrivanie e le tende
        fscanf(elenco_sfighe,"%d ",&vett[i].tassa_scrivanie);
        fscanf(elenco_sfighe,"%d ",&vett[i].tassa_tende);
        fscanf(elenco_sfighe,"%[^\n]s",vett[i].sfighe); ///leggo stringa sfiga
        fscanf(elenco_sfighe, "\n");
        vett[i].tassa=0;
        vett[i].nuova_posizione=0;
    }

    for(i=18;i<29;i++)
    {
        vett[i].t_sfiga=TERZO;
        fscanf(elenco_sfighe,"%[^\n]s",vett[i].sfighe); ///leggo stringa terzo tipo
        fscanf(elenco_sfighe, "\n");
        vett[i].tassa=0;
        vett[i].tassa_aule=0;
        vett[i].tassa_scrivanie=0;
        vett[i].tassa_tende=0;
        vett[i].nuova_posizione=0;
    }

    for(i=29;i<39;i++)
    {
        vett[i].t_sfiga=QUARTO;
        fscanf(elenco_sfighe,"%d ",&vett[i].nuova_posizione); ///leggo intero che indica la nuova posizione del giocatore
        fscanf(elenco_sfighe,"%[^\n]s",vett[i].sfighe);
        fscanf(elenco_sfighe, "\n");
        vett[i].tassa=0;
        vett[i].tassa_aule=0;
        vett[i].tassa_scrivanie=0;
        vett[i].tassa_tende=0;
    }

    int randomnum=rand()%(40); ///genero un numero random da 0 a 39

    fclose(elenco_sfighe);

    return &vett[randomnum]; ///ritorno come valore la sfiga random

    ///return &vett;




}




void controlla_aula(Aula * vett,Giocatore* giocatori,int i,int num)
{

    ///controllo tipologia casella
    switch(vett[giocatori[i].pos].t_casella)
            {
                case AULA:
                {

                    casella_aula(giocatori, vett, i, num); ///se è AULA, gestisco tramite la seguente procedura

                };  break;

                case SFIGA:
                {
                    casella_sfiga(giocatori,vett,i, num); ///se è SFIGA, gestisco tramite la seguente procedura

                };  break;

                case TASSA:
                {
                    casella_tassa(giocatori,vett,i);///se è TASSA, gestisco tramite la seguente procedura

                };  break;

                case ALTRO_TIPO:
                {

                    casella_altro_tipo(giocatori,vett,i); ///se è ALTRO_TIPO, gestisco tramite la seguente procedura
                };  break;


            }


}

void mostra_pedina(Giocatore* giocatori, int i) ///procedura con la quale stampo la pedina del giocatore
{
    switch(giocatori[i].s_posto)
            {
                case 0: printf("Pedina "); break;

                case 1: printf("Corona "); break;

                case 2: printf("Fungo "); break;

                case 3: printf("Tappo "); break;

                case 4: printf("Macchina "); break;

                case 5: printf("Cuore "); break;

                case 6: printf("Vaso "); break;

                case 7: printf("Dito "); break;

            }
}



void Nuova_Partita(Aula* vett) ///funzione che genera una nuova partita
{

    int num; ///numero giocatori
    int i;
    int turno=1;
    srand(time(NULL));
    Partita* partita=(Partita*)malloc(sizeof(Partita)); ///alloco dinamicamente una partita



    ///ciclo che controlla se il numero di giocatori inserito è corretto
    do
    {
        printf("Quanti giocatori vogliono partecipare?(2-8)");
        scanf("%d",&num);
        if(!(num>=2 && num<=8))
        {
            printf("Numero inserito errato.\n");
        }

    }
    while(!(num>=2 && num<=8));


    ///creo una varianile puntatore di tipo Giocatore e la alloco dinamicamente, dando come dimensione il numero di giocatori
    Giocatore* giocatori=NULL;
    giocatori=(Giocatore*)malloc(sizeof(Giocatore)*num);

    ///popolo i campi della variabile partita
    partita->n_giocatori=num;
    partita->n_turni=turno;
    partita->giocatore_attivo=0;

    popola_giocatore(giocatori,num); ///richiamo la funzione per popolare i giocatori

    printf("Assegno i terreni ai giocatori\n");

    assegna_aule(vett,DIM_TAB,num); ///richiamo la funzione che assegna le aule ai giocatori

    assegna_scrivania(vett); ///assegno le scrivanie random ad 1/3 delle aule

    stampa_vett(vett); ///stampo vettore

    conta_aule(giocatori,vett,num); ///conto aule dei giocatori

    ///stampo il numero di terreni, di scrivanie e di tende di ogni giocatore
    for(i=0;i<num;i++)
    {
        int contTenda=0, contScrivania=0,j;
        printf("Terreni di %s: %d\n", giocatori[i].nome, giocatori[i].n_aule);

        for(j=0;j<DIM_TAB;j++) ///scorro ogni casella del tabellone
        {
            if(vett[j].proprietario==giocatori[i].prop_aule) ///se il proprietario della casella è uguale a quello del giocatore
            {
                 if(vett[j].flag_tenda==true) ///se il flag tenda è true, incremento la variabile
                     contTenda++;
                 if(vett[j].flag_scrivania==true) ///se il flag scrivania è true, incremento la variabile
                     contScrivania++;
            }

        }

        printf("Possiedi:\n");
        printf("Scrivanie: %d\n",contScrivania);
        printf("Tende: %d\n",contTenda);

    }

    ///stabilisco il budget di ciascun giocatore in base al valore totale calcolato precedentemente
    assegna_budget(giocatori,vett,num);

    printf("Inizio partita!\n");

    Gioco(partita,giocatori,vett,num);///richiamo la procedura Gioco, dove è presenta la parte centrale del programma

    //return giocatori;
}

void Gioco(Partita* partita, Giocatore * giocatori, Aula* vett, int num)
{

    int i;
    int j;
    int flag=-1; ///variabile usata per il do-while che riprende la scelta degl giocatore di continuare a giocare dopo il salvataggio della partita
    char s_utente; ///scelta utente per il tiro dei dadi o il salvataggio
    int scelta_u; ///scelta utente per scegliere se, dopo il salvataggio, proseguire o uscire dal gioco
    int cont_dadi_doppi[8]={}; ///vettore usato per tenere conto quante volte di seguito i giocatori fanno dado doppio
    Giocatore temp; ///creo variabile temporanea da usare per eliminare il giocatore con il budget negativo
    int dado1,dado2;
    srand(time(NULL));

    ///ciclo do-while che prosegue se il numero di giocatori è diverso da 1
    do
    {

        printf("\n");
        printf("Turno %d\n", partita->n_turni);

        for(i=partita->giocatore_attivo;i<num;i++) ///for che scorre i turni dei giocatori
        {
            do ///do-while che cicla se la scelta dell'utente dopo il salvataggio è quella di continuare a giocare
            {
                partita->giocatore_attivo=i;

                printf("\n");
                printf("Parola a %s:\n", giocatori[i].nome);
                mostra_pedina(giocatori,i);///richiamo la procedura che mi stampa il segnaposto del giocatore
                printf("Posizione cella - %d", giocatori[i].pos);
                printf("\n");

                ///controllo se il budget del giocatore sia negativo
                if(giocatori[i].budget<=0)
                {
                    printf("Budget negativo, %s verrai eliminato!\n", giocatori[i].nome);


                    if(giocatori[i].prop_aule==giocatori[num-1].prop_aule) ///se il giocatore con budget negativo è l'ultimo
                    {
                        ///assegno i suoi terreni al banco e tolto i relativi flag
                        for(j=0;j<DIM_TAB;j++)
                        {
                            if(vett[j].proprietario==giocatori[i].prop_aule)
                            {
                                vett[j].proprietario=-1;
                                vett[j].flag_scrivania=false;
                                vett[j].flag_tenda=false;
                            }
                        }

                        i=0;
                    }
                    else ///se il giocatore da eliminare non è l'ultimo
                    {
                            for(j=0;j<DIM_TAB;j++) ///assegno i suoi terreni al banco e tolto i flag
                            {
                                if(vett[j].proprietario==giocatori[i].prop_aule)
                                {
                                    vett[j].proprietario=-1;
                                    vett[j].flag_scrivania=false;
                                    vett[j].flag_tenda=false;
                                }
                            }

                            ///ciclo for con il quale scorro il vettore di strutture a partire da j che prende il valore di i
                            ///il giocatore da eliminare viene assegnato ad una variabile temporanea, la sua cella verrà poi
                            ///sostituita dal successore, così poi l'ultima cella potrà essere eliminata tramite riallocazione,
                            ///senza perdere le informazioni dei giocatori restanti
                            for(j=i;j<num-1;j++)
                            {
                                temp=giocatori[j];
                                giocatori[j]=giocatori[j+1];

                            }

                            printf("\n");
                            printf("Parola a %s:\n", giocatori[i].nome);
                            mostra_pedina(giocatori,i);
                            printf("Posizione cella - %d", giocatori[i].pos);
                            printf("\n");

                    }

                    num-=1;///decremento il numero di giocatori e rialloco la variabile con il nuovo valore di num, elimando cosi il giocatore con il budget negativo
                    partita->n_giocatori-=1;
                    giocatori=(Giocatore*)realloc(giocatori,num*sizeof(Giocatore));


                    if(num==1) ///se il giocatore è solo uno
                    {
                        int k;
                        for(k=0;k<num;k++)
                        printf("Ha vinto %s!\n", giocatori[k].nome); ///indico chi ha vinto
                        free(giocatori);
                        free(partita);
                        exit(0);
                    }

            }

            if(giocatori[i].pul_bagno>=1) ///se il campo pul_bagno del giocatore è >=1, viene richiamata la procedura che gestisce i turni dei bagni
            {
                turni_bagno(i,giocatori);
            }
            else
            {
                printf("\nCosa vuoi fare %s?\n",giocatori[i].nome);
                printf("d - Lancia i dadi\n");
                printf("s - Salva la partita\n");
                scanf("%s",&s_utente); ///scelta dell'utente su cosa fare nel suo turno
                getchar();
                if(s_utente=='d')
                {
                    do ///do-while che cicla se è stato fatto dado doppio e se la variabile del bagno è 0
                    {
                        printf("\n%s lancia i dadi:\n", giocatori[i].nome);

                        ///assegno a dado 1 e dado 2 valori casuali da 1 a 6
                        dado1=MIN_DADI+rand()%(MAX_DADI-MIN_DADI+1);
                        dado2=MIN_DADI+rand()%(MAX_DADI-MIN_DADI+1);

                        printf("Dado 1:%d \nDado 2:%d\n", dado1,dado2 );

                        if(dado1==dado2) ///incremento la cella del vettore che conta i dadi doppi
                        {
                            printf("Dadi doppi! Al prossimo turno ritira!\n");
                            cont_dadi_doppi[i]++;
                        }

                        if(cont_dadi_doppi[i]==3) ///se il valore di questa cella raggiunge 3
                        {

                                printf("Hai fatto 3 volte dadi doppi! Vai in bagno!\n");
                                cont_dadi_doppi[i]=0;///la variabile viene azzerata
                                giocatori[i].pos=10;///il giocatore va a finire in bagno
                                giocatori[i].pul_bagno=1;


                        }
                        else
                        {
                            cont_dadi_doppi[i]=0;///se il giocatore non ha fatto dadi doppi o ha interrotto la striscia di dadi doppi, la cella del vettore viene portata a 0
                            giocatori[i].pos+=dado1+dado2; ///la posizione del giocatore assume la somma dei dadi

                            if(giocatori[i].pos>=40) ///se la posizione del giocatore è maggiore di 40, viene effettuato il modulo per ottenre la posizione corretta dopo aver oltrepassato il via
                            {
                                giocatori[i].pos%=40;

                                printf("Sei passato dal Via! Ritira 20!\n");
                                giocatori[i].budget+=20;
                                printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);

                            }

                            ///Indico la casella in cui il giocatore è finito
                            printf("%s e' finito in %s\n", giocatori[i].nome, vett[giocatori[i].pos].nome_aula);

                            ///switch che in base alla tipologia della casella esegue i rispettivi case
                            switch(vett[giocatori[i].pos].t_casella)
                            {
                                case AULA:
                                {
                                    casella_aula(giocatori, vett, i, num);///viene richiamata la procedura che gestisce le aule
                                };  break;

                                case SFIGA:
                                {
                                    casella_sfiga(giocatori,vett,i, num);///viene richiamata la procedura che gestisce le sfighe
                                };  break;

                                case TASSA:
                                {
                                    casella_tassa(giocatori,vett,i);///viene richiamata la procedura che gestisce le tasse
                                };  break;

                                case ALTRO_TIPO:
                                {
                                    casella_altro_tipo(giocatori,vett,i); ///viene richiamata la procedura che gestisce le caselle di altro tipo
                                };  break;


                            }

                        }

                        flag=-1;

                    }while(dado1==dado2 && giocatori[i].pul_bagno==0); ///do-while che controlla il dado doppio e la pul_bagno

                }
                else
                {
                    ///se il giocatore non tira i dadi, salva la partita

                    FILE* fop=NULL; ///creo puntatore file
                    fop = fopen("salvapartita.bin", "wb"); ///creo il file su cui salvare la partita
                    if (fop == NULL)
                        exit(0);

                    fwrite(partita, sizeof(Partita),1, fop); ///scrivo sul file le informazioni contenute in "partita"

                    fwrite(giocatori,sizeof(Giocatore),num,fop); ///scrivo sul file le informazioni contenute in "giocatori"

                    fwrite(vett,sizeof(Aula),DIM_TAB,fop); ///scrivo sul file le informazioni contenute in "vett"

                    fclose(fop); ///chiudo il file

                    ///chiedo al giocatore cosa vuole fare dopo aver salvato
                    printf("Vuoi continuare a giocare o uscire?\n");
                    printf("1) Gioca!\n");
                    printf("2) Esci!\n");
                    scanf("%d",&scelta_u);
                    getchar();

                    if(scelta_u==2)
                    {
                        free(giocatori);
                        free(partita);
                        exit(0);
                    }

                    flag=0; ///mettendo il flag a 0, la condizione del seguente while sarà verificata, così il giocatore continuerà il suo turno

                }

            }


            }while(scelta_u==1 && flag==0 ); ///controllo la condizione della scelta del giocatore, se giocare o uscire dopo il salvataggio



        }

        printf("\n");

        partita->n_turni++;///incremento i turni
        partita->giocatore_attivo=0;///riazzero il giocatore attivo per far ripartire il ciclo for dal primo giocatore


    }while(num!=1); ///while che cicla finchè il numero di giocatori è diverso da 1
}



void Carica_Partita(Aula * vett) ///procedura che carica la partita precedentemente salvata
{

    Giocatore giocatori; ///variabile di tipo Giocatore a cui verrà assegnato il contenuto del file di salvataggio
    Partita partita; ///variabile di tipo Partita a cui verrà assegnato il contenuto del file di salvataggio
    int j;
    FILE* fp=NULL; ///creo puntatore di tipo File
    fp = fopen("salvapartita.bin", "rb"); ///apro il file binario di sallvataggio
    if (fp == NULL)
        exit(0);

    Partita *partita_aus=NULL; ///creo una partita ausiliaria, a cui verrà assegnato il contenuto di ciò che leggo dal file riguardo la partita
    partita_aus=(Partita*)malloc(sizeof(Partita));

    ///leggo le informazioni della partita dal file
    fread(&partita, sizeof(Partita),1,fp);
    ///assegno alla partita ausiliaria, il contenuto di ciò che ho letto dal file, assegnato alla variabile partita
    partita_aus->giocatore_attivo=partita.giocatore_attivo;
    partita_aus->n_giocatori=partita.n_giocatori;
    partita_aus->n_turni=partita.n_turni;
    printf("Giocatore attivo: %d\n", partita_aus->giocatore_attivo);
    printf("Numero giocatori: %d\n", partita_aus->n_giocatori);
    printf("Numero turni: %d\n", partita_aus->n_turni);

    ///creo un giocatore ausiliario, a cui verrà assegnato il contenuto di ciò che leggo dal file riguardo i giocatori
    Giocatore* gioc_aus=NULL;
    gioc_aus=(Giocatore*)malloc(sizeof(Giocatore)*partita.n_giocatori);

    ///leggo uno ad uno i giocatori, e assegno le loro informazioni lette dal file al giocatore ausiliario
    ///e stampo le informazioni appena lette dei giocatori
    for(j=0;j<partita.n_giocatori;j++)
    {
        fread(&giocatori,sizeof(Giocatore),1,fp);
        gioc_aus[j].prop_aule=giocatori.prop_aule;
        gioc_aus[j].budget=giocatori.budget;
        gioc_aus[j].n_aule=giocatori.n_aule;
        gioc_aus[j].pos=giocatori.pos;
        gioc_aus[j].pul_bagno=giocatori.pul_bagno;
        gioc_aus[j].s_posto=giocatori.s_posto;
        strcpy(gioc_aus[j].nome,giocatori.nome);
        printf("Giocatore %d - %s\n", j+1, giocatori.nome);
        printf("Budget: %d\n", giocatori.budget);
        printf("Numero aule: %d\n", giocatori.n_aule);
        printf("Posizione nel tabellone: %d\n", giocatori.pos);
        printf("Segnaposto: ");
        mostra_pedina(gioc_aus,j);
        printf("\nPulizia Bagno: %d\n", giocatori.pul_bagno);

   }

    ///leggo le celle del vettore del tabellone
    for(j=0;j<DIM_TAB;j++)
    {
        fread(&vett[j],sizeof(Aula),1,fp);
    }

    ///i valori appena letti, vengono passati come parametri alla procedura seguente, che permetterà di continuare a giocare
    Gioco(partita_aus,gioc_aus,vett,partita.n_giocatori);

}

///procedura che gestisce il caso in cui il giocatore sia finito in un'aula
void casella_aula(Giocatore* giocatori, Aula * vett, int i, int num)
{
    int scelta, flag_nome,j;
    if(giocatori[i].prop_aule==vett[giocatori[i].pos].proprietario) ///se il proprietario della casella è lo stesso del giocatore
    {
        printf("Quest'aula e' tua. Cosa vuoi fare?\n");
        ///nel caso non ci sia ne scrivania, ne tenda
        if(vett[giocatori[i].pos].flag_scrivania==false && vett[giocatori[i].pos].flag_tenda==false)
        {
            printf("1)Acquistare una scrivania - 50 \n2)Non fare nessuna azione.\n");
            scanf("%d", &scelta);
            getchar();
            if(scelta==1)
            {
                ///sottraggo il costo della scrivania e cambio il flag ad 1
                giocatori[i].budget-=COSTO_SCRIVANIA;
                vett[giocatori[i].pos].flag_scrivania=true;
                printf("Hai acquistato una scrivania su questa casella.\n");
                printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);
            }
            else
            {
                printf("Non hai comprato nulla, alla prossima!\n");
            }
        }
        else
        {
            ///se vi è già la scrivania e non la tenda
            if(vett[giocatori[i].pos].flag_scrivania==true && vett[giocatori[i].pos].flag_tenda==false)
            {
                printf("1)Acquistare una tenda - 100 \n2)Non fare nessuna azione.\n");
                scanf("%d", &scelta);
                getchar();
                if(scelta==1)
                {
                    ///sottraggo il costo della tenda, cambio il flag della scrivania a false
                    ///e metto quello della tenda a true
                    giocatori[i].budget-=COSTO_TENDA;
                    vett[giocatori[i].pos].flag_scrivania=false;
                    vett[giocatori[i].pos].flag_tenda=true;
                    printf("Hai acquistato una tenda su questa casella.\n");
                    printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);
                }
                else
                {
                    printf("Non hai comprato nulla, alla prossima!\n");
                }
            }
            else
            {
                ///altrimenti è gia stata comprata una tenda e non si può fare nulla
                printf("Hai gia' comprato una tenda su questa casella.\n");
            }
        }
    }
    else
    {
        ///nel caso che l'aula non fosse tua
        printf("L'aula non e' tua.\n");

        ///se il giocatore che possedeva l'aula è stato eliminato, ora la proprietà appartiene al Banco
        if(vett[giocatori[i].pos].proprietario==-1)
        {
            printf("L'aula appartiene al Banco.\n");
            printf("Devi pagare %d a al Banco\n", (vett[giocatori[i].pos].costo_aula/20)*MOLTIPLICATORE_PEDAGGIO);
            giocatori[i].budget-=(vett[giocatori[i].pos].costo_aula/20)*MOLTIPLICATORE_PEDAGGIO;
            printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);
        }
        else
        {
            ///se il giocatore è ancora vivo, scorro il proprietario dei giocatori e lo confronto con quello dell'aula
            for(j=0;j<num;j++)
            {
                if(giocatori[j].prop_aule==vett[giocatori[i].pos].proprietario)
                {
                    flag_nome=giocatori[j].prop_aule; ///assegno il proprietario alla variabile flag_nome
                }

            }

            printf("L'aula e' di %s\n", giocatori[flag_nome].nome);

            ///nel caso in cui il possessore dell'aula sia in bagno, non riceve soldi, e il giocatore che vi è finito sopra non paga
            if(giocatori[flag_nome].pul_bagno!=0)
            {
                printf("Il giocatore che possiede il terreno e' in bagno, dunque non puo' ricevere soldi.\n");
            }
            else
            {
                ///altrimenti vengono applicate le tariffe in base all'aula, alle scrivanie e tende
                ///nel caso in cui ci sia il flag della scrivania
                if(vett[giocatori[i].pos].flag_scrivania==true && vett[giocatori[i].pos].flag_tenda==false)
                {
                    ///applico il pedaggio della scrivania moltiplicato per la costante letterale del pedaggio
                    ///sottraggo al budget del giocatore la somma e la aggiungo al budget del proprietario
                    printf("Devi pagare %d a %s\n", vett[giocatori[i].pos].pedaggio_scrivania*MOLTIPLICATORE_PEDAGGIO, giocatori[flag_nome].nome);
                    giocatori[i].budget-=vett[giocatori[i].pos].pedaggio_scrivania*MOLTIPLICATORE_PEDAGGIO;
                    giocatori[flag_nome].budget+=vett[giocatori[i].pos].pedaggio_scrivania*MOLTIPLICATORE_PEDAGGIO;
                    printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);
                }
                else
                {
                    ///nel caso sia true il flag della tenda
                    if(vett[giocatori[i].pos].flag_scrivania==false && vett[giocatori[i].pos].flag_tenda==true)
                    {
                        ///applico il pedaggio della tenda moltiplicato per la costante letterale del pedaggio
                        ///sottraggo al budget del giocatore la somma e la aggiungo al budget del proprietario
                        printf("Devi pagare %d a %s\n", vett[giocatori[i].pos].pedaggio_tenda*MOLTIPLICATORE_PEDAGGIO, giocatori[flag_nome].nome);
                        giocatori[i].budget-=vett[giocatori[i].pos].pedaggio_tenda*MOLTIPLICATORE_PEDAGGIO;
                        giocatori[flag_nome].budget+=vett[giocatori[i].pos].pedaggio_tenda*MOLTIPLICATORE_PEDAGGIO;
                        printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);
                    }
                    else
                    {
                        ///se sia il flag della scrivania e della tenda sono false, applico il pedaggio normale
                        printf("Devi pagare %d a %s\n", (vett[giocatori[i].pos].costo_aula/20)*MOLTIPLICATORE_PEDAGGIO, giocatori[flag_nome].nome);
                        giocatori[i].budget-=(vett[giocatori[i].pos].costo_aula/20)*MOLTIPLICATORE_PEDAGGIO;
                        giocatori[flag_nome].budget+=(vett[giocatori[i].pos].costo_aula/20)*MOLTIPLICATORE_PEDAGGIO;
                        printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);
                    }
                }
            }
        }
    }
}

void casella_sfiga(Giocatore* giocatori, Aula * vett, int i, int num)
{
    int num_tenda=0, num_scrivania=0,j,sfiga=0;
    printf("La casella e' una sfiga.\n");
    Sfiga* sfiga_random; ///creo variabile di tipo Sfiga che conterrà la sfiga random restituita dalla funzione seguente
    sfiga_random=CaricaSfighe(giocatori,i,num,vett);

    ///se il tipo della sfiga è il primo
    if(sfiga_random->t_sfiga==PRIMO)
    {
        printf("%s\n",sfiga_random->sfighe);///stampo la sfiga
        giocatori[i].budget-=sfiga_random->tassa;///sottraggo dal capitale del giocatore la tassa da pagare
        printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);
    }
    else
    {
        ///se la sfiga è del secondo tipo
        if(sfiga_random->t_sfiga==SECONDO)
        {
            printf("%s\n",sfiga_random->sfighe);///stampo la stringa della sfiga
            ///conto le tende e scrivanie che il giocatore possiede
            for(j=0;j<DIM_TAB;j++)
            {
                if(vett[j].proprietario==giocatori[i].prop_aule)
                {
                    if(vett[j].flag_tenda==true)
                        num_tenda++;
                    if(vett[j].flag_scrivania==true)
                        num_scrivania++;
                }
            }

            printf("Numero Aule: %d\n",giocatori[i].n_aule);
            printf("Numero Scrivanie: %d\n",num_scrivania);
            printf("Numero Tende: %d\n",num_tenda);
            ///assegno alla variabile sfiga la sommma delle tasse della sfiga per il numero di aule, scrivanie e tende possedute dal giocatore
            sfiga=(sfiga_random->tassa_aule*giocatori[i].n_aule)+(num_tenda*sfiga_random->tassa_tende)+(num_scrivania*sfiga_random->tassa_scrivanie);
            giocatori[i].budget-=sfiga;///sottraggo la somma precedentemente calcolata
            printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);
        }
        else
        {
            ///se la sfiga è del quarto tipo
            if(sfiga_random->t_sfiga==QUARTO)
            {
                printf("%s\n",sfiga_random->sfighe);///stampo la stringa della sfiga
                printf("Nuova posizione[i]:%d\n",sfiga_random->nuova_posizione);///indico la nuova posizione del giocatore
                giocatori[i].pos=sfiga_random->nuova_posizione;///cambio la posizione attuale del giocatore con quella contenuta nella sfiga
                printf("%s e' finito in %s\n", giocatori[i].nome, vett[giocatori[i].pos].nome_aula);
                controlla_aula(vett,giocatori,i,num);///in base alla tipologia della casella in cui è capitato il giocatore, richiamo la procedura
                ///per gestire i vari casi (AULA, SFIGA, TASSA, ALTRO TIPO)
            }
            else
            {
                ///l'utima sfiga rimanente è quella del terzo tipo, dove viene stamapata solamente la stringa
                printf("%s\n",sfiga_random->sfighe);
            }
        }
    }

}

void casella_tassa(Giocatore* giocatori, Aula* vett, int i)///procedura che gestisce le tasse
{
    ///in base alla posizione della tassa nel tabellone, sottraggo al budget del giocstore l'importo della tassa
    printf("La casella e' una tassa\n");
    printf("Devi pagare %d!\n", vett[giocatori[i].pos].pedaggio);
    giocatori[i].budget-=vett[giocatori[i].pos].pedaggio;
    printf("Budget %s: %d\n", giocatori[i].nome, giocatori[i].budget);
}

void casella_altro_tipo(Giocatore* giocatori, Aula* vett, int i) ///procedura che gestisce le caselle di altro tipo
{
    ///nel caso che il nome dell'aula della posizione del giocatore sia la stessa della casella 30, la BatCaverna
    ///il giocatore viene immediatamente mandato a pulire nei bagni
    printf("La casella e' altro tipo\n");
    if(!strcmp(vett[giocatori[i].pos].nome_aula,vett[30].nome_aula))
    {
        printf("Sei stato sorpreso all'interno della BatCaverna! Fila in bagno!\n");
        printf("Sei finito nei %s!\n",vett[giocatori[i].pos].nome_aula);
        giocatori[i].pos=10;
        giocatori[i].pul_bagno=1;
    }
}


