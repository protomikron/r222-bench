import Data.Map as M
import Data.List as L
import Data.ByteString.Char8 as B

type Config = B.ByteString
type Op = Int

solved :: Config
solved = pack "RRRRYYYYBBBBOOOOWWWWGGGG"

ops = [[1,3,0,2,21,20,6,7,4,5,10,11,12,13,14,15,9,8,18,19,16,17,22,23],
       [0,1,8,10,5,7,4,6,15,9,14,11,12,13,20,22,16,17,18,19,3,21,2,23],
       [0,19,2,17,4,1,6,3,9,11,8,10,12,7,14,5,16,13,18,15,20,21,22,23]]

move :: Config -> Op -> Config
move cfg = pack . L.map (index cfg) . (ops!!) -- <- seems to be slow offender?

succs :: Config -> [Op] -> Map Config [Op]
succs cfg ops = M.fromList $ L.map (\op -> (move cfg op, op:ops)) [0,1,2]

updateDB :: Map Config [Op] -> Map Config [Op] -> Map Config [Op]
updateDB sofar new
  | M.null new = sofar
  | otherwise  = updateDB sofar' investigate
  where new' = M.foldr M.union M.empty $ M.mapWithKey succs new
        investigate = new' M.\\ sofar
        sofar' = M.union sofar investigate

makeDB :: Map Config [Op]
makeDB = updateDB initMap initMap
  where initMap = M.singleton solved []

main :: IO ()
main = Prelude.putStr $ L.unlines $ L.map prettyLine $ toList makeDB
  where prettyLine (cfg, ops) = (unpack cfg) ++ ": '" ++ (L.concat $ L.map show ops) ++ "'"

