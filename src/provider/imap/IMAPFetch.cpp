/*
 * IMAPFetch.cpp
 *
 *  Created on: Sep 29, 2013
 *      Author: Rakesh
 */

#include "IMAPFetch.hpp"
#include "IMAPParser.hpp"
#include "INetworkExceptionState.hpp"

namespace provider {
namespace imap {

IMAPFetchRequest::IMAPFetchRequest(const QString& filter, mail::sas::MessageList* list) {
	_filter = filter;
	_list = list;
}

IMAPFetchRequest::~IMAPFetchRequest() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPFetchRequest::stateMethod(mail::sas::CommunicationService& service) {
	mail::sas::INetworkSingleStateSharedPtr retVal;

		if(!IMAPParser::isValid(_filter)) {
		    // Invalid input
		    retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Invalid Creds"));
		} else {

            // Ex: "a100 UID FETCH msgList email password\r\n"
			QString command;
			command.append("a106"); // Should technically be Replaced this with a dynamic tag count.
            command.append(" UID FETCH ");
            command.append(_filter);
            command.append(" (FLAGS BODY[HEADER.FIELDS (From To Subject Date)])");
            command.append("\r\n");

            if ( service.sendData(command)) {
        	    retVal = mail::sas::INetworkSingleStateSharedPtr(new IMAPFetchResponse(_filter, _list));
            }
		}

	return retVal;
}

IMAPFetchResponse::IMAPFetchResponse(const QString& filter, mail::sas::MessageList* list) {
	_filter = filter;
	_list = list;
}

IMAPFetchResponse::~IMAPFetchResponse() {
}

mail::sas::INetworkSingleStateSharedPtr IMAPFetchResponse::stateMethod(mail::sas::CommunicationService& service) {
	mail::sas::INetworkSingleStateSharedPtr retVal;
    QString response = service.receiveResponse();

	if (!service.error() && IMAPParser::isValid(response)) {

		// Parse for protocol error response if any: a100 BAD Command Error. 11
        if (IMAPParser::parseError(response, "a106")) {
            retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Parser Error"));
        } else {
            // No error
            qDebug() << "List Messages Successful";
            IMAPParser::parseFetch(response, _list);
        }

	} else {
	    retVal = mail::sas::INetworkSingleStateSharedPtr(new mail::sas::INetworkExceptionState("Invalid Network response"));
	}

	return retVal;
}


} /* namespace imap */
} /* namespace provider */
