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

struct Item selctedItems[10];
int flag[10][250]={0};
int B[10][250];
int tempW2 = 0;
int countOfSelectedItem = 0;

int totalProfit = 0;
int totalWeight = 0;

void writeOutput(){
  FILE *out_file = fopen("output2.txt", "w");
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

void writeOutput1(){

  FILE *out_file = fopen("entries2.txt", "w");

  /*
  for (int i = 0; i<=numOfItems; i++) {
      for (int j = 0; j<=totalCapacity; j++) {

          fprintf(out_file, "%d ",B[i][j]);
      }
      fprintf(out_file,"\n");
  }
  */
  int sb, sk;
  for(sb = numOfItems; sb >=1; sb--)
  {
      fprintf(out_file,"The %d th row entries:", sb);
      for(sk = 0; sk <=totalCapacity; sk++)
      {
          if(B[sb][sk]!=0)
              fprintf(out_file, "{%d, %d} ",sb, sk);
      }
      fprintf(out_file, "\n");
  }
}

int refinmentDP(int numOfItems, int totalCapacity){
    if (numOfItems == 0 || totalCapacity<=0) {
        return 0;
    }else{
        for (int i = numOfItems-1; i>=0; i--) {
            if (items[i].weight > totalCapacity) {
                flag[numOfItems][totalCapacity] = 0;
                return refinmentDP(numOfItems-1, totalCapacity);
            }else{

                int tmp1 = refinmentDP(numOfItems-1, totalCapacity);
                int tmp2 = items[i].profit + refinmentDP(numOfItems-1, totalCapacity-items[i].weight);

                if (tmp1 > tmp2) {
                    flag[numOfItems][totalCapacity] = 0;
                    B[numOfItems][totalCapacity] = tmp1;
                    return tmp1;
                }else{
                    flag[numOfItems][totalCapacity] = 1;
                    B[numOfItems][totalCapacity] = tmp2;
                    return tmp2;
                }
            }
        }
    }

    return 0;
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
  refinmentDP(numOfItems, totalCapacity);

  int ssb, ssk;
  ssb = numOfItems; ssk =totalCapacity;
  for (int i = 1; i<=numOfItems; i++) {
    if (flag[ssb][ssk]==1) {
      tempW2 += items[ssb-1].weight;
      //printf("%d         %d        %d\n",ssb-1,items[ssb-1].weight, items[ssb-1].profit);
      char tempName[10] = "item";
      char data[2];
      sprintf(data, "%d", ssb-1);
      strcat(tempName, data);
      strcpy(selctedItems[countOfSelectedItem].itemName,tempName);
      selctedItems[countOfSelectedItem].profit = items[ssb-1].profit;
      selctedItems[countOfSelectedItem].weight = items[ssb-1].weight;
      totalProfit = totalProfit + items[ssb-1].profit;
      totalWeight = totalWeight + items[ssb-1].weight;
      ssk -=items[ssb-1].weight;
      countOfSelectedItem++;
    }
    ssb--;
  }
  writeOutput();
  writeOutput1();
  return 0;
}
