sudo aptitude update
sudo aptitude -y upgrade
sudo sh -c "wget -qO- https://get.docker.io/gpg | apt-key add -"
sudo sh -c "echo deb http://get.docker.io/ubuntu docker main > /etc/apt/sources.list.d/docker.list"
sudo aptitude update
curl -sSL https://get.docker.com/ | sh
sudo usermod -aG docker healem

