#include <QtGlobal>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QSettings settings;
    ui->CommandPathText->setText(settings.value("talkPath").toString());
    ui->ServerMode->setChecked(settings.value("ServerMode", false).toBool());
    ui->ServerAddresText->setText(settings.value("ServerAddres", "127.0.0.1").toString());
    ui->PortSpinBox->setValue(settings.value("Port", 6000).toInt());


    QByteArray username = qgetenv("USER");
    if (!username.isNull())
        ui->UserBoxText->setText(settings.value("Username", username).toString());
    else
        ui->UserBoxText->setText(settings.value("Username", "").toString());
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_BrowseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isNull())
        ui->CommandPathText->setText(fileName);
}

void SettingsDialog::done(int r)
{
    if (r == QDialog::Accepted) {
        if (ui->CommandPathText->text().isEmpty()) {
            QMessageBox::critical(this, "Talk GUI", "Se necesita una ruta al comando talk.");
            return;
        }
        else if (!ui->ServerMode->isChecked() && ui->ServerAddresText->text().isEmpty()) {
            QMessageBox::critical(this, "Talk GUI", "Se necesita la direccion del servidor.");
            return;
        }
        else {
            QSettings settings;
            settings.setValue("talkPath", ui->CommandPathText->text());
            settings.setValue("ServerMode", ui->ServerMode->isChecked());
            settings.setValue("ServerAddres", ui->ServerAddresText->text());
            settings.setValue("Port", ui->PortSpinBox->value());
            if (ui->UserBoxText->text().isEmpty()) {
                settings.remove("Username");
            }else
                settings.setValue("Username", ui->UserBoxText->text());
            QDialog::done(r);
            return;
        }
    }
    else QDialog::done(r);
}

void SettingsDialog::on_ServerMode_toggled(bool checked)
{
    ui->ServerAddresText->setDisabled(checked);
    ui->ServerAddresLabel->setDisabled(checked);
}
