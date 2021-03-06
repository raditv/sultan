#include "editpricecountdialog.h"
#include "ui_editpricecountdialog.h"
#include "global_constant.h"
#include "message.h"
#include "util.h"
#include "preference.h"

using namespace LibGUI;
using namespace LibG;

EditPriceCountDialog::EditPriceCountDialog(MessageBus *bus, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPriceCountDialog)
{
    ui->setupUi(this);
    setMessageBus(bus);
    connect(ui->doublePrice, SIGNAL(valueChanged(double)), SLOT(updatePrice()));
    connect(ui->lineDiscount, SIGNAL(textChanged(QString)), SLOT(updatePrice()));
    connect(ui->pushSave, SIGNAL(clicked(bool)), SLOT(saveClicked()));
}

EditPriceCountDialog::~EditPriceCountDialog()
{
    delete ui;
}

void EditPriceCountDialog::setup(const QString &barcode, float count, double price, const QString disc)
{
    ui->doubleCount->setValue(count);
    ui->doublePrice->setValue(price);
    ui->lineDiscount->setText(disc);
    Message msg(MSG_TYPE::ITEM, MSG_COMMAND::CASHIER_PRICE);
    msg.addData("barcode", barcode);
    sendMessage(&msg);
    ui->doubleCount->selectAll();
}

float EditPriceCountDialog::getCount() { return ui->doubleCount->value(); }

double EditPriceCountDialog::getPrice() { return ui->doublePrice->value(); }

QString EditPriceCountDialog::getDiscountFormula() { return ui->lineDiscount->text(); }

void EditPriceCountDialog::messageReceived(LibG::Message *msg)
{
    if(msg->isTypeCommand(MSG_TYPE::ITEM, MSG_COMMAND::CASHIER_PRICE) && msg->isSuccess()) {
        const QVariantList &list = msg->data("prices").toList();
        if(!list.isEmpty()) {
            const QVariantMap &d = list.first().toMap();
            ui->labelMasterPrice->setText(tr("Master price : %1").arg(Preference::toString(d["price"].toDouble())));
            ui->labelMasterDiscount->setText(tr("Master discount : %1").arg(d["discount_formula"].toString()));
        }
    }
}

void EditPriceCountDialog::updatePrice()
{
    auto disc = Util::calculateDiscount(ui->lineDiscount->text(), ui->doublePrice->value());
    ui->labelDiscount->setText(Preference::toString(disc));
    ui->labelFinal->setText(Preference::toString(ui->doublePrice->value() - disc));
}

void EditPriceCountDialog::saveClicked()
{
    mIsOk = true;
    close();
}
