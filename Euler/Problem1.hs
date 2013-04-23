main :: IO()

main = print (sum [ x | x <- [0..2000-1], rem x 3 == 0 || rem x 5 == 0]) 
