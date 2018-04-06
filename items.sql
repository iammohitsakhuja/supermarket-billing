CREATE TABLE items (
    item_id INT PRIMARY KEY NOT NULL,
    item_name TEXT NOT NULL,
    price REAL NOT NULL CHECK (price >= 0),
    quantity INT NOT NULL CHECK (quantity >= 0)
);
INSERT INTO
    items (item_id, item_name, price, quantity)
VALUES
    (1, 'Juice', 25.00, 200),
    (2, 'Beer', 120.00, 50),
    (3, 'Milk', 27.00, 35),
    (4, 'Tea', 155.00, 20),
    (5, 'Water bottle', 20.00, 45),
    (6, 'Ketchup', 270.00, 15),
    (7, 'Bread', 15.00, 20),
    (8, 'Flour', 85.00, 15),
    (9, 'Honey', 92.00, 14),
    (10, 'Olive oil', 250.00, 22),
    (11, 'Pasta', 65.00, 15),
    (12, 'Rice', 133.00, 28),
    (13, 'Fish', 540.00, 23),
    (14, 'Ice cream', 120.00, 25),
    (15, 'Paper towles', 75.00, 10),
    (16, 'Lemons', 80.00, 120),
    (17, 'Cheese', 95.00, 15),
    (18, 'Eggs', 5.00, 150),
    (19, 'Yogurt', 28.00, 12),
    (20, 'Chips', 27.00, 30);
SELECT
    *
FROM
    items;