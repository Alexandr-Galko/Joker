#!/bin/bash          
# This script runs Doxygen an throw an error if
# Doxygen generate an error log

if [ $# -gt 1 ]
then
    echo "Unproper usage, you should give me only one argument"
    exit 1
fi

#run the doxygen
pwd
echo "Running Doxygen...";

if [ $# -eq 1 ]
then
    /usr/local/bin/doxygen $1 &> /dev/null
else
    /usr/local/bin/doxygen .doxygen &> /dev/null
fi

echo "Done";

if [ `more doxygen_error.log | wc -l` -eq 0 ];
then
    echo ".__   __.  __    ______  _______     __  ";
    echo "|  \ |  | |  |  /      ||   ____|   |  | ";
    echo "|   \|  | |  | |  ,----'|  |__      |  | ";
    echo "|  .    | |  | |  |     |   __|     |  | ";
    echo "|  |\   | |  | |   ----.|  |____    |__| ";
    echo "|__| \__| |__|  \______||_______|   (__) ";
    exit 0;
else
    cat doxygen_error.log;
    echo "";
    if [ `more doxygen_error.log | wc -l` -lt 10 ]
    then
        echo " ----------------------------------------------------------";
        echo "| Doxygen founds" `more doxygen_error.log | wc -l` "errors (not bad, but you can do better !)|";
        echo " ----------------------------------------------------------";
    elif [ `more doxygen_error.log | wc -l` -lt 100 ]
    then
        echo " ---------------------------------------";
        echo "| Doxygen founds" `more doxygen_error.log | wc -l` "errors (this is bad) |";
        echo " ---------------------------------------";
    else
        echo " --------------------------------------------";
        echo "| Doxygen founds" `more doxygen_error.log | wc -l` "errors (this is very bad) |";
        echo " --------------------------------------------";
    fi
    exit 1;
fi
