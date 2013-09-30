/*
 * IMAPParser.hpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#ifndef IMAPPARSER_HPP_
#define IMAPPARSER_HPP_

#include "Folder.hpp"
#include "Message.hpp"

namespace provider {
namespace imap {

class IMAPParser {
public:
	IMAPParser();
	~IMAPParser();

	static bool isValid(const QString& authParam);
	static bool parseError(const QString& response, const QString& tag);
	static bool parseLogin(const QString& response);
	static bool parseList(const QString& response, mail::sas::FolderList* list);
	static bool parseSelect(const QString& response);
	static bool parseFetch(const QString& response, mail::sas::MessageList* list);

};

} /* namespace imap */
} /* namespace provider */
#endif /* IMAPPARSER_HPP_ */
