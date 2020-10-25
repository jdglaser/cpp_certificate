# SDEV-415 Assignment Week 08 Questions 1-9
file=datebook.txt
# Change the name Jon to Jonathan
echo "Change the name Jon to Jonathan"
sed 's,Jon,Jonathon,g' $file
echo

# Delete the first three lines
echo "Delete the first three lines"
sed '1,3d' $file
echo

# Print lines 5 through 10
echo "Print lines 5 through 10"
sed -n '5,10p' $file
echo

# Delete lines containing Lane
echo "Delete lines containing Lane"
sed '/Lane/d' $file
echo

# Print all lines where the birthdays are in November or December
echo "Print all lines where the birthdays are in November or December"
sed -n '/\(11\|12\)\/[0-9]\+\/[0-9][0-9]/p' $file
echo

# Append three asterisks to the end of lines starting with Fred
echo "Append three asterisks to the end of lines starting with Fred"
sed -n '/^Fred/ s/$/***/p' $file
echo

# Replace the line containing Jose with JOSE HAS RETIRED.
echo "Replace the line containing Jose with JOSE HAS RETIRED"
sed '/Jose/c JOSE HAS RETIRED' $file
echo

# Change Popeye ’s birthday to 11/14/46. Assume you don’t know Popeye ’s original birthday. Use a regular expression to search for it.
echo "Change Popeye ’s birthday to 11/14/46. Assume you don’t know Popeye ’s original birthday. Use a regular expression to search for it."
sed -n '/^Popeye/ s/[0-9]\+\/[0-9]\+\/[0-9][0-9]/11\/14\/46/p' $file
echo

# Delete all blank lines.
echo "Delete all blank lines."
sed '/^$/d' $file
echo