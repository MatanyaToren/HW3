#!/bin/bash

# this script counts the number of all the preprocessor commands in all the c
# files in a given directory.

# Parameters:
#
#  dir - directory we want to count preprocessor commands inside.
#
# Returns:
#
#  number of the preprocessor commands.

dir="$1"
all_lines=`gcc -E "$dir"/*.c | wc -l`
c_files_lines=`cat "$dir"/*.c | wc -l`
hashtag_lines=`grep "#" "$dir"/*.c | wc -l` # not sure about that.
((counter=$all_lines-$c_files_lines-$hashtag_lines))
echo $counter