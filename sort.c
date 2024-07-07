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

void shuffle(int *array, int n) {
  if (n > 1) {
    int i;
    for(i=0; i < n-1; i++) {
      int j = i + rand() / (RAND_MAX / (n-i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

int main(void) {
  int myArray[5] = {1, 2, 3, 4, 5};
  int arrayElements = 5;

  printf("sorted\n");
  for(int i=0;i<5;i++)
    printf("%d", myArray[i]);

  printf("\nscrambled\n");
  shuffle(myArray, arrayElements);
  for(int i=0;i<5;i++)
    printf("%d", myArray[i]);

  printf("\nsorted\n");
  shellsort(myArray, arrayElements);
  for(int i=0;i<5;i++)
    printf("%d", myArray[i]);
  printf("\n");
  return 0;
}
