ALTER TABLE items DROP COLUMN `barcode_link`;
-- separator
ALTER TABLE items DROP COLUMN `count_link`;
-- separator
CREATE TABLE itemstocklinks (
    `id` INTEGER PRIMARY KEY,
    `type` INT NOT NULL DEFAULT 0,
    `barcode` VARCHAR(128) NOT NULL DEFAULT '',
    `barcode_link` VARCHAR(128) NOT NULL DEFAULT '',
    `count_link` FLOAT NOT NULL DEFAULT '0'
);
-- separator
CREATE INDEX ITEMSTOCKLINKBARCODE ON itemstocklinks (barcode);
-- separator
CREATE INDEX ITEMSTOCKLINKBARCODELINK ON itemstocklinks (barcode_link);
