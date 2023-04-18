//1190880_Qays Safa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100
#define HASH_MAP_SIZE 100

struct Node
{

    char *name;
    char *gender;
    char *admission_date;
    char *dob;
    char *illness;
    char *address;
    char *blood_type;

    struct Node *left;
    struct Node *right;
    int height;
};

struct HashNode{
    char *name;
    char *gender;
    char *admission_date;
    char *dob;
    char *illness;
    char *address;
    char *blood_type;
};



void print_data(struct Node *node);
struct Node *RotateRight(struct Node *y);
struct Node *RotateLeft(struct Node *x);
int GetBalanceFactor(struct Node *N);
struct Node *NewNode(char *name, char *gender,
                     char *admission_date, char *dob, char *illness, char *address, char *blood_type);
int Comparekeys(char *name, char *name2);
struct Node *FindMinValueNode(struct Node *node);
struct Node *InsertNode(struct Node *node, char *name, char *gender,
                         char *admission_date, char *dob, char *illness, char *address, char *blood_type);
struct Node *UpdateData(struct Node *node);
struct Node *DeleteNode(struct Node *node, char *name);
char *GetData(char *input_line, int input_num);
struct Node *InsertNewData(struct Node *node);
struct Node *SearchNode(struct Node *root, struct Node *node, char *name);
void PrintSameIllness(struct Node *node, char *illness);
void SaveData(struct Node *node, FILE *file_pointer);
int HashFunction(char *name);
int InsertNewRecordInHash(struct HashNode *array,int size);
int InsertInHash(struct HashNode *array, char *name, char *gender, char *admission_date, char *dob, char *illness, char *address, char *blood_type, int size);
void SearchHash(struct HashNode* array);
int DeleteHash(struct HashNode *array,int size, char *name);
void SaveHash(struct HashNode *array);


FILE *file_pointer;
int main()
{
    struct Node *node = NULL;

    FILE *stream = fopen("patients.txt", "r");

    char line[1024];
    int num_lines = 0;
    char *name, *gender, *admission_date, *dob, *illness, *address, *blood_type;
    while (fgets(line, 1024, stream))
    {

        if (num_lines == 0)
        {
            num_lines++;
            continue;
        }

        char *tmp = strdup(line);
        name = strdup(GetData(tmp, 1));
        free(tmp);

        tmp = strdup(line);
        gender = strdup(GetData(tmp, 2));
        free(tmp);

        tmp = strdup(line);
        admission_date = strdup(GetData(tmp, 3));
        free(tmp);

        tmp = strdup(line);
        dob = strdup(GetData(tmp, 4));
        free(tmp);

        tmp = strdup(line);
        illness = strdup(GetData(tmp, 5));
        free(tmp);

        tmp = strdup(line);
        address = strdup(GetData(tmp, 6));
        free(tmp);

        tmp = strdup(line);
        blood_type = strdup(GetData(tmp, 7));
        free(tmp);

        node = InsertNode(node, name, gender, admission_date, dob, illness, address, blood_type);
    }
    fclose(stream);

    int user_input;
    char buffer[BUFFER_SIZE];

    while (1)
    {
        printf("\t\t--------- Patients table ----------\n");
        printf("\t 1 to insert a new patient\n");
        printf("\t 2 to search a patient\n");
        printf("\t 3 to view all patient data\n");
        printf("\t 4 to view all patients who have same illness\n");
        printf("\t 5 to save all patients data & enter Hash sections\n");
        printf("\n Enter your choice (1, 2, 3, 4, 5 and 0 to exit): ");

        fgets(buffer, BUFFER_SIZE, stdin);
        sscanf(buffer, "%d", &user_input);

        switch (user_input)
        {
        case 1:
            node = InsertNewData(node);
            break;
        case 2:
            printf("Enter the name of new patient: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            name = strdup(buffer);

            name[strcspn(name, "\n")] = 0;
            node = SearchNode(node, node, name);
            break;
        case 3:
            print_data(node);
            printf("\n\n");
            break;
        case 4:
            printf("Enter the illness to search for: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            illness = strdup(buffer);
            illness[strcspn(illness, "\n")] = 0;
            PrintSameIllness(node, illness);
            break;
        case 5:
            file_pointer = fopen("patients_hash.data", "w");
            //Header
            fputs("Patient Name#Gender#Date of admission#Date of birth#Illness#Address (city)#Blood type\n",file_pointer);
            SaveData(node, file_pointer);
            fclose(file_pointer);

            struct HashNode *array = NULL;
    int size=0;

    array = (struct HashNode*) malloc( HASH_MAP_SIZE * sizeof(struct HashNode));
    for(int j =0; j<HASH_MAP_SIZE;j++){
            array[j].name = NULL;
    }

    FILE *file_pointer = fopen("patients_hash.data", "r");

    char line[1000];
    int num_lines = 0;
    char *name, *gender, *admission_date, *dob, *illness, *address, *blood_type;
    while (fgets(line, 1000, file_pointer))
    {
        if (num_lines == 0)
        {
            num_lines++;
            continue;
        }

        char *tmp = strdup(line);
        name = strdup(GetData(tmp, 1));
        free(tmp);

        tmp = strdup(line);
        gender = strdup(GetData(tmp, 2));
        free(tmp);

        tmp = strdup(line);
        admission_date = strdup(GetData(tmp, 3));
        free(tmp);

        tmp = strdup(line);
        dob = strdup(GetData(tmp, 4));
        free(tmp);

        tmp = strdup(line);
        illness = strdup(GetData(tmp, 5));
        free(tmp);

        tmp = strdup(line);
        address = strdup(GetData(tmp, 6));
        free(tmp);

        tmp = strdup(line);
        blood_type = strdup(GetData(tmp, 7));
        free(tmp);

        size = InsertInHash(array, name, gender, admission_date, dob, illness, address, blood_type,size);
    }
    fclose(file_pointer);

    int user_input;
    char buffer[BUFFER_SIZE];
    while (1)
    {

        printf("\n\n\t\t!---------Hash Table---------!\n");
        printf("\t 1 to Print hashed table (i.e., print the entire table to the screen including empty spots).\n");
        printf("\t 2 to Print out table size. \n");
        printf("\t 3 to Print out the used hash function.\n");
        printf("\t 4 to Insert a new record into the hash table.\n");
        printf("\t 5 to Search for a specific patient.\n");
        printf("\t 6 to Delete a specific record. \n");
        printf("\t 7 to Save hash table back to file.\n");
       printf("\nEnter your choice (1, 2, 3, 4, 5,6,7 and 0 to exit): ");

        fgets(buffer, BUFFER_SIZE, stdin);
        sscanf(buffer, "%d", &user_input);
       int i = 0;
        switch (user_input)
        {
        case 1:

    while (i <HASH_MAP_SIZE)
   {
        if(array[i].name == NULL)
            printf("\n");
        else{
         printf("%s %s %s %s %s %s %s\n",array[i].name,array[i].gender,array[i].admission_date,array[i].dob,array[i].illness,array[i].address,array[i].blood_type);
        }

        i++;
    }
            break;
        case 2:
            printf("\n\nThe Total size hash table is: %d\n",HASH_MAP_SIZE);
            printf("The size of table is %d:\n",size);
            break;
        case 3:
            printf("\nThis hash function works by converting each character of name to integer\n");
            printf("Those values are added up and then a modulo operation by max size returns key\n");
            printf("Collisions are handled by linear hashing\n");
            printf("\nThe hash function is:\n\n");
            printf("int hash_function(char *name){\n");
            printf("   int key = 0;\n");
            printf("   int temp=0;\n");
            printf("   int len = strlen(name);\n");
            printf("   for(int i=0; i<len ;i++){\n");
            printf("       temp = name[i];\n");
            printf("       key += temp;}\n");
             printf("    return key (mod) 100 ;}\n"); // I wrote the word Mod instead of (%) here just to avoid the warning.
            printf("\n\n");
            break;
        case 4:
        size = InsertNewRecordInHash(array,size);

            break;
        case 5:
             printf("Enter the name of patient: ");
            SearchHash(array);
            break;
        case 6:
            printf("Enter the name of patient you want to delete: ");

          fgets(buffer, BUFFER_SIZE, stdin);
         char *name = strdup(buffer);
         name[strcspn(name, "\n")] = 0;
         DeleteHash(array,size,name);
            break;
        case 7:
            SaveHash(array);
            printf("save done");
            break;
        case 0:
            return 0;
        }
    }
            break;
        case 0:
            return 0;
        }
    }
}

void print_data(struct Node *node) //Function to print date.
{
    if (node != NULL)
    {
        printf("%s ", node->name);
        printf("%s ", node->gender);
        printf("%s ", node->admission_date);
        printf("%s ", node->dob);
        printf("%s ", node->illness);
        printf("%s ", node->address);
        printf("%s \n\n", node->blood_type);

        print_data(node->left);
        print_data(node->right);
    }
}

int get_height(struct Node *N) //Function to get height.
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max_of_int(int a, int b)
{
    return (a > b) ? a : b;
}

struct Node *RotateRight(struct Node *y) //Function to rotate right.
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max_of_int(get_height(y->left), get_height(y->right)) + 1;
    x->height = max_of_int(get_height(x->left), get_height(x->right)) + 1;

    return x;
}

struct Node *RotateLeft(struct Node *x) //Function to rotate left.
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max_of_int(get_height(x->left), get_height(x->right)) + 1;
    y->height = max_of_int(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

int GetBalanceFactor(struct Node *N) //Function to get balance factor .

{
    if (N == NULL)
        return 0;
    return get_height(N->left) - get_height(N->right);
}

struct Node *NewNode(char *name, char *gender,
                     char *admission_date, char *dob, char *illness, char *address, char *blood_type)
{ //Function to create a new node .

    struct Node *node = (struct Node *)
        malloc(sizeof(struct Node));

    node->name = malloc(sizeof(char *) * strlen(name));
    node->name = name;

    node->gender = malloc(sizeof(char *) * strlen(gender));
    node->gender = gender;

    node->admission_date = malloc(sizeof(char *) * strlen(admission_date));
    node->admission_date = admission_date;

    node->dob = malloc(sizeof(char *) * strlen(dob));
    node->dob = dob;

    node->illness = malloc(sizeof(char *) * strlen(illness));
    node->illness = illness;

    node->address = malloc(sizeof(char *) * strlen(address));
    node->address = address;

    node->blood_type = malloc(sizeof(char *) * strlen(blood_type));
    node->blood_type = blood_type;

    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

int Comparekeys(char *name, char *name2) //Function to compare between two keys .
{
    int val = strcmp(name, name2);
    return val;
}

struct Node *FindMinValueNode(struct Node *node) //Function to find min value node .
{
    struct Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node *InsertNode(struct Node *node, char *name, char *gender,
                         char *admission_date, char *dob, char *illness, char *address, char *blood_type)
{ //Function to insert data .

    if (node == NULL)
    {
        return NewNode(name, gender, admission_date, dob, illness, address, blood_type);
    }

    int compare_value = Comparekeys(name, node->name);

    if (compare_value < 0)
    {
        node->left = InsertNode(node->left, name, gender, admission_date, dob, illness, address, blood_type);
    }
    else if (compare_value > 0)
    {
        node->right = InsertNode(node->right, name, gender, admission_date, dob, illness, address, blood_type);
    }
    else
        return node;

    node->height = 1 + max_of_int(get_height(node->left),
                                  get_height(node->right));

    int balance = GetBalanceFactor(node);

    if (balance > 1 && Comparekeys(name, node->left->name) < 0)
        return RotateRight(node);

    if (balance < -1 && Comparekeys(name, node->right->name) > 0)
        return RotateLeft(node);

    if (balance > 1 && Comparekeys(name, node->left->name) > 0)
    {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }

    if (balance < -1 && Comparekeys(name, node->left->name) < 0)
    {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }
    return node;
}

struct Node *UpdateData(struct Node *node) //Function to update data .
{
    int user_input;
    char *value;
    char buffer[BUFFER_SIZE];

    printf("\n\n");
    printf(" 1 to update Gender\n");
    printf(" 2 to update admission date\n");
    printf(" 3 to update date of birth\n");
    printf(" 4 to update illness\n");
    printf(" 5 to update address\n");
    printf(" 6 to update blood type\n");
    printf("\nEnter your choice (1, 2, 3, 4, 5,6,7 and 0 to cancel): ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sscanf(buffer, "%d", &user_input);

    switch (user_input)
    {
    case 1:
        printf("Enter the new gender\n");
        fgets(buffer, BUFFER_SIZE, stdin);
        value = strdup(buffer);
        value[strcspn(value, "\n")] = 0;
        free(node->gender);
        node->gender = malloc(sizeof(char *) * strlen(value));
        node->gender = value;
        break;
    case 2:
        printf("Enter the new admission date\n");
        fgets(buffer, BUFFER_SIZE, stdin);
        value = strdup(buffer);
        value[strcspn(value, "\n")] = 0;
        free(node->admission_date);
        node->admission_date = malloc(sizeof(char *) * strlen(value));
        node->admission_date = value;
        break;
    case 3:
        printf("Enter the new date of birth\n");
        fgets(buffer, BUFFER_SIZE, stdin);
        value = strdup(buffer);
        value[strcspn(value, "\n")] = 0;
        free(node->dob);
        node->dob = malloc(sizeof(char *) * strlen(value));
        node->dob = value;
        break;
    case 4:
        printf("Enter the new illness\n");
        fgets(buffer, BUFFER_SIZE, stdin);
        value = strdup(buffer);
        value[strcspn(value, "\n")] = 0;
        free(node->illness);
        node->illness = malloc(sizeof(char *) * strlen(value));
        node->illness = value;
        break;
    case 5:
        printf("Enter the new address\n");
        fgets(buffer, BUFFER_SIZE, stdin);
        value = strdup(buffer);
        value[strcspn(value, "\n")] = 0;
        free(node->address);
        node->address = malloc(sizeof(char *) * strlen(value));
        node->address = value;
        break;
    case 6:
        printf("Enter the new blood type\n");
        fgets(buffer, BUFFER_SIZE, stdin);
        value = strdup(buffer);
        value[strcspn(value, "\n")] = 0;
        free(node->blood_type);
        node->blood_type = malloc(sizeof(char *) * strlen(value));
        node->blood_type = value;
        break;
    }

    return node;
}

struct Node *DeleteNode(struct Node *node, char *name) //Function to delete data .
{

    if (node == NULL)
        return node;

    if (Comparekeys(name, node->name) < 0)
        node->left = DeleteNode(node->left, name);

    else if (Comparekeys(name, node->name) > 0)
        node->right = DeleteNode(node->right, name);

    else
    {

        if ((node->left == NULL) || (node->right == NULL))
        {
            struct Node *temp = node->left ? node->left : node->right;

            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;

            free(temp->name);
            free(temp->gender);
            free(temp->admission_date);
            free(temp->dob);
            free(temp->illness);
            free(temp->address);
            free(temp->blood_type);

            free(temp);
        }
        else
        {
            struct Node *temp = FindMinValueNode(node->right);

            node->name = temp->name;
            node->gender = temp->gender;
            node->admission_date = temp->admission_date;
            node->dob = temp->dob;
            node->illness = temp->illness;
            node->address = temp->address;
            node->blood_type = temp->blood_type;

            node->right = DeleteNode(node->right, temp->name);
        }
    }

    if (node == NULL)
        return node;

    node->height = 1 + max_of_int(get_height(node->left),
                                  get_height(node->right));

    int balance = GetBalanceFactor(node);
    if (balance > 1 && GetBalanceFactor(node->left) >= 0)
        return RotateRight(node);

    if (balance > 1 && GetBalanceFactor(node->left) < 0)
    {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }

    if (balance < -1 && GetBalanceFactor(node->right) <= 0)
        return RotateLeft(node);

    if (balance < -1 && GetBalanceFactor(node->right) > 0)
    {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }

    return node;
};


char *GetData(char *input_line, int input_num)
{
     char *token;
    for (token = strtok(input_line, "#"); token && *token; token = strtok(NULL, "#\n"))
    {
        if (!--input_num)
            return token;
    }
    return NULL;
}

struct Node *InsertNewData(struct Node *node) //Function to insert new data .
{

    char buffer[BUFFER_SIZE];

    char *name, *gender, *admission_date, *dob, *illness, *address, *blood_type;

    printf("Enter the name of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    name = strdup(buffer);
    name[strcspn(name, "\n")] = 0;

    printf("Enter the gender of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    gender = strdup(buffer);
    gender[strcspn(gender, "\n")] = 0;

    printf("Enter the admission date of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    admission_date = strdup(buffer);
    admission_date[strcspn(admission_date, "\n")] = 0;

    printf("Enter the date of birth of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    dob = strdup(buffer);
    dob[strcspn(dob, "\n")] = 0;

    printf("Enter the illness of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    illness = strdup(buffer);
    illness[strcspn(illness, "\n")] = 0;

    printf("Enter the address of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    address = strdup(buffer);
    address[strcspn(address, "\n")] = 0;

    printf("Enter the blood type of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    blood_type = strdup(buffer);
    blood_type[strcspn(blood_type, "\n")] = 0;

    return InsertNode(node, name, gender, admission_date, dob, illness, address, blood_type);
}
struct Node *SearchNode(struct Node *root, struct Node *node, char *name)
//Function to search in Patients and after that make a delete or update if user need
{
    int user_input;
    char buffer[BUFFER_SIZE];

    if (node == NULL)
        return node;
    int compare_value = Comparekeys(name, node->name);
    if (compare_value == 0)
    {

        printf("Patient Data found!\n\n");
        printf("%s ", node->name);
        printf("%s ", node->gender);
        printf("%s ", node->admission_date);
        printf("%s ", node->dob);
        printf("%s ", node->illness);
        printf("%s ", node->address);
        printf("%s \n\n", node->blood_type);

        while (1)
        {
            printf("Enter 1 to update data\n");
            printf("Enter 2 to delete data\n");
            printf("Enter 0 to return to last menu\n");

            fgets(buffer, BUFFER_SIZE, stdin);
            sscanf(buffer, "%d", &user_input);

            switch (user_input)
            {
            case 1:
                node = UpdateData(node);
                return root;
            case 2:
                DeleteNode(root, node->name);
                return root;
            case 0:
                return root;
            }
        }
    }
    else if (compare_value < 0)
        return SearchNode(root, node->left, name);
    else
        return SearchNode(root, node->right, name);
}

void PrintSameIllness(struct Node *node, char *illness) //Function to print Patients that have same illness
{

    if (node == NULL)
    {
        return;
    }
    if (Comparekeys(node->illness, illness) == 0)
    {
        printf("%s ", node->name);
        printf("%s ", node->gender);
        printf("%s ", node->admission_date);
        printf("%s ", node->dob);
        printf("%s ", node->illness);
        printf("%s ", node->address);
        printf("%s \n\n", node->blood_type);
    }

    PrintSameIllness(node->left, illness);
    PrintSameIllness(node->right, illness);
}

void SaveData(struct Node *node, FILE *file_pointer) //Function to save date in file .
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        fputs(node->name, file_pointer);
        fputs("#", file_pointer);
        fputs(node->gender, file_pointer);
        fputs("#", file_pointer);
        fputs(node->admission_date, file_pointer);
        fputs("#", file_pointer);
        fputs(node->dob, file_pointer);
        fputs("#", file_pointer);
        fputs(node->illness, file_pointer);
        fputs("#", file_pointer);
        fputs(node->address, file_pointer);
        fputs("#", file_pointer);
        fputs(node->blood_type, file_pointer);
        fputs("#\n", file_pointer);
    }
    SaveData(node->left, file_pointer);
    SaveData(node->right, file_pointer);
}

int HashFunction(char *name){
    int key = 0;
    int temp=0;
    int len = strlen(name);
    for(int i=0; i<len ;i++){

        temp = name[i];
        key += temp;
    }
    return key % HASH_MAP_SIZE;
}

int InsertInHash(struct HashNode *array, char *name, char *gender, char *admission_date, char *dob, char *illness, char *address, char *blood_type, int size){
//Function to insert data in hash .
    int key = HashFunction(name);
    for(int i=key;i<HASH_MAP_SIZE;i++){
        if(array[i].name == NULL){

            array[i].name = malloc(sizeof(char *) * strlen(name));
            array[i].name = name;

            array[i].gender = malloc(sizeof(char *) * strlen(gender));
            array[i].gender = gender;

            array[i].admission_date = malloc(sizeof(char *) * strlen(admission_date));
            array[i].admission_date = admission_date;

            array[i].dob = malloc(sizeof(char *) * strlen(dob));
            array[i].dob = dob;

            array[i].illness = malloc(sizeof(char *) * strlen(illness));
            array[i].illness = illness;

            array[i].address = malloc(sizeof(char *) * strlen(address));
            array[i].address = address;

            array[i].blood_type = malloc(sizeof(char *) * strlen(blood_type));
            array[i].blood_type = blood_type;

            size++;
            return size;
        }
    }
    printf("Err! Collision occurred when trying to insert.\n");
    return size;

};

int InsertNewRecordInHash(struct HashNode *array,int size){//Function to insert new record in hash if user need .

    char buffer[BUFFER_SIZE];
    char *name, *gender, *admission_date, *dob, *illness, *address, *blood_type;

    printf("Enter the name of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    name = strdup(buffer);
    name[strcspn(name, "\n")] = 0;

    printf("Enter the gender of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    gender = strdup(buffer);
    gender[strcspn(gender, "\n")] = 0;

    printf("Enter the admission date of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    admission_date = strdup(buffer);
    admission_date[strcspn(admission_date, "\n")] = 0;

    printf("Enter the date of birth of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    dob = strdup(buffer);
    dob[strcspn(dob, "\n")] = 0;

    printf("Enter the illness of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    illness = strdup(buffer);
    illness[strcspn(illness, "\n")] = 0;

    printf("Enter the address of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    address = strdup(buffer);
    address[strcspn(address, "\n")] = 0;

    printf("Enter the blood type of new patient: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    blood_type = strdup(buffer);
    blood_type[strcspn(blood_type, "\n")] = 0;

    return InsertInHash(array, name, gender, admission_date, dob, illness, address, blood_type,size);

}
int DeleteHash(struct HashNode *array,int size, char *name){ //Function to delete hash data .

    int key = HashFunction(name);
    for(int i=key;i<HASH_MAP_SIZE;i++){
        if(array[i].name==NULL){
            printf("\nNo Record of that patient\n");
            return size;
        }
        if(Comparekeys(name,array[i].name)==0){

            free(array[i].name);
            free(array[i].gender);
            free(array[i].admission_date);
            free(array[i].dob);
            free(array[i].illness);
            free(array[i].address);
            free(array[i].blood_type);

            array[i].name = NULL;

            printf("\n\tDelet done\n");
            size--;
            return size;
        }

    }

    return size;
}

void SearchHash(struct HashNode* array){//Function to search in hash data .

    char buffer[BUFFER_SIZE];
    char *name;
    fgets(buffer, BUFFER_SIZE, stdin);
    name = strdup(buffer);
    name[strcspn(name, "\n")] = 0;

    int key = HashFunction(name);

    for(int i=key;i<HASH_MAP_SIZE;i++){
        if(array[i].name==NULL){
            printf("\nNot found!\n");
            return;
        }
        if(Comparekeys(name,array[i].name)==0){
            printf("%s %s %s %s %s %s %s\n",array[i].name,array[i].gender,array[i].admission_date,array[i].dob,array[i].illness,array[i].address,array[i].blood_type);
            return;
        }
    }
    return;
}


void SaveHash(struct HashNode *array) //Function to save hash data to file .
{
    FILE *file_pointer = fopen("patients_hash.data", "w");

    for(int i=0;i<HASH_MAP_SIZE;i++){
        if(array[i].name==NULL)
            continue;
        else{
            fputs(array[i].name, file_pointer);
            fputs("#", file_pointer);
            fputs(array[i].gender, file_pointer);
            fputs("#", file_pointer);
            fputs(array[i].admission_date, file_pointer);
            fputs("#", file_pointer);
            fputs(array[i].dob, file_pointer);
            fputs("#", file_pointer);
            fputs(array[i].illness, file_pointer);
            fputs("#", file_pointer);
            fputs(array[i].address, file_pointer);
            fputs("#", file_pointer);
            fputs(array[i].blood_type, file_pointer);
            fputs("#\n", file_pointer);
            fputs("---------------------\n", file_pointer);
        }
    }
    fclose(file_pointer);
}


