/*ASSIGNMENT #6
submitted by: Guingab, Zarene Claire
submitted to: Prof. Renegado
course&sec: BSCS-2AB
date: October 31, 2021 */
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#define MAX 50
using namespace std;

typedef struct rec
{
   int id;
   string fullN;
   int q1, q2, q3;
} REC;

class MyList
{
    private:
        REC sr[MAX];
        int last;
    public:
        void makenull()
        {
           last = -1;
        }
    void add(REC x);
    void del(int a);
    void displayall();
    void display(int i, int a);
    //void update(string n, int i);
    int locate(string n);
    int locateId(int a);
    int pos(string n);
    bool isFull();
    bool isEmpty();
    void save();
    void retrieve();
};


void MyList::add(REC x)
{
    int i,p;
    if (isFull())
    {
        cout<<"List is full.\n";
        system("pause");
    }

    else
    {
        p = pos(x.fullN);
        for (i=last; i>=p; i--)
        {
            sr[i+1]=sr[i];
        }

        sr[p].fullN = x.fullN;
        sr[p].q1 = x.q1;
        sr[p].q2 = x.q2;
        sr[p].q3 = x.q3;
        sr[p].id = x.id;
        last++;
    }
    save();
}

void MyList::del(int a)
{
    int i,p;
    if (isEmpty())
    {
        cout << "\n\t\t\tList is empty.\n";
        system("pause");
    }
    else
    {
        p=locateId(a);
        if (p<0)
        {
            cout <<"\n\t\t\tNot found.\n";
            system("pause");
        }
        else
        {
            for (i=p;i<last;i++)
            {
                sr[i]=sr[i+1];
            }
            last--;
        }
    }
}
void MyList::save()
{
    fstream fp;
    int i;
    fp.open("dsa.dbf",ios::out);
    for (i=0;i<=last;i++)
    {
        fp <<sr[i].id<<" "<<sr[i].fullN<<" "<<sr[i].q1<<"    "<<sr[i].q2<<"  "<<sr[i].q3<<"  "<<endl;
    }
    fp.close();
}
void MyList::retrieve()
{
    fstream fp;
    REC x;
    fp.open("dsa.dbf",ios::in);
    if(!fp)
    {
        fp.open("dsa.dbf", ios::out);
    }
    else
    {
        while(true)
        {
            fp>>x.id>>x.fullN>>x.q1>>x.q2>>x.q3;
            if(fp.eof())
            {
                break;
            }
            add(x);
        }
    }
    fp.close();
}

void MyList::displayall()
{
    int i;
    float ave;
    std::cout << std::setprecision(2) << std::fixed;

    system("cls");
    if(isEmpty())
    {
        cout <<"\n\t\t\tList is Empty\n";  //call isEmpty() function
        getch();
    }
    else
    {
        cout<<"\t-------------------------------------------------------------------\n";
        cout<<"\tID\tNAME\t\tQUIZ 1\tQUIZ 2\tQUIZ 3\t AVERAGE   REMARKS\n";
        cout<<"\t-------------------------------------------------------------------\n";
        for (i=0;i<=last;i++)
        {
            ave=(float)(sr[i].q1 + sr[i].q2 + sr[i].q3)/3;
            cout <<"\t"<<sr[i].id<<".)"<<sr[i].fullN<<"    "<<sr[i].q1<<"      "<<sr[i].q2<<"      "<<sr[i].q3<<"      "<<ave<<"     ";
            if (ave>=75.0)
                cout<<"PASSED"<<endl;
            else
                cout<<"FAILED"<<endl;
        }
    }
}
void MyList::display(int i, int a)
{
    int p;
    float ave;
    std::cout << std::setprecision(2) << std::fixed;

    system("cls");
    if(isEmpty())
    {
        cout <<"\n\t\t\tList is Empty\n";  //call isEmpty() function
        getch();
    }
    else
    {
        p=locateId(a);
        //if(p<0)
        //{
            cout<<"\t-------------------------------------------------------------------\n";
            cout<<"\tID\tNAME\t\tQUIZ 1\tQUIZ 2\tQUIZ 3\t AVERAGE   REMARKS\n";
            cout<<"\t-------------------------------------------------------------------\n";
            //for(i=0;i<=last;i++)
            //{
                ave=(float)(sr[i].q1 + sr[i].q2 + sr[i].q3)/3;
                cout <<"\t"<<sr[i].id<<".)"<<sr[i].fullN<<"    "<<sr[i].q1<<"      "<<sr[i].q2<<"      "<<sr[i].q3<<"      "<<ave<<"     ";
                if (ave>=75.0)
                    cout<<"PASSED"<<endl;
                else
                    cout<<"FAILED"<<endl;
            //}
        //}
    }
}

int MyList::pos(string n)
{
    int i;
    for(i=0;i<=last;i++)
    {
        if (sr[i].fullN.compare(n)>0)
        {
            return(i);
        }
    }
    return(i);
}
bool MyList::isFull()
{
    return(last==MAX-1);
}
bool MyList::isEmpty()
{
    return(last==-1);
}
int MyList::locate(string n)
{
    int i;
    for (i=0;i<=last;i++)
        if (sr[i].fullN.compare(n)==0)
        return i;
    return -1;
}
int MyList::locateId(int a)
{
    int i;
    for (i=0;i<=last;i++)
        if (sr[i].id==a)
        return i;
    return -1;
}

int menu()
{
    int ch;
    system("cls");
    cout <<"\n===============================================================================\n";
    cout <<"\t\t\t WELCOME TO STUDENT CLASS RECORD";
    cout <<"\n===============================================================================\n\n";
    cout <<"\t\t\t\t    MENU\n";
    cout <<"\n\t\t\t\t1. Insert\n";
    cout <<"\n\t\t\t\t2. Display\n";
    cout <<"\n\t\t\t\t3. Delete\n";
    cout <<"\n\t\t\t\t4. Display ALL\n";
    cout <<"\n\t\t\t\t5. Exit\n";
    cout <<"\n\t\t\t\tSelect:(1-5) ";
    cin>>ch;

return (ch);
}
int main()
{
    int i, a;
    REC y;
    MyList L;
    L.makenull();//initialize the list
    L.retrieve();//populate the list with records from file bscs2ab.dbf
    while (true)
    {
        switch(menu())
        {
            case 1: system("cls");
                    cout <<"\n===============================================================================\n";
                    cout <<"\t\t\t\tINSERT RECORD MODE";
                    cout <<"\n===============================================================================\n\n";
                    cout <<"\n\t\tInput Id Number: ";
                    cin>>y.id;
                    cout <<"\n\t\tInput Full Name(Surname,FirstN): ";
                    cin>>y.fullN;
                    i=L.locate(y.fullN);
                    if(i<0)
                    {
                        cout <<"\n\t\tInput Quiz1: ";
                        cin >> y.q1;
                        cout <<"\n\t\tInput Quiz2: ";
                        cin >> y.q2;
                        cout <<"\n\t\tInput Quiz3: ";
                        cin >> y.q3;
                        cout <<"\n\t\tRecord added!\n";
                        cout <<"\n===============================================================================\n\n";
                        L.add(y); system("pause");
                    }
                    else
                    {
                        cout <<"\n\t\t\tAlready in the list. Try another name!\n";
                        cout <<"\n================================================================================\n";
                        getch();
                    }
                    L.save();
                    break;
            case 2: system("cls");
                    //L.displayall();
                    cout <<"\n===============================================================================\n";
                    cout <<"\t\t\t\t DSIPLAY DUPLICATE ID";
                    cout <<"\n===============================================================================\n\n";
                    cout<<"\n\t\t\tInput ID: ";
                    cin >>y.id;
                    i=L.locateId(y.id);
                    if(i>=0)
                    {
                        //L.update(y.id, i);
                        L.display(i, y.id);
                        getch();
                    }
                    else
                    {
                        cout <<"\n\t\t\tNot on the list. Try another ID!\n";
                        cout <<"\n================================================================================\n";
                        getch();
                    }
                    break;
            case 3: system("cls");
                    L.displayall();
                    cout <<"\n===============================================================================\n";
                    cout <<"\t\t\t\tDELETE RECORD MODE";
                    cout <<"\n===============================================================================\n\n";
                    cout <<"\n\t\t\t\tInput ID: ";
                    cin>>y.id;
                    L.del(y.id);
                    cout <<"\n\t\t\tThe record has been successfully deleted!";
                    cout <<"\n================================================================================\n";
                    getch();
                    break;
            case 4: L.displayall(); getch();
                    break;
            case 5: L.save();exit(0);
            default: cout<<"1-5 only.\n";getch();menu();
        }
    }
    return 0;
}
