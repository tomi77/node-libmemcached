const MemcachedClient = require('../index')
const assert = require('chai').assert

const mcc = new MemcachedClient('--SERVER=127.0.0.1')

describe('MemcachedClient', () => {
  describe('#get', () => {
    it('should return Buffer object', () => {
      assert.instanceOf(mcc.get('test'), Buffer)
    })
    it('should return stored value', () => {
      assert.equal(mcc.get('test').compare(Buffer.from('test')), 0)
    })
  })

  describe('#exist', () => {
    it('should throws error, when key is not provided', () => {
      fn = () => mcc.exist()
      assert.throws(fn)
    })
    it('should return true if key exist', () => {
      assert.isTrue(mcc.exist('test'))
    })
    it('should return false if key not exist', () => {
      assert.isFalse(mcc.exist('not_existent_key'))
    })
  })
})
