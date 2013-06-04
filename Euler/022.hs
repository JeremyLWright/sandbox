--Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

--For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 x 53 = 49714.

--What is the total of all the name scores in the file?

import Data.List.Split
import Data.List

names n = sort $ map (filter (/='"')) (splitOn "," n)

letterValues = makeValues ('A', 1)
                where   makeValues ('Z', n) = ('Z', n) : []
                        makeValues (l, n) = (l, n) : makeValues ((succ l), (succ n))


filterJusts [] = []
filterJusts (x:xs) = case x of
                        Just x -> x : filterJusts xs
                        Nothing -> 0 : filterJusts xs

wordValue w = sum .filterJusts . justValues $ w
            where justValues w = map (\c -> lookup c letterValues) w

nameIndex n ns = case elemIndex n ns of
                        Just x -> fromIntegral x + 1
                        Nothing -> 1

--test case: nameScore "COLIN" s -> 49714
nameScore ns n = (nameIndex n (nameList)) * (wordValue n)
                where nameList = names ns

main = do 
        s <- readFile "Data/022.txt"
        let n = nameScore s
        print $ sum $ map n $ names s













