#include <stdio.h>
#include <string.h>
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
    ocean_AVL duplicates[40];
    int counter;
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
    Node->counter=0;
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

    }if (key.T_degC == treenode->key.T_degC){
        treenode->duplicates[treenode->counter].day = key.day;
        treenode->duplicates[treenode->counter].month = key.month;
        treenode->duplicates[treenode->counter].year = key.year;
        (treenode->counter)++;
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


void print_PostOrder(struct Tree_node *root)
{
    if(root != NULL)
    {
        print_PostOrder(root->left);
        print_PostOrder(root->right);
        printf("Date %d/%d/%d Temperature %f \n", root->key.day , root->key.month ,root->key.year , root->key.T_degC);
    }
}

void print_inOrder(struct Tree_node *root)
{
    if(root != NULL)
    {
        print_inOrder(root->left);
        printf("Date %d/%d/%d Temperature  %f\n", root->key.day , root->key.month ,root->key.year , root->key.T_degC);
        print_inOrder(root->right);
    }
}

void print_preOrder(struct Tree_node *root)
{
    if(root != NULL)
    {
        printf("Date %d/%d/%d Temperature  %f \n", root->key.day , root->key.month ,root->key.year , root->key.T_degC);
        print_preOrder(root->left);
        print_preOrder(root->right);
    }
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

struct  Tree_node * find_max_value(struct Tree_node* treenode)
{

    struct Tree_node* node = treenode;

    while (node->right != NULL)
        node = node->right;

    return(node);

}

struct  Tree_node * find_min_value(struct Tree_node* treenode)
{
    struct Tree_node* node = treenode;


    while (node->left != NULL)
    {
        node = node->left;
    }
    return(node);
}

int main() {
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
        printf("Type 4 Find the nodes with the Minimum Temperature in the AVL \n");
        printf("Type 5 Find the nodes with the Highest Temperature in the AVL \n");
        printf("Type 6  Clear Screen\n");
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
                printf("The node with the Minimum Temperature in the AVL is \n");
                struct Tree_node *min = find_min_value(root);
                printf(" The min temperature is %0.4f  C and it is found on the following dates\n ", min->key.T_degC);
                printf("%i / %i / %i \n", min->key.day, min->key.month, min->key.year);
                for(int j =0;j<min->counter; j++)
                {
                    printf("%i / %i / %i " , min->duplicates[j].day  , min->duplicates[j].month  , min->duplicates[j].year );
                    printf("\n");
                }
                break;

            case 5:
                printf("The node with the Highest Temperature in the AVL is \n");
                struct Tree_node *max = find_max_value(root);
                printf(" The max temperature is %0.4f  C and it is found on the following dates\n ", max->key.T_degC);
                printf("%i / %i / %i \n", max->key.day, max->key.month, max->key.year);
                for(int j =0;j<max->counter; j++)
                {
                    printf("%i / %i / %i " , max->duplicates[j].day  , max->duplicates[j].month  , max->duplicates[j].year );
                    printf("\n");
                }
                break;


            case 6:
                system("cls");
                break;

            default:
                printf("Enter Proper Option number \n");
        }

    } while (cases != 0);
    return 0;
}