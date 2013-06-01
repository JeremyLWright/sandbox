import Euler.NumberTheory

amicable_pair n | n == d n = False
                | n == (d . d) n = True
                | otherwise = False

d n = sum $ divisors n

main = print (sum $ filter amicable_pair [1..10000])
          

