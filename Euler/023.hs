
import Euler.Prime

data AbundantSums = Perfect | Abundant | Deficient
    deriving (Show, Eq, Ord)

abundant n  | ((sum . divisors) n) == n = Perfect
            | ((sum . divisors) n) < n  = Deficient
            | ((sum . divisors) n) > n  = Abundant

abundantNums = [x | x <- [1..], abundant x == Abundant]
