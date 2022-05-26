#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


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


struct Tree_node * new_avl_Node(ocean_AVL key)
{
    struct Tree_node* Node = (struct Tree_node *)malloc(sizeof(struct Tree_node));
    Node->key.day   = key.day;
    Node->key.month =key.month;
    Node->key.year =key.year;
    Node->key.T_degC =key.T_degC;
    Node->left   = NULL;
    Node->right  = NULL;
    Node->height = 0; 
    return(Node);
}


int max(int left, int right) {

    if(left > right)
    {
      return  left ;

    }else if (left < right){
        return  right ;
    }

    return 0;
}

int getheight(struct Tree_node * TNode)
{
    if(TNode == NULL){
     return 0;
    }else 
    {
        return 1 + max(getheight(TNode->left),getheight(TNode->right));
    }

}


int getBalance(struct Tree_node *TNode)
{
    if (TNode == NULL){
        return 0;
    }
    return getheight(TNode->left) - getheight(TNode->right);
}


struct Tree_node *Left_Rotation(struct Tree_node *x)
{
    struct Tree_node *y = x->right;
    x->right = y->left;
 
    y->left = x;
 
    x->height = getheight(x);
    y->height = getheight(y);

    return y;
}


struct Tree_node *Right_Rotation(struct Tree_node *y)
{
    struct Tree_node *x = y->left;
    y->left = x->right;
 
    x->right = y;
 
    x->height = getheight(x);
    y->height = getheight(y);
 
    return x;
}


struct Tree_node* insertion(struct Tree_node* treenode , ocean_AVL key)
{
 if (treenode == NULL){
        return(new_avl_Node(key));
 }


    if (key.T_degC < treenode->key.T_degC ){

        treenode->left  = insertion(treenode->left, key);

    }else if (key.T_degC > treenode->key.T_degC){

        treenode->right = insertion(treenode->right, key);

    }else{
        return treenode;
    }
    
    
 treenode->height = getheight(treenode);
 int balance = getBalance(treenode);

   if(balance > 1){
        
        if(getBalance(treenode->left) == 1){
            return Right_Rotation(treenode);
        }
        
        else{
            treenode->left = Left_Rotation(treenode->left);
            return Right_Rotation(treenode);
        }
    }
    else if(balance < -1){
       
        if(getBalance(treenode->right) == -1){
            return Left_Rotation(treenode);
        }

        else{
            treenode->right = Right_Rotation(treenode->right);
            return Left_Rotation(treenode);
        }

    }
 return treenode;
}

void preOrder(struct Tree_node *root)
{
    if(root != NULL)
    {
        printf("%f ", root->key.T_degC);
        preOrder(root->left);
        preOrder(root->right);
    }
}

struct  Tree_node * find_max_value(struct Tree_node* treenode)
{
    
  struct Tree_node* node = treenode; 

    while (node->right != NULL)
        node = node->right;
 
    return(node);

}

struct  Tree_node * find_min_value(Tree_node* treenode)
{
 struct Tree_node* node = treenode; 
 

  while (node->left != NULL)
  {
    node = node->left;
  }
  return(node);
}

int main()
{

  struct Tree_node *root = NULL;

 
  /* Constructing tree given in the above figure */
  ocean_AVL taster;
  taster.day =10;
  taster.month = 123;
  taster.year = 1333;
  taster.T_degC = 10;
  root = insertion(root, taster);

  taster.day =21;
  taster.month = 8;
  taster.year = 2002;
  taster.T_degC = 20;
  root = insertion(root, taster);
  
  
  taster.day =33;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 30;
   root = insertion(root, taster);

   taster.day =44;
  taster.month = 14;
  taster.year = 144;
  taster.T_degC = 40;
   root = insertion(root, taster);
   taster.day =57;
  taster.month = 44;
  taster.year = 69;
  taster.T_degC = 50;
   root = insertion(root, taster);
   taster.day =1333;
  taster.month = 8;
  taster.year = 2022;
  taster.T_degC = 25;
   root = insertion(root, taster);
   

    taster.day =166;
  taster.month = 69696969;
  taster.year = 14;
  taster.T_degC = 1;
   root = insertion(root, taster);
    
   taster.day =22;
  taster.month = 3330;
  taster.year = 333;
  taster.T_degC = 22;
   root = insertion(root, taster);
    
   taster.day =3;
  taster.month = 1330;
  taster.year = 10666;
  taster.T_degC = 3;
   root = insertion(root, taster);
   
   taster.day =558;
  taster.month = 5;
  taster.year = 1555;
  taster.T_degC = 555;
   root = insertion(root, taster);
    
   taster.day =1955;
  taster.month = 1550;
  taster.year = 16;
  taster.T_degC = 19;
   root = insertion(root, taster);

   taster.day =69563;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 69;
   root = insertion(root, taster);

   taster.day =7877;
  taster.month = 1053;
  taster.year = 135350;
  taster.T_degC = 70 ;
   root = insertion(root, taster);
    taster.day =66969;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 66;
   root = insertion(root, taster);

  taster.day =66969;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 556;
   root = insertion(root, taster);

   /* ocean_AVL seer;

 seer.day =70;
 seer.month = 10;
 seer.year = 10;

struct Tree_node *ser = search(root,seer);
printf("thelo kavlia \n");
   preOrder(ser);
    printf("%f",ser->key.T_degC); */
   

  printf("Preorder traversal of the constructed AVL"" tree is \n");
preOrder(root);
  
  struct Tree_node *ser = find_min_value(root);
  printf("thelo kavlia \n");
   preOrder(ser);
    printf("%i / %i / %i ",ser->key.day,ser->key.month,ser->key.year); 

    

   /*ocean_AVL taster1;
    taster1.day =20; 
  taster1.month = 10;
  taster1.year = 10;
  taster1.T_degC = 554444;

  root = Node_deletion(root, taster1);
  taster1.day =69; 
  taster1.month = 10;
  taster1.year = 10;
  taster1.T_degC = 554444;
  root = Node_deletion(root, taster1);
  taster1.day =66; 
  taster1.month = 10;
  taster1.year = 10;
  taster1.T_degC = 554444;
  root = Node_deletion(root, taster1);
  taster1.day =50; 
  taster1.month = 10;
  taster1.year = 10;
  taster1.T_degC = 554444;
  root = Node_deletion(root, taster1);
   taster1.day =30; 
  taster1.month = 10;
  taster1.year = 10;
  taster1.T_degC = 554444;
  root = Node_deletion(root, taster1);
   taster1.day =19; 
  taster1.month = 10;
  taster1.year = 10;
  taster1.T_degC = 554444;
  root = Node_deletion(root, taster1);

  printf("Preorder traversal of the constructed AVL"
         " tree is \n");
  preOrder(root); */
   

 
  return 0;
}