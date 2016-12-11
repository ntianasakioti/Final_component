#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rs232.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <string>
#include "bmp_file.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ProcessImage_clicked();

    void on_TransferOverlay_clicked();

    void on_brightnessSlider_valueChanged(int value);

    void on_constastSlider_valueChanged(int value);

    void transfer_image( bmp_file image);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
