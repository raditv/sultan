/*
 * additemdialog.h
 * Copyright 2017 - ~, Apin <apin.klas@gmail.com>
 *
 * This file is part of Turbin.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include "messagehandler.h"
#include <QDialog>

namespace Ui {
class AddItemDialog;
}

namespace LibGUI {

class AddItemDialog : public QDialog, public LibG::MessageHandler
{
    Q_OBJECT

public:
    enum Tab { Price, Package, Ingridient };
    AddItemDialog(LibG::MessageBus *bus, QWidget *parent = 0);
    ~AddItemDialog();
    void reset(bool isAddAgain = false);
    void fill(const QVariantMap &data);
    void setAsUpdate();
    void disableAddAgain();
    void setBarcode(const QString &barcode);
    inline bool isSuccess() { return mIsSuccess; }

protected:
    void messageReceived(LibG::Message *msg) override;
    void showEvent(QShowEvent *event) override;

private:
    Ui::AddItemDialog *ui;
    bool mIsUpdate = false;
    bool mIsAddAgain = false;
    int mCurrentSuplier = 0;
    int mCUrrentCategory = 0;
    bool mIsOk = false;
    bool mIsReturnPressed = false;
    bool mIsSuccess = false;
    QString mCurrentUnit;
    QVariantList mPriceList;

    void saveData();
    int getItemFlagFromCheckbox();
    void applyItemFlagToCheckbox(int flag);

private slots:
    void barcodeDone();
    void returnPressed();
    void saveClicked();
    void saveAndAgainClicked();
    void checkWidget();
    void calculateDiscount();
    void addPriceClicked();
    void updatePriceClicked(const QModelIndex &index);
    void deletePriceClicked(const QModelIndex &index);
    void openSearchItem();
    void getItemPrice();
    double updatePackagePrice();

signals:
    void success();
};

}
#endif // ADDITEMDIALOG_H
