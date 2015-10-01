#include "SIPClient.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
using std::cin;
// TODO: prenos je UDP - je potreba implementovat timery pro opakovani requestu
// TODO: na vsechny non-200 kody pri invite musim odpovedet ACK -- zkontrolovat s RFC, jestli to je pravda
// TODO: implementovat Basic a auth-int overeni
int main()
{
	enum { SS_STARTED, SS_STOPED, SS_CONNECTED, SS_DIALING, SS_TALKING };
	int status = SS_STARTED;
	int sipStatus;
	//
	string source, destination, callee, auth_user, auth_passwd;
	cout << "URI SIP serveru: ";
	cin >> destination;
	cout << "URI teto stanice: ";
	cin >> source;
	cout << "ID volaneho: ";
	cin >> callee;
	cout << "Vase ID: ";
	cin >> auth_user;
	cout << "Vase heslo: ";
	cin >> auth_passwd;
	//
	cout << "==============================" << endl;
	cout << "Zacinam sezeni." << endl;
	try
	{
		CSipClient sip(destination, 5060, source, 10001, callee, auth_user, auth_passwd);
		//
		fd_set rfds, wfds;
		sip.Init(&rfds, &wfds);
		while(status != SS_STOPED)
		{
			FD_ZERO(&rfds);
			FD_ZERO(&wfds);
			sip.SetFd();
			if(select(FD_SETSIZE, &rfds, &wfds, NULL, NULL) > 0)
			{
				sipStatus = sip.Iterate();
				if(sipStatus == SipStatus::SS_HANGED_UP)
				{
					status = SS_STOPED;
					cout << "Hovor ukoncen." << endl;
					break;
				}
				//
				switch(status)
				{
					case SS_STARTED:
						if(sipStatus == SipStatus::SS_INVITING)
						{
							status = SS_CONNECTED;
							cout << "Sezeni zahajeno." << endl;
							cout << "Kontaktuji vzdaleneho ucastnika." << endl;
						}
						break;
					
					case SS_CONNECTED:
						if(sipStatus == SipStatus::SS_RINGING)
						{
							status = SS_DIALING;
							cout << "Vzdaleny ucastnik kontaktovan." << endl;
							cout << "Vyzvanim..." << endl;
						}
						break;
					
					case SS_DIALING:
						if(sipStatus == SipStatus::SS_CALL_ACCEPTED)
						{
							status = SS_TALKING;
							cout << "Telefonat akceptovan." << endl;
							cout << "Probiha hovor..." << endl;
						}
						break;
					
					case SS_TALKING:
						// komunikace RTP <--> RTMP
						break;
				}
			}
		}
	}
	catch(void *ex)
	{
		delete ex;
		cout << "VYNUCENY KONEC SEZENI!" << endl;
	}
	//
	cout << "Ukoncuji sezeni." << endl;
	//
	return 0;
}
