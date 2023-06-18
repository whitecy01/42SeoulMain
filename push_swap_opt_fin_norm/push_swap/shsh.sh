CNT=100
LIMIT=700	#만점기준
INDEX=0
ITER=15000
SUM=0
NUM_OVER=0
MAX=$LIMIT
ARG=`jot -r $CNT -2147483648 2147483647 | tr "\n" " "`
NUM=`./push_swap $ARG | wc -l`
while [ $INDEX -lt $ITER ]
do
echo "$INDEX	:	$NUM"
if [ $NUM -ge $LIMIT ]; then
NUM_OVER=`expr $NUM_OVER + 1`
fi
if [ $NUM -gt $MAX ]; then
MAX=$NUM
fi
SUM=`expr $SUM + $NUM`
ARG=`jot -r $CNT -2147483648 2147483647 | tr "\n" " "`
NUM=`./push_swap $ARG | wc -l`
INDEX=`expr $INDEX + 1`
done
echo "cnt: $CNT"
echo "$NUM_OVER overred operations for $ITER times (Average: `expr $SUM / $ITER`)"
if [ $NUM_OVER -gt 0 ]; then
echo "Biggest operation number : $MAX"
echo "fix it!!!!!!!!!!"
fi
