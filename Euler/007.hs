--By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

--What is the 10 001st prime number?
minus (x:xs) (y:ys) = case (compare x y) of 
           LT -> x : minus  xs  (y:ys)
           EQ ->     minus  xs     ys 
           GT ->     minus (x:xs)  ys
minus  xs     _     = xs

eratos [] = []
eratos (p:xs) = p : eratos (xs `minus` [p, p+2*p..])

--primesTo m = 2 : eratos [3,5..m]  where
--   eratos []     = []
--   eratos (p:xs) = p : eratos (xs `minus` [p, p+2*p..m])

