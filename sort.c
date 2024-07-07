#include <stdlib.h>
#include <stdio.h>

void shellsort(int v[], int n) {
  int gap, i, j, temp;
  for(gap = n/2; gap > 0; gap /= 2) {
    for(i = gap; i < n; i++) {
      for(j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap) {
        temp = v[j];
        v[j] = v[j+gap];
        v[j+gap] = temp;
      }
    }
  }
}

int main(void) {
  int myArray[5] = {5, 3, 2, 1, 4};
  int arrayElements = 5;
  printf("unsorted\n");
  for(int i=0;i<5;i++)
    printf("%d", myArray[i]);
  printf("\nsorted\n");
  shellsort(myArray, arrayElements);
  for(int i=0;i<5;i++)
    printf("%d", myArray[i]);
  printf("\n");
  return 0;
}
