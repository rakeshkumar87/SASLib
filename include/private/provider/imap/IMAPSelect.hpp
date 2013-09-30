/*
 * IMAPSelect.hpp
 *
 *  Created on: Sep 29, 2013
 *      Author: Rakesh
 */

#ifndef IMAPSELECT_HPP_
#define IMAPSELECT_HPP_

#include "INetworkSingleState.hpp"


namespace provider {
namespace imap {

class IMAPSelectRequest : public mail::sas::INetworkSingleState
{
public:
	IMAPSelectRequest(const QString& mailboxName);
	virtual ~IMAPSelectRequest();
	mail::sas::INetworkSingleStateSharedPtr stateMethod( mail::sas::CommunicationService& service);
	QString toString() { return "IMapSelectRequest"; }

private:
	QString _mailboxName;

};

class IMAPSelectResponse : public mail::sas::INetworkSingleState
{
public:
	IMAPSelectResponse();
	virtual ~IMAPSelectResponse();
	mail::sas::INetworkSingleStateSharedPtr stateMethod( mail::sas::CommunicationService& service );
	QString toString() { return "IMapSelectResponse"; }
};

} /* namespace imap */
} /* namespace provider */
#endif /* IMAPSELECT_HPP_ */
