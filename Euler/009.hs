--A Pythagorean triplet is a set of three natural numbers, a  b  c, for which,

--a^2 + b^2 = c^2
--For example, 32 + 42 = 9 + 16 = 25 = 52.

--There exists exactly one Pythagorean triplet for which a + b + c = 1000.
--Find the product abc.
--Answer: 31875000


triplets l = [[a,b,c] | m <- [2..limit],
                        n <- [1..(m-1)], 
                        let a = m^2 - n^2, 
                        let b = 2*m*n, 
                        let c = m^2 + n^2,
                        a+b+c==l]
    where limit = floor . sqrt . fromIntegral $ l
 
problem_9 = product . head . triplets $ 1000

main = print problem_9

