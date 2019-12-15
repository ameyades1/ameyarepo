
sudo apt-get install samba
whereis samba
sudo vim /etc/samba/smb.conf 
sudo service smbd restart
sudo smbpasswd -a adeswand
sudo service smbd restart
