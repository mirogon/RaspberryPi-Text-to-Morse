#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <ios>
#include <wiringPi.h>

using namespace std::this_thread;
using namespace std::chrono;

const int TIMEUNIT_LENGTH = 100;

bool char_to_morsestr(char c, std::string& outputstr);

std::string str_to_morsestr(std::string string);

void output_morsestr(std::string morsestr, unsigned short pin_num);

int main(int argc, char* argv[])
{
	
	wiringPiSetup();
	pinMode(7,OUTPUT);

	bool quit = false;
	
	while(quit == false)
	{ 
	
		std::cout<<"Insert the text you want to convert to a morse code"<<std::endl;
	
		std::string input;

		std::getline(std::cin, input);
	
		std::string morsestr;

		morsestr = str_to_morsestr(input);

		output_morsestr(morsestr, 7);

		std::cout<<"Continue? Y(YES) N(NO)"<<std::endl;

		char c;

		std::cin>>c;

		if(c == 'Y' || c == 'y')
		{
		}

		else
		{
			quit = true;
		}
	
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	return 0;
}

bool char_to_morsestr(char c, std::string& outputstring)
{
	static std::string morsestr;

	switch(c)
	{
		case 'a':
		case 'A': morsestr = "sl"; break;
		case 'b':
		case 'B': morsestr = "lsss"; break;
		case 'c':
		case 'C': morsestr = "lsls"; break;
		case 'd':
		case 'D': morsestr = "lss"; break;
		case 'e':
		case 'E': morsestr = "s"; break;
		case 'f':
		case 'F': morsestr = "ssls"; break;
		case 'g':
		case 'G': morsestr = "lls"; break;
		case 'h':
		case 'H': morsestr = "ssss"; break;
		case 'i':
		case 'I': morsestr = "ss"; break;
		case 'j':
		case 'J': morsestr = "slll"; break;
		case 'k':
		case 'K': morsestr = "lsl"; break;
		case 'l':
		case 'L': morsestr = "slss"; break;
		case 'm':
		case 'M': morsestr = "ll"; break;
		case 'n':
		case 'N': morsestr = "ls"; break;
		case 'o':
		case 'O': morsestr = "lll"; break;
		case 'p':
		case 'P': morsestr = "slls"; break;
		case 'q':
		case 'Q': morsestr = "llsl"; break;
		case 'r':
		case 'R': morsestr = "sls"; break;
		case 's':
		case 'S': morsestr = "sss"; break;
		case 't':
		case 'T': morsestr = "l"; break;
		case 'u':
		case 'U': morsestr = "ssl"; break;
		case 'v':
		case 'V': morsestr = "sssl"; break;
		case 'w': 
		case 'W': morsestr = "sll"; break;
		case 'x':
		case 'X': morsestr = "lssl"; break;
		case 'y':
		case 'Y': morsestr = "lsll"; break;
		case 'z': 
		case 'Z': morsestr = "llss"; break;
		
		case ' ': morsestr = " "; break;
	
		default: std::cout<<"Your text contains an invalid character: "<<c<<"!"<<std::endl; return 1; break;
	}

	outputstring = morsestr;

	return 0;
}

std::string str_to_morsestr(std::string string)
{
	static std::string morsestr;
	morsestr = std::string();

	if(string.size()<= 0)
	{
		return "";
	}

	for(int i = 0; i < string.size(); ++i)
	{
		static std::string appender;
		if( char_to_morsestr(string.at(i), appender) == 1 )
		{
			return "";
		}	

		morsestr += appender;
		morsestr.push_back('p');
	}

	return morsestr;

}

void output_morsestr(std::string morsestr, unsigned short pin_num)
{	
	if(morsestr.size() <= 0)
	{
		return;
	}

	for(int i = 0; i < morsestr.size(); i++)
	{
		switch(morsestr.at(i))
		{
			case 's': digitalWrite(pin_num, HIGH); sleep_for( milliseconds( TIMEUNIT_LENGTH) ); digitalWrite(pin_num, LOW);  break;
			case 'l': digitalWrite(pin_num, HIGH); sleep_for( milliseconds( TIMEUNIT_LENGTH * 3 ) ); digitalWrite(pin_num, LOW); break;
			case 'p': sleep_for( milliseconds( TIMEUNIT_LENGTH * 3 ) ); break;
			case ' ': sleep_for( milliseconds( TIMEUNIT_LENGTH * 7 ) ); break;
		}

		if(morsestr.at(i) != ' ' && morsestr.at(i) != 'p')
		{
			sleep_for( milliseconds( TIMEUNIT_LENGTH ) );
		}

	}
}
