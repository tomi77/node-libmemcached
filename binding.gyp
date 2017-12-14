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
      'include_dirs' : ["<!(node -e \"require('nan')\")"],
      'link_settings': {
        'libraries': ['-lmemcached']
      }
    }
  ]
}
