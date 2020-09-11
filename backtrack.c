#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct Item {
   char itemName[10];
   int profit;
   int weight;
};

int maxprofit;
int totalWeight = 0;
int num;
int include[10];
int bestset[10];
int X[10];
struct Item items[10];
struct Item selctedItems[10];
int numOfItems;
int totalCapacity;
int countOfSelectedItem = 0;
FILE *out_file1;

struct Item selctedItems[10];

int KWF2(int i, int weight, int profit){
    int bound = profit;
    for (int j = i; j<=numOfItems; j++) {
        X[j] = 0;
    }
    float sbx;
    while (weight < totalCapacity && i<=numOfItems) {
      if (weight + items[i-1].weight <= totalCapacity) {
        //X[i] = 1;
        weight = weight + items[i-1].weight;
        bound = bound + items[i-1].profit;
      }else{
        sbx = (float)(totalCapacity-weight)/(float)items[i-1].weight;
        weight = totalCapacity;
        bound = bound + items[i-1].profit * sbx;
      }
      i += 1;
    }
    return bound;
}


int Promising(int i, int profit, int weight){
    if (weight >= totalCapacity) {
        return 0;
    }
    int bound = KWF2(i+1, weight, profit);

    //printf("(%d, %d, %d)\n",weight,profit,bound);

    fprintf(out_file1, "%d, %d, %d\n",weight,profit,bound);
    return (bound > maxprofit);
}

void knapsack(int i, int profit, int weight){
    if (weight <= totalCapacity && profit > maxprofit) {
        maxprofit = profit;
        num = i;
        //bestset[i] = include[i];
        for (int j = 1; j<=numOfItems; j++) {
            bestset[j] = include[j];
        }
    }
    if (Promising(i, profit, weight)) {
        include[i+1] = 1;
        knapsack(i+1, profit + items[i].profit, weight + items[i].weight);
        include[i+1] = 0;
        knapsack(i+1, profit, weight);
    }

}

void backTrackingAlgorithm(){

    knapsack(0, 0, 0);
    //printf("\nThe final solution(selected items) is: \n\n");
    //printf("Item:    Weight    Profit\n\n");
    for (int i = 1; i<=num; i++) {
        if (bestset[i]==1) {
            totalWeight += items[i-1].weight;
            //printf("%d         %d        %d\n",i-1,items[i-1].weight, items[i-1].profit);
            char tempName[10] = "item";
            char data[2];
            sprintf(data, "%d", i-1);
            strcat(tempName, data);
            strcpy(selctedItems[countOfSelectedItem].itemName,tempName);
            selctedItems[countOfSelectedItem].profit = items[i-1].profit;
            selctedItems[countOfSelectedItem].weight = items[i-1].weight;
            countOfSelectedItem++;
        }
    }

}

void writeOutput(){
  FILE *out_file = fopen("output3.txt", "w");
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
  out_file1 = fopen("entries3.txt", "w");

  int i = 0;
  int j = numOfItems-1;

  while(i < j){
    struct Item temp;
    temp=items[i];
    items[i]=items[j];
    items[j]=temp;
    i++;
    j--;
  }

  backTrackingAlgorithm();
  writeOutput();
  return 0;
}
