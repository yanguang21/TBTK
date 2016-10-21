/** @file Streams.cpp
 *
 *  @author Kristofer Björnson
 */

#include "../include/Streams.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace TBTK{
namespace Util{

//ostream Streams::out(new ForkBuffer(&cout, &Streams::log));
//stream Streams::log(&nullBuffer);
//ostream Streams::err(new ForkBuffer(&cout, &Streams::log));
ostream Streams::out(&stdOutBuffer);
//ostream Streams::log(stdLogBuffer.rdbuf());
ostream Streams::log(&Streams::stdLogBuffer);
ostream Streams::err(&stdErrBuffer);
ostream Streams::null(&nullBuffer);
Streams::NullBuffer Streams::nullBuffer;

//Line one and three below are not memory leak even if they appear as such. The
//created objects are intended to last throughout the existence of the program.
Streams::ForkBuffer Streams::stdOutBuffer(&cout, &Streams::log);
Streams::LogBuffer Streams::stdLogBuffer;
Streams::ForkBuffer Streams::stdErrBuffer(&cout, &Streams::log);
ofstream Streams::logFile;

int Streams::NullBuffer::overflow(int c){
	return c;
}

void Streams::setStdMuteOut(){
	stdOutBuffer.mute(0, true);
	stdOutBuffer.mute(1, false);
}

void Streams::setStdMuteErr(){
	stdErrBuffer.mute(0, true);
	stdErrBuffer.mute(1, false);
}

void Streams::openLog(std::string fileName){
	stdLogBuffer.open(fileName);
}

void Streams::closeLog(){
	stdLogBuffer.close();
}

Streams::ForkBuffer::ForkBuffer(
	basic_ostream<char,
	char_traits<char>> *ostream1,
	basic_ostream<char,
	char_traits<char>> *ostream2
){
	ostreams[0] = ostream1;
	ostreams[1] = ostream2;

	isMute[0] = false;
	isMute[1] = false;
}

void Streams::ForkBuffer::mute(int n, bool isMute){
	this->isMute[n] = isMute;
}

int Streams::ForkBuffer::overflow(int c){
	for(int n = 0; n < 2; n++)
		if(ostreams[n])
			*(ostreams[n]) << (char)c;

	return c;
}

Streams::LogBuffer::LogBuffer(){
}

Streams::LogBuffer::~LogBuffer(){
}

void Streams::LogBuffer::open(std::string fileName){
	if(fout.is_open()){
		cerr << "Error in Util::Streams::LogBuffer::openFile(): Log file already open." << endl;
		exit(1);
	}

	fout.open(fileName);
};

void Streams::LogBuffer::close(){
	if(fout.is_open()){
		fout.close();
	}
	else{
		Util::Streams::err << "Error in Util::Streams::LogBuffer::closeFile(): No log file is open.\n";
		exit(1);
	}
}

int Streams::LogBuffer::overflow(int c){
	if(fout.is_open())
		fout << (char)c;
	return c;
}

};	//End of namespace Util
};	//End of namespace TBTK