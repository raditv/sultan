#include "itemutil.h"
#include "global_constant.h"
#include "db.h"
#include "queryhelper.h"
#include "util.h"
#include <QStringRef>
#include <QStringBuilder>
#include <QDataStream>
#include <QDebug>

using namespace LibServer;
using namespace LibG;
using namespace LibDB;

ItemUtil::ItemUtil(Db *db):
    mDb(db)
{

}

void ItemUtil::updateBuyPrice(const QString &barcode)
{
    if(mBarcodeChecked.contains(barcode)) return;
    mBarcodeChecked << barcode;
    DbResult res = mDb->where("barcode_link = ", barcode)->where("type = ", ITEM_LINK_TYPE::BOX)->
            get("itemlinks");
    if(!res.isEmpty()) {
        DbResult resItem = mDb->where("barcode = ", barcode)->get("items");
        if(resItem.isEmpty()) return;
        const QVariantMap &item = resItem.first();
        for(int i = 0; i < res.size(); i++) {
            const QVariantMap &v = res.data(i);
            const QString &b = v["barcode"].toString();
            double p = item["buy_price"].toDouble() * v["count_link"].toFloat();
            mDb->where("barcode = ", b)->update("items", QVariantMap{{"buy_price", p}});
            updateBuyPrice(barcode);
        }
    }
}
