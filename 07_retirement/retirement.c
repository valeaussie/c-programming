#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double calc_balance(double starting_balance, retire_info info){
  double interest = starting_balance * info.rate_of_return;
  double current_balance = interest + starting_balance;
  current_balance = current_balance + info.contribution;
  return current_balance;
}

void retirement (int startAge, double initial, retire_info working, retire_info retired){
  double current_balance = initial;
  int m = startAge;
  int retirement_age_in_months = startAge + working.months;
  int first_month = startAge + working.months + 1;
  int time_retired = retirement_age_in_months + retired.months -1;
  double first_balance;

  do{
    int year_age = m/12;
    int month_age = m%12;
    first_balance = initial;
    printf("Age %3d month %2d you have $%.2lf\n", year_age, month_age, current_balance);
    m += 1;
    current_balance = calc_balance(initial, working);
    initial = current_balance;
  } while (m <= retirement_age_in_months);

  int i = first_month;

  do{
    int year_age = i/12;
    int month_age = i%12;
    i += 1;
    current_balance = calc_balance(first_balance, retired);
    printf("Age %3d month %2d you have $%.2lf\n", year_age, month_age, current_balance);
    first_balance = current_balance;
  } while (i <= time_retired);

}

int main(void) {
  retire_info working;
  retire_info retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  int startAge = 327;
  double initial = 21345;

  retirement(startAge, initial, working, retired);

  return 0;
}
