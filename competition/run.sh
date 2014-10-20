cp start.txt output.txt
cp temp1.txt log.txt
cp temp2.txt count.txt
cp temp2.txt time.txt
set a=0
set b=0
for i in {1..32}
do
echo "No. ${i} turn."
./agent1
./check1
./agent2
./check2
done