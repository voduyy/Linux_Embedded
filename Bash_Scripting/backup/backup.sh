#!/bin/bash

# Kiểm tra số lượng tham số đầu vào
if [ $# -ne 2 ]; then
    echo "Must have 2 arguments"
    exit 1
fi

# Kiểm tra xem rsync có được cài đặt hay không
if ! command -v rsync &> /dev/null; then
    echo "Must have rsync"
    echo "Installing for you"
    sudo apt-get update && sudo apt-get install -y rsync >> install_log.log
else
    echo "You have rsync ready to run"
fi

# Lấy ngày hiện tại theo định dạng YYYY-MM-DD
current_date=$(date +%Y-%m-%d)

back_up_dir=another_back_up_files
# Đặt các tùy chọn cho rsync
rsync_options="-avb --backup-dir=$back_up_dir/$current_date --delete" #folder do not same name as directory

# Thực hiện lệnh rsync và ghi log
$(which rsync) $rsync_options "$1" "$2" >> "backup_$current_date.log" 2>&1
