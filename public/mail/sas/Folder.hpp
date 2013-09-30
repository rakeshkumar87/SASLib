/*
 * Folder.hpp
 *
 *  Created on: Sep 28, 2013
 *      Author: Rakesh
 */

#ifndef FOLDER_HPP_
#define FOLDER_HPP_

#include <QString>
#include <QList>

namespace mail {
namespace sas {

class Folder {
public:
	Folder();
	~Folder();

	bool hasChildren();
	QString folderPath();

	void setHasChildren(bool hasChildren);
	void setFolderPath(const QString& folderPath);

private:
	bool _hasChildren;
	QString _folderPath;
};

typedef QList<Folder> FolderList;

} /* namespace sas */
} /* namespace mail */
#endif /* FOLDER_HPP_ */
