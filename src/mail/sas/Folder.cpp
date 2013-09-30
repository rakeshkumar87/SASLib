/*
 * Folder.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#include "Folder.hpp"

namespace mail {
namespace sas {

Folder::Folder() {
	_hasChildren = false;
	_folderPath = "";
}

Folder::~Folder() {

}

bool Folder::hasChildren() {
	return _hasChildren;
}

QString Folder::folderPath() {
	return _folderPath;
}

void Folder::setHasChildren(bool hasChildren){
    _hasChildren = hasChildren;
}

void Folder::setFolderPath(const QString& folderPath) {
	_folderPath = folderPath;
}


} /* namespace sas */
} /* namespace mail */
