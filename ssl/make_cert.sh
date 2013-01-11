#!/bin/sh

# make CA cert
if [ ! -f ca.crt ]; then
	openssl req -config tibanne.cnf -batch -newkey rsa:4096 -nodes -keyout ca.key -out ca.req
	openssl x509 -req -signkey ca.key -extfile tibanne.cnf -set_serial 0 -extensions v3_ca -days 6000 -in ca.req -out ca.crt
	rm ca.req
fi

# make server cert
if [ ! -f server.crt ]; then
	openssl req -config tibanne.cnf -batch -subj "/C=JP/ST=Tokyo/L=Shibuya/O=Tibanne Co. Ltd./OU=EFTP/CN=localhost" -newkey rsa:4096 -nodes -keyout server.key -out server.req
	openssl x509 -req -CA ca.crt -CAkey ca.key -extfile tibanne.cnf -set_serial 1 -extensions v3_notca_server -days 365 -in server.req -out server.crt
	rm server.req
fi

# make client certs
CUR_SERIAL=1
for foo in client1 client2 client3 client4; do
	CUR_SERIAL=$[ $CUR_SERIAL + 1 ]
	if [ ! -f "${foo}.crt" ]; then
		openssl req -config tibanne.cnf -batch -subj "/C=JP/ST=Tokyo/L=Shibuya/O=Tibanne Co. Ltd./OU=EFTP/CN=${foo}" -newkey rsa:4096 -nodes -keyout "${foo}.key" -out "${foo}.req"
		openssl x509 -req -CA ca.crt -CAkey ca.key -extfile tibanne.cnf -set_serial $CUR_SERIAL -extensions v3_notca_client -days 365 -in "${foo}.req" -out "${foo}.crt"
		rm "${foo}.req"
	fi
done

