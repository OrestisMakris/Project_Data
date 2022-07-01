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
    float PO4uM;

}float_ocean_data;


float_ocean_data *Heap_Short(float_ocean_data *ocean_data, int size)
{
    int j,l,k,r;
    float_ocean_data temp ,S;
    int n = size -1;

    l=(n/2) -1;//heap sort by tsakalidis
    r=n;

    while(r>=2){
        if(l>1){
            l=l-1;
            j=l;
        }
        else{
            temp = ocean_data[1];
            ocean_data[1] = ocean_data[r];
            ocean_data[r]= temp;

            r = r-1;
            j=1;
        }
        S=ocean_data[j];

        while ((2*j)<=r)
        {
            k=(2*j);
            if(k<r && ocean_data[k].PO4uM<ocean_data[k+1].PO4uM){
                k=k+1;
            }
            if(S.PO4uM<ocean_data[k].PO4uM){
                ocean_data[j]=ocean_data[k];
                j = k;

            }else
            {
                goto E;
            }
        }
        E :
        ocean_data[j] =  S;
    }
    return ocean_data;
}

void open_csv (float_ocean_data *foceanarray) {
    FILE *fptr2 = fopen("C:\\Users\\Orestis\\Downloads\\ocean.csv", "r");
    float_ocean_data string_dates[1407];

    int i = 1;
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
    for (j = 1; j < i; j++) {
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
    FILE *f = fopen("C:\\Users\\Orestis\\Documents\\Project_Data_Ver2_Daddy\\Heap_Short\\Heap_Sort_results.csv", "w");
    if (f == NULL)
    {
        printf("Can't open file\n");
        return ;
    }
    int count = 0;
    fprintf(f, "Date,PO4uM\n");
    while (count <1405) {

        fprintf(f, "%d/%d/%d,%.3f\n",shorted_ocean_data[count].day, shorted_ocean_data[count].month ,shorted_ocean_data[count].year, shorted_ocean_data[count].PO4uM);
        count ++;
    }
    fclose(f);
}



int main(){

    float_ocean_data ocean_data[1406];
    open_csv(ocean_data);

    float_ocean_data * shorted_ocean_data;
    int i  = 1405;
    int j ;

    clock_t t;
    t = clock();

    shorted_ocean_data = Heap_Short(ocean_data, i);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("The shorted are:v \n" ) ;
    for(j =1;j<i;j++)
    {
        printf("-------------------------------------\n");
        printf("Date %d/%d/%d || " ,shorted_ocean_data[j].day, shorted_ocean_data[j].month ,shorted_ocean_data[j].year);
        printf("Phosphate  = %.3f " ,shorted_ocean_data[j].PO4uM);
        printf("\n");

    }

    printf("The Heap Short Algorithm took %lf seconds to execute \n", time_taken);
    Results_CSV(shorted_ocean_data);


}