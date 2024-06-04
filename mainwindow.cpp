#include "mainwindow.h"
#include "./ui_mainwindow.h"

int num_generated_flag=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCursorAllScreen(Qt::CursorShape shape)
{
    QCursor qc;
    qc.setShape(shape);
    MainWindow::setCursor(qc);
    ui->ArraySizeLineEdit->setCursor(qc);
    ui->enterArraySizeText->setCursor(qc);
    ui->BitonicSortButton->setCursor(qc);
    ui->BlockSortButton->setCursor(qc);
    ui->SampleSortButton->setCursor(qc);
    ui->stdSortButton->setCursor(qc);
    ui->InputDataButton->setCursor(qc);
    ui->centralwidget->setCursor(qc);
    ui->numGenerateButton->setCursor(qc);
    ui->menubar->setCursor(qc);
    ui->OutputDataButton->setCursor(qc);
    ui->label->setCursor(qc);
    ui->maxNumberLineEdit->setCursor(qc);
}

void MainWindow::on_BlockSortButton_clicked()
{
    if (!num_generated_flag)
    {
        ui->screenOutput->setText("Произошла ошибка!\nСначала сгенерируйте данные");
        return;
    }
    int num;
    if (ui->ArraySizeLineEdit->isModified())
    {
        num = ui->ArraySizeLineEdit->text().toInt();
    }
    block_sort bs(num);
    setCursorAllScreen(Qt::CursorShape::WaitCursor);
    QString qstr = bs.sort_16();
    setCursorAllScreen(Qt::CursorShape::ArrowCursor);
    ui->screenOutput->setText(qstr);
}

void MainWindow::on_BitonicSortButton_clicked()
{
    if (!num_generated_flag)
    {
        ui->screenOutput->setText("Произошла ошибка!\nСначала сгенерируйте данные");
        return;
    }
    int num;
    if (ui->ArraySizeLineEdit->isModified())
    {
        num = ui->ArraySizeLineEdit->text().toInt();
    }
    setCursorAllScreen(Qt::CursorShape::WaitCursor);
    QString qstr = batcher_recursive_init(num);
    setCursorAllScreen(Qt::CursorShape::ArrowCursor);
    ui->screenOutput->setText(qstr);
}

void MainWindow::on_SampleSortButton_clicked()
{
    if (!num_generated_flag)
    {
        ui->screenOutput->setText("Произошла ошибка!\nСначала сгенерируйте данные");
        return;
    }
    int num;
    if (ui->ArraySizeLineEdit->isModified())
    {
        num = ui->ArraySizeLineEdit->text().toInt();
    }
    SampleSort ss(num);
    setCursorAllScreen(Qt::CursorShape::WaitCursor);
    QString qstr = ss.sort();
    setCursorAllScreen(Qt::CursorShape::ArrowCursor);
    ui->screenOutput->setText(qstr);
}

void MainWindow::on_stdSortButton_clicked()
{
    if (!num_generated_flag)
    {
        ui->screenOutput->setText("Произошла ошибка!\nСначала сгенерируйте данные");
        return;
    }
    int num;
    if (ui->ArraySizeLineEdit->isModified())
    {
        num = ui->ArraySizeLineEdit->text().toInt();
    }
    check_stdsort cs;
    setCursorAllScreen(Qt::CursorShape::WaitCursor);
    QString qstr = cs.sort(num);
    setCursorAllScreen(Qt::CursorShape::ArrowCursor);
    ui->screenOutput->setText(qstr);
}

void MainWindow::on_InputDataButton_clicked()
{
    system(".\\in.txt");
}

void MainWindow::on_OutputDataButton_clicked()
{
    system(".\\out.txt");
}

void MainWindow::on_numGenerateButton_clicked()
{
    int num, max_num;
    if (ui->ArraySizeLineEdit->isModified())
    {
        num = ui->ArraySizeLineEdit->text().toInt();
    }
    if (ui->maxNumberLineEdit->isModified())
    {
        max_num = ui->maxNumberLineEdit->text().toInt();
    }
    if (num!=0 && max_num!=0 && ui->ArraySizeLineEdit->text().size() <= 11 && ui->maxNumberLineEdit->text().size() <= 11 && ui->maxNumberLineEdit->isModified())
    {
        setCursorAllScreen(Qt::CursorShape::WaitCursor);
        random_numbers_at_file("in.txt", num, max_num);

        setCursorAllScreen(Qt::CursorShape::ArrowCursor);
        num_generated_flag = 1;
        ui->screenOutput->setText("Успешная генерация");
    }
    else
    {
        ui->screenOutput->setText("Произошла ошибка!\nСначала задайте размер массива\nи максимальное число в массиве,\nа также проверьте правильный формат данных");
    }
}

