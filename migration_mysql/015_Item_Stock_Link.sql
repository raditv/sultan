ALTER TABLE items DROP COLUMN `barcode_link`;
ALTER TABLE items DROP COLUMN `count_link`;
-- type will be : 0: box, 1 : ingridient
CREATE TABLE itemstocklinks (
    `id` INT NOT NULL AUTO_INCREMENT,
    `type` INT NOT NULL DEFAULT 0,
    `barcode` VARCHAR(128) NOT NULL DEFAULT '',
    `barcode_link` VARCHAR(128) NOT NULL DEFAULT '',
    `count_link` FLOAT NOT NULL DEFAULT '0'
    INDEX `BARCODE` (`barcode` ASC),
    INDEX `BARCODELINK` (`barcode_link` ASC),
    PRIMARY KEY (`id`)
) ENGINE = InnoDB;
