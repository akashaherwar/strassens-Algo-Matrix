#include<stdio.h>
#define MAX 16
void divide(int A[MAX][MAX],int B[MAX][MAX],int size)
{
	int i,j,matSize=size/2;
	int a00[2][2],a01[2][2],a10[2][2],a11[2][2],b00[2][2],b01[2][2],b10[2][2],b11[2][2];
	int tmp1[2][2],tmp2[2][2],m1[2][2],m2[2][2],m3[2][2],m4[2][2],m5[2][2],m6[2][2],m7[2][2];
	int c00[2][2],c01[2][2],c10[2][2],c11[2][2];
	int mainMat[4][4];
	if(size==2)
	{
		strassen(A,B,m1,size);
		display(m1,size);
	}
	else
	{
	   for(i=0;i<matSize;i++) 
	   {
		for(j=0;j<matSize;j++)
		{
			a00[i][j]=A[i][j];
			a01[i][j]=A[i][j+matSize];
			a10[i][j]=A[i+matSize][j];
			a11[i][j]=A[i+matSize][j+matSize];
			b00[i][j]=B[i][j];
			b01[i][j]=B[i][j+matSize];
			b10[i][j]=B[i+matSize][j];
			b11[i][j]=B[i+matSize][j+matSize];
		}
           }
	add(a00,a11,tmp1,2);
	add(b00,b11,tmp2,2);
	strassen(tmp1,tmp2,m1,matSize);
	
	add(a10,a11,tmp1,2);
	strassen(tmp1,b11,m2,matSize);
	
	sub(b01,b11,tmp1,2);
	strassen(tmp1,a00,m3,matSize);
	
	sub(b10,b00,tmp1,2);
	strassen(tmp1,a11,m4,matSize);
	
	add(a00,a01,tmp1,2);
	strassen(tmp1,b11,m5,matSize);
	
	sub(a10,a00,tmp1,2);
	add(b00,b01,tmp2,2);
	strassen(tmp1,tmp2,m6,matSize);
	
	sub(a01,a11,tmp1,2);
	add(b10,b11,tmp2,2);
	strassen(tmp1,tmp2,m7,matSize);
	
	//c00
	add(m1,m4,tmp1,2);
	add(m5,m7,tmp2,2);
	sub(tmp1,tmp2,c00,2);
	//c01
	add(m3,m5,c01,2);
	//c10
	add(m2,m4,c10,2);
	//c11
	add(m1,m3,tmp1,2);
	add(m2,m6,tmp2,2);
	sub(tmp1,tmp2,c11,2);

	for(i=0;i<matSize;i++)
	{
		for(j=0;j<matSize;j++)
		{
			mainMat[i][j]=c00[i][j];
			mainMat[i][j+matSize]=c01[i][j];
			mainMat[i+matSize][j]=c10[i][j];
			mainMat[i+matSize][j+matSize]=c11[i][j];
		}
	}
	printf("\n\n\tResult\n");	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{		
		printf(" %d\t",mainMat[i][j]);
		}		
	printf("\n");
	}	
	}	
}
/*************************************************************************/
int padding(int num)
{
	int temp=num,power=0,i,anum=1;
	if(num==1)
		return 1;
	while(num>1) 
	{
		power++;
		num/=2;
	}

	for(i=0;i<power;i++) 
	{
		anum*=2;
	}
	if(anum==temp)
		return temp;

	else
		return anum*2;
}

/*************************************************************************/
void add(int t1[2][2],int t2[2][2],int t3[2][2],int size)
{
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			t3[i][j]=t1[i][j]+t2[i][j];
}
/*************************************************************************/
void sub(int t1[2][2],int t2[2][2],int t3[2][2],int size)
{
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			t3[i][j]=t1[i][j]-t2[i][j];
}

/*************************************************************************/
void  accept(int A[MAX][MAX],int size)
{
	int i,j;
	printf("Enter the element : \n");
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)		
			scanf("%d",&A[i][j]);
}

/*************************************************************************/
void  display(int A[MAX][MAX],int size)
{
	int i,j;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)		
			printf(" %d\t",A[i][j]);		
	printf("\n");
	}
}
/*************************************************************************/
void strassen(int A[2][2],int B[2][2],int C[2][2],int size)
{
	int m1,m2,m3,m4,m5,m6,m7,i,j;
	
	m1=(A[0][0]+A[1][1])*(B[0][0]+B[1][1]);
	m2=(A[1][0]+A[1][1])*(B[0][0]);
	m3=(A[0][0])*(B[0][1]-B[1][1]);
	m4=A[1][1]*(B[1][0]-B[0][0]);
	m5=(A[0][0]+A[0][1])*B[1][1];
	m6=(A[1][0]-A[0][0])*(B[0][0]+B[0][1]);
	m7=(A[0][1]-A[1][1])*(B[1][0]+B[1][1]);;

	C[0][0]=m1+m4-m5+m7;
	C[0][1]=m3+m5;
	C[1][0]=m2+m4;
	C[1][1]=m1+m3-m2+m6;

}
/*************************************************************************/
void main()
{
	int size1,size;
	int A[MAX][MAX]={0},B[MAX][MAX]={0},C[MAX][MAX]={0};
	printf("Enter the size of matrix :");
	scanf("%d",&size1);
	size=padding(size1);
	printf("Enter the A Matrix \n");
	accept(A,size1);
	printf("Enter the B Matrix \n");
	accept(B,size1);
	printf("\tMatrix A\n");
	display(A,size);
	printf("\tMatrix B\n");
	display(B,size);
	divide(A,B,size);
}

