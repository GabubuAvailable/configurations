#!/bin/sh
# candybar configuration

# modules location
. "$HOME/.config/candybar/modules.sh"

# module list
# module name           icon/prefix     suffix
#module_mpc              " "            " | "
#module_ram              " "            " | "
#module_cpu              " "            " | "
module_user             " "            "  "
module_ip               " "            " | "
module_vol              " "            "%  "
module_mic              " "              " | "
module_battery          " "             " | "
module_date             " "            " "
