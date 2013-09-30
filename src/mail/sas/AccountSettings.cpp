/*
 * AccountSettings.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#include "AccountSettings.hpp"

namespace mail {
namespace sas {

AccountSettings::AccountSettings(const QString& username, const QString& password, const QString& address, int port) {
    _username = username;
    _password = password;
    _address = address;
    _port = port;
}

AccountSettings::AccountSettings(const AccountSettings& other) {
    _username = other.username();
    _password = other.password();
    _address = other.address();
    _port = other.port();
}

AccountSettings::~AccountSettings() {
	// TODO Auto-generated destructor stub
}


QString AccountSettings::username() const {
	return _username;
}

QString AccountSettings::password() const {
	return _password;
}

QString AccountSettings::address() const {
	return _address;
}

int AccountSettings::port() const {
	return _port;
}

} /* namespace sas */
} /* namespace mail */
