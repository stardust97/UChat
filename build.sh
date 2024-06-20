#！/bin/bash
set -o errexit

DIR=`pwd`
# if [ -d build ]; then
#   rm -rf uchat
# fi

# mkdir uchat

cd ${DIR}/Client
  bash build.sh $* 
cd ${DIR}/ChatServer
  bash build.sh $* 
cd ${DIR}/GateServer
  bash build.sh $* 
cd ${DIR}/VerifyServer
  bash build.sh $* 

