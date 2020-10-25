# Write a sed script that will:
    # a) Insert above the first line the title PERSONNEL FILE.
    # b) Remove the salaries ending in 500
    # c) Print the contents of the file with the last names and first names reversed
    # d) Append at the end of the file THE END
# a
1i PERSONNEL FILE
# b
/500$/ s/:[0-9]\+$//
# c
s/^\([A-Za-z]\+\) \([A-Za-z]\+\):/\2 \1:/
# d
$aTHE END
