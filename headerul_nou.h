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
  inaltime,
  activitate; // de cate ori face sport pe saptamana
  // 0 = sedentar, 1 = 1-3 ori, 2 = 3-5 ori, 3 = 6-7
  short int tip_regim; // La fel ca la meniu
  char sex; // poate fi doar 'M' sau 'F'
} TPersoana;

float BMI(TPersoana p)
{
  return (float)p.greutate / (p.inaltime * p.inaltime / (100 * 100));
}

float BMR(TPersoana p)
{
  int bmr;
  bmr = 10 * p.greutate + 6.25 * p.inaltime - 5 * p.varsta;
  if(p.sex == 'F')
    bmr -= 161;
  else if(p.sex == 'M')
    bmr += 5;
  switch(p.activitate)
  {
    case 0:
      bmr *= 1.2;
      break;
    case 1:
      bmr *= 1.375;
      break;
    case 2:
      bmr *= 1.55;
      break;
    case 3:
      bmr *= 1.725;
      break;
  }
  return bmr;
}
TMeniu* Generare_Meniu(TLista meniuri, TPersoana *persoana, char status[13])
{
    TMeniu meniul_zilei[3];
    int i;
    for(; meniuri != NULL; meniuri = meniuri->urm);

    return NULL;
}

char* afisareStatus(TPersoana p, int *calorii_target)
{
  float b = BMI(p);
  char status[25];
  strcpy(status, "");
  printf("STATUS: ");

  if(b < 18.5)
  {
    strcpy(status, "Subponderal");
    //*calorii_target =
  }
  else if(b >= 18.5 && b < 25)
  {
    strcpy(status, "Normoponderal");
  }
  else if(b >= 25 && b < 30)
  {
    strcpy(status, "Supraponderal");
  }
  else if(b >= 30 && b < 40)
  {
    strcpy(status, "Obezitate");
  }
  else
  {
    strcpy(status, "Obezitate morbida");
  }

  printf("%s\n", status);
  return 0;
}


#endif
