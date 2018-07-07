#include "music.h"

DWORD WINAPI Loop(LPVOID in)
{
	info *inf = (info*)in;
	bool* ref = inf->flag;
	while (true)
	{
	    
		if (*ref == true)
		{
			const char* name = (inf->name).c_str();
			PlaySound(name, NULL, SND_ASYNC);
		}
		Sleep((inf->secs)*1000);

	}

}

music::music()
{
	fire = new bool();
	ongoing = false;
	*fire = true;
}
void music::loop(string name,int dur) {
	this->name = name;
	info *inf=new info;
	inf->name = name;
	inf->flag = fire;
	inf->secs = dur;
	ongoing = true;
	CreateThread(0, 0, Loop, inf, 0, 0);

}
void music::pause() {
	*fire= false;
	PlaySound(0, 0, SND_SYNC);

}
void music::resume() {
	*fire = true;
	PlaySound(name.c_str(), 0, SND_ASYNC);

}

