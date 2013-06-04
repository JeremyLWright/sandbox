
--2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
--What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

evendiv :: Integral a => a -> a -> Bool
evendiv x y 
    | x `mod` y == 0 = True
    | otherwise = False

factors x = [x-1, x-2..2]


evendown 1 _ = True
evendown n m 
    | evendiv m n = evendown (n - 1) m
    | otherwise = False



euler5 h = if evendown 20 h then h else 0

main = print $ foldr1 lcm [1..20]
--This works, but it doesn't tell me the number
--take 1 (filter (==True) (map evedown10 [2521..]))
