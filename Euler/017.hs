--
--fstOrder = [('1', "one")
--    , ('2',"two")
--    , ('3', "three")
--    , ('4', "four")
--    , ('5', "five")
--    , ('6', "six")
--    , ('7', "seven")
--    , ('8', "eight")
--    , ('9', "nine")]
--sndOrder = [("10", "ten")
--    , ("11", "eleven")
--    , ("12", "twelve")
--    , ("13", "thirteen")
--    , ("14", "fourteen")
--    , ("15", "fifteen")
--    , ("16", "sixteen")
--    , ("17", "seventeen")
--    , ("18", "eighteen")
--    , ("19", "nineteen")]
----sndOrder = [("2", "twenty")
----    , ("3", "thirty")
----    , ("4", "fourty")
----    , ("5", "fifty")
----    , ("6", "sixty")
----    , ("7", "seventy")
----    , ("8", "eighty")
----    , ("9", "ninty")]
--thrdOrder = [("1", "hundred")]
--fourthOrder = [("1", "thousand")]
--
--
--
--englishify (x:xs)   | length xs == 3 = case lookup x fstOrder of
--                                        Just c -> c ++ " thousand " ++ englishify xs
--                                        Nothing -> []
--                    | length xs == 2 = case lookup xs sndOrder of
--                                        Just c -> c 
--                                        Nothing -> case lookup x fstOrder of
--                                                    Just c -> c ++ " hundred and " ++ englishify xs
--                                                    Nothing -> []
--                    | length xs == 1 = case lookup x fstOrder of
--                                        Just c -> c ++ englishify xs
--                                        Nothing -> []
--                    | length xs == 0 = []
--                    | otherwise = []
----                    | length xs == 2 = case lookup xs fstOrder of
--                                        Just c -> c
--                                        Nothing -> case lookup x fstOrder of 
--                                        case lookup x fstOrder of 
--                                                   Just c -> c ++ " hundred " ++ englishify xs
--                                                   Nothing -> []
--                    | length xs == 1 = case lookup x sndOrder of
--                                        Just c -> c ++ " " ++ englishify xs
--                                        Nothing -> []
--                    | length xs == 0 = case lookup x fstOrder of 
--                                        Just c -> c
--                                        Nothing -> []
--


--                | otherwise = ""


import Data.Char
 
one = ["one","two","three","four","five","six","seven","eight",
     "nine","ten","eleven","twelve","thirteen","fourteen","fifteen",
     "sixteen","seventeen","eighteen", "nineteen"]
ty = ["twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"]
 
decompose x 
    | x == 0                       = []
    | x < 20                       = one !! (x-1)
    | x >= 20 && x < 100           = 
        ty !! (firstDigit (x) - 2) ++ decompose ( x - firstDigit (x) * 10)
    | x < 1000 && x `mod` 100 ==0  = 
        one !! (firstDigit (x)-1) ++ "hundred"
    | x > 100 && x <= 999          = 
        one !! (firstDigit (x)-1) ++ "hundredand" ++decompose ( x - firstDigit (x) * 100)
    | x == 1000                    = "onethousand"
 
  where firstDigit x = digitToInt . head . show $ x
 
problem_17 = length . concatMap decompose $ [1..1000]

