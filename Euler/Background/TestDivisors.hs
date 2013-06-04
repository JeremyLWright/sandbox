import Euler.NumberTheory

factorize n = go n (2:[3,5..])    -- or:  (go n primes)  where
   where                          --  primes = 2 :
     go n ds@(d:t)                --   filter (null.tail.factorize) [3,5..]
        | d*d > n    = [n]
        | r == 0     =  d : go q ds
        | otherwise  =      go n t
            where  (q,r) = quotRem n d


main = print $ factorize 24
