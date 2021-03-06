/* qt_main.h - The interface for the RoadMap/QT main class.
 *
 * LICENSE:
 *
 *   (c) Copyright 2003 Latchesar Ionkov
 *
 *   This file is part of RoadMap.
 *
 *   RoadMap is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   RoadMap is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with RoadMap; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef INCLUDE__ROADMAP_QT_MAIN__H
#define INCLUDE__ROADMAP_QT_MAIN__H

#include <QDeclarativeView>
#include <QMap>
#include <QSocketNotifier>
#include <QPushButton>
#include <QTimer>
#include <QToolTip>
#include <QEvent>
#include <QIcon>
#include <QEventLoop>
#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QDeclarativeView>
#include <QSettings>
#define ROADMAP_MAX_TIMER 64

extern "C" {

#include "roadmap.h"
#include "roadmap_start.h"
#include "roadmap_config.h"
#include "roadmap_history.h"
#include "roadmap_main.h"
#include "roadmap_path.h"

typedef void (*RoadMapQtInput) (int fd);

BOOL roadmap_horizontal_screen_orientation();
void roadmap_main_message_dispatcher( int aMsg );
}

#include "qt_canvas.h"
#include "qt_contactslistmodel.h"

typedef enum
{
    _IO_DIR_UNDEFINED = 0x0,
    _IO_DIR_CONNECT = 0x1,
    _IO_DIR_READ = 0x2,
    _IO_DIR_WRITE = 0x4
} io_direction_type;

#define MSG_CATEGORY_IO_CALLBACK	0x010000
#define MSG_CATEGORY_IO_CLOSE		0x020000
#define MSG_CATEGORY_TIMER			0x040000
#define MSG_CATEGORY_MENU			0x080000
#define MSG_CATEGORY_RENDER			0x100000
#define MSG_CATEGORY_RESOLVER			0x200000

#define MSG_ID_MASK			0xFFFF

class QObservableInt : public QObject {

Q_OBJECT

public:
    QObservableInt();
    void setValue(int value);

signals:
    void valueChanged(int newValue);

private:
    int _value;
};

class RMapCallback : public QObject {

Q_OBJECT

public:
   RMapCallback(RoadMapCallback cb);

protected slots:
   void fire();

protected:
   RoadMapCallback callback;
};

class RMapTimerCallback : public QObject {

Q_OBJECT

public:
   RMapTimerCallback(RoadMapCallback cb);
   int same (RoadMapCallback cb);

protected slots:
   void fire();

protected:
   RoadMapCallback callback;
};

class RMapTimers : public QObject {

Q_OBJECT

public:
  RMapTimers(QObject *parent = 0);
  ~RMapTimers();
  void addTimer(int interval, RoadMapCallback cb);
  void removeTimer(RoadMapCallback cb);

private:
   QTimer* tm[ROADMAP_MAX_TIMER];
   RMapTimerCallback* tcb[ROADMAP_MAX_TIMER];

};

class RCommonApp : public QObject {
    Q_OBJECT

public:
    static void signalHandler(int sig);
    static RCommonApp* instance();

public slots:
    void invokeAction(QString actionName);
    void quit();
    void handleSignal(int sig);
    void mouseAreaPressed();

private:
   RCommonApp();
   ~RCommonApp();
   QObservableInt signalFd;

};

extern QDeclarativeView* mainWindow;

#endif
