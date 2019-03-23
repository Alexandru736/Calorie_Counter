#include "headerul_nou.h"

int main()
{
  TMeniu p,
  meniu_zi[3]; // mesele unei persoane intr-o zi
  TLista L = NULL;
  TPersoana pers;
  FILE *f = fopen("input.in", "r");
  int n = 0;

  fscanf(f, "%s %c %d %d %d %d %d", pers.nume, &pers.sex, &pers.varsta,
  &pers.greutate, &pers.inaltime, &pers.tip_regim, &pers.activitate);
  fgetc(f);
  printf("%s:\n|Sex: %c\n|Varsta: %d\n|Greutate(kg): %d\n|Inaltime(cm): %d\n|Activitate saptamanala: %d\n",
  pers.nume, pers.sex, pers.varsta, pers.greutate, pers.inaltime, pers.activitate);
  float bmi = BMI(pers), bmr = BMR(pers);
  printf("\nBMI (%s) = %.3f\n", pers.nume, bmi);
  afisareStatus(pers, &n);
  printf("\nBMR (%s) = %.3f\n", pers.nume, bmr);


  printf("\n");
  while(fscanf(f, "%s %d %hd %hd", p.denumire,
  &p.calorii, &p.masa, &p.categorie) == 4)
  {
    p.contor = 0;
    ins_Inceput_Meniu(&L, p);
    fgetc(f);
  }
  printLista(L);
  printf("\n");

  distrugeLista(&L);
  fclose(f);

  return 0;
}
