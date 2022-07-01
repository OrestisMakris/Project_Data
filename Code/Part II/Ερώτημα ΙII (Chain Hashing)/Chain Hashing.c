#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Buckets 250

typedef struct box {

float T_degC;
char date[11];
struct box *next_cell;

}ocean_Cell;

typedef struct hash
{
    ocean_Cell *head;
    int  count;

}hashTable;

hashTable *hash_table = NULL ;


ocean_Cell * new_Cell(char *date , float T_degC)
{

  ocean_Cell *newCell;

  newCell = (ocean_Cell *)malloc(sizeof(ocean_Cell));

  newCell->T_degC = T_degC;
  strcpy(newCell->date, date);
  newCell->next_cell = NULL;

  return newCell;

}

int hashing_function ( char date[11])
{
  int sum = 0;

    for (int k = 0; k < 11; k++){
        sum = sum + date[k];
    }
    return  sum % Buckets ;
}


void insertion(char *date , float T_degC)
{
 int i = hashing_function(date);

 ocean_Cell *newCell =  new_Cell(date,T_degC);

 if ( !hash_table[i].head){

  hash_table[i].head=newCell;
  hash_table[i].count =1;
  return;

 }

 newCell->next_cell = (hash_table[i].head);

 hash_table[i].head = newCell;
 hash_table[i].count++;
  return;

}

float searching(char *date)
{
    int index = hashing_function(date);

    ocean_Cell * search_hash ;
    search_hash = hash_table[index].head;

    while(search_hash != NULL)
    {
        if (strcmp(search_hash->date ,date) == 0) {

            return search_hash->T_degC;
        }

        search_hash = search_hash->next_cell;

    }
}


ocean_Cell *modification(char *date)
{
    int index = hashing_function(date);

    ocean_Cell * search_hash ;
    search_hash = hash_table[index].head;

    while(search_hash != NULL)
    {
        if (strcmp(search_hash->date ,date) == 0) {
            return search_hash;
        }
        search_hash = search_hash->next_cell;
    }
}


void printing() {
    ocean_Cell *print_hash;
    int i;
    for (i = 0; i < Buckets ; i++) {
        if (hash_table[i].count == 0)
            continue;
        print_hash = hash_table[i].head;
        if (!print_hash)
            continue;
        while (print_hash != NULL) {
            printf(" Date %s ", print_hash->date);
            printf("Temperature %f \n", print_hash->T_degC);
            print_hash = print_hash->next_cell;
        }
    }
    return;
}

void deletion(char *date) {

    int Index = hashing_function(date);

    ocean_Cell  *temp_del ;
    ocean_Cell *delet;
    delet = hash_table[Index].head;
    temp_del = delet;

    while (delet != NULL) {

        if (strcmp(delet->date , date) == 0) {

            if (delet == hash_table[Index].head) {
                hash_table[Index].head = delet->next_cell;
            }
            else {
                temp_del->next_cell = delet->next_cell;
            }

            hash_table[Index].count--;
            free(delet);
            break;
        }
        temp_del = delet;
        delet = delet->next_cell;
    }
}

void open_csv_hashing(ocean_Cell *foceanarray) {
    FILE *fptr2 = fopen("C:\\Users\\Orestis\\Downloads\\ocean.csv", "r");


    int i = 0;
    if (!fptr2) {
        perror("ERROR unable to open the given CSV file.\n");
    } else {
        char buffer[1024];
        int row = 0;
        int column = 0;

        while (fgets(buffer, 1024, fptr2)) {
            column = 0;
            row++;

            if (row == 1) {
                continue;
            }

            char *data_values = strtok(buffer, ", ");

            while (data_values) {
                if (column == 0) {
                    strcpy(foceanarray[i].date ,data_values);
                }
                if (column == 1) {
                    foceanarray[i].T_degC = atof(data_values);
                }
                data_values = strtok(NULL, ", ");
                column++;
            }
            i++;
        }
        fclose(fptr2);
    }
}



int main() {
    hash_table = (hashTable *) calloc(Buckets, sizeof(hashTable));
    ocean_Cell foceanarray[1406];


    open_csv_hashing(foceanarray);
    for (int m = 0; m < 1406; m++) {
        insertion(foceanarray[m].date, foceanarray[m].T_degC);
    }

    int cases;

    do {


        printf("Type 1 to print the Chained Hash table  \n");
        printf("Type 2 search the Chained Hash table \n");
        printf("Type 3 Change the temperature giving a specific Data \n");
        printf("Type 4  Delete a specific Date from the Chained Hash table  \n");
        printf("Type 5  Clear Screen\n");
        printf("Type 0 Exit Program\n");

        scanf("%d", &cases);

        switch (cases) {
            case 0:
                break;
            case 1:

                printing();

                break;

            case 2:

                printf("Search \n");
                printf("Enter the date of the temperature you want to find in the Chained Hash table : \n ");
                printf("Give the date in the following format month 00 /day 00 /year 0000 : \n ");
                char *search_date[11];

                printf("Enter :  ");
                scanf("%s", search_date);

                float myf = 0;
                myf = searching(search_date);

                printf("Value found %0.4f \n", myf);


                break;

            case 3:

                printf("Modification \n");
                printf("Enter the date of the node you want to modify the temperature: \n");

               printf("Give the date in the following format month 00 /day 00 /year 0000 : \n ");

                char *mod_date[11];
                float new_temp = 0;

                printf("Enter: ");
                scanf("%s", mod_date);

                printf("Enter the new temperature: ");
                scanf("%f", &new_temp);

                modification(mod_date)->T_degC = new_temp;

                break;

            case 4:

                printf("Enter the date of the temperature you want to DELETE in the Chained Hash table : \n");

                printf("Give the date in the following format month 00 /day 00 /year 0000 : \n ");

                char date[11] ;
                printf("Enter:  ");
               scanf("%s", date);

                deletion(date);
                break;

            case 5:

                system("cls");
                break;

            default:
                printf("Enter Proper Option number \n");
        }

    } while (cases != 0);
    return 0;
}

