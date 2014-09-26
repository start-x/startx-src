#!/bin/bash

sudo apt-get install puppet
puppet module install --modulepath=./puppet/modules tracywebtech-pip
sudo puppet apply --modulepath=./puppet/modules/ ./puppet/manifests/site.pp

