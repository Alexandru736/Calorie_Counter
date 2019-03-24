#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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
  TLista aux;
  while(*aL)
  {
    aux = *aL;
    *aL = aux->urm;
    free(aux);
  }
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
  printf("printare in functie: %d, %d\n", p.greutate, p.inaltime);
  return (float)p.greutate * 10000 / (p.inaltime * p.inaltime);
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

void Generare_Meniu(TLista L, TPersoana pers, float bmr, int nr_elem_lista)
{
  int i, j, min, ok;
  int calor;
  TLista m;
  TMeniu p;
  int pozitii[nr_elem_lista];
  int poz = 0;
  time_t t;
  srand((unsigned) time(&t));

  for(i = 0; i < nr_elem_lista; i++)
    pozitii[i] = 0;

  switch(pers.tip_regim)
  {
    case 4:
      printf("Regim vegan\n");
      break;
    case 2:
      printf("Regim vegetarian\n");
      break;
    case 1:
      printf("Regim normal\n");
      break;
  }
  for (i = 0; i < 7; i++)
  {
    printf("----------- Ziua %d -------------\n", i+1);
    poz = 0;
    min = 10000;

    if(pers.tip_regim == 4) // vegan
    {
      calor = 0;
      for(m = L; m; m = m->urm, poz++) // MIC DEJUN
      {
        if((((m->info).masa) & 1) && (!pozitii[poz])
        && (((m->info).categorie >> 2) & 1))
        {
          calor += (m->info).calorii;
          pozitii[poz] +=  rand() % 3 + 3;

          printf("Mic dejun: %s ---- %d\n", (m->info).denumire, (m->info).calorii);
          m = m->urm;
          poz++;
          break;
        }
      }
      for( ; m; m = m->urm, poz++) // CINA
      {

        if((((m->info).masa >> 2) & 1) && (!pozitii[poz])
        && (((m->info).categorie >> 2) & 1))
        {
          calor += (m->info).calorii;
          pozitii[poz] +=  rand() % 3 + 3;

          printf("Cina: %s ---- %d\n", (m->info).denumire, (m->info).calorii);
          m = m->urm;
          poz++;
          break;
        }
      }
      for( ; m; m = m->urm, poz++) // PRANZ
      {
        if((((m->info).masa >> 1) & 1) && (!pozitii[poz])
        && ((m->info).categorie & 1))
        {
          if(abs(bmr - (m->info).calorii) < min)
          {
            min = abs(bmr - (m->info).calorii);
            ok = poz;
            p = m->info;
          }
          calor += p.calorii;
          pozitii[ok] +=  rand() % 3 + 3;

          printf("Pranz: %s ---- %d\n", p.denumire, p.calorii);
          break;
        }
      }
      printf("Total kcal: %d\n", calor);
      }
    else if(pers.tip_regim == 2) // vegetarian
    {
      calor = 0;
      for(m = L; m; m = m->urm, poz++)
      {
      // MIC DEJUN
        if((((m->info).masa) & 1) && (!pozitii[poz])
        && (((m->info).categorie >> 1) & 1))
        {
          calor += (m->info).calorii;
          pozitii[poz] +=  rand() % 3 + 3;

          printf("Mic dejun: %s ---- %d\n", (m->info).denumire, (m->info).calorii);
          m = m->urm;
          break;
        }
      }
      for( ; m; m = m->urm, poz++)
      {
      // CINA
        if((((m->info).masa >> 2) & 1) && (!pozitii[poz])
        && (((m->info).categorie >> 1) & 1))
        {
          calor += (m->info).calorii;
          pozitii[poz] +=  rand() % 3 + 3;

          printf("Cina: %s ---- %d\n", (m->info).denumire, (m->info).calorii);
          m = m->urm;
          poz++;
          break;
        }
      }
      for( ; m; m = m->urm, poz++) // PRANZ
      {
        if((((m->info).masa >> 1) & 1) && (!pozitii[poz])
        && (((m->info).categorie >> 1) & 1))
        {
          if(abs(bmr - (m->info).calorii) < min)
          {
            min = abs(bmr - (m->info).calorii);
            ok = poz;
            p = m->info;
          }
          calor += p.calorii;
          pozitii[ok] +=  rand() % 3 + 3;

          printf("Pranz: %s ---- %d\n", p.denumire, p.calorii);
          break;
        }
      }

      printf("Total kcal: %d\n", calor);
      }
    else if(pers.tip_regim == 1) // oarecare
    {
      calor = 0;
      for(m = L; m; m = m->urm, poz++)
      {
      // MIC DEJUN
        if((((m->info).masa) & 1) && (!pozitii[poz])
        && ((m->info).categorie & 1))
        {

          calor += (m->info).calorii;
          pozitii[poz] +=  rand() % 3 + 3;

          printf("Mic dejun: %s ---- %d\n", (m->info).denumire, (m->info).calorii);
          m = m->urm;
          poz++;
          break;
        }
      }
      for( ; m; m = m->urm, poz++) // CINA
      {

        if((((m->info).masa >> 2) & 1) && (!pozitii[poz])
        && ((m->info).categorie & 1))
        {
          calor += (m->info).calorii;
          pozitii[poz] +=  rand() % 3 + 3;

          printf("Cina: %s ---- %d\n", (m->info).denumire, (m->info).calorii);
          m = m->urm;
          poz++;
          break;
        }
      }
      for( ; m; m = m->urm, poz++) // PRANZ
      {
        if((((m->info).masa >> 1) & 1) && (!pozitii[poz])
        && ((m->info).categorie & 1))
        {
          if(abs(bmr - (m->info).calorii) < min)
          {
            min = abs(bmr - (m->info).calorii);
            ok = poz;
            p = m->info;
          }
          calor += p.calorii;
          pozitii[ok] +=  rand() % 3 + 3;

          printf("Pranz: %s ---- %d\n", p.denumire, p.calorii);
          break;
        }
      }

      printf("Total kcal: %d\n", calor);
    }

    for(m = L, poz = 0; m; m = m->urm, poz++)
      if(pozitii[poz])
        pozitii[poz]--;
    printf("\n");
  }
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
