import Data.Char (digitToInt)
import Data.List (tails)
 
problem_8 = do str <- readFile "008.txt"
               let number = map digitToInt (concat $ lines str) --take the 
               print $ maximum $ map (product . take 5) (tails number)

