#include "headerul_nou.h"

int main()
{
  TMeniu p;
  TLista L = NULL;
  FILE *f = fopen("input.in", "r");

  while(fscanf(f, "%s %d %d %hd %hd", p.denumire,
  &p.calorii, &p.contor, &p.masa, &p.categorie) == 5)
    ins_Inceput_Meniu(&L, p);

  printLista(L);

  fclose(f);

  return 0;
}
