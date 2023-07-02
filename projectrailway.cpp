
#include<conio.h>
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
class passenger
{
    public:
    char name[20];
    char gender;
    int age;
    int no_of_tickets;
    int train_no;
    int ticket_no;
    int seat_no[5];

};
class ticket
{
    public:
    int train_no;
    int total_seats[72];
    int booked_seat;
    int state;
    int waiting_list;

};

// FUNCTION DECLARATION

void login();
void choice();
void book_ticket();
void train_details();
void pass_details();
void cancel_ticket();
float charge(int,int);
void printticket(char name[],int num_of_seats,int train_num,float charges,int seat_no[]);
void show_choosen_train(int train_num);
void seat_allocation(int ,int ,int seatno[]);
void ticket_record();
void remove_seat(int tno,int no_of_ticket,int seat_no[]);
void seat_available();
void berth_type(int seat_number);

// STARTING OF MAIN FUNCTION

int main()
{


    login();
    ticket_record();
    choice();


}
//---------------------------------------------------------------------------------------
// FUNCTION FOR LOGIN SCREEN
void login()
{
    char username[20];
    char password[15];
    int i,j,ch,k;

    for(k=1; k<=3; k++)
    {

        cout<<"----------------------------------------------------------------------------";
        printf(" \n \n\t\t\t\t\t RAILWAY RESERVATION SYSTEM \t\t\t\t\t\n ");

        printf("\n\n\t\t\t * LOGIN *  \t\t\n\n");

        printf("\t\t\t ENTER THE USERNAME :");
        scanf("%s",&username);
        printf("\t\t\t ENTER THE PASSWORD :");
        for(j=0; j<=5; j++)
        {
            password[j]=getch();
            printf("*");
        }
        password[j]='\0';


        if((strcmp(username,"abcd")==0) && (strcmp(password,"leader")==0))   // CHECKING OF USERNAME AND PASSWORD
        {
            printf("\n\n\n\t\t\t  Welcome to our project && Your login is successful \n");
            printf("\n\n\t\t\t\t  Press any key to continue.......");
            getch();
            break;
        }
        else
        {
            if(k==3)
            {

                printf("\n \n \n \t ----  YOU HAVE EXCEEDED THE LOGIN LIMIT  ----\n \n  \n ");
                exit(0);
            }
            printf("\n INCORRECT  USERNAME  OR  PASSWORD \n");
            printf("\n PRESS ANY KEY TO RE-LOGIN \n");

        }
    }
}
//-----------------------------------------------------------------------------------------------------------
//FUNCTION FOR MAIN MENU
void choice(){
    system("cls");
    int ch;

    while(1)
    {
        system("cls");
        printf("----------------------------------------------------------------------------");
        printf(" \n \n\t\t\t\t\t RAILWAY RESERVATION SYSTEM \t\t\t\t\t\n ");

        printf("\nSELECT YOUR OPTION :");
        printf("\n\n1.VIEW ALL AVAILABLE TRAINS\n2.BOOK TICKET\n3.VIEW PASSENGER DETAILS\n4.VIEW ALL SEATS AVAILABLE \n5.CANCEL TICKET\n6.QUIT");
        printf("\n\n Enter your choice :");
        scanf("%d",&ch);
        if(ch==6)
        {
            exit(0);
        }
        else
        {
            switch(ch)
            {
            case 1:
            {
                train_details();
                break;
            }
            case 2:
            {
                book_ticket();
                break;
            }
            case 3:
            {
                pass_details();
                break;
            }
            case 4:
            {
                seat_available();
                break;
            }
            case 5:
            {
                cancel_ticket();
                break;
            }
            default:
            {
                printf("wrong choice ! try again");
                break;
            }
            }

        }
    }
}
//-----------------------------------------------------------------------------------------------------------
//FUNCTION FOR BOOKING
void book_ticket()
{

    system("cls");
    fstream fp;
    char confirm;
    float charges;
     passenger e;
    int s,seatno[5];
    long int recsize;
    fp.open("passenger_details.DAT",ios::out|ios::app|ios::binary);
   /* if(fp==NULL)
    {
        fp=fopen("passenger_details.DAT","wb+");
    }*/
    recsize=sizeof(e);



    fp.seekg( 0, ios::beg);

    printf("\n  Enter details of passenger \n \n   Name :   ");
    cin.ignore();
    cin.getline(e.name,50);
    printf("\n Geder (M /F) :   ");
    scanf("%c",&e.gender);
    printf("\n Age :  ");
    scanf("%d",&e.age);
    printf("\n Number of tickets:  ");
    scanf("%d",&e.no_of_tickets );
    cin.ignore();
    train_details();

    printf("\n \n Enter train no: ");
s1:
    scanf("%d",&e.train_no);

    if(e.train_no>=1001 && e.train_no <=1005)
    {
        printf("\n\nConfirm Ticket (Y/N):>");
s2:
        scanf(" %c",&confirm);
        if(confirm == 'y')
        {

            charges=charge(e.train_no,e.no_of_tickets);
            seat_allocation(e.no_of_tickets,e.train_no,e.seat_no);
            if(e.seat_no[0]==-121)
            {
                printf("All seats and waiting lists are full : ");
                goto s3;
            }
            printticket(e.name,e.no_of_tickets,e.train_no,charges,e.seat_no);
            fp.write((char*)&e,recsize);
            printf("\n==================");
            printf("\n Reservation Done\n");
            printf("==================");
            printf("\nPress any key to go back to Main menu");
        }
        else
        {
            if(confirm=='n')
            {
                printf("\nReservation Not Done!\nPress any key to go back to  Main menu!");
            }
            else
            {
                printf("\nInvalid choice entered! Enter again-----> ");
                goto s2;
            }
        }

    }
    else
    {
        printf("\nInvalid train Number! Enter again--> ");
        goto s1;
    }






s3:

    fp.close();

    getch();

}
//-----------------------------------------------------------------------------------------------------------
//FUNCTION TO SHOW DETAILS OF PASSENGERS
void pass_details()
{
    int i;
    fstream ft;
    long int recsize;
    float charges;
     passenger e;
    system("cls");
    recsize =sizeof(e);
    ft.open("passenger_details.DAT",ios::in |ios::app|ios::binary);
    if(ft.eof())
    {
        printf("\nNo passenger Details ");
    }
    else
    {
        printf("\n\n pname\t\tage\t\tno of seats\t\ttrain no\t\tcharges\t\tseat no ");
        printf("\n-------------------------------------------------------------------------------------------------------------------------\n\n");
        while(ft.read((char*)&e,recsize))
        {
            charges=charge(e.train_no,e.no_of_tickets);
            printf("\n %s\t\t%d\t\t%d\t\t\t%d \t\t\t%.2f\t \t",e.name,e.age,e.no_of_tickets,e.train_no,charges);
            for (i=0; i<e.no_of_tickets; i++)
            {
                if(e.seat_no[i]>0)
                    printf("  %d  ",e.seat_no[i]);
                else
                {
                    int s= -1*e.seat_no[i];
                    printf(" WL %d  ",s);
                }
            }
        }
    }
    ft.close();
    getch();
}
//-----------------------------------------------------------------------------------------------------------
//FUNCTION TO SHOW ALL AVAILABLE TRAINS
void train_details()
{
    system("cls");
    printf("------------------------------------------------------------------------------------------------");
    printf("\nTr.No\tName\t\t\tfrom\t\t\t to\t\t\tCharges\n");
    printf("------------------------------------------------------------------------------------------------");
    printf("\n1001\tRajdhani  Express\tPatna(6.00AM)    \tNewDelhi(4.00PM) \tRs.5000 ");
    printf("\n1002\tShatabdi  Express\tAhmedabad(2.30PM)\tMumbai(9.35PM)   \tRs.4000");
    printf("\n1003\tGatimaan  Express\tNew Delhi(8.10AM)\tJhansi(12.35PM)  \tRs.3000");
    printf("\n1004\tIndore    Express\tIndore(4.00PM)   \tKhajuraho(6.00AM)\tRs.2000");
    printf("\n1005\tBangalore Express\tNew Delhi(9.15PM)\tBangalore(1.40PM) \tRs.1000");

    getch();
}
//-------------------------------------------------------------------------------------------
//FUNCTION FOR CALCULATING CHARGES
float charge(int train_num,int num_of_seats)
{

    if (train_num==1001)
    {
        return(5000.0*num_of_seats);
    }
    if (train_num==1002)
    {
        return(4000.0*num_of_seats);
    }
    if (train_num==1003)
    {
        return(3000.0*num_of_seats);
    }
    if (train_num==1004)
    {
        return(2000.0*num_of_seats);
    }
    if (train_num==1005)
    {
        return(1000.0*num_of_seats);
    }

}
//-------------------------------------------------------------------------------------------
//FUNCTION TO CANCEL TICKETS
void cancel_ticket()
{
    system("cls");
     passenger e;
    fstream fp,ft;
    float charges;
    long int recsize;
    char name[20];
    int age,day;
    float returnf;
    int choice;
    printf("Enter name of passenger : ");
    scanf("%s",name);
    printf("Enter age of passenger : ");
    scanf("%d",&age);
    printf("Enter the days before cancellation :");
    scanf("%d",&day);
    fp.open("passenger_details.DAT",ios::in |ios::out|ios::app|ios::binary);
    recsize=sizeof(e);
    ft.open("temp.DAT",ios::in |ios::out|ios::app|ios::binary);
    printf("\nEnter 1--> Confirm cancellation \nEnter 2 --> Quit\n");
    scanf("%d",&choice);
    if(choice==1)
    {

        while(fp.read((char*)&e,recsize))
        {

            if(strcmp(e.name,name)!=0)
            {
                ft.write((char*)&e,recsize);
            }
            else if(e.age!=age)
            {
                ft.write((char*)&e,recsize);
            }
            else
            {

                float fare=charge(e.train_no,e.no_of_tickets);



                if (day>20)
                {
                    returnf = fare;                    // NO MONEY DEDUCED FOR DAYS > 20
                }
                else if((day<=20) && (day>=7))
                {
                    returnf =fare - (fare *0.3);     // 30% MONEY DEDUCED
                }
                else if((day<7) && (day>=3))
                {
                    returnf = fare - (fare*0.5);    // 50% MONEY DEDUCED
                }
                else
                {
                    returnf = fare- fare ;      //NO MONEY RETURN
                }

                printf("Return fares = %f\n",returnf);
                printf("\n Your ticket cancelled successfully......\n");
                remove_seat(e.train_no,e.no_of_tickets,e.seat_no);
            }
        }
        fp.close();
        ft.close();
        remove("passenger_details.DAT");
        rename("temp.DAT","passenger_details.DAT");
    }

    else if (choice==2)
    {
        printf("\tYour ticket not cancelled   \n");
    }
    else
    {
        printf("\n Invalid data\n");
    }
    printf("\n\n\n\t press any key to continue..........");
    getch();

}
//FUNCTION TO REMOVE SEAT AFTER CANCELLATION
void remove_seat(int tno,int no_of_ticket,int seat_no[])
{
    int i,j,k;
     ticket t;
     fstream fp;
    long int recsize=sizeof(t);
    fp.open("ticket.DAT",ios::in |ios::out|ios::app|ios::binary);
    while(fp.read((char*)&t,recsize))
    {
        if(t.train_no==tno)
            break;
    }

    for (i = 0; i < no_of_ticket; i++)
    {
        if(seat_no[i]>=0)
        {
        t.total_seats[seat_no[i]-1]=0;
        t.booked_seat-=1;
        }
        else
        {
            t.waiting_list--;
        }
    }
    fp.seekp(fp.tellg()-recsize,ios::cur);
    fp.write((char*)&t,recsize);
    fp.close();


    getch();
}
//--------------------------------------------------------------------------------------------------
//FUNCTION TO PRINT ALL THE SPECIFICATIONS OF PASSENGER DURING BOOKING
void printticket(char name[],int num_of_seats,int train_num,float charges,int seat_no[])
{
    int i;
    system("cls");
    printf("-------------------\n");
    printf("\tTICKET\n");
    printf("-------------------\n\n");
    printf("Name:\t\t\t%s",name);
    printf("\nNumber Of Seats:\t%d",num_of_seats);
    printf("\nTrain Number:\t\t%d",train_num);
    show_choosen_train(train_num);
    printf("Your seat numbers : \n");
    for (i=0; i<num_of_seats; i++)
    {
        if(seat_no[i]>0)
        {
             berth_type(seat_no[i]);
        }
        else
        {
            int s= -1*seat_no[i];
            printf(" WL %d  ",s);
        }
    }
    printf("\nCharges:\t\t%.2f",charges);
}
//------------------------------------------------------------------------------
//FUNCTION TO CHOOSE TRAIN DURING BOOKING
void show_choosen_train(int train_num)
{

    if (train_num==1001)
    {
        printf("\nTrain:\t\t\tRajdhani Express");
        printf("\nDestination:\t\tPatna  to NewDelhi");
        printf("\nDeparture:\t\t 5.00 am ");
        printf("\nArrival: \t \t 4.00 pm\n");
    }
    if (train_num==1002)
    {
        printf("\nTrain:\t\t\tShatabdi Express");
        printf("\nDestination:\t\tAhmedabad to Mumbai");
        printf("\nDeparture:\t\t 2.30 Pm ");
        printf("\nArrival: \t \t 9.00 pm\n");
    }
    if (train_num==1003)
    {
        printf("\nTrain:\t\t\tGatiman Express");
        printf("\nDestination:\t\tHazrat Nizamuddin  to jhansi");
        printf("\nDeparture:\t\t 8.00 am ");
        printf("\nArrival: \t \t 12.35 pm\n");
    }
    if (train_num==1004)
    {
        printf("\nTrain:\t\t\tIndore Express");
        printf("\nDestination:\t\tIndore  to khajuraho");
        printf("\nDeparture:\t\t 4.00 Pm ");
        printf("\nArrival: \t \t 6.00 Am\n");
    }
    if (train_num==1005)
    {
        printf("\nTrain:\t\t\t karnataka Express");
        printf("\nDestination:\t\tNew Delhi  to Bangalore");
        printf("\nDeparture:\t\t 9.50 Pm ");
        printf("\nArrival: \t \t 1.40 pm\n");
    }

}
//-------------------------------------------------------------------------------------------------------------------------
//FUNCTION TO SHOW ALL SEATS AVAILABLE FOR PARTICULAR TRAIN
void seat_available()
{
    int tno;
    int i,j,k;
     ticket t;
    fstream fp;
    long int recsize=sizeof(t);
    printf("Enter train number: ");
    scanf("%d",&tno);
    if(tno>=1001 && tno <=1005)
    {


        fp.open("ticket.DAT",ios::in |ios::app|ios::binary);
        while(fp.read((char*)&t,recsize))
        {
            if(t.train_no==tno)
                break;
        }
        if(t.booked_seat<=72)
        {
        printf("\nNo of seats available = %d\n",72-t.booked_seat);
        }
        else if(t.waiting_list<=15)
        {
               printf(" \n Waiting List %d",t.waiting_list);
        }
        else
            {
                printf(" All seats and Waiting lists are full");

        }
        printf("\n");

        fp.close();
    }
    else
    {
        printf("\nInvalid train Number! Enter again--> ");
    }
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------
//FUNCTION TO STORE RECORD OF ALL TRAINS IN FILE
void ticket_record()
{
    fstream fp;
    long int recsize ;
     ticket t[5],tt;
    int i,j;
    recsize=sizeof(t[0]);
    fp.open("ticket.DAT",ios::in |ios::out|ios::app|ios::binary);
    if(fp.eof())
    {
        fp.open("ticket.DAT",ios::in |ios::out|ios::app|ios::binary);
        for(i=0; i<5; i++)
        {
            t[i].train_no=1001 +i;
            t[i].waiting_list=0;
            for(j=0; j<72; j++)
            {
                t[i].total_seats[j]=0;
            }
            t[i].booked_seat=0;
            fp.write((char*)&t[i],recsize);
        }

    }
    fp.close();
}
//----------------------------------------------------------------------------------------
//FUNCTION FOR ALLOTING THE SEATS DURING BOOKING
void seat_allocation(int no_of_seats ,int tno,int seatno[])
{

    int i,p;
    struct ticket t;
    fstream fp;
    long int recsize=sizeof(t);
    fp.open("ticket.DAT",ios::in |ios::out|ios::app|ios::binary);
    while(fp.read((char*)&t,recsize))
    {
        if(t.train_no==tno)
            break;
    }
    printf(" \n No of seats available = %d \n",72-t.booked_seat);

    // seat booking from middle of the berth to end of the berth
    if(t.state==0)
    {
        for( i=36,p=0; p<no_of_seats && i<72; i++)
        {
            if(t.total_seats[i]==0)
            {
                seatno[p]=i+1;
                p++;
                t.state=1;
                t.booked_seat+=1;
                t.total_seats[i]=i+1;
            }
        }
    }
    // seat booking from middle to the starting of the berth
    else
    {
        for( i=35,p=0; i>=0 && p<no_of_seats; i-- )
        {

            if(t.total_seats[i]==0)
            {
                seatno[p]=i+1;
                p++;
                t.state=0;
                t.booked_seat+=1;
                t.total_seats[i]=i+1;

          }
        }
    }
    // Remaining seats
    if(p<no_of_seats)
    {
        for( i=0; p<no_of_seats && i<72; i++)
        {
            if(t.total_seats[i]==0)
            {
                seatno[p]=i+1;
                p++;
                t.booked_seat+=1;
                t.total_seats[i]=i+1;
            }
        }

    }
    // Waiting list
    if (p<no_of_seats)
    {


        for( i=0; p<no_of_seats && t.waiting_list<=15; i++ )
        {
            seatno[p]=(-1*t.waiting_list)-1;
            t.waiting_list++;
            p++;
        }

    }
    // All seats and Waiting list is full
    if(p<no_of_seats)
    {
        seatno[0]=-121;
        return ;
    }

   fp.seekp(fp.tellg()-recsize,ios::cur);
    fp.write((char*)&t,recsize);
    fp.close();
    // getch();


}
//--------------------------------------------------------------------------------------------------------------
//FUNCTION FOR DECLARING BERTH TYPE DURING PRINTING SPECIFICATIONS OF PASSENGER IN BOOKING
void berth_type(int seat_number)
{
    if(seat_number>0 && seat_number<72)
    {
        if(seat_number%8==1||seat_number%8==4)
        {
            printf(" %d is  lower berth \n",seat_number);
        }
        else if(seat_number%8==2||seat_number%8==5)
        {
            printf(" %d is  middle  berth \n",seat_number);
        }
        else if(seat_number%8==3||seat_number%8==6)
        {
            printf(" %d is  upper  berth \n",seat_number);
        }
        else if(seat_number%8==7)
        {
            printf(" %d is  side lower berth \n",seat_number);
        }
        else
        {
            printf(" %d is  side upper\n",seat_number);
        }

    }
}


//================================ END OF CODE ===============================