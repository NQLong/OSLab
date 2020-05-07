first:
	sudo apt-get update
	sudo apt-get install build-essential
	sudo apt-get install kernel-package
	mkdir ~/kernelbuild
	cd ~/kernelbuild
	wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.4.20.tar.xz
	tar -xvJf linux -4.4.21.tar.xz
second:
	cp /boot/config-3.13.0-32-generic ~/kernelbuild/.config
	sudo apt-get install libncurses5-dev
	cd ~/kernelbuild/linux-4.4.21
	make ncofig
