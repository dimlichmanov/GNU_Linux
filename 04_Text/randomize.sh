full_text=""
total_len=0
IFS=''

# Elements with a row offset - scan (acc sum) values
csr=()

while read -r line; do
  line_len=$(echo ${line} | wc -m)
  full_text="$full_text $line"
  column_counter=$(($column_counter + 1))
  csr+=("$total_len")
  total_len=$((total_len + line_len))
done
csr+=("$total_len")

IFS=' '
shfl=($(seq 0 $(($total_len - 1)) | shuf | paste - -s -d ' '))

tput clear

sleep_time='0.01'
if [ $# -eq 1 ]; then sleep_time=$1; fi

for global_idx in ${shfl[*]}; do
  sleep $sleep_time
  row_idx=0
  loop_count=0
  for j in "${csr[@]}"; do
    if [ $global_idx -gt $j ]; then row_idx=$loop_count; fi
    ((loop_count++))
  done

  col_idx=$(($global_idx - ${csr[$row_idx]}))
  tput cup $row_idx $col_idx
  symb=${full_text:$global_idx:1}
  echo $symb
done

sleep 5
