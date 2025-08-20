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

}

void readSalesCsv(string &fname, vector<Record> &records)
{
    cout<<"\nREADING THE SALES.CSV\n";
    ifstream read(fname);
    if(!read.is_open())
    {
        cout<<"\nError opening file\n";
        exit(1);
    }
    string summa,line;
    getline(read,summa);
    while(getline(read,line))
    {
        if(!line.empty())
        {
            records.emplace_back(line);
        }
    }
    read.close();
}

void deleteInCsv(string &fname,string &header)
{
    cout<<"\nDELETING THE DATA ON SALE.CSV FILE\n";
    fstream sales(fname);
    fstream temp("temp.csv");
    int n;
    cout<<"\nHow many rows you need to delete\n";
    cin>>n;
    string line;
    getline(sales,line);
    for(int i=0;i<n;i++)
    {
        int target;
        cout<<"\nEnter the target salesID:\n";
        cin>>target;
        while(getline(sales,line))
        {
            stringstream ss(line);
            string date,salesID,itemName,itemQuantity,unitPrice;
            getline(ss,date,','); 
            getline(ss,salesID,',');
            getline(ss,itemName,',');
            getline(ss,itemQuantity,',');
            getline(ss,unitPrice);
            if(target==stoi(salesID))
            {
                continue;
            }
            else{
                temp<<date<<","<<salesID<<","<<itemName<<","<<itemQuantity<<","<<unitPrice<<"\n";
            }
        }
    }
    sales.close();
    temp.close();
    remove("sales.csv");
    rename("temp.csv","sales.csv");
}

void updateInCsv(string &fname,string &header)
{
    cout<<"\nUPDATING THE DATA ON SALE.CSV FILE\n";
    fstream sales(fname);
    fstream temp("temp.csv");
    temp<<header<<"\n";
    int n;
    cout<<"\nHow many rows you need to update\n";
    cin>>n;
    string line;
    getline(sales,line);
    for(int i=0;i<n;i++)
    {
        int target;
        cout<<"\nEnter the target salesID:\n";
        cin>>target;
        while(getline(sales,line))
        {
            stringstream ss(line);
            string date,salesID,itemName,itemQuantity,unitPrice;
            getline(ss,date,','); 
            getline(ss,salesID,',');
            getline(ss,itemName,',');
            getline(ss,itemQuantity,',');
            getline(ss,unitPrice);
                if(target==stoi(salesID))
            {
                int ch;
                cout<<"\nWhich one you need to update\n1.date\n2.itemname\n3.itemquantity\n4.unitprice\n5.all\n";
                cin>>ch;
                switch(ch)
                {
                    case 1:
                        cout<<"\nEnter the updated date:\n";cin>>date;
                        break;
                    case 2:
                        cout<<"\nEnter the updated item name:\n";cin>>itemName;
                        break;
                    case 3:
                        cout<<"\nEnter the updated item quantity:\n";cin>>itemQuantity;
                        break;
                    case 4:
                        cout<<"\nEnter the updated unit price:\n";cin>>unitPrice;
                        break;
                    case 5:
                        cout<<"\nEnter all the updated details:\n";
                        cout<<"\nEnter the date:\n";
                        cin>>date;
                        cout<<"\nEnter the item name:\n";
                        cin>>itemName;
                        cout<<"\nEnter the item quantity:\n";
                        cin>>itemQuantity;
                        cout<<"\nEnter the unit price:\n";
                        cin>>unitPrice;
                        break;
                    default:
                        cout<<"\nInvalid option:";
                        break;
                }
                temp<<date<<","<<salesID<<","<<itemName<<","<<itemQuantity<<","<<unitPrice<<"\n";
            }
            else{
                temp<<date<<","<<salesID<<","<<itemName<<","<<itemQuantity<<","<<unitPrice<<"\n";
            }
        }
    }
    sales.close();
    temp.close();
    remove("sales.csv");
    rename("temp.csv","sales.csv");
}


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