/*
 * IMAPLogout.cpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#include "IMAPLogout.hpp"
#include "IMAPParser.hpp"
#include "INetworkExceptionState.hpp"

namespace provider {
namespace imap {


IMAPLogoutRequest::IMAPLogoutRequest()
{
}

IMAPLogoutRequest::~IMAPLogoutRequest() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPLogoutRequest::stateMethod(mail::sas::CommunicationService& service) {
	QSharedPointer<INetworkSingleState> retVal;

	// Ex: "a108 LOGOUT\r\n"
	QString command;
	command.append("a108"); // Should technically be Replaced this with a dynamic tag count.
    command.append(" logout");
    command.append("\r\n");

    if ( service.sendData(command)) {
         retVal = mail::sas::INetworkSingleStateSharedPtr(new IMAPLogoutResponse());
    }

	return retVal;
}




IMAPLogoutResponse::IMAPLogoutResponse() {
}

IMAPLogoutResponse::~IMAPLogoutResponse() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPLogoutResponse::stateMethod(mail::sas::CommunicationService& service) {
	QSharedPointer<INetworkSingleState> retVal;
    QString response = service.receiveResponse();

	if (!service.error() && IMAPParser::isValid(response)) {

		// Parse for protocol error response if any: a100 BAD Command Error. 11
        if (IMAPParser::parseError(response, "a108")) {
            retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Parser Error"));
        } else {
            // No error
            qDebug() << "Logout Successful" << response;
        }

	} else {
	    retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Invalid response"));
	}

	return retVal;
}

}
}
