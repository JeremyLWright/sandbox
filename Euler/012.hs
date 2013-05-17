import Data.List 

primeFactors n = factor n primes
    where
        factor n (p:ps)
            | p*p > n           = [n]
            | n `mod` p == 0    = p: factor (n `div` p) (p:ps)
            | otherwise         = factor n ps

primes = 2 : filter ((==1) . length . primeFactors) [3,5..]

divisors f = sort $ nub $ concat [(primeFactors f), (map product (tails $ primeFactors f))]

triangleNumbers = map sum $ inits [1..]

--take 1 filter (==500) (map length (map divisors triangleNumbers))
nDivisors n = product $ map ((+1). length) (group (primeFactors n))

main = print (head $ filter ((>500) . nDivisors) triangleNumbers)
--factorLength f = filter (==f) (map length (map divisors



