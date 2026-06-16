#include <stdio.h>
#include <stdlib.h>


// int main(void) {
//   int i, sum=0,size=0;
//   printf("Enter the size of the array:\n");
//   scanf("%d", &size);
//   int arr[size];
//   printf("Enter %d element in the array:", size);
//   for(i=0;i<size;i++){
//     scanf("%d", &arr[i]);
//   }
//   for(i=0;i<size;i++){
//     sum += arr[i];
//   }
//   printf("The sum of the array is: %d \n", sum);
//
//   return 0;
// }

int main(void) {
  int i, sum=0, size=0;
  printf("Enter the size of the array:\n");
  scanf("%d", &size);
  printf("Enter %d element in the array:", size);
  int tmp;
  for (i = 0; i < size; i++) {
    scanf("%d", &tmp);
    sum += tmp;
  }
  printf("The sum of the array is: %d \n", sum);

  return 0;
}
