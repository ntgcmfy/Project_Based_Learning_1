#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1000

struct Node{
    double data;
    struct Node *next;
};


//Hàm đếm số hàng và số cột của ma trận.
void countRows_ColumnsfromFile(char *filename,int *rows, int *columns){
    FILE *fp;
    fp = freopen(filename,"r",stdin);

    char c;
    *rows = 0;
    *columns = 0;
    c = getc(fp);
    while (c != EOF){
        if(c == '\n'){
            (*rows)++;
        }
        c = getc(fp);
    }
    //Tới cuối file thì tính thêm 1 hàng.
    (*rows)++;
    //Đưa con trỏ về đầu file
    rewind(fp);
    //Đếm số cột
    while (c!= '\n'){
        if(c == ' '){
            (*columns)++;
        }
    c = getc(fp);
    }
    //Tới cuối hàng thì tính thêm một cột.
    (*columns)++;
    fclose(fp);
}

//Tạo ra một Node mới chứa dữ liệu cần chèn.    
struct Node* createNode( double data ) {
    struct Node* node = (struct Node *) malloc(sizeof(struct Node));
    node -> data = data;
    node->next = NULL;
    return node;
}

//Hàm dùng để chèn một Node mới vào danh sách theo thứ tự tăng dần.
void sorted_Insert (struct Node** head, struct Node* newNode){
    
    //Nếu danh sách rỗng thì chèn Node mới vào đầu danh sách.
    if(*head == NULL){
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    struct Node* prev = NULL;
    //Tìm vị trí phù hợp để chèn Node vào danh sách.
    while (current -> next != NULL && current->next->data < newNode->data){
        prev = current;
        current = current->next;
    }
    //Nếu vị trí cần chèn ở đầu danh sách.
    if (prev == NULL){
        newNode->next = *head;
        *head = newNode;
    } else {
        prev->next = newNode;
        newNode->next = current;
    }
}

//Đọc từ file các danh sách liên kết và lưu các con trỏ chỉ đến các hàng trong mảng List.
void readfromFile (char* filename,int list[], int rows, int columns){
    FILE *fp;
    fp = freopen(filename,"r",stdin);

    char line[MAX_LINE_LEN];
    int i = 1;
    while (fgets(line,MAX_LINE_LEN,fp) != NULL){
        struct Node *newRows = NULL;
        //Lấy từng phần tử trong hàng ra và đổi sang kiểu char.
        char *token = strtok(line," ");
        while ( token != NULL){
            double value = atof(token);//Trả dữ liệu về lại dạng số thực.
            struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
            newNode->data = value;
            newNode->next = NULL;
            sorted_Insert(&newRows,newNode);
            token = strtok(NULL, " ");
        }
    list[i++] = newRows;
    }
    fclose(fp);
}

//Hàm lưu ma trận vào file chỉ định.
void saveMatrixToFile(char *filename,int list[], int rows) {
    FILE *fp = fopen(filename, "w");

    for (int i = 1; i <= rows; i++) {
        struct Node *current = list[i];
        while (current != NULL) {
            fprintf(fp, "%g ", current->data);
            current = current->next;
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

//Hàm in ma trận ra màn hình.
void printMatrix(int list[], int rows) {
    for (int i = 1; i <= rows; i++) {
        struct Node *current = list[i];
        while (current != NULL) {
            printf("%g ", current->data);
            current = current->next;
        }
        printf("\n");
    }
} 

int main(){
    int rows,columns;
    //Đếm số hàng và số cột trong file.
    countRows_ColumnsfromFile("Matrix2.txt",&rows,&columns);
    printf("So hang la %d\nSo cot la %d\n",rows,columns);

    //Lấy dữ liệu từ file.
    int list[rows+2];
    readfromFile("Matrix2.txt",list,rows,columns);

    //In ma trận ra màn hình.
    printMatrix(list,rows);

    //Thêm mỗi hàng một phần tử nhập từ bàn phím.
    double n;
    printf("Nhap %d phan tu de them vao moi hang: \n",rows);
    for (int i = 1; i<columns; i++){
        // printf("Phan tu thu %d: ",i+1);
        // scanf("%lf",&n);
        n = i;
        struct Node* newNode = createNode(n);
        struct Node* insertToken = list[i];
        sorted_Insert(&insertToken,newNode);
    }
    saveMatrixToFile("RESULT1.OUT.txt",list,rows);
    return 0;
}