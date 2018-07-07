#include<iostream>
#include<string>
#include<vector>
using namespace std;

class state
{

public:
	virtual bool registerstudent(void * whatsection, int studentid) { return 0; };
	virtual bool cancel(void * whatsection)
	{

		return 0;
	};
	virtual bool  close(void * whatsection)
	{
		return 0;
	};
	virtual bool open(void * whatsection)
	{


		return 0;
	}


};



class section
{
	
	
	int size;
	state *current_state;
	vector<int> studentIDs;
public:
	section()
	{
		size = 0;
	}
	state* getState()
	{
		return current_state;

	}
	void dispose()
	{
		size = 0;
		studentIDs.clear();

	}
	static const int min = 25;
	static const int max = 50;
	void setState(state* newState)
	{

		current_state = newState;

	}
	void Push(int id)
	{
		studentIDs.push_back(id);

	}
	int getSize()
	{
		return size;
	}
	void increment()
	{
		size++;
	}
	bool register_student(int studentid )
	{
		return current_state->registerstudent(this,studentid);
	};
	bool cancel()
	{
	   return current_state->cancel(this);
	
	};
	bool  close()
	{
		return current_state->close(this);
	};
	bool open()
	{
	
		return current_state->open(this);
	
	}

};
class Cancelled : public state
{
private: Cancelled() {}

public:
	static Cancelled* singleton;
	static void setInstance()
	{
		if (singleton == NULL) singleton = new Cancelled();

	}
	bool registerstudent(void * whatsection, int studentid)
	{

		return 0;
	};
	bool cancel(void * whatsection)
	{

		return 0;
	};
	bool  close(void * whatsection)
	{
		return 0;
	};
	bool open(void * whatsection)
	{


		return 0;
	}



};

class Closed : public state
{
private: Closed() {}

public:
	static Closed* singleton;
	static void setInstance()
	{
		if (singleton == NULL) singleton = new Closed();

	}
	bool registerstudent(void * whatsection, int studentid)
	{

		return 0;
	};
	bool cancel(void * whatsection)
	{
		section* ref = (section*)whatsection;
		ref->dispose();
		cout << " All Sudents Disposed!" << endl;
		ref->setState(Cancelled::singleton);
		return 1;
	};
	bool  close(void * whatsection)
	{
	

		return 0;
	};
	bool open(void * whatsection)
	{


		return 0;
	}



};




class OES : public state
{
private: OES() {}

public:
	static OES* singleton;
	static void setInstance()
	{
		if (singleton == NULL) singleton = new OES();

	}
	bool registerstudent(void * whatsection, int studentid)
	{

		section* ref = (section*)whatsection;

		ref->Push(studentid);
		ref->increment();
		if (ref->getSize() > section::max)
		{

			ref->setState(Closed::singleton);
		}



		return 1;
	};
	bool cancel(void * whatsection)
	{
		section *ref =(section*) whatsection;
		ref->dispose();
		cout << " All Sudents Disposed!" << endl;
		ref->setState(Cancelled::singleton);

		return 1;
	};
	bool  close(void * whatsection)
	{
		section *ref = (section*)whatsection;
		ref->setState(Closed::singleton);
		return 1;
	};
	bool open(void * whatsection)
	{


		return 0;
	}



};


class ONES : public state
{
private: ONES(){}
		 
public:
	static ONES* singleton;
	static void setInstance()
	{
		if (singleton == NULL) singleton = new ONES();
	
	}
	bool registerstudent(void * whatsection, int studentid)
	{
		
		section* ref = (section*)whatsection;

		ref->Push(studentid);
		ref->increment();
		if (ref->getSize() > section::min)
		{
			ref->setState(OES::singleton);

		}


		
		return 1;
	};
	bool cancel(void * whatsection)
	{
		section *ref = (section*)whatsection;
		ref->dispose();
		cout << " All Sudents Disposed!" << endl;
		ref->setState(Cancelled::singleton);

		return 1;
	};
	bool  close(void * whatsection)
	{
		section *ref = (section*)whatsection;
		ref->setState(Closed::singleton);
		return 1;
	};
	bool open(void * whatsection)
	{


		return 0;
	}



};
class planned : public state
{

private: planned() {}

public:
	static planned* singleton;
	static void setInstance()
	{
		if (singleton == NULL) singleton = new planned();

	}

	bool registerstudent(void * whatsection, int studentid)
	{
		return 0;
	};
    bool cancel(void * whatsection)
	{

		return 0;
	};
	bool  close(void * whatsection)
	{
		return 0;
	};
	bool open(void * whatsection)
	{
		

		((section*)whatsection)->setState(ONES::singleton);
		return 0;
	}



};

OES* OES::singleton = 0;
ONES* ONES::singleton = 0;
Closed* Closed::singleton = 0;
Cancelled* Cancelled::singleton = 0;
planned* planned::singleton = 0;


string currentState(section& sec)
{
	if (sec.getState() == OES::singleton)
	{
		return  ("[Open Enough Student]");
	}
	else
		if (sec.getState() == ONES::singleton)
		{
			return  ("[Open Not Enough Student]");
		}
		else
			if (sec.getState() == Cancelled::singleton)
			{
				return  ("[Cancelled]");
			}
			else
				if (sec.getState() == Closed::singleton)
				{
					return  ("[Closed]");
				}
				else
					if (sec.getState() == planned::singleton)
					{
						return  ("[Planned]");
					}
					
	return "[null]";
}

int main()
{


	OES::setInstance();
	ONES::setInstance();
	Closed::setInstance();
	Cancelled::setInstance();
	planned::setInstance();


	section OOAD;
	OOAD.setState(planned::singleton);

	cout << " The initial state is " << currentState(OOAD)<<endl;
	OOAD.open();
	cout << "  after open() is called " << currentState(OOAD) << endl;
	for (int i = 0; i < 55; i++)
	{
		cout << "Student trying to register has id " << i + 1;
		OOAD.register_student(i);
		cout << " after the student registered "<<currentState(OOAD)<<endl;

	}
	OOAD.close();
	cout << "  after close() is called " << currentState(OOAD) << endl<<endl;
	OOAD.cancel();
	cout << "  after cancel() is called " << currentState(OOAD) << endl;

	_getwch();
}