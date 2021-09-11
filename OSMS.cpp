#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<regex>

using namespace std;

//Record specification
class osupply{
public:
char ind[5],did[5],name[30],phone[15],quantity[5],capacity[5],add[20],odate[15];
}osrec[100],found[30];
int n;
int did=101;
//Number Of Records
int get_num_records()
{
	int I=0;
	fstream file2;	
	file2.open("record.txt",ios::in);
	if(!file2)
	{
		return 0;
	}
	while(!file2.eof())
 	{
		file2.getline(osrec[I].ind,5,'|');
		file2.getline(osrec[I].did,5,'|');
		file2.getline(osrec[I].name,30,'|');
		file2.getline(osrec[I].phone,15,'|');
		file2.getline(osrec[I].quantity,5,'|');
		file2.getline(osrec[I].capacity,5,'|');
        file2.getline(osrec[I].add,20,'|');
		file2.getline(osrec[I].odate,15,'\n');
		I++; 	
 	}
	I--;
	file2.close();
	return I;
}
//Retrieve Details
void retrieve_details(char s_did[])
{
	n = get_num_records();
	for(int i=0;i<n;i++)
 	{
		if(strcmp(osrec[i].did,s_did)==0) 
	 	{
			cout<<"\n\tCustomer Found";
			cout<<"\n DID : "<<osrec[i].did<<"\n Name : "<<osrec[i].name<<"\n Phone : "<<osrec[i].phone<<"\n Quantity : "<<osrec[i].quantity<<"\n Capacity : "<<osrec[i].capacity<<"\n Place : "<<osrec[i].add<<"\n Date : "<<osrec[i].odate;
	 		break;
		}
 	}
}
//Login 
int login()
{
    char uname[50];
    char pass[20];
    int i=0;
    char a;
    cout<<"\n Enter Username  :  ";
    gets(uname);
    if((strcmp(uname,"Sunidhi")==0) || (strcmp(uname,"Harshitha")==0) || (strcmp(uname,"Puneeth")==0))
    {
        cout<<"\n Enter Password   :  ";
        for(i=0;;)
        {
            a=getch();
            if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))
            {
                pass[i]=a;
                ++i;
                cout<<"*";
            }
            if(a=='\b'&&i>=1)
            {
                cout<<"\b \b";
                --i;
            }
            if(a=='\r')            
                break;        
        }
        if(strcmp(pass,"osms123")==0)
        {
            cout<<"\nLogin Successful";
            return 1;
        }
        else
            cout<<"\nInvalid password";
			getch();
            return 0;
     }
     else
	 {
        cout<<"\nInvalid User Name";  
		getch();
	 }	
    return 0; 
}
//About Us
void about_us()
{
	cout<<"\n ABOUT US:";
	cout<<"\n\n   Co-oxy Oxygen Supplier is one of the most reliable and customer friendly firm in Karnataka, supplying Medical oxygen.During this Covid-19 pandemic, we have risen to the occasion and providing 24*7 supply/service to the needy hospitals.";
	cout<<"\n\nThe various types of oxygen cylinders supplied by our company are:";
	cout<<"\n   Type A (capacity 5L)";
	cout<<"\n   Type B (capacity 10L)";
	cout<<"\n   Type C (capacity 25L)";
	cout<<"\n   Type D (capacity 50L)";
	cout<<"\n\n FOR MORE DETAILS";
    cout<<"\nContact:\n\tWebsite: www.cooxysuppliers.com\n\tMail: infocooxysuppliers@gmail.com";
	cout<<"\n\nTHANK YOU FOR REACHING US";
}
//Add Record
void add_record()
{
	char buf1[300],buf2[100];
	fstream file1,file2;
	int I,cnt;
	osupply s;
	cnt=get_num_records();
	if(cnt == 0)
		did=101;
	file1.open("index.txt",ios::out|ios::app);
	if(!file1)
	{
		exit(0);
	}
	file2.open("record.txt",ios::out|ios::app);
	if(!file2)
	{
		exit(0);
	}
	cout<<"\nEnter the number of record to enter : ";
	cin>>n;
	cout<<"\nEnter the details :\n"; 
	for(I=cnt; I<(cnt+n); I++)
   {                  
		cout<<"\n Name : ";
		cin>>s.name;
		cout<<"\n Phone : ";
		cin>>s.phone;
		cout<<"\n Quantity: ";
		cin>>s.quantity;
		cout<<"\n Capacity : ";
		cin>>s.capacity;
		cout<<"\n Address : ";
		cin>>s.add;
		cout<<"\n Date(dd-mm-yyyy) : ";
		cin>>s.odate;

		if(strlen(s.phone)!=10)
		{
			cout<<"\n Invalid phone number";
			cout<<"\nEnter the valid Phone number : ";
			cin>>s.phone;
		}
		if((strcmp(s.capacity,"50")==0) || (strcmp(s.capacity,"25")==0) || (strcmp(s.capacity,"10")==0) || (strcmp(s.capacity,"5")==0)){}
		else
		{
			cout<<"\n Invalid Cylinder Capacity";
			cout<<"\nEnter the valid Cylinder Capacity : ";
			cin>>s.capacity;    
		}
    	regex re("([0-9]+)-([0-9]+)-([0-9]*)?");	
    	if (regex_match(s.odate, re) == false) {
			cout<<"\n Invalid Date Format";
			cout<<"\nEnter the valid Date : ";
			cin>>s.odate;
		}      
		
		sprintf(buf2,"%d|%d\n",did,I);
		file1<<buf2;

		sprintf(buf1,"%d|%d|%s|%s|%s|%s|%s|%s\n",I,did,s.name,s.phone,s.quantity,s.capacity,s.add,s.odate);
		file2<<buf1;
		did++;
	}
	file1.close();
	file2.close();
}
//Display
void display_records()
{
	fstream file2;
	osupply s;	
	file2.open("record.txt",ios::in);
	cout<<"\n\n"<<"Supply details : \n";
	cout<<" ---------------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"|\tIndex\t|\tDID\t|\tName\t|\t  Phone  \t|   Quantity    |   Capacity    |\tAddress\t|\tDate\t|"; 
	cout<<"\n ---------------------------------------------------------------------------------------------------------------------------------------";
	while(!file2.fail()) 
 	{
		file2.getline(s.ind,5,'|');
		file2.getline(s.did,5,'|');
		file2.getline(s.name,30,'|');
		file2.getline(s.phone,15,'|');
		file2.getline(s.quantity,5,'|');
		file2.getline(s.capacity,5,'|');
        file2.getline(s.add,20,'|');
		file2.getline(s.odate,15,'\n');
		if(!file2.fail())
			cout<<"\n|\t"<<s.ind<<"\t|\t"<<s.did<<"\t|\t"<<s.name<<"\t|\t"<<s.phone<<"\t|\t"<<s.quantity<<"\t|\t"<<s.capacity<<"\t|\t"<<s.add<<"\t|   "<<s.odate<<"  |"; 	
 	}
	 cout<<"\n ---------------------------------------------------------------------------------------------------------------------------------------";
	file2.close();
}
//Search Cutomer
void search_customer()
{
	int I,flag;
	osupply s;
	char name[20];
	fstream file2;
	cout<<"\nEnter the Customer name : ";
	cin>>name;
	file2.open("record.txt",ios::in); 
	if(!file2)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag=0;
	while(!file2.eof())
	{
		file2.getline(s.ind,5,'|');
		file2.getline(s.did,5,'|');
		file2.getline(s.name,30,'|');
		file2.getline(s.phone,15,'|');
		file2.getline(s.quantity,5,'|');
		file2.getline(s.capacity,5,'|');
        file2.getline(s.add,20,'|');
		file2.getline(s.odate,15,'\n');    
		if(strcmp(s.name,name)==0)
		{
			retrieve_details(s.did);         
			flag=1;                  
		}
	}
	if(!flag)
	cout<<"\nCustomer not found search failed !!\n"; 
	file2.close();
}
//Type A
void type_a()
{
	osupply s;
	int k=0,i,n;
 	fstream file;
 	file.open("record.txt",ios::in);
 	while(!file.eof())
 	{
  		file.getline(s.ind,5,'|');
		file.getline(s.did,5,'|');
		file.getline(s.name,30,'|');
		file.getline(s.phone,15,'|');
		file.getline(s.quantity,5,'|');
		file.getline(s.capacity,5,'|');
        file.getline(s.add,20,'|');
		file.getline(s.odate,15,'\n');    
		if(strcmp(s.capacity,"5")==0)
		{
			strcpy(found[k].ind,s.ind);
			strcpy(found[k].did,s.did);
   			strcpy(found[k].name,s.name);
			strcpy(found[k].quantity,s.quantity);   
   			k++;  
  		}
	}
 	file.close();
  	for(i=0;i<k;i++)
   		cout<<"\nDID : "<<found[i].did<<"| Name : "<<found[i].name<<"| Quantity : "<<found[i].quantity;
}
//Type B
void type_b()
{
	osupply s;
	int k=0,i,n;
 	fstream file;
 	file.open("record.txt",ios::in);
 	while(!file.eof())
 	{
  		file.getline(s.ind,5,'|');
		file.getline(s.did,5,'|');
		file.getline(s.name,30,'|');
		file.getline(s.phone,15,'|');
		file.getline(s.quantity,5,'|');
		file.getline(s.capacity,5,'|');
        file.getline(s.add,20,'|');
		file.getline(s.odate,15,'\n');    
		if(strcmp(s.capacity,"10")==0)
		{
			strcpy(found[k].ind,s.ind);
			strcpy(found[k].did,s.did);
   			strcpy(found[k].name,s.name);
			strcpy(found[k].quantity,s.quantity);   
   			k++;  
  		}
	}
 	file.close();
  	for(i=0;i<k;i++)
   		cout<<"\nDID : "<<found[i].did<<"| Name : "<<found[i].name<<"| Quantity : "<<found[i].quantity;
}
//Type C
void type_c()
{
	osupply s;
	int k=0,i,n;
 	fstream file;
 	file.open("record.txt",ios::in);
 	while(!file.eof())
 	{
  		file.getline(s.ind,5,'|');
		file.getline(s.did,5,'|');
		file.getline(s.name,30,'|');
		file.getline(s.phone,15,'|');
		file.getline(s.quantity,5,'|');
		file.getline(s.capacity,5,'|');
        file.getline(s.add,20,'|');
		file.getline(s.odate,15,'\n');    
		if(strcmp(s.capacity,"25")==0)
		{
			strcpy(found[k].ind,s.ind);
			strcpy(found[k].did,s.did);
   			strcpy(found[k].name,s.name);
			strcpy(found[k].quantity,s.quantity);   
   			k++;  
  		}
	}
 	file.close();
  	for(i=0;i<k;i++)
   		cout<<"\nDID : "<<found[i].did<<"| Name : "<<found[i].name<<"| Quantity : "<<found[i].quantity;
}
//Type D
void type_d()
{
	osupply s;
	int k=0,i,n;
 	fstream file;
 	file.open("record.txt",ios::in);
 	while(!file.eof())
 	{
  		file.getline(s.ind,5,'|');
		file.getline(s.did,5,'|');
		file.getline(s.name,30,'|');
		file.getline(s.phone,15,'|');
		file.getline(s.quantity,5,'|');
		file.getline(s.capacity,5,'|');
        file.getline(s.add,20,'|');
		file.getline(s.odate,15,'\n');    
		if(strcmp(s.capacity,"50")==0)
		{
			strcpy(found[k].ind,s.ind);
			strcpy(found[k].did,s.did);
   			strcpy(found[k].name,s.name);
			strcpy(found[k].quantity,s.quantity);   
   			k++;  
  		}
	}
 	file.close();
  	for(i=0;i<k;i++)
   		cout<<"\nDID : "<<found[i].did<<"| Name : "<<found[i].name<<"| Quantity : "<<found[i].quantity;
}
//Search Cylinder
void search_cylinder()
{
	int c;
	cout<<"\nPlease choose type of Cylinder : ";
	cout<<"\n\t1 : Type A (capacity 5L)\t\t2 : Type B (capacity 10L)\t\t";
	cout<<"\n\t3 : Type C (capacity 25L)\t\t4 : Type D (capacity 50L)\t\t\n";
	cin>>c;
	switch(c)
	{
		case 1: type_a();break;
		case 2:	type_b();break;
		case 3: type_c();break;
		case 4: type_d();break;
		default:cout<<"\n\tInvalid choice";break;
	}	
}
//Day-to-Day Transaction
void display_dtd()
{
	osupply s;
	int k=0,i,n;
 	char s_date[15];
 	fstream file;
 	file.open("record.txt",ios::in);
 	cout<<"\nPlease enter the date to see transaction in dd-mm-yyyy format : ";
 	cin>>s_date;
 	while(!file.eof())
 	{
		file.getline(s.ind,5,'|');
		file.getline(s.did,5,'|');
		file.getline(s.name,30,'|');
		file.getline(s.phone,15,'|');
		file.getline(s.quantity,5,'|');
		file.getline(s.capacity,5,'|');
        file.getline(s.add,20,'|');
		file.getline(s.odate,15,'\n');    
		if(strcmp(s_date,s.odate) == 0)
		{
			strcpy(found[k].ind,s.ind);
			strcpy(found[k].did,s.did);
   			strcpy(found[k].name,s.name);   
   			k++;  
  		}
 	}
 	file.close();
	if(k>0){
  		for(i=0;i<k;i++)
   			retrieve_details(found[i].did);
		cout<<"\n The Complete Day Trasaction";	
    }
	else
    	cout<<"Invalid Entry !\n"; 
	return;   
}
//Modify
void modify()
{
	fstream file1,file2;
  	char sdid[5];
  	int I,j,i=0;
	n=get_num_records();
  	osupply s1[200];
	file1.open("index.txt",ios::in);
	file2.open("record.txt",ios::in);
  	if(!file1)
 	 {
      exit(0);
  	}
	cout<<"\nINDEX : ";
	cout<<"\n DID | Index";
	for(int i=0;i<n;i++)
	{
		file1.getline(found[i].did,5,'|');
		file1.getline(found[i].ind,5,'\n');
		cout<<"\n "<<found[i].did<<" | "<<found[i].ind;
	}
  	cout<<"\nEnter the DID : ";
  	cin>>sdid;
  	while(!file2.eof())
  	{
      	file2.getline(s1[i].ind,5,'|');
		file2.getline(s1[i].did,5,'|');
		file2.getline(s1[i].name,30,'|');
		file2.getline(s1[i].phone,15,'|');
		file2.getline(s1[i].quantity,5,'|');
		file2.getline(s1[i].capacity,5,'|');
        file2.getline(s1[i].add,20,'|');
		file2.getline(s1[i].odate,15,'\n');    
		i++;
  	}
  	for(j=0;j<n;j++)
  	{
      if(strcmp(sdid,s1[j].did)==0)
      {
    	  cout<<"\nThe old values of the record with DID "<<sdid<<" are : ";
          cout<<"\nName    = "<<s1[j].name;
          cout<<"\nPhone   = "<<s1[j].phone;
          cout<<"\nQuantity   = "<<s1[j].quantity;
          cout<<"\nCapacity    = "<<s1[j].capacity;
          cout<<"\nAddress    = "<<s1[j].add;
          cout<<"\nDate  = "<<s1[j].odate;
          cout<<"\n\nEnter the new values :";
          cout<<"\nName    = ";cin>>s1[j].name;
          cout<<"\nPhone   = ";cin>>s1[j].phone;
          cout<<"\nQuantity   = ";cin>>s1[j].quantity;
          cout<<"\nCapacity    = ";cin>>s1[j].capacity;
          cout<<"\nAddress    = ";cin>>s1[j].add;
          cout<<"\nDate  = ";cin>>s1[j].odate;
		  if(strlen(s1[j].phone) !=10 )
		{
			cout<<"\n Invalid phone number";
			cout<<"\nEnter the valid Phone number : ";
			cin>>s1[j].phone;
		}
		if((strcmp(s1[j].capacity,"50") == false) || (strcmp(s1[j].capacity,"25")== false) || (strcmp(s1[j].capacity,"10")== false) || (strcmp(s1[j].capacity,"5")== false))
		{
		}
		else
		{
			cout<<"\n Invalid Cylinder Capacity";
			cout<<"\nEnter the valid Cylinder Capacity : ";
			cin>>s1[j].capacity;
		}
    	regex re("([0-9]+)-([0-9]+)-([0-9]*)?");	
    	if (regex_match(s1[j].odate, re) == false) {
			cout<<"\n Invalid Date Format";
			cout<<"\nEnter the valid Date : ";
			cin>>s1[j].odate;
		}
        break;
      }
    }
	if(j==n)
    {
        cout<<"\nThe record with DID "<<sdid<<" is not present"; 
        return;
    }
    file2.close();
	file1.close();

    char buf1[100],buf2[20];
	fstream out1,out2;
	int l,cnt;
	osupply s;
	cnt=get_num_records();
	file1.open("index.txt",ios::out|ios::trunc);
	if(!file1)
	{
		exit(0);
	}
	file2.open("record.txt",ios::out|ios::trunc);
	if(!file2)
	{
		exit(0);
	}
	for(l=0;l<cnt;l++)
   {                  
		sprintf(buf2,"%s|%s\n",s1[l].did,s1[l].ind);
		file1<<buf2;

		sprintf(buf1,"%s|%s|%s|%s|%s|%s|%s|%s\n",s1[l].ind,s1[l].did,s1[l].name,s1[l].phone,s1[l].quantity,s1[l].capacity,s1[l].add,s1[l].odate);
		file2<<buf1;
	}
		out1.close();
		out2.close();
}
//Deletion
void delete_stdrecord(char idno[])
{
int I=0;
fstream file1,file2;
	n = get_num_records();	
	int flag=-1;
	for(I=0;I<n;I++)      
	{
		if(strcmp(osrec[I].ind,idno)==0)
		{
			flag=I;
			break;
		}	
	}
	if(flag==-1)                
	{
		cout<<"\nError !";
		return;
	}
	if(flag==(n-1))            
	{
		n--;
		cout<<"\nDeleted !\n";	
	}
	else
	{
		for(I=flag;I<n;I++)
		{
			osrec[I] = osrec[I+1];
		}
		n--;
		cout<<"\nDeleted !\n";
	}
	file1.open("index.txt",ios::out);  
	file2.open("record.txt",ios::out);  
	for(I=0;I<n;I++)                   
	{                                   
		file1<<osrec[I].did<<"|"<<I<<"\n";
		file2<<I<<"|"<<osrec[I].did<<"|"<<osrec[I].name <<"|"<<osrec[I].phone<<"|"<<osrec[I].quantity<<"|"<<osrec[I].capacity<<"|"<<osrec[I].add<<"|"<<osrec[I].odate<<endl;
	}
	file1.close();
	file2.close();
	return;
}
void delete_record()
{
int I,flag;
char st_no[5],st_did[5],rt_did[5];
fstream file1;
	cout<<"\nPlease enter the DID of the record to be deleted : ";
	cin>>st_did;
	file1.open("index.txt",ios::in);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag=0;
	while(!file1.eof())
	{
		file1.getline(rt_did,5,'|');     
		file1.getline(st_no,5,'\n');       
		if(strcmp(st_did,rt_did)==0)
		{
			delete_stdrecord(st_no); 
			flag=1;
			break;
		}
	}
	if(!flag)
	cout<<"\nDeletion failed !\n"; 
	file1.close();	
}
//Main Function
int main()
{
int choice,r;
    r = login();
    if(r==1)
    {
	    for(;;)
	    {
		    cout<<"\n\n\t\t\t\t\t\t\t\t****************************************\t\t\t\t\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\tCO-OXY OXYGEN SUPPIPLIERS\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t----------------------------------------\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\t1: About Us\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\t2: Add Supply Details\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\t3: Dispatch Summary\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\t4: Customer Orders\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\t5: Cylinder Details\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\t6: Day-to-Day Transactions\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\t7: Modify Record Details\t\t\t\t\t\t";
			cout<<"\n\t\t\t\t\t\t\t\t\t8: Remove Record Details\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\t9: Exit\t\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t****************************************\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t****************************************\t\t\t\t\t";
            cout<<"\n\t\t\t\t\t\t\t\t\tEnter your choice : ";
		    cin>>choice;
            cout<<"\n\t\t\t\t\t\t\t\t----------------------------------------\t\t\t\t\t";
		    switch(choice)
		    {
			    case 1: about_us();break;
				case 2:	add_record();break;
				case 3: display_records();break;
				case 4: search_customer();break;
				case 5: search_cylinder();break;
				case 6: display_dtd();break;
				case 7: modify();break;
				case 8: delete_record();break;
				case 9: exit(0);
				default:cout<<"\n\t\t\t\t\t\t\t\t\tInvalid choice";
						cout<<"\n\t\t\t\t\t\t\t\t\tTry again";
						break;
		    }
        }
	}
}