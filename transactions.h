#include <stdio.h>  //printf(),scanf()
#include <stdlib.h> //exit(0),system()
#include <conio.h>  //getch()
#include <time.h>  //time(),ctime()
#include <string.h> 

struct Account{
    long long int acc_no;
    char name[30];
    float balance;
    struct Account *next;
};

void load_accounts(struct Account **head);
void save_accounts(struct Account *head);
void create_account(struct Account **head);
void deposit_money(struct  Account *head,long long int acc_no);
void withdraw_money(struct Acocunt *head,long long int acc_no);
void tranfer(struct Acount *head);
void transfer_money(struct Account *head, long long int acc_no, float amount);
void transfer_money_outside(struct Account *head, long long int acc_no, float amount);
void display_balance(struct Account *head, long long int acc_no);
void display_all_accounts(struct Account *head);
void free_accounts(struct Account *head);
void delete_account(struct Account **head);

//Not done yet
void load_accounts(struct Account **head) {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
    }

    long long int acc_no;
    char name[20];
    float balance;

    while (fscanf(file, "%lld %s %f", &acc_no, name, &balance) == 3) {
        struct Account *new_account = (struct Account *)malloc(sizeof(struct Account));
        if (new_account == NULL) {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }
        new_account->acc_no = acc_no;
        strcpy(new_account->name, name);
        new_account->balance = balance;
        new_account->next = *head;
        *head = new_account;
    }

    fclose(file);
}

void save_accounts(struct Account *head) {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    struct Account *temp = head;
    while (temp != NULL) {
        fprintf(file, "%lld %s %.2f\n", temp->acc_no, temp->name, temp->balance);
        temp = temp->next;
    }

    fclose(file);
}

void create_account(struct Account **head) {
    long long int new_acc_no;
    struct Account *temp = *head;

    // Ask user for the new account number
    printf("Enter account number: ");
    scanf("%lld", &new_acc_no);

    // Check if the account number already exists
    while (temp != NULL) {
        if (temp->acc_no == new_acc_no) {
            printf("Account with this account number already exists!\n");
            printf("Please choose a different account number.\n");
            getch(); // Wait for user input
            return; // Exit the function without creating a new account
        }
        temp = temp->next;
    }

    // If account number doesn't exist, proceed with creating the new account
    struct Account *new_account = (struct Account *)malloc(sizeof(struct Account));
    if (new_account == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Ask user for the account name
    printf("Enter name: ");
    scanf("%s", new_account->name);

    // Initialize account details
    new_account->acc_no = new_acc_no;
    new_account->balance = 0.0;
    new_account->next = *head;
    *head = new_account;

    printf("Account created successfully.\n");
    getch(); // Wait for user input
}


void deposit_money(struct Account *head, long long int acc_no) {
    struct Account *temp = head;
    int found=0;
    float amount;
    while (temp != NULL) {
        if (temp->acc_no == acc_no) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            found=1;
            temp->balance += amount;
            printf("Deposit successful. New balance: %.2f\n", temp->balance);
        }
        temp = temp->next;
    }
     if(!found){
        printf("Account not found!\n");
    }
    getch();
}

void withdraw_money(struct Account *head, long long int acc_no) {
    struct Account *temp = head;
    int found=0;
    float amount;
    while (temp != NULL) {
        if (temp->acc_no == acc_no) {
            found=1;
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (temp->balance >= amount) {
                temp->balance -= amount;
                printf("Withdrawal successful. New balance: %.2f\n", temp->balance);
            } else {
                printf("Insufficient balance!\n");
            }
        }
        temp = temp->next;
    }
     if(!found){
        printf("Account not found!\n");
    }
    getch();
}

void transfer_money(struct Account *head, long long int from_acc_no, long long int to_acc_no, float amount) {
    struct Account *from_account = NULL;
    struct Account *to_account = NULL;

    // Find the source and destination accounts
    struct Account *temp = head;
        while (temp != NULL) {
        if (temp->acc_no == from_acc_no)
            from_account = temp;
        if (temp->acc_no == to_acc_no)
            to_account = temp;
        temp = temp->next;
        }

        // Check if both accounts are found
        if (from_account == NULL || to_account == NULL) {
            printf("One or both accounts not found!\n");
            getch();
            return;
        }

        // Check if source account has sufficient balance
        if (from_account->balance < amount) {
            printf("Insufficient balance in the source account!\n");
            getch();
            return;
        }

        // Perform the transfer
        from_account->balance -= amount;
        to_account->balance += amount;

        printf("Transfer successful.\n");
        printf("New balance in account %lld: %.2f\n", from_account->acc_no, from_account->balance);
        printf("New balance in account %lld: %.2f\n", to_account->acc_no, to_account->balance);
        getch();
}

void display_balance(struct Account *head, long long int acc_no) {
    struct Account *temp = head;
    int found =0;
    while (temp != NULL) {
        if (temp->acc_no == acc_no){
            printf("Account number: %lld\n", temp->acc_no);
            printf("Account name: %s\n", temp->name);
            printf("Account balance: %.2f\n", temp->balance);
            found =1;
        }
        
        temp = temp->next;
        
    }
    if(!found){
        printf("Account not found!\n");
    }
    getch();
}

void display_all_accounts(struct Account *head) {
    struct Account *temp = head;
    printf("\nAccount Number\t\tAccount Name\t\tBalance\n");
    while (temp != NULL) {
        // printf("Account number: %lld\n", temp->acc_no);
        // printf("Account name: %s\n", temp->name);
        // printf("Account balance: %.2f\n", temp->balance);
        printf("%lld\t\t%s\t\t%.2f",temp->acc_no,temp->name,temp->balance);
        printf("\n");
        temp = temp->next;
    }
    getch();
}

void free_accounts(struct Account *head) {
    struct Account *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void delete_account(struct Account **head) {
    long long int acc_no;
    struct Account *prev = NULL;
    struct Account *current = *head;

    // Ask user for the account number to delete
    printf("Enter account number to delete: ");
    scanf("%lld", &acc_no);

    // Search for the account number in the linked list
    while (current != NULL && current->acc_no != acc_no) {
        prev = current;
        current = current->next;
    }

    // If account number not found
    if (current == NULL) {
        printf("Account not found!\n");
        getch();
        return;
    }

    // If account number found at the head of the list
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    // Free memory allocated for the deleted node
    free(current);

    printf("Account deleted successfully.\n");
    getch(); // Wait for user input
}


void transfer_money_outside(struct Account *head, long long int acc_no, float amount){

    struct Account *from_account = NULL;
    struct Account *temp = head;
    while(temp!=NULL){
        if(temp->acc_no==acc_no){
            from_account=temp;
        }
            temp = temp->next;
    } 
    if(from_account==NULL){
        printf("Account not found");
        getch();
        return;
    }

    if(from_account->balance<amount){
        printf("INsufficient Balance");
        getch();
        return;
    }    

    from_account->balance -= amount;
    printf("Transfer successful.\n");
    printf("New balance in account %lld: %.2f\n", from_account->acc_no, from_account->balance);
    getch();
}

void transfer(struct Account *head){
    long long int from_acc_no, to_acc_no;
    float amount;
    int x;
    printf("\n1. Within the Bank\n2. Outside the Bank\n");
    printf("Enter Choice: ");
    scanf("%d",&x);
    if(x==1){
        printf("Enter account from transfer: ");
        scanf("%lld",&from_acc_no);
        printf("Enter account to transfer: ");
        scanf("%lld",&to_acc_no);
        printf("Enter Amount to transfer: ");
        scanf("%f",&amount);
        transfer_money(head,from_acc_no,to_acc_no,amount);
    }
    else if(x==2){
        printf("Enter account from transfer: ");
        scanf("%lld",&from_acc_no);
        printf("Enter account to transfer: ");
        scanf("%lld",&to_acc_no);
        printf("Enter Amount to transfer: ");
        scanf("%f",&amount);
        transfer_money_outside(head,from_acc_no,amount);
    }
}