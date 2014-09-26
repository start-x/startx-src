#!/bin/bash

sudo apt-get install puppet
sudo puppet apply --modulepath=./puppet/modules/ ./puppet/manifests/site.pp

