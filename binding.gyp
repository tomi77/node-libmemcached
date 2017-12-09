{
  'targets': [
    {
      'target_name': 'memcached',
      'sources': ['src/binding.cc'],
      'include_dirs' : ["<!(node -e \"require('nan')\")"],
      'link_settings': {
        'libraries': ['-lmemcached']
      }
    }
  ]
}
