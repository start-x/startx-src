#!/bin/bash

dpkg -l puppet
if [ $? != 0 ]; then
  sudo apt-get install puppet
fi

sudo puppet apply --modulepath=./puppet/modules/ ./puppet/manifests/site.pp

