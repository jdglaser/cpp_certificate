#! /bin/bash

# Jarred Glaser
# 12/4/2020
# A menu selection program

enjoy="Enjoy your meal!"

select varName in "Steak and potatoes" "Fish and chips" "Soup and salad"
do
	case $varName in
		"Steak and potatoes")
			echo -e "Stick to your ribs\nWatch your cholesterol.\n$enjoy";;
		"Fish and chips")
			echo -e "British are coming!\n$enjoy";;
		"Soup and salad")
			echo -e "Health foods…\nDieting is so boring.\n$enjoy";;
		*)
			echo "Sorry...that isn't on the menu";;
	esac			
done