#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define GOTOXY(x,y) printf("\033[%d,%df",y,x)
void delay(int time)
{
    int milli = 1000* time;
    clock();
    while(clock()<milli);
}
void input();
void writefile();
void search();
void output();

struct date {
    int month;
    int day;
    int year;
};
struct account{
    int number;
    char name[100];
    int acct_no ;
    float mobile_no;
    char street[100];
    char city[100];
    char acct_type;
    float oldbalance;
    float newbalance;
    float payment;
    struct date lastpayment;
}customer;
int tl,sl,ts ;
int main()
{
    int i,n;
    char ch;

    printf("    ---------------------CUSTOMER BILLING SYSTEM---------------------\n\n");
    printf("    =================================================================\n");
    printf("    l: ADD ACCOUNT ON LIST \n");
    printf("    2: SEARCH CUSTOMER ACCOUNT \n");
    printf("    3: EXIT\n");
    printf("    =================================================================\n");
    do
    {
        printf(" \n    SELECT FROM THE ABOVE ?? \n");
        ch=getchar();

    }while(ch<='0'||ch>'3');
    switch (ch)
    {
        case '1' :

        printf("\n HOW MANY CUSTOMERS ACCOUNT :  ");
        scanf("%d",&n);
        getchar();
        for(i=0;i<n;i++)
        {
            input();
             if (customer.payment > 0.0)
        customer.acct_type=(customer.payment <customer.oldbalance)? '0':'D';
        else
        customer.acct_type=(customer.oldbalance >0)?'D':'C';
        customer.newbalance=customer.oldbalance-customer.payment;
        writefile();
    }
        main();
        case '2':
        getchar();

        printf("SEARCH BY WHAT ?? \n\n");
        printf("l: SEARCH BY CUSTOMER NUMBER \n");
        printf("2:SEARCH BY NAME \n");
        search();
        ch =getchar();
        main();
        case '3':

        delay(500);
        GOTOXY(10,25);
        printf("A PROJECT BY VEDANT VAYA");
        delay(1500);
        exit(1);
    }
      }
         void input()
	{
	  FILE *fp=fopen("file.txt","ab+");
	  fseek (fp,0,SEEK_END);
	  tl=ftell(fp);
	  sl=sizeof(customer);
	  ts=tl/sl;
	  fseek(fp,(ts-1)*sl,SEEK_SET);
	  fread(&customer,sizeof(customer),1,fp);
	  printf("\nCUSTOMER NO:%d\n",++customer.number);
	  fclose(fp);
	  printf("\n         ACCOUNT NUMBER:");
	  scanf("%d",&customer.acct_no);
	  getchar();
	  printf("\n       NAME:");
	  scanf("%s",customer.name);
	  getchar();
	  printf("\n       MOBILE NO.:");
	  scanf("%f",&customer.mobile_no);
	  getchar();
	  printf("\n         STREET:");
	  scanf("%s",customer.street);
	    getchar();
	  printf("\n         CITY:");
	  scanf("%s",customer.city);
	    getchar();
	  printf("\n         PREVIOUS BALANCE:");
	  scanf("%f",&customer.oldbalance);
	    getchar();
	  printf("\n         CURRENT PAYMENT:");
	  scanf("%f",&customer.payment);
	    getchar();
	  printf("         PAYMENT DATE(MM/DD/YYYY):");
	  scanf("%d/%d/%d",&customer.lastpayment.month,&customer.lastpayment.day,&customer.lastpayment.year);
	   getchar();
   }


    void writefile()
   {
	  FILE *fp;
	  fp=fopen("file.txt","ab+");
	  fwrite(&customer,sizeof(customer),1,fp);
	  fclose(fp);
	  return;
	  }
 void search()
   {
	 char ch;
	 char nam[100];
	 int n,i,m=1;
	 FILE *fp;
	 fp=fopen("file.txt","r+");
	 do
	 {
		printf("\n ENTER YOUR CHOICE: ");
		ch=getchar();
	 }while(ch!='1' && ch!='2');
	 switch(ch)
	 {
	      case '1':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(customer);
		    ts=tl/sl;
		    do
		    {
			printf("\n CHOOSE CUSTOMER NUMBER:");
			scanf("%d",&n);
			if(n<=0 || n>ts)
			printf("\n ENTER CORRECT \n");
			else
			{
			    fseek(fp,(n-1)*sl,SEEK_SET);

			    fread(&customer,sl,1,fp);
			    output();
			}
				printf("\n\nAGAIN?(y/n)");
			ch=getchar();
			}while(ch=='y');
		    fclose(fp);
		    break;
	        case '2':
		    fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(customer);
		    ts=tl/sl;
		    fseek(fp,(ts-1)*sl,SEEK_SET);
		    fread(&customer,sizeof(customer),1,fp);
		    n=customer.number;
		     do
		     {
			printf("\n ENTER THE NAME:");
			scanf("%s",nam);
			fseek(fp,0,SEEK_SET);
			for(i=1;i<=n;i++)
			{
			     fread(&customer,sizeof(customer),1,fp);
			     if(strcmp(customer.name,nam)==0)
			     {
				output();
				m=0;
				break;
			     }
			}
			if(m!=0)
			printf("\n\n DOESN'T EXIST\n");
			printf("\n ANOTHER?? (y/n)");
			ch=getchar();
		    }while(ch=='y');
		    fclose(fp);
	      }
	      return;
}
void output()
{
    printf("\n\n    CUSTOMER NUMBER    :%d \n",customer.number);
	   printf("    NAME 	   :%s \n",customer.name);
	   printf("    MOBILE NO      :%.f \n",customer.mobile_no);
	   printf("    ACCOUNT NUMBER :%d \n",customer.acct_no);
	   printf("    STREET       :%s \n",customer.street);
	   printf("    CITY         :%s \n",customer.city);
	   printf("    OLD BALANCE    :%.2f \n",customer.oldbalance);
	   printf("    CURRENT PAYMENT:%.2f \n",customer.payment);
	   printf("    NEW BALANCE    :%.2f \n",customer.newbalance);
	   printf("    PAYMENT DATE   :%d/%d/%d \n \n",customer.lastpayment.month,customer.lastpayment.day,customer.lastpayment.year);
	   printf("    ACCOUNT STATUS :");
     switch(customer.acct_type)
	      {
	      case 'C':
		 printf("CURRENT \n\n");
		 break;
	      case '0':
		 printf("OVERDUE \n\n");
		 break;
	      case 'D':
		 printf("DELINQUENT \n\n");
		 break;
	      default:
		 printf("ERROR\n\n");
	      }
	      return;}
