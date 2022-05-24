#include<iostream>
#include<string>
#include<iomanip>
#include<windows.h>
#include<conio.h>
#include<fstream>
using namespace std;

string flightList[50][7];
string seatList[50][10][10];//0-2 first a then 3-9 economy
int countf=0;

void Setup();

void USER();

void ReserveSeat(string userName, string Phone);
void UserTicket(string userName, string Phone, string flight);
void FlightSchedule(string flight);
void DisplayPassenger(string flight);
void Removebooking(string userName, string flight);
int allOccupied(int index,int k, int l);
int BookSeat(string user,int index);
string SearchUser(string userName);

void ADMIN();

int SearchIndexNo(string flightNo);
void AddNewFlight();
void EditFlight();
void DeleteFlight();
void AllFlightSchedule();
void FlightSave();
void FlightLoad();
void SeatSave();
void SeatLoad();

int main()
{

    system("title Airlines Reservation System");
    Setup();
    system("Color 0A");

    while(true)
    {
        system("cls");
        string star="**************************************";
        cout<<star<<"Welcome To Airlines Reservation System"<<star<<"\n"<<endl;

        cout<<star<<"Login Menu"<<star<<"\n"<<endl;
        cout<<"1. User"<<endl;
        cout<<"2. Administrator"<<endl;
        cout<<"3. Exit Program"<<endl;

        char choice = _getch();

        if(choice=='1')
            USER();

        else if(choice=='2')
            ADMIN();

        else if(choice=='3')
        {
            cout<<"Are you sure? (y/n): ";

            char exit=_getch();

            if(exit=='y' || exit=='Y')
                return 0;
            else
                break;
        }

        else
            cout<<"Wrong input"<<endl;
    }

    return 0;
}


void Setup()
{
    for (int i=0; i<50; i++)
        for (int j=0; j<10; j++)
            for (int k=0; k<10; k++)
            {
                if(k==0 || k==9)
                    seatList[i][j][k]="Window";
                else if(k==4 || k==5)
                    seatList[i][j][k]="Aisle";
                else
                    seatList[i][j][k]="Center";
            }
}


int allOccupied(int index, int k,int l)
{
	int countSeat=0;

    for(int i=k; i<l; i++)
    {
        for(int j=0; j<10; j++)
            if(seatList[index][i][j]=="Center" || seatList[index][i][j]=="Window" || seatList[index][i][j]=="Aisle")
                countSeat++;
    }

    return countSeat;
}


void Display(int index, int z, int k)
{

    cout<<"Seats : "<<endl;

    if(z==0)
        cout<<setw(10)<<"First class "<<endl;

    else if(z==3)
        cout<<setw(10)<<"Economy class "<<endl;


    cout<<setw(5)<<""<<setw(10)<<"1"<<setw(10)<<"2"<<setw(10)<<"3"<<setw(10)<<"4"<<setw(10)<<"5";
    cout<<setw(10)<<"|||||"<<setw(10)<<"6"<<setw(10)<<"7"<<setw(10)<<"8"<<setw(10)<<"9"<<setw(10)<<"10"<<""<<endl;


    for (int i=z; i<k; i++)
    {
        cout<<setw(5)<<i+1;
        for (int j=0; j<10; j++)
        {
            if(seatList[index][i][j]=="Center" || seatList[index][i][j]=="Window" || seatList[index][i][j]=="Aisle")
                cout<<setw(10)<<seatList[index][i][j];
            else
                cout<<setw(10)<<"Booked";
            if(j==4)
                cout<<setw(10)<<"|||||";
        }
        cout<<""<<endl;
    }
}

int BookSeat(string user, int index)
{
    int choice, Class, check, amount=stoi(flightList[index][6]);

    cout<<"Enter 1 for first class, 2 for Economy class,any other to exit:"<<endl;
    Class=_getch();

    if(Class=='1')
    {
        int seat=allOccupied(index,0,3);

        if(seat>0)
            check=0;
        else
            check=1;

        if(check)
        {
            cout<<"First Class Seats are full"<<endl;
            cout<<"Press any key to return"<<endl;
            _getch();
        }

        else
        {
            int i=0, n;

            cout<<"Price of each ticket is "<<amount*2<<""<<endl;

            cout<<"Enter number of seats: ";
            cin>>n;

            if(n>seat)
            {
                cout<<"Not Enough Seats"<<endl;
                cout<<"Press any key to return"<<endl;
                _getch();

                return 0;
            }

            while(i<n)
            {
                system("cls");
                string star="**************************************";
                cout<<star<<"Seat Reservation Menu"<<star<<"\n"<<endl;

                Display(index,0,3);

                int x,y;
                cout<<"Enter row (at left) and column(at top) number of seat to register: ";
                cin>>x>>y;

                x=x-1;
                y=y-1;

                if(x<0 || x>2)
                {
                    cout<<"Invalid Seat Row"<<endl;
                    cout<<"Try again"<<endl;
                    _getch();

                    continue;
                }

                if(y<0 || y>9)
                {
                    cout<<"Invalid Seat Column"<<endl;
                    cout<<"Try again"<<endl;
                    _getch();

                    continue;
                }

                if(seatList[index][x][y]=="Center" || seatList[index][x][y]=="Window" || seatList[index][x][y]=="Aisle")
                {
                    seatList[index][x][y]=user;

                    cout<<"Seat Booked"<<endl;
                    _getch();

                    i++;
                }

                else
                {
                    cout<<"Seat already occupied"<<endl;
                    cout<<"Try again"<<endl;
                    _getch();
                }
            }

            cout<<"Booking Completed"<<endl;
            cout<<"Amount deducted : "<<amount*2*n<<""<<endl;
            cout<<"Press any key to continue";
            getch();

            return 1;
        }
    }

    if(Class=='2')
    {
        int seat=allOccupied(index,3,10);

        if(seat>0)
            check=0;
        else
            check=1;

        if(check)
        {
            cout<<"Economy Class Seats are full"<<endl;
            cout<<"Press any key to return"<<endl;
            _getch();
        }
        else
        {
            int i=0,n;

            cout<<"Price of each ticket is "<<amount<<""<<endl;

            cout<<"Enter number of seats: ";
            cin>>n;

            if(n>seat)
            {
                cout<<"Not Enough Seats"<<endl;
                cout<<"Press any key to return"<<endl;
                _getch();

                return 0;
            }

            while(i<n)
            {
                system("cls");
                string star="**************************************";
                cout<<star<<"Seat Reservation Menu"<<star<<"\n"<<endl;

                Display(index,3,10);

                int x,y;
                cout<<"Enter row (at left) and column(at top) number of seat to register: ";
                cin>>x>>y;

                x=x-1;
                y=y-1;

                if(x<3 || x>9)
                {
                    cout<<"Invalid Seat Row"<<endl;
                    cout<<"Try again"<<endl;
                    _getch();

                    continue;
                }

                if(y<0 || y>9)
                {
                    cout<<"Invalid Seat Column"<<endl;
                    cout<<"Try again"<<endl;
                    _getch();

                    continue;
                }

                if(seatList[index][x][y]=="Center" || seatList[index][x][y]=="Window" || seatList[index][x][y]=="Aisle")
                {
                    seatList[index][x][y]=user;

                    cout<<"Seat Booked"<<endl;
                    _getch();

                    i++;
                }

                else
                {
                    cout<<"Seat already occupied"<<endl;
                    cout<<"Try again"<<endl;
                    _getch();
                }
            }

            cout<<"Booking Completed"<<endl;
            cout<<"Amount deducted : "<<amount*n<<""<<endl;
            cout<<"Press any key to continue";
            getch();

            return 1;
        }
    }

    return 0;
}



string SearchUser(string userName)
{

    for (int i=0; i<50; i++)
        for (int j=0; j<10; j++)
            for (int k=0; k<10; k++)
            {
                if(seatList[i][j][k]==userName)

                    return flightList[i][0];
            }

    return "";
}


void ReserveSeat(string userName, string phone)
{
    system("cls");
    string star="**************************************";
    cout<<star<<"Seat Reservation Menu"<<star<<"\n"<<endl;

    string flightNo="";
    string ticketNo;

    cout<<"Enter Flight No: ";
    getline(cin, flightNo);

    int index=SearchIndexNo(flightNo);

    if(index==-1)
    {
        cout<<"Flight not found!"<<endl;
        cout<<"Press any key to return to user menu"<<endl;
        _getch();
    }

    else
    {
        int check=BookSeat(userName,index);

        system("cls");
        string star="**************************************";
        cout<<star<<"Seat Reservation Menu"<<star<<"\n"<<endl;

        if(check==1)
        {
            ticketNo="fl"+flightNo+phone.substr(1,3);

            cout<<"your ticket is booked"<<endl;
            cout<<"Please note you ticket number:  "<<ticketNo<<""<<endl;
            _getch();
        }
        else
        {
            cout<<"Your reservation process was aborted"<<endl;
            cout<<"Sorry for inconvenience"<<endl;
            cout<<"Press any key to return to user menu"<<endl;
            getch();
        }
    }
}


void UserTicket(string userName, string Phone, string flight)
{
    system("cls");
    string star="**************************************";
    cout<<star<<"User Ticket Menu"<<star<<"\n"<<endl;

    if(flight=="")
    {
        cout<<"No reservation done.First reserve please"<<endl;
        cout<<"\n\n Press any key to return";
        _getch();

        return;
    }

    string ticketNo="fl"+flight+Phone.substr(1,3);

    int index=SearchIndexNo(flight);
    int amount=stoi(flightList[index][6]);
    int Count=0, x=2;

    for (int j=0; j<10; j++)
    {
        for (int k=0; k<10; k++)
        {
            if(seatList[index][j][k]==userName)
            {
                Count++;
                if(j<3)
                {
                    x=1;
                }
            }
        }
    }

    string userClass;
    if(x==1)
        userClass="First Class";
    else
        userClass="Economy Class";

    cout<<left<<setw(20)<<"Showing Ticket of "<<userName<<endl;
    cout<<left<<setw(20)<<"Ticket No.: "<<ticketNo<<endl;
    cout<<left<<setw(20)<<"User Name: "<<userName<<endl;
    cout<<left<<setw(20)<<"User Phone No.: "<<Phone<<endl;
    cout<<left<<setw(20)<<"Flight No.: " <<flight<<endl;
    cout<<left<<setw(20)<<"Class: " <<userClass<<endl;
    cout<<left<<setw(20)<<"Flight From: "<<flightList[index][4]<<endl;
    cout<<left<<setw(20)<<"Flight Destination: "<<flightList[index][5]<<endl;
    cout<<left<<setw(20)<<"Number of seats: "<<Count<<endl;
    cout<<left<<setw(20)<<"Booking Amount: "<<amount*x*Count<<endl;

    cout<<"\n\n Press any key to return";
    _getch();
}

void DisplayPassenger(string flight)
{
    system("cls");
    string star="**************************************";
    cout<<star<<"Seat reservation in Flight"<<star<<"\n"<<endl;

    if(flight=="")
    {
        cout<<"No reservation done.First reserve please"<<endl;
        cout<<"\n\n Press any key to return";
        getch();

        return;
    }

    int index=SearchIndexNo(flight);

    if(index==-1)
    {
        cout<<"Flight not found!"<<endl;
        cout<<"Press any key to return to user menu"<<endl;
        _getch();
    }
    else
    {
        cout<<"Seats arrangement "<<endl;

        for (int i=0; i<10; i++)
        {
            if(i==0)
                cout<<setw(10)<<"First class "<<endl;

            else if(i==3)
                cout<<setw(10)<<"Economy class "<<endl;

            cout<<setw(2)<<(i+1)<<"  ";
            cout<<setw(10)<<seatList[index][i][0];
            cout<<setw(10)<<seatList[index][i][1];
            cout<<setw(10)<<seatList[index][i][2];
            cout<<setw(10)<<seatList[index][i][3];
            cout<<setw(10)<<seatList[index][i][4];

            cout<<setw(10)<<"|||||";

            cout<<setw(10)<<seatList[index][i][5];
            cout<<setw(10)<<seatList[index][i][6];
            cout<<setw(10)<<seatList[index][i][7];
            cout<<setw(10)<<seatList[index][i][8];
            cout<<setw(10)<<seatList[index][i][9]<<""<<endl;
        }

        cout<<"\n\n Press any key to return";
        _getch();
    }
}

void Removebooking(string userName, string flight)
{
    system("cls");
    string star="**************************************";
    cout<<star<<"User Remove Reservation Menu"<<star<<"\n"<<endl;

    if(flight=="")
    {
        cout<<"No reservation done to cancel"<<endl;
        cout<<"\n\n Press any key to return";
        _getch();

        return;
    }

    int index=SearchIndexNo(flight);

    int c=0, cost=0, amount=stoi(flightList[index][6]);

    for (int j=0; j<10; j++)
        for (int k=0; k<10; k++)
        {
            if(seatList[index][j][k]==userName)
            {
                if(k==0 || k==9)
                    seatList[index][j][k]="Window";
                else if(k==4 || k==5)
                    seatList[index][j][k]="Aisle";
                else
                    seatList[index][j][k]="Center";

                if(j<3)
                    cost+=amount*2;
                else
                    cost+=amount;
                c++;
            }
        }

    cout<<userName<<" reservation for "<<c<<" has been removed"<<endl;
    cout<<"Amount Returned : "<<int(cost*0.8)<<endl<<endl;

    cout<<"\n\n Press any key to return";
    _getch();
}

void FlightSchedule(string flight)
{
    system("cls");
    string star="***************************";
    cout<<star<<"Flight Arrival and Departure query"<<star<<"\n"<<endl;

    if(flight=="")
    {
        cout<<"No reservation done.First reserve please"<<endl;
        cout<<"\n\n Press any key to return";
        getch();

        return;
    }

    int index=SearchIndexNo(flight);

    if(index==-1)
    {
        cout<<"Flight not found!"<<endl;
        cout<<"Press any key to return to"<<endl;
        _getch();
    }
    else
    {
        cout<<left<<setw(20)<<"Flight No";
        cout<<left<<setw(20)<<"Flight Name";
        cout<<left<<setw(20)<<"Flight From";
        cout<<left<<setw(20)<<"Flight Destination";
        cout<<left<<setw(20)<<"Departure Time";
        cout<<left<<setw(20)<<"Arrival Time";
        cout<<left<<setw(20)<<"Flight Amount"<<endl;

        cout<<left<<setw(20)<<flightList[index][0];
        cout<<left<<setw(20)<<flightList[index][1];
        cout<<left<<setw(20)<<flightList[index][2];
        cout<<left<<setw(20)<<flightList[index][3];
        cout<<left<<setw(20)<<flightList[index][4];
        cout<<left<<setw(20)<<flightList[index][5];
        cout<<left<<setw(20)<<flightList[index][6]<<""<<endl;

        cout<<"\n\n Press any key to return";
        _getch();
    }
}

int SearchIndexNo(string flightNo)
{
    int index=-1;

    for(int i=0; i<countf; i++)
    {
        if(flightList[i][0]==flightNo)
        {
            index=i;

            break;
        }
    }

    return index;
}

void AddNewFlight()
{
    system("cls");
    string star="**************************************";
    cout<<star<<"Add New Flight Menu"<<star<<"\n"<<endl;

    if(countf>=50)
    {
        cout<<"Flight list full"<<endl;
        _getch();
    }

    else
    {
        string flightNo="";
        cout<<"Enter Flight No: ";
        getline(cin, flightNo);

        int index=SearchIndexNo(flightNo);

        if(index==-1)
            flightList[countf][0]=flightNo;

        else
        {
            cout<<"Flight number already existed"<<endl;
            cout<<"Aborted process"<<endl;
            _getch();

            return;
        }

        cout<<"Enter Flight Name: ";
        getline(cin, flightList[countf][1]);

        cout<<"Enter Flight From: ";
        getline(cin, flightList[countf][2]);

        cout<<"Enter User Destination: ";
        getline(cin, flightList[countf][3]);

        cout<<"Enter Departure Time: ";
        getline(cin, flightList[countf][4]);

        cout<<"Enter Arrival Time: ";
        getline(cin, flightList[countf][5]);

        cout<<"Enter Amount: ";
        getline(cin, flightList[countf][6]);

        countf++;
        cout<<"Flight added successfully"<<endl;
        cout<<"\n\n Press any key to return";
        _getch();
    }
}

void EditFlight()
{
    system("cls");
    string star="**************************************";
    cout<<star<<"Edit Flight Menu"<<star<<"\n"<<endl;
    AllFlightSchedule();

    string flightNo="";
    cout<<"\nEnter flight No to edit: ";
    getline(cin, flightNo);

    int index=SearchIndexNo(flightNo);

    if(index==-1)
    {
        cout<<"Flight not found!"<<endl;
        _getch();
    }

    else
    {

        cout<<"Enter Flight Name: ";
        getline(cin, flightList[index][1]);

        cout<<"Enter Flight From: ";
        getline(cin, flightList[index][2]);

        cout<<"Enter User Destination: ";
        getline(cin, flightList[index][3]);

        cout<<"Enter Departure Time: ";
        getline(cin, flightList[index][4]);

        cout<<"Enter Arrival Time: ";
        getline(cin, flightList[index][5]);

        cout<<"Enter Amount: ";
        getline(cin, flightList[index][6]);

        cout<<"Flight edited successfully"<<endl;
        cout<<"\n\n Press any key to return";
        _getch();
    }
}

void DeleteFlight()
{
    system("cls");
    string star="**************************************";
    cout<<star<<"Delete Flight Menu"<<star<<"\n"<<endl;
    AllFlightSchedule();
    string flightNo="";
    cout<<"\nEnter flight No to edit: ";
    getline(cin, flightNo);

    int index=SearchIndexNo(flightNo);

    if(index==-1)
    {
        cout<<"Flight not found!"<<endl;
        _getch();
    }

    else
    {
        while(index!=countf)
        {
            flightList[index][0]=flightList[index+1][0];
            flightList[index][1]=flightList[index+1][1];
            flightList[index][2]=flightList[index+1][2];
            flightList[index][3]=flightList[index+1][3];
            flightList[index][4]=flightList[index+1][4];
            flightList[index][5]=flightList[index+1][5];
            flightList[index][6]=flightList[index+1][6];

            for(int i=0; i<10; i++)
                for(int j=0; j<10; j++)
                    seatList[index][i][j]=seatList[index+1][i][j];

            index++;
        }

        countf--;

        cout<<"\nFlight Deleted..."<<endl;
        cout<<"\n\n Press any key to return";
        _getch();
    }
}


void AllFlightSchedule()
{
    system("cls");
    string star="****************************";
    cout<<star<<"Flight Arrival and Departure Timetable"<<star<<""<<endl;

    cout<<left<<setw(20)<<"Flight No";
    cout<<left<<setw(20)<<"Flight Name";
    cout<<left<<setw(20)<<"Flight From";
    cout<<left<<setw(20)<<"Flight Destination";
    cout<<left<<setw(20)<<"Departure Time";
    cout<<left<<setw(20)<<"Arrival Time";
    cout<<left<<setw(20)<<"Flight Amount"<<endl;

    for(int i=0; i<countf; i++)
    {
        cout<<left<<setw(20)<<flightList[i][0];
        cout<<left<<setw(20)<<flightList[i][1];
        cout<<left<<setw(20)<<flightList[i][2];
        cout<<left<<setw(20)<<flightList[i][3];
        cout<<left<<setw(20)<<flightList[i][4];
        cout<<left<<setw(20)<<flightList[i][5];
        cout<<left<<setw(20)<<flightList[i][6]<<""<<endl;
    }

    cout<<"\n\n Press any key to return";
    _getch();
}

void FlightSave()
{
    ofstream file("flight.txt");

    if(file.is_open())
    {
        file<<countf<<"\n";

        for(int i=0; i<countf; ++i)
        {
             for(int j=0; j<7; ++j)
            {
                file<<setw(20)<<flightList[i][j];
            }

            file<<"\n";
        }
    }

    file.close();
}

void FlightLoad()
{
    ifstream file("flight.txt");

    if(file.is_open())
    {
        file>>countf;

        for(int i=0; i<countf; ++i)
        {
             for(int j=0; j<7; ++j)
            {
                file>>setw(20)>>flightList[i][j];
            }
        }
    }

    file.close();
}

void SeatSave()
{
    ofstream file("Seats.txt");

    if(file.is_open())
    {

        for(int i=0; i<countf; ++i)
        {
             for(int j=0; j<10; ++j)
            {
                for(int k=0; k<10; ++k)
                {
                    file<<setw(20)<<seatList[i][j][k];
                }

                file<<"\n";
            }

            file<<"\n";
        }
    }

    file.close();

    cout<<"File Saved successfully "<<endl;
    cout<<"\n\n Press any key to return";
    _getch();
}

void SeatLoad()
{
    ifstream file("Seats.txt");

    if(file.is_open())
    {
        for(int i=0; i<countf; ++i)
             for(int j=0; j<10; ++j)
                for(int k=0; k<10; ++k)
                    file>>setw(20)>>seatList[i][j][k];
    }

    file.close();

    cout<<"File loaded successfully "<<endl;
    cout<<"\n\n Press any key to return";
    _getch();
}

void ADMIN()
{
    system("cls");

    string password ="";
    cout<<"Enter Administrator password: ";
    fflush(stdin);
    getline(cin, password);

    if(password!="dsa" && password!="DSA")
    {
        cout<<"Wrong Password"<<endl;
        _getch();

        return;
    }

    while(true)
    {
        system("cls");
        string star="**************************************";
        cout<<star<<"Airlines Reservation Administrator Menu"<<star<<"\n"<<endl;

        cout<<"1. Add Flight"<<endl;
        cout<<"2. Edit Flight"<<endl;
        cout<<"3. Delete Flight"<<endl;
        cout<<"4. Flight Schedule Timetable"<<endl;
        cout<<"5. Flight Seat Booking"<<endl;
        cout<<"6. Save and Load flight details"<<endl;
        cout<<"7. Log out"<<endl;

        char choice = _getch();

        switch (choice)
        {
            case '1':
            {
                AddNewFlight();

                break;

            }
            case '2':
            {
                EditFlight();

                break;
            }
            case '3':
            {
                DeleteFlight();

                break;
            }
            case '4':
            {
                AllFlightSchedule();

                break;
            }
            case '5':
            {
                system("cls");

                string flightNo="";
                cout<<"\n\nEnter flight No to see: ";
                getline(cin, flightNo);

                DisplayPassenger(flightNo);

                break;
            }
            case '6':
            {
                system("cls");

                string star="**************************************";
                cout<<star<<"Flight details Save/Load Menu"<<star<<"\n"<<endl;
                cout<<"Press 1 to save"<<endl;
                cout<<"Press 2 to load"<<endl;

                choice=_getch();

                if(choice=='1')
                {
                    FlightSave();

                    SeatSave();

                    break;
                }
                if(choice=='2')
                {
                    FlightLoad();

                    SeatLoad();

                    break;
                }
            }
            case '7':
            {
                cout<<"Are you sure? (y/n): ";
                char exit=_getch();

                if(exit=='y' || exit=='Y')
                    return;

                break;
            }
            default:
            {
                cout<<"Wrong input"<<endl;
                cout<<"\n\n Press any key to return";
            }
        }
    }
}


void USER()
{
    string user ="";
    string Phone="";

    int flag;
    while(flag!=2)
    {
        system("cls");

        flag=0;
        cout<<"Enter User Name: ";
        fflush(stdin);
        getline(cin,user);

        if(user=="")
        {
             cout<<"Invalid User name"<<endl;
             cout<<"Press any key to continue";
             _getch();
             continue;
        }
        else
            flag++;
        cout<<"Enter User Phone No: ";
        getline(cin, Phone);

        if(Phone.length()<5)
        {
            cout<<"Invalid Phone number"<<endl;
             cout<<"Press any key to continue";
             _getch();
             continue;
        }
        else
            flag++;
    }

    while(true)
    {
        system("cls");

        string star="**************************************";
        cout<<star<<"Airlines Reservation User Menu"<<star<<"\n"<<endl;

        cout<<"1. Reserve user Seat"<<endl;
        cout<<"2. Show User Ticket"<<endl;
        cout<<"3. Flight Schedule"<<endl;
        cout<<"4. Remove Reservation"<<endl;
        cout<<"5. Log out"<<endl;

        char choice= _getch();

        string flight=SearchUser(user);

        switch (choice)
        {
            case '1':
            {
                if(flight=="")
                {
                    ReserveSeat(user, Phone);
                }
                else
                {
                     string star="**************************************";
                     cout<<star<<"Airlines Reservation User Menu"<<star<<"\n"<<endl;

                     cout<<"You have already done a reservation on flight number: "<<flight<<""<<endl;

                     cout<<"\n\n Press any key to return";
                     _getch();
                }

                break;
            }
            case '2':
            {
                UserTicket(user, Phone, flight);

                break;
            }
            case '3':
            {
                FlightSchedule(flight);

                break;
            }
            case '4':
            {
                Removebooking(user, flight);

                break;
            }
            case '5':
            {
                cout<<"Are you sure? (y/n): ";
                char exit=_getch();

                if(exit=='y' || exit=='Y')
                    return;

                break;
            }
            default:
            {
                cout<<"Wrong input"<<endl;
                cout<<"\n\n Press any key to return";
            }
        }
    }
}
