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