#include<iostream>
//#include< bits/stdc++>
using namespace std;
class Frame
{
	friend class Slidingwindow;
	public:
		int data;
		bool ack;
		Frame()
		{
			data=0;
			ack=true;
		}
};
class Slidingwindow
{
	public:
		Frame *frames;
	void send(int n)
	{
		frames =new Frame[n];
		for(int i=0;i<n;i++)
		{
			cout<<"\n\t Enter data for the frame"<<i+1<<" :";
			cin>>frames[i].data;
		}
	}
	void recack(int r)
	{
	frames[r].ack=false;
	cout<<"\n\t The Frame Number"<<r+1<<"is not received.."<<endl;	
	}
	void resendGb(int n,int r)
	{
		cout<<"\n\t Resending frame from"<<r+1<<".."<<endl;
		for(int i=r;i<n;i++)
		{
			frames[i].ack=true;
			cout<<"\n\t Received Data of frame"<<i+1<<","<<frames[i].data<<endl;
		}
	}
	void resendSr(int r)
	{
		cout<<"\n\t Resending Frame Number"<<r+1<<".."<<endl;	
		frames[r].ack=true;
		cout<<"\n\t Received Data of frame"<<r+1<<","<<frames[r].data<<endl;
	
	}
	void goback(int n,int r)
	{
		send(n);
		recack(r);
		resendGb(n,r);
		cout<<"\n\t ALl frames sent successfully"<<endl;
	}
	void selective(int n,int r)
	{
		send(n);
		recack(r);
		resendSr(r);
		cout<<"\n\t all frames sent successfully"<<endl;
	}	
};
int main()
{
	int n,r,choice;
	Slidingwindow sw;
	while(1)
	{
		cout<<"\n\t---Menu--\n\t 1. Go back N ARQ \n\t\t 2. Selective Repeat ARQ\n\t\t 3.Exit ";
		cout<<"enter choice";
		cin>>choice;
		if(choice==1)
		{
			cout<<"Enter no. of frames";
			cin>>n;
			r=rand()%n;
			sw.goback(n,r);
		}
		else if(choice==2)
		{
			cout<<"Enter no. of frames";
			cin>>n;
			r=rand()%n;
			sw.selective(n,r);
		}
		else if(choice==3)
		{
			cout<<" Program over";
			exit(0);
		}
		else
		{
			cout<<"Enter correct option"<<endl;
		}
	}
}
