set TOOLCHAIN /home/seven7/Application/loongson-gnu-toolchain-8.3-x86_64-loongarch32r-linux-gnusf-v2.0/bin

set -x PATH $TOOLCHAIN $PATH

set -x CHIPLAB_HOME $(realpath ./)

echo "Loongson toolchain path is set to $TOOLCHAIN"
echo "CHIPLAB_HOME is set to $CHIPLAB_HOME $(realpath ./)"
