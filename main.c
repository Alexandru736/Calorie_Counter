#include "headerul_nou.h"

int main()
{
  TMeniu p,
  meniu_zi[3]; // mesele unei persoane intr-o zi
  TLista L = NULL, aux;
  TPersoana pers;
  FILE *f = fopen("input.in", "r");
  int n = 0, i;
  int nr_elem_lista = 0;
  float mass;

  fscanf(f, "%s %c %d %d %d %hd %d", pers.nume, &pers.sex, &pers.varsta,
  &pers.greutate, &pers.inaltime, &pers.tip_regim, &pers.activitate);
  fgetc(f);
  printf("%s:\n|Sex: %c\n|Varsta: %d\n|Greutate(kg): %d\n|Inaltime(cm): %d\n|Activitate saptamanala: %d\n",
  pers.nume, pers.sex, pers.varsta, pers.greutate, pers.inaltime, pers.activitate);
  float bmi = BMI(pers), bmr = BMR(pers);
  printf("\nBMI (%s) = %.3f\n", pers.nume, bmi);
  afisareStatus(pers, &n);

  printf("\nBMR (%s) = %.3f\n", pers.nume, bmr);
  if(bmi > 25)
  {
    printf("Alege cu cat vrei sa slabesti (0.5, 1) kg / saptamana: ");
    scanf("%f", &mass);

    switch((int)(2 * mass))
    {
      case 1:
        bmr -= 500;
        break;
      case 2:
        bmr -= 1100;
        break;
    }
  }
  else if(bmi < 18.5)
  {
    printf("Alege cu cat vrei sa te ingrasi (0.5, 1) kg / saptamana: ");
    scanf("%f", &mass);

    switch((int)(2 * mass))
    {
      case 1:
        bmr += 500;
        break;
      case 2:
        bmr += 1100;
        break;
    }
  }
  printf("\nNr. calorii / zi: %.3f\n", bmr);
  printf("\n");
  while(fscanf(f, "%s %d %hd %hd", p.denumire,
  &p.calorii, &p.masa, &p.categorie) == 4)
  {
    p.contor = 0;
    ins_Inceput_Meniu(&L, p);
    nr_elem_lista++;
    fgetc(f);
  }
  printLista(L);
  printf("\n");

  Generare_Meniu(L, pers, bmr, nr_elem_lista);

  distrugeLista(&L);
  fclose(f);

  return 0;
}
