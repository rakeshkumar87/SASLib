/*
 * IMAPList.hpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#ifndef IMAPLIST_HPP_
#define IMAPLIST_HPP_

#include "Folder.hpp"
#include "INetworkSingleState.hpp"

namespace provider {
namespace imap {

class IMAPListRequest : public mail::sas::INetworkSingleState {
public:
	IMAPListRequest(const QString& mailboxName, const QString& filter, mail::sas::FolderList* list);
	virtual ~IMAPListRequest();
	mail::sas::INetworkSingleStateSharedPtr stateMethod(mail::sas::CommunicationService& service);
	QString toString() { return "IMapListRequest"; }

private:
	QString _mailboxName;
	QString _filter;
	mail::sas::FolderList* _list;
};

class IMAPListResponse : public mail::sas::INetworkSingleState {
public:
	IMAPListResponse(mail::sas::FolderList* list);
	virtual ~IMAPListResponse();
	mail::sas::INetworkSingleStateSharedPtr stateMethod(mail::sas::CommunicationService& service);
	QString toString() { return "IMapListRequest"; }

private:
	mail::sas::FolderList* _list;
};

} /* namespace imap */
} /* namespace provider */
#endif /* IMAPLIST_HPP_ */
