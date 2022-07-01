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

float_ocean_data linearsearch(float_ocean_data *ocean_data ,int left,int right,float_ocean_data target){
    int next = 0;
    int counter ;
    while(Compare_Dates(target , ocean_data[next]) != 0 && left < right)
    {
        next = left+1;
        if(Compare_Dates(target, ocean_data[next]) == 0 || Compare_Dates(target, ocean_data[next]) == 1)
            right = next-1;
        else
        {
            left = next+1;
        }
      counter++;
    }
    if(Compare_Dates(target, ocean_data[next]) == 0) {
        printf("dd %d " , counter );
        return ocean_data[next];
    }
}

const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int countLeapYears(float_ocean_data date)
{
    int years = date.year;

    if (date.month <= 2)
        years--;

    return years / 4
           - years / 100
           + years / 400;
}
int getDifference_date(float_ocean_data day1, float_ocean_data day2)
{

    long int n1 = day1.year * 365 + day1.day;


    for (int i = 0; i < day1.month - 1; i++){
        n1 += monthDays[i];
    }

    n1 += countLeapYears(day1);

    long int n2 = day2.year * 365 + day2.day;
    for (int i = 0; i < day2.month - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(day2);


    return (n2 - n1);
}



void quicksort(float_ocean_data *number,int first,int last ){
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



float_ocean_data Exponential_Binary_Interpolation_Search(float_ocean_data *ocean_data , float_ocean_data target  , int n )
{
    int left = 1;
    int right = n-1 ;
    int size ;
    int next =  (int)ceil(((right - left + 1)*(getDifference_date( ocean_data[left], target)))/(getDifference_date(ocean_data[left] , ocean_data[right])))+1 ;

    while(Compare_Dates(target , ocean_data[next]) != 0)
    {
        int i=1;

        size = right - left +1;
        if(size<=2)
        {
            return linearsearch(ocean_data, left, right, target);
        }

        if(Compare_Dates(target, ocean_data[next]) == 0 || Compare_Dates(target, ocean_data[next]) == 2)
        {
            while(Compare_Dates(target ,ocean_data[(int)(next + i*sqrt(size) )]) == 2){
                i = 2*i;
            }
            right = next + i*sqrt(size);
            left = next + (i-1)*sqrt(size);
        }
        else if(Compare_Dates(target, ocean_data[next]) == 1 )
        {
            while(Compare_Dates(target ,ocean_data[(int)(next - i*sqrt(size) )]) == 1){
                i = 2*i;
            }
            right = next - (i-1)*sqrt(size);
            left = next - i*sqrt(size);
        }
        next = left + (int)ceil(((right - left + 1)*(getDifference_date( ocean_data[left], target)))/(getDifference_date(ocean_data[left] , ocean_data[right])))-1 ;
    }

    if(Compare_Dates(target, ocean_data[next]) == 0)
    {
        return ocean_data[next];
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

int main() {

    float_ocean_data ocean_data[1406];
    open_csv(ocean_data);

    float_ocean_data *shorted_ocean_data;
    int i = 1405;
    int j;

    quicksort(ocean_data, 0, i - 1);

    printf("The shorted are:");
    for (j = 0; j < i; j++) {
        printf("--------------------------------------------------------------\n");
        printf("Date %d/%d/%d || ", ocean_data[j].day, ocean_data[j].month, ocean_data[j].year);
        printf("Temperature  = %.3f || ", ocean_data[j].T_degC);
        printf("Phosphate  = %.3f ", ocean_data[j].PO4uM);
        printf("\n");
    }

    float_ocean_data temp;

    printf("Give the value you want to find in the shorted ocean data: \n");
    printf("Enter Day: \n");
    scanf("%d", &temp.day);
    printf("Enter Month: \n");
    scanf("%d", &temp.month);
    printf("Enter Year: \n");
    scanf("%d", &temp.year);

    clock_t t;
    t = clock();
    temp = Exponential_Binary_Interpolation_Search(ocean_data, temp, i);
    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC;

    if (temp.T_degC == 0 ) {
        printf("This date doesn't exist in this date set \n");
    } else {
        printf("The date %d/%d/%d has been found the Temperature is %.3f , and the Phosphate is %.3f \n ", temp.day,
               temp.month, temp.year, temp.T_degC, temp.PO4uM);
    }

    printf("The Quick Short Algorithm took %lf seconds to execute \n", time_taken);
    return 0;
}