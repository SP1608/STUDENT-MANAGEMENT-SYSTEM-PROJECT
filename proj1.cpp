#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
void gotoxy(int x ,int y);
void menu();
void insert();
void display();
void search();
void modify();
void delrec();
struct student
{
	int rollno;
	char name[20];
	char mobileno[10];
	char course[20];
	char branch[20];	
};

int  main()
{
	gotoxy(15,6);
	printf("---STUDENT RECORD MANAGEMENT---");
	gotoxy(15,7);
	printf("PRESS ANY TO CONTINUE");
	getch();
	menu();
	return 0;
}

void menu()
{
	int ch;
	system("cls");
	gotoxy(10,4);
	printf("----MENU----");//main menu 
    gotoxy(12,5);
	printf("1.Insert Record ");
	gotoxy(12,6);
	printf("2.Display Record");
	gotoxy(12,7);
	printf("3.Search Record");
	gotoxy(12,8);
	printf("4.Modify Record");
	gotoxy(12,9);
	printf("5.Delete Record");
	gotoxy(12,10);
	printf("6.Exit");
	gotoxy(12,12);
	printf("Enter Choice");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			insert();
			break;
		case 2:
			display();
            break;
		case 3:
			search();
			break;
		case 4:
		    modify();
		    break;
		case 5:
		    delrec();
		    break;
        case 6:
			exit(1);
			break;
		default:
			printf("INVALID CHOICE");
			break;
		
	}
	
}
void insert()
{
	FILE *fp;
	struct student std;
	char d='y';
	system("cls");
	fp=fopen("record.txt","ab+");
	if(fp==NULL)
	{
		gotoxy(12,5);
		printf("Error\n");
		exit(1);
		
	}
	fflush(stdin);
	while (d=='y')
	{
		
		gotoxy(12,7);
		printf("---INSERT RECORD---");
	    gotoxy(12,8);
		printf("Details of student ");
		gotoxy(12,10);
			
		printf("Enter roll number");
		scanf("%d",&std.rollno);
		fflush(stdin);
		gotoxy(12,11);
		printf("Enter name:");
	    gets(std.name);
        gotoxy(12,12);
		printf("Enter mobile number: ");
		gets(std.mobileno);
	    gotoxy(12,13);
	    printf("Enter branch:");
	    gets(std.branch);
	    gotoxy(12,14);
	    printf("Enter course:");
        gets(std.course);
	    gotoxy(12,15);
	    fwrite(&std,sizeof(std),1,fp);
	    gotoxy(12,19);
	    printf("If you want to continue enter 'y' else enter 'n' ");
	    fflush(stdin);
	    d=getch();
	    system("cls");
	    fflush(stdin);
	}
	fclose(fp);
	menu();			   
		
	
}
void display()
{
	FILE *fp;
	int i=1,j;
	struct student std;
	system("cls");
	
	gotoxy(12,3);
	printf("---Display Record---");
	gotoxy(12,4);
	printf("      Roll No:     Name of student:    Mobile No.:     Branch:    Course:  ");
	gotoxy(12,6);
	fp=fopen("record.txt","rb+");
	if(fp==NULL)//no data present in file
	{
		gotoxy(12,7);
		printf("ERROR");
		exit(1);
	}
	j=7;
	while(fread(&std,sizeof(std),1,fp)==1)
	{
		gotoxy(12,j);
		printf("%-7d%-9d%-22s%-12s%-12s%-12s",i,std.rollno,std.name,std.mobileno,std.course,std.branch);
		i++;
		j++;
	}
	fclose(fp);
	gotoxy(12,j+3);
    printf("Press any key to continue.");
    getch();
	menu();
	
	
	
}
void search()
{
	FILE *fp;
	struct student std;
	char sname[20];
	system("cls");
	gotoxy(12,4);
	printf("----VIEW RECORD----");
	gotoxy(12,6);
	printf("Enter name of student");//name to be searched
	fflush(stdin);
	gets(sname);
	fp=fopen("record.txt","rb+");
	if(fp==NULL)
	{
		gotoxy(12,7);
		printf("ERROR");
		exit(1);
		
	}
	while(fread(&std,sizeof(std),1,fp)==1)
	{
		if(strcmp(sname,std.name)==0)
		{
			gotoxy(12,8);
			printf("ROLL NO:%d",std.rollno);
			gotoxy(12,9);
			printf("NAME:%s",std.name);
			gotoxy(12,10);
			printf("MOBILE NO:%d",std.mobileno);
			gotoxy(12,11);
			printf("BRANCH:%d",std.branch);
			gotoxy(12,12);
			printf("COURSE:%d",std.course);
			
		}
		fclose(fp);
		menu();	
	}
}

void modify()
{
	
	char sname[20];
	FILE *fp;
	struct student std;
	system("cls");
	gotoxy(12,3);
	printf("---MODIFY RECORD---");
	gotoxy(12,4);
	printf("Enter name of student to be modified:");
	fflush(stdin);
	gets(sname);
	fp=fopen("record.txt","rb+");
	if (fp==NULL)
	{
		gotoxy(12,5);
		printf("ERROR");
		exit(1);
	}	
    rewind(fp);//reposition fp to the beginning of the file 
    fflush(stdin);
    while(fread(&std,sizeof(std),1,fp)==1)
    {
    	if(strcmp(sname,std.name)==0)
    	{
    		gotoxy(12,6);
    		printf(" Roll no:");
    		scanf("%d",&std.rollno);
    		gotoxy(12,7);
    		printf("Name:");
    		fflush(stdin);
    		gets(std.name);
    		gotoxy(12,8);
    		printf("Mobile no:");
    		fflush(stdin);
    		gets(std.mobileno);
    		gotoxy(12,9);
    		printf("Branch");
    		fflush(stdin);
    		gets(std.branch);
    		gotoxy(12,10);
    		printf("Course:");
    		fflush(stdin);
    		gets(std.course);
    		fseek(fp,sizeof(std),SEEK_CUR);//fp move to current position that is place where modified data is to be placed in file
    		fwrite(&std,sizeof(std),1,fp);//write updated data in the file
    		break;
        }
    }
    fclose(fp);
    menu();
    	
}

void delrec()
{
	FILE *fp,*ft;
	struct student std;
	char sname[20];
	system("cls");
	gotoxy(12,4);
	printf("---DELETE RECORD---");
	gotoxy(12,5);
	printf("Enter name of student to delete record ");
    fflush(stdin);
	gets(sname);
	fp=fopen("record.txt","rb+");
	if(fp==NULL)
	{
		gotoxy(12,6);
		printf("ERROR");
		exit(1);
	}
	ft=fopen("temp.txt","wb+");
	if(ft==NULL)
	{
		gotoxy(12,7);
		printf("ERROR");
		exit(1);
	}
	while(fread(&std,sizeof(std),1,fp)==1)
	{
		if(strcmp(sname,std.name)!=0)//fetch all record where name of the student to be deleted is not same with the student name in record 
		{
			fwrite(&std,sizeof(std),1,ft);//write all those names in new file"temp.txt"
		}
	fclose(fp);
	fclose(ft);
	remove("record.txt");//delete "record.txt"  with data where name of student matches with the name in record   
	rename("record.txt","temp.txt");//rename temp as "record.txt"
	menu();
	
	}
}
void gotoxy(int x,int y)
{
    COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

