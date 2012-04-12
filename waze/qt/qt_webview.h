#ifndef QT_WEBVIEW_H
#define QT_WEBVIEW_H

#include <QDeclarativeView>
#include <QUrl>
#include "qt_main.h"

class WazeWebView : public QDeclarativeView
{
    Q_OBJECT

    public:
        explicit WazeWebView(RMapMainWindow *parent = 0);
        void show(QUrl url, int flags);
        void hide();

    signals:

    public slots:

    private:
        RMapMainWindow *mainWindow;
    };

#endif // QT_WEBVIEW_H