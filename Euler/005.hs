
--2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
--What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

evendiv :: Integral a => a -> a -> Bool
evendiv x y = if x `mod` y == 0 then True else False

factors x = [x-1, x-2..2]


evendown 1 _ = True
evendown n m = if evendiv m n then evendown (n - 1) m else False


euler5 h = if evendown 20 h then h else 0

--This works, but it doesn't tell me the number
--take 1 (filter (==True) (map evedown10 [2521..]))
