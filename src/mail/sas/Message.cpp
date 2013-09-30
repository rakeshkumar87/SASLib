/*
 * Message.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#include "Message.hpp"

namespace mail {
namespace sas {

Message::Message() {

}

Message::~Message() {

}

QString Message::id() {
	return _uid;
}

QString Message::from() {
	return _from;
}

QString Message::subject() {
    return _subject;
}

QString Message::date() {
	return _date;
}

QString Message::to() {
	return _to;
}

void Message::setId(const QString& uid) {
	_uid = uid;
}

void Message::setFrom(const QString& from) {
    _from = from;
}

void Message::setSubject(const QString& subject) {
	_subject = subject;
}

void Message::setDate(const QString& date) {
	_date = date;
}

void Message::setTo(const QString& to) {
	_to = to;
}


} /* namespace sas */
} /* namespace mail */
