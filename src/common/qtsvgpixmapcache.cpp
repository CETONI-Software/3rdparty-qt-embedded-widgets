/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#include "qtsvgpixmapcache.h"

#include <QtGui/QPainter>
#include <QtSvg/QSvgRenderer>
#include <QDebug>

#include <iostream>


class QtSvgPixmapCachePrivate
{
public:
    void updatePixmapCache(const QSizeF& size);

public:
    QSvgRenderer svgRenderer;
    QPixmap pixmapCache;
    double DevicePixelRatio = 1;
};

QtSvgPixmapCache::QtSvgPixmapCache(QObject* parent) : QObject(parent)
    , d(new QtSvgPixmapCachePrivate())
{
}

QtSvgPixmapCache::QtSvgPixmapCache(const QString& url)
    : d(new QtSvgPixmapCachePrivate())
{
    load(url);
}

QtSvgPixmapCache::~QtSvgPixmapCache()
{
    delete d;
}

bool QtSvgPixmapCache::load(const QString& url)
{
    d->svgRenderer.load(url);
    d->pixmapCache = QPixmap();
    return d->pixmapCache.isNull();
}

bool QtSvgPixmapCache::isValid() const
{
    return d->svgRenderer.isValid();
}

void QtSvgPixmapCache::render(QPainter* painter, const QRectF& bounds)
{
    if (!d->svgRenderer.isValid()) {
        return;
    }

    QSizeF BoundsSize = bounds.size() * d->DevicePixelRatio;
    if (d->pixmapCache.isNull() || BoundsSize.toSize() != d->pixmapCache.size()
    	|| d->DevicePixelRatio != painter->device()->devicePixelRatioF())
    {
    	d->DevicePixelRatio = painter->device()->devicePixelRatioF();
        d->updatePixmapCache(bounds.size());
    }

    painter->drawPixmap(bounds.topLeft(), d->pixmapCache);
}

QSize QtSvgPixmapCache::defaultSize() const
{
    return d->svgRenderer.defaultSize();
}

void QtSvgPixmapCachePrivate::updatePixmapCache(const QSizeF& size)
{
	QSizeF PixmapSize = size * DevicePixelRatio;
	pixmapCache = QPixmap(PixmapSize.toSize());
    pixmapCache.fill(Qt::transparent);

    QPainter painter(&pixmapCache);
    svgRenderer.render(&painter);
    painter.end();
	pixmapCache.setDevicePixelRatio(DevicePixelRatio);
}
