#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>



typedef struct idata
{
    char date[11];
    int day;
    int month;
    int year;
    int PO4uM;

}int_ocean_data;

int getMax(int_ocean_data *a , int n)
{
    int_ocean_data max;
    max.PO4uM = a[0].PO4uM;
    for(int i =1; i<n ; i++)
    {
        if(a[i].PO4uM > max.PO4uM)
        {
            max.PO4uM = a[i].PO4uM;
        }
    }
    return max.PO4uM;
}

void Counting_Short(int_ocean_data *ocean_data,int n ,int  k)
{
    int_ocean_data output[n +1];
    int count[k+1];

    for(int i=0; i <= k ; i++)
    {
        count[i]=0;
    }
    for (int i = 0; i < n; i++) // Store the count of each element
    {
        count[ocean_data[i].PO4uM]++;
    }
    for(int i = 1; i<=k; i++)
    {
        count[i] += count[i-1];
    }

    for(int i = n - 1; i >= 0; i--)
    {
        output[count[ocean_data[i].PO4uM] - 1]= ocean_data[i];
        count[ocean_data[i].PO4uM]--;
    }

    for(int i = 0; i<n; i++) {
        ocean_data[i] = output[i];
    }

}

void open_csv (int_ocean_data *foceanarray) {
    FILE *fptr2 = fopen("C:\\Users\\Orestis\\Downloads\\ocean.csv", "r");
    int_ocean_data string_dates[1406];

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

                if (column == 2) {
                    foceanarray[i].PO4uM = atof(data_values)*100;

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

void Results_CSV ( int_ocean_data * shorted_ocean_data)
{
    FILE *f = fopen("C:\\Users\\Orestis\\Documents\\Project_Data_Ver2_Daddy\\Counting_Sort\\Counting Sort_results.csv", "w");
    if (f == NULL)
    {
        printf("Can't open file\n");
        return ;
    }
    int count = 0;
    fprintf(f, "Date,PO4uM\n");
    while (count <1405) {

        fprintf(f, "%d/%d/%d,%d\n",shorted_ocean_data[count].day, shorted_ocean_data[count].month ,shorted_ocean_data[count].year, shorted_ocean_data[count].PO4uM);
        count ++;
    }
    fclose(f);
}



int main(){

    int_ocean_data ocean_data[1406];
    open_csv(ocean_data);

    int i  = 1405;
    int j ;

    int max = getMax(ocean_data , i);
    clock_t t;
    t = clock();

     Counting_Short(ocean_data, i, max );

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("The shorted are:") ;
    for(j =0;j<i;j++)
    {
        printf("------------------------------\n");
        printf("Date %d/%d/%d || " ,ocean_data[j].day, ocean_data[j].month ,ocean_data[j].year);
        printf("PO4uM = %d " ,ocean_data[j].PO4uM);
        printf("\n");;
    }

    printf("The Heap Short Algorithm took %lf seconds to execute \n", time_taken);
    Results_CSV(ocean_data);


}