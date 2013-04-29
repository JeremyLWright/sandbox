fizzbuzz x  | x `mod` 15 == 0   = "FIZZBUZZ"
            | x `mod` 3 == 0    = "FIZZ"
            | x `mod` 5 == 0    = "BUZZ"
            | otherwise         = show x

main = print (map fizzbuzz [1..100])

