
divide2 :: Integral a => a -> a
divide2 x = x `div` 2

square_term x p | (divide2 x) `mod` p == 0 = True -- is can x be a square term of p
                | otherwise      = False
                where second_term = divide2 x 

