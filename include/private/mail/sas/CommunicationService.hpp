/*
 * CommunicationService.hpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#ifndef COMMUNICATIONSERVICE_HPP_
#define COMMUNICATIONSERVICE_HPP_

#include "AccountSettings.hpp"
#include <QtNetwork/QSslSocket>

/**
 * Performs socket connection management, allows sending and receiving of data.
 */

namespace mail {
namespace sas {


class CommunicationService {
public:
	CommunicationService(const AccountSettings& account);
	virtual ~CommunicationService();
	bool sendData(const QString& data);

	// Ideally would want to return a SocketResponse Object here which contains error info etc.
	QString receiveResponse();

	bool error();
	bool init();

private:
	void reset();
	QSslSocket _socket;
	QString _address;
	int _port;
	char _buff[4 * 1024];
	bool _error;
	bool _init;
};

} /* namespace sas */
} /* namespace mail */

#endif /* COMMUNICATIONSERVICE_HPP_ */
