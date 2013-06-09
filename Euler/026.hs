import Data.List
import Data.Ord
import Euler.NumberTheory

grouper :: Ord a => [a] -> [(a, Int)] 
grouper = map (\xs@(x:_) -> (x, length xs)) . group . sort

carmichael (p,a) | p == 2 && a > 2 = 2^(a-2)
                 | otherwise        = p^(a-1)*(p-1)
--http://math-it.org/Mathematik/Zahlentheorie/Carmichael.html
--https://en.wikipedia.org/wiki/Repeating_decimal
--https://en.wikipedia.org/wiki/Carmichael_function
--n	        1	2	3	4	5	6	7	8	9	10	11	12	13	14	15
--lambda(n)	1	1	2	2	4	2	6	2	6	 4	10	 2	12	 6	 4
carmichael2 n = foldr1 lcm $ map carmichael $ grouper $ primeFactors n

remainders d 0 rs = 0
remainders d r rs = let r' = r `mod` d
                    in case elemIndex r' rs of
                        Just i -> i + 1
                        Nothing -> remainders d (10*r') (r':rs)

recurringCycle d = remainders d 10 []

problem_26 = fst $ maximumBy (comparing snd) [(n , recurringCycle n) | n <- takeWhile (<1000) primes]

main = print problem_26
