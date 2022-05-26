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
    Node->height = 0;  // new node is initially added at leaf
    return(Node);
}


int max(int left, int right) {

    if(left > right)
    {
      return  left ;

    }else if (left < right)
    {
        return  right ;
    }
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



 int compare_nodes(ocean_AVL key1 , ocean_AVL key2)
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

  int conditiondate = compare_nodes(key , treenode->key);

    if (conditiondate == 1 ){

        treenode->left  = insertion(treenode->left, key);

    }
     if (conditiondate == 2){

        treenode->right = insertion(treenode->right, key);

    }
    if (conditiondate == 0){
        treenode->left = insertion(treenode->left, key);
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
        printf("%d ", root->key.day);
        preOrder(root->left);
        preOrder(root->right);
    }
}


struct Tree_node* search(struct Tree_node* treenode , ocean_AVL key)
{
   int conditiondate = compare_nodes(key , treenode->key);

    if (conditiondate == 1 ){
      return search(treenode->left,key);
    }
     if (conditiondate == 2){
     return search(treenode->right,key);
    }
    if (conditiondate == 0 || treenode == NULL  ){
        return treenode;
    }
}

struct  Tree_node * find_max_inorder(struct Tree_node* treenode)
{
    
  struct Tree_node* node = treenode; 

    while (node->right != NULL)
        node = node->right;
 
    return node;

}

struct Tree_node * Node_deletion(struct Tree_node* treenode , ocean_AVL key)
{
  
  if (treenode == NULL){
        return treenode;
     }

  int conditiondate = compare_nodes( key , treenode->key);

    if (conditiondate == 1 ){
        treenode->left  =  Node_deletion(treenode->left, key);

    }
    if (conditiondate == 2){

        treenode->right =  Node_deletion(treenode->right, key);
       

    }
    if (conditiondate == 0) {
        
        if ((treenode->right == NULL || treenode->left== NULL ))
        {
             struct Tree_node  *temp_tree = treenode->left ? treenode->left : treenode->right;


            if(temp_tree == NULL){
                temp_tree = treenode;
                treenode = NULL;
            }else{
                *treenode = *temp_tree;
                free(temp_tree);
            }
            

        }
        else{

            struct Tree_node * temp_tree = find_max_inorder(treenode->left);

            treenode->key = temp_tree->key;

            treenode->left = Node_deletion(treenode->left, temp_tree->key);
        }
    }
    
 if (treenode == NULL){
  return treenode;
  }

 treenode->height =getheight(treenode);
 int balance = getBalance(treenode);

   if(balance > 1){
        // LL Rotation Case
        if(getBalance(treenode->left) ==1){
            return Right_Rotation(treenode);
        }
        // LR Rotation Case
        else{
            treenode->left = Left_Rotation(treenode->left);
            return Right_Rotation(treenode);
        }
    }
    else if(balance < -1){
        // RR Rotation Case
        if(getBalance(treenode->right) ==-1 ){
            return Left_Rotation(treenode);
        }
        // RL Rotation Case
        else{
            treenode->right = Right_Rotation(treenode->right);
            return Left_Rotation(treenode);
        }
    }

  return treenode;
}

int main()
{

  struct Tree_node *root = NULL;

 




  /* Constructing tree given in the above figure */
  ocean_AVL taster;
  taster.day =10;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 66666;
  root = insertion(root, taster);

  taster.day =20;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 554444;
  root = insertion(root, taster);
  
  
  taster.day =30;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);

   taster.day =40;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);
   taster.day =50;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);
   taster.day =25;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);


   taster.day =1;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);
    
   taster.day =22;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);
    
   taster.day =3;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);
   
   taster.day =555;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);
    
   taster.day =19;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);

   taster.day =19;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);

  /* taster.day =69;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster);

   taster.day =70;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 10.394999 ;
   root = insertion(root, taster);
    taster.day =66;
  taster.month = 10;
  taster.year = 10;
  taster.T_degC = 4444;
   root = insertion(root, taster); *\

   /* ocean_AVL seer;

 seer.day =70;
 seer.month = 10;
 seer.year = 10;

 struct Tree_node *ser = search(root,seer);
  printf("thelo kavlia \n");
   preOrder(ser);
    printf("%f",ser->key.T_degC); */
   

    printf("Preorder traversal of the constructed AVL"
         " tree is \n");
  preOrder(root);
     ocean_AVL taster1;
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
  preOrder(root);
   

 
  return 0;
}