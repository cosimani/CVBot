/********************************************************************************
** Form generated from reading UI file 'principal.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPAL_H
#define UI_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "ventana.h"

QT_BEGIN_NAMESPACE

class Ui_Principal
{
public:
    QGridLayout *gridLayout;
    Ventana *ventana;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *lEstado;

    void setupUi(QWidget *Principal)
    {
        if (Principal->objectName().isEmpty())
            Principal->setObjectName(QStringLiteral("Principal"));
        Principal->resize(400, 300);
        gridLayout = new QGridLayout(Principal);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ventana = new Ventana(Principal);
        ventana->setObjectName(QStringLiteral("ventana"));
        gridLayout_2 = new QGridLayout(ventana);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 223, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 1);


        gridLayout->addWidget(ventana, 1, 0, 1, 1);

        lEstado = new QLabel(Principal);
        lEstado->setObjectName(QStringLiteral("lEstado"));
        QFont font;
        font.setFamily(QStringLiteral("IPAGothic"));
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        lEstado->setFont(font);
        lEstado->setTextFormat(Qt::AutoText);
        lEstado->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lEstado, 0, 0, 1, 1);


        retranslateUi(Principal);

        QMetaObject::connectSlotsByName(Principal);
    } // setupUi

    void retranslateUi(QWidget *Principal)
    {
        Principal->setWindowTitle(QApplication::translate("Principal", "Form", Q_NULLPTR));
        lEstado->setText(QApplication::translate("Principal", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Principal: public Ui_Principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
