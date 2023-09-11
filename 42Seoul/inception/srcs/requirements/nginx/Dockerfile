FROM debian:buster

ARG INTRA=gyeon

RUN apt-get update -y && apt-get upgrade -y && \
    apt-get install nginx openssl -y && \
    mkdir -p /etc/nginx/ssl /var/run/nginx /var/run/php/ && \
    openssl req -new -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
        -out /etc/nginx/ssl/$INTRA.42.fr.crt \
        -keyout /etc/nginx/ssl/$INTRA.42.fr.key \
        -subj "/C=KR/ST=Seoul/L=Songpa-gu/O=42/OU=42Seoul/CN=${INTRA}.42.fr" &&\
        chmod 600 /etc/nginx/ssl/$INTRA.42.fr.crt /etc/nginx/ssl/$INTRA.42.fr.key && \
        rm -rf /etc/nginx/conf.d/default.conf && \
        chown -R www-data:www-data /var/run/nginx /var/run/php/

COPY conf/default.conf /etc/nginx/conf.d/default.conf
COPY tools/setting.sh /tmp/setting.sh
RUN chmod +x /tmp/setting.sh
EXPOSE 443
ENTRYPOINT ["sh", "-c", "/tmp/setting.sh"]