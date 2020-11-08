#!/usr/bin/env bash

# Assignment (refer to the file called datebook below).  Search the 'datebook' file for the below:
file="./datebook.txt"

# Print all lines containing the string San
echo "Lines containing string 'San':"

grep San $file

# Print all lines where the person’s first name starts with J.
echo
echo "First name starting with 'J':"
grep '^J[A-Za-z]' $file

# Print all lines ending in 700
echo
echo "All lines ending in '700':"
grep -E "700$" $file

# Print all lines that don’t contain 834
echo
echo "All lines that don't contain 834:"
grep -v "834" $file

# Print all lines where birthdays are in December (assume the user does not know the details of the file format, assume no colon precedes the month)
echo
echo "All birthdays in Dec: "
grep -E "12\/(([0-2]*[0-9])|(3[01]))\/[0-9]{2}" $file

# Print all lines where the phone number is in the 408 area code (same as previous question, assume no colon precedes the area code)
echo
echo "408 area code:"
grep -E "408-[0-9]{3}-[0-9]{4}" $file

# Print all lines containing an uppercase letter, followed by four lowercase letters, a comma, a space, and one uppercase letter.
echo
echo "Uppercase, 4 lowercase, comma, space, one uppercase:"
grep -E "[[:upper:]][[:lower:]]{4}, [[:upper:]]" $file

# Print lines where the last name begins with K or k.
echo
echo "Last name begins with K or k:"
grep -E "^[A-Za-z]+ [Kk][A-Za-z]+" $file

# Print lines preceded by a line number where the salary is a six-figure number
echo
echo "Lines before 6 figures:"
grep -E -B 1 "[1-9][0-9]{5}$" $file

# Print lines containing Lincoln or lincoln (remember that grep is sensitive to case)
echo
echo "Lincoln or lincoln:"
grep "[Ll]incoln" $file