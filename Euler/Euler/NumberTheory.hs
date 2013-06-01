module Euler.NumberTheory ( divisors, divides ) where
divisorsslow n = 1:[x | x <- [2..(n `div` 2)], n `rem` x == 0]


--main = print $ divisors 100000000
--real	0m2.599s
--user	0m2.568s
--sys	0m0.024s
divisors n = 1 : filter ((==0) . rem n) [2 .. n `div` 2]

divides m = filter some [m `div` 2, ((m `div` 2)-1)..1]
    where some n | m `mod` n == 0   = True
                 | otherwise        = False 



