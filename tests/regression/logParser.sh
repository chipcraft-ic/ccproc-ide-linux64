#!/bin/bash
logFileName=""
testResultLineArray=""
testResultSuccessArray=""
testResultFailuresArray=""
testResultTotalsArray=""
testErrorsArray=""
testTimeoutArray=""
testCasesArray=""
successNum=0
totalNum=0
failureNum=0
testProgramsNumber=0
testCasesNumber=0
testErrorsCount=0
testTimeoutsCount=0
logFileName="$1"

testCasesArray=`grep -oP "TESTCASE:" "$logFileName"`
for x in $testCasesArray ; do
    testCasesNumber=$(($testCasesNumber + 1))
done
if [ $testCasesNumber -eq 0 ]; then
    testCasesNumber=$(($testCasesNumber + 1))
fi

testErrorsArray=`grep -oP "_ERROR" "$logFileName"`
for x in $testErrorsArray ; do
    testErrorsCount=$(($testErrorsCount + 1))
done

testTimeoutArray=`grep -oP "_TIMEOUT_" "$logFileName"`
for x in $testTimeoutArray ; do
    testTimeoutsCount=$(($testTimeoutsCount + 1))
done

testResultLineArray=`grep "tests succeeded" "$logFileName"`
for x in `echo $testResultLineArray | grep -oP '\/'` ; do
    testProgramsNumber=$(($testProgramsNumber + 1))
done

#succeeded
#echo $testResultLineArray | grep -oP '[0-9]+\/' | grep -oP '[0-9]+[^\/]'
testResultSuccessArray=`echo $testResultLineArray | grep -oP '[0-9]*\/' | grep -oP '[0-9]*[^\/]'`
#echo $testResultSuccessArray
for x in $testResultSuccessArray ; do
    successNum=$(($successNum + $x))
done

#total
#echo $testResultLineArray | grep -oP '\/[0-9]+' | grep -oP '[^\/][0-9]+'
testResultTotalsArray=`echo $testResultLineArray | grep -oP '\/[0-9]*' | grep -oP '[^\/][0-9]*'`
#echo $testResultTotalsArray
for x in $testResultTotalsArray ; do
    totalNum=$(($totalNum + $x))
done

#failed
#echo $testResultLineArray | grep -oP '[0-9]+ tests failed' | grep -oP '[0-9]+'
testResultFailuresArray=`echo $testResultLineArray | grep -oP '[0-9]* tests failed' | grep -oP '[0-9]*'`
#echo $testResultFailuresArray
for x in $testResultFailuresArray ; do
    failureNum=$(($failureNum + $x))
done

#echo "Executed testcases:   $testCasesNumber" >> $logFileName
echo "Test programs number: $testProgramsNumber" >> $logFileName
echo "Tests succedeed:      $successNum" >> $logFileName
echo "Tests failed:         $failureNum" >> $logFileName
echo "Total tests number:   $totalNum" >> $logFileName

if [ $testErrorsCount -gt 0 ]; then
    echo "" >> $logFileName
    echo "Test programs failures detected: $testErrorsCount" >> $logFileName
fi

echo "" >> $logFileName

if [ $(($testErrorsCount + $failureNum)) -gt 0 ]; then
    echo "!!!!! ERRORS DETECTED DURING SIMULATION   !!!!!" >> $logFileName
fi

if [ $testTimeoutsCount -gt 0 ]; then
    echo "!!!!! TIMEOUTS DETECTED DURING SIMULATION !!!!!" >> $logFileName
fi

if [ $(($testErrorsCount + $failureNum + $testTimeoutsCount)) -eq 0 ]; then
    echo "TESTS PASSED" >> $logFileName
fi
