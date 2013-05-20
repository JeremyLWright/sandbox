import Control.Arrow
import Data.Array

input :: String -> Array (Int, Int) Int
input = listArray ((1,1), (4,4)) . map read . words

senses = [(+1) *** id,(+1) *** (+1), id *** (+1), (+1) *** (\n -> n - 1)]
 
inArray a i = inRange (bounds a) i
 
prods :: Array (Int, Int) Int -> [Int]
prods a = [product xs | i <- range $ bounds a,
                        s <- senses,
                        let is = take 4 $ iterate s i,
                        all (inArray a) is,
                        let xs = map (a!) is]
main = print . maximum . prods . input =<< getContents

