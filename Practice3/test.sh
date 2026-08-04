#!/bin/bash
set -e

echo "=== Building copy ==="
gcc -Wall -Wextra copy.c -o copy

echo ""
echo "=== Creating test files ==="
mkdir -p test_dir
cd test_dir

echo "Hello, this is a test file." > file1.txt
echo -n "" > empty.txt
dd if=/dev/urandom of=big.bin bs=1024 count=200 2>/dev/null

echo ""
echo "=== Test 1: normal copy (unnamed pipe) ==="
../copy file1.txt empty.txt big.bin

diff file1.txt file1.txt.copy && echo "file1.txt.copy  OK" || echo "file1.txt.copy  FAIL"
diff empty.txt empty.txt.copy     && echo "empty.txt.copy  OK" || echo "empty.txt.copy  FAIL"
diff big.bin big.bin.copy         && echo "big.bin.copy    OK" || echo "big.bin.copy    FAIL"

echo ""
echo "=== Test 2: nonexistent file ==="
../copy nonexistent.txt 2>/dev/null || true
if [ ! -f nonexistent.txt.copy ]; then
    echo "nonexistent.txt.copy  OK (not created)"
else
    echo "nonexistent.txt.copy  FAIL"
fi

echo ""
echo "=== Test 3: FIFO mode (-p) ==="
rm -f myfifo
../copy -p myfifo file1.txt

diff file1.txt file1.txt.copy && echo "FIFO file1.txt.copy  OK" || echo "FIFO file1.txt.copy  FAIL"

cd ..
echo ""
echo "=== Cleaning up ==="
rm -rf test_dir copy

echo ""
echo "All tests finished."
