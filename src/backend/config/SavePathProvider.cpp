/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "SavePathProvider.h"

SavePathProvider::SavePathProvider()
{
    mConfig = KsnipConfigProvider::instance();
}

QString SavePathProvider::savePath() const
{
    return PathHelper::makeUniqueFilename(saveDirectory(), getFilename(), mConfig->saveFormat());
}

QString SavePathProvider::savePathWithFormat(const QString &format) const
{
    return PathHelper::makeUniqueFilename(saveDirectory(), getFilename(), getFormat(format));
}

QString SavePathProvider::getFilename() const
{
    return PathHelper::replaceWildcards(mConfig->saveFilename());
}

QString SavePathProvider::getFormat(const QString &format) const
{
    return format.startsWith(QStringLiteral(".")) ? format : QStringLiteral(".") + format;
}

QString SavePathProvider::saveDirectory() const
{
	auto path = mConfig->saveDirectory();
	if (path.isEmpty()) {
		auto lastPath = mConfig->lastSaveDirectory();
		if (!lastPath.isEmpty()) {
			path = lastPath;
		}
	}
    return PathHelper::replaceWildcards(path);
}

