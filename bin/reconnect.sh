#i use this script to try to reconnect wifi until successful 
echo -n "enter SSID: "
read ssid
while true; do
		connect="$(nmcli device wifi connect "$ssid")"
		case $connect in
				*'successfully'*) $(notify-send "reactivated $ssid"); break;;
		esac
        sleep 1
done
