echo "25BCE2202" 
read num
copy=$num 
rev=0
len=${#copy} 
mult=$(( 10 ** ($len - 1) ))
while [[ copy -gt 0 ]]; do 
    (( rev += (( copy % 10)) * $mult )) 
    (( copy /= 10 ))
    (( mult /= 10 )) 
done 
echo $rev
