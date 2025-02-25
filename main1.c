#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct account
{
    char first_name[20];
    char last_name[20];
    char user_name[20];
    char phone[15];
    char address[30];
    char DOB[15];
    char gender;
    char password[15];
    char password1[15];
    char nick_name[20];
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
char *takepassword(char[]);
int main()
{
    while (1)
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
            printf("\n*******************THANK YOU********************\n\n");
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
    scanf("%d", &c);
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
    printf("Enter your first name : ");
    scanf("%s", s.first_name);
    printf("Enter your last name : ");
    scanf("%s", s.last_name);
    printf("Enter your mobile number : ");
    scanf("%s", s.phone);
    printf("Enter your address : ");
    scanf(" %[^\n]", s.address);
    printf("Enter your Date of birth(YYYY-MM-DD) : ");
    scanf("%s", s.DOB);
start:
    printf("Enter your Gender(M/F) : ");
    scanf(" %c", &s.gender);
    if (s.gender != 'M' && s.gender != 'F')
    {
        printf("INVALID GENDER!\n");
        goto start;
    }
    printf("Enter your user name : ");
    scanf("%s", s.user_name);
top:
    printf("Enter your password : ");
    takepassword(s.password);
    printf("\n");
    printf("Confirm your password : ");
    takepassword(pass2);
    printf("\n");
    if (strcmp(pass2, s.password) != 0)
    {
        printf("Passwords doesn't match try again.\n");
        goto top;
    }
    else
    {
        FILE *fp = fopen("D:\\account.txt", "wb");
        printf("\nEnter security question (In Case You Forget Your Password) \n");
        printf("What is your nickname? : ");
        scanf("%s", s.nick_name);
        fwrite(&s, sizeof(struct account), 1, fp);
        fclose(fp);
        printf("\n*************ACCOUNT CREATED SUCCESFULLY*************");
        getch();
    }
}
char *takepassword(char pass[])
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
    char user[30], log_pass[20], nick[20], pass2[20];
    struct account s;
    FILE *fp = fopen("D:\\account.txt", "r");
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
        printf("\nEnter password : ");
        takepassword(log_pass);
        if (strcmp(s.password, log_pass))
        {
            printf("\nINCORRET PASSWORD \n");
            printf("\nDid you forget your password?[Y/N] : ");
            char f = getche();
            if (f == 'Y' || f == 'y')
            {
            nickname:
                printf("\nWhat is your nickname? : ");
                scanf("%s", nick);
                if (strcmp(nick, s.nick_name))
                {
                    printf("Incorrect Nickname. Please try again.");
                    goto nickname;
                }
                else
                {
                top:
                    printf("\nEnter new password : ");
                    takepassword(s.password1);
                    if (strcmp(s.password1, s.password))
                    {
                        printf("\n");
                        printf("Confirm new password : ");
                        takepassword(pass2);
                        printf("\n");
                        if (strcmp(pass2, s.password1))
                        {
                            printf("Passwords doesn't match try again.\n");
                            goto top;
                        }
                        else
                        {
                            strcpy(s.password, s.password1);
                            fp = fopen("D:\\account.txt", "w");
                            fwrite(&s, sizeof(s), 1, fp);
                            printf("***************PASSWORD CHANGED SUCCESSFULLY***************\n");
                            getch();
                            goto logpass;
                        }
                    }
                    else
                    {
                        printf("\nNew password cannot be same as Old password.\n");
                        goto top;
                    }
                }
            }
            else
            {
                goto logpass;
            }
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
            printf("Address      : %s\n", s.address);
            printf("DOB          : %s\n", s.DOB);
            printf("Gender       : %c\n", s.gender);
            printf("Username     : %s\n", s.user_name);
            printf("Nickname     : %s\n", s.nick_name);
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
    char user1[20], pass[15], nick[20], pass2[20];
    int i;
    FILE *f = fopen("D:\\account.txt", "rb");
    fread(&s, sizeof(s), 1, f);
top1:
    printf("Enter username : ");
    scanf("%s", user1);
    if (strcmp(user1, s.user_name))
    {
        printf("\nUser name doesn't match.\n");
        goto top1;
    }
    else
    {
        goto top2;
    }
top2:
    printf("Enter password : ");
    takepassword(pass);
    if (strcmp(pass, s.password))
    {
        printf("\nPassword doesn't match.\n");
        goto top2;
    }
    else
    {
        fclose(f);
    }
    system("cls");
    FILE *fp = fopen("D:\\account.txt", "r+b");
    fread(&s, sizeof(s), 1, fp);
    printf("\n*****************WELCOME %s*****************\n", s.first_name);
    divider();
top3:
    printf("\nWhat do you want to modify :\n");
    printf("1. First name.\n2. Last name.\n3. Phone number.\n4. Address.\n5. Date of birth.\n6. Gender.\n7. User name. \n8. Exit. \n");
    divider();
    printf("\nEnter your choice : ");
    scanf("%d", &i);
    switch (i)
    {
    case 1:
        printf("Enter your new First name : ");
        scanf("%s", s.first_name);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************FIRST NAME CHANGED SUCCESSFULLY***********\n");
        getch();
        goto top3;
    case 2:
        printf("Enter your new Last name : ");
        scanf("%s", s.last_name);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************LAST NAME CHANGED SUCCESSFULLY************\n");
        getch();
        goto top3;
    case 3:
        printf("Enter your new Phone number : ");
        scanf("%s", s.phone);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************PHONE NUMBER CHANGED SUCCESSFULLY************\n");
        getch();
        goto top3;
    case 4:
        printf("Enter your new Address : ");
        scanf(" %[^\n]", s.address);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n**************ADDRESS CHANGED SUCCESSFULLY************\n");
        getch();
        goto top3;
    case 5:
        printf("Enter your new Date of Birth : ");
        scanf("%s", s.DOB);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************DOB CHANGED SUCCESSFULLY************\n");
        getch();
        goto top3;
    case 6:
    start:
        printf("Enter your new Gender(M/F): ");
        scanf(" %c", &s.gender);
        if (s.gender != 'M' && s.gender != 'F')
        {
            printf("INVALID GENDER!\n");
            goto start;
        }
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************GENDER CHANGED SUCCESSFULLY************\n");
        getch();
        goto top3;
    case 7:
        printf("Enter your User Name : ");
        scanf("%s", s.user_name);
        fp = fopen("D:\\account.txt", "wb");
        fwrite(&s, sizeof(s), 1, fp);
        printf("\n************USER NAME CHANGED SUCCESSFULLY************\n");
        getch();
        goto top3;
    case 8:
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
    char current[20];
    char pass2[20];
    char nick[20];
    struct account s;
    FILE *fp = fopen("D:\\account.txt", "r");
    fread(&s, sizeof(s), 1, fp);
current:
    printf("\nEnter current password : ");
    takepassword(current);
    if (strcmp(current, s.password))
    {
        printf("\nPassword doesn't match.\n");
        printf("\nDid you forget your password?[Y/N] : ");
        char f = getche();
        if (f == 'Y' || f == 'y')
        {
        nickname:
            printf("\nWhat is your nickname? : ");
            scanf("%s", nick);
            if (strcmp(nick, s.nick_name))
            {
                printf("Incorrect Nickname. Please try again.");
                goto nickname;
            }
            else
            {
            top:
                printf("\nEnter new password : ");
                takepassword(s.password1);
                if (strcmp(s.password1, s.password))
                {
                    printf("\n");
                    printf("Confirm new password : ");
                    takepassword(pass2);
                    printf("\n");
                    if (strcmp(pass2, s.password1))
                    {
                        printf("Passwords doesn't match try again.\n");
                        goto top;
                    }
                    else
                    {
                        strcpy(s.password, s.password1);
                        fp = fopen("D:\\account.txt", "w");
                        fwrite(&s, sizeof(s), 1, fp);
                        printf("***************PASSWORD CHANGED SUCCESSFULLY***************\n");
                        getch();
                    }
                }
                else
                {
                    printf("\nNew password cannot be same as Old password.\n");
                    goto top;
                }
            }
        }
        else
        {
            goto current;
        }
    }
    else
    {
    up:
        printf("\nEnter new password : ");
        takepassword(s.password1);
        if (strcmp(s.password1, s.password))
        {
            printf("\n");
            printf("Confirm new password : ");
            takepassword(pass2);
            printf("\n");
            if (strcmp(pass2, s.password1))
            {
                printf("Passwords doesn't match try again.\n");
                goto up;
            }
            else
            {
                strcpy(s.password, s.password1);
                fp = fopen("D:\\account.txt", "w");
                fwrite(&s, sizeof(s), 1, fp);
                printf("***************PASSWORD CHANGED SUCCESSFULLY***************\n");
                getch();
            }
        }
        else
        {
            printf("\nNew password cannot be same as Old password.\n");
            goto up;
        }
    }
    fclose(fp);
}
void delete_account()
{
    system("cls");
    char user[20];
    char pass[15];
    char nick[20];
    char pass2[20];
    struct account s;
    printf("DELETING YOUR ACCOUNT....\n");
    divider();
    FILE *fp = fopen("D:\\account.txt", "rb");
    fread(&s, sizeof(s), 1, fp);
top1:
    printf("Enter username : ");
    scanf("%s", user);
    if (strcmp(user, s.user_name))
    {
        printf("\nUser name doesn't match.\n");
        goto top1;
    }
    else
    {
        goto top2;
    }
top2:
    printf("\nEnter password : ");
    scanf("%s", pass);
    if (strcmp(pass, s.password))
    {
        printf("\nPassword doesn't match.\n");
        printf("\nDid you forget your password?[Y/N] : ");
        char f = getche();
        if (f == 'Y' || f == 'y')
        {
        nickname:
            printf("\nWhat is your nickname? : ");
            scanf("%s", nick);
            if (strcmp(nick, s.nick_name))
            {
                printf("Incorrect Nickname. Please try again.");
                goto nickname;
            }
            else
            {
            top:
                printf("\nEnter new password : ");
                takepassword(s.password1);
                if (strcmp(s.password1, s.password))
                {
                    printf("\n");
                    printf("Confirm new password : ");
                    takepassword(pass2);
                    printf("\n");
                    if (strcmp(pass2, s.password1))
                    {
                        printf("Passwords doesn't match try again.\n");
                        goto top;
                    }
                    else
                    {
                        strcpy(s.password, s.password1);
                        fp = fopen("D:\\account.txt", "w");
                        fwrite(&s, sizeof(s), 1, fp);
                        printf("***************PASSWORD CHANGED SUCCESSFULLY***************\n");
                        getch();
                        goto top2;
                    }
                }
                else
                {
                    printf("\nNew password cannot be same as Old password.\n");
                    goto top;
                }
            }
        }
        else
        {
            goto top2;
        }
    }
    else
    {
        printf("\nARE YOU SURE THAT YOU WANT TO DELETE YOUR ACCOUNT[Y/N]? : ");
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
    fclose(fp);
}
