#!/bin/sh
set -ex

(
curl -OL http://ftpmirror.gnu.org/autoconf/autoconf-2.69.tar.gz
tar -xzf autoconf-2.69.tar.gz 
cd autoconf-2.69
./configure && make && sudo make install
)

(
curl -OL http://ftpmirror.gnu.org/automake/automake-1.14.tar.gz
tar -xzf automake-1.14.tar.gz
cd automake-1.14
./configure && make && sudo make install
)

(
curl -OL http://ftpmirror.gnu.org/libtool/libtool-2.4.2.tar.gz
tar -xzf libtool-2.4.2.tar.gz
cd libtool-2.4.2
./configure && make && sudo make install
)

(
curl -OL http://pkgconfig.freedesktop.org/releases/pkg-config-0.28.tar.gz
tar -xzf pkg-config-0.28.tar.gz
cd pkg-config-0.28
./configure --with-internal-glib && make && sudo make install
)

(
curl -OL http://ftpmirror.gnu.org/gettext/gettext-0.18.3.tar.gz
tar -xzf gettext-0.18.3.tar.gz
cd gettext-0.18.3
./configure && make && sudo make install
)

(
curl -OL http://www.tortall.net/projects/yasm/releases/yasm-1.3.0.tar.gz
tar -xzf yasm-1.3.0.tar.gz
cd yasm-1.3.0
./configure && make && sudo make install
)

(
curl -OL https://raw.githubusercontent.com/yuvi/gas-preprocessor/master/gas-preprocessor.pl
sudo install -m 755 gas-preprocessor.pl /usr/local/bin
)