make fclean
make -j5
echo "\nONLY DUMP WITHOUT NUMBER"
./corewar -dump

echo "\nONLY DUMP"
./corewar -dump

echo "\nONLY WDHT W/O NUMBER"
./corewar -w

echo "\nONLY WIDTH"
./corewar -w 10

echo "\nONLY DUMP WITH ZERO"
./corewar -dump 0

echo "\nTEST_DUMP"
./corewar ./src/champs/ex.cor -dump 00001  ./src/champs/ex.cor

echo "\nTEST_DUMP1"
./corewar ./src/champs/ex.cor -dump -1  ./src/champs/ex.cor

echo "\nTEST_DUMP1"
./corewar ./src/champs/ex.cor -dump 2147483647  ./src/champs/ex.cor

echo "\nTEST_DUMP2"
./corewar ./src/champs/ex.cor -dump 2147483648  ./src/champs/ex.cor

echo "\nTEST_DUMP3"
./corewar ./src/champs/ex.cor -dump -2147483648  ./src/champs/ex.cor

echo "\nTEST_DUMP4"
./corewar ./src/champs/ex.cor -dump -2147483649  ./src/champs/ex.cor

echo "\nTEST_DUMP5"
./corewar ./src/champs/ex.cor -dump  ./src/champs/ex.cor

echo "\nTEST_DUMP6"
./corewar ./src/champs/ex.cor -dump -w   ./src/champs/ex.cor

echo "\nTEST_DUMP7"
./corewar ./src/champs/ex.cor -dump 21 -w 0  ./src/champs/ex.cor

echo "\nTEST_DUMP8"
./corewar ./src/champs/ex.cor -dump 21 -w b  ./src/champs/ex.cor

echo "\nTEST_NUM1"
./corewar ./src/champs/ex.cor -dump 21 -w 8 -n 0  ./src/champs/ex.cor

echo "\nTEST_NUM2"
./corewar ./src/champs/ex.cor -dump 21 -w 8 -n -2147483648  ./src/champs/ex.cor

echo "\nTEST_NUM3"
./corewar ./src/champs/ex.cor -dump 21 -w 8 -n 2147483648  ./src/champs/ex.cor

echo "\nTEST_NUM4"
./corewar ./src/champs/ex.cor -dump 21 -w 8 -n 2147483647  ./src/champs/ex.cor

echo "\nTEST_NUM5"
./corewar ./src/champs/ex.cor -dump 21 -w 8 -n 333  ./src/champs/ex.cor

echo "\nTEST_ORDER"
./corewar ./src/champs/ex.cor -w 8 -n 2  ./src/champs/ex.cor -dump 2

echo "\nTEST_ORDER1"
./corewar ./src/champs/ex.cor -dump 21 -n 48  ./src/champs/ex.cor /src/champs/ex.cor -w 8

echo "\nTEST_ORDER3"
./corewar ./src/champs/ex.cor -w 8 -n 2  ./src/champs/ex.cor -dump 2

echo "\nTEST_ORDER4"
./corewar ./src/champs/ex.cor -w 8 -n 2  ./src/champs/ex.cor -dump 2

echo "\nTEST_CNT ARG"
./corewar ./src/champs/ex.cor -w 8 -n 2 ./src/champs/ex.cor ./src/champs/ex.cor ./src/champs/ex.cor  ./src/champs/ex.cor -dump 2 

echo "\nTEST_CNT ARG"
./corewar ./src/champs/ex.cor -w 8 -n 2 ./src/champs/ex.cor ./src/champs/ex.cor ./src/champs/ex.cor  ./src/champs/ex.cor -dump 2

echo "\nTEST_CNT ARG1"
./corewar ./src/champs/ex.cor -w 8 -n 2 ./src/champs/ex.cor ./src/champs/ex.cor ./src/champs/ex.cor  ./src/champs/ex.cor -dump 2 -w 12

echo "\nTEST_CNT ARG2"
./corewar ./src/champs/ex.cor -w 8 -n 2 ./src/champs/ex.cor  -dump 2 22 -w

echo "\nTEST_CNT ARG3"
./corewar -v

echo "\nTEST_CNT ARG4"
./corewar -dump 7

echo "\nTEST_CNT ARG5"
./corewar -n 2

# echo ""
# ./corewar -

# echo ""
# ./corewar -

# echo ""
# ./corewar -

# echo ""
# ./corewar -

# echo ""
# ./corewar -

# echo ""
# ./corewar -