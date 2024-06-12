#include<stdio.h>
#include<stdbool.h>		//in C, for boolean we use this
#include<string.h>
#include<stdlib.h>

typedef struct date
{
    int day;
    int month;
    int year;
} date;

typedef struct node
{
    char type[50];
    char category[100];
    date d;
    int amount;
    struct node* next;
} node;

char passwords[3][100]; //made the '3' passwords global.
bool password (int choice);
void first_screen ();
bool change_password (int cp);
void secondscreen();
void secondscreenhandler(int user_choice);
void thirdscreen();
void thirdscreenhandler(int user_choice, int wallet_choice);
void displaydetails(node* head);
node* delete_entry(int user_choice, int wallet_choice, node* head);
void delete_from_file(int user_choice, int wallet_choice, node* head);
node* add_entry(int user_choice, int wallet_choice, node* head);
node* linked_list_loader(int user_choice, int wallet_choice);
node* reset_list(node* head);
void build_file_name(int user_choice, int wallet_choice, char* name);
void delete_user_screen_handler();
void delete_data_wallet_handler(int choice);
void delete_user_screen();
void delete_data(int user_choice, int wallet_choice);

node* head = NULL;
int goal=0, initial_balance=0;

node* insert(node* h, char* type, char* category, date d, int amount)
{
    node*h1 = h;
    node* temp = (node*) malloc(sizeof(node));
    strcpy(temp->type, type);
    strcpy(temp->category, category);
    temp->d.year = d.year;
    temp->d.month = d.month;
    temp->d.day = d.day;
    temp->amount = amount;
    temp->next = NULL;
    
    if(h==NULL)
    h1 = temp;
    else
    {
        while(h->next!=NULL)
        {
            h = h->next;
        }
        h->next = temp;
    }
    return h1;
}

void print(node* h)
{
    int total = 1000;
    while(h!=NULL)
    {
        total = total+h->amount;
        
        printf("%s\t%s\t%d/%d/%d\t%d\n", h->type, h->category, h->d.day, h->d.month, h->d.year, h->amount);
        h = h->next;
    }
    printf("%d", total);
    return;
}

void clear_screen()
{
    //for mac:
    system("clear");    
    //for windows: 
    //system("cls");
}

int main()
{
    int choice;
    clear_screen();
    first_screen();
    do                  //This do while will work until 6 is pressed. This means it will be printed in the screen until 6 is pressed.
    {
      printf ("\nEnter any choice: ");
      scanf ("%d", &choice);	//asking the user to enter any choice from the list.
      clear_screen();
      switch (choice)
	{
	case 1:
	if(password(choice)==false)
	{
	    clear_screen();
	    printf("Wrong password\n");
	    first_screen();
	}
	else
	secondscreenhandler(choice);
	clear_screen();
	first_screen();
	break;
	
	case 2:
	if(password(choice)==false)
	{
	    clear_screen();
	    printf("Wrong password\n");
	    first_screen();
	}
	else
	secondscreenhandler(choice);
	clear_screen();
	first_screen();
	break;
	
	case 3:
	if(password(choice)==false)
	{
	    clear_screen();
	    printf("Wrong password\n");
	    first_screen();
	}
	else
	secondscreenhandler(choice);
	clear_screen();
	first_screen();
	break;
	
	case 4:

	  printf ("Change the password for which user (1/2/3)?\n");
	  int cp;
	  scanf ("%d", &cp);
	  if (change_password (cp) == false)
	    {
	      printf ("\nCould not be changed\n");
	    }
    
     clear_screen();
     first_screen();
	  break;

	case 5:
    
     delete_user_screen_handler();
     clear_screen();
     first_screen();
	     
	  break;

	case 6:
	  break;

	default:
	clear_screen();
	first_screen();
	printf ("Kindly print the numbers listed in the code above:)\n\n");
	}
    }
  while (choice != 6);
  
  return 0;
}

void secondscreenhandler(int user_choice)
{
    clear_screen();
    secondscreen();
    int c;
    do{
        fflush(stdin);
        scanf("%d", &c);
        switch(c)
        {
            case 1:
            thirdscreenhandler(user_choice, c);
            clear_screen();
            secondscreen();
            break;
            case 2:
            thirdscreenhandler(user_choice, c);
            clear_screen();
            secondscreen();
            break;
            case 3:
            thirdscreenhandler(user_choice, c);
            clear_screen();
            secondscreen();
            break;
            case 4:         //Go back to the main screen
            break;
            default:
            clear_screen();
            secondscreen();
            printf("\nPlease enter a valid value\n");
        }
    }while(c!=4);
    return;
}

void thirdscreen()
{
    printf("PICK A CHOICE:\n\n\n");
    printf("1: Display details.\n");
    printf("2: Add an entry\n");
    printf("3: Delete an entry\n");
    printf("4: Go back\n");
    return;
}

node* add_entry(int user_choice, int wallet_choice, node* head)
{
    clear_screen();
    char* temptype = (char*)malloc(50*sizeof(char));
    char* tempcategory = (char*)malloc(100*sizeof(char));
    date tempd;
    int tempamount;
    printf("Enter type ('Income' or 'Expense'): ");
    scanf("%s", temptype);
    printf("Enter category: ");
    scanf("%s", tempcategory);
    printf("Enter date (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &tempd.day, &tempd.month, &tempd.year);
    printf("Enter amount: ");
    scanf("%d", &tempamount);
    head = insert(head, temptype, tempcategory, tempd, tempamount);
    char* name = (char*)malloc(9*sizeof(char));
    build_file_name(user_choice, wallet_choice, name);
    FILE* fp = fopen(name, "a");

    long file_size = ftell(fp);

    if (file_size == 0) {
        fprintf(fp, "Initial Balance: %d\n", initial_balance);
        fprintf(fp, "Goal: %d\n", goal);
    }

    fprintf(fp, "%s\t%s\t%d/%d/%d\t%d\n", temptype, tempcategory, tempd.day, tempd.month, tempd.year, tempamount);
    fclose(fp);
    printf("Entry added successfully...\n");
    free(temptype);
    free(tempcategory);
    free(name);
    return head;
}

void delete_from_file(int user_choice, int wallet_choice, node* head)
{
    char* name = (char*)malloc(9*sizeof(char));
    build_file_name(user_choice, wallet_choice, name);
    FILE* fp = fopen(name, "w");
    fprintf(fp, "Initial Balance: %d\n", initial_balance);
    fprintf(fp, "Goal: %d\n", goal);
    node* h=head;
    while(h!=NULL)
    {
        fprintf(fp, "%s\t%s\t%d/%d/%d\t%d\n", h->type, h->category, h->d.day, h->d.month, h->d.year, h->amount);
        h=h->next;
    }
    printf("Deleted from file...\n");
    fclose(fp);
    free(name);
    return;
}

node* delete_entry(int user_choice, int wallet_choice, node* head)
{
    displaydetails(head);
    if(head==NULL)
    {
        printf("Empty list, nothing to delete...\n");
        return head;
    }
    int n;
    printf("\nEnter the position of the entry to be deleted\n");
    scanf("%d", &n);
    node* p1 = head;
    node* p2 = head->next;
    if(n==1)
    {
        free(head);
        head = p2;
        delete_from_file(user_choice, wallet_choice, head);
        return head;
    }
    int c=2;
    while(p2!=NULL && c<=n)
    {
        if(c==n)
        {
            p1->next = p2->next;
            free(p2);
            delete_from_file(user_choice, wallet_choice, head);
            return head;
        }
        p1=p1->next;
        p2=p2->next;
        c++;
    }
    printf("No such entry found...\n");
    return head;
}

void thirdscreenhandler(int user_choice, int wallet_choice)
{
    clear_screen();
    thirdscreen();
    node* head = linked_list_loader(user_choice, wallet_choice);
    int c;
    do{
        fflush(stdin);
        scanf("%d", &c);
        switch(c)
        {
            case 1:
            displaydetails(head);
            thirdscreen();
            break;
            case 2:
            head = add_entry(user_choice, wallet_choice, head);
            thirdscreen();
            break;
            case 3:
            head = delete_entry(user_choice, wallet_choice, head);
            thirdscreen();
            break;
            case 4:
            break;
            default:
            clear_screen();
            thirdscreen();
            printf("Enter a valid value.\n");
        }
    }while(c!=4);
    head = reset_list(head);
    return;
}

node* reset_list(node* head)
{
    initial_balance = 0;
    goal = 0;
    node* temp=head;
    node* temp2=head->next;
    while(temp->next!=NULL)
    {
        free(temp);
        temp=temp2;
        temp2=temp2->next;
    }
    free(temp);
    return head;
}

node* linked_list_loader(int user_choice, int wallet_choice)
{
    node* head = NULL;
    char* name = (char*)malloc(9*sizeof(char));
    build_file_name(user_choice, wallet_choice, name);
    FILE* fp = fopen(name, "r");
    fscanf(fp, "Initial Balance: %d\n", &initial_balance);
    fscanf(fp, "Goal: %d\n", &goal);
    char* temptype = (char*)malloc(50*sizeof(char));
    char* tempcategory = (char*)malloc(100*sizeof(char));
    date tempd;
    int tempamount;
    while(fscanf(fp, "%s\t%s\t%d/%d/%d\t%d\n", temptype, tempcategory, &tempd.day, &tempd.month, &tempd.year, &tempamount) == 6)
    {
        head = insert(head, temptype, tempcategory, tempd, tempamount);
    }
    free(temptype);
    free(tempcategory);
    free(name);
    fclose(fp);
    return head;
}

void displaydetails(node* head)
{
    int current_balance = initial_balance;
    char expensive_category[50];
    int most_expense=0;
    int net_expense=0;
    node* h = head;
    while(h!=NULL)
    {
        printf("\n%s\t\t%s\t\t%d/%d/%d\t\t%d\n", h->type, h->category, h->d.day, h->d.month, h->d.year, h->amount);
        
        current_balance+=h->amount;
        if(strcmp(h->type, "Expense")==0)
        {
            current_balance-=2*(h->amount);
            net_expense+=h->amount;
            if(h->amount > most_expense)
            {
                most_expense = h->amount;
               strcpy(expensive_category, h->category);
            }
        }
        h=h->next;
    }
    
    printf("\n\nNet Balance: %d\n", current_balance);
    printf("Net expense: %d\n", net_expense);
    printf("Net income: %d\n", current_balance+net_expense-initial_balance);
    printf("Goal: %d\n", goal);
    if(net_expense<=goal)
    {
        printf("Goal is being achieved.\n");
    }
    else
    {
        printf("\nGoal failed.\n\n");
    }
    return;
}

void first_screen()
{
  printf ("WELCOME TO MY WALLET:)\n\n\n");
  printf ("1: USER 1\n");
  printf ("2: USER 2\n");
  printf ("3: USER 3\n");
  printf ("4: Change User password\n");
  printf ("5: Delete data from user\n");           
  printf ("6: Terminate the Program\n\n");
}

bool password (int choice)
{
  FILE *fp;
  fp = fopen ("password.txt", "r");
  int i = 0;
  while (fscanf (fp, "%s", passwords[i]) == 1)	//scanf returns integer value (0/1) or number of successfully read fields.
    //file ptr , string or takes a word , stores it in the 2d array  
    i++;
  char user_pass[100];
  printf ("Enter current password\n");
  scanf ("%s", user_pass);
  fclose (fp);
  if (strcmp (passwords[choice - 1], user_pass) == 0)	
  return true;
  return false;
  
}

bool change_password (int cp)	//for example if cp=1 then it means that the user have to change the password of 1st one
{
  if (password (cp) == false)
    {
      printf ("Sorry! Password is wrong:( \n");
      return false;
    }
  printf ("Enter the new password: ");
  char np[100];
  scanf ("%s", np);
  strcpy (passwords[cp - 1], np);
  FILE *fp;
  fp = fopen ("password.txt", "w");
  for (int i = 0; i < 3; i++)
    {
      fprintf (fp, "%s\n", passwords[i]);
    }
  fclose (fp);
  printf ("New Password is: %s\n", passwords[cp - 1]);

  return true;
}

void delete_data(int user_choice, int wallet_choice)
{
    char* name = (char*)malloc(9*sizeof(char));
    build_file_name(user_choice, wallet_choice, name);
    FILE* fp = fopen(name, "w");
    fclose(fp);
    free(name);
    return;
}

void build_file_name(int user_choice, int wallet_choice, char* name)
{
    *(name+0) = (char)(user_choice + '0');
    *(name+1) = '_';
    switch(wallet_choice)
    {
        case 1:
        *(name+2) = 'P';
        break;
        case 2:
        *(name+2) = 'S';
        break;
        case 3:
        *(name+2) = 'T';
        break;
    }
    *(name+3) = 'W';
    *(name+4) = '.';
    *(name+5) = 't';
    *(name+6) = 'x';
    *(name+7) = 't';
    *(name+8) = '\0';
    return;
}

void secondscreen()
{
        printf("PICK A WALLET-:\n\n");
        printf("1: Personal Wallet\n"); //under personal income and expenses of mostly all types would come
        printf("2: Savings Wallet\n");  //under savings wallet, only incomes will be there.
        printf("3: Trip Wallet\n");     //under trip wallet, income and expenditure incurred on the trip would come.
        printf("4: Go back to the main screen\n");   
}

void delete_user_screen()
{
        printf("Which user's data to erase?-:\n\n");
        printf("1: User 1\n");
        printf("2: User 2\n");
        printf("3: User 3\n");
        printf("4: Go back to the previous screen\n");   
        return;
}

void delete_user_screen_handler()
{
    clear_screen();
    delete_user_screen();
    int choice;
    do
    {
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            delete_data_wallet_handler(choice);
            clear_screen();
            delete_user_screen();
            break;

            case 2:
            delete_data_wallet_handler(choice);
            clear_screen();
            delete_user_screen();
            break;

            case 3:
            delete_data_wallet_handler(choice);
            clear_screen();
            delete_user_screen();
            break;

            case 4:
            break;

            default:
            clear_screen();
	        delete_user_screen();
	        printf ("Kindly print the numbers listed in the code above:)\n\n");
        }
    }while(choice != 4);
}

void delete_data_wallet_handler(int choice)
{
    clear_screen();
    secondscreen();
    int choice_wallet;
    do
    {
        scanf("%d", &choice_wallet);
        switch (choice_wallet)
        {
        case 1:
        delete_data(choice, choice_wallet);
        clear_screen();
        secondscreen();        
        break;

        case 2:
        delete_data(choice, choice_wallet);
        clear_screen();
        secondscreen();
        break;

        case 3:
        delete_data(choice, choice_wallet);
        clear_screen();
        secondscreen();
        break;

        case 4:
        break;
        
        default:
        clear_screen();
	    secondscreen();
	    printf ("Kindly print the numbers listed in the code above:)\n\n");
        }
    } while (choice_wallet != 4);
    return;
}