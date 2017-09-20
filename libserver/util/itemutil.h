#ifndef ITEMUTIL_H
#define ITEMUTIL_H

#include <QStringList>

namespace LibDB {
class Db;
}

namespace LibServer {

class ItemUtil
{
public:
    ItemUtil(LibDB::Db *db);
    void updateBuyPrice(const QString &barcode);

private:
    LibDB::Db *mDb;
    QStringList mBarcodeChecked;
};

}

#endif // ITEMUTIL_H
