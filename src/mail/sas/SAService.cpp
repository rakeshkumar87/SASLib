/*
 * SAService.cpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#include "SAService.hpp"
#include "AccountSettings.hpp"
#include "IMAPLogin.hpp"
#include "IMAPLogout.hpp"
#include "IMAPList.hpp"
#include "IMAPSelect.hpp"
#include "IMAPFetch.hpp"
#include <QtConcurrentRun>

namespace mail {
namespace sas {

SAService::SAService(const AccountSettings& account)
    : _account(account),
      _stateMachine(account)
{
}

SAService::~SAService() {
    logout();
}

bool SAService::login() {
	return loginInternal(_stateMachine);
}

bool SAService::loginInternal(StateMachineExecutor& stateMachine) {
	// Ideally you want to get this request object from a factory
	INetworkSingleStateSharedPtr finalState =
			               INetworkSingleStateSharedPtr(new provider::imap::IMAPLoginRequest(_account));
    stateMachine.setFinalState(finalState);
    return stateMachine.execute();
}


bool SAService::logout() {
	INetworkSingleStateSharedPtr finalState = INetworkSingleStateSharedPtr(new provider::imap::IMAPLogoutRequest());
	_stateMachine.setFinalState(finalState);
    return _stateMachine.execute();
}


FolderList SAService::folders(const QString& mailboxName, const QString& filter) {
	FolderList list;
	INetworkSingleStateSharedPtr finalState =
			INetworkSingleStateSharedPtr(new provider::imap::IMAPListRequest(mailboxName, filter, &list));
    _stateMachine.setFinalState(finalState);
	_stateMachine.execute();
    return list;
}


MessageList SAService::messages(const QString& mailboxName, const QString& filter) {
    return messagesInternal(mailboxName, filter, _stateMachine);
}

MessageList SAService::messagesInternal(const QString& mailboxName, const QString& filter, StateMachineExecutor& stateMachine) {
	MessageList list;
	INetworkSingleStateSharedPtr selectState =
			     INetworkSingleStateSharedPtr(new provider::imap::IMAPSelectRequest(mailboxName));

	INetworkSingleStateSharedPtr fetchState =
			     INetworkSingleStateSharedPtr(new provider::imap::IMAPFetchRequest(filter, &list));

	stateMachine.setFinalState(fetchState);
	stateMachine.addState(selectState);
    stateMachine.execute();
    return list;
}

void SAService::asyncMessages(const QString& mailboxName, const QString& filter, QFutureWatcher<MessageList>& watcher){
	QFuture<MessageList> future = QtConcurrent::run(this, &SAService::asyncMessagesInternal, mailboxName, filter);
	watcher.setFuture(future);
}

MessageList SAService::asyncMessagesInternal(QString mailboxName, QString filter){
    MessageList list;
    AccountSettings account(_account);
    StateMachineExecutor stateMachine(account);
    if ( loginInternal(stateMachine) ) {
        list = messagesInternal(mailboxName, filter, stateMachine);
    }
    return list;
}

} /* namespace sas */
} /* namespace mail */
