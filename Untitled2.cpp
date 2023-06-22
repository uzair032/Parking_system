#include<iostream>
#include<ctime>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
struct vehicle
{
	int register_no;
	string driver_name;
	string vehicle_make;
	int vehicle_model;
	int park2;
	string vehicle_color;
	tm *new_t;
	tm *new_t2;
	tm *new_t3;
	time_t start,end,entry;
	vehicle *nptr;
};
vehicle *fptr=NULL;
float to_int(string );
int from_string(string);
int main()
{
	
	string b;
	vehicle *ptr;
	ptr=new vehicle;
   fstream file;
   file.open("last_saved_data.txt",ios::app);
   file.close();
   file.open("last_saved_data.txt",ios::in);
   while(!file.eof())
   {
		  
		   vehicle *ptr;
		   ptr=new vehicle;
			getline(file,b);
			ptr->register_no=from_string(b);
			
			getline(file,b);
			ptr->driver_name=b;
			getline(file,b);
			ptr->vehicle_make=b;
			getline(file,b);
			ptr->vehicle_model=from_string(b);
			getline(file,b);
			ptr->vehicle_color=b;
			if (fptr == NULL)
			{
				fptr=ptr;
				ptr->nptr=NULL;
			}
			else
			{
				vehicle *current=fptr;
				while (current->nptr!=NULL)
				{
					current=current->nptr;
			    }
				current->nptr=ptr;
				ptr->nptr=NULL;
			}
	    
   }
   file.close();
	int option,color,flag,reg_no,j,total_park=0,park,m;
	char s;
	while(1)
	{
		cout<<"Select from the following\n1.Vehicle Entry\n2.Vehicle Exit\n3.Parking fee collected\n4.Parking status\n5.Close the program\n";
		cin>>option;
		switch(option)
		{
			case 1:
				{
					vehicle *ptr;
					ptr=new vehicle;
					
					cout<<"Enter vehicle Registration number: ";
					cin>>ptr->register_no;
					cin.ignore();
					cout<<"Enter Driver name: ";
					getline(cin,ptr->driver_name);
					cout<<"Enter vehicle make: ";
					getline(cin,ptr->vehicle_make);
					cout<<"Enter vehicle model: ";
					cin>>ptr->vehicle_model;
					cout<<"Enter vehicle color:\nSelect from the following:\n1.White\n2.Black\n3.Red\n4.Grey\n";
					cin>>color;
					if(color==1)
					ptr->vehicle_color="White";
					else if(color==2)
					ptr->vehicle_color="Black";
					else if(color==3)
					ptr->vehicle_color="Red";
					else if(color==4)
					ptr->vehicle_color="Grey";
					else
					{
						cout<<"Invalid option"<<endl; break;
					}
					
					ptr->start=time(0);
				    ptr->new_t2=localtime(&ptr->start);
					cout << "Vehicle entered at  " << ptr->new_t2->tm_hour<<":" <<ptr->new_t2->tm_min<<":"<<ptr->new_t2->tm_sec<<endl;
					fstream file2;
					file2.open("parking status.txt",ios::app);
					file2<<"Registration number: "<<ptr->register_no<<endl;
			    	file2<<"Driver name: "<<ptr->driver_name<<endl;
			    	file2<<"Vehicle make: "<<ptr->vehicle_make<<endl;
			    	file2<<"Vehicle model: "<<ptr->vehicle_model<<endl;
			    	file2<<"Vehicle color: "<<ptr->vehicle_color<<endl<<endl;
			    	file2.close();
					// Linked list
				    if(fptr==NULL)
		            {
		        	ptr->nptr=NULL;
		        	fptr=ptr;
	            	}
		            else
	        	    {
			         vehicle *currentptr=fptr; 
                     while(currentptr->nptr!=NULL)
                    {
                      currentptr=currentptr->nptr;
                    } 
                      ptr->nptr=NULL; 
                      currentptr->nptr=ptr; 
		            }
				    
					break; 
				}
			case 2:
			    {
			    	
			    	vehicle *currentptr=fptr;
			    	cout<<"Enter registration number: ";
			    	cin>>reg_no;
			    	cout<<endl;
				
					 flag=0;
					    
					    if(reg_no==fptr->register_no) 
			    		{
			    			
			    			fptr->end=time(0);
				            fptr->new_t=localtime(&fptr->end);
					        cout << "Vehicle exit at  " << fptr->new_t->tm_hour<<":" <<fptr->new_t->tm_min<<":"<<fptr->new_t->tm_sec<<endl;
			    			flag=1;
			    			
			    			if(difftime(fptr->end,fptr->start)<=60)
			    			{
							park=50;
							cout<<"Collect Rs  "<<park<<" amount from Car reg "<<fptr->register_no<<endl;
						    }
			    			else if(difftime(fptr->end,fptr->start)>60)
			    			{
			    			park=70;
			    			cout<<"Collect Rs  "<<park<<" amount from Car reg "<<fptr->register_no<<endl;
						    }
						    
						    total_park=total_park+park;
							fptr=fptr->nptr;
			    			break;
						}
						else 
						{
							while(currentptr!=NULL)
							{
						    if(reg_no==currentptr->nptr->register_no)
						    {							
							currentptr->end=time(0);
				            currentptr->new_t=localtime(&currentptr->start);
					        cout << "Vehicle exit at  " << currentptr->new_t->tm_hour<<":" <<currentptr->new_t->tm_min<<":"<<currentptr->new_t->tm_sec<<endl;
			    			flag=1;
			    			
			    			if(difftime(currentptr->end,currentptr->start)<=60)
			    			{
							park=50;
							cout<<"Collect Rs  "<<park<<" amount from Car reg "<<currentptr->nptr->register_no<<endl;
						    }
			    			else if(difftime(currentptr->end,currentptr->start)>60)
			    			{
			    			park=70;
			    			cout<<"Collect Rs  "<<park<<" amount from Car reg "<<currentptr->nptr->register_no<<endl;
						    }
						    
						    total_park=total_park+park;
							currentptr->nptr=currentptr->nptr->nptr;
							break;
						    }
						    else
					        currentptr=currentptr->nptr;
					        }
					    }
					    if(flag==0)
					    {
						    cout<<"Not found"<<endl; break;
					    }
			    	break;
				}
			case 3:
				{
					cout<<"Total parking fees collected Rs "<<total_park<<endl;
					if(total_park==0)
					{
						break;
					}
					else
					{
						string word;
					fstream file2;
					file2.open("Parking status.txt",ios::in);
					while(!file2.eof())
					{
						getline(file2,word);
						cout<<word<<endl;
					}
					file2.close();
				    }
				    
					break;
				}		
			case 4:
			    {
			    	
			    	/*string word;
			    	cout<<"Previous Data:"<<endl;
			    	fstream file;
			    	file.open("last_saved_data.txt",ios::in);
			    	if(!file)
			    	{
			    		cout<<"No such file"<<endl;
			    		
					}
					else
					{
						if(file.eof()==NULL)
						{
							cout<<"No data found"<<endl;
						}
			    	while(!file.eof())
			    	{
			    		getline(file,word);
			    		cout<<word<<endl;
					}
				    }
					file.close();*/
					cout<<"New data:"<<endl;
			    	vehicle *currentptr=fptr;
			    	if(currentptr==NULL)
			    	{
			    		cout<<"No data present"<<endl;
					}
					else
					{
			    	while(currentptr!=NULL)
			    	{
			    		cout<<"Registration number: "<<currentptr->register_no<<endl;
			    		cout<<"Driver name: "<<currentptr->driver_name<<endl;
			    		cout<<"Vehicle make: "<<currentptr->vehicle_make<<endl;
			    		cout<<"Vehicle model: "<<currentptr->vehicle_model<<endl;
			    		cout<<"Vehicle color: "<<currentptr->vehicle_color<<endl<<endl;
			    		currentptr=currentptr->nptr;
					}
				    }
					break;
				}
			case 5:
			    {
			    	
			    	vehicle *currentptr=fptr;
			    	currentptr->entry=time(0);
				    currentptr->new_t3=localtime(&currentptr->entry);
			    	fstream file;                                    
					
			    	file.open("last_saved_data.txt",ios::app);
			    //	file << "Data saved at  " << currentptr->new_t3->tm_hour<<":" <<currentptr->new_t3->tm_min<<":"<<currentptr->new_t3->tm_sec<<endl;
			    	while(currentptr!=NULL)
			    	{
			    		file<<currentptr->register_no<<endl;
			    		file<<currentptr->driver_name<<endl;
			    		file<<currentptr->vehicle_make<<endl;
			    		file<<currentptr->vehicle_model<<endl;
						file<<currentptr->vehicle_color<<endl;
			    		currentptr=currentptr->nptr;
					}
					file.close();
					cout<<"Thank you"<<endl;
					return 0;			
		            }    
    }
		cout<<"\nPress A to continue \n";
		cin>>s;
		system("CLS");
		if(s=='A')
		continue;
 }
}
int from_string(string a){
	int b;	
	stringstream ss;
	ss<<a;
	ss>>b;
	return b;
}
float to_int(string a){
	int b;	
	stringstream ss;
	ss<<a;
	ss>>b;
	return b;
}