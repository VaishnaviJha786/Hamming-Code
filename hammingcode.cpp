#include<iostream>
#include<math.h>
using namespace std;
class sender
{
	int a[20], ham[20], n,  r;
public:
	void input()
	{
		int i, j;
		r = 0;
		cout << "\nEnter the no. of bits for the data you want to enter: ";
		cin >> n;
		while (n + r + 1 > pow(2, r))
		{
			r++;
		}
		cout << "\nNo of data bits to be added :" << r << "\nTotal Bits :" << n + r << endl;
		cout << "\nEnter the data\n";
		for ( i = 1;i <= n;i++)
		{
			cin >> a[i];
		}
		cout << "\nThe entered data is: ";
		for ( i = 1;i <= n;i++)
			cout << a[i] << " ";
		cout << endl;
	}
	void parity()
	{
		int i, j, d = 0;
		int count, c, parity;
		for (j = 1, i = 1;j <= n + r, i <= n;j++)
		{
			if (j == pow(2, d) )
			{
				ham[j] = 0;
				d++;
			}
			else
			{
				ham[j] = a[i];
				i++;
			}
			
		}
		d = 0;
		for (j = 1;j <= n + r;j = pow(2, ++d))
		{
			//cout << "j";
			c = 0;
			count = 0;
			for (int k = pow(2, d) ;k <= n + r;k++)
			{
				//cout << "k";
				count++;
				if (ham[k] == 1)
					c++;
				if (count == pow(2, d))
					{k = k + pow(2, d);
					count=0;
					}


			}
			if (c % 2 == 0)
				parity = 0;
			else
				parity = 1;
			ham[j] = parity;
			
		}
		cout << "\nThe data after adding parity bits is: \n";
		for (int k = 1;k <= n + r;k++)
			cout << ham[k] << " ";
	}
	void flip()
	{
		int index;
		cout << "\nwhich bit do you want to flip?";
		cin >> index;
		if (index > n + r)
			cout << "\n invalid bit index";
		else
		{
			if (ham[index] == 1)
				ham[index] = 0;
			else
				ham[index] = 1;
		}
		cout << "\nAFTER FLIPPING: ";
		for (int i = 1;i <= n + r;i++)
			cout << ham[i];
	}
	int* getmessage()
	{
		int* ptr;
		ptr = ham;
		return ptr;
	}
	int getsize()
	{
		return n + r;
	}
};
class reciever
{
	int message[20];
	int n;
public:
	void rec_size(int m)
	{
		n = m;
	}
	void rec_message(int* p)
	{
		cout << "\nRecieved message:";
		for (int i = 1;i <= n;i++)
		{
			message[i] = *(p + i);
			cout << message[i];
		}
	}
	void checkerror()
	{
		int  j, k, d = 0, c, count, err_pos;
		err_pos = 0;
		for (j = 1;j <= n ;j = pow(2, ++d))
		{
			c = 0;
			count = 0;
			for (int k = pow(2, d) ;k <= n ;k++)
			{
				count++;
				if ( message[k] == 1)
					c++;
				if (count == pow(2,d))
					{k = k + pow(2, d);
                     count=0;
					}

			}
			if (c % 2 != 0)
			{
				err_pos = err_pos + j;
			}
			
		}
		if (err_pos != 0)
			cout << "\n\nError at" << err_pos;
		else
			cout << "\n\n No error";
	}
};
int main()
{
	sender s;
	s.input();
	s.parity();
	s.flip();
	int size = s.getsize();
	int* mess = s.getmessage();
	reciever r;
	r.rec_size(size);
	r.rec_message(mess);
	r.checkerror();
	return 0;
}

