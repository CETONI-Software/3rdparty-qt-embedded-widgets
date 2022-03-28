/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/
// Button implemented as a switch
// Compared to a QPushButton it's less likely that this button
// will be pressed accidently

#ifndef QT_SVG_SPIN_BUTTON_H
#define QT_SVG_SPIN_BUTTON_H

#include <QRect>
#include <QAbstractButton>

class QtSvgPixmapCache;
class QtNavigationButton;


class QtSvgSpinButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
public:
    explicit QtSvgSpinButton(QWidget * parent = 0);
    virtual ~QtSvgSpinButton();

    QAbstractButton * upButton();
    QAbstractButton * downButton();

    void setSkin(const QString& skin);
    QString skin() const;

private Q_SLOTS:

protected:
    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);
    virtual int heightForWidth(int w) const;

private:
    void init();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    /** name of actual skin **/
    QString m_skin;

    /** pointer to one Button **/
    QtNavigationButton* m_upButton;
    /** pointer to one Button **/
    QtNavigationButton* m_downButton;
};


#endif // QT_SVG_SPIN_BUTTON_H
