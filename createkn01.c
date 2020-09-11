#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct Item {
   char itemName[10];
   int profit;
   int weight;
};

int main(int argc, char* argv[]){

  //srand(time(0));
  int numOfItems = rand() % 4 + 4;
  printf("Number of items : %d\n", numOfItems);


  struct Item items[numOfItems];

  int totalCapacity = 0;

  for(int count = 0; count < numOfItems; count++){
      char tempName[10] = "item";
      char data[2];
      sprintf(data, "%d", count);
      strcat(tempName, data);
      strcpy(items[count].itemName,tempName);

      items[count].profit = rand() % 20 + 10;

      items[count].weight = rand() % 15 + 5;

      totalCapacity = totalCapacity + items[count].weight;
  }
  printf("capacity : %d\n", totalCapacity);
  int knapsackCapacity = floor(0.6*totalCapacity);
  printf("knapsackCapacity : %d\n", knapsackCapacity);
  FILE *out_file = fopen(argv[2], "w");
  fprintf(out_file, "%d ", numOfItems);
  fprintf(out_file, "%d\n", knapsackCapacity);

  for(int count = 0; count < numOfItems; count++){
    fprintf(out_file, "%s ", items[count].itemName);
    fprintf(out_file, "%d ", items[count].profit);
    fprintf(out_file, "%d\n", items[count].weight);
  }

  fclose(out_file);
}
