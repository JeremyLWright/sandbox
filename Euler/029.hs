import Data.List

nums = [a^b | a <- [2..100], b <- [2..100]]

main = print (length . nub $ nums)

