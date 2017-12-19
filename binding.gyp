{
  'targets': [
    {
      'target_name': 'memcached',
      'cflags': ['-Wall', '-std=c++11'],
      'sources': [
        'src/auto.cc',
        'src/binding.cc',
        'src/delete.cc',
        'src/exist.cc',
        'src/get.cc',
        'src/storage.cc',
        'src/touch.cc'
      ],
      'variables': {
        'TRAVIS%': '<!(node -e "console.log(process.env.TRAVIS)")',
        'HOME%': '<!(node -e "console.log(process.env.HOME)")',
      },
      'include_dirs': ["<!(node -e \"require('nan')\")"],
      'conditions': [
        ["TRAVIS == 'true'", {
          'cflags+': ['-fPIC'],
          'include_dirs+': ["<(HOME)/include"],
          'link_settings': {
            'libraries': ['<(HOME)/lib/libmemcached.a']
          }
        }, {
          'link_settings': {
            'libraries': ['-lmemcached']
          }
        }]
      ]
    }
  ]
}
