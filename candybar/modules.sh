#!/bin/sh
# candybar modules

module_date() {
	export bar="${bar}${1}$(date +'%a %Y-%m-%d %R')${2}"
}

module_mpc() {
	mpcoutput="$(mpc | grep -v '\[.*\]' | grep -v 'volume:')"
	[ "$mpcoutput" = "" ] || export bar="${bar}${1}${mpcoutput}${2}"
}

module_uptime() {
	export bar="${bar}${1}$(uptime -p | sed 's/up // ; s/ year.*/y/ ; s/ week.*,/w/ ; s/ day.*,/d/ ; s/ hour.*,/h/ ; s/ minute.*/m/')${2}"
}

module_ram() {
	export bar="${bar}${1}$(free -h | awk '/^Mem/ { print $3"/"$2 }' | sed s/i//g)${2}"
}

module_user() {
	export bar="${bar}${1}$(whoami)@$(cat /proc/sys/kernel/hostname)${2}"
}

module_vol() {
	export bar="${bar}${1}$(if command -v pamixer > NULL; then pamixer --get-volume; else amixer sget Master | awk -F'[][]' '/Mono:/ { print $2 }'; fi)${2}"
}

module_kernel() {
	export bar="${bar}${1}$(sed "s/version // ; s/ (.*//" /proc/version)${2}"
}

module_loadavg() {
	export bar="${bar}${1}$(uptime | sed 's/.*load average: //')${2}"
}

module_weather() {
	export bar="${bar}${1}$(curl -s 'wttr.in/?format=1' | sed 's/.* //')${2}"
}

module_du() {
	export bar="${bar}${1}$(df -T / | awk '{if (NR!=1) {print $6}}')${2}"
}

module_ip() {
	export bar="${bar}${1}$(ip -f inet a | awk '/inet / { print $2 }' | tail -n 1 | sed 's/\/.*//')${2}"
}

module_cpu() {
	# https://github.com/speediegamer/xshbar-plugins/blob/main/cpustatus.plugin
	export bar="${bar}${1}$(top -bn1 | grep 'Cpu(s)' | sed 's/.*, *\([0-9.]*\)%* id.*/\1/' | awk '{print 100 - $1"%"}')${2}"
}

module_battery() {
	export bar="${bar}${1}$(cat /sys/class/power_supply/BAT0/capacity)%${2}"
}

module_todo() {
	todooutput="$(head -n 1 ~/.todo.txt)"
	[ "$todooutput" = "" ] || export bar="${bar}${1}${todooutput}${2}"
}

module_upload() {
	# https://github.com/speediegamer/xshbar-plugins/blob/main/netstat.plugin
	up="$(cat /sys/class/net/${netdevice}/statistics/rx_bytes | awk '{$1=$1/1024000; print $1"B";}' | tail -n 1)"
	export bar="${bar}${1}${up}${2}"
}

module_download() {
	# https://github.com/speediegamer/xshbar-plugins/blob/main/netstat.plugin
	down="$(cat /sys/class/net/${netdevice}/statistics/tx_bytes | awk '{$1=$1/1024000; print $1"B";}' | tail -n 1)"
	export bar="${bar}${1}${down}${2}"
}

module_mail() {
	mailoutput="$(ls ${maildir} | wc -l)"
	[ "$mailoutput" = "0" ] || export bar="${bar}${1}${mailoutput}${2}"
}

module_dfmpeg() {
	[ -f "/tmp/dfmpeg-recording" ] && export bar="${bar}${1}${2}"
}
