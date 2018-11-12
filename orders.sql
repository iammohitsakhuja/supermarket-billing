CREATE TABLE orders (
    order_id INT NOT NULL,
    customer_name TEXT NOT NULL,
    item_id INT NOT NULL,
    item_qty INT NOT NULL CHECK (item_qty > 0),
    PRIMARY KEY (order_id, item_id),
    FOREIGN KEY (item_id) REFERENCES items (item_id)
);
INSERT INTO
    orders
VALUES
    (1, "Chandragupta", 5, 3),
    (1, "Chandragupta", 12, 1),
    (1, "Chandragupta", 18, 12),
    (2, "Alexander", 3, 5),
    (2, "Alexander", 7, 2),
    (2, "Alexander", 9, 8),
    (2, "Alexander", 19, 6);
SELECT
    *
FROM
    orders;