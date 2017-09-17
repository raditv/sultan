#include "stockcardwidget.h"
#include "ui_normalwidget.h"
#include "tablewidget.h"
#include "tablemodel.h"
#include "tableview.h"
#include "headerwidget.h"
#include "global_constant.h"
#include "db_constant.h"
#include "guiutil.h"

using namespace LibGUI;
using namespace LibG;

StockCardWidget::StockCardWidget(LibG::MessageBus *bus, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalWidget),
    mTableWidget(new TableWidget(this))
{
    ui->setupUi(this);
    setMessageBus(bus);
    ui->verticalLayout->addWidget(mTableWidget);
    mTableWidget->initButton(QList<TableWidget::ButtonType>() << TableWidget::Refresh);
    ui->labelTitle->setText(tr("Item sales"));
    auto model = mTableWidget->getModel();
    model->setMessageBus(bus);
    model->addColumn("barcode", tr("Barcode"));
    model->addColumn("name", tr("Name"));
    model->addColumnMoney("stock", tr("Stock"));
    model->addColumnMoney("count", tr("Sold"));
    model->addColumn("unit", tr("Unit"));
    model->addColumn("category", tr("Category"));
    model->addColumn("suplier", tr("Suplier"));
    model->addHeaderFilter("barcode", HeaderFilter{HeaderWidget::LineEdit, TableModel::FilterLike, QVariant()});
    model->addHeaderFilter("name", HeaderFilter{HeaderWidget::LineEdit, TableModel::FilterLike, QVariant()});
    model->setTypeCommand(MSG_TYPE::SOLD_ITEM, MSG_COMMAND::SOLD_ITEM_REPORT);
    model->setTypeCommandOne(MSG_TYPE::SOLD_ITEM, MSG_COMMAND::GET);
    mTableWidget->setupTable();
    GuiUtil::setColumnWidth(mTableWidget->getTableView(), QList<int>() << 150 << 150 << 100 << 100 << 100 << 150 << 150);
    mTableWidget->getTableView()->horizontalHeader()->setStretchLastSection(true);
    model->refresh();
}

StockCardWidget::~StockCardWidget()
{
    delete ui;
}

void StockCardWidget::messageReceived(LibG::Message */*msg*/)
{

}
