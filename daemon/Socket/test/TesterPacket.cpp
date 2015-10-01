#include "TesterPacket.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

bool
CTesterPacket::Init()
{
	p1 = new CPacket;
	p1->SetBuffer("p1", 3);
	//
	p2 = new CPacket(*p1);
	//
	p3 = new CPacket("p3", 3);
	//
	return true;
}

bool
CTesterPacket::Run()
{
	try
	{
		string strTemp;
		//
		// Constructors (@Init)
		cout << "Constructors...";
		strTemp = p1->GetBuffer();
		if((strTemp != "p1") || (p1->GetLength() != (int)strTemp.length() + 1))
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		strTemp = p2->GetBuffer();
		if((strTemp != "p1") || (p2->GetLength() != (int)strTemp.length() + 1))
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		strTemp = p3->GetBuffer();
		if((strTemp != "p3") || (p3->GetLength() != (int)strTemp.length() + 1))
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		cout << "OK" << endl;
		//
		// SetBuffer
		cout << "SetBuffer...";
		p2->SetBuffer("p2", 3);
		strTemp = p2->GetBuffer();
		if((strTemp != "p2") || (p2->GetLength() != (int)strTemp.length() + 1))
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		cout << "OK" << endl;
		//
		// operator=
		cout << "operator=...";
		*p1 = *p2;
		strTemp = p1->GetBuffer();
		if((strTemp != "p2") || (p1->GetLength() != (int)strTemp.length() + 1))
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		cout << "OK" << endl;
		//
		// ClearBuffer
		cout << "ClearBuffer...";
		p3->ClearBuffer();
		if((p3->GetBuffer() != NULL) || (p3->GetLength() != 0))
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		cout << "OK" << endl;
		//
		// AppendToBuffer
		cout << "Append to buffer...";
		p2->AppendToBuffer("_P2", 4);
		const char *tmp = p2->GetBuffer();
		char check[7] = { 'p', '2', 0, '_', 'P', '2', 0 };
		if(p2->GetLength() != 7)
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		for(int i = 0; i < 7; ++i)
			if(tmp[i] != check[i])
				throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		cout << "OK" << endl;
	}
	catch(SocketException *ex)
	{
		delete ex;
		cout << "FAILED" << endl;
		return false;
	}
	return true;
}

bool
CTesterPacket::Clean()
{
	delete p1;
	delete p2;
	delete p3;
	//
	return true;
}
