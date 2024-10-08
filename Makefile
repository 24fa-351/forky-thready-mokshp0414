# Makefile for compiling the process_forking program

forky: process_forking.c
    gcc -o forky process_forking.c

results: forky
    (echo "Pattern 1:" 1>&2; ./forky 7 1; \
    echo 1>&2; \
    echo "Pattern 2:" 1>&2; ./forky 7 2; \
    echo 1>&2; \
    echo "Pattern 3:" 1>&2; ./forky 8 3) \
    2> results.txt

clean:
    rm -f forky


