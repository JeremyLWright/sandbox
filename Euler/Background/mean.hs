import Data.List
mean (x:xs) = realToFrac (x) / genericLength xs + mean xs

main = print (mean [1..10^7])
