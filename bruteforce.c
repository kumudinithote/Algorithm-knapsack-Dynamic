#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct Item {
   char itemName[10];
   int profit;
   int weight;
};

struct Item items[10];
int numOfItems;
int totalCapacity;
int countOfSelectedItem = 0;

struct Item selctedItems[10];

void writeOutput(){
  FILE *out_file = fopen("output.txt", "w");
  fprintf(out_file, "%d\t", countOfSelectedItem);

  int totalProfit = 0;
  int totalWeight = 0;

  for(int i = 0; i < countOfSelectedItem; i++){
    totalProfit = totalProfit + selctedItems[i].profit;
    totalWeight = totalWeight + selctedItems[i].weight;
  }

  fprintf(out_file, "%d\t", totalProfit);
  fprintf(out_file, "%d\n", totalWeight);

  for(int count = 0; count < countOfSelectedItem; count++){
    fprintf(out_file, "%s\t", selctedItems[count].itemName);
    fprintf(out_file, "%d\t", selctedItems[count].profit);
    fprintf(out_file, "%d\n", selctedItems[count].weight);
  }
}

void bruteForceKnapsack(){
  int bestValue = 0;
  int bestPosition = 0;

  int iter=pow(2.0,numOfItems);

  for (int i = 0; i < iter; i++){
    int total = 0;
    int weight = 0;

    for (int j = 0; j < numOfItems; j++){
      if (((i >> j) & 1) != 1) continue;
        total += items[j].profit;
        weight += items[j].weight;
    }

    if (weight <= totalCapacity && total > bestValue){
      bestPosition = i;
      bestValue = total;
    }
  }

  for (int j = 0; j < numOfItems; j++){
    if (((bestPosition >> j) & 1) == 1){
      selctedItems[countOfSelectedItem] = items[j];
      countOfSelectedItem++;
    }
  }

}

int parseFile(char * filename){
  FILE *file;
  int count = 0;
  file = fopen(filename,"r");
	if(file == NULL) {
		printf("\nERROR in opening the file!\n\n");
    return 0;
	}

  char ch;
  char line [1000];
  if(fgets(line,sizeof line,file)!= NULL){
    char * token = strtok(line, " ");
    //printf("%s\n", token );

    numOfItems = atoi(token);
    token = strtok(NULL, " ");
    //printf("%s\n", token );
    totalCapacity = atoi(token);
  }

  while(fgets(line,sizeof line,file)!= NULL){
    //fprintf(stdout,"%s",line);
    char * token = strtok(line, " ");
    strcpy(items[count].itemName, token);

    token = strtok(NULL, " ");
    items[count].profit = atoi(token);

    token = strtok(NULL, " ");
    items[count].weight = atoi(token);

    count++;
  }
  fclose(file);
  return 0;
}

int main(int argc, char* argv[]){
  parseFile(argv[2]);
  bruteForceKnapsack();
  writeOutput();
  return 0;
}
