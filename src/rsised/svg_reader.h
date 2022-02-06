/*
 * Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *
 * This file is part of the RSiSed project, a editor of the alignment of forces
 * and means in extinguishing a fire. (RSiSed)
 *
 * RSiSed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RSiSed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SVG_READER_H
#define SVG_READER_H

#include <QGraphicsItem>

QT_BEGIN_MOC_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class SvgReader
{
public:
    SvgReader(QMenu *itemMenu);

    QRectF getSize(const QString &fileName) const;
    QList<QGraphicsItem *> getElements(const QString &fileName);

private:
    enum class PathType{ Polyline, Curve };
    QMenu   *m_itemMenu;
    PathType currentPathType;
};

#endif // SVG_READER_H
