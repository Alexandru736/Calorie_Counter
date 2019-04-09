#include "header.h"

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
  printf("Nume: %s\n", pers.nume);
  printf("Sex: %c\n", pers.sex);
  printf("Varsta: %d\n", pers.varsta);
  printf("Greutate(kg): %d\n", pers.greutate);
  printf("Inaltime(cm): %d\n", pers.inaltime);
  printf("Activitate saptamanala (0 - sedentar, 1 - 1-3 ori, 2 - 3-5 ori, 3 - 6-7 ori): %d\n",
  pers.activitate);
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
  printf("\nTarget ----> Nr. calorii / zi: %.3f\n", bmr);
  printf("\n");
  while(fscanf(f, "%s %d %hd %hd", p.denumire,
  &p.calorii, &p.masa, &p.categorie) == 4)
  {
    p.contor = 0;
    ins_Inceput_Meniu(&L, p);
    nr_elem_lista++;
    fgetc(f);
  }

  Generare_Meniu(L, pers, bmr, nr_elem_lista);

  distrugeLista(&L);
  fclose(f);

  return 0;
}
