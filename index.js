try {
  module.exports = require('./build/Release/memcached.node').MemcachedClient;
} catch(err) {
  module.exports = require('./build/Debug/memcached.node').MemcachedClient;
}
