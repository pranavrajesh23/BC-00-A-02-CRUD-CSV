#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<string>
#include<ctime>
#include<iomanip>
using namespace std;

struct Record
{
    string date,saleID,itemName,itemQuantity,unitPrice,ogline,ofline;

    Record(const string &line)
    {
        ogline=line;
        stringstream ss(line);
        getline(ss,date,','); 
        getline(ss,saleID,',');
        getline(ss,itemName,',');
        getline(ss,itemQuantity,',');
        getline(ss,unitPrice);

    }
};


int createSalesCsv(string &fname,string &header,int saleID)
{
    cout<<"\nCREATING THE SALES.CSV FILE AND APPENDING THE DATA\n";
    ofstream sales(fname);

    cout<<"\nEnter the headers\n";
    getline(cin,header);
    
    sales<<header<<"\n";

    
    cout<<"\nEnter the no.of rows to be created:\n";
    int n;
    cin>>n;
    // cin.ignore();
    for(int i=0;i<n;i++)
    {
        string date,itemName,itemQuantity,unitPrice;
        cout<<"\nEnter the date:\n";
        cin>>date;
        cout<<"\nEnter the item name:\n";
        cin>>itemName;
        cout<<"\nEnter the item quantity:\n";
        cin>>itemQuantity;
        cout<<"\nEnter the unit price:\n";
        cin>>unitPrice;

        sales<<date<<","<<saleID++<<","<<itemName<<","<<itemQuantity<<","<<unitPrice<<"\n";
    }
    sales.close();
    cout<<"\nDatas are appended to the sales.csv file successfully\n";
    // cout<<saleID;
    return saleID;

}

void addInCsv(string &filename,int newid)
{
    fstream sales(filename, ios::app);
    cout<<"\nHow many rows you need to add:\n";
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        string date,itemName,itemQuantity,unitPrice;
        cout<<"\nEnter the date:\n";
        cin>>date;
        cout<<"\nEnter the item name:\n";
        cin>>itemName;
        cout<<"\nEnter the item quantity:\n";
        cin>>itemQuantity;
        cout<<"\nEnter the unit price:\n";
        cin>>unitPrice;

        sales<<date<<","<<newid++<<","<<itemName<<","<<itemQuantity<<","<<unitPrice<<"\n";
    }
    sales.close();
    cout<<"\nDatas are added successfully\n";
}

int main()
{
    cout<<"CRUD OPERATIONS ON CSV FILES\n";
    string header;
    vector<Record> records;
    string input="sales.csv";
    int saleID=1;
    int newid=createSalesCsv(input,header,saleID);

        cout<<"\nDO YOU WANT EDIT YOUR FILE:(yes/no)\n";
        string choice;
        cin>>choice;
        if(choice=="yes")
        {
            while(true)
            {
                cout<<"\nADD (or) UPDATE (or) DELETE: (A/U/D), enter anything else to move to the read function...\n";
                string ch;
                cin>>ch;
                if(ch=="A" || ch=="a")
                {
                    addInCsv(input,newid);
                }
                else if(ch=="U" || ch=="u")
                {
                    updateInCsv(input,header);
                }
                else if(ch=="D"||ch=="d")
                {
                    deleteInCsv(input,header);
                }
                else
                {
                    cout<<"\nMoving to the next function\n";
                    break;
                }
            }
        }
    readSalesCsv(input,records);
    sortSalesCsv(records);
    string output="temp.csv";
    writeTempCsv(records,output,header);
    string report="report.txt";
    reportTxt(records,report,header);
}