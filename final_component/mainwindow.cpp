#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <QThread>

const int comport_number = 0;
const int baudrate = 115200;
const char * mode = "8N1";
const int d = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::transfer_image( bmp_file image)
{
    int result = 1;

    for ( unsigned int i = 0; i < (image.getHeight() * image.getWidth()); i++)
    {
        result = RS232_SendByte(comport_number,image.getPixel(i+image.getStartOfBitmap()));

        //ui->progress->setValue(i);

        //printf (&quot;Shade %d\t counter is %d\n&quot;,new_value, i);

        if( result == 1)
        {
            QMessageBox failed_send;
            failed_send.setText("Error: Sending Image Byte Failed.");
            failed_send.exec();
        }

        QThread::usleep(d);
    }
}

void MainWindow::on_ProcessImage_clicked()
{
    unsigned char tag = 0x03;
    int result = 1;

    result = RS232_SendByte(comport_number,tag);

    if( result == 1)
    {
        QMessageBox sending_tag_error;
        sending_tag_error.setText("Sending the Tag failed");
        sending_tag_error.exec();
    }

   else
   {
        QThread::usleep(d);
   }
}

void MainWindow::on_TransferOverlay_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Open Bitmap"),
                    "Bitmap Images (*.bmp);;All Files (*.*)"
                     );
    if(fileName != "")
    {
        //ui->progress->setHidden(false);
        QByteArray temp = fileName.toLatin1();
        bmp_file overlay_image;
        overlay_image = bmp_file(temp.data());
        int result = 1;

        if ( overlay_image.getWidth() != 320 || overlay_image.getHeight() != 240)
        {
            QMessageBox width_error;
            width_error.setText("Error: Width of image is incompatible");
            width_error.exec();
        }
        else
        {
            unsigned char tag = 0x0C;
            result = RS232_SendByte(comport_number,tag);

            if( result == 1)
            {
                QMessageBox sending_tag_error;
                sending_tag_error.setText("Sending the Tag failed");
                sending_tag_error.exec();
            }
            else
            {
                 QThread::usleep(d);
                 transfer_image(overlay_image);
            }
        }
    }
}

void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    unsigned char tag = 0x30;
    int result = 1;
    result = RS232_SendByte(comport_number,tag);

    if( result == 1)
    {
        QMessageBox sending_tag_error;
        sending_tag_error.setText("Sending the Tag failed");
        sending_tag_error.exec();

    }
    else
    {
        int opResult = RS232_SendByte(comport_number, (unsigned char)value);

        if(opResult == 1)
        {
            QMessageBox failed_send;
            failed_send.setText("Error: Sending Brightness Failed.");
            failed_send.exec();
        }

        QThread::usleep(d);

    }
}

void MainWindow::on_constastSlider_valueChanged(int value)
{
    unsigned char tag = 0xC0;
    int result = 1;
    result = RS232_SendByte(comport_number,tag);

    if( result == 1)
    {
        QMessageBox sending_tag_error;
        sending_tag_error.setText("Sending the Tag failed");
        sending_tag_error.exec();
    }

    else
    {
        int opResult = RS232_SendByte(comport_number, (unsigned char)value);

        if(opResult == 1)
        {
            QMessageBox failed_send;
            failed_send.setText("Error: Sending Contrast Failed.");
            failed_send.exec();
        }

        QThread::usleep(d);

        //ui->disp->setText(QString::number(value));

    }
}
