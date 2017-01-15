#include "Text_Data.h"
#include <fstream>

using namespace std;

Text_Data::Text_Data(char text [3][300])
{
		fstream f;
		string Dateiname = text[0];
		const char Standart1[] = "Vorname:    ";
		const char Standart2[] = "Nachname:   ";
		const char Standart3[] = "Abteilug:   ";
		const char Standart4[] = "Tätigkeit:  ";
																		
		f.open("C:\\Users\\Public\\Documents\\" + Dateiname + ".txt", ios::out | ios::app);
		f << Standart1 << text[0] << endl;
		f << Standart2 << text[1] << endl;
		f << Standart3 << text[2] << endl;
		f << Standart4 << text[3] << endl;
		f.close();
}