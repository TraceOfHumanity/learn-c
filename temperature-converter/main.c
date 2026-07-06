#include <math.h> // NAN, isnan
#include <stdio.h>

static const double KELVIN_OFFSET = 273.15;
static const double FAHRENHEIT_RATIO = (9.0 / 5.0);
static const double FAHRENHEIT_OFFSET = 32.0;

double celsiusToFahrenheit(double value) {
  return value * FAHRENHEIT_RATIO + FAHRENHEIT_OFFSET;
}
double celsiusToKelvin(double value) { return value + KELVIN_OFFSET; }

double fahrenheitToCelsius(double value) {
  return (value - FAHRENHEIT_OFFSET) / FAHRENHEIT_RATIO;
}
double fahrenheitToKelvin(double value) {
  return celsiusToKelvin(fahrenheitToCelsius(value));
}

double kelvinToCelsius(double value) {
  if (value < 0)
    return NAN;
  return value - KELVIN_OFFSET;
}
double kelvinToFahrenheit(double value) {
  if (value < 0)
    return NAN;
  return celsiusToFahrenheit(kelvinToCelsius(value));
}

int main(void) {
  int selectedDegreeScale;
  double value;

  printf("Обери, яку шкалу в яку бажаєш конвертувати.\n");
  printf("1) C->F  2) C->K  3) F->C  4) F->K  5) K->C  6) K->F\n");
  printf("Вибір: ");
  scanf("%d", &selectedDegreeScale);

  printf("Введи значення: ");
  scanf("%lf", &value);

  switch (selectedDegreeScale) {
  case 1:
    printf("%.2f\n", celsiusToFahrenheit(value));
    break;
  case 2:
    printf("%.2f\n", celsiusToKelvin(value));
    break;
  case 3:
    printf("%.2f\n", fahrenheitToCelsius(value));
    break;
  case 4:
    printf("%.2f\n", fahrenheitToKelvin(value));
    break;
  case 5:
    printf("%.2f\n", kelvinToCelsius(value));
    break;
  case 6:
    printf("%.2f\n", kelvinToFahrenheit(value));
    break;
  default:
    printf("Невірний вибір\n");
  }
  return 0;
}