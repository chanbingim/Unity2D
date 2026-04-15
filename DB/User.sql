drop table users;
drop table player;
CREATE TABLE IF NOT EXISTS player (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(30) NOT NULL,
    level INT DEFAULT 1
);

INSERT INTO player(name, level) VALUES("Alice", 1);
INSERT INTO player(name, level) VALUES("Tom", 1);
INSERT INTO player(name, level) VALUES("Bob", 1);


CREATE TABLE IF NOT EXISTS users (
    Number INT PRIMARY KEY AUTO_INCREMENT,
    User_ID VARCHAR(30) NOT null unique,
    Password VARCHAR(30) NOT NULL,
    Table_id INT,
	FOREIGN KEY (Table_id) REFERENCES player(id)
);

INSERT INTO Users(User_ID, Password, Table_id) VALUES("A", "1234", 1);
INSERT INTO Users(User_ID, Password, Table_id) VALUES("AB", "1234", 2);
INSERT INTO Users(User_ID, Password, Table_id) VALUES("ABC", "1234", 3);



SELECT * FROM Users;
SELECT * FROM player;