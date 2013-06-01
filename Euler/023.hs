import Euler.NumberTheory
import qualified Data.List as L
import qualified Data.Set as Set

isAbundant n = (sum $ divisors n) > n
abundantNumbers = filter isAbundant [1..]

abundantSums limit = L.nub $ [x + y | x <- takeWhile (<limit) abundantNumbers, y <- takeWhile (<limit) abundantNumbers]

nonAbundantSums = Set.toList $ (Set.fromList [1..28123]) Set.\\ (Set.fromList $ abundantSums 28123)

main = print $ sum nonAbundantSums
