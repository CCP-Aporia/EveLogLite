#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QTimer>
#include "abstractlogmodel.h"

class SearchBox;
class LogStatistics;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &fileName, QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent *event);
private:
    void openFilePath(QString fileName);

    Ui::MainWindow *ui;
    LogStatistics *m_stats;
    QTimer m_quickFilterEdited;
    bool m_monospaceFont;
private slots:
    void itemSelected();
    void anchorClicked(const QUrl& url);
    void itemMenu(QPoint pos);
    void urlClicked();

    void textFilterChanged();
    void textFilterTimeout();

    void openFind();
    void findNext();
    void findPrevious();

    void columnMenu(const QPoint &position);
    void columnMenuChanged();
    void columnMoved();

    void copySelection();
    void copyMessages();
    void selectAll();

    void openFile();
    void saveFile();
    void exportAsText();

    void setServerMode();
    void splitByPids();
    void showSettings();
    void showAboutDialog();

    void editFilters();
    void editHighlights();

    void buildFiltersMenu();
    void customFilterSet(QAction*);

    void buildHighlightsMenu();
    void highlightSet(QAction*);
    void showFilterMenu();
    void showHighlightsMenu();

    void buildClientsMenu();
    void disconnectClient();
};

#endif // MAINWINDOW_H
