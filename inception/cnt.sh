echo -ne "\033[0;33mWaiting"
for i in {12..01}
do
echo -en "."
sleep 1
done
echo 
echo -e "\033[32mCOMPLETE!\033[0m"