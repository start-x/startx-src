
class bike-x::os::debian {

  include pip

  $packages = ['python2.7','python-serial','python2.7-dev',
        'doxygen','graphviz','dots','binutils-msp430',
        'gcc-msp430','msp430-libc','msp430mcu','mspdebug',
        'libxext-dev','mesa-common-dev','freeglut3-dev',
        'libxinerama-dev','libxrandr-dev','libxxf86vm-dev',
        'swig']

  exec { 'update':
    command => "apt-get update",
    path    => "/usr/bin/",
  }

  package { $packages:
    ensure  => installed,
    require => Exec['update'],
  }

  pip::install { 'pyserial':
    package => 'pyserial',
    version => '2.7',
    python_version => '',
    ensure  => present,
  }

  pip::install { 'mock':
    package => 'mock',
    version => '1.0.1',
    python_version => '',
    ensure  => present,
  }

  file { "90-oculus.rules":
    ensure  => present, 
    path    => "/lib/udev/rules.d/90-oculus.rules",
    content => 'KERNEL=="hidraw*", SUBSYSTEM=="hidraw", ATTRS{idVendor}=="2833", MODE="0666"',
  }

  exec { 'link libudev':
    command => "ln -sf /lib/x86_64-linux-gnu/libudev.so.1 /usr/lib/libudev.so",
    path    => "/bin/",
  }
}

