#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

typedef struct Cdata
{
    char date[11];
    char T_degC[6];
    char PO4uM[5];
    char SiO3uM[5];
    char NO2uM[5];
    char NO3uM[5];
    char Salnty[7];
    char O2ml_L[6];

}char_ocean_data;

typedef struct fdata
{
    int day;
    int month;
    int year;
    float T_degC;
   float PO4uM;
    float SiO3uM;
    float NO2uM;
    float NO3uM;
    float Salnty;
   float O2ml_L;

}float_ocean_data;


int main()
{
  FILE *fptr2 = fopen("C:\\Users\\Orestis\\Downloads\\ocean.csv" , "r");
  char_ocean_data oceanarray[1450];
  float_ocean_data foceanarray[1450];

   if(!fptr2)
   {
       perror("ERROR unable to open the given CSV file.\n");
       
   }else
   {
       char buffer[1024];
       int row = 0;
       int column = 0;
       int i=0;

       while (fgets(buffer, 1024,fptr2))
       {
           column = 0;
           row ++;

           if(row == 1)
           {
               continue;
           }

           char* data_values = strtok(buffer, ", ");

           while (data_values)
           {
               if(column==0)
               {
                   strcpy(oceanarray[i].date , data_values);

                   for(int j =0; j <11; j++)
                   {
                     int coo;
                     coo ++;
                   }
            
               }

               if(column==1)
               {
                 strcpy(oceanarray[i].T_degC , data_values);
                 foceanarray[i].T_degC = atof( oceanarray[i].T_degC);
               }

               if(column==2)
               {
                   strcpy(oceanarray[i].PO4uM , data_values);
                   foceanarray[i].PO4uM = atof( oceanarray[i].PO4uM);
                   
               }

               if(column==3)
               {
                   strcpy(oceanarray[i].SiO3uM , data_values);
                   foceanarray[i].SiO3uM = atof( oceanarray[i].SiO3uM);
                   
               }

               if(column==4)
               {
                  strcpy(oceanarray[i].NO2uM , data_values);
                  foceanarray[i].NO2uM = atof( oceanarray[i].NO2uM);
                   
               }

               if(column==5)
               {
                  strcpy(oceanarray[i].NO3uM , data_values);
                  foceanarray[i].NO3uM = atof( oceanarray[i].NO3uM);
                   
               }

               if(column==6)
               {
                   strcpy(oceanarray[i].Salnty , data_values);
                   foceanarray[i].Salnty = atof( oceanarray[i].Salnty);
                   
               }

               if(column==7)
               {
                   strcpy(oceanarray[i].O2ml_L , data_values);
                   foceanarray[i].O2ml_L = atof( oceanarray[i].O2ml_L);
                   
               }
                data_values = strtok(NULL, ", ");
                column++;
            }
          i++;
        }

       fclose(fptr2);

    int j;
       for(j =0;j<i;j++)
       {
           printf("Date %s " , oceanarray[j].date);
           printf("T_degC %.3f " ,foceanarray[j].T_degC);
           printf("PO4uM %.3f " , foceanarray[j].PO4uM);
           printf("SiO3uM %.3f " ,foceanarray[j].SiO3uM);
           printf("NO2uM %.3f " , foceanarray[j].NO2uM);
           printf("NO3uM %.3f " , foceanarray[j].NO3uM);
           printf("Salnty %.3f " ,foceanarray[j].Salnty);
           printf("O2ml_L %.3f " ,foceanarray[j].O2ml_L);
           printf("\n");
       }
         
}
  return 0; 
}

