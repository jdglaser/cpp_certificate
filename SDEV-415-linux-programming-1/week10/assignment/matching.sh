cd ./wildcards
shopt -s extglob
ls a*
ls *+([0-9])
ls [aA]*
ls *.+([0-9])
ls *+([xyXY])
ls *+([0-9A-Za-z])