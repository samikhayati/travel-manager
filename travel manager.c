#include <stdio.h>
#include < ctype.h >
#include <stdlib.h>
#include <conio.h> 
#include <Windows.h>

#pragma comment(lib, "Kernel32.lib")




struct date {
    int j, m, y;
};
struct time {
    int h, m;
};

struct voyage {
    int flight_number;
    struct time start_time;
    struct date start_date;
    struct time end_time;
    struct date end_date;
    char departue[40], destination[40];
    char destination_abv[5], departure_abv[4];
    char airline[40];

};


typedef struct Noeud Noeud;
struct Noeud
{
    struct voyage val;
    struct Noeud* suivant;
};
typedef Noeud* Liste;

void setcursor(int x, int y, HANDLE handle) {
    COORD C;
    C.X = x;
    C.Y = y;
    SetConsoleCursorPosition(handle, C);
}

void clearline(int y,HANDLE handle) {
	COORD C;
	C.X = 0;
	C.Y = y;
    SetConsoleCursorPosition(handle, C);
    printf("                                                                       ");

}


Liste ajout_tete(struct voyage e, Liste L) {       //currently working but you cant use it on first value

    Liste p;
    p = (Noeud*)malloc(sizeof(Noeud));
    p->suivant = L;
    p->val = e;
    L = p;
    return L;
}

Liste supprimer_tete(Liste L) {
    Liste Q;
    if (L) {
        Q = L;
        L = L->suivant;
        free(Q);
    }
    return L;
}

Liste supprimer_queue(Liste L) {
    Liste Q, Pred;
    Q = L;
    Pred = NULL;

    while (Q->suivant) {
        Pred = Q;
        Q = Q->suivant;
    }
    if (Pred == NULL) L = NULL;
    else Pred->suivant = NULL;
    free(Q);
    return L;
}


int d1LTd2v2(struct date d1, struct date d2) {
    int i1, i2;
    i1 = d1.j + d1.m * 31 + d1.y * (12 * 31);
    i2 = d2.j + d2.m * 31 + d2.y * (12 * 31);
    if (i1 < i2) {
        return 1;
    }
    else {
        return 0;
    }
}

int d1LEd2v2(struct date d1, struct date d2) {
    int i1, i2;
    i1 = d1.j + d1.m * 31 + d1.y * (12 * 31);
    i2 = d2.j + d2.m * 31 + d2.y * (12 * 31);
    if (i1 <= i2) {
        return 1;
    }
    else {
        return 0;
    }
}



int v1LTv2(Liste v1,Liste v2) {
    int av1, av2,dv1,dv2;
    dv1 = v1->val.start_date.j+ v1->val.start_date.m*31+ v1->val.start_date.y * (31*12);         //i know not all month have 31 days  but this solution still wokrs
    dv2 = v2->val.start_date.j + v2->val.start_date.m * 31 + v2->val.start_date.y * (31*12);
    if (dv1 < dv2) {
        return 1;
    }
    if (dv2<dv1) {
        return 0;
    }
    av1 = v1->val.start_time.m + v1->val.start_time.h * 60;
    av2 = v2->val.start_time.m + v2->val.start_time.h * 60;
    if (av1 <= av2) {
        return 1;
    }
    else {
        return 0;
    }
}

void afficher_Liste(Liste L) {         //currently working
    int i = 0;
    Liste Q = L;
    if (!Q) printf("\nListe vide ");
    else {
        while (Q) {
            i++;
            printf("\nL'element %d est m %d  h %d  d %d  m %d  y %d TU %d", i, Q->val.start_time.m, Q->val.start_time.h, Q->val.start_date.j, Q->val.start_date.m, Q->val.start_date.y, Q->val.flight_number);
            Q = Q->suivant;
        }
    }
}

Liste ajout_queue(struct voyage e, Liste L) {   //currently working
    Liste p, Q;
    p = (Noeud*)malloc(sizeof(Noeud));
    p->suivant = NULL;
    p->val = e;
    Q = L;
    while (Q->suivant) {
        Q = Q->suivant;
    }
    Q->suivant = p;
    return L;
}
Liste ajout_voyage(struct voyage v, Liste tete) {         //working but dont use it on the  first element
    Liste vl;
    vl = (Noeud*)malloc(sizeof(Noeud));
    vl->val = v;
    vl->suivant = NULL;
    if (v1LTv2(vl,tete)) {
        tete = ajout_tete(v, tete);

    }
    else {
        Liste t1, t2;
        t1 = t2 = tete;
        t2 = t2->suivant;
        while (t2 != NULL) {
            if (v1LTv2(t1,vl) && v1LTv2(vl,t2)) {
                vl->suivant = t2;
                t1->suivant = vl;
                break;


            }
            else {
                t1 = t2;
                t2 = t2->suivant;
            }
        }
        if (t2 == NULL) {
            ajout_queue(v, tete);
        }
    }
    return tete;

}

Liste addflight(Liste L,HANDLE handle) {
    struct voyage v;
    char a[20];
    printf("\nflight number:TU");
    printf("\nstart date:__/__/____             start time:__:__");
    printf("\nend date:__/__/____               end time:__:__");
    printf("\ndeparture:___(abbreviation)/___________________ destination:___(abbreviation)/__________________");
    printf("\nairline:________________");
    setcursor(16, 1, handle);
    scanf_s("%d", &v.flight_number);
    setcursor(11, 2, handle);
    scanf_s("%d", &v.start_date.j);
    setcursor(14, 2, handle);
    scanf_s("%d:", &v.start_date.m);
    setcursor(17, 2, handle);
    scanf_s("%d", &v.start_date.y);
    setcursor(45, 2, handle);
    scanf_s("%d", &v.start_time.h);
    setcursor(48, 2, handle);
    scanf_s("%d", &v.start_time.m);
    setcursor(9, 3, handle);
    scanf_s("%d", &v.end_date.j);
    setcursor(12, 3, handle);
    scanf_s("%d:", &v.end_date.m);
    setcursor(15, 3, handle);
    scanf_s("%d", &v.end_date.y);
    setcursor(43, 3, handle);
    scanf_s("%d", &v.end_time.h);
    setcursor(46, 3, handle);
    scanf_s("%d", &v.end_time.m);
    setcursor(10, 4, handle);
    fgets(a, 20, stdin);
    fgets(v.departure_abv, 6, stdin);
    setcursor(28, 4, handle);
    fgets(v.departue, 40, stdin);
    setcursor(60, 4, handle);
    fgets(v.destination_abv, 6, stdin);
    setcursor(78, 4, handle);
    fgets(v.destination, 40, stdin);
    setcursor(8, 5, handle);
    fgets(v.airline, 40, stdin);
    printf("\n flight added succesfully!");
    printf("\n enter 0 to get back to menu:");
    L = ajout_voyage(v, L);
    return L;

}
void between2d(Liste L,HANDLE handle) {
    struct date d1, d2,dCL;
    printf("\nflights avaible between __/__/____   and __/__/____:");
    setcursor(24, 1, handle);
    scanf_s("%d", &d1.j);
    setcursor(27, 1, handle);
    scanf_s("%d", &d1.m);
    setcursor(30, 1, handle);
    scanf_s("%d", &d1.y);
    setcursor(41, 1, handle);
    scanf_s("%d", &d2.j);
    setcursor(44, 1, handle);
    scanf_s("%d", &d2.m);
    setcursor(47, 1, handle);
    scanf_s("%d", &d2.y);
    Liste CL;
    CL = L;
    int i=6;
    while (CL != NULL) {
        dCL = CL->val.start_date;
        if (d1LEd2v2(d1,dCL)==1) {
            break;
        }
        else {
            CL = CL->suivant;
        }
    }
    if (CL != NULL) {
        printf("\n___________________________________________________________________________");
        printf("\n|start date and time|end date and time|flight number|departure|destination|");
        printf("\n|_________________________________________________________________________|");
        while (CL != NULL) {
            dCL = CL->val.start_date;
            if (d1LEd2v2(dCL, d2) == 1) {
                printf("\n|%d/%d/%d %d:%d",  CL->val.start_date.j, CL->val.start_date.m, CL->val.start_date.y, CL->val.start_time.h, CL->val.start_time.m);
                setcursor(20, i, handle);
                printf("|%d/%d/%d %d:%d", CL->val.end_date.j, CL->val.end_date.m, CL->val.end_date.y, CL->val.end_time.h, CL->val.end_time.m);
                setcursor(38, i, handle);
                printf("|TU %d",CL->val.flight_number);
                setcursor(52, i, handle);
                printf("|%s", CL->val.departure_abv);
                setcursor(62, i, handle);
                printf("|%s", CL->val.destination_abv);
                setcursor(74, i, handle);
                printf("|");
                CL = CL->suivant;
                i = i + 1;
            }
            else {
                break;
            }
        }
        printf("\n|_________________________________________________________________________|");
    }
    printf("\n enter 0 to get back to menu:");

}

Liste remove_flight(Liste tete) {
    int fn;
    printf("give removed flight number:TU");
    scanf_s("%d", &fn);
    Liste CN, c1,c2;
    CN = tete;
    if (CN->val.flight_number == fn) {
        tete=supprimer_tete(tete);
    }
    else {
        c1 = CN;
        CN = CN->suivant;
        while (CN != NULL) {
            if (CN->val.flight_number == fn) {

                c1->suivant = CN->suivant;
                break;
            }
            else {
                c1 = CN;
                CN = CN->suivant;
            }
        }

    }
    printf("\n enter 0 to get back to menu:");
    return tete;
}
Liste modify_flight(Liste tete, HANDLE handle) {
    int fn;
    Liste CN;
    printf("give modified flight number:TU");
    scanf_s("%d", &fn);
    CN = tete;
    while (CN != NULL) {
        if (CN->val.flight_number == fn) {
            break;
        }
        else {
            CN = CN->suivant;
        }
    }
    if (CN != NULL) {
        char a[20];
        printf("\nstart date:__/__/____             start time:__:__");
        printf("\nend date:__/__/____               end time:__:__");
        printf("\ndeparture:___(abbreviation)/___________________ destination:___(abbreviation)/__________________");
        printf("\nairline:________________");
        setcursor(11, 2, handle);
        scanf_s("%d", &CN->val.start_date.j);
        setcursor(14, 2, handle);
        scanf_s("%d:", &CN->val.start_date.m);
        setcursor(17, 2, handle);
        scanf_s("%d", &CN->val.start_date.y);
        setcursor(45, 2, handle);
        scanf_s("%d", &CN->val.start_time.h);
        setcursor(48, 2, handle);
        scanf_s("%d", &CN->val.start_time.m);
        setcursor(9, 3, handle);
        scanf_s("%d", &CN->val.end_date.j);
        setcursor(12, 3, handle);
        scanf_s("%d:", &CN->val.end_date.m);
        setcursor(15, 3, handle);
        scanf_s("%d", &CN->val.end_date.y);
        setcursor(43, 3, handle);
        scanf_s("%d", &CN->val.end_time.h);
        setcursor(46, 3, handle);
        scanf_s("%d\n", &CN->val.end_time.m);
        setcursor(10, 4, handle);
        fgets(CN->val.departure_abv, 6, stdin);
        setcursor(28, 4, handle);
        fgets(CN->val.departue, 40, stdin);
        setcursor(60, 4, handle);
        fgets(CN->val.destination_abv, 6, stdin);
        setcursor(78, 4, handle);
        fgets(CN->val.destination, 40, stdin);
        setcursor(8, 5, handle);
        fgets(CN->val.airline, 40, stdin);
        printf("\n flight modified succesfully!");
        printf("\n enter 0 to get back to menu:");
    }
    return tete;

}
void searchflight(Liste L,HANDLE handle) {

    Liste CL;
    CL = L;
    struct date d1,dCL;
    int i;
    printf("departure date:__/__/____");
    setcursor(15, 0, handle);
    scanf_s("%d", &d1.j);
    setcursor(18, 0, handle);
    scanf_s("%d", &d1.m);
    setcursor(21, 0, handle);
    scanf_s("%d", &d1.y);
    i = 5;
    while (CL != NULL) {
        dCL = CL->val.start_date;
        if ((d1.j == dCL.j) && (d1.m == dCL.m) && (d1.y == dCL.y)) {
            break;
        }
        else {
            CL = CL->suivant;
        }
    }
    if (CL != NULL) {
        printf("\n___________________________________________________________________________");
        printf("\n|start date and time|end date and time|flight number|departure|destination|");
        printf("\n|_________________________________________________________________________|");
        while (CL != NULL) {
            dCL = CL->val.start_date;
            if ((d1.j == dCL.j) && (d1.m == dCL.m) && (d1.y == dCL.y)) {
                printf("\n|%d/%d/%d %d:%d", CL->val.start_date.j, CL->val.start_date.m, CL->val.start_date.y, CL->val.start_time.h, CL->val.start_time.m);
                setcursor(20, i, handle);
                printf("|%d/%d/%d %d:%d", CL->val.end_date.j, CL->val.end_date.m, CL->val.end_date.y, CL->val.end_time.h, CL->val.end_time.m);
                setcursor(38, i, handle);
                printf("|TU %d", CL->val.flight_number);
                setcursor(52, i, handle);
                printf("|%s", CL->val.departure_abv);
                setcursor(62, i, handle);
                printf("|%s", CL->val.destination_abv);
                setcursor(74, i, handle);
                printf("|");
                CL = CL->suivant;
                i = i + 1;
            }
            else {
                break;
            }
        }
        printf("\n|_________________________________________________________________________|");
    }
    printf("\n enter 0 to get back to menu:");
}
void flightdesc(Liste tete,HANDLE handle) {
    printf("give flight number:TU");
    int fn;
    Liste CN;
    scanf_s("%d", &fn);
    CN = tete;
    while (CN != NULL) {
        if (CN->val.flight_number == fn) {
            break;
        }
        else {
            CN = CN->suivant;
        }
    }
    if (CN != NULL) {
        system("cls");
        printf("flight: TU %d -",fn);
        printf("%s", CN->val.airline);
        setcursor(60, 0, handle);
        printf("%d/%d/%d", CN->val.start_date.j, CN->val.start_date.m, CN->val.start_date.y);
        printf("\n---------------------------------------------------------------------------");
        printf("\n departure: ");
        printf("%s", CN->val.departue);
        setcursor(60, 2, handle);
        printf("%d/%d/%d %d:%d", CN->val.start_date.j, CN->val.start_date.m, CN->val.start_date.y, CN->val.start_time.h, CN->val.start_time.m);
        printf("\n destination: ");
        printf("%s", CN->val.destination);
        setcursor(60, 3, handle);
        printf("%d/%d/%d %d:%d", CN->val.end_date.j, CN->val.end_date.m, CN->val.end_date.y, CN->val.end_time.h, CN->val.end_time.m);
        printf("\n---------------------------------------------------------------------------");


    }
    printf("\n enter 0 to get back to menu:");
}

void booking() {
    int a, m, j, h, mn, s;
    char nom[10], prenom[10];
    int cin;
    char cat[2];
    printf("beinvenue!\n");
    printf("donner la date de depart :\n ");
    printf("annee:\t"); do { scanf_s("%d", &a); } while (a < 2022 || a> 2050);
    printf("mois:\t"); do { scanf_s("%d", &m); } while ((m < 0) || m > 12);
    printf("jour:\t"); do { scanf_s("%d", &j); } while ((j < 0) || (j > 31));
    printf("heure:\t"); do { scanf_s("%d", &h); } while (h < 0 || h>24);
    printf("minute:\t"); do { scanf_s("%d", &mn); } while (mn < 0 || mn>59);
    printf("\n donner votre coordonnes!!\n");
    printf("\n nom:\t"); scanf_s("%s", &nom);
    printf("\n prenom:\t"); scanf_s("%s", &prenom);
    printf("\n cin:\t"); scanf_s("%d", &cin);
    //printf("choisir la categorie du votre voyage:\t");scanf("%s",&cat);
    printf("\n votre reservation est reussie");

}

void allflights(Liste L, HANDLE handle) {
    Liste CL;
    struct date dCL;
    CL = L;
    printf("\n___________________________________________________________________________");
    printf("\n|start date and time|end date and time|flight number|departure|destination|");
    printf("\n|_________________________________________________________________________|");
    int i = 4;
    while (CL != NULL) {
        dCL = CL->val.start_date;
        printf("\n|%d/%d/%d %d:%d", CL->val.start_date.j, CL->val.start_date.m, CL->val.start_date.y, CL->val.start_time.h, CL->val.start_time.m);
        setcursor(20, i, handle);
        printf("|%d/%d/%d %d:%d", CL->val.end_date.j, CL->val.end_date.m, CL->val.end_date.y, CL->val.end_time.h, CL->val.end_time.m);
        setcursor(38, i, handle);
        printf("|TU %d", CL->val.flight_number);
        setcursor(52, i, handle);
        printf("|%s", CL->val.departure_abv);
        setcursor(62, i, handle);
        printf("|%s", CL->val.destination_abv);
        setcursor(74, i, handle);
        printf("|");
        CL = CL->suivant;
        i = i + 1;
    }
    printf("\n|_________________________________________________________________________|");
    printf("\n enter 0 to get back to menu:");
}


int main() {                       
    HANDLE handle;                            
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    struct voyage v1, v2, v3, v4, v5,v6,v7,v,v8;      //voyage exemples to test code
    v1.start_time.h = 10;                            //important!!!   //lines from 530 to 636:creating voyage exemples and adding them to the list    //important !!!
    v1.start_time.m = 0;
    v2.start_time.h = 13;
    v2.start_time.m = 0;
    v3.start_time.h = 2;
    v3.start_time.m = 0;
    v4.start_time.h = 7;
    v4.start_time.m = 0;
    v5.start_time.h = 44;
    v5.start_time.m = 0;
    v8.start_time.h = 23;
    v8.start_time.m = 30;
    v.start_time.h = 25;
    v.start_time.m = 0;
    v1.start_date.j = 18;
    v1.start_date.m = 8;
    v1.start_date.y = 2008;
    v2.start_date.j = 17;
    v2.start_date.m = 6;
    v2.start_date.y = 2008;
    v3.start_date.j = 17;
    v3.start_date.m = 6;
    v3.start_date.y = 2009;
    v4.start_date.j = 15;
    v4.start_date.m = 6;
    v4.start_date.y = 2008;
    v5.start_date.j = 15;
    v5.start_date.m = 7;
    v5.start_date.y = 2008;
    v6.start_date.j = 3;
    v6.start_date.m = 4;
    v6.start_date.y = 2018;
    v7.start_date.j = 11;
    v7.start_date.m = 1;
    v7.start_date.y = 1999;
    v6.start_time.h = 12;
    v6.start_time.m = 30;
    v7.start_time.h = 23;
    v7.start_time.m = 11;
    v8.start_date.j = 17;
    v8.start_date.m = 6;
    v8.start_date.y = 2009;
    v1.end_time.h = 10;
    v1.end_time.m = 0;
    v2.end_time.h = 13;
    v2.end_time.m = 0;
    v3.end_time.h = 2;
    v3.end_time.m = 0;
    v4.end_time.h = 7;
    v4.end_time.m = 0;
    v5.end_time.h = 44;
    v5.end_time.m = 0;
    v8.end_time.h = 1;
    v8.end_time.m = 45;
    v1.end_date.j = 18;
    v1.end_date.m = 8;
    v1.end_date.y = 2008;
    v2.end_date.j = 17;
    v2.end_date.m = 6;
    v2.end_date.y = 2008;
    v3.end_date.j = 18;
    v3.end_date.m = 6;
    v3.end_date.y = 2009;
    v4.end_date.j = 16;
    v4.end_date.m = 6;
    v4.end_date.y = 2008;
    v5.end_date.j = 15;
    v5.end_date.m = 7;
    v5.end_date.y = 2008;
    v6.end_date.j = 3;
    v6.end_date.m = 4;
    v6.end_date.y = 2018;
    v7.end_date.j = 11;
    v7.end_date.m = 1;
    v7.end_date.y = 1930;
    v8.end_date.j = 18;
    v8.end_date.m = 6;
    v8.end_date.y = 2009;
    v6.start_time.h = 12;
    v6.start_time.m = 30;
    v7.start_time.h = 23;
    v7.start_time.m = 11;
    v1.flight_number = 1487;
    v2.flight_number = 2645;
    v3.flight_number = 9300;
    v4.flight_number = 1777;
    v5.flight_number = 6666;
    v6.flight_number = 5128;
    v7.flight_number = 6927;
    v8.flight_number = 5514;
    char ch1[40]="tunisia", ch2[4]="tun", ch3[40] = "istanbul", ch4[4] = "ist", ch5[40] = "tunisair";
    strcpy_s(v4.departue, 40, ch1);
    strcpy_s(v4.destination, 40, ch3);
    strcpy_s(v4.airline, 40, ch5);
    strcpy_s(v4.departure_abv, 4, ch2);
    strcpy_s(v4.destination_abv, 4, ch4);
    Liste tete;
    tete = (Noeud*)malloc(sizeof(Noeud));
    tete->val = v1;
    tete->suivant = NULL;
    tete= ajout_voyage(v2,tete);
    tete = ajout_voyage(v3, tete);
    tete = ajout_voyage(v4, tete);
    tete = ajout_voyage(v5, tete);
    tete = ajout_voyage(v7, tete);
    tete = ajout_voyage(v6, tete);
    tete = ajout_voyage(v8, tete);


    printf("\n 1/flighs avaible between two dates                                  creatiors:sami khayati,ayoub riahi");
    printf("\n 2/add flight ");
    printf("\n 3/show flight description ");
    printf("\n 4/modify flight ");
    printf("\n 5/delete flight ");
    printf("\n 6/search flights using a percise date ");
    printf("\n 7/flight booking");
    printf("\n 8/show all avaible flights");
    printf("\n 9/exit");
    printf("\n your choice:");
    setcursor(13,10, handle);
    int choice;

    while (1==1) {
        scanf_s("%d", &choice);
        if (choice == 0) {
            system("cls");
            printf("\n 1/flighs avaible between two dates                                  creatiors:sami khayati,ayoub riahi");
            printf("\n 2/add flight ");
            printf("\n 3/show flight description ");
            printf("\n 4/modify flight ");
            printf("\n 5/delete flight ");
            printf("\n 6/search flights using a percise date ");
            printf("\n 7/flight booking");
            printf("\n 8/show all avaible flights");
            printf("\n 9/exit");
            printf("\n your choice:");
        }
        if (choice == 1) {
            system("cls");
            between2d(tete, handle);
        }
        if (choice == 2) {
            system("cls");
            tete=addflight(tete,handle);
        }
        if (choice == 5) {
            system("cls");
            tete = remove_flight(tete);
        }
        if (choice == 9) {
            return 0;
        }


        if (choice == 4) {
            system("cls");
            tete = modify_flight(tete, handle);
        }
        if (choice == 3) {
            system("cls");
            flightdesc(tete, handle);
        }
        if (choice == 6) {
            system("cls");
            searchflight(tete,handle);
        }
        if (choice == 8) {
            system("cls");
            allflights(tete, handle);
        }
        if (choice == 7) {
            system("cls");
            booking();
        }

        if ((9 < choice) || (choice<0)){
            printf(" error : wrong choice !! ");
        }
    }



}