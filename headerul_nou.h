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
  printf("(53 / H)\n");
  if(!(*aL)) // daca lista este goala
    *aL = aux;

  else
  {
    aux->urm = *aL;
    *aL = aux;
  }
  printf("(62 / H)\n");
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

// ------------------- PERSOANA ---------------------

typedef struct
{
  int varsta,
  greutate,
  inaltime;
} TPersoana;

float BMI(TPersoana p)
{
  return (float)p.greutate / (p.inaltime * p.inaltime);
}

void afisareStatus(TPersoana p)
{
  float b = BMI(p);
  printf("STATUS: ");

  if(b < 18.5)
    printf("Subponderal\n");
  else if(b >= 18.5 && b < 25)
    printf("Normoponderal\n");
  else if(b >= 25 && b < 30)
    printf("Supraponderal\n");
  else if(b >= 30 && b < 40)
    printf("Obezitate\n");
  else
    printf("Obezitate morbida\n");
}
#endif
