#!/bin/bash

# this script counts the number of all the preprocessor commands in all the c
# files in a given directory.

# Parameters:
#
#  dir - directory we want to count preprocessor commands in.
#
# Returns:
#
#  number of the preprocessor commands.

dir="$1"
counter=`gcc -E -dM "$dir"/*.c | wc -l`
echo $counter