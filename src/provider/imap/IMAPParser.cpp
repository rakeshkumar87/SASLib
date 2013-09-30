/*
 * IMAPParser.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#include "IMAPParser.hpp"
#include <QRegExp>
#include <QStringList>


namespace provider {
namespace imap {

IMAPParser::IMAPParser() {
}

IMAPParser::~IMAPParser() {
}

bool IMAPParser::isValid(const QString& authParam) {
	return ( !authParam.isNull() && !authParam.isEmpty() && authParam.length() > 0);
}


bool IMAPParser::parseError(const QString& response, const QString& tag) {

	bool retVal = false;

	if (response.isEmpty() || response.isNull() ) {
	    retVal = true;
	} else {
	    QStringList lines = response.split("\r\n");
	    int length = lines.length() - 1;
        int i = length;

	    while ( i >= 0 ) {
	    	QString line = lines.at(i);
	    	if ( line.contains(tag) ) {
	             if ( line.contains("BAD") || line.contains("NO") ) {
	                 retVal = true;
	             }
	             break;
	        }
	    	i--;
	    }
	}

	return retVal;
}


bool IMAPParser::parseLogin(const QString& response) {
	bool retVal = false;

	if (!response.isEmpty() || !response.isNull() ) {
	    if ( response.contains("SUCCESS", Qt::CaseInsensitive)) {
	    	retVal = true;
	    }
	}

	return retVal;
}

bool IMAPParser::parseSelect(const QString& response) {
	return parseLogin(response);
}

bool IMAPParser::parseList(const QString& response, mail::sas::FolderList* folderList){
	bool retVal = false;
	if (!response.isEmpty() || !response.isNull() ) {

	    QStringList sList = response.split("\r\n");
	    sList.removeLast();
	    sList.removeLast();
	    QStringListIterator itr(sList);

	    while ( itr.hasNext()) {
	        QString listLine = itr.next();
	        mail::sas::Folder folder;
	        if ( listLine.contains("haschildren",Qt::CaseInsensitive) ) {
	        	folder.setHasChildren(true);
	        }
	        QStringList folderAttr = listLine.split('"');
	        folderAttr.removeLast();
            folder.setFolderPath(folderAttr.last());
            folderList->append(folder);
	    }

	    retVal = true;
	}
    return retVal;
}

bool IMAPParser::parseFetch(const QString& response, mail::sas::MessageList* messageList) {
    bool retVal = false;
	if (!response.isEmpty() || !response.isNull() ) {

		QStringList mList = response.split("FETCH (UID");
		QStringListIterator messageItr(mList);

		while ( messageItr.hasNext() ) {
			QString msgAttr = messageItr.next();

			// rough estimate for skipping unwanted strings. Wouldn't do this in production :)
			if ( msgAttr.size() < 6) {
				continue;
			}

	        mail::sas::Message message;
            QStringList attrList = msgAttr.split("\n");
            message.setDate(attrList.at(1).split("Date:").at(1));
            message.setSubject(attrList.at(2).split("Subject:").at(1));
            message.setFrom(attrList.at(3).split("From:").at(1));
            message.setTo(attrList.at(4).split("To:").at(1));
            messageList->append(message);
		}

		retVal = true;
	}

	return retVal;
}



} /* namespace imap */
} /* namespace provider */
