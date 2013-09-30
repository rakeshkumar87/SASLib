/*
 * SAService.hpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#ifndef SASERVICE_HPP_
#define SASERVICE_HPP_

#include "Folder.hpp"
#include "Message.hpp"
#include "AccountSettings.hpp"
#include "StateMachineExecutor.hpp"
#include <QFutureWatcher>


/**
  Entry point for any method being called on any protocol.
  Typically needs to take an account settings object to determine protocol to interact with.
*/

namespace mail {
namespace sas {

class SAService {
public:
	SAService(const AccountSettings& account);
    ~SAService();

    /**
     * Logs into the account with the given account settings.
     * @return - returns true if success.
     */
	bool login();

	/**
	 * Logs out of the account.
	 * @return - returns true if success.*/
	bool logout();

	/**
	 * Fetches the list of folders in the given mailbox.
	 * @param mailboxName: Top level folder name.
	 * @param filter: filter to be applied
	 * @return- List of folders.
	 * e.g. folders("INBOX", "*")
	 */
	FolderList folders(const QString& mailboxName, const QString& filter);

	/**
	 * Fetches the list of messages in the given mailbox.
	 * @param mailboxName: Top level folder name.
	 * @param filter: filter to be applied
	 * @return- List of Messages.
	 * e.g. folders("INBOX", "*")
	 */
	MessageList messages(const QString& mailboxName, const QString& filter);

	/**
	 * Fetches the list of messages asynchronously. Sets the QFuture to the QFutureWatcher
	 * Object for client to listen to the completion notifications.
	 * @param mailboxName: Top level folder name.
	 * @param filter: filter to be applied
	 * @param watcher: Watcher object to listen for completion notification
	 * @return- List of Messages.
	 * e.g. folders("INBOX", "*")
	 */
     void asyncMessages(const QString& mailboxName, const QString& filter, QFutureWatcher<MessageList>& watcher);

private:
    // if shipping as a true library or a third party api, all these fields and methods should be
    // in SAServicePrivate
    AccountSettings _account;
    StateMachineExecutor _stateMachine;

    bool loginInternal(StateMachineExecutor& stateMachine);
    MessageList messagesInternal(const QString& mailboxName, const QString& filter, StateMachineExecutor& stateMachine);
    MessageList asyncMessagesInternal(QString mailboxName, QString filter);

};

} /* namespace sas */
} /* namespace mail */
#endif /* SASERVICE_HPP_ */
