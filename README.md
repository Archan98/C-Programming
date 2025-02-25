#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct account{
    char first_name[20];
    char last_name[20];
    char user_name[20];
    char phone[15];
    char address[30];
    char DOB[15];
    char gender;
    char password[15];
};
void divider()
{
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
    printf("\n");
}
int menu();
void sign_up();
void log_in();
void modify();
void change_pass();
void delete_account();
char* takepassword(char []);
int main()
{
    while(1)
    {
        system("cls");
        switch (menu())
        {
        case 1:
            sign_up();
            break;
        case 2:
            log_in();
            break;
        case 3:
            modify();
            break;
        case 4:
            change_pass();
            break;
        case 5:
            delete_account();
            break;
        case 6:
            printf("\n*******************THANK YOU********************\n");
            exit(0);
        default:
            printf("INVALID NUMBER.\n");
            getch();
            break;
        }
    }
    return 0;
}
int menu()
{
    int c;
    printf("***************MAIN MENU***************\n");
    divider();
    printf("1. SIGN UP.\n");
    printf("2. LOG IN.\n");
    printf("3. MODIFY YOUR EXISTING DATA.\n");
    printf("4. CHANGE PASSWORD.\n");
    printf("5. DELETE ACCOUNT.\n");
    printf("6. EXIT.\n");
    divider();
    printf("Enter your choice. ");
    scanf("%d",&c);
    return c;
}
void sign_up()
{
    struct account s;
    system("cls");
    char nick_name[20];
    char pass2[20];
    printf("CREATING YOUR ACCOUNT....\n");
    divider();
    printf("Enter your first name: ");
    scanf("%s",s.first_name);
    printf("Enter your last name: ");
    scanf("%s",s.last_name);
    printf("Enter your mobile number: ");
    scanf("%s",s.phone);
    printf("Enter your address: ");
    scanf(" %[^\n]",s.address);
    printf("Enter your Date of birth(YYYY-MM-DD): ");
    scanf("%s",s.DOB);
    start:
    printf("Enter your Gender(M/F): ");
    scanf(" %c",&s.gender);
    if (s.gender != 'M'  && s.gender != 'F' )
    {
        printf("INVALID GENDER!\n");
        goto start;
    }
    printf("Enter your user name: ");
    scanf("%s",s.user_name);
    top:
    printf("Enter your password: ");
    takepassword(s.password);
    printf("\n");
    printf("Confirm your password: ");
    takepassword(pass2);
    printf("\n");
    if(strcmp(pass2,s.password) !=0)
    {
        printf("Passwords doesn't match try again.\n");
        goto top;
    }
    else
    {
        FILE *fp = fopen("D:\\account.txt", "wb");
        printf("\nEnter security question for changing password: \n");
        printf("Your nickname: ");
        scanf("%s",nick_name);
        fwrite(&s, sizeof(struct account), 1, fp);
        fclose(fp);
        printf("\n*************ACCOUNT CREATED SUCCESFULLY*************");
        getch();
    }
}
char* takepassword(char pass[])
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            pass[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == 9 || ch == 32)
        {
            continue;
        }
        else
        {
            pass[i++] = ch;
            printf("*");
        }
    }
    return pass;
}
void log_in()
{
    system("cls");
    printf("LOGGING IN....\n");
    divider();
    char user[30], log_pass[20];
    struct account s;
    FILE *fp = fopen("D:\\account.txt", "rb");
    fread(&s, sizeof(struct account), 1, fp);
    name:
    printf("Enter Username : ");
    scanf("%s", user);
    if (strcmp(s.user_name, user))
    {
        printf("\nPLEASE ENTER CORRECT USERNAME\n ");
        goto name;
    }
    else
    {
    logpass:
        printf("Enter password : ");
        takepassword(log_pass);
        if (strcmp(s.password, log_pass))
        {
            printf("\nINCORRET PASSWORD \n");
            goto logpass;
        }
        else
        {
            system("cls");
            printf("\n*****************WELCOME %s*****************\n", s.first_name);
            divider();
            printf("\nYour Details \n");
            divider();
            printf("First name   : %s\n", s.first_name);
            printf("Last name    : %s\n", s.last_name);
            printf("Phone number : %s\n", s.phone);
            printf("Address      : %s\n",s.address);
            printf("DOB          : %s\n",s.DOB);
            printf("Gender       : %c\n", s.gender);
            printf("Username     : %s\n", s.user_name);
            printf("Password     : %s\n", s.password);
        }
        getch();
    }
    fclose(fp);
}
void modify()
{
    system("cls");
    printf("MODIFYING YOUR DATA....\n");
    divider();
    struct account s;
    char user[20],pass[15];
    int i;
    FILE *f = fopen("D:\\account.txt","rb");
    fread(&s,sizeof(s),1,f);
    top:
    printf("Enter username    :");
    scanf("%s",user);
    if(strcmp(user,s.user_name))
    {
        printf("\nUser name doesn't match.\n");
        goto top;
    }
    top2:
    printf("Enter password    :");
    takepassword(pass);
    if(strcmp(pass,s.password))
    {
        printf("\nPassword doesn't match.\n");
        goto top2;
    }
    fclose(f);
    system("cls");
    FILE *fp = fopen("D:\\account.txt","rb+");
    fread(&s,sizeof(s),1,fp);
    printf("\n*****************WELCOME %s*****************\n", s.first_name);
    divider();
    top3:
    printf("\nWhat do you want to modify :\n");
    printf("1. First name.\n2. Last name.\n3. Phone number.\n4. Address.\n5. Date of birth.\n6. Gender.\n7. User name\n");
    divider();
    printf("\nEnter your choice : ");
    scanf("%d",&i);
    switch(i)
    {
    case 1:
        printf("Enter your new First name : ");
        scanf("%s",s.first_name);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************FIRST NAME CHANGED SUCCESSFULLY***********\n");
        getch();
        break;
    case 2:
        printf("Enter your new Last name : ");
        scanf("%s",s.last_name);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************LAST NAME CHANGED SUCCESSFULLY************\n");
        getch();
        break;
    case 3:
        printf("Enter your new Phone number : ");
        scanf("%s",s.phone);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************PHONE NUMBER CHANGED SUCCESSFULLY************\n");
        getch();
        break;
    case 4:
        printf("Enter your new Address : ");
        scanf(" %[^\n]",s.address);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n**************ADDRESS CHANGED SUCCESSFULLY************\n");
        getch();
        break;
    case 5:
        printf("Enter your new Date of Birth : ");
        scanf("%s",s.DOB);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************DOB CHANGED SUCCESSFULLY************\n");
        getch();
        break;
    case 6:
        start:
        printf("Enter your new Gender(M/F): ");
        scanf(" %c",&s.gender);
        if (s.gender !='M' && s.gender != 'F' )
        {
            printf("INVALID GENDER!\n");
            goto start;
        }
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************GENDER CHANGED SUCCESSFULLY************\n");
        getch();
        break;
    case 7:
         printf("Enter your User Name : ");
        scanf("%s",s.user_name);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************USER NAME CHANGED SUCCESSFULLY************\n");
        getch();
        break;
    default:
        printf("INVALID NUMBER!\n");
        getch();
        goto top3;
    }
    fclose(fp);
}
void change_pass()
{
    system("cls");
    printf("CHANGING YOUR PASSWORD.....\n");
    divider();
    char pass2[20];
    struct account s;
    FILE *fp = fopen("D:\\account.txt", "rb");
    fread(&s, sizeof(s), 1, fp);
    top:
    printf("Enter new password : ");
    takepassword(s.password);
    printf("\n");
    printf("Confirm new password :");
    takepassword(pass2);
    printf("\n");
    if(strcmp(pass2,s.password))
    {
        printf("Passwords doesn't match try again.\n");
        goto top;
    }
    else
    {
        fp = fopen("D:\\account.txt", "w");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n***************PASSWORD CHANGED SUCCESSFULLY***************\n");
        getch();
    }
    fclose(fp);
}
void delete_account()
{
    system("cls");
    printf("DELETING YOUR ACCOUNT....\n");
    divider();
    FILE *fp = fopen("D:\\account.txt", "rb");
    struct account s;
    fread(&s, sizeof(s), 1, fp);
    char user[20],pass[15];
    top:
    printf("Enter username    :");
    scanf("%s",user);
    if(strcmp(user,s.user_name))
    {
        printf("\nUser name doesn't match.\n");
        goto top;
    }
    top2:
    printf("Enter password    :");
    scanf("%s",pass);
    if(strcmp(pass,s.password))
    {
        printf("\nPassword doesn't match.\n");
        goto top2;
    }
    printf("\nARE YOU SURE[Y/N]? :");
    char ch = getche();
    if (ch == 'Y' || ch == 'y')
    {
        fp = fopen("D:\\account.txt", "w");
        fprintf(fp, " ");
        printf("\n*****************ACCOUNT DELETED SUCCESSFULLY********************\n");
        getch();
    }
    else if (ch == 'N' || ch == 'n')
    {
    printf("\n*****************ACCOUNT DELETION STOPPED***********************\n");
    getch();
    }
}
