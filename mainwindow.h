#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QCursor>

#include "src/block_sort.h"
#include "src/batcher_recursive.h"
#include "src/sample_sort.h"
#include "src/check_stdsort.h"
#include "src/generator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BlockSortButton_clicked();

    void on_BitonicSortButton_clicked();

    void on_SampleSortButton_clicked();

    void on_InputDataButton_clicked();

    void on_OutputDataButton_clicked();

    void on_stdSortButton_clicked();

    void on_numGenerateButton_clicked();

private:
    void setCursorAllScreen(Qt::CursorShape shape);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
