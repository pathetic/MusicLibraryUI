#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void RefreshTable();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_updateBtn_clicked();

    void on_actionCombo_currentIndexChanged(int index);

    void on_listenSong_clicked();

    void enableUndoBtn(bool enabled);

    void enableRedoBtn(bool enabled);

    void on_undoBtn_clicked();

    void on_redoBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
