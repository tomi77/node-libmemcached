const MemcachedClient = require('../index')
const assert = require('chai').assert

const mcc = new MemcachedClient('--SERVER=127.0.0.1')

describe('MemcachedClient', () => {
  describe('#get', () => {
    it('should throws error, when key is not provided', () => {
      fn = () => mcc.get()
      assert.throws(fn)
    })
    it('should return Buffer object', () => {
      assert.instanceOf(mcc.get('test'), Buffer)
    })
    it('should return stored value', () => {
      assert.equal(mcc.get('test').compare(Buffer.from('test')), 0)
    })
    it('should return "undefined" when key doesn\'t exist', () => {
      assert.isUndefined(mcc.get('not_existent_key'))
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

  describe('#touch', () => {
    it('should throw a exception when key not exist', () => {
      fn = () => mcc.touch('not_existent_key', 1000)
      assert.throws(fn)
    })
    it('shouldn\'t throw a exception when key exist', () => {
      fn = () => mcc.touch('test', 10000)
      assert.doesNotThrow(fn)
    })
    it('should return "undefined"', () => {
      assert.isUndefined(mcc.touch('test', 1000))
    })
  })
})
