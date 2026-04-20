-- 1. 계정 테이블 (로그인 담당)
drop table player_inventory;
drop table player_info;
drop table users;

CREATE TABLE users (
    id          INT PRIMARY KEY AUTO_INCREMENT,
    user_id     VARCHAR(30) NOT NULL UNIQUE,  -- 아이디
    password    VARCHAR(256) NOT NULL,         -- 암호화 저장!
    email       VARCHAR(100) UNIQUE,
    created_at  DATETIME DEFAULT NOW(),        -- 가입일
    last_login  DATETIME,                      -- 마지막 로그인
    is_banned   TINYINT DEFAULT 0              -- 밴 여부
);

-- 2. 인게임 캐릭터 테이블
CREATE TABLE player_info (
    id          INT PRIMARY KEY AUTO_INCREMENT,
    user_id     INT NOT NULL UNIQUE,           -- users.id 참조
    nickname    VARCHAR(30) NOT NULL,
    level       INT DEFAULT 1,
    exp         INT DEFAULT 0,
    hp          INT DEFAULT 100,
    mp          INT DEFAULT 50,
    gold        INT DEFAULT 0,
    map_id      INT DEFAULT 1,                 -- 현재 위치
    pos_x       FLOAT DEFAULT 0,
    pos_y       FLOAT DEFAULT 0,
    pos_z       FLOAT DEFAULT 0,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

-- 3. 인벤토리 테이블
CREATE TABLE player_inventory (
    id          INT PRIMARY KEY AUTO_INCREMENT,
    player_id   INT NOT NULL,                  -- player_info.id 참조
    item_id     INT NOT NULL,                  -- 아이템 종류
    quantity    INT DEFAULT 1,
    slot        INT,                           -- 인벤토리 슬롯 번호
    FOREIGN KEY (player_id) REFERENCES player_info(id)
);

INSERT INTO users(user_id, password, email) VALUES
("Alice123",  "hashed_pw_1", "alice@gmail.com"),
("Tom456",    "hashed_pw_2", "tom@gmail.com"),
("Bob789",    "hashed_pw_3", "bob@gmail.com"),
("Jenny007",  "hashed_pw_4", "jenny@gmail.com"),
("Chris999",  "hashed_pw_5", "chris@gmail.com");

-- 인게임 캐릭터 테이블
INSERT INTO player_info(user_id, nickname, level, exp, hp, mp, gold, map_id, pos_x, pos_y, pos_z) VALUES
(1, "AliceKnight",  15, 3200, 180, 90,  5000,  1,  10.5,  0.0,  22.3),
(2, "TomMage",       8, 1500, 100, 200, 2300,  2,  -5.2,  0.0,  11.0),
(3, "BobArcher",    23, 8700, 150, 70,  12000, 1,  33.1,  0.0,  -8.5),
(4, "JennyHealer",   5, 800,  120, 180, 900,   3,   0.0,  0.0,   0.0),
(5, "ChrisWarrior", 31, 15000,220, 50,  30000, 2,  -20.0, 0.0,  45.7);

