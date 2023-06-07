#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <string>
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

//Khởi Tạo Stack
void KhoiTaoStack(STACK &s){
	s.pTop = NULL;
}

//Khởi tạo 1 node
NODE *KhoiTaoNode(double x){
     NODE *p = new NODE;
     p -> data = x;
     p -> pNext = NULL;
     return p;
}

//Kiểm tra stack có rỗng hay không
bool IsEmpty(STACK s){
    if(s.pTop == NULL) return true;
    else return false;
		
}

//Thêm 1 phần tử vào đầu stack
bool Push(STACK &s, NODE *p){
	if(p == NULL) return false;
	if(IsEmpty(s) == true){
		s.pTop = p;
	}
	else{
		p -> pNext = s.pTop;
		s.pTop = p;
	}
	return true;
}

//Lấy phần tử đầu stack và trả về giá trị của nó đồng thời hủy nó đi
bool Pop(STACK &s, double &x ){
	if(IsEmpty(s) == true) return false;
	else{
		NODE *p = s.pTop;
		x = p->data;
		s.pTop = s.pTop->pNext;
		delete p;
	}
	return true;
}

//Xem thông tin phần tử đầu danh sách mà không bị mất giá trị
bool Top(STACK &s, double &x){
	if(IsEmpty(s) == true) return false;
	else{
		x = s.pTop->data;
	}
	return true;
}

//Đảo ngược giá trị của stack
void Reverse(STACK &s){
	STACK temp;
	KhoiTaoStack(temp);
	for(NODE *k = s.pTop; k != NULL; k = k -> pNext){
		NODE *p = KhoiTaoNode(k -> data);
		Push(temp,p);
	}
	s = temp;
}

//Thêm 1 phần tử vào cuối
void PushBack(STACK &s, NODE *p){
	Reverse(s);
	Push(s, p);
	Reverse(s);
}

//Hàm truy đến giá trị của 1 node trong Stack
double Get(STACK &s, int index){
	int x = 0;
    NODE *k = s.pTop;
    while(x != index){
    	k = k -> pNext;
    	x++;
	}
	return k -> data;
}

//Hàm Ẩn Hiện Dấu Nháy Trên Màn Hình Console
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

//Hàm Đưa Con Nháy Đến Địa Chỉ(x,y) Trên Màn Hình Console
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}

//Hàm Thay Đổi Màu Sắc Văn Bản 
void SetColor ( int code ) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}

//Hamf Thay Đổi Màu Sắc BackGround
void TextColor(int x) 
{
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , x);
}

//Hàm Tạo 1 Hình Chữ Nhật Có Nội Dung
void Box(int x, int y, int w, int h, int t, int b, char *nd){
	TextColor(b);
	for(int iy = y+1; iy <= y + h-1; iy++){
		for(int ix = x + 1; ix <= x + w - 1; ix++){
			gotoxy(ix, iy); printf(" ");
		}
	}
	SetColor(b);
	gotoxy(x + 1, y + 1); printf("%s", nd);
	TextColor(1);
	SetColor(t);
	if(h <= 1|| w <= 1) return;
	for(int ix = x; ix <= x + w; ix++){
		gotoxy(ix, y); printf("%c", char(205));
		gotoxy(ix, y + h); printf("%c", char(205));
	}
	for(int iy = y; iy <= y + h;iy++){
		gotoxy(x, iy);printf("%c", char(186));
		gotoxy(x + w, iy);printf("%c", char(186));
	}
	gotoxy(x, y); printf("%c", char(201));
	gotoxy(x, y + h); printf("%c", char(200));
	gotoxy(x + w, y); printf("%c", char(187));
	gotoxy(x + w, y +h);printf("%c", char(188)); 
}

//Hàm In Ma Trân
void Print_Matrix(STACK s[], int N, int y){
	int v;
	for(int i = 0; i < N; i++){
	 	    gotoxy(62, y + i);
	 	    v = 1;
		    for(NODE *k = s[i].pTop; k != NULL; k = k -> pNext){
		        printf("%.3lf", k -> data);
		        v += 8;
		        gotoxy(62 + v, i + y);
	        }     
	       } 
}

//Hàm ghi File Ma Trận Sau Khi Thêm Mỗi Hàng 1 phần tử
int Write_File1(char *filename, STACK s[], int N){
	FILE *fp;
	fopen_s(&fp, filename, "w");
	char c = '\n';
	if(fp == NULL) return 0;
	else{
		for(int i = 0; i < N; i++){
			for(NODE *k = s[i].pTop; k != NULL; k = k->pNext){
		    fprintf( fp, "%.3lf  ", k -> data);
	        }
	    fprintf( fp, "%c", c);
        }
    }
    fclose(fp);
    return 1;
}

//Hàm Ghi File Các nghiệm X của Hệ Phương Trình
int Write_File2(char *filename,double X[],int N){
	FILE *fp;
	fopen_s( &fp, filename, "w");
	if(fp == NULL) return 0;
    else{
	   for(int i = 0; i < N; i++){
		fprintf(fp, "X%d=%.3lf\n", i+1, X[i]);
	   }
    }
     fclose(fp);
    return 1;
}

//Hàm Đọc Ma Trận Từ File
int Read_File(char *filename, STACK s[], int N){
	STACK k;
	int dem = 0;
	KhoiTaoStack(k);
    FILE *fp = NULL;
    double x;
    fopen_s(&fp,filename,"r");
     if(fp == NULL) return 0;
   else{ while( fscanf( fp , "%lf " , &x) != EOF){//Đọc Hết Các Giá Trị trong File vào Stack k
	   NODE *p = KhoiTaoNode(x);
	   Push( k , p );
	   dem++;
	  }Reverse(k);//Hoán đổi ngược lại các vị trí
    }fclose( fp );
    if(dem != N*(N-1)) return 2;
    for(int i = 0; i < N; i++){
	   for(int j = 0; j < (N-1); j++){	
		  double v;
		  Pop(k, v);
		  NODE *p = KhoiTaoNode(v);
		  Push(s[i], p);
		}Reverse(s[i]);
    }
   return 1;
}

//Hàm Kiểm Tra Ma Trận Có Phải Ma Trận Vuông Hay Không
int CheckMatrix(STACK s[],int N){
	int dem=0;
	for(int i=0;i<N;i++){
		for(NODE *k=s[i].pTop;k!=NULL;k=k->pNext){
			dem++;
		}
	}
	if(dem==N*N) return 1;
	else return 0;
}

// Hàm tính Định Thức Ma Trận Vuông Cấp N
double Det(STACK A[], int N){
    double a[50][50];
	//Gán Các Giá Trị Của Stack A cho mảng hai chiều 
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			a[i][j] = Get(A[i],j);
		}
	}
	int det = 1;
	for(int i = 0; i < N-1; i++){
		for(int k = i+1; k < N; k++){
			if(a[k][i] == 0) continue;
			if(a[k][i] != 0){
				for(int j = 0; j < N; j++){
					a[k][j] = - a[k][j] * (a[i][i] / a[k][i]);
					a[i][j] = a[i][j] + a[k][j];
					int t = a[k][j];
					a[k][i] = - a[i][j];
					a[i][j] = t;
				}
			}
		}
	}
	for(int i = 0; i < N; i++) det *= a[i][i];
	return det;
}

//Hàm Kiểm Tra Điều Kiện Hội Tụ Của Phương Pháp Lặp Gauss_Siedel
int Gauss_Terms(STACK A[], int N){
 	double r1[N], r2[N];
 	double max1, max2, max3;
 	double B[10][10];
 	for(int i = 0; i < N; i++){
 		for(int j = 0; j < N; j++){
 			if(i == j) B[i][j] = 0;
 			else{
 				B[i][j] = Get(A[i], j) / Get(A[i], i);
			 }
		 }
	 }
	  	max1 = 0;
	for(int i = 0; i < N; i++){
	 	r1[i] = 0;
 	 	for(int j = 0; j < N; j++){
	 	    r1[i] += abs(B[i][j]);	
		}
		if(max1 < r1[i] ) max1 = r1[i];
	}
	max2 = 0;
	for(int j = 0; j < N; j++){
	 	r2[j] = 0;
	 	for(int i = 0; i < N; i++){
	 		r2[j] += abs(B[i][j]);
		}
		if(max2 < r2[j]) max2 = r2[j]; 
	 }
	 max3 = 0;
	for(int i = 0; i < N; i++){
	 	for(int j = 0; j < N; j++){
	 		max3 += B[i][j] * B[i][j];
		}
	}
	if(max1 < 1 || max2 < 1 || max3 < 1) return 1;
	else return 0;
}

//Giao dien cua Menu
void Interface(){
	Box(0,0,58,29,1,1," ");
	Box(1,21,56,7,1,1," ");
	Box(60,0,58,29 ,7,1," ");
	Box(10,7,10,3,11,7," NHAP N ");
	SetColor(7);
	gotoxy(12,9); printf(" N =");
	Box(1,4,6,8,4,7," M");
	SetColor(7);
	gotoxy(2,7); printf(" E");
	gotoxy(2,9);printf(" N");
	gotoxy(2,11);printf(" U");
	char *nd;
	Box(25, 1, 30, 3, 9, 7, "   THOAT CHUONG TRINH");
	Box(25, 5, 30, 3, 9, 7, "   HIEN THI MA TRAN");
    Box(25, 9, 30, 3, 9, 7, "   THEM 1 COT PHAN TU");
    Box(25, 13, 30, 3, 9, 7, "   XOA 1 COT PHAN TU");
    Box(25, 17, 30, 3, 9, 7, "   TIM NGHIEM X");
	SetColor(6);
	gotoxy(8,8); printf("%c%c",char(205),char(205));
	gotoxy(8,9); printf("%c%c",char(205),char(205));
	gotoxy(21,8); printf("%c", char(205));
	gotoxy(21,9); printf("%c", char(205));
	gotoxy(22,8);printf("%c",char(188));
	gotoxy(22,9);printf("%c",char(187));
	for(int i=3;i<=19;i++){
		if (i==9||i==8) continue;
		gotoxy(22,i); printf("%c",char(186));
	}
	gotoxy(22,3);printf("%c%c%c",char(201),char(205),char(205));
	gotoxy(22,7);printf("%c%c%c",char(204),char(205),char(205));
	gotoxy(22,11);printf("%c%c%c",char(204),char(205),char(205));
	gotoxy(22,15);printf("%c%c%c",char(204),char(205),char(205));
	gotoxy(22,19);printf("%c%c%c",char(200),char(205),char(205));	
}

//Hàm tìm nghiệm X khi biết AX=B với A là ma trận đọc từ file và B là mảng nhập từ bàn phím
void Find_X(STACK S[], int N){
    STACK A[N]; //Sử Dụng 1 Stack Thay Thế
    double X[N], Y[N], B[N];
    int i, j;
    int yp = 18;
	for( i = 0; i < N; i++){ //Gán Stack Đã Đọc Từ File Qua Stack Thay Thế
	  KhoiTaoStack(A[i]);
	  A[i] = S[i];
	} 
	//Kiểm Tra Điều Kiện Của Hệ Phương Trình
	if(Det(A,N) == 0){
		Box(1,21,56,7,1,1," ");
		SetColor(4);
		gotoxy(2,22); printf("MA TRAN KHONG CO NGHIEM DUY NHAT");
		gotoxy(3,23);system("pause");
	}
	else{
	    Box(62,1,6,6,9,7,"NHAP");
	    SetColor(7);
	    gotoxy(63,4); printf("MANG");
	    gotoxy(63,6);printf("B");
	    for( i = 1; i <= N; i++){
    	    Box(72,i*3,15,2,11,1,"  ");
    	    SetColor(11);
    	    if(i!=1){
    	        gotoxy(79,3*i); printf("%c",char(202));
            }
            if(i!=N){
    	       gotoxy(79,3*i+2); printf("%c",char(203));
    	       gotoxy(79,3*i+3);printf("%c",char(186));
            }
    	    SetColor(7);
    	    gotoxy(73,i*3+1); printf("B[%d]=",i-1);
    	    fflush( stdin);
    	    gotoxy(80,i*3+1);
    	    scanf("%lf", &B[i-1]);
    	    NODE *p = KhoiTaoNode(B[i-1]);
    	    PushBack(A[i-1],p);
	    }
	    Box(60,0,58,29 + (N-5)*5 ,7,1," ");
	    SetColor(7);
	    gotoxy(4,11);printf("%d",N);
	    gotoxy(18,9); printf("4");
	    Box(63,1,50,2,5,7,"He Phuong Trinh Co Dang Ma Tran");
	    gotoxy(88,3);printf("%c",char(203));
	    Box(61,4,56,N+1,2,1," ");
	    gotoxy(88,4);printf("%c",char(202));
	    SetColor(7);
	    Print_Matrix(A,N,5); //Xuất Hệ Phương Trình
	    //Kiểm Tra Điều Kiện Hội Tụ
	    if(Gauss_Terms(A, N) == 0){
	    	Box(1,21,56,7,1,1," ");
	    	SetColor(4);
	    	gotoxy(2,22);
			printf("ERROR: Khong Thoa Man Dieu Kien Hoi Tu");
			gotoxy(2,23);
			system("pause");
	    }
        else{
	        for( i = 0; i < N; i++) X[i] = 0;	//Cho tập nghiệm x ban đầu là 0 hết	 
	        int t;
	        double Sum;
	        Box(63,6+N,40,2,3,7,"Tap nghiem cua he phuong trinh");
	        for( i = 1; i <= N; i++){
	        	if(i==1) SetColor(3);
	        	else SetColor(4);
	        	gotoxy(75,5+N+3*i); printf("%c",char(203));
	            Box(68,N+6+3*i,20,2,4,7," ");
	         	SetColor(4);
	        	gotoxy(75,6+N+3*i); printf("%c",char(202));
	            SetColor(7);
	            gotoxy(69,N+7+3*i);printf(" X %d = ", i); 
		    }
            do{
	            t = 0;
	            for( i = 0; i < N; i++){
		            Sum = 0;
		            for(j = 0; j < (N+1); j++){
			           if(j != i) Sum = Sum + Get(A[i], j)*X[j];
		            }
		            Y[i] = (Get(A[i],N) - Sum) / Get(A[i], i);
		            if(abs(Y[i] - X[i]) >= 0.001) t = 1;
	                X[i] = Y[i];
                } 
            }
            while(t == 1);
            for( i = 0; i < N; i++){
	            gotoxy(77,N+10+3*i);
	            SetColor(7);
			    printf("%.3lf", X[i]);  
            }
	        Box(1,21,56,7,1,1," ");
	        if(Write_File2("D:\RESULT2.OUT.txt", X, N) == 0){
		        Box(1,21,56,7,1,1," ");
		        SetColor(4);
		        gotoxy(2,22); printf("Error: Khong ton tai File D:\RESULT2.OUT.txt");
	        } 
		    else {
		        Box(1,21,56,7,1,1," ");
		        SetColor(10);
		        gotoxy(2,22); printf("Ket qua  duoc luu vao File D:\RESULT2.OUT.txt thanh cong");
	        }
	        Box(95,18,20,2,6,4,"    Xem Qua Trinh");
	        Box(95,21,20,2,6,7,"      Bo Qua");
	        bool kt = true;
	        while(kt){
	        	ShowCur(0);
	        	SetColor(6);
	            gotoxy(105,20); printf("%c",char(203));
	            gotoxy(105,21);printf("%c",char(202));
	    	    if(kbhit()){
	        		char c = getch();
	        		if(c == -32){
	    	    		c = getch();
	    			    if(c == 80 && yp == 18) {
	    				    yp += 3;
					     	Box(95,18,20,2,6,7,"    Xem Qua Trinh");
	                        Box(95,21,20,2,6,4,"      Bo Qua");
				        }
					    if(c == 72 && yp == 21) {
						    yp -=3;
						    Box(95,18,20,2,6,4,"    Xem Qua Trinh");
	                        Box(95,21,20,2,6,7,"      Bo Qua");
					    }					 
				    } else if(c == 13) break;
			   }
		    }
		    if(yp==18){
		        	Box(60,0,58,29 +(N-5)*5 ,7,1," ");
		    	    for( i=1;i<=N;i++){
		    		    Box(55+9*i,1,5,2,4,7," ");
		    		    SetColor(7);
		    		    gotoxy(57+9*i,2); printf("X%d",i);
		    	    }
            	    int k=4;
            	    for( i = 0; i < N; i++) X[i] = 0;
		            do{
	                    t = 0;
	                    for( i = 0; i < N; i++){
		                    Sum = 0;
		                    for(j = 0; j < (N+1); j++){
			                    if(j != i) Sum = Sum + Get(A[i], j)*X[j];
		                    }
		                    Y[i] = (Get(A[i],N) - Sum) / Get(A[i], i);
		                    if(abs(Y[i] - X[i]) >= 0.001) t = 1;
	                        X[i] = Y[i];
						    gotoxy(64+9*i,k); printf("%.3lf",X[i]);
 					    } 
 					    k++;
                    }
                    while(t == 1);
		    }
	    }
	    SetColor(6);
	    gotoxy(2,23); printf("Nhan phim UP / DOWN va ENTER de tiep tuc cac lua chon");
	    gotoxy(2,24);
    }
}
// Hàm Menu Chứa Và Thực Hiện Các Động Lệnh
void Menu(){
	int N = 5;
	int x = 25;
	int y = 1;
    do{
       Interface();
       SetColor(10);
       gotoxy(2,22);
       printf("Doc ma tran gom N (N>=5) hang tu File D:\DAYSO.IN.txt");
       gotoxy(17,9);
  	   scanf("%d", &N);
  	   if(N < 5) {
  	  	  Box(1,21,56,7,1,1," ");
		  gotoxy(2,22);
		  SetColor(4);
		  printf("ERROR: N khong hop le");
		  gotoxy(2,23);
		  system("pause");
		  system("cls");
      }
	} while(N < 5);
    STACK s[N];
    for(int i = 0; i < N; i++) KhoiTaoStack(s[i]);
    int check = Read_File("D:\DAYSO.IN.txt", s, N);
    if( check == 0){
	   Box(1,21,56,7,1,1," ");
	   gotoxy(2,22); 
	   SetColor(4);
	   printf("ERROR: Loi file D:\DAYSO.IN.txt");
	   gotoxy(2,23);
	   system("pause");
    }
    else if(check == 2){
       Box(1,21,56,7,1,1," ");
	   gotoxy(2,22); 
	   SetColor(4);
	   printf("ERROR:So Phan Tu Trong File D:\DAYSO.IN.txt Khong Hop Le");
	   gotoxy(2,23);
	   system("pause");
	}
	else if( check == 1){	
	   Box(1,21,56,7,1,1," ");
	   SetColor(10);
	   gotoxy(2,22);printf("Ma tran doc tu File thanh cong");
	   SetColor(6);
	   gotoxy(2,23);printf("Nhan phim UP / DOWN va ENTER de tiep tuc cac lua chon");
	   SetColor(7);
	   gotoxy(17,9);printf("%d",N);
	   while(true){
	       ShowCur(0);
	       int yp = y;
	       int ycu = yp;
           char *nd ="   THOAT CHUONG TRINH";
           Box(25, 5, 30, 3, 9, 7, "   HIEN THI MA TRAN");
           Box(25, 9, 30, 3, 9, 7, "   THEM 1 COT PHAN TU");
           Box(25, 13, 30, 3, 9, 7, "   XOA 1 COT PHAN TU");
           Box(25, 17, 30, 3, 9, 7, "   TIM NGHIEM X");
           bool kt = true;
           while(true){
    	       if(kt == true){
    	       Box(x,ycu,30,3,9,7,nd);
    	       ycu = yp;	
    	       if(yp == 5) nd = "   HIEN THI MA TRAN";
    	       else if(yp == 9) nd = "   THEM 1 COT PHAN TU";
    	       else if(yp == 13) nd ="   XOA 1 COT PHAN TU";
    	       else if(yp == 17) nd ="   TIM NGHIEM X";
    	       else if(yp == 1) nd ="   THOAT CHUONG TRINH";
    	       Box(x,yp,30,3,6,10,nd);
    	       kt = false;
               }   
    	       if(kbhit()){
    		       char c = getch();
    		       if(c == 13) break;
    		       else if(c ==-32 ){
    			       kt = true;
    			       c = getch();
    			       if(c == 72 && yp != y){
    				        if(yp != y) yp -= 4;
    				        else{
    					      yp = y +16;
					        }
				        }
				        else if(c == 80 && yp != y + 16){
					        if(yp != y + 9) yp += 4;
					        else{
						       yp = y;
					        }
				        }
			        }
		        }
	        }
		    ShowCur(1);				
	        if(yp == 1){
	            gotoxy(2,29);
	            break;
            }
	        else if(yp == 5) {
	            Box(62,2,15,2,6,7,"    MA TRAN");
	            gotoxy(67,4); printf("%c",char(203));
	            gotoxy(67,5); printf("%c",char(186));
	            gotoxy(68,4); printf("%c",char(203));
	            gotoxy(68,5); printf("%c",char(186));
                Box(61,6,56+(N-6)*6,N+1,2,1," ");
	            SetColor(10);
	            gotoxy(67,6); printf("%c",char(202));
	            gotoxy(68,6); printf("%c",char(202));
	            SetColor(7);
	            Print_Matrix(s,N,7);
	            Box(1,21,56,7,1,1," ");
	            SetColor(6);
	            gotoxy(2,22);
	            printf("Nhan phim UP / DOWN va ENTER de tiep tuc cac lua chon");
	            gotoxy(2,23);
	            system("pause");
            }
            else if(yp == 9) {
        	    Box(1,21,56,7,1,1," ");
                SetColor(4);
                gotoxy(2,22);
                printf("VUI LONG NHAP SO THUC");
                Box(1,21,56,7,1,1," ");
                SetColor(10);
	            gotoxy(2,22);
	            printf("Cac phan tu se duoc them vao dau moi hang cua ma tran");
    	        gotoxy(60,1);
    	        SetColor(3);
    	        Box(62,1,40,2,5,7,"Nhap cac phan tu can them vao ma tran");
    	        SetColor(6);
	            for(int i = 1; i <= N; i++){
		        double value;
		            for( i = 1; i <= N; i++){
		  	            if(i==1) SetColor(5);
		   	            else SetColor(6);
		                gotoxy(70,3*i); printf("%c",char(203));
    	                Box(62,1+i*3,28,2,6,7,"  ");
    	                gotoxy(70,3*i+1);printf("%c",char(202));
    	                SetColor(7);
    	                gotoxy(64,2+3*i); printf("Phan Tu Thu %d = ",i);
    	                fflush( stdin);
    	                gotoxy(80,2+3*i);
	  	                scanf("%lf", &value);
		                NODE *p = KhoiTaoNode(value);
		                Push(s[i-1], p);
                    }
                }
                Box(1,21,56,7,1,1," ");
                SetColor(6);
	            gotoxy(2,22);
	            printf("Nhan phim UP / DOWN va ENTER de tiep tuc cac lua chon");
	            gotoxy(2,23);
            }
            else if(yp==13){
        	    Box(1,21,56,7,1,1," ");
        	    SetColor(10);
          	    gotoxy(2,22); printf("Xoa phan tu dau tien moi hang cua ma tran");
           	    double z;
           	    for(int i=0;i<N;i++) Pop(s[i],z);
			    SetColor(6);
	            gotoxy(2,23);
	            printf("Nhan phim UP / DOWN va ENTER de tiep tuc cac lua chon");
	            gotoxy(2,24);
	            system("pause");
		    }
			else if(yp==17){
                if(CheckMatrix(s,N)==0){
            	    Box(1,21,56,7,1,1," ");
            	    gotoxy(2,22);
            	    SetColor(4);
            	    printf("ERROR: Ma tran hien khong phai ma tran vuong");
           		    gotoxy(2,23);
		        }
				else{
		    	    Box(1,21,56,7,1,1," ");
				    SetColor(10);
				    gotoxy(2,22); printf("He phuong trinh co dang AX=B voi B nhap tu ban phim");
	                gotoxy(60,1);
	                Find_X(s, N);
	            }
                system("pause");
            }
            Box(60,0,58,29,7,1," ");
        }          
    }
}
int main(){
	Menu();
}
