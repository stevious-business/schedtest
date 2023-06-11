clear
make all_tests | grep -i "running\|<<<"
for i in build/tests/*;
do
    valgrind --leak-check=yes $i 2>&1 | grep -i "error summary\|in use";
done
