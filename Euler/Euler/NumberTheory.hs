module Euler.NumberTheory ( divisors, primeFactors, primes, properdivisors) where

primeFactors n = factor n primes
    where
        factor n (p:ps)
            | p*p > n           = [n]
            | n `mod` p == 0    = p: factor (n `div` p) (p:ps)
            | otherwise         = factor n ps

primes = 2 : filter ((==1) . length . primeFactors) [3,5..]

divisors n = [x | x <- [1..(n-1)], n `rem` x == 0]
--main = print $ divisors 100000000
--real	0m2.599s
--user	0m2.568s
--sys	0m0.024s
properdivisors n = 1 : [x*y | x <- primeFactors n, y <- primeFactors n]
--filter ((==0) . rem n) [2 .. n `div` 2]

divides m = filter some [m `div` 2, ((m `div` 2)-1)..1]
    where some n | m `mod` n == 0   = True
                 | otherwise        = False 



