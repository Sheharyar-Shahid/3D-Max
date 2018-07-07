#include"commons.cpp"
int main()
{
	for (int i = 0; i < 49; i++)
	{
		string filepath =".\\actor\\devil2\\right\\actor"+str(i)+".png";

Image read;
read.loadFromFile(filepath);
for (int j = 0; j < read.getSize().x; j++) {
	for (int k = 0; k < read.getSize().y; k++)
	{
		Color red = read.getPixel(j, k);
	
		if (red.a>250) red.a = 175;
		read.setPixel(j, k, red);
	}
}
read.saveToFile(filepath);
	}
	return 0;
}