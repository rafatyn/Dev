/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *NameEdit;
    QLabel *label_2;
    QLineEdit *PassEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *LogInButton;
    QPushButton *RegisterButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(420, 224);
        centralwidget = new QWidget(Login);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        NameEdit = new QLineEdit(centralwidget);
        NameEdit->setObjectName(QStringLiteral("NameEdit"));

        verticalLayout->addWidget(NameEdit);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        PassEdit = new QLineEdit(centralwidget);
        PassEdit->setObjectName(QStringLiteral("PassEdit"));

        verticalLayout->addWidget(PassEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        LogInButton = new QPushButton(centralwidget);
        LogInButton->setObjectName(QStringLiteral("LogInButton"));
        LogInButton->setFocusPolicy(Qt::TabFocus);

        horizontalLayout->addWidget(LogInButton);

        RegisterButton = new QPushButton(centralwidget);
        RegisterButton->setObjectName(QStringLiteral("RegisterButton"));

        horizontalLayout->addWidget(RegisterButton);


        verticalLayout->addLayout(horizontalLayout);

        Login->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Login);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 420, 22));
        Login->setMenuBar(menubar);
        statusbar = new QStatusBar(Login);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Login->setStatusBar(statusbar);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QMainWindow *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "LogIn", Q_NULLPTR));
        label->setText(QApplication::translate("Login", "Please, write your name:", Q_NULLPTR));
        label_2->setText(QApplication::translate("Login", "And password:", Q_NULLPTR));
        LogInButton->setText(QApplication::translate("Login", "Log In", Q_NULLPTR));
        RegisterButton->setText(QApplication::translate("Login", "Register", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
