Create Database Item_DB;
use Item_DB;

CREATE TABLE Item
(
    ItemID INT NOT NULL PRIMARY KEY,
    ItemName VARCHAR(50) NOT NULL,
    ItemType INT NOT NULL,
    ItemMaxCount INT NOT NULL
);

INSERT INTO Item (ItemID, ItemName, ItemType, ItemMaxCount) VALUES
(1001, 'Potion',      1, 99),
(1002, 'HiPotion',    1, 99),
(2001, 'IronSword',   2, 1),
(2002, 'SteelShield', 3, 1),
(3001, 'MagicScroll', 4, 20);

select* From Item;