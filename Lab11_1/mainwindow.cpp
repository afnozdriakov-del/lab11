#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->labelResult->setText("...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Кнопка "Вычислить"
void MainWindow::on_pushButtonCalc_clicked()
{
    QString text = ui->lineEditYear->text();

    bool ok;

    int year = text.toInt(&ok);

    // Проверка ввода
    if (!ok || year <= 0)
    {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Введите корректный положительный год!"
            );

        return;
    }

    // Вычисление столетия
    int century = (year - 1) / 100 + 1;

    // Вывод результата
    ui->labelResult->setText(
        QString::number(century)
        );
}

// Открытие файла
void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Открыть файл",
        "",
        "Text Files (*.txt)"
        );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(
            this,
            "Ошибка",
            "Не удалось открыть файл!"
            );

        return;
    }

    QTextStream in(&file);

    QString year = in.readLine();

    ui->lineEditYear->setText(year);

    file.close();
}

// Сохранение файла
void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить файл",
        "",
        "Text Files (*.txt)"
        );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(
            this,
            "Ошибка",
            "Не удалось сохранить файл!"
            );

        return;
    }

    QTextStream out(&file);

    out << "Год: "
        << ui->lineEditYear->text()
        << "\n";

    out << "Столетие: "
        << ui->labelResult->text()
        << "\n";

    file.close();

    QMessageBox::information(
        this,
        "Успех",
        "Файл успешно сохранён!"
        );
}

// Выход
void MainWindow::on_actionExit_triggered()
{
    close();
}