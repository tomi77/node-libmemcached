// Type definitions for libmemcached
// TypeScript Version: 2.3

/**
 * @summary A memcached client.
 * @class
 */
export default class MemcachedClient {
  /**
   * Constructor.
   * @constructor
   * @param {string} config Configuration string.
   */
  constructor(config: string);

  /**
   * Store item.
   * @param {string}                   key        The key.
   * @param {Buffer | string | number} value      The value to store.
   * @param {integer}                  expiration Expiration time in seconds.
   * @return {MemcachedClient}
   */
  set(key: string, value: Buffer | string | number, expiration?: integer=0): MemcachedClient;

  /**
   * Add item. If key does exist - do nothing.
   * @param {string}                   key        The key.
   * @param {Buffer | string | number} value      The value to store.
   * @param {integer}                  expiration Expiration time in seconds.
   * @return {MemcachedClient}
   */
  add(key: string, value: Buffer | string | number, expiration?: integer=0): MemcachedClient;

  /**
   * Replace item. If key doesn't exist - do nothing.
   * @param {string}                   key        The key.
   * @param {Buffer | string | number} value      The value to store.
   * @param {integer}                  expiration Expiration time in seconds.
   * @return {MemcachedClient}
   */
  replace(key: string, value: Buffer | string | number, expiration?: integer=0): MemcachedClient;

  /**
   * Get item.
   * @param {string} key The key.
   * @return {Buffer | undefined}
   */
  get(key: string): Buffer | undefined;

  /**
   * Determine if a item exists.
   * @param {string} key The key.
   * @return {boolean}
   */
  exist(key: string): boolean;

  /**
   * Update the expiration time of an existing item without fetching it.
   * @param {string}  key        The key.
   * @param {integer} expiration Expiration time in seconds.
   */
  touch(key: string, expiration: integer): MemcachedClient;

  /**
   * Remove a item.
   * @param {string} key The key.
   */
  delete(key: string): MemcachedClient;

  /**
   * Incrementing item.
   * @param {string}  key    The key.
   * @param {integer} offset The increment step.
   */
  increment(key: string, offset?: integer=1): integer;

  /**
   * Decrementing item.
   * @param {string}  key    The key.
   * @param {integer} offset The increment step.
   */
  decrement(key: string, offset?: integer=1): integer;
}
