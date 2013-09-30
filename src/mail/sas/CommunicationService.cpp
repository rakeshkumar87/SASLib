/*
 * CommunicationService.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#include "CommunicationService.hpp"

namespace mail {
namespace sas {

CommunicationService::CommunicationService(const AccountSettings& account) {
	_address = account.address();
	_port = account.port();
	_error = false;
	_init = false;
    reset();
}

CommunicationService::~CommunicationService() {
    _socket.close();
}

void CommunicationService::reset() {
	_error = false;
    std::memset( _buff, 0, sizeof( _buff ) );
}

bool CommunicationService::error() {
	return _error;
}

bool CommunicationService::init() {

	bool retVal = false;

	_socket.setPeerVerifyMode(QSslSocket::VerifyNone);
    _socket.connectToHostEncrypted(_address, _port);

    if (!_socket.isOpen()) {
        qWarning() << "failed to connect to " << _address;
        _socket.close();
    } else {
        _socket.waitForReadyRead();
        QString response = receiveResponse();
         qWarning() << "Connected : " << _buff;
        _init = true;
        retVal = true;
    }

    return retVal;
}

bool CommunicationService::sendData(const QString& data) {
	reset();

	if (!_init ) {
		init();
	}

    qint64 written = _socket.write(data.toLatin1().data(), data.length());
    return (written == data.length());
}

QString CommunicationService::receiveResponse() {
    _socket.waitForReadyRead();

    QByteArray buffer;
    while ( _socket.readLine( _buff, sizeof( _buff ) ) > 0) {
        buffer.append(_buff);
    }

    return QString(buffer.data());
}


} /* namespace sas */
} /* namespace mail */
