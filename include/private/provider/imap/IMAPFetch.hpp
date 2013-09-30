/*
 * IMAPFetch.hpp
 *
 *  Created on: Sep 29, 2013
 *      Author: Rakesh
 */

#ifndef IMAPFETCH_HPP_
#define IMAPFETCH_HPP_

#include "INetworkSingleState.hpp"
#include "Message.hpp"

namespace provider {
namespace imap {

class IMAPFetchRequest : public mail::sas::INetworkSingleState
{
public:
	IMAPFetchRequest(const QString& filter, mail::sas::MessageList* list);
	virtual ~IMAPFetchRequest();
	virtual mail::sas::INetworkSingleStateSharedPtr stateMethod( mail::sas::CommunicationService& service);
	virtual QString toString() { return "IMAPFetchRequest"; }
private:
	QString _filter;
	mail::sas::MessageList* _list;
};

class IMAPFetchResponse : public mail::sas::INetworkSingleState
{
public:
	IMAPFetchResponse(const QString& filter, mail::sas::MessageList* list);
	virtual ~IMAPFetchResponse();
	virtual mail::sas::INetworkSingleStateSharedPtr stateMethod( mail::sas::CommunicationService& service );
	virtual QString toString() { return "IMAPFetchResponse"; }
private:
	QString _filter;
	mail::sas::MessageList* _list;
};

} /* namespace imap */
} /* namespace provider */
#endif /* IMAPFETCH_HPP_ */
