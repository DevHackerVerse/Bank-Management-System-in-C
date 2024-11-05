// Bank Management System
#include <stdio.h>  //printf(),scanf()
#include <stdlib.h> //exit(0),system()
#include <conio.h>  //getch()
#include "password_aunthcate.h" //address of file
#include "transactions.h"


void load_accounts(struct Account **head);
void save_accounts(struct Account *head);
void create_account(struct Account **head);
void deposit_money(struct  Account *head,long long int acc_no);
void withdraw_money(struct Acocunt *head,long long int acc_no);
void transfer(struct Account *head);
void transfer_money(struct Account *head, long long int acc_no, float amount);
void transfer_money_outside(struct Account *head, long long int acc_no, float amount);
void display_balance(struct Account *head, long long int acc_no);
void display_all_accounts(struct Account *head);
void free_accounts(struct Account *head);
void delete_account(struct Account **head);
void menu();


void divider()
{
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
}

//#Driver function
int main()
{
    password_aunthcate();
    struct Account *head=NULL;
    load_accounts(&head);

    
    //int choice;
    long long int acc_no, to_acc_no;
    float amount;
  
    int ch;
    

    while (1)
    {
        menu();
        printf("\nEnter your choice :\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                create_account(&head);
                break;
            case 2:
                printf("Enter account number: ");
                scanf("%lld", &acc_no);
                
                deposit_money(head, acc_no);
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%lld", &acc_no);
                
                withdraw_money(head, acc_no);
                break;
            case 4:
                transfer(head);
                break;
            case 5:
                printf("Enter account number: ");
                scanf("%lld", &acc_no);
                display_balance(head, acc_no);
                break;
            case 6:
                display_all_accounts(head);
                break;
            case 7:
                delete_account(&head);
                break;
            case 8:
                free_accounts(head);
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 8.\n");
        }
        save_accounts(head);
    } 
    

    return 0;
}

//!----------------------------------------------------------
//Menu Function

void menu()
{

    system("cls");
    divider();
    system("color 69");
    printf("\n\t  ====Welcome to Bhartyam Bank====");
    printf("\n\n\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");

    divider();
    printf("\n1. Create Account\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Transfer Money\n");
    printf("5. Display Balance\n");
    printf("6. Display All Accounts\n");
    printf("7. Delete Account\n");
    printf("8. Exit\n");
    divider();
}

//!---------------------------------------------------------