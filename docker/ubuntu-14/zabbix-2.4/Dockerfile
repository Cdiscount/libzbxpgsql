FROM ubuntu:trusty

ENV DEBIAN_FRONTEND noninteractive

RUN \
	apt-get -q update && \
	apt-get -y install wget && \
	wget -nv http://repo.zabbix.com/zabbix/2.4/ubuntu/pool/main/z/zabbix-release/zabbix-release_2.4-1+trusty_all.deb && \
	dpkg -i zabbix-release_2.4-1+trusty_all.deb && \
	apt-get -q update && \
	apt-get -y install zabbix-agent libpq5
	
COPY entrypoint.sh /entrypoint.sh

CMD /entrypoint.sh
