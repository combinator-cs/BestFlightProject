#include<iostream>
#include <list>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>
#include<ctype.h>


using namespace std;


//----------------------------------------------------------------------------------------------------------------------------------
                                                   // CONSOLE HANDLING

/*

Name         | Value
             |
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15





*/

COORD coord = {0,0}; ///intilises x,y to 0,0
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; ///takes in c,y co-ordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void SetColor(int ForgC)
{
      WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


void ClearConsoleToColors(int ForgC, int BackC)
 {
 WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
               //Get the handle to the current output buffer...
 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                     //This is used to reset the carat/cursor to the top left.
 COORD coord = {0, 0};
                  //A return value... indicating how many chars were written
                    //   not used but we need to capture this since it will be
                      //   written anyway (passing NULL causes an access violation).
  DWORD count;

                               //This is a structure containing all of the console info
                      // it is used here to find the size of the console.
 CONSOLE_SCREEN_BUFFER_INFO csbi;
                 //Here we will set the current color
 SetConsoleTextAttribute(hStdOut, wColor);
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                          //This fills the buffer with a given character (in this case 32=space).
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
                          //This will set our cursor position for the next print statement.
      SetConsoleCursorPosition(hStdOut, coord);
 }
 return;
}
//----------------------------------------------------------------------------------------------------------------------------------





//----------------------------------------------------------------------------------------------------------------------------------
                                        //Global variables and Define statements

#define INF 999999999  //infinite length showing no connection

list<int> *pArr; //pointer to an array containing adjacency list for containing paths
int posPath; // for storing index of various paths

#define NCity 8 // no. of ports
// A directed graph using adjacency list representation

int myStNo; //find seat no. of user for bookTicket function
#define MaxSeatNo 10  //defining maximum seats in a flight
#define maxListSize 500 // size of list containing all paths from src to dest.
int flNo;     //find flight no. of user for bookTicket function




//----------------------------------------------------------------------------------------------------------------------------------
                                            // Function definitions

int findFlights(int gArr[],int no,int tm);    //no indicates no. of total nodes




//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

                                                        // GRAPH - some part of code was taken from online sources like GeeksForGeeks and others then were edited accordingly

class Graph
{
	int V; // No. of vertex in graph
	list<int> *adj; // Pointer to an array containing adjacency lists

	// A recursive function used by printAllPaths()
	void printAllPathsUtil(int , int , bool [], int [], int &);

public:
	Graph(int V); // Constructor
	void addEdge(int u, int v);
	void printAllPaths(int s, int d);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v); // Add v to u’s list.
}

// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];

	// Create an array to store paths
	int *path = new int[V];
	int path_index = 0; // Initialize path[] as empty

	// Initialize all vertices as not visited
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to print all paths
	printAllPathsUtil(s, d, visited, path, path_index);
}

// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[],
							int path[], int &path_index)
{
	// Mark the current node and store it in path[]
	visited[u] = true;
	path[path_index] = u;
	path_index++;

	// If current vertex is same as destination, then print
	// current path[]
	if (u == d)
	{

		for (int i = 0; i<path_index; i++)
        {
			//cout << path[i] << " ";
            pArr[posPath].push_back(path[i]);
        }
		//cout << endl;
        ++posPath;
	}
	else // If current vertex is not destination
	{
		// Recur for all the vertices adjacent to current vertex
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (!visited[*i])
				printAllPathsUtil(*i, d, visited, path, path_index);
	}

	// Remove current vertex from path[] and mark it as unvisited
	path_index--;
	visited[u] = false;
}


//----------------------------------------------------------------------------------------------------------------------------------
                                            // Function definitions 2

void codeControl(Graph g, int gpW[NCity][NCity]);
int priceCalc(Graph g,int gpW[NCity][NCity],int s,int d, int time);



//----------------------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------------------
                                            // function to error handle wrong integer input

int checkInt(char ch[])
{
    int check = 1;
    int l = strlen(ch);
    for(int i = 0; i<l; i++)
    {
        if(ch[i]>=48 && ch[i]<=57);

        else
        {
            check = 0;
            break;
        }
    }

    if(check == 0)
        return 0;
    else
        return 1;
}






int finalPrice(int userPr,int gpW[NCity][NCity], int time)
{
    list<int>::iterator j;
    list<int>::iterator k;
    int price = 0;
    int minPrice = INF; //initially sets price to infinite
    int coNodes[posPath]; //to store number of nodes in each path
    for(int i=0; i<posPath ; i++)
    {
            coNodes[i] = 0;
    }

    int leastNodes = INF; //to store least number of nodes
    for(int i = 0; i<posPath; i++)
    {
        price = 0;
        k = pArr[i].begin();
        int x; // length of temporary variable(array)
        x = pArr[i].size();
        int tempArr[x];
        int c1 =  0; //counter for temporary array

        for(j = pArr[i].begin(); j != pArr[i].end(); ++j)
        {
            ++k;
            if( k != pArr[i].end())
                price+= gpW[*j][*(k)];

            coNodes[i]++;
            tempArr[c1++] = *j;
        }
       if(findFlights(tempArr,coNodes[i],time) == 1)
        {
                price = price + (coNodes[i]-2)*300;

            if(price<=minPrice)
            {
                if(price == minPrice && leastNodes>coNodes[i])
                    leastNodes = coNodes[i];
                else
                    minPrice = price;

                leastNodes = coNodes[i];
            }
        }


    }

    if(userPr > minPrice)
    {
        cout<<"\nBest Flight software will charge you just(After adding special discounts): "<<minPrice<<"\n\n";
        return 1;
    }
    else if(userPr == minPrice && minPrice != INF)
    {
        cout<<"\nBest Flight software will charge you just: "<<minPrice<<"\n\n";
        return 1;
    }
    else if(minPrice == INF)
        cout<<"\nNo such Flight available."<<endl;
    else
        cout<<"\nNo such Flight available."<<endl;
        return 0;

}


//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

                                                //  FILE HANDLING AND MANAGEMENT



void updateFlightData(int fltNo, int seat)
{

    FILE* flights;
    flights = fopen("planeData.txt","r");
    FILE* tempF;
    tempF = fopen("tempPlaneData.txt","w");

    int planeNo;
    int src;
    int dest;
    int time;
    int seatCount;
    int ihop;  //hop node value
    char ch;
    while(getc(flights) != EOF)
    {
        fscanf(flights,"%d%d%d%d%d",&planeNo,&src,&dest,&time,&seatCount);

        if(planeNo == fltNo)
            fprintf(tempF," %d %d %d %d %d",planeNo,src,dest,time,seat);
        else
            fprintf(tempF," %d %d %d %d %d",planeNo,src,dest,time,seatCount);
        int i = 0;
        while((ch = getc(flights))!='\n' )
        {
            fscanf(flights,"%d",&ihop);
            i++;
            fprintf(tempF," %d",ihop);
        }
        fprintf(tempF,"\n");

    }


    fclose(tempF);
    fclose(flights);

    remove("planeData.txt");
    rename("tempPlaneData.txt","planeData.txt");

}


void updateFlightData(int fltNo)
{

    FILE* flights;
    flights = fopen("planeData.txt","r");
    FILE* tempF;
    tempF = fopen("tempPlaneData.txt","w");

    int planeNo;
    int src;
    int dest;
    int time;
    int seatCount;
    int ihop;  //hop node value
    char ch;
    while(getc(flights) != EOF)
    {
        fscanf(flights,"%d%d%d%d%d",&planeNo,&src,&dest,&time,&seatCount);

        if(planeNo == fltNo)
            fprintf(tempF," %d %d %d %d %d",planeNo,src,dest,time,seatCount-1);
        else
            fprintf(tempF," %d %d %d %d %d",planeNo,src,dest,time,seatCount);
        int i = 0;
        while((ch = getc(flights))!='\n' )
        {
            fscanf(flights,"%d",&ihop);
            i++;
            fprintf(tempF," %d",ihop);
        }
        fprintf(tempF,"\n");

    }


    fclose(tempF);
    fclose(flights);

    remove("planeData.txt");
    rename("tempPlaneData.txt","planeData.txt");

}








void bookTicket(FILE* passengers, Graph g, int gpW[NCity][NCity])
{

    SetColor(5);
    cout<<"\n\n\n\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout<<"\t\t\t\t\t\t\t\tWELCOME TO BOOKING PANEL\n";
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout<<"\n\t\t\t\tCHOOSE THE SOURCE AND DESTINATION FROM THE LIST BY ENTERING THE SERIEL NO. WRITTEN AGAINST THEM\n\n";
    cout<<"\t\t\t\t\t\tNEW DELHI : 0"<<"\t\t\tMUMBAI     : 1\n";
    cout<<"\t\t\t\t\t\tNEW YORK  : 2"<<"\t\t\tWASHINGTON : 3\n";
    cout<<"\t\t\t\t\t\tTOKYO     : 4"<<"\t\t\tCANBERRA   : 5\n";
    cout<<"\t\t\t\t\t\tLONDON    : 6"<<"\t\t\tPARIS      : 7\n";


    char name[20];
    int age;
    char ageS[20]; //ageS denote string input will be taken then later will be converted to integer, similarly for all integers for error handling
    int src;  //source of flight
    char srcS[20];
    int dest; //destination of flight
    char destS[20];
    int time; //time of flight
    char timeS[20];
    int mob;  // Mobile no.
    char mobS[20];
    long date;
    char dateS[20];

sourceInp:
    cout<<"\n\n\t\t\tEnter source: ";
    cin>>srcS;
    if(checkInt(srcS) == 1)
    {
        src = atoi(srcS);
        if(src<0 || src>8)
        {
            cout<<"\nEnter correct source input\n";
            goto sourceInp;
        }
    }
    else
    {
        cout<<"\nEnter correct input\n";
        goto sourceInp;
    }

destInp:
    cout<<"\n\t\t\tEnter destination: ";
    cin>>destS;
    if(checkInt(destS) == 1)
    {
        dest = atoi(destS);
        if(dest<0 || dest>8)
        {
            cout<<"\nEnter correct destination input\n";
            goto destInp;
        }
    }
    else
    {
        cout<<"\nEnter correct input\n";
        goto destInp;
    }

timeInp:
    cout<<"\n\n\t\t\tEnter time of your flight(use 24-hour format): ";
    cin>>timeS;
    if(checkInt(timeS) == 1 )
    {
        time = atoi(timeS);
    }
    else
    {
        cout<<"\nEnter correct time input\n";
        goto timeInp;
    }

    if(time>0 && time<24);
    else
    {
        cout<<"Enter correct time input\n";
        goto timeInp;
    }


dateInp:
    cout<<"\n\n\t\t\tEnter date of your flight(use DDMMYYYY format): ";
    cin>>dateS;
    if(checkInt(dateS)==1)
    {
        date = atoi(dateS);
    }
    else
    {
        cout<<"\nEnter correct date input\n";
        goto dateInp;
    }

    int month = date%1000000;
    month = month/10000;

    if(strlen(dateS)!=8 || date/1000000>31 || date/1000000 <1 || month<1 || month>12 || date%10000 <2019 || date%10000>2020 || (date%10000 == 2019 && month <11 ) || (date%10000 == 2019 && month == 11 && date/1000000 <29))
    {
        //cout<<month <<" "<<date/1000000<<" "<<date%10000;
        cout<<"\nEnter correct date input\n";
        goto dateInp;
    }
    if((month == 4 || month == 6||month==9||month==11)&& date/1000000>30)
    {
        cout<<"\nEnter correct date input\n";
        goto dateInp;
    }

    if(month==2 && date/1000000 >29)
    {
        cout<<"\nEnter correct date input\n";
        goto dateInp;
    }


    int check = priceCalc(g,gpW,src,dest,time);

                                            // If flight preferred was available

    if(check == 1)
    {

    cout<<"Ticket of your demand is available. Enter Y to proceed for booking.\nEnter any other key to go back to main menu.";
    char choice3[20];
    cin>>choice3;
    if(strcmp(choice3,"Y")==0 || strcmp(choice3,"y")==0)
    {

    cout<<"Enter your details\n\n\n\t\t\t";
    cout<<"Enter Name: ";
    cin>>name;

ageInp:
    cout<<"\n\t\t\tEnter age: ";
    cin>>ageS;
    if(checkInt(ageS) == 1)
    {
        age = atoi(ageS);
    }
    else
    {
        cout<<"\nEnter correct Age input\n";
        goto ageInp;
    }

    if(age<0 || age>130)
    {
        cout<<"\nEnter correct Age input\n";
        goto ageInp;
    }

mobInp:
    cout<<"\n\t\t\tEnter your Mobile number: ";
    cin>>mobS;
    if(checkInt(mobS) == 1)
    {
        mob = atoi(mobS);
    }
    else
    {
        cout<<"\nEnter correct Mobile number input\n";
        goto mobInp;
    }

    if(mob<0)
    {
        cout<<"\nEnter correct Mobile number input\n";
        goto mobInp;
    }


    int fltNo = flNo; //flight no. of customer
    passengers = fopen("E:/Projects and lab/JIIT sem-3/DS project/Practice/Prac1/passengersData.txt","a");

    fprintf(passengers,"\n%s %d %d %d %d %d %d %d", name,age,src,dest,time,mob,++myStNo,fltNo);

    updateFlightData(fltNo,myStNo);

    cout<<"\n\t\t\t\t\tTICKET SUCCESSFULLY BOOKED\n";
    cout<<"\n\t\t\t\t\tEnter P to print the ticket or any other to go to Main menu: ";
    char printOp[20]; //option to check for print or not
    cin>>printOp;
    if(strcmp(printOp,"p")==0 || strcmp(printOp,"P")==0)
    {


        char srcP[20]=""; //source to be printed
        char destP[20]=""; //dest. to be printed
        switch(src)
        {
        case 0:
            strcpy(srcP,"NEW DELHI");
            break;
        case 1:
            strcpy(srcP,"MUMBAI");
            break;
        case 2:
            strcpy(srcP,"NEW YORK");
            break;
        case 3:
            strcpy(srcP,"WASHINGTON D.C.");
            break;
        case 4:
            strcpy(srcP,"TOKYO");
            break;
        case 5:
            strcpy(srcP,"CANBERRA");
            break;
        case 6:
            strcpy(srcP,"LONDON");
            break;
        case 7:
            strcpy(srcP,"PARIS");
            break;
        }

        switch(dest)
        {
        case 0:
            strcpy(destP,"NEW DELHI");
            break;
        case 1:
            strcpy(destP,"MUMBAI");
            break;
        case 2:
            strcpy(destP,"NEW YORK");
            break;
        case 3:
            strcpy(destP,"WASHINGTON D.C.");
            break;
        case 4:
            strcpy(destP,"TOKYO");
            break;
        case 5:
            strcpy(destP,"CANBERRA");
            break;
        case 6:
            strcpy(destP,"LONDON");
            break;
        case 7:
            strcpy(destP,"PARIS");
            break;
        }




    system("CLS");
    gotoxy(56,10);
    printf("%c",201);

    for(int i = 57; i<106; i++)
        printf("%c",205);

    gotoxy(106,10);
        printf("%c",187);

    gotoxy(56,32);
    printf("%c",200);

    for(int i = 57; i<106; i++)
        printf("%c",205);

    gotoxy(106,32);
        printf("%c",188);


    for(int i=11; i<32; i++)
    {
        gotoxy(56,i);
        printf("%c",186);
        gotoxy(106,i);
        printf("%c",186);
    }

    gotoxy(56,13);
    printf("%c",186);
    printf("\t\tBEST FLIGHT PVT LTD.");

    gotoxy(56,14);
    printf("%c",186);
    printf("\t  -------------------------------");


    gotoxy(56,16);
    printf("%c",186);
    printf("\t\t   FLIGHT TICKET");


    gotoxy(62,19);
    cout<<"Name: "<<name;
    gotoxy(62,21);
    cout<<"From: "<<srcP<<" To "<<destP;
    gotoxy(62,23);
    cout<<"Date(DDMMYYYY): "<<dateS;
    gotoxy(62,25);
    cout<<"Time(24-hr): "<<timeS;
    gotoxy(73,28);
    cout<<"FLIGHT NO.: "<<fltNo;
    gotoxy(73,29);
    cout<<"Seat No.: "<<myStNo;

    gotoxy(73,40);

    }
    }

    }
    fclose(passengers);
}


void getPassDetails(FILE* passengers)
{

    passengers = fopen("passengersData.txt","r");
    char name[20];
    int age;
    int src;
    int dest;
    int time;
    int mob;
    int seatNo;
    int fltNo;

    printf("\n\t\t\t\t\tCUSTOMER NAMES:\n\n");
    while(getc(passengers) != EOF)
    {
        fscanf(passengers,"%s%d%d%d%d%d%d%d",name,&age,&src,&dest,&time,&mob,&seatNo,&fltNo);
        printf("\t\t\t\t\t%s\n",name);
    }
    fclose(passengers);
}


void cancelTicket(FILE* passengers)
{
    SetColor(6);

    passengers = fopen("passengersData.txt","r");
    FILE *temp;
    temp = fopen("temp.txt","w");

ftnoTag:
    cout<<"Enter Flight No. where you want to cancel: ";
    char FtNoS[20];
    cin>>FtNoS;
    int FtNo,StNo;
    if(checkInt(FtNoS)==1)
    {
        FtNo = atoi(FtNoS);
    }
    else
    {
        cout<<"Please enter valid Flight no. ";
        goto ftnoTag;
    }
stnoTag:
    cout<<"\nEnter Seat No. where you want to cancel: ";
    char StNoS[20];
    cin>>StNoS;
    if(checkInt(StNoS)==1)
    {
        StNo = atoi(StNoS);
    }
    else
    {
        cout<<"Please enter valid Seat no. ";
        goto stnoTag;
    }

    char name[20];
    int age;
    int src;
    int dest;
    int time;
    int mob;
    int seatNo;
    int fltNo;
    int flightSave; //saves flight no where ticket is cancelled
    int check = 0;  //check if such ticket is there or not
    while(getc(passengers) != EOF)
    {
        fscanf(passengers,"%s%d%d%d%d%d%d%d",name,&age,&src,&dest,&time,&mob,&seatNo,&fltNo);
        if(fltNo != FtNo || seatNo!=StNo)
        {
            fprintf(temp,"\n%s %d %d %d %d %d %d %d",name,age,src,dest,time,mob,seatNo,fltNo);
        }

        if(fltNo == FtNo && seatNo==StNo)
        {
            check = 1;
            flightSave = fltNo;
        }
    }

    if(check == 0)
        cout<<"\n\n\t\t\t\tNo such booking present\n";
    else
    {
        updateFlightData(flightSave);
        cout<<"\n\n\t\t\t\tTicket successfully canceled\n";
    }
    fclose(temp);
    fclose(passengers);

    remove("passengersData.txt");
    rename("temp.txt","passengersData.txt");


}

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------



void addPlaneData(FILE* planes)
{


    /*
        In this function bookTicket and other functions, input has been taken all in strings
        and if integer was required then its first checked that input string is
        correct or not(i.e. it is number or not) then it is converted to integer using
        atoi() function. Thus all temporary string inputs are taken with the same
        name as their integer counterpart and also adding 'S' at their end
        e.g - src is integer, its string input is taken as srcS
     */

    cout<<"\t\t\t\tEnter plane data:"<<endl;
    int planeNo; //plane number
    char planeNoS[20];
    int src;
    char srcS[20];
    int dest;
    char destS[20];
    int time;
    char timeS[20];
    int seatCount = 0;

planeNoInp:
    cout<<"\t\t\t\tenter plane no.: ";
    cin>>planeNoS;
    if(checkInt(planeNoS) == 1 )
    {
        planeNo = atoi(planeNoS);
    }
    else
    {
        cout<<"\nEnter correct input\n";
        goto planeNoInp;
    }

sourceInp:
    cout<<"\n\t\t\t\tenter source: ";
    cin>>srcS;
    if(checkInt(srcS) == 1)
    {
        src = atoi(srcS);
    }
    else
    {
        cout<<"\nEnter correct input\n";
        goto sourceInp;
    }

destInp:
    cout<<"\n\t\t\t\tEnter destination: ";
    cin>>destS;
    if(checkInt(destS) == 1)
    {
        dest = atoi(destS);
    }
    else
    {
        cout<<"\nEnter correct input\n";
        goto destInp;
    }

timeInp:
    cout<<"\n\t\t\t\tenter time: ";
    cin>>timeS;
    if(checkInt(timeS) == 1 )
    {
        time = atoi(timeS);
    }
    else
    {
        cout<<"\nEnter correct time input\n";
        goto timeInp;
    }

    if(time>0 && time<24);
    else
    {
        cout<<"Enter correct time input\n";
        goto timeInp;
    }


nHopInp:
    cout<<"\n\t\t\t\tenter no. of hops: ";
    int nHop;
    char nHopS[20];
    cin>>nHopS;
    if(checkInt(nHopS) == 1)
    {
        nHop = atoi(nHopS);
    }
    else
    {
        cout<<"\nEnter correct input\n";
        goto nHopInp;
    }

    int hop[nHop];

    cout<<"\n\t\t\t\t\tEnter hop Junction codes: ";
    for(int i = 0; i<nHop ; i++)
    {
        char hopTemp[20];
    hopInp:
        cout<<"\n\t\t\t\t\t";
        cin>>hopTemp;
        if(checkInt(hopTemp) == 1)
        {
            hop[i] = atoi(hopTemp);
        }
        else
        {
            cout<<"\nEnter correct input\n";
            goto hopInp;
        }
    }

    planes = fopen("planeData.txt","a");
    fprintf(planes," %d %d %d %d %d",planeNo,src,dest,time,seatCount);
    for(int i = 0; i<nHop; i++)
        fprintf(planes," %d",hop[i]);
    fprintf(planes,"\n");
    fclose(planes);
}





void readPlaneData(FILE* planes)
{
    int planeNo; //plane number
    int src;
    int dest;
    int time;
    int nHop;
    int seatCount;
    cout<<"\n\t\t\t\t\t\tEnter no. of hops: ";
    cin>>nHop;
    int hop[nHop];
    char ch;
    int i = 0;

    planes = fopen("planeData.txt","r");

    printf("\n\t\t\t\tPlane No.  Source  Destination  Time  Seat Count  Hop Station codes\n");

    while(getc(planes)!=EOF)
    {
        i = 0;
        fscanf(planes,"%d%d%d%d%d",&planeNo,&src,&dest,&time,&seatCount);
        //printf("%d %d %d %d ",planeNo,src,dest,time);
        while((ch = getc(planes))!='\n' )
        {
            fscanf(planes,"%d",&hop[i]);
            //printf("%d ",hop[i]);
            i++;
        }
        //cout<<i;
        int j = 0;
        if(i==nHop)
        {
            printf("\n\t\t\t\t%d\t   %d\t     %d\t         %d\t%d\t\t",planeNo,src,dest,time,seatCount);

            for(j=0; j<nHop; j++)
            {
                printf("  %d ",hop[j]);
            }
        }
    }

    fclose(planes);

}





void adminOptions(Graph g, int gpW[NCity][NCity])
{
    ClearConsoleToColors(9,15);
    FILE *passengers; //creating a file for passenger details
    passengers = fopen("passengersData.txt","r");
    fclose(passengers);

    FILE *planes; //creating file for storing flight data
    planes = fopen("planeData.txt","a");
    fclose(planes);

    system("CLS");
adminMenu:
    cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t :OPTIONS FOR ADMIN:\n\n";
    cout<<"\n\t\t\t\t\t\t1111. Add a new flight"<<"\t\t\t\t 2222. View Database of flights\n";
    cout<<"\n\t\t\t\t\t\t3333. View Customer Database"<<"\t\t\t 9999. To go back to Main Menu";
    int adCh; //admin choice
    char adChS[20];
    cout<<"\n\n\n";
adChInp:
    cout<<"\n\t\t\t\t\t\t\t\t-:Please give an Input of your choice:-\n\t\t\t\t\t\t\t\t\t\t    ";
    cin>>adChS;

    if(checkInt(adChS) == 1)
    {
        adCh = atoi(adChS);
    }
    else
    {
        cout<<"\nEnter correct input\n";
        goto adChInp;
    }

    if(adCh == 1111)
        addPlaneData(planes);
    else if(adCh == 2222)
        readPlaneData(planes);
    else if(adCh == 3333)
        getPassDetails(passengers);
    else if(adCh == 9999)
        return;
    else
    {
        system("CLS");
        cout<<"\n\n\n\t\t\t\t\t\t Enter correct input\n";
        goto adminMenu;
    }

    getchar();
        cout<<"\n\n\t\t\tEnter any button to go back to Admin  menu";
        if(getchar())
        {
            system("CLS");
            goto adminMenu;
        }


    cout<<"\n";
}




//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------------------

int priceCalc(Graph g,int gpW[NCity][NCity], int s, int d, int time)
{
    pArr = new list<int>[maxListSize];
    posPath = 0;
	//int s = 2, d = 3;
	//cout << "\nFollowing are all different paths from " << s
    //      << " to " << d << endl;
	g.printAllPaths(s,d);

	cout<<"\n";
	list<int>::iterator j;
    list<int>::iterator k;


    int userPr; //maximum price set by user
    char userPrS[20];
userPrInp:
    cout<<"SET YOUR MAX PRICE: ";
    cin>>userPrS;
    if(checkInt(userPrS) == 1 && strlen(userPrS)<8)
    {
        userPr = atoi(userPrS);
    }
    else
    {
        cout<<"\nEnter Legitimate price\n";
        goto userPrInp;
    }

    return finalPrice(userPr,gpW,time);   // to calculate the if ticket available or not and calculate final price
}
//----------------------------------------------------------------------------------------------------------------------------------



int findFlights(int gArr[],int no, int tm)    //no indicates no. of total nodes, tm is time put by customer
{

    FILE* planes;
    int planeNo; //plane number
    int src;
    int dest;
    int time;
    int seatCount;
    int nHop = no-2;
    int hop[nHop];
    char ch;
    int i = 0;

    planes = fopen("planeData.txt","r");
    int check = 1;
    while(getc(planes)!=EOF)
    {
        i = 0;
        fscanf(planes,"%d%d%d%d%d",&planeNo,&src,&dest,&time,&seatCount);
        while((ch = getc(planes))!='\n' )
        {
            fscanf(planes,"%d",&hop[i]);
            i++;
        }
        //cout<<"\n"<<i<<" "<<nHop<<endl;
        check = 1;
        if(i==nHop && seatCount<MaxSeatNo && tm == time)
        {
            for(int k = 0; k<nHop+2; k++)
            {
                if(k==0)
                {
                    if(src != gArr[k])
                    {
                        check = 0;
                        break;
                    }
                }
                else if(k==nHop+1)
                {
                    if(dest != gArr[k])
                    {
                        check = 0;
                        break;
                    }
                }
                else
                {
                    if(hop[k-1] != gArr[k])
                    {
                        check = 0;
                        break;
                    }
                }
            }

            if(check == 1)
            {
               // for(int k=0;k<no;k++)
                //    cout<<gArr[k]<<" ";
                //cout<<"\n";
                flNo = planeNo;
                myStNo = seatCount;
                fclose(planes);
                return 1;
            }

        }

    }

fclose(planes);
return 0;

}





//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
                                                    // FINAL CODE CONTROL - FLOW

void codeControl(Graph g, int gpW[NCity][NCity])
{
    system("CLS");
    //MENU:


start:
    cout<<"\n\n\t\t\t\t--------------------------------------------WELCOME---------------------------------------------------\n\n"<<endl;
    cout<<"\n\n\n\n\n\t\t\t\t\t\t\t\t    :OPTIONS FOR CUSTOMER:\n";
    cout<<"\n\t\t\t\t      1. Book a Ticket"<<"\t\t\t\t\t\t      2. Cancel your Ticket\n";

    cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t  Enter 1991 to get into EXIT \n";

    cout<<"\n\n\n\t\t\t\t\t\t\tOr Enter 9999 to get into Administrator Panel\n\n\n\n\t\t\t\t\t\t\t    ";
optionInp:
    cout<<"-:Please give an Input of your choice:-\n\t\t\t\t\t\t\t\t\t    ";
    int option; //to store option
    char optionS[20];
    cin>>optionS;
    if(checkInt(optionS) == 1)
    {
        option = atoi(optionS);
    }
    else
    {
        cout<<"\nEnter correct input\n\n\t\t\t\t\t\t\t    ";
        goto optionInp;
    }

    // Enter admin mode
    if(option == 9999)
    {
    enterpass:
        system("CLS");
        char adminPass[20]; //password for admin
        cout<<"Enter your password to continue: ";
        cin>>adminPass;
        if(strcmp(adminPass,"*****")==0)
        {
            adminOptions(g,gpW);
            ClearConsoleToColors(0,11);
        }

        else
        {
            SetColor(4);
            cout<<"\n\t\t\t\t\tWrong password entered\n";
            char mkCh1[20];
            cout<<"\n\t\t    Enter 1 to enter password again or any other button to go to Main menu: ";
            cin>>mkCh1;
            if(strcmp(mkCh1,"1")==0)
            {
                ClearConsoleToColors(0,11);
                goto enterpass;
            }
            else
            {
                system("CLS");
                ClearConsoleToColors(0,11);
                goto start;
            }
        }

    }

    // Different customer services
    else if(option != 1991)
    {
        FILE *passengers; //creating a file for passenger details
        passengers = fopen("passengersData.txt","r");
        fclose(passengers);
        system("CLS");
        if(option == 1 )
        {
            bookTicket(passengers,g,gpW);
            SetColor(0);
        }
        else if(option == 2)
          {
            cancelTicket(passengers);
            SetColor(0);
          }
        else
        {
            system("CLS");
            cout<<"\n        \t\t\t\t\t\t\t\tPlease select correct option\n\n";
            goto start;
        }

            system("pause");
            system("CLS");
            goto start;
    }

    else if(option == 1991)
    {
    exitOp:            // option to exit the software
        char ch3[20];
        SetColor(4);
        cout<<"Do you really want to exit (Y/N): ";
        cin>>ch3;

        if(strcmp(ch3,"Y")==0 || strcmp(ch3,"y")==0)
            return;
        else if(strcmp(ch3,"N")==0 || strcmp(ch3,"n")==0)
        {
            system("CLS");
            SetColor(0);
            goto start;

        }
        else
        {
            system("CLS");
            cout<<"\n\n    \t\t\t\t\t\t\tPlease select correct option\n\n";
            SetColor(0);
            system("pause");
            goto exitOp;
        }

    }
    system("CLS");
    goto start;
}

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------------------------------------------
                                                        //PROGRESS BAR(LOADING BAR) DISPLAY


void hidecursor()       //source - https://stackoverflow.com/questions/30126490
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void showcursor()       //source - https://stackoverflow.com/questions/30126490
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 2;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}


void display_progress_bar()
{

    printf("\n\n");
    printf("\t\t\t\t\t\t\t\t\t    LOADING\n\n");
    hidecursor();
    Sleep(250);
    for(int i = 0; i<=60; i++)
    {
        printf("\r\t\t\t\t\t\t");
        for(int j = 0;j<=i;j++)
        {
            printf("%c",219);
        }
        Sleep(20);
        printf("%c",219);
    }
}





//----------------------------------------------------------------------------------------------------------------------------------


// Driver program
int main()
{


//----------------------------------------------------------------------------------------------------------------------------------


    /*
                                            CITY DESCRIPTION

                                    CITY NAME               NODE VALUE

                                    NEW DELHI                   0
                                    MUMBAI                      1
                                    CHENNAI                     2
                                    KOLKATA                     3
                                    NEW YORK                    4
                                    WASHINGTON D.C.             5


    */

        // GRAPH CREATION

	Graph g(8);
	g.addEdge(0, 1); g.addEdge(1, 0); g.addEdge(0, 2); g.addEdge(0, 3);
	g.addEdge(3, 0); g.addEdge(2, 0);
	g.addEdge(2, 1); g.addEdge(1, 2); g.addEdge(1, 3); g.addEdge(3, 1);
	g.addEdge(0, 4); g.addEdge(4, 0); g.addEdge(0, 5); g.addEdge(5, 0);
    g.addEdge(0, 6); g.addEdge(6, 0);
    g.addEdge(1, 4); g.addEdge(4, 1); g.addEdge(1, 5); g.addEdge(5, 1);
    g.addEdge(1, 7); g.addEdge(7, 1);
    g.addEdge(2, 5); g.addEdge(5, 2); g.addEdge(2, 6); g.addEdge(6, 2); g.addEdge(2, 7); g.addEdge(7, 2);
    g.addEdge(3, 5); g.addEdge(5, 3); g.addEdge(3, 7); g.addEdge(7, 3);
    g.addEdge(4, 5); g.addEdge(5, 4); g.addEdge(4, 6); g.addEdge(6, 4);
    g.addEdge(5, 6); g.addEdge(6, 5); g.addEdge(5, 7); g.addEdge(7, 5);
    g.addEdge(6, 7); g.addEdge(7, 6);

    int gpW[8][8] = {{0,5000,8125,10050,6050,4300,7192,INF},   //matrix storing edge weight, weight here is assumed to be price(this was thought at start of project)
                    {5000,0,3500,11132,7700,6668,INF,4000},
                    {8125,3500,0,INF,INF,2000,6700,7865},
                    {10050,11132,INF,0,INF,6400,INF,3999},
                    {6050,7700,INF,INF,0,2885,5000,INF},
                    {4300,6668,2000,6400,2885,0,8100,10200},
                    {7192,INF,6700,INF,5000,8100,0,1999},
                    {INF,4000,7865,3999,INF,10200,1999,0}};




//----------------------------------------------------------------------------------------------------------------------------------
                                        // FINAL CODE - FLOW MANAGEMENT




    ClearConsoleToColors(4,14);

    cout<<"\n\n\n\n\n\n\n\n";
    system("type WelcomeCode.txt");
    cout<<"\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t";
    system("pause");
    display_progress_bar();
    Sleep(500);

    ClearConsoleToColors(0,11);

    codeControl(g,gpW);      //All code control flow


    return 0;
}
