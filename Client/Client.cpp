#include "Client.h"
#include "Manager/Manager.h"

Client::Client(std::string n) {

	this->name = n.c_str();
	this->mgr = new Manager(this);

};