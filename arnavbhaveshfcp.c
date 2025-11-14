#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
FILE *fptr;
int tno=0;
void create_new_ticket();
void display_data();
int price_calculation(char category, float distance);
void print_ticket(char *source, char *destination, int people, int total_price);
int main()
{
    while(1)
    {
        int action;
        printf("Bus Ticket Generation System ");
        r: printf("\nChoose following by selecting respective serial number : \n 1. Create a new ticket \n 2. Display all data. \n 3. Exit \n\n");
        if(scanf("%d", &action)!=1)
        {
            printf("Invalid input. Try Again\n ");
            while(getchar()!='\n')
            continue;
        }
        else
        {
            switch(action)
            {
                case 1:
                    create_new_ticket();
                    break;
                case 2:
                    display_data();
                    break;
                case 3:
                    printf("Exiting program. ");
                    return 0;
                default:
                    printf("Invalid input. Try again\n");
                    break;
            }
        }
    }
    return 0;
}
void create_new_ticket()
{
    int total_price=0, i=1, people;
    float distance;
    char source[100], destination[100], category;
    tno++;
    printf("Enter source \n");
    scanf("%s", source);
    printf("Enter destination \n");
    scanf("%s", destination);
    p: printf("Enter distance \n");
    scanf("%f", &distance);
    if(distance<=0)
    {
        printf("Invalid input. Try again\n ");
        goto p;
    }
    s: printf("Enter number of people \n");
    scanf("%d", &people);
    if(people<=0)
    {
        printf("Invalid input. Try again \n");
        goto s;
    }
    while(i<=people)
    {
        printf("Enter category: Student: S, Adult: A, Senior Citizen: O \n");
        scanf(" %c", &category);
        if(category!='S' && category!='A' && category!='O')
        {
            printf("Invalid input. Try again\n");
            continue;
        }
        total_price = total_price + price_calculation(category, distance);
        i++;
    }
    print_ticket(source, destination, people, total_price);
    printf("\n\n");
}
void display_data()
{
    fptr = fopen("busticket.txt", "r");
    if(fptr == NULL)
    {
        printf("Unable to open file\n");
        tno=0;
        exit(1);
    }
    char buffer[100];
    while(fgets(buffer, sizeof(buffer), fptr) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(fptr);
}
int price_calculation(char category, float distance)
{
    int price;
    if(category =='S' || category =='O')
    {
        if(distance>=30.0)
            price=20;
        else if (distance>=15.0)
            price=15;
        else if (distance>=5.0)
            price=10;
        else
            price=5;
    }
    else if(category =='A')
    {
        if(distance>=30.0)
            price=40;
        else if (distance>=15.0)
            price=30;
        else if (distance>=5.0)
            price=20;
        else
            price=10;
    }
    return price;
}
void print_ticket(char *source, char *destination, int people, int total_price)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    printf("\n\n");
    printf("\t Ticket no: %d \n\n", tno);
    printf("\t %d-%d-%d ", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    printf("\t\t\t %d:%d:%d \n\n", t->tm_hour, t->tm_min, t->tm_sec);
    printf("\t%s to %s\n\n", source, destination);
    printf("\tNumber of people = %d \n\n", people);
    printf("\t\t Total: Rs.%d \n", total_price);

    fptr = fopen("busticket.txt", "a");
    fprintf(fptr, "\n Ticket no: %d \n %s to %s, Number of people = %d, Total: Rs.%d \n", tno, source, destination, people, total_price);
    fprintf(fptr, "Date: %d-%d-%d, Time: %d:%d:%d\n\n", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, t->tm_hour, t->tm_min, t->tm_sec);
    fclose(fptr);
}
