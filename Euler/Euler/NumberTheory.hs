module Euler.NumberTheory ( primeFactors, primes, properdivisors) where
import qualified Data.List as L

sigma n =  [x | x <- [0..n], (gcd x n) == 1]
phi n = eulerTotient n
eulerTotient n = length $ sigma n

--A number n for which the sum of divisors rho(n)>2n (http://en.wikipedia.org/wiki/Abundant_number)
isAbundant n = (sum (sigma n)) > 2*n

primeFactors n = factor n primes
    where
        factor n (p:ps)
            | p*p > n           = [n]
            | n `mod` p == 0    = p: factor (n `div` p) (p:ps)
            | otherwise         = factor n ps

primesSlow = 2 : filter ((==1) . length . primeFactors) [3,5..]

--Taken from paper: http://www.cs.hmc.edu/~oneill/papers/Sieve-JFP.pdf
primes = 2:([3..] `minus` composites)
    where
        composites = union [multiples p | p <- primes]
        multiples n = map (n*) [n..] 
        (x:xs) `minus` (y:ys) | x < y = x:(xs `minus` (y:ys))
                                | x == y = xs `minus` ys
                                | x > y = (x:xs) `minus` ys

union = foldr merge []
    where
        merge (x:xs) ys = x:merge' xs ys
        merge' (x:xs) (y:ys) | x < y = x:merge' xs (y:ys)
                             | x == y = x:merge' xs ys
                             | x > y = y:merge' (x:xs) ys
-- End of primes function


properdivisors m = filter some [1..m `div` 2]
    where some n | m `mod` n == 0   = True
                 | otherwise        = False 



