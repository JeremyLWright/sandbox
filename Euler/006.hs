sumSquares a = sum [1..a] ^ 2

squareSums a = sum (map (^2) [1..a])

main :: IO()
main = print (sumSquares 100 - squareSums 100) 
