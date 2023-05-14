#1
printf "#Architecture: "
uname -a

#2
printf "#CPU phusical : "
grep 'cpu cores' /proc/cpuinfo | tail -l | wc -l

#3
printf "#vCPU : "
grep -c processor /proc/cpuinfo

#4
printf "#Memory Usage: "
free | grep Mem | awk '{printf"%d/%dMB (%.2f%%)\n", $3, $2, $3/$2 * 100 }'

#5
printf "#Disk Usage: "
df -Bm | grep /dev/map | awk '{sum += $3}END{print sum}' | tr -d "\n"
printf "/"
df -BG | grep /dev/map | awk '{sum += $2}END{print sum}' | tr -d "\n"
printf "Gb ("
df -Bm | grep /dev/map | awk '{sum1 += $3 ; sum2 += $2 }END{printf "%d%%)\n", sum1 / sum2 * 100}'


#6
#apt install sysstat
printf "#CPU load: "
mpstat | grep all | awk '{printf "%.2f%%\n", 100-$13}'

#7
printf "#Last boot: "
who -b | awk '{print $3, $4}'

#8
printf "#LVM use: "
lsblk | grep lvm | wc -l | awk '{if($NF > 0) {print "yes"} else {print "no"}}'

#9
printf "#Connections TCP : "
ss | grep -i tcp | wc -l | awk '{if($NF == 0) {print $NF" ""NONE"} else if ($NF >= 1) {print $NF" ""ESTABLISHED"}}'

#10
printf "#User log: "
who | wc -l

#11
printf "#Netwrok: IP "
hostname -I | tr -d "\n"
printf "("
ip addr | grep ether | awk '{print $2}' | tr -d "\n"
printf ")\n"

#12
printf "#Sudo : "
journalctl _COMM=sudo | wc -l | tr -d "\n"
printf " cmd\n"
