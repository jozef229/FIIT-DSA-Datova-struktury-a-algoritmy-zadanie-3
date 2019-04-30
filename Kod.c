






//  main.c
//  DSA_3_ZADANIE_VARGA POPOLVAR
//
//  Created by Jozef Varga on 18.11.17.
//  Copyright © 2017 Jozef Varga. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct vrchol{
    int vzdialenost;
    int x;
    int y;
    int pred;
}VRCHOL;

int **teleport0, **teleport1, **teleport2, **teleport3, **teleport4, **teleport5, **teleport6, **teleport7, **teleport8, **teleport9;

void vloz_halda(VRCHOL **halda, VRCHOL *novy, int *pocet_v_halde){
    if(*pocet_v_halde == 0) {
        halda[0] = (VRCHOL*)malloc(sizeof(VRCHOL));
        halda[0]->vzdialenost = -2;
    }
    (*pocet_v_halde)++;
    int aktualny_pocet = *pocet_v_halde;
    halda[*pocet_v_halde] = novy;
    while(halda[aktualny_pocet/2]->vzdialenost > novy->vzdialenost){
        halda[aktualny_pocet] = halda[aktualny_pocet/2];
        if(aktualny_pocet == 1)break;
        aktualny_pocet /= 2;
    }
    halda[aktualny_pocet] = novy;
}

VRCHOL* vyber_halda_min(VRCHOL **halda, int *pocet_v_halde){
    int podstrom, i;
    VRCHOL *hladane = (VRCHOL*)malloc(sizeof(VRCHOL));
    *hladane = *halda[1];
    for(i=1; 2*i < *pocet_v_halde; i=podstrom){
        podstrom = i*2;
        if(podstrom != *pocet_v_halde){
            if(halda[podstrom]->vzdialenost >= halda[podstrom+1]->vzdialenost){
                podstrom++;
            }
        }
        if(halda[*pocet_v_halde]->vzdialenost > halda[podstrom]->vzdialenost){
            halda[i] = halda[podstrom];
        }else break;
    }
    halda[i] = halda[*pocet_v_halde];
    (*pocet_v_halde)--;
    return hladane;
}

int cena_policka(char znak){
    if(znak == 'h' || znak == 'H')return 2;
    else if (znak == 'n' || znak == 'N')return -1;
    else return 1;
}

int **vrat_teleport(char znak, int *x){
    int **teleport = NULL;
    switch (znak) {
        case '0':teleport = teleport0;break;
        case '1':teleport = teleport1;break;
        case '2':teleport = teleport2;break;
        case '3':teleport = teleport3;break;
        case '4':teleport = teleport4;break;
        case '5':teleport = teleport5;break;
        case '6':teleport = teleport6;break;
        case '7':teleport = teleport7;break;
        case '8':teleport = teleport8;break;
        case '9':teleport = teleport9;break;
        default: *x = 1;break;
    }
    return teleport;
}

void nastav_teleport(char znak, int **teleport){
    switch (znak) {
        case '0':teleport0 = teleport;break;
        case '1':teleport1 = teleport;break;
        case '2':teleport2 = teleport;break;
        case '3':teleport3 = teleport;break;
        case '4':teleport4 = teleport;break;
        case '5':teleport5 = teleport;break;
        case '6':teleport6 = teleport;break;
        case '7':teleport7 = teleport;break;
        case '8':teleport8 = teleport;break;
        case '9':teleport9 = teleport;break;
        default:;break;
    }
}

void presun_hodnot_teleportu(int **t0,int **t1,int **t2,int **t3,int **t4,int **t5,int **t6,int **t7,int **t8,int **t9){
    teleport0 = t0;
    teleport1 = t1;
    teleport2 = t2;
    teleport3 = t3;
    teleport4 = t4;
    teleport5 = t5;
    teleport6 = t6;
    teleport7 = t7;
    teleport8 = t8;
    teleport9 = t9;
}

void teleport_dijkstra(char **mapa,VRCHOL **pole_ciest, VRCHOL **halda, VRCHOL *vyber, int n, int m, int *pocet_v_halde){
    int **teleport = NULL;
    int x = 0;
    teleport = vrat_teleport(mapa[vyber->y][vyber->x], &x);
    if(x == 0){
        if(teleport != NULL){
            for(int i = 0;i<(teleport[2][0]);i++){
                if(pole_ciest[teleport[0][i] + (teleport[1][i])*m]->vzdialenost == -2){
                    VRCHOL *vklad;
                    vklad = (VRCHOL*)malloc(sizeof(VRCHOL));
                    vklad->x = teleport[0][i];
                    vklad->y = teleport[1][i];
                    vklad->vzdialenost = pole_ciest[vyber->x + (vyber->y)*m]->vzdialenost;
                    pole_ciest[vklad->x + (vklad->y)*m]->vzdialenost = vklad->vzdialenost;
                    pole_ciest[vklad->x + (vklad->y)*m]->pred = (vyber->x) + vyber->y*m;
                    vloz_halda(halda, vklad, pocet_v_halde);
                }
            }
            teleport = NULL;
            nastav_teleport(mapa[vyber->y][vyber->x], teleport);
        }
    }
}

void nastavenie_vedlajsieho_policka(char **mapa, VRCHOL **pole_ciest, VRCHOL **halda,int zx, int zy, VRCHOL *vyber, int n, int m, int *pocet_v_halde){
    if(pole_ciest[(vyber->x + zx) + (vyber->y + zy)*m]->vzdialenost == -2 && cena_policka(mapa[vyber->y + zy][vyber->x + zx]) != -1){
        VRCHOL *vklad = (VRCHOL*)malloc(sizeof(VRCHOL));
        vklad->x = vyber->x + zx;
        vklad->y = vyber->y + zy;
        vklad->vzdialenost = pole_ciest[vyber->x + (vyber->y)*m]->vzdialenost + cena_policka(mapa[vklad->y][vklad->x]);
        pole_ciest[vklad->x + (vklad->y)*m]->vzdialenost = vklad->vzdialenost;
        pole_ciest[vklad->x + (vklad->y)*m]->pred = (vyber->x) + vyber->y*m;
        vloz_halda(halda, vklad, pocet_v_halde);
    }
}

void dijkstra(char **mapa, VRCHOL **pole_ciest, int x, int y, int n, int m, int teleportovanie){
    for(int i = 0;i<m*n;i++){
        pole_ciest[i]->vzdialenost = -2;
        pole_ciest[i]->x = (i % (m));
        pole_ciest[i]->y = i / (m);
        pole_ciest[i]->pred = -1;
    }
    VRCHOL **halda;
    halda = NULL;
    int pocet_v_halde = 0;
    
    do{
        if(halda == NULL){
            VRCHOL *start;
            start = (VRCHOL*)malloc(sizeof(VRCHOL));
            start->vzdialenost = 0;
            start->pred = -1;
            start->x = x;
            start->y = y;
            pole_ciest[x + (y * m)]->vzdialenost = 0;
            halda =(VRCHOL**)malloc((m*n)*sizeof(VRCHOL*));
            vloz_halda(halda, start, &pocet_v_halde);
        }
        VRCHOL *vyber;
        vyber = vyber_halda_min(halda, &pocet_v_halde);
        if(vyber->x > 0){
            nastavenie_vedlajsieho_policka(mapa, pole_ciest, halda, -1, 0, vyber, n, m, &pocet_v_halde);
        }
        if(vyber->x < m-1){
            nastavenie_vedlajsieho_policka(mapa, pole_ciest, halda, 1, 0,  vyber, n, m, &pocet_v_halde);
        }
        if(vyber->y > 0){
            nastavenie_vedlajsieho_policka(mapa, pole_ciest, halda, 0, -1, vyber, n, m, &pocet_v_halde);
        }
        if(vyber->y < n-1){
            nastavenie_vedlajsieho_policka(mapa, pole_ciest, halda, 0, 1, vyber, n, m, &pocet_v_halde);
        }
        if(teleportovanie != 0){
            teleport_dijkstra(mapa, pole_ciest, halda, vyber, n, m, &pocet_v_halde);
        }
    }while (pocet_v_halde != 0);
    free(halda);
}

int **vyhladaj_cestu(VRCHOL **pole_ciest, int ciel_x, int ciel_y, int start_x, int start_y, int n, int m){
    int **cesta;
    int i = 0;
    cesta = (int **)malloc(4*sizeof(int*));
    cesta[0] = (int*)malloc(sizeof(int));
    cesta[1] = (int*)malloc(sizeof(int));
    cesta[2] = (int*)malloc(sizeof(int));
    cesta[3] = (int*)malloc(sizeof(int));
    cesta[0][i] = start_x;
    cesta[1][i] = start_y;
    cesta[2][i] = pole_ciest[start_x + start_y * m]->vzdialenost;
    int pomoc = pole_ciest[start_x + start_y * m]->pred;
    while(pomoc != -1){
        i++;
        cesta[0] = (int*)realloc(cesta[0], (i+1)*sizeof(int));
        cesta[1] = (int*)realloc(cesta[1], (i+1)*sizeof(int));
        cesta[0][i] = pole_ciest[pomoc]->x;
        cesta[1][i] = pole_ciest[pomoc]->y;
        pomoc = pole_ciest[pomoc]->pred;
    }
    cesta[3][0] = i;
    return cesta;
}

int *stavba_cesty(int *cesta, int **cast, int *x){
    int i;
    if(*x!=0)(*x)--;
    for(i=0+*x;i<=cast[3][0]+*x;i++){
        cesta[i*2] = cast[0][i-*x];
        cesta[i*2+1] = cast[1][i-*x];
    }
    *x=i;
    return cesta;
}

int *stavba_cesty_opacne(int *cesta, int **cast, int *x){
    int i;
    if(*x!=0)(*x)--;
    for(i=cast[3][0];i>=0;i--){
        cesta[*x*2] = cast[0][i];
        cesta[*x*2+1] = cast[1][i];
        (*x)++;
    }
    return cesta;
}

int *vytvor_cestu(int velkost, int **prve,int a, int **druhe,int b,int **tretie, int c,int **stvrte, int d,int **piate, int e, int *x){
    int *cesta = (int *)malloc(velkost*3*sizeof(int));
    if(a==1)cesta = stavba_cesty(cesta, prve, x);
    else if(a==0) cesta = stavba_cesty_opacne(cesta, prve, x);
    if(b==1)cesta = stavba_cesty(cesta, druhe, x);
    else if(b==0) cesta = stavba_cesty_opacne(cesta, druhe, x);
    if(c==1)cesta = stavba_cesty(cesta, tretie, x);
    else if(c==0) cesta = stavba_cesty_opacne(cesta, tretie, x);
    if(d==1)cesta = stavba_cesty(cesta, stvrte, x);
    else if(d==0) cesta = stavba_cesty_opacne(cesta, stvrte, x);
    if(e==1)cesta = stavba_cesty(cesta, piate, x);
    else if(e==0) cesta = stavba_cesty_opacne(cesta, piate, x);
    return cesta;
}

void kontrola_teleport(char **mapa, int i, int j){
    int **teleport = NULL;
    int x = 0;
    teleport = vrat_teleport(mapa[i][j], &x);
    if(x == 0){
        if(teleport == NULL){
            teleport = (int **)malloc((3)*sizeof(int*));
            teleport[0] = (int *)malloc(sizeof(int));
            teleport[1] = (int *)malloc(sizeof(int));
            teleport[2] = (int *)malloc(sizeof(int));
            teleport[0][0] = j;
            teleport[1][0] = i;
            teleport[2][0] = 1;
        }
        else {
            teleport[0] = (int *)realloc(teleport[0], (teleport[2][0] + 1)*sizeof(int));
            teleport[1] = (int *)realloc(teleport[1], (teleport[2][0] + 1)*sizeof(int));
            teleport[2] = (int *)realloc(teleport[2], (teleport[2][0] + 1)*sizeof(int));
            teleport[0][teleport[2][0]] = j;
            teleport[1][teleport[2][0]] = i;
            teleport[2][0]++;
        }
        nastav_teleport(mapa[i][j], teleport);
    }
}

void nastavenie_bodov(int *bod,int x,int y){
    bod[0] = x;
    bod[1] = y;
}

int *zachran_princezne(char **mapa, int n, int m, int t, int *dlzka_cesty){
    int **drak_popolvar, **drak_princezna1, **drak_princezna2, **drak_princezna3, **princezna1_2, **princezna1_3, **princezna2_3;
    int **tdrak_princezna1, **tdrak_princezna2, **tdrak_princezna3, **tprincezna1_2, **tprincezna1_3, **tprincezna2_3;
    int **g_popolvar, **g_princezna1, **g_princezna2, **g_princezna3, **g_drak;
    int **tg_princezna1, **tg_princezna2, **tg_princezna3, **tg_drak;
    int **teleport0Z, **teleport1Z, **teleport2Z, **teleport3Z, **teleport4Z;
    int **teleport5Z, **teleport6Z, **teleport7Z, **teleport8Z, **teleport9Z;
    teleport0 = NULL;
    teleport1 = NULL;
    teleport2 = NULL;
    teleport3 = NULL;
    teleport4 = NULL;
    teleport5 = NULL;
    teleport6 = NULL;
    teleport7 = NULL;
    teleport8 = NULL;
    teleport9 = NULL;
    int drak_bod[2] = {0,0}, princezna1_bod[2] = {0,0}, princezna2_bod[2] = {0,0}, princezna3_bod[2] = {0,0}, generator_bod[2] = {0,0};
    VRCHOL **pole_ciest;
    pole_ciest = (VRCHOL**)malloc((m*n)*sizeof(VRCHOL*));
    for(int i = 0;i<m*n;i++){
        pole_ciest[i] = (VRCHOL*)malloc(sizeof(VRCHOL));
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            kontrola_teleport(mapa,i,j);
            if(mapa[i][j] == 'd' || mapa[i][j] == 'D'){
                nastavenie_bodov(drak_bod, j, i);
            }
            if(mapa[i][j] == 'g' || mapa[i][j] == 'G'){
                nastavenie_bodov(generator_bod, j, i);
            }
            if(mapa[i][j] == 'p' || mapa[i][j] == 'P'){
                if(princezna1_bod[0] == 0 && princezna1_bod[1] == 0){
                    nastavenie_bodov(princezna1_bod, j, i);
                }else if(princezna2_bod[0] == 0 && princezna2_bod[1] == 0){
                    nastavenie_bodov(princezna2_bod, j, i);
                }else if(princezna3_bod[0] == 0 && princezna3_bod[1] == 0){
                    nastavenie_bodov(princezna3_bod, j, i);
                }
            }
        }
    }
    teleport0Z = teleport0;
    teleport1Z = teleport1;
    teleport2Z = teleport2;
    teleport3Z = teleport3;
    teleport4Z = teleport4;
    teleport5Z = teleport5;
    teleport6Z = teleport6;
    teleport7Z = teleport7;
    teleport8Z = teleport8;
    teleport9Z = teleport9;
    
    dijkstra(mapa, pole_ciest, generator_bod[0], generator_bod[1], n, m, 0);    //dijkstra od generatora vsade bez teleportov
    g_popolvar = vyhladaj_cestu(pole_ciest, generator_bod[0], generator_bod[1], 0, 0 , n, m);
    g_drak = vyhladaj_cestu(pole_ciest, generator_bod[0], generator_bod[1], drak_bod[0], drak_bod[1] , n, m);
    g_princezna1 = vyhladaj_cestu(pole_ciest, generator_bod[0], generator_bod[1], princezna1_bod[0], princezna1_bod[1] , n, m);
    g_princezna2 = vyhladaj_cestu(pole_ciest, generator_bod[0], generator_bod[1], princezna2_bod[0], princezna2_bod[1] , n, m);
    g_princezna3 = vyhladaj_cestu(pole_ciest, generator_bod[0], generator_bod[1], princezna3_bod[0], princezna3_bod[1] , n, m);
    
    dijkstra(mapa, pole_ciest, generator_bod[0], generator_bod[1], n, m, 1);    //dijkstra od generatora vsade s teleportom
    tg_drak = vyhladaj_cestu(pole_ciest, generator_bod[0], generator_bod[1], drak_bod[0], drak_bod[1] , n, m);
    tg_princezna1 = vyhladaj_cestu(pole_ciest, generator_bod[0], generator_bod[1], princezna1_bod[0], princezna1_bod[1] , n, m);
    tg_princezna2 = vyhladaj_cestu(pole_ciest, generator_bod[0], generator_bod[1], princezna2_bod[0], princezna2_bod[1] , n, m);
    tg_princezna3 = vyhladaj_cestu(pole_ciest, generator_bod[0], generator_bod[1], princezna3_bod[0], princezna3_bod[1] , n, m);
    presun_hodnot_teleportu(teleport0Z,teleport1Z,teleport2Z,teleport3Z,teleport4Z,teleport5Z,teleport6Z,teleport7Z,teleport8Z,teleport9Z);
    
    dijkstra(mapa, pole_ciest, drak_bod[0], drak_bod[1], n, m, 0);      //dijkstra od draka vsade bez teleportom
    drak_popolvar = vyhladaj_cestu(pole_ciest, drak_bod[0], drak_bod[1], 0, 0 , n, m);
    drak_princezna1 = vyhladaj_cestu(pole_ciest, drak_bod[0], drak_bod[1], princezna1_bod[0], princezna1_bod[1] , n, m);
    drak_princezna2 = vyhladaj_cestu(pole_ciest, drak_bod[0], drak_bod[1], princezna2_bod[0], princezna2_bod[1] , n, m);
    drak_princezna3 = vyhladaj_cestu(pole_ciest, drak_bod[0], drak_bod[1], princezna3_bod[0], princezna3_bod[1] , n, m);
    
    dijkstra(mapa, pole_ciest, drak_bod[0], drak_bod[1], n, m, 1);      //dijkstra od draka vsade s teleportom
    tdrak_princezna1 = vyhladaj_cestu(pole_ciest, drak_bod[0], drak_bod[1], princezna1_bod[0], princezna1_bod[1] , n, m);
    tdrak_princezna2 = vyhladaj_cestu(pole_ciest, drak_bod[0], drak_bod[1], princezna2_bod[0], princezna2_bod[1] , n, m);
    tdrak_princezna3 = vyhladaj_cestu(pole_ciest, drak_bod[0], drak_bod[1], princezna3_bod[0], princezna3_bod[1] , n, m);
    presun_hodnot_teleportu(teleport0Z,teleport1Z,teleport2Z,teleport3Z,teleport4Z,teleport5Z,teleport6Z,teleport7Z,teleport8Z,teleport9Z);
    
    dijkstra(mapa, pole_ciest, princezna1_bod[0], princezna1_bod[1], n, m, 0);  //dijkstra od princezna1 vsade bez teleportom
    princezna1_2 = vyhladaj_cestu(pole_ciest, princezna1_bod[0], princezna1_bod[1], princezna2_bod[0], princezna2_bod[1] , n, m);
    princezna1_3 = vyhladaj_cestu(pole_ciest, princezna1_bod[0], princezna1_bod[1], princezna3_bod[0], princezna3_bod[1] , n, m);
    
    dijkstra(mapa, pole_ciest, princezna1_bod[0], princezna1_bod[1], n, m, 1);  //dijkstra od princezna1 vsade s teleportom
    tprincezna1_2 = vyhladaj_cestu(pole_ciest, princezna1_bod[0], princezna1_bod[1], princezna2_bod[0], princezna2_bod[1] , n, m);
    tprincezna1_3 = vyhladaj_cestu(pole_ciest, princezna1_bod[0], princezna1_bod[1], princezna3_bod[0], princezna3_bod[1] , n, m);
    presun_hodnot_teleportu(teleport0Z,teleport1Z,teleport2Z,teleport3Z,teleport4Z,teleport5Z,teleport6Z,teleport7Z,teleport8Z,teleport9Z);
    
    dijkstra(mapa, pole_ciest, princezna2_bod[0], princezna2_bod[1], n, m, 0);  //dijkstra od princezna2 vsade bez teleportom
    princezna2_3 = vyhladaj_cestu(pole_ciest, princezna2_bod[0], princezna2_bod[1], princezna3_bod[0], princezna3_bod[1] , n, m);
    
    dijkstra(mapa, pole_ciest, princezna2_bod[0], princezna2_bod[1], n, m, 1); //dijkstra od princezna2 vsade s teleportom
    tprincezna2_3 = vyhladaj_cestu(pole_ciest, princezna2_bod[0], princezna2_bod[1], princezna3_bod[0], princezna3_bod[1] , n, m);
    presun_hodnot_teleportu(teleport0Z,teleport1Z,teleport2Z,teleport3Z,teleport4Z,teleport5Z,teleport6Z,teleport7Z,teleport8Z,teleport9Z);
    
    int D123, D132, D213, D231, D312, D321;
    int TD123, TD132, TD213, TD231, TD312, TD321;
    int DT123, DT132, DT213, DT231, DT312, DT321;
    int D1T23, D1T32, D2T13, D2T31, D3T12, D3T21;
    int D12T3, D13T2, D21T3, D23T1, D31T2, D32T1;
    
    int najkratsia_cesta[30];
    najkratsia_cesta[0] = D123 = drak_popolvar[2][0] + drak_princezna1[2][0] + princezna1_2[2][0] + princezna2_3[2][0];
    najkratsia_cesta[1] = D132 = drak_popolvar[2][0] + drak_princezna1[2][0] + princezna1_3[2][0] + princezna2_3[2][0];
    najkratsia_cesta[2] = D213 = drak_popolvar[2][0] + drak_princezna2[2][0] + princezna1_2[2][0] + princezna1_3[2][0];
    najkratsia_cesta[3] = D231 = drak_popolvar[2][0] + drak_princezna2[2][0] + princezna2_3[2][0] + princezna1_3[2][0];
    najkratsia_cesta[4] = D312 = drak_popolvar[2][0] + drak_princezna3[2][0] + princezna1_3[2][0] + princezna1_2[2][0];
    najkratsia_cesta[5] = D321 = drak_popolvar[2][0] + drak_princezna3[2][0] + princezna2_3[2][0] + princezna1_2[2][0];
    najkratsia_cesta[6] = TD123 = g_popolvar[2][0] + tg_drak[2][0] + tdrak_princezna1[2][0] + tprincezna1_2[2][0] + tprincezna2_3[2][0];
    najkratsia_cesta[7] = TD132 = g_popolvar[2][0] + tg_drak[2][0] + tdrak_princezna1[2][0] + tprincezna1_3[2][0] + tprincezna2_3[2][0];
    najkratsia_cesta[8] = TD213 = g_popolvar[2][0] + tg_drak[2][0] + tdrak_princezna2[2][0] + tprincezna1_2[2][0] + tprincezna1_3[2][0];
    najkratsia_cesta[9] = TD231 = g_popolvar[2][0] + tg_drak[2][0] + tdrak_princezna2[2][0] + tprincezna2_3[2][0] + tprincezna1_3[2][0];
    najkratsia_cesta[10] = TD312 = g_popolvar[2][0] + tg_drak[2][0] + tdrak_princezna3[2][0] + tprincezna1_3[2][0] + tprincezna1_2[2][0];
    najkratsia_cesta[11] = TD321 = g_popolvar[2][0] + tg_drak[2][0] + tdrak_princezna3[2][0] + tprincezna2_3[2][0] + tprincezna1_2[2][0];
    najkratsia_cesta[12] = DT123 = drak_popolvar[2][0] + g_drak[2][0] + tg_princezna1[2][0] + tprincezna1_2[2][0] + tprincezna2_3[2][0];
    najkratsia_cesta[13] = DT132 = drak_popolvar[2][0] + g_drak[2][0] + tg_princezna1[2][0] + tprincezna1_3[2][0] + tprincezna2_3[2][0];
    najkratsia_cesta[14] = DT213 = drak_popolvar[2][0] + g_drak[2][0] + tg_princezna2[2][0] + tprincezna1_2[2][0] + tprincezna1_3[2][0];
    najkratsia_cesta[15] = DT231 = drak_popolvar[2][0] + g_drak[2][0] + tg_princezna2[2][0] + tprincezna2_3[2][0] + tprincezna1_3[2][0];
    najkratsia_cesta[16] = DT312 = drak_popolvar[2][0] + g_drak[2][0] + tg_princezna3[2][0] + tprincezna1_3[2][0] + tprincezna1_2[2][0];
    najkratsia_cesta[17] = DT321 = drak_popolvar[2][0] + g_drak[2][0] + tg_princezna3[2][0] + tprincezna2_3[2][0] + tprincezna1_2[2][0];
    najkratsia_cesta[18] = D1T23 = drak_popolvar[2][0] + drak_princezna1[2][0] + g_princezna1[2][0] + tg_princezna2[2][0] + tprincezna2_3[2][0];
    najkratsia_cesta[19] = D1T32 = drak_popolvar[2][0] + drak_princezna1[2][0] + g_princezna1[2][0] + tg_princezna3[2][0] + tprincezna2_3[2][0];
    najkratsia_cesta[20] = D2T13 = drak_popolvar[2][0] + drak_princezna2[2][0] + g_princezna2[2][0] + tg_princezna1[2][0] + tprincezna1_3[2][0];
    najkratsia_cesta[21] = D2T31 = drak_popolvar[2][0] + drak_princezna2[2][0] + g_princezna3[2][0] + tg_princezna2[2][0] + tprincezna1_3[2][0];
    najkratsia_cesta[22] = D3T12 = drak_popolvar[2][0] + drak_princezna3[2][0] + g_princezna3[2][0] + tg_princezna1[2][0] + tprincezna1_2[2][0];
    najkratsia_cesta[23] = D3T21 = drak_popolvar[2][0] + drak_princezna3[2][0] + g_princezna3[2][0] + tg_princezna2[2][0] + tprincezna1_2[2][0];
    najkratsia_cesta[24] = D12T3 = drak_popolvar[2][0] + drak_princezna1[2][0] + princezna1_2[2][0] + g_princezna2[2][0] + tg_princezna3[2][0];
    najkratsia_cesta[25] = D13T2 = drak_popolvar[2][0] + drak_princezna1[2][0] + princezna1_3[2][0] + g_princezna3[2][0] + tg_princezna2[2][0];
    najkratsia_cesta[26] = D21T3 = drak_popolvar[2][0] + drak_princezna2[2][0] + princezna1_2[2][0] + g_princezna1[2][0] + tg_princezna3[2][0];
    najkratsia_cesta[27] = D23T1 = drak_popolvar[2][0] + drak_princezna2[2][0] + princezna2_3[2][0] + g_princezna3[2][0] + tg_princezna1[2][0];
    najkratsia_cesta[28] = D31T2 = drak_popolvar[2][0] + drak_princezna3[2][0] + princezna1_3[2][0] + g_princezna1[2][0] + tg_princezna2[2][0];
    najkratsia_cesta[29] = D32T1 = drak_popolvar[2][0] + drak_princezna3[2][0] + princezna2_3[2][0] + g_princezna2[2][0] + tg_princezna1[2][0];
    
    int min = najkratsia_cesta[0];
    for(int i = 0; i<30;i++){
        if(najkratsia_cesta[i]<min)min = najkratsia_cesta[i];
    }
    
    int *cesta = NULL, miesto = 0;
    if(D123 == min){
        cesta = vytvor_cestu(D123, drak_popolvar, 1, drak_princezna1, 0, princezna1_2, 0, princezna2_3, 0, NULL, 3, &miesto);
    }else if(D132 == min){
        cesta = vytvor_cestu(D132, drak_popolvar, 1, drak_princezna1, 0, princezna1_3, 0, princezna2_3, 1, NULL, 3, &miesto);
    }else if(D213 == min){
        cesta = vytvor_cestu(D213, drak_popolvar, 1, drak_princezna2, 0, princezna1_2, 1, princezna1_3, 0, NULL, 3, &miesto);
    }else if(D231 == min){
        cesta = vytvor_cestu(D231, drak_popolvar, 1, drak_princezna2, 0, princezna2_3, 0, princezna1_3, 1, NULL, 3, &miesto);
    }else if(D312 == min){
        cesta = vytvor_cestu(D312, drak_popolvar, 1, drak_princezna3, 0, princezna1_3, 1, princezna1_2, 0, NULL, 3, &miesto);
    }else if(D321 == min){
        cesta = vytvor_cestu(D321, drak_popolvar, 1, drak_princezna3, 0, princezna2_3, 1, princezna1_2, 1, NULL, 3, &miesto);
    }else if(TD123 == min){
        cesta = vytvor_cestu(TD123, g_popolvar, 1, tg_drak, 0, tdrak_princezna1, 0, tprincezna1_2, 0, tprincezna2_3, 0, &miesto);
    }else if(TD132 == min){
        cesta = vytvor_cestu(TD132, g_popolvar, 1, tg_drak, 0, tdrak_princezna1, 0, tprincezna1_3, 0, tprincezna2_3, 1, &miesto);
    }else if(TD213 == min){
        cesta = vytvor_cestu(TD213, g_popolvar, 1, tg_drak, 0, tdrak_princezna2, 0, tprincezna1_2, 1, tprincezna1_3, 0, &miesto);
    }else if(TD231 == min){
        cesta = vytvor_cestu(TD231, g_popolvar, 1, tg_drak, 0, tdrak_princezna2, 0, tprincezna2_3, 0, tprincezna1_3, 1, &miesto);
    }else if(TD312 == min){
        cesta = vytvor_cestu(TD312, g_popolvar, 1, tg_drak, 0, tdrak_princezna3, 0, tprincezna1_3, 1, tprincezna1_2, 0, &miesto);
    }else if(TD321 == min){
        cesta = vytvor_cestu(TD321, g_popolvar, 1, tg_drak, 0, tdrak_princezna3, 0, tprincezna2_3, 1, tprincezna1_2, 1, &miesto);
    }else if(DT123 == min){
        cesta = vytvor_cestu(DT123, drak_popolvar, 1, g_drak, 1, tg_princezna1, 0, tprincezna1_2, 0, tprincezna2_3, 0, &miesto);
    }else if(DT132 == min){
        cesta = vytvor_cestu(DT132, drak_popolvar, 1, g_drak, 1, tg_princezna1, 0, tprincezna1_3, 0, tprincezna2_3, 1, &miesto);
    }else if(DT213 == min){
        cesta = vytvor_cestu(DT213, drak_popolvar, 1, g_drak, 1, tg_princezna2, 0, tprincezna1_2, 1, tprincezna1_3, 0, &miesto);
    }else if(DT231 == min){
        cesta = vytvor_cestu(DT231, drak_popolvar, 1, g_drak, 1, tg_princezna2, 0, tprincezna2_3, 0, tprincezna1_3, 1, &miesto);
    }else if(DT312 == min){
        cesta = vytvor_cestu(DT312, drak_popolvar, 1, g_drak, 1, tg_princezna3, 0, tprincezna1_3, 1, tprincezna1_2, 0, &miesto);
    }else if(DT321 == min){
        cesta = vytvor_cestu(DT321, drak_popolvar, 1, g_drak, 1, tg_princezna3, 0, tprincezna2_3, 1, tprincezna1_2, 1, &miesto);
    }else if(D1T23 == min){
        cesta = vytvor_cestu(D1T23, drak_popolvar, 1, drak_princezna1, 0, g_princezna1, 1, tg_princezna2, 0, tprincezna2_3, 0, &miesto);
    }else if(D1T32 == min){
        cesta = vytvor_cestu(D1T32, drak_popolvar, 1, drak_princezna1, 0, g_princezna1, 1, tg_princezna3, 0, tprincezna2_3, 1, &miesto);
    }else if(D2T13 == min){
        cesta = vytvor_cestu(D2T13, drak_popolvar, 1, drak_princezna2, 0, g_princezna2, 1, tg_princezna1, 0, tprincezna1_3, 0, &miesto);
    }else if(D2T31 == min){
        cesta = vytvor_cestu(D2T31, drak_popolvar, 1, drak_princezna2, 0, g_princezna2, 1, tg_princezna3, 0, tprincezna1_3, 1, &miesto);
    }else if(D3T12 == min){
        cesta = vytvor_cestu(D3T12, drak_popolvar, 1, drak_princezna3, 0, g_princezna3, 1, tg_princezna1, 0, tprincezna1_2, 0, &miesto);
    }else if(D3T21 == min){
        cesta = vytvor_cestu(D3T21, drak_popolvar, 1, drak_princezna3, 0, g_princezna3, 1, tg_princezna2, 0, tprincezna1_2, 1, &miesto);
    }else if(D12T3 == min){
        cesta = vytvor_cestu(D12T3, drak_popolvar, 1, drak_princezna1, 0, princezna1_2, 0, g_princezna2, 1, tg_princezna3, 0, &miesto);
    }else if(D13T2 == min){
        cesta = vytvor_cestu(D13T2, drak_popolvar, 1, drak_princezna1, 0, princezna1_3, 0, g_princezna3, 1, tg_princezna2, 0, &miesto);
    }else if(D21T3 == min){
        cesta = vytvor_cestu(D21T3, drak_popolvar, 1, drak_princezna2, 0, princezna1_2, 1, g_princezna1, 1, tg_princezna3, 0, &miesto);
    }else if(D23T1 == min){
        cesta = vytvor_cestu(D23T1, drak_popolvar, 1, drak_princezna2, 0, princezna2_3, 0, g_princezna3, 1, tg_princezna1, 0, &miesto);
    }else if(D31T2 == min){
        cesta = vytvor_cestu(D31T2, drak_popolvar, 1, drak_princezna3, 0, princezna1_3, 1, g_princezna1, 1, tg_princezna2, 0, &miesto);
    }else if(D32T1 == min){
        cesta = vytvor_cestu(D32T1, drak_popolvar, 1, drak_princezna3, 0, princezna2_3, 1, g_princezna2, 1, tg_princezna1, 0, &miesto);
    }
    *dlzka_cesty = miesto;
    free(teleport0);
    free(teleport1);
    free(teleport2);
    free(teleport3);
    free(teleport4);
    free(teleport5);
    free(teleport6);
    free(teleport7);
    free(teleport8);
    free(teleport9);
    return cesta;
}

// Vlastna funkcia main() je pre vase osobne testovanie. Dolezite: pri testovacich scenaroch sa nebude spustat!
int main()
{
    return 0;
}

//
//int main(){
//    int i;
//    int j;
//    int dlzka_cesty = 0;
//    int t = 30;
//    int n;
//    int m;
//    char **mapa;
//
//
//    //  test 1
//    //        m=5;
//    //        n=5;
//    //        mapa = (char**)malloc(n * sizeof(char*));
//    //        mapa[0] = "PPHHH";
//    //        mapa[1] = "HCHHC";
//    //        mapa[2] = "CCHCC";
//    //        mapa[3] = "CHCHC";
//    //        mapa[4] = "HPCDC";
//
//    //    test2
//    //    m = 7;
//    //    n = 7;
//    //    mapa = (char**)malloc(n * sizeof(char*));
//    //    mapa[0] = "CCCHHCH";
//    //    mapa[1] = "CCHHHCH";
//    //    mapa[2] = "HCDCHHC";
//    //    mapa[3] = "HHHCHHC";
//    //    mapa[4] = "HCHHCCC";
//    //    mapa[5] = "HCHHPHH";
//    //    mapa[6] = "PCHCHHP";
//
//    //   test3
//    //   n = 5;
//    //   m = 30;
//    //   mapa = (char**)malloc(n * sizeof(char*));
//    //   mapa[0] = "HHHHHCHCCCHHHCHHHHPDHCCCCHCCCH";
//    //   mapa[1] = "CCHCCCCCCHCCCCCHCHHHCCCCCCHCCH";
//    //   mapa[2] = "CCCCCHPCCCHHCCHCCCCHCCCCHCCCCH";
//    //   mapa[3] = "CCCCHHHHCHCCCHCCCCCHCCHCCCCHCH";
//    //   mapa[4] = "CPHHCCHHCCCHHCHHHCCHCHCHHCCHCC";
//
//    //  test 5
//    //    n = 40;
//    //    m = 50;
//    //    mapa = (char**)malloc(n * sizeof(char*));
//    //    mapa[0] = "CCCCCCCCHGCCCHCCCCCCHCCCCCCCHCCCHHHCHCCCCCCCCCCCCC";
//    //    mapa[1] = "CCCCCCCHC2CHCCCHCHCCCCCHHHCHCCHHHCCC0CCCCHCCHCCCCC";
//    //    mapa[2] = "CCCHCCCC0CCC2CCCCHCCCCHCCCCCCCCCHCCCCCCHCCCCCHHCHC";
//    //    mapa[3] = "CHCCCCCCCCCCCCCCCCCHHHCCCCHCHCHCHCC3CCHCCCCHCCCHCC";
//    //    mapa[4] = "CCCHCCCHCHHCCHCCCCCHHCCHCCHCCCCCCHHCCHCCHHCHCCCCCH";
//    //    mapa[5] = "HCCCCHCCHCCC0CCCCCCCCHCHCCCCCHCCCCHCCCCCCHHCCHCCCC";
//    //    mapa[6] = "CCCHCHCCCCCHHCCCCCCHCCCCCHCCPCCCCCCCHCCCCCCCCHCHCC";
//    //    mapa[7] = "CCCHCHCCHCHCCCCHHCCCCCCCCCCCHCCHCCCCCCCCCCCHCCCHHC";
//    //    mapa[8] = "CCCCCCCCCCCCCHCCCCCHCHHCCHCCCCCCHHCCC3CHCHHCCCCCCH";
//    //    mapa[9] = "CCCCCCHCCHC0HCCHCCHHCCCHCCCCCCCCHCCCCCCCCCCHHC3HCC";
//    //    mapa[10] = "CCCHCCCCCCHCCHCCCCHHCHCCCCCCCCCHCCHCCCCCHCCCCCCCCC";
//    //    mapa[11] = "HCCCCHHCCCCCCCCCCCCCHCCCCHHCCCCCCHCCHCCCCCCHCCCHCC";
//    //    mapa[12] = "CCCHCCCCCCHCCCCCHHCCC0CCCHCHH1CCCCCCHCCCCCHCCHCCCC";
//    //    mapa[13] = "HHCCCCCCHHCCCHHCHCCCCCCCCCCCCCCCCCCCHCHCCHCCCCHCCC";
//    //    mapa[14] = "CCCCHCHCCHHCHHCCCHHCCHHCCCHCCCCCCCHHCCCCCCCCHCCCHC";
//    //    mapa[15] = "CCCHCCHHCHCCHHCCCCCHCCCCCCCCCHCCCCCCCCCCCCCCCCCCCC";
//    //    mapa[16] = "CCCCCCC2CHCCHCCCCCHCCCHCCCHHCCHCCHHCCCCCCCHCC0HHHC";
//    //    mapa[17] = "HHCCCPCCCHCHH1CCCHCHCCCHCCCHCHHCCCCCCCCCCCCHCCCCCC";
//    //    mapa[18] = "CCCCCCCHCHCCCHHCHCCHCHCCCCCCCCCCHCCCCCCCCCCCCHCCCC";
//    //    mapa[19] = "CCCHCCCCCCCHHCH0CCCCCCCHCHCCCCHHHCCCCHCHCCCCCCC2CC";
//    //    mapa[20] = "CCHHCCHCCCCCCCCCCCCCCCHCCCCCCCCHCCCCCCHCCCCCHCHCHH";
//    //    mapa[21] = "HHCHCCCCCCCCCCCCCCCHCHCCCCCCHCCHCCCCCCCCCCCCCCCHCC";
//    //    mapa[22] = "CCHCC0CHCCCCCHCCCCCCCCCCCHCHCCCC3HHCCCCCCC2CCCCCCC";
//    //    mapa[23] = "HHCCCCHCCHCCCCCCCHCCCCCCCCCCCHCCHHCCHCCCHCHCHCHHCC";
//    //    mapa[24] = "CCHCCCCHCCCCCCCCHCCCCCCCCCCCCHHHHHCHCCCCCCCCHCCCCC";
//    //    mapa[25] = "CCCCCCCCHHCCCCCCCCCCCCHCCCHHCCCCCCHDCCCCCHCHCCHCCC";
//    //    mapa[26] = "HCCCCCCCHHCCHCHCCCCHCHCCCCCCCCCCCCCHCCC2CCCCCCCCCC";
//    //    mapa[27] = "HCHCHCHHHCCCCHHCCCCCHCC1CHCCHHCHHCCHCCCCCCCCCCCCCC";
//    //    mapa[28] = "CCCCCCCCCCCHCCCCCCHCCCHCCHHHCCCCCHCCCCCHCCCCCCCCHC";
//    //    mapa[29] = "CCHCHCCCCCCCCHCCCCHCHC2HHCCPHC0HCHHHCC2HCCHHHHCCCC";
//    //    mapa[30] = "CCCCCCCCCCCHCCCCHCHCCCCCCCCHCCCCCCCCHHHCCHCCHCCCCH";
//    //    mapa[31] = "CCHCCCCCCCCCCCCCHCCCCCCCCCCCCCHCCCCCCCHCCCCHCCHHHC";
//    //    mapa[32] = "CHCHCCCCCCCHCCHHHCCHCCCCCHCHCCCCCHCHCCHCCCCCCCHCCC";
//    //    mapa[33] = "HCCHCCHHCCCCCCCHHHCHHHCHHCCHCHCCCCCCCHCCCCCHCCCCCC";
//    //    mapa[34] = "CCCCCCCCCCCCCCCCHCCCCCCHCHCCCHCCHHHCCHCHCCHHCCCCCH";
//    //    mapa[35] = "CHCCHCCCHCCCCHCCCCCHHHCHCCCHHCCCCCCCHHCCCHCHCCHCCC";
//    //    mapa[36] = "CCHCCCHCCCCCCCCCCC2CCCCCCHCCCCCCHCCCCCCCHCCCHCCCCC";
//    //    mapa[37] = "HCCCCHHHCCCCCCHCCCHCHCCCCHCCCHCCCCCHCCCCCCCCCCCHCH";
//    //    mapa[38] = "CHHHHHHHCCHCCCCCHCCCHCCCCCCCCHCHCCCCCCCHHCCCCHCCC0";
//    //    mapa[39] = "CCCCHHCCCHHCHCCCCCHHCCCHCCCCCCHHCCCCCCCHCCCHCCCCCC";
//    //
//
//    //        m=5;
//    //        n=5;
//    //        mapa = (char**)malloc(n * sizeof(char*));
//    //        mapa[0] = "0GPH0";
//    //        mapa[1] = "PCHHC";
//    //        mapa[2] = "CCHCC";
//    //        mapa[3] = "CHCHC";
//    //        mapa[4] = "HP0DH";
//    m=150;
//    n=150;
//    mapa = (char**)malloc(n * sizeof(char*));
//    int k = 0;
//    mapa[k] = "CHHHCCCCCCHHCHCHHHCHCHHHCHCCHHHHCCHCCHHCHHHHCHCHHHCCHCHCHHCHCHHHHCHHCCHHHCHCHHHHHHHCHHHCCHCCHCHHHHHHCHHCHCCHCHHHCHCCCCCHHHHHCHHCCCCHCCHCHHCHCHCCCHHCHH";k++;
//    mapa[k] = "CHHHCHHHCCHHHHCCCHCHHCHHHCHHCCHCHCHHHCCHCCCCCHCHHCHCHCHHCHCHCHHHHCHCCCCHCHCCHHHHCCHHCCCCCCHHHHCHHHHCCHHCCCHHHCHHHCHCCCCHHCCCCHHHHCCHHHCHCCCHHHHCHCHCCH";k++;
//    mapa[k] = "CCHCCHHCHHHHCCCCCHCCCHCCHHHCHCCCHCCHCCCHHCHCCHCCHHCHHHCHHHCCHHHCCCHCHCHHHHCHHCCCHCHHCHCHHHCHCCHHCHHCHHCHHCCHHCHCCHHHCHCHHCCCCCCCHCCHHHHCHCCCHHCCHHHHHH";k++;
//    mapa[k] = "HCHCCHHHHHHCHCHHCHHHCHHCCCHHHCCCHCHHCHCCCHCHHHHCHCHHCHHHHCCHCHHHHCCHHHHHCHCCHCCHCHHCHCHHHHCHCHHCHHHHHCHHHHCHCCHHHCHCCHCCCHHCCHCHHHHHCHCCCHCHHHCCHCCCHH";k++;
//    mapa[k] = "CCHHHHCCCHCCHCCHHHCCHCCCHCCCHCHCCHCCHHHHCCHHHHHCHCHHCHHCHCCHHCCCHHCHHCHCCHHHCCHCCCHHHHCHCCHCHCCCCHHCCCCHHHC1HHCHCHCCCCHCHHCCCCHHHCHCHHCHCCHHHCCHCCHCCH";k++;
//    mapa[k] = "HHHCHCCHHHHHHCHCCHCHHHCHHHHCHHHHCCCCCHHCHHCCCHHCHHHHCHCCHHHHHCHCCHCCCHHCHHCCHHHHHCCHCCHHHHCHCCHHHCCHHHHCHCHHCHCHCCCCCHHHCCCHCHCHHHHHCHCHHHHCCCCCCHHCCH";k++;
//    mapa[k] = "HHCCCCHCHHCCHCHCHCHCHHCHHCHHCCHHCCHHHCHHCHHCHHHHHHCHHHHHCCHHHHHCCCHHCHCCCCHCHCHCCHHCHHHHCHHCCHHCHCHCCCCCCCHHCHHHHHHHCCHHCHCCCCHHCCHHHCHHHCCC0CCHCHHHCC";k++;
//    mapa[k] = "HHHCCHHCCCHHCCCHHHCHHCHCHHCCHHHHHHCCCHCHCCCHHHCCCHHHCHCHHCHHHHCHCHCCCHHHHHHHHCCHHCHHHCCHHHHHHHCHHHHCHCCHHCCCHCHHHCCCCHCCHCCCCCHHHHCCHHHCCHHHHCCHCHHCHH";k++;
//    mapa[k] = "HCHCCHHHHHCCHHHCCCCCHHHHHHHCCCHHCCHHCHCCCHHCHCCHCHHHHHHCHHHCHCHHHHHHHHHHCHHCHCCCHHHCHCCCHCHCCHCHHHCCHHHCCHHHHHCHCHCHHHHHHHCHCHCCHHHCHCHCCHCCCHHCHCCHCH";k++;
//    mapa[k] = "CHCCHCHCCHCHCCHHHCCHHCCCHCCCHCCCHHHHHHHHHHHHCHHCCCHCCHCCCHCCHHHCCCC0HHHCCCHHHHHCHCCCHCCHHHH1HCCCHHHCCHCCCCCCHHCHHHCHCHHHHHHCCCHHCHCCHHCHHHHHCCHCCHHHHC";k++;
//    mapa[k] = "CCHHCCHCCHCCHHCHCCHCCHHHCHHHHCCHHCHCCCCHCCCCHCHCHHHHCCHCHCHHHHCHHCHHCHHHHHHCCHHHHCCHCHCCCCHHCCCHCHHHCHHCCHCCHCHCCCHCHCCHCHC0HCHHCCHCCHHHHHHHHHHCCCCCCC";k++;
//    mapa[k] = "HHCHCHCHCHHHHCHHCHCHHCCCHHHHCCCCHCHCHHCCCCCHCHCCHHCCHHPCHCCCHHCCHHHCCCCCHHCCCCHHHHHCHCHCCCHHHHCCHHCCHHCCHCHHHHHCCHCCCCHCCHCHCCCCCCCHHHHHHHCHCHHCHCHHHH";k++;
//    mapa[k] = "HHHHCHHHHHCHHHHCHCCCCHHHHHHHCHCH1CCHHCCHHCHHHHHCHCCHHHCHHCCCCHHHHCHCHHHHCHCHHCCHHCHHCCHHHCCHHCCHHHHHCHCHHHCHHCHHHCHHHCHHCCCHCCHCHHCHHCCCHHHHHHHCHCHCCH";k++;
//    mapa[k] = "HHHCCHCHHHHHHHHHHHHC0CCCHCCCHHCCHHCHHCHCHCCHCHHHCCCHCCCHHHCHCHCHCHCCHCHCCHCHHCHHCCHHHHCCHHCHHHHCHHCHHCHCHHCCCHHCHHCCHHCCHCHCHHCHHHHHHCHHHHCHCHCCHHHHHH";k++;
//    mapa[k] = "CCCHHHCCHHHHHHCHHCHHHHHCCHHHCCHCHCC0HCCHHCHCCCHHCHHHHCHHCCHCHHCHHHCCHCCHCCCHCHHCCHHHCCCHHCCCCHHHCHCCHHCCCCCCHHHHHCHCHHHHHCHCHCHCCHCCHHCHHCCHHCHCCCCHHH";k++;
//    mapa[k] = "HCHCHHCCHHCHHCCHHCHHCHHCCHCCHHCCHCHCHHCCHHCHCCHHCCHCCHCHCHCCHCCCHHHHHHHHHHHHCCCHCHHCCHHCCHHHCCHHHCHCCHCCCCH0HHHHCHCHHCHHHHHHCHCCHCCHCHCHHHHCHHCHHHCHHH";k++;
//    mapa[k] = "CCHHHCCHCHHCCHCHHHCCCCCCCHHHHCCCCHHHCCCHCHHHHHHHHHHCHHCHCHHHCCHCCHHHHHHHHHCHHCHHCCHHHCCCHHHHCHCCCHHHCHCHCHHCHCCCCCHHHCHCHCCHCHCHHHCCCCCHCCHHCCCHHHCHCH";k++;
//    mapa[k] = "HHCHHCHHCHCHHHHCHHHCCHHHCHHHHCCCHCCHCHHCHHCCHHCCHCCHHCCHHHHCHCHHHCCCCCCCCHCHHHHCHHHHHCHHCHHHCHHCCHCHHHHCHHCCCHHHHCHCCHHCHHCCHCCCCCHHCCHCHCHHCCCHHHHCCC";k++;
//    mapa[k] = "CHCHCHCHHCHCCHHHHHHHHHHHCHHHCHHHCCCHCCHCCHCCHCHHHCCHHHCHHHCHCCHHHHHHCHCCHHHCCCHHCHCHHHHHCCCHHHHCHHHHCHCHCCCHHCHHHHHCHCCHHHCHHHCCHHHHHHHCCCHCHHCHCHHHHH";k++;
//    mapa[k] = "HHCCHHHHCHCHHCHHCHHCCCCCCHHHHHCHHCHCHHHCHCCCCHHHHCCHCCCHCHHHCCCCHHHCCCCCCCHHHHHCHHCHHHHCHHHHCHCHHHCCCCCHCHHCCHHCHCHHCCCCHCHHHCHHHHHHCHCCHHCCCHHHHHHHHC";k++;
//    mapa[k] = "HCHHHHHCHHHHCHCHHHHCCHCHHCCHHCHHCHHHHHHHHHHCHHHHCHHHHCHCHCCHCCCCCHHCCHCHHCCCCCCCCHHHCHHHHCCCHCHHHCHHHCCCCHHHCHCCCHHHCHHCHHHCCCHHHHCCHCHHHHHCCCHHCHHHCH";k++;
//    mapa[k] = "HHHCHHHCCCHCCCHHHHCCCHCCHHHHHCCHHCHCCCHHHHCHHCHCCHCCHHCHHCCCCCCHHHHCHHCHCCHHCCHHHHCHCHHHHH0CCHCHCHHHCHCHCCCCHCHHCHCCHHHHHCHCCCHHCHHHHCCCHCHHHCCHHHCCHC";k++;
//    mapa[k] = "CCHHCHHCCCCHCHCHCCCCHCHCHHCHCHHHHCCCHHCHHHCHHHHCHHCCCHH1HCHHHCHCCCCHCHCHHCHHCCCHHCCCCHHHHHCHCHHHCCCHCCHHHHHHHCCCHCHHHCHHCCHCCHCHHH11CHHCHHCCCCCCCCHHC0";k++;
//    mapa[k] = "HHHCCHHCHHHHHHHCHCHHHCHHCHHCCHHHCHHHHHCHHCCCCCCHHH0HHHHCHHCHCHHCCCHHHHHCHHHHHCHHHCHHCHHCCCHHCHCCCCHCCHCHCHCHHHHHHHHHCHCCHHHCCCHHHCHCHCHHHCHCCHCCHHCCHC";k++;
//    mapa[k] = "CHCHCHHCCHHCHHCHHCCCHHCC1CHHHCCCHHHHCHCCHHHHHCHHHCCHHCCHHCHHHHHHHCCHHCCCHCHCHCHCCCCHCCCCHHHHCHHHHCCCCHHCCHCCCHCHHHHHCHHCCCCHHHHCHHHHHCCHCHHCHHCHCCCHCH";k++;
//    mapa[k] = "HHCCHHHCCCCHHCCCCHCCCCCCCCCHHHHHHHCCCHCCCHCCCHHHHHHHCHCHCHCCCCCHHHHHHCCHCCCCHCCHHHCCHHHHCHHCCCHHCCCHCCCCHHHCHCCHCHHCHCHHCHHHCHHCHCHHHCHCHCCCHCCHHCHHCH";k++;
//    mapa[k] = "HCHHCCCHHHHHCHHCCHHCCHHCHCCCHHHHHCHHHCCHHCHCHHHHCHCCHCCHHCHHHHHCCCCHCCHCHHHHCHCCCHHHCHCHCCPHHCHHCCHCCCCCCCCHHHHHCHHCHHCHHCCCCHHHHCHHCCCCHHHHHHHCHCHHCH";k++;
//    mapa[k] = "CCCHHCHHCCHHCHHCCCHCHHCHHHHH1HCHCCHCHCHCHHHCCCHHHHHCCCHCCHCCHHCCHCHCCHCHHCHCHCHCHHHCHHHHCHHHHHCCCCHCHHCHHHHHCHCCCCCHHHCCHCH0HHCHCCHCCCCHCCCCHHHHCCCCCC";k++;
//    mapa[k] = "HHHHCHHCHCHCCCCCCHCHHHCHCHHCHCCCHHCCCHHHHHHCCCCCCHCHCHHCHCHHHHHHCHHHCCHCCCCHCHCHHCCCCHHCHHHCHCHHHHCHCCCCHHHHHHCHCHHHHHHCCHHHCHHHCCCCCHCHCCCHCHHCCHHCHC";k++;
//    mapa[k] = "CCCCHHCCHHHHHHHCHCCCHHHCCHHHHHCCCCHCCCHHHHCHHCCCHHHHHHCHCCHCHCCCHCCHHCCCHHHHCCCHCCCHHHHCHHHHHHHCHHCCHCHHHHCHCCHCCCCHCHHHCCHHHCCCCHHCCHCHHHHHHCCHCHHCHH";k++;
//    mapa[k] = "HCCHHHCHHCHCHHCCHCHCCCHHHHHHCHCHHHHHCHCHHHCHHHCHHCHCHCHCHCHCHCCHHHCHCCCHHHHHHCHCHHHCCCCCHCHHHCHHHCHHCCHCHHHCCCCHHCHHHCCCHCCHCHHCHCCCCHHHHHCHHHCCHCCCHH";k++;
//    mapa[k] = "HHCHCCCHHHHCCHHHCCCCHCCHHHCCCCHHCCCHCHHHHCHCCCHHCCHCCCHCCHHCCHHHCCHCCHCHHHCCHHCHCHHCCCHHHCHHCCCCCCCHHHCHHHHCCHHHHCCCHHCCCHHCHHCHCHCHHHHHCCHCCCCCHCHCCH";k++;
//    mapa[k] = "CHCHHCCHHCHHCHCHCHHHCHCHCCCCHHCHHHCHCHHCCCHHCHCCCHCHHCHHHHCHHHHCHHCCHHCHHHHCHCCHCCCHHHHCCHHHCHCCCCHCCHHHCHHHHCHHHHCHCHCHHHHHCHCHCHHCHHHCHCHCHHHHCHHHHC";k++;
//    mapa[k] = "HHHHHHCHCHHHHHCHCHHCHCCCHCCHHHCHCHHHCHCGHHCHCCHHCHCHHCCHHHCCHHHHCHC1CHHCCCHHCCHCCHCHHHHCHHHHHHHHHHHHHHHHHHHHHHCHCCHCCHCCCCHCHHHCHHHHCCCCCHCHCCHHHCHHCH";k++;
//    mapa[k] = "HCHCHCCCHCHHCCHHCHCCHCHHHCHHHCHHCCHHHCCHHCH1HHCHCCCHHCHCCCHCHHHHCCHHHHHHCCHHHCHHHHCHCCHHCHCCCHHCCHCHHCCCHHCHCHHCHHHHCHHHHHCHHHHCCCHHCHC0HCCHHHHCHCHHHC";k++;
//    mapa[k] = "HCCHCHCHHHCHHHCHCCHHCCHHCCHHCCCCCHHHHHHCHHHHCHHCHCCHCHHHHHHHHHHHCHCCHCCHHHCCCCCCHCHHCCCCCHHHCHCCHCHCHCCHHHHHHCCHHCHHCHHCHHCCHCHCCHHCCCHHHHCHHHHCCCHHHC";k++;
//    mapa[k] = "HHCCCHHCHHCHHHHHCHCCCHHHHCCCHHHHHCCHCHHHCCHCHCHCHHHHHCHHCHHHHHCCHHHCHHHCHCHCHHCCHCHCHHHHHHCHCCHCHCHHHCCCCHHHCCHHHHHHHHHHCCHHCHCHCCCHCCCCHHCHCHCCCHCHHH";k++;
//    mapa[k] = "CCCHHCCCHHHHCCHHHCCCHHCHHHCHHHCCHHCCCHHHHCCHHCHCCHHHCHCCHCHHHHHHCHHCHCCHCCHHHHCCHHCHCHCCCHHCHHCHHHCHCCCCCHCCCHCCHHHHHHHHHCHCCHHCHHCHCCHHHHHHHHHCCCCHCH";k++;
//    mapa[k] = "HHHCHHHHHHCCHHCCHHHHHHHHHHHHHHHCHHCCHCHHHHHCCHHCHHHCCHHHHCCCCCCCCCCHCHHHHCHCHHCCCHCHCHHHCHCCCHCCCHHCHHCHCCHCHHCCHCCCHHCCHHCCHHHHHCHHHCHCHCCCHCHCCHHCHC";k++;
//    mapa[k] = "CHHHHHCHHHCCHHCHCCHCHHCHCHHHHCHHCHHHHHCHCCCHCCCHHCHHHHCHCCHHHHCHHHHHCHHHCHHHHHHHHHHHHHHHHCHCHCCCCHHHCHCHHHHHCHHHCHHCCCHHHHHHCHCHCHCHCHHCCHCHCCCHHCCCHH";k++;
//    mapa[k] = "CHHHCCCCCHHCCHHCHHHHCHHHHHHCHHHHCCHCHHCCCHHCHHHHCCCHHHHCCHCCCHCHHCHHHHCHCCHCHHCCCHHHHCHHHHCCHHHCHHHHHHHHHHCCCHCHHCCHHHHHHHHHHCHCHHCCCHHHHHHCCHCHHHCHCH";k++;
//    mapa[k] = "CCCHHHHHHCCCHCHHCHCHCHHHHCCHHHCCHCCHCCHCCHCCHHCHCCHHHHHHHHHHHCCHCHCHHCCHHHHCHHCCHCCCHHHHCCCCCCCHCCCCHCCHHCCHCHCCCCHHHHHHHHCHHCHCHHHCCHHCHHCHCHHHHHCCHC";k++;
//    mapa[k] = "CCHHHHCCCCCHHCHHCHCCCHHHHHHHHHCCCHCCHHHCHCCHCHHCCHCHHCCHHCCCHHHHHHHCHCCHCCCCCCCHHHHHHCCHHCHHCHCHHCCCHCHCCCCHHCCCCCHHCHHCCHCHCHCHHHCHHCHHCCCCCCHHHHHHCH";k++;
//    mapa[k] = "HHCCHHHCHHHHCCCHCCHCCHHCCHHCHHHCHHHCCHCHHCCHCHHHHCCCHHHCCCHHCHHHHCCHHHCHHCCHHCCC1HHHHHCCHHHHCHHCHCHHHCCHHCCHCCHCHCHCCHHHCCCHCCHCHCCCHHCHCHHCCHHCHHHHHH";k++;
//    mapa[k] = "HHHCHCHHCCHCCHHHHHCCHHHHHCHCCHCHCCHHHCCCHHCHCHCHHHHHCHHHHCHCHHHHHHCCCHHCCHHHCHHCCHHHCCCCHHCHCHCHHHCHCCHHHHHHHHCHHHHCHHHCCCHCCHHHCCCCHCCHCHCHCCCCCCCHHC";k++;
//    mapa[k] = "HCHCHHCHHHHCHHCCHCHCCHHHHHCHHHHHHHHHHCCHCHHCCHCHHCHHHHCHHHHHCHHHHCHHHCHHHCCCCHCHCCCCCHCCHHHHHHCHHCHCHCHHHHCHHHHHCCHHHHCCHHCHCHHHCCHHCHHHHHHHHCHCHHCHHC";k++;
//    mapa[k] = "HHHHCHHHCHCCHCCCCCCCHHHHHHCHHCCCHHCCHHHCHCHCHHHHHCHCHHHCHHHCHCHHHHCCCHHHHCCCHHCHHHCHHCCCHHCCHCHHCCCCHCCHHCHCHHHHCHCCCCHCCHHHCCCCCCHHHCCCHHHCHCCHCHHCCC";k++;
//    mapa[k] = "CHCCHHHHHHHHHCCHCHCHHHHCCHCHCCCCHHHHCCHCHCCHHCHHHHHHCHHCHHCCHHHHHHHCCCHHHCHCHHCHCCCHHCCHHCHHHCCHHCCHHCCCHCHHHCHCCHCCHHHCCHHHHCHCCCCHCCHHCHHHHCCCHHCCHC";k++;
//    mapa[k] = "HCHCCCHHCCHCHHHHCCHCCCHCHHH1HCHCCCCHCHHHHCHCCHHHHHHCHCCHHHHHHHCCHCHHHHCHCCHCCCHHCHCHCHCHHCCHHCHHHHCHHHHHCHHHCHCCCHHCHHHCHHHHHHHCHHHHCCHHHHCHHHHHCCCHHC";k++;
//    mapa[k] = "HCCCHCHHCCCHHHHHCCCHCCHHHHCCHHHHHCCCCHHHCCCHHCCHHHHCCHHHHHHHHCCHHHCCHHCHHCCCCCCHHHCCHHCHHHHCHCHHCHHCHHCHHHHCHCCHHCCHCHCHHHHHHHHHCCHCHCCHHHHHHHHHCHHCHC";k++;
//    mapa[k] = "CHCCCHCHHHHCHHCHHHHCHHHHHCHHCHCHCHCHCCHCHCHHCHHHHHCHCCCCHCHCHCHHHCCCCCHCCHCHHHHHCHCCCCCCHCHCCCCHCHHHHHHCHHHCHCCCHHHHHHCHHHHHHHCCHCCCCHCHCCHHHCHCCHCCHC";k++;
//    mapa[k] = "HHHCCCHHHCHHCCHCCHHHCHHCHHCCCCHCHCHCCHCHCCHCCHCHCHCHHHCHCHCHHHCHCCHCCCCHHHCCHCHHHHHHCCHHCHHHCCHHCHHCHCHHHHCCHHHHHHHHHCHHHHCHCHCHCCC2HHHHHCHCCHHCHCCCCH";k++;
//    mapa[k] = "CHHCHHCCHHCHCHCHHHHHCCCCCHCHCHHCCCHCHCHCHHHHHCHCHCCHHCHHCCHHCCCCHHHHHCHHHCCCCCHHHHCHHCHCHCHHHHHHHCHHCCHHHHCHCCCCHCHHHHCCHCHHCCCHCHHCHCCCCHHHCHCHHCHHHC";k++;
//    mapa[k] = "CCCCCHHCHHCCHCCCHCCHCCCHHCHHHHHCHHCHHHCHHCCHHCCCCHHCHCHHHHHCHHCCCHCHCCHHHCHHHCCHHCCHHHCCHHCHCHHCCHHCCHCCHHHCHCCHCHCCHHCHHHHHHHHHCHHHHHHHHHCCHCHHHHHCHH";k++;
//    mapa[k] = "CHCHCCHCCHHHHHCHHCHHHCHHCHHCHHHHHHHHCHCCCHHHCHHCCHCHHCHHCCCHHCHCHHCCCHCCHHHHHHCHCCHHHCCCCHHCCHCCCHHHHCCHHHCHHHCHHCHHCHHCHHHCHCHHHCHHHHHHHCHHCCCCCCHHHC";k++;
//    mapa[k] = "HHHCHHHHHCHHHCCCCHCHCCCCCCCCCHCHHHHHHHHHCCHCCCCCHCCCCHHCHHHHHCHCHHCCHCCCHCCHHHHCCHHHCCCHHHCHHCHCCCCCHHHHCCHCCHCHCHCCCHHCHHHHHCHHHHHHCCHHHCHCHHHHHCHHCH";k++;
//    mapa[k] = "HCCCCHHHCHHCHCHHCHCCCCHCHCHHHHCCCHHHCCHHHCHCHCHCHHHHHCHHHHCCCHHHHCHCCHCCHCCCH0HCCCCHHCHHHHHHHCHHHCHHCHHCHHCHHCCHCHHHCCCHHHHCCCCHHCHCHHCCHCCHHCCHCCHHHH";k++;
//    mapa[k] = "CHHHCHCHCHCCCCHHHCHCHCHCCHCHCHCHCHHCCCHCHHHCCCHHHHCHHCHHHHHHHHCHCCCHHCCHHHHHHCCHHHCCHHCHHHHHHCCCCCHHCHCHCHHCCCHCHHHHCHHHCHCCHCHHHHHHHCHCHCCCCCHHCHCCHH";k++;
//    mapa[k] = "HCHHHHHHCCCHHHCHHHHHHHHHHHHHHCCCCCHHHHCCHHCHHCHHCHHHCCCHHCHCHHHHHCHCCCHHCHHHHHCHHCCHCHCHHCCCHHCCCCCHHCHHHCCHCCHCCCCCHCCCCHHCHHCCHHHCCHCCHCCHCHHHHHCCHH";k++;
//    mapa[k] = "CHHCCHCHHCCHHHHHHHCHHCCCHHCCHCCHHCHHHHHHCHCHCCCHHCHCHCCHHCHHCHHHCHHCCCHHHHHHHHCHCHHCHCHHHCCHCHHHHHHHHHCHHHCCHCCCCCHHCHHCCHCCHHHCHCCCHCCHCCHCCCCCHCHHHC";k++;
//    mapa[k] = "HHHHCHCHCHHHHCHHHCCCCCCHHHHCHCHCHHCHCCCCHCHHCCHCCHCHHCCHHHCHCCHHHHHHCCHCCHHCCHHHHCHHHCHHCHCCHHHHHHHCCHHCCCCHHHHHHHCHHCHCHHHHHCCCHCHHHHHCHCHCHHHHHHCCHC";k++;
//    mapa[k] = "CCHHHHCCHHHCCCHCHCHCCHHHHCHHCCHHCHHCCHCCHCCCCCHHCCHHHCCHCHHHHHCCHCCCHHHHHCHCCCHCHCHHCCCHCCCHHHCHCHCCCCHCHCHHHCCHHCHCHHCCHCH0CHCCCCCCCCHHCHCHCCHCHHHHHH";k++;
//    mapa[k] = "HHHHCCCCHHCHCCCHHHHCHHHCHCCHCHHCCCCHHHCCHHCHCHHHCCCHHHCHCHHHCCCHHCHCHHCCHHHCCHCHCHCHHCCHCHHCHHCHHCCCHCCCCHCCCHHHCCHHCCHCHCHHCHHCHCHCHHCHHHCHCCHCHHHCHC";k++;
//    mapa[k] = "HCCCHCHHHHCHCHHCHCHCHCCHHHCCHHHCCHHHCHCCCCHCHCHCHHHCCHHCHCCHCHCHHHCCHCCCHCCCCHHCCCCHHHCHCCHHHHCHHHHHHHHHCCCHHHCHCCCCHCHHHHHCCCHCHCHCCHHCCHCHCCCHHHHCCH";k++;
//    mapa[k] = "HCHHHCHHCHHHCHHCCCCCHCCCHCCHCCCHHCCHHHCHCCCHCHHCHHCCHCCCCCHCHHCHHHHHHHCHC1CHCCCHHHHCCHHCHHHHHHCHCCHCHHHCCHHCCCHHHCCCCHCHHCCHHHCCCCCCCC0HCHCCHCHHCCCHCC";k++;
//    mapa[k] = "CHHCHHCHCCHHCHCHHCHCCCHCCHHHCHHCHHCCHCCHHCCCCCHCCCHHHHHHCCCHCCCHCCCHCCHCCHCHHHCHHHHHHHCHHCHHHHCCCHCHHCHHHHHHHHHCHCCHCCHHCCHCCCHCHCHHC0HCHHHHCHCHHHCCHH";k++;
//    mapa[k] = "HCCHCCHCHHHCHCHHCHHCCCCHHHHCHHCHHCCHHCCHCHCCHCCHCHHHCHCCHHCCHCHHHHHHCCHCHCHCCCCHHHCHHHCHCHCCCHHHCCCHCHCHHCHCCHHHHHCHHHHCHCHHHHCCHHCHHCCHCCHHHCHHHCHCHC";k++;
//    mapa[k] = "CHHHCCHCCCHCHCHCHCHHHHHHHHCHCCCHHHCCHCHHCCHCHCHHHCHCHHHCHCHHHHCHHCHCHHHHHHHCCHCH1CCCCCCHHHCHCCHHCHHCCCHCCCCHCCHCHCCCHHHHHHCHHHHCCHHCHHHCHCHHCHCHHCHCHH";k++;
//    mapa[k] = "HHHCCHHHHCHHHHHCHCHHHHHHCHCHCCCCCHHCHCCHHHHHHCCCCCCHHCCHHCCHHCCCHCHHCCCCHCHHHHHCHHHCCHHHCCHCCHHCHCCHHCCCCCHCCHCHHHCCHCCHCHCHHCCCCCCCCHHHHCCHHHHHHHHHHH";k++;
//    mapa[k] = "HCHCCHCCCHCHCHHHCCCCHCHHHCCHCHHHHHHCCCHCCHHCCHCHCHCCHHCCCCCHCHHHHHHCHHHCHHHHCHCHHCCHHCHHHHHHCCHHHHHCCHHHCCHHHHCCCCHHHCCHCCHHHCHHHCCHHCCHCHHCHCCCHCCHCC";k++;
//    mapa[k] = "HCCHCCHHCCCCCHCHHCCCHCCCHCCHCCHHHHCHCCHHCHHHHHCHHHCHCHHHHCCHCCCHHHHHHHCHCHCCCCHHHCCHCHHCCHCCCCHCCCCCCCCCHHCHCCHCHCHCHCHHCCHHHHCCCCHCCHCHCHCCHCCCCCCHHC";k++;
//    mapa[k] = "HHCCHHCHHHHCHHHCCCHHCCCCCHCHHCCCHHHHCHHHHHCHCCCHCHHCCHHCHHHCHHCCHHHCHHCCCCCHHHCHCHCHCCCCCCHHHCHHHCCCHHCHHHHCHCHHCCHHHCHCCCCCCHHHHHCHHCHHHHHHHCCCCHCHHH";k++;
//    mapa[k] = "HCHHHHHHHHHHHHHHCCHHHHHHHCCCHCCHCCCHHCCHHCHHCCHHHHHHCCCCCCHCHHHHHHCHCCHCHHCCHHHHHHHCH1HHHHHHCHCCCHCHHCCCHCHHCCHCCCCHCCCHCHHCHCHCHCCHCHCCCCHCCHHHHCHHHC";k++;
//    mapa[k] = "HHCCHCHHHCCHHHCCCHCHHHHHHHCHCCCHHHHCHHCCHHHHCHHCCHHCHHHHHHHHCCHHCCHCHHCHCCHCHHHHCHHCHHHHHHHCHCCHCCCHHHCCHHHCHHCHHHHCHCHHHHCHHHHHHHCHCHCHHCHHCHHHCCCHHC";k++;
//    mapa[k] = "HCHHCHHHHCHHCHHHCCCHCHCCCHCHHCCHCCCHCHCHCCCHHHCHCCCCHHCHCHHHCCCCCCCHCHCHHHCHHCCHHHHCHHCCHCHHCHHCHCHHCCHHCHHHHCHCCHHHHHHCHCCCHCCCHHHCCCCHCCCCCCHHHHCHCH";k++;
//    mapa[k] = "CCHCHCCCHCHCHCHHCCHCHHCCHHHHCHHCCCHHHCCHCCHHCCCHHHHHHHHCHHC0HHCCCHHHCHHHCHHHHHHHCHHC0HCCHHCCHHHHHHHCHHHCCHCHHCHHHCHHHHCHCHCCHHHHHHCCHHCHHCCCHCHHHHCCHC";k++;
//    mapa[k] = "HHHCHHHCHCHHHCCHHHHHHHHCHHCHHHHHHHHHHCHHHHHCHHCCHCCHCHCHHCCHHCCHHHHHHHCCHCHHHHHCHHCCHCCHHCCHHCHCHHHHCCCCHHHCCHCCHCHCHCHHHCCHCHCCHHHCCHHCCCHHCHCHCHHCHC";k++;
//    mapa[k] = "HHHHHCHCHHCCCCCHCCHHHHHHHHHHCHCCHHCCCCCHHCHHHHCHHHHHCCCHCHHHCCHCCCHCCHHHHHCCHCHHHCHCHHCCCHCHCCCHCCCHHHHHHCCCHCHCHHHHCHHCHCHHCCHHHHCCHCHCHHHHCHHHHCCCCH";k++;
//    mapa[k] = "CHCHHHCHHHHCHCCHHCHHHHHHHHCCCHHHHHHCHHCCCHHCCCCHCHCHCHHCHCHCHCCCCHHCHHHHHHCHCCHHHHCHCHHHHCHHCCCCHHCCCHHCHCHHHHHCHHHHHHHHHCCHCCHHCCHCCCHCHHHHHHHCHCHHCH";k++;
//    mapa[k] = "CHHHCHHHCHCHCCCCHHHHCHHCCHHCCHHCCCCCCHHHHCCCHHCHHCHHHHCCCHCHHCCCCHHHHHCCCHHCCHCHCCHCCCCHHHCHHHCHHHCHHCHHCCHHCCHCHCHCCCCCCHCHHHCCHHCHHHHCCHCHCCHHHHHCCC";k++;
//    mapa[k] = "CCCHHCHCCHHCCHHHCCCHCHCHHCHCHHHHCHHHHCHHCHHCCCCCCHCHCHHCHHCCHCHHHHHHHHHHCHHCHHCHHHHCHCHCCCHHCHHCCHHHHHCHHHCHHHCCHH2CCCHCCCHHCCHCHHHHHHHCHCCHCHCHCCHHHH";k++;
//    mapa[k] = "HCHHHHCCH0HCCHCHHCHHHHHHHHHHCCHCCCHHCCHCHHHHHHHHHHHHCHCHHCHHHCCCCHHHCCHHHHHCHHHCHCHCCHCHHCHHHCCHCHHCCHCHCHHCHCHCCCHCHHHHCHHCHHHHHHCHCHHHCCCCCHHHCCCHHH";k++;
//    mapa[k] = "CCHCCCHHHCCCCCHHHHCCHHHHHHCHHHCHCHHHHHCHHHHHHCCHCCCCHCCCHCHCCHHHCHCHHHHCCCHCCCCHCCCCCHCHCCHHHHH1HHHCHHCHHCHCHCCCCHHHHHHCHHHHHCHCHHHHCCCCCHHHHCCHCHHHHC";k++;
//    mapa[k] = "HCCCCHCHHCCCHHCCCHCCHHHHHHCHHHCHHHHCHHHCCHHHCCCHHHHCCCCHHCHCCHCHHHCCCCHHCCHCCCHHCHCCCCHCHCCCHCCHHCCHCCHHHHCHHHCCHHHHHHCHHCCHHCCCHCCHHCCCCHHHHCCHHHHHHC";k++;
//    mapa[k] = "HHHHHHCHCCCCCHCHHHCHCCCHHHHHHHCCCCHHCCHCHHHHCCCHCHCHCCHCHHCCHHCHHHHHHCCCCHCCHCHCHHHCCHCCCCCCCHHCHCCHHHHHHHHCCHCHCHCCHCCHHHHCCCCCHCCHCHCCCCHCHCHHHCHHHH";k++;
//    mapa[k] = "HCHCCCCHHHCHCCHHHHHCHHHCHCCCCHHHHC1CCHCCCHCCHCCHHCCCHHHHHHHCHHHHHHCCCCHHCCCHHCHHCCCHCCHHHHCHCHHHHHHCCHHHHCCHCHHCHHHHCCHCCHHHHHCCHHHHHHCHCHCHHCHHHHHHHC";k++;
//    mapa[k] = "HCHHHHCHCCHHHCHCHHCCHHHCCHCHHHHHHHHHCHCHCCCCCHHHCCCCCHCHHCHHHHCHHHCCCHCHCCHCCCHHCHCCCHCHCCHHCHHHCHHHCHCCCHCHCHHCHHHCHCCHCCHCCHHCHCHCHCCHCCHCHHHHCHHCHC";k++;
//    mapa[k] = "HCHCHHHHHCHCCHHHCCCHHCCCHHHCHCHHHCHCHHHCCCHHHCHHHHHCHHHHHCHCHCCHCHCCHCCCHCHCHHHCCCHHCHHHCHHCHHHCCHCCHHCHHHCHCHCHHHHHHCCHHCHHHCCHHCHHHCCCHHHCCHHHHCHCHC";k++;
//    mapa[k] = "CCHHHHCHCHHCHHHCCCCCHHHCCHCHHHCHHCHCCHCHHCHHHHHHHHCHCHHHHHHHCHHHCCHHHCCCCHHHHHHCHHCCCCHHCCHCHCHHHCCHHHCHCCHHCCCCCHHCHCCHCCCHCCCCHCCCHHHHCCHCCHCHHHHHCC";k++;
//    mapa[k] = "CHHHCHHCCCHCHHHCHCHHCHHCCCHHHCHHHHHCHCCCCHHCHHHHCHHCCCHHCHHHHHCCHCHCCCCHHHHHHCHHCHHCHCCCCCHCHHCCHCHHHCHCHCCCCH1HCCCHCHCHHCHHHHHHCHCCHCHCCHCHCCHCHHCCCH";k++;
//    mapa[k] = "HHCHCHCHCCHCCHCCCHHHCHHHCHHCHCHCHHHCCHHCCCHCHHCHCHHHCCHCHCCHHHHCHCCHHHCHHHCHCHHHHCHCCHHCCHHHHCCHCHHCHCHHCCCCHCHHCHHCCCCCHCCCHHHHHCCCHHCHCHCHCCHCHHHHHC";k++;
//    mapa[k] = "HCCCHHHHHCHHCCCHHCCHHCHCHHHHHCHHHHCHCCHCHHCCCCHHCCCCCHCHCHHCCCCCCHCHCCHHCHHCHHHCCCCHHHHHCHCHCCHCHHHCHHHCCCHCHHHHHHHHHCCCCHHHCHCHCHHCHHCHCHCHHHCHCHCHCH";k++;
//    mapa[k] = "HCHCCHHHHCCCHCCHCHHCHCCCCHHCCHHHHHCCHCHCHCCHCHCCHCCHCHCHHHCHCHHCCHHHCCCCHHHCHCHCHHHCHCHHHCHHHHHHHCHCCHCHHHHHHCHHCCHHHCHHCHHCHCHHHHHHHCHCHCHCHCCCHHCHCC";k++;
//    mapa[k] = "HCHHHHH1CHHCCHHCHHCHCCCHHCCCCCCHHHHHHHCCCHHHHHCHCHCCHCHHHCHCHHHCCHHCCHHHCHHHCCCCCHHCHHCCCHHHCHCHHCHHCHHHHCHHHCCHHCHCCHHHCCHCHCCHHHHCHHCHHHCHHHHHHHHHCH";k++;
//    mapa[k] = "HCHCCHHHCHHHHCHHHHHCHCHHCHHCHHCHCCCHCHHHHCCCHCCHHHHHHHCHCHCCHHHHCCHCHCHHHCHCCCCHCHCCHCHHCHHCHHHHHCHHHHHCHCHCCHHHCHCHCHCCCCHHCCCCHCCCHHHHHCHHCHCHCHHHCC";k++;
//    mapa[k] = "HHHHHHCCCHHHCHHHHHCCHHHHCCCHHHHCHHCHHHCCCHHCHHHHHCHHCHCCHHCHHHCCCCCHHHHCHHHHHHHCHHCCHCCCHHHHHHCHHCHHCCHCCHCHHHHHCCCHHHCCCCCHHHHHHCCHHHCHHHHCHHHHHHCHCC";k++;
//    mapa[k] = "CCHCHHCHHCHCHCHCHHHHCHCCHHHHHHHHCHHHHHHCCCCCCHCHHCHHCHCHHHHHHHHHCCCCHHHHHHCHHCCHHHHCHHHCCHCHCCCHCCCCCHHCHHHCHHCCCHHHCHHCHCCCHCCHHHCCHHCHHCHHHCHCHCHCCC";k++;
//    mapa[k] = "CHCCHHHCHCHCHCCCCHHHHCHCHHCHHHCCHHCCCCHCHCHCCHHCCCHHHHCHCCCHHHHCCCCCCHHHCHHHHHHHHCHCHHHHHCCHCCHCHHCHHHHHHHCHHCHCHHCCCCCCCHHHHHHCHHCHHHCCCHCCHCHHHCCHHC";k++;
//    mapa[k] = "CHHCCCHHHHHHCHH0HHCHCHCHCHHCHHHCCCHHCCCHHHCH1HHHCHHHHCHCHHHHCHCHHHCHCHHHCCCHHHCHHCCHCCHHHHHHHCCHCHHHCHHCHCHCCHHCCCHCHHHHCHHCCHCCHHHCHCHHHHCHHHCCCCCHCH";k++;
//    mapa[k] = "CCCCHCHCCHHHHHHCCCCHCCCHHCHCHCHCHCHHCHCHCCCHCCHHCHCHHHCCHCHHHHCCHHHCCHHHCHCHHCCHHHHCCCHCCHHCCHCHHCHHCHCHHHHHHCHHCHHHHCCCHHHHHHCHCCHCHCHHCHHHHHHCHCHCCC";k++;
//    mapa[k] = "CCCHHHHCHCHCHCHHCHHHCHHCHCCHHCHHCHHCHHCCHHCHHCHCHHHHHHHCCHHHHHHHHCCCHHCHCCCHHCCHCHHHCCHHHHHCHCCHHCHHHHHHCCHHCHCCHCHCHHHHHHHCHHHCCCCHCHHHHCHHCHCHHCHCCH";k++;
//    mapa[k] = "HCHHH0CCHCCCHHHCCCHCCHHHCHCHCHHCCHCCHCHHCHHCCCCCCCCCCHHCCCCCCHHCCCCHHCHCCHHHHHCHHHCHCHHCHCCHHCHCHHHHHCHCHHCCHHCHHHHHHCCCCHCHCHCCHCHHHHCHCHHCCHHHHHCHCH";k++;
//    mapa[k] = "HHHHHHCCHHCHCHHCCHHHHHCCHHHH1CHCHHCCHCCHHHHHHCHHCCCCHCHHCCHHHHCCCHHHCHHHCHHCHCHCCCHHCCCCHHCCHCCHCHHHHHHHHCHHHHHHHHHCCCHCCHHHHHHHHCHHCHCCHHHHHCCCHHCCCH";k++;
//    mapa[k] = "HCHCCHCCHHHHHHCCCCHCCCHCCHHHCHCHHCHHCHHCHHCHCHCCHHCCCCCCCCCHCCHHCCCCHHHCCCCCHCHCCCHCCHCHHCHCCCHCHHCHCHCHHCCHHCHCHCCCHHHHHHHHHHHHHCCCHHCHHHHHCCHHCCCHHH";k++;
//    mapa[k] = "CCCHCCCHHHHHHCHHCHHCCHCHCHHHHHHHHCHCCCCHHCHHHHHHHCHCHHHHHCHHHHCHHCHCHHCHHHHCCHHHCHHHCCHCHHCHHCHHCHCCC1HCCCHHCHHCHHCHHCHCH0CHHCHHHHHCCHHHCHHHCCCHCHCCCC";k++;
//    mapa[k] = "CCCHHCCCCHCHHCCHHHCHHHHHCHHHCCHCCCCCHHCHCHCCCHHHHCHHHCCCCCHHHHCHCHHHHHHCHCHHHHHCCCCCHHHHCHHHCHCHHCHHCCHCHHCHHHHHCHHHCHHCHCCHHHCCHHHHHHHCHHHHCCCHCHHHHC";k++;
//    mapa[k] = "CHHHHHHCHCCCHHHCHCCHHHCCHHCHCHCCCHCHHHCCHHHHCHHCCHHHCHHHCHCCCHCHHHHHCHHHHCHHCHCCCHHHCCCCHCCCCCHHCCCHHHHCHHCHCHCCHCHCCHHHCCHHCHHHCHHHCCHHHHHHCCHCCCHHCH";k++;
//    mapa[k] = "HHCCHHHCHHHHHHCCHCHCHHHCHHHCHCHHCHHCCHCHCHHHCCCHCHHHHHCCHHHHHCHHHHHHCHHHCHHCCCCCCHHHCHHHCCHCHCCHHHHHCHHHHHCHHHHHHHHHHHHHHHHHHHHHHHHHCCHHHHCCCHCCHHHHHH";k++;
//    mapa[k] = "HCHCCCHCCHCHCHHHCHCHHCHHCCHHHCCHCHHCCHCHCCCHHHHHCCHHHHHCHCCCCHHHHHCHCCHCCHCHCCHCCHHHCCHCHCHHHCHCHCHHHCCCHHHHHHCHHCHHCHCCHHCCHCHCHHHHCHCCHCCHHHHCHHHHHC";k++;
//    mapa[k] = "HHCHHCCHHHHCCCCCHCHCHHHHHHHCHHHHCHCHCCHHHHHHCHCCCCHCCCCHCCHHCHHCCHHCCHHHHHHHHHHHCCHCCHHHHCHHCCCHCHHHHCCCHCHHHCHHCHHCHCCCHHCCCCHHHHCCHCHCHCH0CHCHH1CCCC";k++;
//    mapa[k] = "HHCCCCHHHHHHHHHHHHCCHHHHHHHCHHHCHCHCCCCCH1HHHHCHCHHHHCCHHCHCHCHHCHHCCHHCCCCCCCHHCCHHHCHHCCCHCCHCHHHHCHHCCHCHCHCHCCHHCHHHHCCHHHHHHHHHHHHHHHCHHCCHHCHCCC";k++;
//    mapa[k] = "CHHHCHHHCCHHCCCHHCCHCHCHHHCHHHHCCHCHHHHHHCHHHCCCHHHCHHCHHHHCHCCHCHHHHCCHCH2CCHHCHHHCHHHHHCHHHHHHHHCHHCCHCHHCHHHCCHHCHHHHCHHHCCHCHHHCHCCHHHHHCCHCCHCHHH";k++;
//    mapa[k] = "CCHCCHCCHCHCCCHCHCHCHCHHHCCHCCHHCCHHHCHHHCHCHCHCHCHHCHCCCCCCCCCCHHCHCHCCCCHHCDHHHHCHCHCHCHCHHCCHHHHCCHCHHCHHHCHHCHCCCHCHCCHCHCCCHCCCCHHHHHCHCHCHHHCHHC";k++;
//    mapa[k] = "CCHHHHHCCHCCCCCCHHCHHHCHHHHCHHCHHHCCCCHCHHHHCCHHHHCHCCHCCCCHHHHHHHHHCCHHHCHCCHHHCHHCHHCHCCCHHHCHHHHHCCHCCHHCHHCHCHHHCHCCHHHHHCHHHHHCHHCCCHHHHCHHCHHHHH";k++;
//    mapa[k] = "HHHCHHCCHCCHHHCHHHHHHCCCHCHCCHHCCHHHCHHCCCCCCHCHHCHHHCCHHHHHHHCHCCCCHCCCHCHHHHHCHCCCHHHHCCHHHHCCCHCHCCHCCHHHCHCHHHHHCCHHHCCHHCCCHHHHCHCHHHCHHHHHCHHHHH";k++;
//    mapa[k] = "HHCHHCHHCHCHHHCHCHHHCHHHCCCHHCCCCCCCCHCCCCCCCCHHHCHCHHHCHHCCCCHCHHCHCHCHCHHHCHHCCHHCHHHPHCHHCCCHHCCCCCHHHHCHHCCHCCCCCHHHHCCHCHCHHHCCCCHCHHHCHCCCCHCCHC";k++;
//    mapa[k] = "CCCCCCHCCCHHHHHCCHHHCHCHHHCHHHCCCHHHHCHCHHHCCHCCHHCHHCHHHHHHHCHHCCHCCCHHHCCCHCCCHHHHCHCCHHHHCHCCHHHHHHHHCHCHHHHHCHHCCCHCHHCHHHCHHCHHHHHCCHHHCHCHCCCHCH";k++;
//    mapa[k] = "C0CHHHCCCCCHCHHHHHHHCHHHHCCHCHHCHCHHCHCHCCCHHCHHHHCHHHCCCHHHHCHHHCHHHHHHCHHCCHHHHCCHCHCHCHHCHCCHCHHHCHCHHCHHHHHHHCHHHHCCHCHHHCCCHCHHCHHHHHCCCCHHHHHHCH";k++;
//    mapa[k] = "CHCCHHCCHHCCHCCHHCHHHHHCHCCCHHHHCHCCHCHCCCHHHCHHHCHHCCHHHCHHHHHHHCCHHCCCCCHCCCHHCHCCCCCCHHHHHCHCHHCHHHHHHHCCCCCCCHCHHHHHHCHHCCHHCHCCCHCHHHHCHHCHHCCHHC";k++;
//    mapa[k] = "HHHHHHCHHCHCCCHCCHHCCHCHCCCHHCCHHCCHCCCHCHCHHHCHCHHHHHHHHCC1HCCHCHHHCHHHHHCHCHHHCHHHCCCHHCHHCCCCHCCCCCHHHCCHCHCHHCCHCHCCHHHCHHHCCHHCHHCHCHCCHCHHHCCCCH";k++;
//    mapa[k] = "HCHHCHHHHHHHCCCHHHHCHHHHHHCCHHCHHHHHHCHHCHHCHCHHHCCHCHCHHCCHHHCHHCHCCHCCHCHHHCCHCHHHHCHCCHCCHHHHHHHHHHHHHCHHHCCHHHCHCCCHHCCHHHCHCHHCHCHCCHHCHHCCCHCCCH";k++;
//    mapa[k] = "HHHCCHCHHCHCHHCHCCHCCCHHHHCHHHHCCHHHCHCHCCHHCCHCHCHCCCCCCHHCHHHCCCHCCHHCCCHHHCHCCHHHHHHCCCHHHHCHHCCCCCCHHHHHHCHHHCHCCHHHHHCCCCCHCHHCCCHCCHHCHCCHHHCCCH";k++;
//    mapa[k] = "CHHHCCCHCHCHCCHCHCCHHCHCCCHHCCHCCCHHHHCHHHHCHCHHCHHHHHCHHCHHCCHCCHHCHCHCCHCCHHHCCCCHHCHCCHHHCCCHCHHCHHHHCHCHHHHHCCHHCHHHHH0HHHCCCHHCHCCCCCHHCHCCCCHCHH";k++;
//    mapa[k] = "CCHCCHHHHCHHCHCHHHCHHHHHCHCHCHHCCCHHHHCHHHCCHCHCCHHHHHCHCCHCCHHHCCHHHHCHHHHCCHCCHCHCCCHHHHHCHHHCCHCCCHCCHHHCHHHHCHHCHCHHCCHHHHCCCHCHCCCHHHCCHHCHHHCCHC";k++;
//    mapa[k] = "HHHHCHHHHHHHH0CHHHHCHCCHCCCHHHCHCCCHHHHCCHHHHHCHCHHHHCCHHHHHHCCHHHHHHHCHCCHHCCHHHHHCHHHHCHHCCHHCHHHHHCHHHCHHCHCCHHCHHCCCHCCHHHHHCHHHCCCCCHCHHHCCCHHHCH";k++;
//    mapa[k] = "CHCCCHHHHCHCHHCCHCCHHHCHHHHHHHHHHCCHHHCHHHHCCHHHCCHCCCHHHHCHHCHHCCHHCHHHCHCHCHHCHHCHCHHCHHHCHHHCCHHHCHHCCCCCHCHCHHHHCCHHCHCHHHHCHHCCHHCCHHHHCCHHCHCHHH";k++;
//    mapa[k] = "CHHHCHCHHCCHCHCCCCCCHHHCHHHCHHHCHHHCHCCHCHHCHCHHHCCHCHHCCCHCHHHHHHHHCCHHHCCHHHCHHHCCCHCCCCHCCHHCHHHHCHHHHHHCHCHCCHHCHCCCHHH0CCCHCCCHHCCHCHHCHHHHCHHHHC";k++;
//    mapa[k] = "CHHCHHHCHHCCCHHHCCCHHCHCCHCCHHCHCCHCCCCHCCCCHHCCHCCHHCCHHCHHHHHCCCCCHHCHCCCHCHHHCHHCCHCCHHHHCHCHHCCHCCCCHCCHCHCCHCHHCHCHCHHHHHHHHCHCHHHCCHC0HHCHCHHHCH";k++;
//    mapa[k] = "HHHHHCCHHCHHHCHHHCCHHCHCHHHHCHHCCHHCHCCCHHHCHHHCCHCHHHHCCHHCHCHHHCHCHHCHHHHCHCCCHHCCCCHCCCCCCHCCCHCCCCHCCHCCCCHCHHHHCHCHHHHCHCHCHHCHCHHHCCCHCHHCCCCCHC";k++;
//    mapa[k] = "CCHCHCHCHHHCCCCCHHHHHCCHCHHCHHHHHHCCHHHHHCCCHHCHCHHCHCHHHCHHCHHHHCHHHHHCHHHCHCCHCCHCHCHHHCHHCHCC1HCCHHHHHCHHHCHCHHCCCHCCHCHCCHHCCHCCHHHCHHCCCHHCHHHHCC";k++;
//    mapa[k] = "HHHCHCHHHHHCHHCHCHCHCCHCHCHHCCHCCCCCCHHCCHHCHCHCCHHHCCHHHCHCHCHHCCHHHHHCCCHCCHCHHHHCHHCHHHHHHCCCCHHCCCCHHCCCHHCHCHCHHHCCHCCHCCCHCCCCHHHHHHCCCHHHCCHCHH";k++;
//    mapa[k] = "HHHHHCHHHHCCHHCHCCHCCH1HHCHHCCCHCHCHHCHCHCCHCCHHCCHHCCCHCHCHHHHHCHCCHHHCHHCCCHCCHCCCHCHHCHCHCHHCCCHHCCHHHCCCCHCCHHHCHHHHHHHHCCCHHHCCHCCHHCCHCCHCHHCCHH";k++;
//    mapa[k] = "HHCHCHHCHCCCCCHHHCCHCHHCHHCHCHHHHCHH0CHCCCHCCHHHCCHHHHHCHHHHHCHCCHHCHCCHHCHCHCCCHHCHHCHC1HCHCHHCCHHCCCHCHHHHCHCCCHHCCHCCHHHHCHHHHHHCCCHHCHCHHCHCHHHCHH";k++;
//    mapa[k] = "HCHCCHHHCCHCHCCCCCHCHHHCCCHCCCCCHCCHHCCCCCHHCHHCHCHHCCCHCHHCCCCHHCHCCHHHCCHHCCCHCHCHHHCHCHHHCHHHHHHHHCCHCHHHHCHHHHCHCCCCHHCHCCCCCHHCCCHHHHHHCHHHCCCHHH";k++;
//    mapa[k] = "CHCHHHHCHHCHHCHCCCHCCCHCHHHCHCHCHHHHHHCHCHHHCCHHHCHCCHCHHHCHCCHCCCHCHCHCCHCCHHHHHHHHHCHHHHHHCHHHHHHHCHHHHCHCHCHHHCCHHHCHHCCHHHCHCHHCHCHHHCHHHHHCCCHHHC";k++;
//    mapa[k] = "HCCCHCCHCHHHHHCCCHHHCHHHCCCCCHCCHHHCHCHHCCCCHHCCHCCHHHHHHHCCHHCCHHHCCCHCCHHHHHCHHCHHHHHCCHHCCCCHCHHCHHHHCHHHHCHHCHCHHHHHHCCHCCCHHHHHCCHCCHHCHHHHHCHHCC";k++;
//    mapa[k] = "HCHHHHCH1HCHCCHCCHHCHHCCHHCCHHHHHHHHCCHCCCHHCHCCHHHCHHHHCHHHCCCCCHCHCHCCHCHHHHHHCHCCHHCHCHHHHCHCCHHHHCCCHCCCHCHCCCCHHHHHCHCCHCHHCHHHCCHHHHHCCCHHHHHCHH";k++;
//    mapa[k] = "HCCHHHHCHCHCCCHHHCHCHCCHHHHHCHCHCHHHCHCHHHHHCCHHHHHHCHCHCHHHHHHHCHCHCHCCCCHCHHCHHHHHHHHCHHHCHHHCHHHHHHCHCCCHHHHHHHHHCCHHHHHCCHHCHHCCCHCHHCHHHHHHCHCHHH";k++;
//    mapa[k] = "HHCCHHCHHHCHCHCHHHHHHHCCHHCCCHCCHHCCCHHHHCCCHHCCCCCCCCHHHCHCHHHHCHHCHCHCHHHHCHHCCHHCHHHCCHHCCCHHHHCCCCHHCCHHHCHCCHHHHHHHCCCCHCHHCHCHHHCHCHCHHCCHCHHHCH";k++;
//    mapa[k] = "CHHHCHHHHHHCHHHH1HHHHHHCCHCCHHHCHHCCHHCHHCCCCHHCHHCCCHCCCHHCHCHCHCCCCCHHHCHCCHHHCCHHHHHCHHCHCHCHCHCCCHCCHCCHHCCCCCCHCHHCHCHHHHHHHCCCHHCCHHCCCHHHHHCCCC";k++;
//    mapa[k] = "HHCCHHHCCCCHHHCCCCCCHCHHHCHHCCHCHHCHHHHHHHHHHHCHCCHCHCCHHHCHCHCCHHCCHHHCCHHHHCCHHHCHCCCHHCHHHCHHHHCCHHCHCHCCHCCCHHHCCCHHHCHHHHCHHCHCCCHHCCCCHHHHHHCHHH";k++;
//    mapa[k] = "HCHCCCHCHHHHHHHHHHHCCHCCCCHHCHCHCHHHHHHCCHHHHCHCCCCHHHCHCHCHHHHHHCHCCHHHHHCCHHHCCHCHHHCHHHCCHHCHCCHHHCHHCHHHHCCHHCCCCC0CHHCHCHCHHCHCCHHHHCCHHCHHHCHCHH";k++;
//    mapa[k] = "CCCCHCHCCCCHCCHCCHHCHHHCHCCHHCCCCCCHCHHHHHHHCHCHHCCCCHHCHCHCCHHHCHHCCCCHCHHHHHHHHHHHCCCHCHHHHHHHCCCHHHHHCCHHCHCCHHHHCCHCHCCCHHCHCHCHHCCCHCCHHHHCCCHCCC";k++;
//    mapa[k] = "CHHHCHCCHHCHHCHCCCHHCCCHHHHHCHHHHCCHCHHHCHCCHCHHHCHCHCCCCCHCCCHCCHHHCHHCHCCCHHHHHCCHHCCHCCCHCCCHCCHHCCCHCHCHHHHHCCCHHCHHHHCCHCHHHHHCCCHHCHCCCCHCCHCCHC";k++;
//    mapa[k] = "HCCCHHCHCHCCHCCCCHCCCCCCCHCCHCHHCHCHHHHHCHHCCHCCHCHHHHHHHHCHCCCHHHHHCCHHHHHHHCHHCCHHHCHHHCHHHHHHCCHHHHCCHCHCCHHCHHCCHHHHHCHHCCCHCHHHHHHCCCHHHHCHHCCHHH";k++;
//    mapa[k] = "HCHCCHCHCCCHHHHCCCCHCHCHCCHHHCHHCHHCH0HCHCHHCCHCHCHCCHHCHHHHCHHCHCCHCHHHHHCCCHCCHHCCHHHCCHHHCHCCHCHCHCHHCCCHHCHCCHHHHHHCCCCCHCHHCHCHCCCCCCCCCCCHHHHCHH";k++;
//    mapa[k] = "CHCCCHHHHCCHHCCHCHHCCHHHHHCHHHHCCHCCHCCCCHCHHHHHHCHHCHCHHCHCCCHHCCHCHCHCHCCHHHCCHCCHHCHCCCCHCCCHHHHHCCHCCCHCCHCHHHCCCCCHHCCCCHHHCCHHCCCHHHCHHCHHHHCHHH";k++;
//    mapa[k] = "HHHHCHHHHHCHHHCCCHCHCCHHHCHHCHHCHHHHHCHHHCHCHCHCCHHHCCHHCCHCHHHHHCCCCHCCHHCHHHHHHHCHHHHHHCHHHCHCCCCCCCCCCHCCHHHCHHHHCCHHCHCHHCHCCHHCHHHHCCCHHCCHCHCHHC";k++;
//    mapa[k] = "CCHHHHCCHHHHHCCHCHCHCHHCHHHHHHHHCCCHCHCCHHHHCCCHHCHHHHHHHHHCHCHCHHCHHHHCCCCHCCHCCHHHHHHCHCHHCCCHCCCCCCHHHCHHHHHHHHHCHCHHCCCCCHCHHCCCHCCHHHCCHHCC0HHCHH";k++;
//    mapa[k] = "HHCHHCHHCCCHHCHHCHCHCHHCCHHHHCHHCHHCCHHCHCHCCHCHHHCHHCHHCHCHHCHHHHHHCHHHCHHHCCHCHHHCCCHHHCCCHCCHHCCHHHHCCCCHCHCHHHHCHCCHHHHCCHHCHHHCHHCCHHCCCHCHCHCCCC";k++;
//
//
//
//    //    printf("\n");
//    //    printf("\n --0---1---2---3---4---5---6---7---8---9--10--11--12--13--14--15--16--17--18--19--\n");
//    //    for(i=0;i<n;i++){
//    //        printf("%d",i);
//    //        for(j=0;j<m;j++){
//    //            printf("| %c ",mapa[i][j]);
//    //        }
//    //        printf("|\n ----------------------------------------------------------------------------\n");
//    //    }
//
//
//    int *cesta;
//    cesta = zachran_princezne(mapa, n, m, t, &dlzka_cesty);
//
//
//
//    printf("\n pocet: %d |cestaaa:\n",dlzka_cesty);
//    for (i=0;i<dlzka_cesty;++i) printf("%d %d\n", cesta[i*2], cesta[i*2+1]);
//    printf("\n");
//    printf("\n --0---1---2---3---4---5---6---7---8---9--10--11--12--13--14--15--16--17--18--19--\n");
//    for(i=0;i<n;i++){
//        printf("%d",i);
//        for(j=0;j<m;j++){
//            printf("| %c ",mapa[i][j]);
//        }
//        printf("|\n ----------------------------------------------------------------------------\n");
//    }
//    
//
//    return 0;
//}

