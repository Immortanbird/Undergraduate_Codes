module Main where
import Control.Monad.Writer


merge [] xs = xs
merge xs [] = xs
merge (x:xs) (y:ys)
  | x<=y = x:merge xs (y:ys)
  | otherwise = y:merge (x:xs) ys


mergesort :: Int -> [Int] -> Writer String [Int]
mergesort l [] = do
  return []


mergesort l s@[x] = do
  return [x]


mergesort l s@xs = do
  let (a1,a2) = splitAt (length s `div` 2) xs
  curMergeResult <- liftM2 merge (mergesort (l+2) a1) (mergesort (l+2) a2)
  return curMergeResult
  


main :: IO ()
main = do
  let res = runWriter $ mergesort 0 [5,4,3,10,9,101,2,1]
  putStrLn $show $ fst $res
  putStrLn $ snd $ res