/*
 * IMAPSelect.cpp
 *
 *  Created on: Sep 29, 2013
 *      Author: Rakesh
 */

#include "IMAPSelect.hpp"
#include "IMAPParser.hpp"
#include "INetworkExceptionState.hpp"

namespace provider {
namespace imap {

IMAPSelectRequest::IMAPSelectRequest(const QString& mailboxName) {
	_mailboxName = mailboxName;
}

IMAPSelectRequest::~IMAPSelectRequest() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPSelectRequest::stateMethod(mail::sas::CommunicationService& service) {
	mail::sas::INetworkSingleStateSharedPtr retVal;

	if(!IMAPParser::isValid(_mailboxName)) {
		// Invalid input
        retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Invalid mailbox"));
	} else {
	    // Ex: "a101 SELECT mailbox\r\n"
		QString command;
		command.append("a104"); // Should technically be Replaced this with a dynamic tag count.
        command.append(" SELECT ");
        command.append(_mailboxName);
        command.append("\r\n");

        if ( service.sendData(command)) {
            retVal = mail::sas::INetworkSingleStateSharedPtr(new IMAPSelectResponse());
        }
    }

	return retVal;
}




IMAPSelectResponse::IMAPSelectResponse() {
}

IMAPSelectResponse::~IMAPSelectResponse() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPSelectResponse::stateMethod(mail::sas::CommunicationService& service) {
	mail::sas::INetworkSingleStateSharedPtr retVal;
    QString response = service.receiveResponse();

	if (!service.error() && IMAPParser::isValid(response)) {

		// Parse for protocol error response if any: a104 BAD Command Error. 11
        if (IMAPParser::parseError(response, "a104")) {
            retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Parser Error"));
        } else {
            // No error
            qDebug() << "Select Successful" << response;
        }

	} else {
	    retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Invalid response"));
	}
	return retVal;
}


} /* namespace imap */
} /* namespace provider */
