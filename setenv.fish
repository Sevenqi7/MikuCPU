set TOOLCHAIN /home/seven7/Applications/loongson-gnu-toolchain-8.3-x86_64-loongarch32r-linux-gnusf-v2.0/bin
set -x PATH $TOOLCHAIN $PATH

set -x CHIPLAB_HOME $(realpath ./chiplab)

set -x NPC_HOME $(realpath ./simulators/npc)
set -x AM_HOME $(realpath ./simulators/abstract-machine)

echo "Loongson toolchain path is set to $TOOLCHAIN"
echo "CHIPLAB_HOME is set to $CHIPLAB_HOME"
echo "NPC_HOME is set to $NPC_HOME"
echo "AM_HOME is set to $AM_HOME"