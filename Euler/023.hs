import Euler.NumberTheory
import qualified Data.List as L
import Data.IntSet (toList, fromList)

--data AbundantSums = Perfect | Abundant | Deficient
--    deriving (Show, Eq, Ord)
--
--abundant n  | ((sum . divisors) n) == n = Perfect
--            | ((sum . divisors) n) < n  = Deficient
--            | ((sum . divisors) n) > n  = Abundant
--
--abundantNums = [x | x <- [1..], abundant x == Abundant]
--

--According to oeis.org/A048242, a(1456) - 20161 is the final term
sequence_A048243_Limit = 20161

isAbundant n = (sum $ properdivisors n) > n
abundants = filter isAbundant [1..sequence_A048243_Limit]

abundantSums = sum $ nub' $ [x + y | x <- abundants, y <- abundants, (x+y) < sequence_A048243_Limit]
                    where
                        nub' = toList . fromList

nonAbundantSums = (sum [1..sequence_A048243_Limit]) - abundantSums 

main = print $ nonAbundantSums
