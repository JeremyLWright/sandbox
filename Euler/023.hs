import Euler.NumberTheory
import qualified Data.List as L

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
abundantNumbers = filter isAbundant [1..]

abundantSums limit = L.nub $ [x + y | x <- abundantMemo, y <- abundantMemo]
                    where
                        abundantMemo = takeWhile (<limit) abundantNumbers

nonAbundantSums = [1..sequence_A048243_Limit] L.\\ abundantSums sequence_A048243_Limit

main = print $ sum nonAbundantSums
