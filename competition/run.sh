cp start.txt output.txt
a=0
b=0
for i in {1..32}
do
echo "No. ${i} turn."
start=`date +%s`
./agent1
end=`date +%s`
a=`expr $a + $[end-start]`
./check1
start=`date +%s`
./agent2
end=`date +%s`
b=`expr $b + $[end-start]`
./check2
done
echo "Agent 1 running time: ${a}"
echo "Agent 2 running time: ${b}"