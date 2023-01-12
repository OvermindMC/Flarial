#include "Client.h"
#include "Manager/Manager.h"

Client::Client(std::string n) {

	Utils::setDebugPath(n);
	Utils::debugOutput("Initializing Client");

	this->name = n.c_str();
	this->mgr = new Manager(this);

};