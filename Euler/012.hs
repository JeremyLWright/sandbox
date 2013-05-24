import Data.List 
import Euler.Prime

divisors f = sort $ nub $ concat [(primeFactors f), (map product (tails $ primeFactors f))]

triangleNumbers = map sum $ inits [1..]

--take 1 filter (==500) (map length (map divisors triangleNumbers))
nDivisors n = product $ map ((+1). length) (group (primeFactors n))

main = print (head $ filter ((>500) . nDivisors) triangleNumbers)
--factorLength f = filter (==f) (map length (map divisors



