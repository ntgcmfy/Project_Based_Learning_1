#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
//Khai Báo Cấu Trúc 1 Node
struct node{
	double data;
	struct node *pNext;
};
typedef struct node NODE;

//Khai báo cấu trúc 1 stack
struct stack{
	NODE *pTop;//dùng con trỏ đầu để quản lí stack
};
typedef struct stack STACK;

//khởi tạo stack
void KhoiTaoStack(STACK &s){
	s.pTop=NULL;
}

// Hàm khởi tạo 1 node
NODE *KhoiTaoNode(double x){
     NODE *p=new NODE;
     p->data=x;
     p->pNext=NULL;
     return p;
}

//Kiểm tra stack có rỗng hay không
bool IsEmpty(STACK s){
    if(s.pTop==NULL) return true;
    else return false;
		
}

//Thêm 1 phần tử vào đầu stack
bool Push(STACK &s, NODE *p){
	if(p==NULL) return false;
	if(IsEmpty(s)==true){
		s.pTop=p;
	}
	else{
		p->pNext=s.pTop;
		s.pTop=p;
	}
	return true;
}

//Lấy phần tử đầu stack và trả về giá trị của nó đồng thời hủy nó đi
bool Pop(STACK &s, double &x ){
	if(IsEmpty(s)==true) return false;
	else{
		NODE *p=s.pTop;
		x=p->data;
		s.pTop=s.pTop->pNext;
		delete p;
	}
	return true;
}

//xem thông tin phần tử đầu danh sách thôi
bool Top(STACK &s, double &x){
	if(IsEmpty(s)==true) return false;
	else{
		x=s.pTop->data;
	}
	return true;
}

//Đảo ngược giá trị của 1 Stack
void Reverse(STACK &s){
	STACK temp;
	KhoiTaoStack(temp);
	for(NODE *k=s.pTop;k!=NULL;k=k->pNext){
		NODE *p=KhoiTaoNode(k->data);
		Push(temp,p);
	}
	s=temp;
}

//Thêm 1 phần tử vào cuối
void PushBack(STACK &s, NODE *p){
	Reverse(s);
	Push(s,p);
	Reverse(s);
}

//Hàm truy đến giá trị của 1 node trong Stack
double Get(STACK &s, int index){
	int x=0;
    NODE *k=s.pTop;
    while(x!=index){
    	k=k->pNext;
    	x++;
	}
	return k->data;
}

//Hàm Xuất 1 Dòng Ứng Với 1 Stack
void Print_Stack(STACK &s){
	for(NODE *k=s.pTop;k!=NULL;k=k->pNext){
		printf("%.3lf  ",k->data);
	}
}

// Hàm Xuất Ma Trận 
void Print_Matrix(STACK s[], int N){
	for(int i=0;i<N;i++){
		for(int j=0;j<=N;j++){
			printf("%3.3lf  ",Get(s[i],j));
			if(j==N) printf("\n");
		}
	}
}

//Hàm ghi File Ma Trận Sau Khi Thêm Mỗi Hàng 1 phần tử
int Write_File1(char *filename,STACK s[],int N){
	FILE *fp;
	fopen_s(&fp,filename,"w");
	char c='\n';
	if(fp==NULL) return 0;
	else{
		for(int i=0;i<N;i++){
			for(NODE *k=s[i].pTop;k!=NULL;k=k->pNext){
		    fprintf(fp,"%.3lf  ",k->data);
	        }
	    fprintf(fp,"%c",c);
        }
    }
    fclose(fp);
    return 1;
}

//Hàm Ghi File Các nghiệm X của Sau Khi giải Hệ Phương Trình Băng Phương Pháp Lặp Đơn
int Write_File2(char *filename,double X[],int N){
	FILE *fp;
	fopen_s(&fp,filename,"w");
	if(fp==NULL) return 0;
    else{
	   for(int i=0;i<N;i++){
		fprintf(fp,"X%d=%.3lf\n",i+1,X[i]);
	   }
    }
     fclose(fp);
    return 1;
}

//Phân loại các giá trị của Stack k vào các Stack riêng biệt,mỗi stack là 1 hàng ma trận
void Make_Matrix(STACK s[],STACK &k,int &N){
	for(int i=0;i<N;i++){
	   for(int j=0;j<(N-1);j++){	
		  double v;
		  Pop(k,v);
		  NODE *p=KhoiTaoNode(v);
		  Push(s[i],p);
		}Reverse(s[i]);
    }
}

//Hàm Đọc Ma Trận Từ File
int Read_File(char *filename,STACK &k){
    FILE *fp=NULL;
    double x;
    fopen_s(&fp,filename,"r");
     if(fp==NULL) return 0;
   else{ while(fscanf(fp,"%lf ",&x)!=EOF){//Đọc Hết Các Giá Trị trong File vào Stack k
	NODE *p=KhoiTaoNode(x);
	   Push(k,p);
	  }Reverse(k);//Hoán đổi ngược lại các vị trí
    }fclose(fp);
   return 1;
}

//Hàm tính định thức ma trận vuông cấp N
double Det(STACK A[], int N){
    double a[50][50];
	//Gán Các Giá Trị Của Stack A cho mảng hai chiều 
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			a[i][j]=Get(A[i],j);
		}
	}
	int det=1;
	for(int i=0;i<N-1;i++){
		for(int k=i+1;k<N;k++){
			if(a[k][i]==0) continue;
			if(a[k][i]!=0){
				for(int j=0;j<N;j++){
					a[k][j]=-a[k][j]*(a[i][i]/a[k][i]);
					a[i][j]=a[i][j]+a[k][j];
					int t=a[k][j];
					a[k][i]=-a[i][j];
					a[i][j]=t;
				}
			}
		}
	}
	for(int i=0;i<N;i++) det*=a[i][i];
	return det;
}

//Hàm Kiểm Tra Điều Kiện Hội Tụ Của Quá Trình Lặp
 int Gauss_Terms(STACK A[], int N){
 	double r1[N],r2[N];
 	double max1,max2,max3;
 	double B[10][10];
 	for(int i=0;i<N;i++){
 		for(int j=0;j<N;j++){
 			if(i==j) B[i][j]=0;
 			else{
 				B[i][j]=Get(A[i],j)/Get(A[i],i);
			 }
		 }
	 }
	  	max1=0;
	 for(int i=0;i<N;i++){
	 	r1[i]=0;
	 	for(int j=0;j<N;j++){
	 	r1[i]+=abs(B[i][j]);	
		 }
		 if(max1<r1[i] ) max1=r1[i];
	 }
	 max2=0;
	 for(int j=0;j<N;j++){
	 	r2[j]=0;
	 	for(int i=0;i<N;i++){
	 		r2[j]+=abs(B[i][j]);
		 }
		if(max2<r2[j]) max2=r2[j]; 
	 }
	 max3=0;
	 for(int i=0;i<N;i++){
	 	for(int j=0;j<N;j++){
	 		max3+=B[i][j]*B[i][j];
		 }
	 }
	 for(int i=0;i<N;i++){
	 	for(int j=0;j<N;j++){
	 		printf("%.3lf   ",B[i][j]);
		 }
		 printf("\n");
	 }
	 if(max1<1||max2<1||max3<1) return 1;
	 else return 0;
 }
 
//Hàm tìm nghiệm X khi biết AX=B với A là ma trận đọc từ file và B là mảng nhập từ bàn phím
void Find_X(STACK S[],int N){
    STACK A[N];//Sử Dụng 1 Stack Thay Thế
    double X[N],Y[N],B[N];
    int i,j;
    for(i=0;i<N;i++) KhoiTaoStack(A[i]);
	for( i=0;i<N;i++){ //Gán Stack Đã Đọc Từ File Qua Stack Thay Thế
      A[i]=S[i];
	} 
	//Kiểm Tra Điều Kiện Có Nghiệm Duy Nhất Của Hệ Phương Trình
	if(Det(A,N)==0){
           printf("Ma tran khong co nghiem duy nhat\n");
	}
	else{
	   printf("\nNhap cac gia tri cua mang B");
	   for(int i=0;i<N;i++){
    	      printf("\nB[%d]=",i);
    	      fflush(stdin);
    	      scanf("%lf",&B[i]);
    	      NODE *p=KhoiTaoNode(B[i]);
    	      PushBack(A[i],p);
	    }
	   printf("\nHe Phuong Trinh Co Dang La Ma Tran\n");
	   Print_Matrix(A,N);//Xuất Hệ Phương Trình
	   printf("\n");
	   //Kiểm Tra Điều Kiện Hội Tụ
	   if(Gauss_Terms(A,N)==0) printf("\nHe Phuong Trinh Khong Thoa Dieu Kien Hoi Tu Cua Phuong Phap Lap Don\n");
           else{
	        for(int i=0;i<N;i++) X[i]=0;	//Cho tập nghiệm x ban đầu là 0 hết	 
	        int t;
	        double Sum;
	        for( i=0;i<N;i++) printf(" x[%d]    ",i+1);
	         printf("\n");
                do{
	           t=0;
	           for(i=0;i<N;i++){
		   Sum=0;
		   for(j=0;j<(N+1);j++){
		       if(j!=i) Sum=Sum+Get(A[i],j)*X[j];
		   }
		   Y[i]=(Get(A[i],N)-Sum)/Get(A[i],i);
		   if(abs(Y[i]-X[i])>=0.001) t=1;
	           }
                 for(i=0;i<N;i++){
	         X[i]=Y[i];
	         printf("%.3lf    ",X[i]);
	         if(i==N-1) printf("\n");
                 }
           }
     while(t==1);
     for( i=0;i<N;i++){	
	if(i==N) printf("\n");
     }
   }
 }
if(Write_File2("D:\RESULT2.OUT.txt",X,N)==0){
	printf("Loi File Khong Ton Tai\n");
 }else{
	printf("\nKet Qua  Duoc Luu vao File Thanh Cong\n");
  }
}

void Menu(){
    STACK k;
	int N;
    KhoiTaoStack(k);
    int check = Read_File("D:\DAYSO.IN.txt",k);
    do{
      printf("Doc Vao N DSLK tu File voi N>=5, moi hang la 1 DSLK\n");
  	  printf("Nhap Gia Tri Cua N_");
  	  scanf("%d",&N);
  	  if(N<5) system("cls");
    } while(N<5);
    STACK s[N];
    for(int i=0;i<N;i++) KhoiTaoStack(s[i]);
    Make_Matrix(s,k,N);
    if(check=0) printf("Loi Doc File\n");\
	else{
	printf("Ma Tran Da Duoc Doc Tu File Thanh Cong\n");	
    int luachon;
	while(true){   
	printf("==========MENU==========\n");
	printf("0.Thoat Menu\n");
	printf("1.Hien Thi Ma Tran Ra Man Hinh\n");
	printf("2.Them 1 phan tu vao moi hang cua ma tran\n");
	printf("3.Tim Tap Nghiem X cua He Phuong Trinh AX=B\n");
	printf("Nhap lua chon_");
	scanf("%d", &luachon);
	if(luachon==0)	break;
	else if(luachon==1){
	    for(int i=0;i<N;i++){
		   Print_Stack(s[i]);
		   printf("\n");
	    }
	fflush(stdin);
	system("pause");
    }else if(luachon==2){
	    printf("Nhap cac phan tu can them vao ma tran\n");
	 for(int i=0;i<N;i++){
		double value;
		printf("Phan tu thu %d = ",i+1);
		scanf("%lf",&value);
		NODE *p=KhoiTaoNode(value);
		Push(s[i],p);
	 }
	 if(Write_File1("D:\RESULT1.OUT.txt",s,N)==0) printf("Loi File Khong Ton Tai");
	 else{
	 	printf("\nKet Qua Duoc Luu Vao File Thanh Cong\n");
	 	system("pause");
	 }
	 fflush(stdin);
    }else if(luachon==3){
    	Find_X(s,N);
    	system("pause");
	}else{
	    printf("Lua chon khong hop le. Vui long nhap lai\n");
	    system("pause");
    } 
    system("cls");
  }
 }
}
int main(){
	Menu();
}
