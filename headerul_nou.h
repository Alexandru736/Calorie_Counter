#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HEADER
#define HEADER

typedef struct
{
  int calorii, // nr. total calorii
  contor; // nr. de mese peste care poate sa mai serveasca aceasta masa

  char denumire[30]; // cum se numeste masa respectiva

  short int masa, // 1 = mic dejun, 2 = pranz, 4 = cina
  categorie; // 1 = normal, 2 = vegetarian, 4 = vegan
} TMeniu;

typedef struct cel
{
  TMeniu info;
  struct cel * urm;
}TCel, *TLista, **ALista;

TLista AlocCelula(TMeniu M)
{
  TLista aux = (TLista)malloc(sizeof(TCel));
  if(!aux)
    return NULL;
  aux->info = M;
  aux->urm = NULL;
  return aux;
}

int ins_Inceput_Meniu(ALista aL, TMeniu M)
{
  TLista aux = AlocCelula(M);
  if(!aux)
    return 0;
  if(!(*aL)) // daca lista este goala
    *aL = aux;

  else
  {
    aux->urm = *aL;
    *aL = aux;
  }
  return 1;
}

void printLista(TLista L)
{
  TMeniu m;
  for(; L; L = L->urm)
  {
    m = L->info;
    printf("%s %d %d %hd %hd\n", m.denumire,
            m.calorii, m.contor, m.masa, m.categorie);
  }
}

void distrugeLista(ALista aL)
{
  printf("Accesam distrugerea.\n");
  TLista aux;
  while(*aL)
  {
    aux = *aL;
    *aL = aux->urm;
    free(aux);
  }
  printf("Lista e goala.\n");
}
// ------------------- PERSOANA ---------------------

typedef struct
{
  char nume[10];

  int varsta,
  greutate,
  inaltime;
  short int tip_regim;
} TPersoana;

float BMI(TPersoana p)
{
  return (float)p.greutate / (p.inaltime * p.inaltime / (100 * 100));
}

TMeniu* Generare_Meniu(TLista meniuri, TPersoana *persoana, char status[13])
{
    TMeniu meniul_zilei[3];
    int i;
    for(; meniuri != NULL; meniuri = meniuri->urm)
    {

    }
    return meniul_zilei;
}

char* afisareStatus(TPersoana p, int *calorii_target)
{
  float b = BMI(p);
  char status[13];
  printf("STATUS: ");

  if(b < 18.5)
  {
    printf("Subponderal\n");
    *calorii_target =
    strcpy(status, "Subponderal");
  }
  else if(b >= 18.5 && b < 25)
  {
    printf("Normoponderal\n");
    strcpy(status, "Normoponderal");
  }
  else if(b >= 25 && b < 30)
  {
    printf("Supraponderal\n");
    strcpy(status, "Supraponderal");
  }
  else if(b >= 30 && b < 40)
  {
    printf("Obezitate\n");
    strcpy(status, "Obezitate");
  }
  else
  {
    printf("Obezitate morbida\n");
    strcpy(status, "Obezitate morbida");
  }
  return status;
}


#endif
