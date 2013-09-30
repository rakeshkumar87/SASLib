/*
 * IMAPList.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#include "IMAPList.hpp"
#include "IMAPParser.hpp"
#include "INetworkExceptionState.hpp"

namespace provider {
namespace imap {

IMAPListRequest::IMAPListRequest(const QString& mailboxName, const QString& filter, mail::sas::FolderList* list) {
	_mailboxName = mailboxName;
	_filter = filter;
	_list = list;
}

IMAPListRequest::~IMAPListRequest() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPListRequest::stateMethod(mail::sas::CommunicationService& service) {
	mail::sas::INetworkSingleStateSharedPtr retVal;

		if(!IMAPParser::isValid(_filter)) {
		    // Invalid input
		    retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Invalid Filter for list"));
		} else {
            // Ex: "a102 LIST "INBOX" *\r\n"
			QString command;
			command.append("a102"); // Should technically be Replaced this with a dynamic tag count.
            command.append(" LIST ");
            command.append(_mailboxName);
            command.append(" ");
            command.append(_filter);
            command.append("\r\n");

            if ( service.sendData(command)) {
                retVal = mail::sas::INetworkSingleStateSharedPtr(new IMAPListResponse(_list));
            }
		}

	return retVal;
}




IMAPListResponse::IMAPListResponse(mail::sas::FolderList* list) {
	_list = list;
}

IMAPListResponse::~IMAPListResponse() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPListResponse::stateMethod(mail::sas::CommunicationService& service) {
	mail::sas::INetworkSingleStateSharedPtr retVal;
    QString response = service.receiveResponse();

	if (!service.error() && IMAPParser::isValid(response)) {

		// Parse for protocol error response if any: a102 BAD Command Error. 11
        if (IMAPParser::parseError(response, "a102")) {
            retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Parser Error"));
        } else {
            // No error
            qDebug() << "List Folders Successful";
            IMAPParser::parseList(response, _list);
        }

	} else {
	    retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Invalid response"));
	}

	return retVal;
}

} /* namespace imap */
} /* namespace provider */
