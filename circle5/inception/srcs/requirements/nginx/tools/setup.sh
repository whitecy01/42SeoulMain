#!/bin/sh

openssl req -newkey rsa:4096 -days 30 -nodes -x509 \
    -subj "/C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=${COALITIONS}/CN=${INTRA_ID}.42.fr" \
    -keyout "/etc/ssl/${INTRA_ID}.42.fr.key" \
    -out "/etc/ssl/${INTRA_ID}.42.fr.crt" 2>/dev/null

echo "\
--------------------

@nginx ready
@port:443

--------------------"

exec nginx -g 'daemon off;'