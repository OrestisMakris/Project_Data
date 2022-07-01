#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

 // AVL part of the code

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


struct Tree_node* Dinsertion(struct Tree_node* treenode , ocean_AVL key)
{
    if (treenode == NULL){
        return(new_avl_Node(key));
    }


    if (key.T_degC < treenode->key.T_degC ){

        treenode->left  = Dinsertion(treenode->left, key);

    }else if (key.T_degC > treenode->key.T_degC){

        treenode->right = Dinsertion(treenode->right, key);

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
        printf("Date %d/%d/%d Temperature %0.4f \n", root->key.day , root->key.month ,root->key.year , root->key.T_degC);
    }
}

void print_inOrder(struct Tree_node *root)
{
    if(root != NULL)
    {
        print_inOrder(root->left);
        printf("Date %d/%d/%d Temperature  %0.4f\n", root->key.day , root->key.month ,root->key.year , root->key.T_degC);
        print_inOrder(root->right);
    }
}

void print_preOrder(struct Tree_node *root)
{
    if(root != NULL)
    {
        printf("Date %d/%d/%d Temperature  %0.4f \n", root->key.day , root->key.month ,root->key.year , root->key.T_degC);
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



// Chained Hash table part of the code



#define Buckets 250

typedef struct box {

    float T_degC;
    char date[11];
    struct box *next_cell;

}ocean_Cell;

typedef struct hash
{
    ocean_Cell *head;
    int  count;

}hashTable;

hashTable *hash_table = NULL ;


ocean_Cell * new_Cell(char *date , float T_degC)
{

    ocean_Cell *newCell;

    newCell = (ocean_Cell *)malloc(sizeof(ocean_Cell));

    newCell->T_degC = T_degC;
    strcpy(newCell->date, date);
    newCell->next_cell = NULL;

    return newCell;

}

int hashing_function ( char date[11])
{
    int sum = 0;

    for (int k = 0; k < 11; k++){
        sum = sum + date[k];
    }
    return  sum % Buckets ;
}


void Hinsertion(char *date , float T_degC)
{
    int i = hashing_function(date);

    ocean_Cell *newCell =  new_Cell(date,T_degC);

    if ( !hash_table[i].head){

        hash_table[i].head=newCell;
        hash_table[i].count =1;
        return;

    }

    newCell->next_cell = (hash_table[i].head);

    hash_table[i].head = newCell;
    hash_table[i].count++;
    return;

}

float searching(char *date)
{
    int index = hashing_function(date);

    ocean_Cell * search_hash ;
    search_hash = hash_table[index].head;

    while(search_hash != NULL)
    {
        if (strcmp(search_hash->date ,date) == 0) {

            return search_hash->T_degC;
        }

        search_hash = search_hash->next_cell;

    }
}


ocean_Cell *modification(char *date)
{
    int index = hashing_function(date);

    ocean_Cell * search_hash ;
    search_hash = hash_table[index].head;

    while(search_hash != NULL)
    {
        if (strcmp(search_hash->date ,date) == 0) {
            return search_hash;
        }
        search_hash = search_hash->next_cell;
    }
}


void printing() {
    ocean_Cell *print_hash;
    int i;
    for (i = 0; i < Buckets; i++) {
        if (hash_table[i].count == 0)
            continue;
        print_hash = hash_table[i].head;
        if (!print_hash)
            continue;
        while (print_hash != NULL) {
            printf(" Date %s ", print_hash->date);
            printf("Temperature %f \n", print_hash->T_degC);
            print_hash = print_hash->next_cell;
        }
    }
    return;
}

void deletion(char *date) {

    int Index = hashing_function(date);

    ocean_Cell  *temp_del ;
    ocean_Cell *delet;
    delet = hash_table[Index].head;
    temp_del = delet;

    while (delet != NULL) {

        if (strcmp(delet->date , date) == 0) {

            if (delet == hash_table[Index].head) {
                hash_table[Index].head = delet->next_cell;
            }
            else {
                temp_del->next_cell = delet->next_cell;
            }

            hash_table[Index].count--;
            free(delet);
            break;
        }
        temp_del = delet;
        delet = delet->next_cell;
    }
}

void open_csv_hashing(ocean_Cell *foceanarray) {
    FILE *fptr2 = fopen("C:\\Users\\Orestis\\Downloads\\ocean.csv", "r");


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
                    strcpy(foceanarray[i].date ,data_values);
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
}


int main(){


    int case_1;
    int case_2;
    int case_3;
    struct Tree_node *root = NULL;
    ocean_AVL foceanarray[1406];
    hash_table = (hashTable *) calloc(Buckets, sizeof(hashTable));
    ocean_Cell Hfoceanarray[1406];

    do{

        printf("Type 1 to load the csv file with the date in a  AVL Tree data structure \n");
        printf("Type 2 o load the csv file with the date in a Chained Hash table \n");
        printf("Type 0 Exit Program\n");
        scanf("%d", &case_1);


        switch(case_1){

            case 0:
                break;
            case 1:

                do {
                    printf("Type 1 to load the AVL Tree data structure based on Date  \n");
                    printf("Type 2 to load the AVL Tree data structure based on Temperature \n");
                    printf("Type 0 Exit Program\n");
                    scanf("%d", &case_2);

                    switch(case_2){
                        case 0:
                            break;
                        case 1:

                            open_csv(foceanarray);

                            for (int m = 0; m < 1405; m++) {
                                root = insertion(root, foceanarray[m]);
                            }

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

                                scanf("%d", &case_3);

                                switch (case_3) {
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

                                        struct Tree_node *ser ;

                                        printf("Enter Day: \n ");
                                        scanf("%d", &temp.day);
                                        printf("Enter Month: \n");
                                        scanf("%d", &temp.month);
                                        printf("Enter Year: \n");
                                        scanf("%d", &temp.year);

                                        ser = search(root, temp);

                                        if (ser != NULL) {
                                            printf("Value found Date %d/%d/%d Temperature %0.4f \n", temp.day, temp.month,temp.year ,ser->key.T_degC);
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

                                        ocean_AVL del ;

                                        printf("Enter Day: \n");
                                        scanf("%d", &del.day);
                                        printf("Enter Month: \n");
                                        scanf("%d", &del.month);
                                        printf("Enter Year: \n");
                                        scanf("%d", &del.year);

                                        root = Node_deletion(root, del);
                                        break;

                                    case 7:
                                        system("cls");
                                        break;

                                    default:
                                        printf("Enter Proper Option number \n");
                                }

                            } while (case_3 != 0);

                            break;
                        case 2:

                            open_csv(foceanarray);

                            for (int m = 0; m < 1405; m++) {
                                root = Dinsertion(root, foceanarray[m]);
                            }

                            do {

                                ocean_AVL temp;

                                printf("Type 1 to print the Inorder represation of the tree \n");
                                printf("Type 2 to print the Preorder represation of the tree\n");
                                printf("Type 3 to print the Postorder represation of the tree\n");
                                printf("Type 4 Find the node with the Minimum Temperature in the AVL \n");
                                printf("Type 5 Find the node with the Highest Temperature in the AVL \n");
                                printf("Type 6  Clear Screen\n");
                                printf("Type 0 Exit Program\n");

                                scanf("%d", &case_3);

                                switch (case_3) {
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

                            } while (case_3 != 0);

                        default:
                            printf("Enter Proper Option number \n");
                    }

                }while  (case_2 != 0);
                break;
            case 2:

                
                open_csv_hashing(Hfoceanarray);

                for (int m = 0; m < 1406; m++) {

                    Hinsertion(Hfoceanarray[m].date,Hfoceanarray[m].T_degC );
                }

                do {


                    printf("Type 1 to print the Chained Hash table  \n");
                    printf("Type 2 search the Chained Hash table \n");
                    printf("Type 3 Change the temperature giving a specific Data \n");
                    printf("Type 4  Delete a specific Date from the Chained Hash table  \n");
                    printf("Type 5  Clear Screen\n");
                    printf("Type 6 Exit Program\n");

                    scanf("%d", &case_3);

                    switch (case_3) {
                        case 0:
                            break;
                        case 1:

                            printing();

                            break;

                        case 2:

                            printf("Search \n");
                            printf("Enter the date of the temperature you want to find in the Chained Hash table : \n ");
                            printf("Give the date in the following format month 00 /day 00 /year 0000 : \n ");
                            char *search_date[11];

                            printf("Enter :  ");
                            scanf("%s", search_date);

                            float myf = 0;
                            myf = searching(search_date);

                            printf("Value found %0.4f \n", myf);


                            break;

                        case 3:

                            printf("Modification \n");
                            printf("Enter the date of the node you want to modify the temperature: \n");

                            printf("Give the date in the following format month 00 /day 00 /year 0000 : \n ");

                            char *mod_date[11];
                            float new_temp = 0;

                            printf("Enter: ");
                            scanf("%s", mod_date);

                            printf("Enter the new temperature: ");
                            scanf("%f", &new_temp);

                            modification(mod_date)->T_degC = new_temp;

                            break;

                        case 4:

                            printf("Enter the date of the temperature you want to DELETE in the Chained Hash table : \n");

                            printf("Give the date in the following format month 00 /day 00 /year 0000 : \n ");

                            char date[11] ;
                            printf("Enter:  ");
                            scanf("%s", date);

                            deletion(date);
                            break;

                        case 5:

                            system("cls");
                            break;

                        default:
                            printf("Enter Proper Option number \n");
                    }

                } while (case_3 != 0);
                break;
            default:
                printf("Enter Proper Option number \n");
        }

    }while (case_1 != 0);

    return 0;
}