#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>


typedef struct fdata
{
    char date[11];
    int day;
    int month;
    int year;
    float T_degC;

}float_ocean_data;


float_ocean_data *quicksort(float_ocean_data *data, int first , int last )
{
    int i ,  pivot ,j ;
    float_ocean_data temp;;

    if(first<last){

        pivot= first;
        i=first;
        j=last;

        while(i<j){
            while(data[i].T_degC<=data[pivot].T_degC&&i<last) {
                i++;
            }
            while(data[j].T_degC>data[pivot].T_degC)
            {
                j--;
            }
            if(i<j){
                temp = data[i];
                data[i]=data[j];
                data[j]=temp;
            }
        }

        temp=data[pivot];
        data[pivot]=data[j];
        data[j]=temp;
        quicksort(data,first,j-1);
        quicksort(data,j+1,last);

    }
    return data;
}


void open_csv (float_ocean_data *foceanarray) {
    FILE *fptr2 = fopen("C:\\Users\\Orestis\\Downloads\\ocean.csv", "r");
    float_ocean_data string_dates[1406];

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
                    strcpy(string_dates[i].date, data_values);
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
    int j = 0;
    for (j = 0; j < i; j++) {
        char *temp;
        temp = strtok(string_dates[j].date, "/");
        int count = 0;
        while (temp != NULL) {
            if (count == 0) {
                foceanarray[j].month = atoi(temp);
            }
            if (count == 1) {
                foceanarray[j].day = atoi(temp);
            }

            if (count == 2) {
                foceanarray[j].year = atoi(temp);
            }
            temp = strtok(NULL, "/");
            count++;
        }
    }
}

void Results_CSV ( float_ocean_data * shorted_ocean_data)
{
    FILE *f = fopen("C:\\Users\\Orestis\\Documents\\Project_Data_Ver2_Daddy\\Q\\Quicksort_result.csv", "w");
    if (f == NULL)
    {
        printf("Can't open file\n");
        return ;
    }
    int count = 0;
    fprintf(f, "Date,T_degC\n");
    while (count <1406) {

        fprintf(f, "%d/%d/%d,%.3f\n",shorted_ocean_data[count].day, shorted_ocean_data[count].month ,shorted_ocean_data[count].year, shorted_ocean_data[count].T_degC);
        count ++;
    }
    fclose(f);
}

int main()
{

    float_ocean_data ocean_data[1406];
    open_csv(ocean_data);

    float_ocean_data * shorted_ocean_data;
    int i  = 1406;
    int j ;
    clock_t t;
    t = clock();
    shorted_ocean_data = quicksort(ocean_data, 0 ,1405);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("The shorted are: \n") ;
    for(j =1;j<i;j++)
    {
        printf("----------------------------------\n");
        printf("Date %d/%d/%d || " ,shorted_ocean_data[j].day, shorted_ocean_data[j].month ,shorted_ocean_data[j].year);
        printf("T_degC = %.3f " ,shorted_ocean_data[j].T_degC);
        printf("\n");
    }
   Results_CSV(shorted_ocean_data);
    printf("The Quick Short Algorithm took %lf seconds to execute \n", time_taken);
    return 0;
}