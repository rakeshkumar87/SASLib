/*
 * Message.hpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include<QString>
#include<QList>

namespace mail {
namespace sas {

class Message {
public:
	Message();
	~Message();

	QString id();
	QString from();
	QString subject();
	QString date();
	QString to();

	void setId(const QString& uid);
	void setFrom(const QString& from);
	void setSubject(const QString& subject);
	void setDate(const QString& date);
	void setTo(const QString& to);

private:
	QString _uid;
	QString _from;
	QString _subject;
	QString _date;
	QString _to;
};

typedef QList<Message> MessageList;

} /* namespace sas */
} /* namespace mail */

#endif /* MESSAGE_HPP_ */
