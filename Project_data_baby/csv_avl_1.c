#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

typedef struct fdata
{
  char date[11];
  int day;
  int month;
  int year;
  float T_degC;

}float_ocean_data;


int main()
{
  FILE *fptr2 = fopen("C:\\Users\\Orestis\\Downloads\\ocean.csv" , "r");
  float_ocean_data foceanarray[1450];
  int i=0;

   if(!fptr2)
   {
       perror("ERROR unable to open the given CSV file.\n");
       
   }else
   {
    char buffer[1024];
    int row = 0;
    int column = 0;

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
             strcpy(foceanarray[i].date , data_values);
            }

            if(column==1)
            {
              foceanarray[i].T_degC = atof( data_values);
            }

            data_values = strtok(NULL, ", ");
            column++;
          }
        i++;
        }
fclose(fptr2);       
}

int j;

 for(j =0;j<i;j++)
  {
   char * temp; 
   temp = strtok ( foceanarray[j].date,"/");
   int count =0;
   while (temp != NULL)
  {
    if (count == 0)
    {
      foceanarray[j].month= atoi(temp);
    }
    if (count == 1)
    {
     foceanarray[j].day= atoi(temp);
    }

    if (count == 2)
    {
     foceanarray[j].year= atoi(temp);
    }
    temp = strtok ( NULL,"/");
    count ++;
  }     
  } 

for(j =0;j<i;j++)
{
  printf("date %d %d %d " ,foceanarray[j].day, foceanarray[j].month ,foceanarray[j].year);
  printf("T_degC %.3f " ,foceanarray[j].T_degC);
  printf("\n");
}

  return 0; 
}
