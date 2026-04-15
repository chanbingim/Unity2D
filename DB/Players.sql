DROP TABLE player;

CREATE TABLE IF NOT EXISTS player (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(30) NOT NULL,
    level INT DEFAULT 1
);

INSERT INTO player(name, level) VALUES("Alice", 1);
INSERT INTO player(name, level) VALUES("Tom", 1);
INSERT INTO player(name, level) VALUES("Bob", 1);

SELECT * FROM player;