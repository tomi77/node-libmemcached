const MemcachedClient = require('../index')
const {assert} = require('chai')

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
      assert.equal(mcc.get('test').compare(Buffer.from('1')), 0)
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
    it('should return reference to MemcachedClient object', () => {
      assert.equal(mcc.touch('test', 1000), mcc)
    })
  })

  describe('#delete', () => {
    it('should throws error, when key is not provided', () => {
      fn = () => mcc.delete()
      assert.throws(fn)
    })
    it('should throws error, when key is not exist', () => {
      fn = () => mcc.delete('not_existent_key')
      assert.throws(fn)
    })
    it('should return reference to MemcachedClient object', () => {
      assert.equal(mcc.delete('to_del'), mcc)
    })
    it('should delete item', () => {
      mcc.delete('to_del2')
      assert.isUndefined(mcc.get('to_del2'))
    })
  })

  describe('#increment', () => {
    it('should throws error, when key is not provided', () => {
      fn = () => mcc.increment()
      assert.throws(fn)
    })
    it('should throws error, when offset is not integer', () => {
      fn = () => mcc.increment('test', '1')
      assert.throws(fn)
      fn = () => mcc.increment('test', 'q')
      assert.throws(fn)
      fn = () => mcc.increment('test', 1.23)
      assert.throws(fn)
    })
    it('should throws error, when key is not exist', () => {
      fn = () => mcc.increment('not_existent_key')
      assert.throws(fn)
    })
    it('should throws error, when value is not integer', () => {
      fn = () => mcc.increment('str')
      assert.throws(fn)
    })
    if (process.env.DISABLE_INC_DEC_TEST == null) {
      it('should increment by 1 by default', () => {
        assert.equal(mcc.increment('test'), 2)
      })
      it('should increment by provided value', () => {
        assert.equal(mcc.increment('test', 2), 4)
      })
    }
  })

  describe('#decrement', () => {
    it('should throws error, when key is not provided', () => {
      fn = () => mcc.decrement()
      assert.throws(fn)
    })
    it('should throws error, when offset is not integer', () => {
      fn = () => mcc.decrement('test', '1')
      assert.throws(fn)
      fn = () => mcc.decrement('test', 'q')
      assert.throws(fn)
      fn = () => mcc.decrement('test', 1.23)
      assert.throws(fn)
    })
    it('should throws error, when key is not exist', () => {
      fn = () => mcc.decrement('not_existent_key')
      assert.throws(fn)
    })
    it('should throws error, when value is not integer', () => {
      fn = () => mcc.decrement('str')
      assert.throws(fn)
    })
    if (process.env.DISABLE_INC_DEC_TEST == null) {
      it('should decrement by 1 by default', () => {
        assert.equal(mcc.decrement('test'), 3)
      })
      it('should decrement by provided value', () => {
        assert.equal(mcc.decrement('test', 2), 1)
      })
    }
  })

  describe('#set', () => {
    it('should throws error, when key is not provided', () => {
      fn = () => mcc.set()
      assert.throws(fn)
    })
    it('should throws error, when value is not provided', () => {
      fn = () => mcc.set('net_key')
      assert.throws(fn)
    })
    it('should throws error, when value is boolean', () => {
      fn = () => mcc.set('bool_key', true)
      assert.throws(fn)
    })
    it('should throws error, when value is null', () => {
      fn = () => mcc.set('null_key', null)
      assert.throws(fn)
    })
    it('should throws error, when value is undefined', () => {
      fn = () => mcc.set('undef_key', undefined)
      assert.throws(fn)
    })
    it('should throws error, when value is function', () => {
      fn = () => mcc.set('func_key', () => {})
      assert.throws(fn)
    })
    it('should throws error, when value is object', () => {
      fn = () => mcc.set('func_key', {'a': 1})
      assert.throws(fn)
    })
    it('should throws error, when value is Array', () => {
      fn = () => mcc.set('func_key', [1, 2, 3])
      assert.throws(fn)
    })
    it('should return reference to MemcachedClient object', () => {
      assert.equal(mcc.set('ref_test', 'ref'), mcc)
    })
    it('should store Buffer value', () => {
      mcc.set('buf_key', Buffer.from('val'))
      assert.equal(mcc.get('buf_key').compare(Buffer.from('val')), 0)
    })
    it('should store string value', () => {
      mcc.set('str_key', 'val')
      assert.equal(mcc.get('str_key').compare(Buffer.from('val')), 0)
    })
    it('should store float value', () => {
      mcc.set('num_key', 1.23)
      assert.equal(parseFloat(mcc.get('num_key').toString()), 1.23)
    })
    it('should store integer value', () => {
      mcc.set('int_key', 2)
      assert.equal(parseInt(mcc.get('int_key').toString()), 2)
    })
  })
})
