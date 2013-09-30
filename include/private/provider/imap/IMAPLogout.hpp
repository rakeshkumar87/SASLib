/*
 * IMAPLogout.hpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#ifndef IMAPLOGOUT_HPP_
#define IMAPLOGOUT_HPP_

#include "INetworkSingleState.hpp"
#include <QSharedPointer>

namespace provider {
namespace imap {

class IMAPLogoutRequest : public mail::sas::INetworkSingleState
{
public:
	IMAPLogoutRequest();
	virtual ~IMAPLogoutRequest();
	mail::sas::INetworkSingleStateSharedPtr stateMethod( mail::sas::CommunicationService& service);
	QString toString() { return "IMAPLogoutRequest"; }

};

class IMAPLogoutResponse : public mail::sas::INetworkSingleState
{
public:
	IMAPLogoutResponse();
	virtual ~IMAPLogoutResponse();
	mail::sas::INetworkSingleStateSharedPtr stateMethod( mail::sas::CommunicationService& service );
	QString toString() { return "IMAPLogoutResponse"; }
};

} /* namespace imap */
} /* namespace provider */
#endif /* IMAPLOGOUT_HPP_ */
