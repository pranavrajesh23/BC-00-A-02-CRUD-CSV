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

void reportTxt(vector<Record> &records, string &filename,string &header) {
    cout << "\nWRITING THE TEMP.CSV INTO THE REPORT.TXT FILE\n";
    ofstream report(filename);
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    report << "Date : " << setfill('0') << setw(2) << ltm->tm_mday << "-"
           << setw(2) << 1 + ltm->tm_mon << "-"
           << 1900 + ltm->tm_year << "\n\n";

    report << "Sales Report : Stationary Items Sold\n";
    report << string(75, '-') << endl;
    string h1,h2,h3,h4,h5,h6="SALESAMOUNT";
    stringstream ss(header);
    getline(ss,h1,',');
    getline(ss,h2,',');
    getline(ss,h3,',');
    getline(ss,h4,',');
    getline(ss,h5);
    report << left <<setfill(' ')<< setw(12) <<h1
           << setw(12) << h2
           << setw(10) <<h3
           << right << setw(10) <<h4
           << setw(12) << h5
           << setw(14) << h6 << endl;

    report << string(75, '-') << endl;

    string currentdate = "";
    double subtotal = 0.0, grandtotal = 0.0;

    report << fixed << setprecision(2);

    for (auto &record : records) {
        double total = stoi(record.itemQuantity) * stod(record.unitPrice);
        string formatDate = record.date.substr(6, 4) + "-" + record.date.substr(3, 2) + "-" + record.date.substr(0, 2);
        if (!currentdate.empty() && record.date != currentdate) {
            report << string(75, '-') << endl;
            report << right << setw(47) << "SUBTOTAL FOR " << currentdate << " = " << setw(10) << subtotal << endl;
            report << string(75, '-') << endl;
            grandtotal += subtotal;
            subtotal = 0;
        }
        report << left << setw(12) << formatDate
               << setw(12) << record.saleID
               << setw(10) << record.itemName
               << right << setw(10) << record.itemQuantity
               << setw(12) << record.unitPrice
               << setw(14) << total << endl;

        subtotal += total;
        currentdate = record.date;
    }
    if (!records.empty()) {
        report << string(75, '-') << endl;
        report << right << setw(47) << "SUBTOTAL FOR " << currentdate << " = " << setw(10) << subtotal << endl;
        report << string(75, '-') << endl;
        grandtotal += subtotal;
    }

    report << "\n" <<"GRAND TOTAL : " << setw(10) << grandtotal << endl;
    report.close();
}

void writeTempCsv(vector<Record> &records, string &filename, string &header)
{
    cout<<"\nWRITING THE SORTED DATA INTO TEMP.CSV\n";
    ofstream temp(filename);
    if(!temp.is_open())
    {
        cout<<"\nFailed to open the file\n";
        exit(1);
    }
    temp<<header<<"\n";
    for(auto rec: records)
    {
        temp<<rec.ogline<<"\n";
    }
    temp.close();
}

void sortSalesCsv(vector<Record> &records)
{
    cout<<"\nSORTING THE SALES.CSV FILE IN REGARD OF THE DATE OF PURCHASE\n";
    sort(records.begin(),records.end(),[](Record &a, Record &b)
    {
        int d1,d2,m1,m2,y1,y2;
        sscanf(a.date.c_str(),"%d/%d/%d",&d1,&m1,&y1);
        sscanf(b.date.c_str(),"%d/%d/%d",&d2,&m2,&y2);

        if (y1!=y2) return y1<y2;
        if(m1 !=m2) return m1<m2;
        return d1<d2;
        // return a.date < b.date;
    });
    // for(auto a:records)
    // {
    //     cout<<a.ofline<<"\n";
    // }
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