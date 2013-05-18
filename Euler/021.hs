amicable_pair n | n == d n = False
                | n == (d . d) n = True
                | otherwise = False

d n = sum $ divides n

divides m = filter some [m `div` 2, ((m `div` 2)-1)..1]
    where some n | m `mod` n == 0   = True
                 | otherwise        = False 

main = print (sum $ filter amicable_pair [1..10000])
          

