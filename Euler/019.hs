problem_19 =  length . filter (== sunday) . drop 12 . take 1212 $ since1900
since1900 = scanl nextMonth monday . concat $
              replicate 4 nonLeap ++ cycle (leap : replicate 3 nonLeap)
 
nonLeap = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
 
leap = 31 : 29 : drop 2 nonLeap
 
nextMonth x y = (x + y) `mod` 7
 
sunday = 0
monday = 1

main = print problem_19
