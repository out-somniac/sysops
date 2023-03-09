touch results/report.txt
echo "" > results/report.txt
for filename in results/*.test
do
	echo "$filename" >> results/report.txt
    echo "<-------------->" >> results/report.txt
    cat "$filename" >> results/report.txt
done