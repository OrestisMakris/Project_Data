#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

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

struct fdata
{
    char date[11];
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
        treenode ;
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

void print_PostOrder(struct Tree_node *root)
{
    if(root != NULL)
    {
        print_PostOrder(root->left);
        print_PostOrder(root->right);
        printf("Date %d/%d/%d Temperature %0.4f \n", root->key.day , root->key.month ,root->key.year , root->key.T_degC);
    }
}

void print_inOrder(struct Tree_node *root)
{
    if(root != NULL)
    {
        print_inOrder(root->left);
        printf("Date %d/%d/%d Temperature  0.4f\n", root->key.day , root->key.month ,root->key.year , root->key.T_degC);
        print_inOrder(root->right);
    }
}

void print_preOrder(struct Tree_node *root)
{
    if(root != NULL)
    {
        printf("Date %d/%d/%d Temperature  0.4f \n", root->key.day , root->key.month ,root->key.year , root->key.T_degC);
        print_preOrder(root->left);
        print_preOrder(root->right);
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
    return  treenode;
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


void open_csv ( ocean_AVL *foceanarray) {
    FILE *fptr2 = fopen("C:\\Users\\Orestis\\Downloads\\ocean.csv", "r");
    struct fdata string_dates[1406];

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

int main(){
    struct Tree_node *root = NULL;
    ocean_AVL foceanarray[1406];

    open_csv(foceanarray);

    for (int m = 0; m < 1405; m++) {
        root = insertion(root, foceanarray[m]);
    }

    int cases;

    do {

        ocean_AVL temp;

        printf("Type 1 to print the Inorder represation of the tree \n");
        printf("Type 2 to print the Preorder represation of the tree\n");
        printf("Type 3 to print the Postorder represation of the tree\n");
        printf("Type 4 Search the AVL tree for a specific node\n");
        printf("Type 5 Change the temperature giving a specific Data\n");
        printf("Type 6 Delete a specific Node\n");
        printf("Type 7  Clear Screen\n");
        printf("Type 0 Exit Program\n");

        scanf("%d", &cases);

        switch (cases) {
            case 0:
                break;
            case 1:

                printf("Print the Inorder \n");

                print_inOrder(root);

                break;

            case 2:

                printf("Print the Preorder \n");

                print_preOrder(root);

                break;

            case 3:

                printf("Print the Postorder\n");

                print_PostOrder(root);

                break;

            case 4:

                printf("Search \n");
                printf("Enter the date of the node you want to search in the AVL: \n ");

                struct Tree_node *ser;

                printf("Enter Day: \n ");
                scanf("%d", &temp.day);
                printf("Enter Month: \n");
                scanf("%d", &temp.month);
                printf("Enter Year: \n");
                scanf("%d", &temp.year);

                ser = search(root, temp);

                if (ser != NULL) {
                    printf("Value found 0.4f \n", ser->key.T_degC);
                } else {
                    printf("Value NOT found\n");
                }

                break;

            case 5:

                printf("Modification \n");
                printf("Enter the date of the node you want to modify the temperature: \n");

                float temper = 0;

                printf("Enter Day: \n");
                scanf("%d", &temp.day);
                printf("Enter Month: \n");
                scanf("%d", &temp.month);
                printf("Enter Year: \n");
                scanf("%d", &temp.year);
                printf("Enter the new temperature: ");
                scanf("%f", &temper);

                search(root, temp)->key.T_degC = temper;
                break;

            case 6:
                printf("Enter the date of the node you want to DELETE in the AVL: \n");


                printf("Enter Day: \n");
                scanf("%d", &temp.day);
                printf("Enter Month: \n");
                scanf("%d", &temp.month);
                printf("Enter Year: \n");
                scanf("%d", &temp.year);

                root = Node_deletion(root, temp);
                break;

            case 7:
                system("cls");
                break;

            default:
                printf("Enter Proper Option number \n");
        }

    } while (cases != 0);
    return 0;
}
