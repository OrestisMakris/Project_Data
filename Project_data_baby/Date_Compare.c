#include<stdio.h>
#include<stdlib.h>

typedef enum { F, T } bool;

typedef struct data
{
    int day;
    int month;
    int year;
    float T_degC;
}ocean_AVL;


struct Tree_node
{
 ocean_AVL key;
 struct Tree_node *left;
 struct Tree_node *right;
 int height;
};

int taster(ocean_AVL key1 , ocean_AVL key2)
{
   int keydate = 0 ;

  if (key1.year < key2.year){
        keydate = 1;
    }if (key1.year ==key2.year && key1.month < key2.month){
        keydate = 1;
    }if (key1.year == key2.year && key1.month == key2.month && key1.day < key2.day){
        keydate = 1;
    }else if (key1.year > key2.year)
    {
        keydate = 2;

    }else if (key1.year== key2.year&& key1.month >key2.month)
    {
        keydate = 2;

    }else if (key1.year==key2.year && key1.month ==  key2.month && key1.day > key2.day)
    {
       keydate = 2;
    }

     return keydate;
}

int main()
{
   ocean_AVL key = {2,12,2002};
  struct Tree_node  tree = {1,12,2002};
  int keydate = taster(key , tree.key);
  printf("e %i", keydate);
    return 0;
}