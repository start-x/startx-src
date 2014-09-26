
class bike-x::os::debian {

  $packages = ['python2.7','python-serial','doxygen','graphviz',
        'dots','binutils-msp430','gcc-msp430','msp430-libc',
        'msp430mcu','mspdebug','libudev-dev','libxext-dev',
        'mesa-common-dev','freeglut3-dev','libxinerama-dev',
        'libxrandr-dev','libxxf86vm-dev']

  exec { 'update':
    command => "apt-get update",
    path    => "/usr/bin/"
  }

  package { $packages:
    ensure  => installed,
    require => Exec['update']
  }

  file { "90-oculus.rules":
    ensure  => present, 
    path    => "/lib/udev/rules.d/90-oculus.rules",
    content => 'KERNEL=="hidraw*", SUBSYSTEM=="hidraw", ATTRS{idVendor}=="2833", MODE="0666"',
  }
}

