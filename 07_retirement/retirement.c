#include<stdio.h>
#include<stdlib.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double add_balance(double prevBalance, double contribution, double rate_of_return) {

  double addCurrentBalance = (prevBalance * rate_of_return) + contribution; 

  return addCurrentBalance;
  
}

void retirement(int startAge /*in months*/, double initial /*initial savings in dollars*/, retire_info working, retire_info retired) {

  for(int m = 0; m < working.months; m++) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
    startAge++;
    initial += add_balance(initial, working.contribution, working.rate_of_return);
  }

  for(int v = 0; v < retired.months; v++) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
    startAge++;
    initial += add_balance(initial, retired.contribution, retired.rate_of_return);
  }
}

int main(void/*retire_info working, retire_info retired*/) {

  //Starting conditions:
  int age = 327;
  double savings = 21345.00;

  //Working:
  retire_info working;
  working.months = 489;
  working.contribution = 1000.00;
  working.rate_of_return = (0.045/12);

  //Retired:
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000.00;
  retired.rate_of_return = (0.01/12);

  retirement(age, savings, working, retired);

  return 0;
  
}
