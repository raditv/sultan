CREATE TABLE itemlinks (
    `id` INTEGER PRIMARY KEY,
    `type` INT NOT NULL DEFAULT 0,
    `barcode` VARCHAR(128) NOT NULL DEFAULT '',
    `barcode_link` VARCHAR(128) NOT NULL DEFAULT '',
    `count_link` FLOAT NOT NULL DEFAULT '0'
);
-- separator
CREATE INDEX ITEMLINKBARCODE ON itemstocklinks (barcode);
-- separator
CREATE INDEX ITEMLINKBARCODELINK ON itemstocklinks (barcode_link);
