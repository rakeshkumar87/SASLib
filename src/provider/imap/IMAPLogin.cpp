/*
 * IMAPLogin.cpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#include "IMAPLogin.hpp"
#include "IMAPParser.hpp"
#include "INetworkExceptionState.hpp"

namespace provider {
namespace imap {


IMAPLoginRequest::IMAPLoginRequest(const mail::sas::AccountSettings& account) :
	_account(account)
{

}

IMAPLoginRequest::~IMAPLoginRequest() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPLoginRequest::stateMethod(mail::sas::CommunicationService& service) {
	QSharedPointer<INetworkSingleState> retVal;

		if(!IMAPParser::isValid(_account.username()) || !IMAPParser::isValid(_account.password())) {
		    // Invalid input
		    retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Invalid Creds"));
		} else {
            // Ex: "a100 LOGIN email password\r\n"
			QString command;
			command.append("a100"); // Should technically be Replaced this with a dynamic tag count.
            command.append(" LOGIN ");
            command.append(_account.username());
            command.append(" ");
            command.append(_account.password());
            command.append("\r\n");

            if ( service.sendData(command)) {
                qDebug() << "Login: " << _account.username();
    		    retVal = mail::sas::INetworkSingleStateSharedPtr(new IMAPLoginResponse());
            }
		}

	return retVal;
}




IMAPLoginResponse::IMAPLoginResponse() {
}

IMAPLoginResponse::~IMAPLoginResponse() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPLoginResponse::stateMethod(mail::sas::CommunicationService& service) {
	QSharedPointer<INetworkSingleState> retVal;
    QString response = service.receiveResponse();

	if (!service.error() && IMAPParser::isValid(response)) {

		// Parse for protocol error response if any: a100 BAD Command Error. 11
        if (IMAPParser::parseError(response, "a100")) {
            retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Parser Error"));
        } else {
            // No error
            qDebug() << "Login Successful" << response;
        }

	} else {
	    retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Invalid response"));
	}
	return retVal;
}

}
}
