echo "25BCE2202"
read year
yearval=$(($year % 4)) 
mod100=$(($year % 100)) 
mod400=$(($year % 400)) 

if [ $yearval == 0 ]; then
    if [ $mod100 == 0 ]; then 
        if [ $mod400 == 0 ]; then 
            echo "Leap Year!" 
        else
            echo "Not a Leap Year!" 
        fi 
    else 
        echo "Leap Year!" 
    fi
else
    echo "Not a Leap Year!"
fi 