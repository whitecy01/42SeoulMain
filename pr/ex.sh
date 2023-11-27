ckage in $(sudo apt-get install catdoc 2>&1 | grep "warning: files list file for package '" | grep -Po "[^'\n ]+'" | grep -Po "[^']+");
do
	`  sudo apt-get -y install --reinstall "$package"
  done
