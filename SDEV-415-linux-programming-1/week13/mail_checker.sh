#! /bin/bash

prevSize=$(wc -c /var/spool/mail/jarred/mail | awk '{print $1}')

while true
do 
echo "Checking for new mail..."
curSize=$(wc -c /var/spool/mail/jarred/mail | awk '{print $1}')
if [ $curSize -gt $prevSize ]
then
echo "$USER, You have mail!"
prevSize=$(wc -c /var/spool/mail/jarred/mail | awk '{print $1}')
else
echo "No new mail :("
fi
sleep 5
done