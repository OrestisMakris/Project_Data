#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct fdata
{
    char date[11];
    int day;
    int month;
    int year;
    float T_degC;
    float PO4uM;
}float_ocean_data;


int Compare_Dates(float_ocean_data date1 , float_ocean_data date2)
{
    int keydate = 0 ;

    if (date1.year < date2.year){
        keydate = 1;
    }if (date1.year == date2.year && date1.month < date2.month){
        keydate = 1;
    }if (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day){
        keydate = 1;
    }else if (date1.year > date2.year)
    {
        keydate = 2;
    }else if (date1.year == date2.year && date1.month > date2.month)
    {
        keydate = 2;
    }else if (date1.year==date2.year && date1.month ==  date2.month && date1.day > date2.day)
    {
        keydate = 2;
    }
    return keydate;
}


void quicksort(float_ocean_data *number,int first,int last){
    int i, j, pivot;
    float_ocean_data temp;

    if(first<last){
        pivot=first;
        i=first;
        j=last;

        while(i<j){
            while((Compare_Dates(number[i],number[pivot])==1 || Compare_Dates(number[i],number[pivot])==0 )&& i<last )
                i++;
            while(Compare_Dates(number[j],number[pivot])==2 )
                j--;
            if(i<j){
                temp=number[i];
                number[i]=number[j];
                number[j]=temp;
            }
        }

        temp=number[pivot];
        number[pivot]=number[j];
        number[j]=temp;
        quicksort(number,first,j-1);
        quicksort(number,j+1,last);
    }
}

float_ocean_data Binary_Search(float_ocean_data *ocean_data, float_ocean_data target, int  array_Size)
{

    int left = 0;
    int right = array_Size-1;

    int next ;

    while( left<=right)
    {
        next = (int) floor((right+left)/2);
    if(Compare_Dates(target , ocean_data[next]) ==2 ){
        left = next + 1;
    }else if(Compare_Dates(target , ocean_data[next]) ==1){
            right = next-1;
    }else {
        return ocean_data[next];
    }

    }
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
                if (column == 2) {
                    foceanarray[i].PO4uM = atof(data_values);

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
    FILE *f = fopen("C:\\Users\\Orestis\\Documents\\Project_Data_Ver2_Daddy\\Binary_Search\\Dates_Sorted.csv", "w");
    if (f == NULL)
    {
        printf("Can't open file\n");
        return ;
    }
    int count = 0;
    fprintf(f, "Date,T_degC , PO4uM \n");
    while (count <1405) {

        fprintf(f, "%d/%d/%d,%.3f\n",shorted_ocean_data[count].day, shorted_ocean_data[count].month ,shorted_ocean_data[count].year, shorted_ocean_data[count].T_degC ,shorted_ocean_data[count].PO4uM);
        count ++;
    }
    fclose(f);
}

int main()
{

    float_ocean_data ocean_data[1406];
    open_csv(ocean_data);

    float_ocean_data * shorted_ocean_data;
    int i  = 1405;
    int j ;

    quicksort(ocean_data,0, i-1);


    printf("The shorted are: \n") ;
    for(j =0;j<i;j++)
    {
        printf("--------------------------------------------------------------\n");
        printf("Date %d/%d/%d || " ,ocean_data[j].day, ocean_data[j].month ,ocean_data[j].year);
        printf("Temperature  = %.3f || " ,ocean_data[j].T_degC);
        printf("Phosphate  = %.3f " ,ocean_data[j].PO4uM);
        printf("\n");
    }

    float_ocean_data temp;
    printf("Give the value you want to find in the shorted ocean data: \n") ;
    printf("Enter Day: \n");
    scanf("%d", &temp.day);
    printf("Enter Month: \n");
    scanf("%d", &temp.month);
    printf("Enter Year: \n");
    scanf("%d", &temp.year);

    clock_t t;
    t = clock();
     temp = Binary_Search(ocean_data ,temp, i);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    if (temp.T_degC == 0)
    {
        printf("This date doesn't exist in this date set \n"   );
    }else
    {
        printf("The date %d/%d/%d has been found the Temperature is %.3f , and the Phosphate is %.3f \n ",temp.day,temp.month,temp.year , temp.T_degC , temp.PO4uM );
    }

    printf("The Quick Short Algorithm took %lf seconds to execute \n", time_taken);
    Results_CSV(ocean_data);

    return 0;
}