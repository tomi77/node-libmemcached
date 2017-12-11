{
  'targets': [
    {
      'target_name': 'memcached',
      'sources': [
        'src/binding.cc',
        'src/delete.cc',
        'src/exist.cc',
        'src/get.cc',
        'src/touch.cc'
      ],
      'include_dirs' : ["<!(node -e \"require('nan')\")"],
      'link_settings': {
        'libraries': ['-lmemcached']
      }
    }
  ]
}
