
--Starting in the top left corner of a 2 by 2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
-- How many such routes are there through a 2020 grid?
-- Answer: 137846528820

main = print $ (product [21..40] `div` product [2..20])
