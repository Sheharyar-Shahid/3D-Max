#include<iostream>
using namespace std;
class a 
{
	int arr[10];
	int x;

public:
	a()
	{
		x = 1;
	}
	

	friend  class b;
	b* start();
};

class b {
	a* obj;
public:
	b( a& f)
	{
		obj = &f;
	}

	int  next()
	{
		cout << obj->x;
		obj->x++;
		return 0;
	}

};
b*  a::start()
{
	
	return new b(*this);

}
int main()
{
	a d;
	b *ge;
	ge=d.start();
	ge->next();
	cout << "hello";
	_getwch();
}