/*
 * AccountSettings.hpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#ifndef ACCOUNTSETTINGS_HPP_
#define ACCOUNTSETTINGS_HPP_

namespace mail {
namespace sas {

class AccountSettings {
public:
	AccountSettings(const QString& username, const QString& password, const QString& address, int port);
	AccountSettings(const AccountSettings& other);
	~AccountSettings();

	QString username() const;
	QString password() const;
	QString address() const;
	int port() const;

private:
    QString _username;
    QString _password;
    QString _address;
    int _port;
};

} /* namespace sas */
} /* namespace mail */
#endif /* ACCOUNTSETTINGS_HPP_ */
